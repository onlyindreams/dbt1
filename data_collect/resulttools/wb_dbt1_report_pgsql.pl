#!/usr/bin/perl -w 
# wb_dbt3_report.pl: generate dbt3 result html
#
# This file is released under the terms of the Artistic License.  Please see
# the file LICENSE, included in this package, for details.
#
# Copyright (C) 2003 Open Source Development Lab, Inc.
#
# Author: Jenny Zhang
# March 2003

use strict;
use English;
use File::Spec::Functions;
use File::Basename;
use File::Copy;
use FileHandle;
use Getopt::Long;
use CGI qw(:standard *table start_ul :html3);
use Pod::Usage;
#use Env qw(DBT1_PERL_MODULE);
#use lib "$DBT1_PERL_MODULE";
#use Data_report;

use constant DEBUG => 0;

=head1 NAME

wb_dbt1_report_pgsql.pl

=head1 SYNOPSIS

generates dbt1 result page

=head1 ARGUMENTS

 -indir <result data directory>
 -outfile <filename - defaults to STDOUT >
 -file <config filename to read from> 
 -write <config filename to write to> 

=cut

my ( $indir, $hlp, $outfile, $configfile, $writeme, $relative_indir );

GetOptions(
	"indir=s" => \$indir,
	"outfile=s" => \$outfile,
	"help"      => \$hlp,
	"file=s"    => \$configfile,
	"write=s"   => \$writeme
);


my $fcf = new FileHandle;
my ( $cline, %options );
my ( $iline, $fh );

if ($hlp) { pod2usage(1); }

if ( $configfile ) {
	unless ( $fcf->open( "< $configfile" ) ) {
		die "Missing config file $!";
	}
	while ( $cline = $fcf->getline ) {
		next if ( $cline =~ /^#/ );
		chomp $cline;
	my ( $var, $value ) = split /=/, $cline;
		$options{ $var } = $value;
	}
	$fcf->close;
}

if ( $indir ) { $options{ 'indir' } = $indir; }
elsif ( $options{ 'indir' } ) {
	$indir =  $options{ 'indir' };
}
else
{
	die "No input dir $!";
}

if ( $outfile ) {
	$options{ 'outfile' } = $outfile;
	$fh = new FileHandle;
	unless ( $fh->open( "> $outfile" ) ) { die "can't open output file $!"; }
} 
elsif ( $options{ 'outfile' } ) {
	$outfile=$options{ 'outfile' };
	$fh = new FileHandle;
	unless ($fh->open("> $outfile")) { die "can't open output file $!"; }
}
else
{
	$fh = *STDOUT;
}

if ( $writeme ) {
	my $ncf = new FileHandle;
	unless ( $ncf->open( "> $writeme" ) ) { die "can't open file $!"; }
	my $name;
	foreach $name ( keys( %options ) ) {
	    print $ncf $name, "=", $options{ $name }, "\n";
	}
	$ncf->close;
}

#read configuration from config.txt file
my $fconfig = new FileHandle;

print "indir is $indir\n";
unless ( $fconfig->open( "< $indir/config.txt" ) )   { die "No config file $!"; }
my (%configs);

while (<$fconfig>)
{
	chop $_;
	my ( $var, $value ) = split /:/, $_;
	$configs{ $var } = $value;
}
$fconfig->close;

# get relative input dir if it is a absolute path
if ($indir =~ /^\// && $indir =~ /\/(\w*)$/)
#if ($indir =~ /^\/([a-z0-9\._-]*)$/)
{
        $relative_indir = "./".$1;
	print "relative_indir is $relative_indir\n";
}
else
{
	$relative_indir = $indir;
}

print $fh h1("DBT-1-PGSQL on Node $configs{'node'} Test Result"), "\n";
print $fh h2("Configurations: "), "\n";
#generate configuration table
print $fh table({-border=>undef},
	Tr({-valign=>"TOP"},
	[
		th(["Software Version", "Hardware Configuration", "Run Parameters"]),
		td(["Linux Kernel: $configs{'kernel'}", "$configs{'CPUS'} CPUS @ $configs{'MHz'} MHz", "Database Size (items): $configs{'dbitems'}"]),
		td(["Distribution: $configs{'distribution'}", "CPU model $configs{'model'}", "Database Size (customers): $configs{'dbcustomers'}"]),
		td(["PostgreSQL:  $configs{'pgsql'}", "$configs{'memory'} Memory", "number of cache: $configs{'numcache'}"]),
		td(["sysstat: $configs{'sysstat'}", "&nbsp", "number of connections between cache and database: $configs{'cachedbconnection'}"]),
		td(["procps: $configs{'procps'}", "&nbsp", "number of application server: $configs{'numserver'}"]),
		td(["&nbsp", "&nbsp", "number of connections between server and database: $configs{'serverdbconnection'}"]),
		td(["&nbsp", "&nbsp", "number of drivers: $configs{'numdriver'}"]),
		td(["&nbsp", "&nbsp", "eus/driver: $configs{'eus'}"]),
		td(["&nbsp", "&nbsp", "rampuprate/driver: $configs{'rampuprate'}"]),
		td(["&nbsp", "&nbsp", "duration/driver: $configs{'duration'}"]),
		td(["&nbsp", "&nbsp", "thinktime/driver: $configs{'thinktime'}"]),
		td(["&nbsp", "&nbsp", "Put WAL on different driver: $configs{'redirect_xlog'}"]),
		td(["&nbsp", "&nbsp", "Put pgsql_tmp on different driver: $configs{'redirect_tmp'}"]),
		td(["&nbsp", "&nbsp", "database parameters: $configs{'db_param'}"]),
		td(["&nbsp", "&nbsp", "shmmax: $configs{'shmmax'}"]),
	])), "\n";

print $fh br;
print $fh h2("Transaction Distribution and Response Time: "), "\n";

my $fbt = new FileHandle; 
unless ( $fbt->open( "< $indir/BT" ) ) {
	die "Missing run result file BT $!";
}
print $fh start_table({-border=>undef});
print $fh Tr(th(["Interaction", "Percentage", "Average Response time (s)"])), "\n";
while ( <$fbt> ) {
	next if ( /^Interaction/ );
	last if ( /^$/ );
	chomp;
	# don't know why I have to add t1 and t2, but I will use it for now
	my ($interaction, $t1, $percentage, $t2, $responsetime) = split /( ){2,}/;
	print $fh Tr(td[($interaction, $percentage, $responsetime)]), "\n";
} 

while ( <$fbt> ) {
	chomp;
	print $fh $_, "\n";
	print $fh br;
}
$fbt->close;
print $fh end_table;

#generate $indir/plot directory
if (! -d "$indir/plot")
{
	unless (mkdir("$indir/plot", 0755)) { die "create plot directory failed $!"; }
}

#generate gnuplot files
system("./dbt1_gen_graphs.sh", "$indir", "$indir/plot");

system("cp", "$indir/build.iostat.txt", "$indir/plot/build.iostat.txt");
system("cp", "$indir/build.ziostat.txt", "$indir/plot/build.ziostat.txt");
system("cp", "$indir/build.vmstat.out", "$indir/plot/build.vmstat.txt");
system("cp", "$indir/run.iostat.txt", "$indir/plot/run.iostat.txt");
system("cp", "$indir/run.ziostat.txt", "$indir/plot/run.ziostat.txt");
system("cp", "$indir/run.vmstat.out", "$indir/plot/run.vmstat.txt");
system("cp", "$indir/ips.csv", "$indir/plot/ips.csv.txt");
#system("cp", "$indir/dbt1_run.prof", "$indir/plot/dbt1_run_prof.txt");
#change_file_name("$indir/plot", "xcons*.dat", ".dat", ".txt");
print $fh h2("Raw data");
table_of_glob("$indir/plot", "$relative_indir/plot", "*.txt", 1);
#
print $fh h2("gnuplot charts");
print $fh "<form method=\"post\" 
	action=\"http://webdev/jenny/cgi-bin/showchart.cgi \"
        enctype=\"application/x-www-form-urlencoded\">";
print $fh "<INPUT TYPE=\"hidden\" NAME=\"pathname\" VALUE=\"$relative_indir/plot\">";
table_of_glob("$indir/plot", "$relative_indir/plot", "*.png", 1);
print $fh "<INPUT TYPE=\"submit\" NAME=\"showchart\" VALUE=\"Show Charts\">";
print $fh "</form>";

print $fh h2("Run log data");
my @runlog;

my @driver_out = glob("$indir/dbdriver.out.*");
my @cache_out = glob("$indir/cache.out.*");
my @server_out = glob("$indir/server.out.*");
my ($name, $fname);
@runlog=("BT","ips.csv","result.mix.log","dbdriver/","appserver/","cache/", "dbt1_master.out", "dbt1_slave.out");
print $fh start_ul;
foreach $name (@runlog)
{
	print $fh li(a( {-href=>"$relative_indir/$name"}, $name)), "\n";
}
foreach $name (@driver_out)
{
	if ( $name =~ /\/([a-zA-z0-9\.\-_]*)$/ )
	{
		$fname = $1;
	}
	else
	{
		$fname = $name;
	}
	print $fh li(a( {-href=>"$relative_indir/$fname"}, $fname)), "\n";
}
foreach $name (@cache_out)
{
	if ( $name =~ /\/([a-zA-z0-9\.\-_]*)$/ )
	{
		$fname = $1;
	}
	else
	{
		$fname = $name;
	}
	print $fh li(a( {-href=>"$relative_indir/$fname"}, $fname)), "\n";
}
foreach $name (@server_out)
{
	if ( $name =~ /\/([a-zA-z0-9\.\-_]*)$/ )
	{
		$fname = $1;
	}
	else
	{
		$fname = $name;
	}
	print $fh li(a( {-href=>"$relative_indir/$fname"}, $fname)), "\n";
}

print $fh end_ul;

print $fh h2("Database Monitor Data");
print $fh start_ul;
if (!-e "$indir/db_stat.tar.gz")
{
	system("tar cvfz $indir/db_stat.tar.gz -C $indir db_stat");
	system("rm -rf $indir/db_stat");
}
print $fh li(a( { -href=>"$relative_indir/param.out"}, "database parameters")), "\n";
print $fh li(a( { -href=>"$relative_indir/indexes.out"}, "database indexes and primary key")), "\n";
print $fh li(a( { -href=>"$relative_indir/db_stat.tar.gz"}, "database monitor files")), "\n";
print $fh li(a( { -href=>"$relative_indir/db_logfile.txt"}, "database log files")), "\n";
print $fh end_ul;

print $fh h2("Other data");
print $fh start_ul;
print $fh li(a( { -href=>"$relative_indir/build.meminfo0.out"}, "meminfo before building the database")), "\n";
print $fh li(a( { -href=>"$relative_indir/build.meminfo1.out"}, "meminfo after building the database")), "\n";
print $fh li(a( { -href=>"$relative_indir/run.meminfo0.out"}, "meminfo before run")), "\n";
print $fh li(a( { -href=>"$relative_indir/run.meminfo1.out"}, "meminfo after run")), "\n";
if (!-e "$indir/ipcs.tar.gz")
{
	system("tar cvfz $indir/ipcs.tar.gz -C $indir ipcs");
	system("rm -rf $indir/ipcs");
}
print $fh li(a( { -href=>"$relative_indir/ipcs.tar.gz"}, "ipcs data")), "\n";
print $fh end_ul;

#write table of files 
sub table_of_glob {
	my ($indir, $relative_indir, $globname, $flag) = @_;

	#generate a list of *.png files
	my @filelist = glob("$indir/$globname");
	print "filelist $#filelist", join ( '  ', @filelist ) if DEBUG;

	print $fh start_table( { -border => undef });
	if ( $flag == 0 )
	{
#		print $fh Tr(th[("sar", "vmstat", "iostat", "xcons", "read_profile")]);
		print $fh Tr(th[("sar", "vmstat", "iostat", "ziostat", "interactions/s","read_profile")]);
	}
	else
	{
#		print $fh Tr(th[("sar", "vmstat", "iostat", "xcons")]);
		print $fh Tr(th[("sar", "vmstat", "iostat", "ziostat", "interactions/s")]);
	}

#	my (@sarlist, @iostatlist, @vmstatlist, @xconslist, @profilelist, $sar_index, $iostat_index, $vmstat_index, $xcons_index, $profile_index);
	my (@sarlist, @iostatlist, @vmstatlist, @profilelist, @ipslist, @ziostatlist, $sar_index, $iostat_index, $vmstat_index, $profile_index, $ips_index, $ziostat_index);
	$sar_index=0;
	$iostat_index=0;
	$ziostat_index=0;
	$vmstat_index=0;
#	$xcons_index=0;
	$profile_index=0;
	$ips_index=0;
	for ( my $i = 0; $i <= $#filelist; $i++ ) {
		$_=$filelist[$i];
		if (/sar/)
		{
			$sarlist[$sar_index]=$_;
			$sar_index++;
		}
		elsif (/vmstat/)
		{
			$vmstatlist[$vmstat_index]=$_;
			$vmstat_index++;
		}
		elsif (/iostat/ && !/ziostat/)
		{
			$iostatlist[$iostat_index]=$_;
			$iostat_index++;
		}
		elsif (/ziostat/)
		{
			$ziostatlist[$ziostat_index]=$_;
			$ziostat_index++;
		}
		elsif (/ips/)
		{
			$ipslist[$ips_index]=$_;
			$ips_index++;
		}
		elsif (/prof/)
		{
			$profilelist[$profile_index]=$_;
			$profile_index++;
		}
	}
		
	my $max_row=$#sarlist;
	if ($max_row < $#vmstatlist) { $max_row=$#vmstatlist; }
	if ($max_row < $#iostatlist) { $max_row=$#iostatlist; }
	if ($max_row < $#ziostatlist) { $max_row=$#ziostatlist; }
	if ($max_row < $#ipslist) { $max_row=$#ipslist; }
	if ( $flag == 0 && $max_row < $#profilelist ) {
		$max_row=$#profilelist;
	}
	
	my ($sarname, $vmstatname, $iostatname, $profilename, $ipsname, $ziostatname);
	for ( my $i = 0; $i <= $max_row; $i++ ) 
	{
		if ($i>$#sarlist) {$sarlist[ $i ]="&nbsp";}
		if ($i>$#vmstatlist) {$vmstatlist[ $i ]="&nbsp";}
		if ($i>$#iostatlist) {$iostatlist[ $i ]="&nbsp";}
		if ($i>$#ziostatlist) {$ziostatlist[ $i ]="&nbsp";}
		#if ($i>$#sarlist) {$sarlist[ $i ]="";}
		#if ($i>$#vmstatlist) {$vmstatlist[ $i ]="";}
		#if ($i>$#iostatlist) {$iostatlist[ $i ]="";}
		if ($i>$#ipslist) {$ipslist[ $i ]="";}
		if ( $flag == 0 && $i>$#profilelist ) {
			$profilelist[ $i ]="&nbsp";
		#	$profilelist[ $i ]="";
		}

		$sarname=basename($sarlist[ $i ]);
		$vmstatname=basename($vmstatlist[$i]);
		$iostatname=basename($iostatlist[$i]);
		$ziostatname=basename($ziostatlist[$i]);
		$ipsname=basename($ipslist[$i]);
		if ( $flag == 0 )
		{
			$profilename=basename($profilelist[$i]);
		}
		if ($flag == 1)
		{
		print $fh Tr(
			td("<INPUT TYPE=\"checkbox\" NAME=\"png\" VALUE=\"$sarname\"> <a href=\"$relative_indir/$sarname\"> $sarname</a>"),
			td("<INPUT TYPE=\"checkbox\" NAME=\"png\" VALUE=\"$vmstatname\"> <a href=\"$relative_indir/$vmstatname\"> $vmstatname</a>"),
			td("<INPUT TYPE=\"checkbox\" NAME=\"png\" VALUE=\"$iostatname\"> <a href=\"$relative_indir/$iostatname\"> $iostatname</a>"),
			td("<INPUT TYPE=\"checkbox\" NAME=\"png\" VALUE=\"$ziostatname\"> <a href=\"$relative_indir/$ziostatname\"> $ziostatname</a>"),
			td("<INPUT TYPE=\"checkbox\" NAME=\"png\" VALUE=\"$ipsname\"> <a href=\"$relative_indir/$ipsname\"> $ipsname</a>"),
			), "\n";
		}
		else
		{
		print $fh Tr(
                        td( a( { -href => "$relative_indir/$sarname" }, "$sarname" ) ),
                        td( a( { -href => "$relative_indir/$vmstatname" }, "$vmstatname") ),
       			td( a( { -href => "$relative_indir/$iostatname" }, "$iostatname") ),
       			td( a( { -href => "$relative_indir/$ziostatname" }, "$ziostatname") ),
      			td( a( { -href => "$relative_indir/$ipsname" }, "$ipsname") ),
       			td( a( { -href => "$relative_indir/$profilename" }, "$profilename") ),
			), "\n";
		}
	}
	print $fh end_table, "\n";
}
#
#sub change_file_name {
#	my ($indir, $globname, $from, $to) = @_;
#	#generate a list of *.png files
#	my @filelist = glob("$indir/$globname");
#	print "filelist $#filelist", join ( '  ', @filelist ) if DEBUG;
#
#	for (my $i=0; $i<=$#filelist; $i++)
#	{
#		my $new_name=$filelist[$i];
#		$new_name=~s/$from$/$to/;
#		system("mv", "$filelist[$i]", "$new_name");
#	}
#}
#
