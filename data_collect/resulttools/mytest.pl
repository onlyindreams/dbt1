#!/usr/bin/perl -w 

# CVS Strings 
# $Id$ $Author$ $Date

use strict;
use English;
use Getopt::Long;
use File::Spec::Functions;
use FileHandle;
use CGI qw(:standard :html3);
use Pod::Usage;
use constant DEBUG => 0;

my $var = "dev8-160";

if ($var =~ /^dev8-16$/ )
{
	print "match\n";
}
else
{
	print "not match\n";
}

my $ftp = new FileHandle;
unless ( $ftp->open( ">> tt" ) ) {
                die "Missing tt $!";
        }

print $ftp "newline";
close($ftp);
