#!/usr/bin/perl -w
require 5.002;
#use strict;
BEGIN { $ENV{PATH} = '/usr/ucb:/bin' }
use Socket;
use Carp;
use FileHandle;

system("ulimit -s 2048");
# make output dir
if (! -d "dbdriver")
{
        unless (mkdir("dbdriver", 0755)) { die "create dbdriver directory failed $!"; }
}
else
{
	system("rm dbdriver/*");
}
if (! -d "appserver")
{
        unless (mkdir("appserver", 0755)) { die "create appserver directory failed $!"; }
}
else
{
	system("rm appserver/*");
}
if (! -d "cache")
{
        unless (mkdir("cache", 0755)) { die "create cache directory failed $!"; }
}
else
{
	system("rm cache/*");
}

sub logmsg { print "$0 $$: @_ at ", scalar localtime, "\n" }

my $port = shift || 2345;
my $proto = getprotobyname('tcp');
socket(Server, PF_INET, SOCK_STREAM, $proto) or die "socket: $!";
setsockopt(Server, SOL_SOCKET, SO_REUSEADDR, pack("l", 1))
                                             or die "setsockopt: $!";
bind(Server, sockaddr_in($port, INADDR_ANY)) or die "bind: $!";
listen(Server,SOMAXCONN)                     or die "listen: $!";

logmsg "server started on port $port";

$SIG{CHLD} = \&REAPER;

my ($master_name, $is_driver, $paddr, $line, $driver_duration, $driver_path);
$is_driver = 0;
$driver_path = "/home/pgsql/dbt1/dbdriver";

for ( ; $paddr = accept(Client,Server); close Client) {
	my($port,$iaddr) = sockaddr_in($paddr);
	$master_name = gethostbyaddr($iaddr,AF_INET);

	logmsg "connection from $master_name [", 
            inet_ntoa($iaddr), "] at port $port";

	# assume the first one I get is time
	while (1)
	{
		$line='';
		recv Client, $line, 1024,  MSG_NOSIGNAL;
		print "line is $line", "\n";
		if ( $line =~ /master time/ )
		{
			chomp($line);
			$line =~ s/master time //;
			my $master_time = $line; 
			print "master time $master_time", "\n";
	#		system("/usr/bin/sudo date --set=\"$master_time\"") && warn  "can not set time";
			send Client, "time set", MSG_DONTWAIT;
		}
		if ( $line =~ /appCache/ )
		{
			my ($cache_path);
			$cache_path="/home/pgsql/dbt1/cache";
			#make this command untainted
			if ( $line =~ /(.*)/ ) {$line = "$cache_path/".$1};
			print "cmd is $line\n";
			system("$line --output_path ./cache 2>&1 > cache.out &");
			#wait until the cache is warmed up
			while (1)
			{
				my $rec;
				print "checking result...\n";
				$rec = parse_out("./cache.out", "fail", "cache is warm");
				print "rec is $rec\n";
				if ( $rec == 0) 
				{
					send Client, "$line failed", MSG_DONTWAIT;
					last;
				}
				elsif ($rec == 1)
				{
					send Client, "$line succeeded", MSG_DONTWAIT;
					last;
				}
				else { sleep(10);}
			}
		}
		if ( $line =~ /appServer/ )
		{
			my ($server_path);
			$server_path="/home/pgsql/dbt1/appServer";
			#make this command untainted
			if ( $line =~ /(.*)/ ) {$line = "$server_path/".$1};
			print "cmd is $line\n";
			system("$line --output_path ./appserver 2>&1 > server.out &");
			#wait until the appserver is up
			while (1)
			{
				my $rec;
				print "checking result...\n";
				$rec = parse_out("./server.out", "fail", "server is active");
				print "rec is $rec\n";
				if ( $rec == 0) 
				{
					send Client, "$line failed", MSG_DONTWAIT;
					last;
				}
				elsif ($rec == 1)
				{
					send Client, "$line succeeded", MSG_DONTWAIT;
					last;
				}
				else { sleep(10);}
			}
		}
		if ( $line =~ /dbdriver/ )
		{
			$is_driver = 1;
			if ( $line =~ /--duration ([0-9]+)/ )
			{
			        $driver_duration = $1;
			}
			else
			{
				# use default
			        $driver_duration = 300;
			}
			print "driver duration is $driver_duration\n";
			#make this command untainted
			if ( $line =~ /(.*)/ ) {$line = "$driver_path/".$1};
			print "cmd is $line\n";
			STDOUT->autoflush;
			STDERR->autoflush;
			system("$line --output_path ./dbdriver 2>&1 > driver.out &");
			send Client, "got driver command", MSG_DONTWAIT;
		}
		if ( $line =~ /last/ )
		{
			send Client, "$line confirmed", MSG_DONTWAIT;
			close(Client);
			last;
		}
		if ( $line =~ /terminate/ )
		{
			last;
		}
	}
	if ( $line =~ /terminate/ )
	{
		close(Server);
		last;
	}
}

# sleep wait for the master sever to start
sleep 15;
my $master_port;
$master_port = 'MASTER';
if ( $is_driver )
{
	#sleep for duration
	sleep("$driver_duration");
	print "connecting to master\n";
	connect_to_host($master_name, 2346, $master_port);
	while (1)
	{
		my $rec;
		print "checking driver done...\n";
		$rec = parse_out("./driver.out", "fail", "Dbdriver ended");
		print "rec is $rec\n";
		if ( $rec == 0) 
		{
			send "$master_port", "dbdriver: failed", MSG_DONTWAIT;
			last;
		}
		elsif ($rec == 1)
		{
			send "$master_port", "dbdriver: ended", MSG_DONTWAIT;
			last;
		}
		else { sleep(10);}
	}
	print "wait for request:\n";
	recv "$master_port", $line, 1024, MSG_NOSIGNAL;
		print "got request: $line";
	if ( $line =~ /send mix log/ )
	{
		my $fmix = new FileHandle;
		unless ($fmix->open( "< dbdriver/mix.log" ) )
			{ die "can't open file mix.log: $!"; }
		while (<$fmix>)
		{
			print "sending mix.log...$_\n";
			send "$master_port", "$_", MSG_DONTWAIT;
		}	
		close($fmix);
		# sleep so that the buffer is sent
		sleep(15);
		send "$master_port", "last", MSG_DONTWAIT;
	}
}

sub connect_to_host
{
        my ($host, $port, $socket_name) = @_;
        my ($iaddr, $proto, $paddr, $line);
        # make cache_port untaint
        if ($port =~ /^([0-9]+)$/)
        {
                $port=$1;
        }
        # make cache_host untaint
        if ( $host =~ /^(.*)$/ )
        {
                $host=$1;
        }
        
        $iaddr   = inet_aton($host) or die "no host: $host";
        $paddr   = sockaddr_in($port, $iaddr);
 
        $proto   = getprotobyname('tcp');
        socket("$socket_name", PF_INET, SOCK_STREAM, $proto) or die "socket: $!";
        connect("$socket_name", $paddr) or die "connect: $!";
}

# parse the output content in $filename
# returns 0 if found $error string
# returns 1 if found $success string
# returns 2 if not found either above
sub parse_out
{
	my($filename, $error, $success) = @_;
	my $fout;
	$fout = new FileHandle;
	unless ($fout->open( "< $filename" ) )
		{ die "can't open file $filename: $!"; }
	while (<$fout>)
	{
		if ( /$error/i )
			{ close($fout); return 0;}
		elsif ( /$success/i )
			{ close($fout); return 1;}
	}
	close($fout);
	return 2;
}

sub REAPER { wait; }
