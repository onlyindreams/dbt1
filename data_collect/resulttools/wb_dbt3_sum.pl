#!/usr/bin/perl -w
#
# wb_dbt3_sum.pl
#
# This file is released under the terms of the Artistic License.  Please see
# the file LICENSE, included in this package, for details.
#
# Copyright (C) 2003 Open Source Development Lab, Inc.
#
# Author: Jenny Zhang

use strict;
use English;
use Getopt::Long;
use Pod::Usage;
use FileHandle;
use CGI qw(:standard *table start_ul :html3);
use Env qw(DBT3_INSTALL_PATH DBT3_PERL_MODULE);
use lib "$DBT3_PERL_MODULE";
use Cal_average_std;

=head1 NAME

# wb_dbt3_sum.pl

=head1 SYNOPSIS

generate dbt3 run summary list

=head1 ARGUMENTS

 -configfile <config filename to read from> 

=cut

my ($configfile, $hlp);

my ($fcf, $cline, @tables, $table_title, $fout, $outfile);

GetOptions(
	"configfile=s"    => \$configfile,
	"help" 		=> \$hlp
);

if ( !$configfile )
{
	die "config file is required";
}

$fcf = new FileHandle;

if ($hlp) { pod2usage(1); }

unless ( $fcf->open( "< $configfile" ) ) {
	die "Missing config file $!";
}
# get output file name and tabels to generate
while ( $cline = $fcf->getline ) {
	next if ( $cline =~ /^#/ || $cline =~ /^$/ );
	chomp $cline;
	my ( $var, $value ) = split /=/, $cline;
	if ( $var =~ /outfile/ )
	{
		$outfile = $value;
	}
	elsif ( $var =~ /outtables/ )
	{
		@tables = split /;/, $value;
	}
}
$fcf->close;

$fout = new FileHandle;
unless ( $fout->open( "> $outfile" ) ) { die "can't open file $!"; }
print $fout h1("DBT-3 run summary"), "\n";;

for (my $s=0; $s<=$#tables; $s++)
{
	my ( $inputdir, @dirname, @varname, $filename, $average, $std); 

	my $table_name = $tables[$s];
	# read from config file
	unless ( $fcf->open( "< $configfile" ) ) {
		die "Missing config file $!";
	}

	# read to this tables config
	while ( $cline = $fcf->getline ) {
		chop $cline;
		last if ( $cline  eq "[$table_name]" );
	}
	
	# read to next config
	while ( $cline = $fcf->getline ) 
	{
		next if ( $cline =~ /^#/ || $cline =~ /^$/);
		last if ( $cline =~ /\[table/ );
		chomp $cline;
		my ( $var, $value ) = split /=/, $cline;
		if ( $var =~ /$table_name/ )
		{
			$table_title = $value;
		}
		if ( $var =~ /filename/ )
		{
			$filename = $value;
		}
		elsif ( $var =~ /dirname/ )
		{
			@dirname = split /;/, $value;
		}
		elsif ( $var =~ /varname/ )
		{
			@varname = split /;/, $value;
		}
		elsif ( $var =~ /inputdir/ )
		{
			$inputdir = $value;
		}
	}
	
	print $fout h2("$table_title"), "\n";;
	print $fout start_table( { -border => undef }), "\n";
	#print the header of the table
	print $fout "<tr><th>Base Kernel</th><th>Patches</th><th>Scale Factor</th><th>Number of Streams</th>";
	for (my $i=0; $i<=$#varname; $i++)
	{
		my $tmp_title;
		# replace the load title
		if ( $varname[$i] eq 'load') 
		{ 
			$tmp_title = "database load (seconds)";
		}
		else
		{
			$tmp_title = $varname[$i];;
		}
		print $fout "<th><a href=\"./dbt3_explain.html#$varname[$i]\"> $tmp_title</a> average</th><th> $tmp_title Standard Deviation</th>";
	}
	
	print $fout "<th>Result Page</th></tr>\n";
	
	for (my $j=0; $j<=$#dirname; $j++)
	{
		my ($basekernel, @patches, $num_of_streams, $scale_factor);
		($scale_factor, $num_of_streams, $basekernel, @patches) = 
			parse_dir_name($dirname[$j]);
		print $fout "<tr><td>$basekernel</td>";
		print $fout "<td><ul>";
		for (my $i=0; $i<=$#patches; $i++)
		{
			if ( $patches[$i] =~ /plm/ )
			{
				$patches[$i] =~ s/plm//;
				print $fout "<li>
					<a href=\"http://www.osdl.org/cgi-bin/plm?module=patch_info&patch_id=$patches[$i]\"> PLM $patches[$i]</a>"
			}
			else
			{
				print $fout "<li>$patches[$i]"
			}
		}
		print $fout "</ul></td>";
		
		print $fout "<td>$scale_factor</td><td>$num_of_streams</td>";
		for (my $i=0; $i<=$#varname; $i++)
		{
			($average, $std) = cal_average_std( $inputdir, $dirname[$j], $filename, $varname[$i] );
			printf $fout "<td>%.2f</td><td>%.2f</td>", $average, $std;
		}
		#assume the pages are under the same dir
		my @pagelist = glob("$dirname[$j].html");
		print $fout "<td><ul>";
		for (my $k=0; $k<=$#pagelist; $k++)
		{
			print $fout "<li><a href=\"$pagelist[$k]\"> $pagelist[$k]</a>"
		}
		print $fout "</ul></td></tr>\n";
	}
	print $fout end_table( { -border => undef }), "\n";
	close($fcf);
}
close($fout);
	
sub parse_dir_name
{
	my ($dirname) = @_;
	print "parameter is @_\n";
	print "dirname $dirname\n";
	my (@value, @retvalue);
	# dirname should be in the format of 
	# dbt3_scale_streams_kernel_patch1[_patch2...]_run
	@value = split '_', $dirname;
	print "value is ", join(' ', @value), "\n";
	# the first one is dbt3
	# the second one is scale_factor
	$retvalue[0] = $value[1];
	# the third one is number of streams
	$retvalue[1] = $value[2];
	# the forth one is base kernel
	$retvalue[2] = $value[3];
	# the rest is the patches
	for (my $i=4, my $j=3; $i<=$#value; $i++, $j++)
	{
		if ( $i < $#value )
		{
			$retvalue[$j] = $value[$i];
		}
		else
		{
			#get rid of the '*'
			$value[$i] =~ s/\*//;
			$retvalue[$j] = $value[$i];
		}
	}
	print "revalue is ", join(' ', @retvalue), "\n";
	return @retvalue;
}

