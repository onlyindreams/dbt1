/*
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2004 Mark Wong & Open Source Development Labs, Inc.
 *
 * 8 April 2004
 */

#include <pthread.h>
#include <iostream>
#include <string>

#include <signal.h>
#include <getopt.h>

#include "WebDriver.h"

using namespace std;

int browsers = 0;
int items = 1000;
int customers = 1;
time_t duration = 0;
int thinktime = 7500; // In milliseconds, 7.5 seconds.
int usmd = 900; // In seconds.
int verbose = 0;
string url;

pthread_t *tid;

void *worker(void *);

int main(int argc, char *argv[])
{
    int c;

    while (1) {
        static struct option long_options[] = {
            { "browsers", required_argument, 0, 'b' },
            { "customers", required_argument, 0, 'c' },
            { "duration", required_argument, 0, 'd' },
            { "items", required_argument, 0, 'i' },
            { "thinktime", required_argument, 0, 't' },
            { "usmd", required_argument, 0, 's' },
            { "url", required_argument, 0, 'u' },
            { "verbose", required_argument, 0, 'v' },
            { 0, 0, 0, 0 }
        };
	int option_index = 0;

        c = getopt_long_only(argc, argv, "", long_options, &option_index);
        if (c == -1) {
            break;
        }
        switch (c) {
        case 0:
            if (long_options[option_index].flag != 0) {
                break;
            }
            cout << "option " << long_options[option_index].name;
            if (optarg) {
                cout << " with arg " << optarg;
            }
            cout << endl;
            break;
        case 'b':
            browsers = atoi(optarg);
            break;
        case 'c':
            customers = atoi(optarg);
            break;
        case 'd':
            duration = atoi(optarg);
            break;
        case 'i':
            items = atoi(optarg);
            break;
        case 's':
            usmd = atoi(optarg);
            break;
        case 't':
            thinktime = atoi(optarg);
            break;
        case 'u':
            url = optarg;
            break;
        case 'v':
            verbose = atoi(optarg);
            break;
        default:
            exit(1);
        }
    }

    // Check to make sure that all of the parameters have been set.
    if (browsers == 0) {
        cout << "--browsers #" << endl;
        exit(1);
    }
    if (duration == 0) {
        cout << "--duration #" << endl;
        exit(1);
    }

    cout << "URL: " << url << endl;
    cout << "Starting " << browsers << " browser(s)." << endl;
    cout << "Test duration is " << duration << " second(s)." << endl;
    cout << "User session minimum duration " << usmd << " second(s)." << endl;
    cout << "Average thinktime will be approximately " << thinktime
         << " millisecond(s)." << endl;

    // Ignore SIGPIPE.  We don't want the program to exit.
    signal(SIGPIPE, SIG_IGN);

    // Start all browsers.
    tid = new pthread_t[browsers];
    for (int i = 0; i < browsers; i++) {
        if (pthread_create(&tid[i], NULL, &worker, NULL) != 0) {
            cerr << "error creating worker thread" << endl;
            exit(2);
        }
        sleep(1);
    }

    // Wair for browsers to finish.
    for (int i = 0; i < browsers; i++) {
        if (pthread_join(tid[i], NULL) != 0) {
            cerr << "error joining worker thread" << endl;
            exit(3);
        }

    }
    cout << "I am done driving." << endl;
    delete tid;
    return 0;
}

void *worker(void *)
{
    // Ignore SIGPIPE.  We don't want the program to exit.
    // It appears I might have to do it per thread.
    signal(SIGPIPE, SIG_IGN);

    WebDriver wd(pthread_self(), items, customers, url, time(NULL) + duration,
        usmd, thinktime);
    if (verbose) {
        cout << "verbose level: " << verbose << endl;
        wd.verbose(verbose);
    }
    wd.start();

    return NULL;
}
