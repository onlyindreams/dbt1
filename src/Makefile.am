# This file is released under the terms of the Artistic License.  Please see
# the file LICENSE, included in this package, for details.
#
# Copyright (C) 2004 Mark Wong & Open Source Development Labs, Inc.
#
# 7 April 2004

AUTOMAKE_OPTIONS = no-dependencies

INCLUDES = -I../include

bin_PROGRAMS = web_test driver

web_test_SOURCES = SocketTable.cc WebClient.cc web_test.cc

driver_SOURCES = SocketTable.cc WebClient.cc WebDriver.cc Interaction.cc \
    driver.cc

EXTRA_DIST = \
../include/Interaction.h \
../include/SocketTable.h \
../include/WebClient.h \
../include/WebDriver.h
