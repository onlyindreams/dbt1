/*
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2004 Mark Wong & Open Source Development Labs, Inc.
 *
 * 7 April 2004
 */

#include <getopt.h>

#include "WebClient.h"

int main(int argc, char *argv[])
{
    int c;
    int iter = 1;
    int verbose = 0;
    string url;

    while (1) {
        static struct option long_options[] = {
            { "iter", required_argument, 0, 'i' },
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
        case 'i':
            iter = atoi(optarg);
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

    WebClient wc(1);
    if (verbose) {
        wc.verbose(verbose);
    }
    cout << "iterations: " << iter << endl;
    cout << "url: " << url << endl;
    for (int i = 0; i < iter; i++) {
        wc.httpGet(url);
        cout << wc.getHttpBody() << endl;
    }
    return 0;
}
