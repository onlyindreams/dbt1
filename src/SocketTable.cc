/*
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2004 Mark Wong & Open Source Development Labs, Inc.
 *
 * 7 May 2004
 */

///
// SocketTable.cc
//
// 12 November 2000
// Mark Wong (markw@osdl.org)
////

#include <values.h>
#include <SocketTable.h>

////
// Title:       closeSocket
//
// Description:
//
//              Close a socket.
//
// Inputs:      string serverAddress  -    The server domain name or ip address
//                                       and port int the form: host:port
//
// Outputs:
//
// Examples:    closeSocket(host);
//
// Date:        20 December 2000
//
// Author:      Mark Wong (markw@osdl.org)
////
int SocketTable::closeSocket(string serverAddress) {
    close(socketTable[serverAddress]);
    socketTable[serverAddress] = -1;
    return 1;
}


////
// Title:       getSocket
//
// Description:
//
//              Look up the host address in the socket table and return
//              a descriptor for the socket.
//
// Inputs:      string serverAddress  -    The server domain name or ip address
//                                       and port int the form: host:port
//
// Outputs:
//
// Examples:    getSocket(host);
//
// Date:        5 October 2000
//
// Author:      Mark Wong (markw@osdl.org)
////
int *SocketTable::getSocket(string serverAddress) {

    // Look up the serverAddress to see if a socket is already connected.
    int *sock = &socketTable[serverAddress];

    if (*sock > 0) {
        return sock;
    }

    // Connect to serverAddress and store the socket descriptor.
    *sock = socketTable[serverAddress] = connectSocket(serverAddress);

    return sock;
}

////
// Title:       connectSocket
//
// Description:
//
//              Open an HTTP connection.
//
// Inputs:      string serverAddress  -    The server domain name or ip address
//                                        and port int the form: host:port
//
// Outputs:
//
// Examples:    connectSocket(serverAddress);
//
// Date:        5 October 2000
//
// Author:      Mark Wong (markw@osdl.org)
////
int SocketTable::connectSocket(string serverAddress) {
    int sock;

    int bufferSize;
    int soKeepalive = 1;

    string host;
    unsigned short port;
    string::size_type pos;

    struct hostent *he;
    struct sockaddr_in sa;

    // Extract the domain name or ip address portion of the host information.
    // Set the port to 80, if no port number has been specified.
    pos = serverAddress.find(":");
    if (pos == string::npos) {
        host = serverAddress;
        port = 80;
    } else {
        host = serverAddress.substr(0, pos);
        port = atoi(serverAddress.substr(pos + 1,
                serverAddress.length() - pos).c_str());
    }

    //cout << "Connecting to " << host << " : " << port << endl;

    // Assume host is in the form ms.thesis.com.
    he = gethostbyname(host.c_str());
    if (he == NULL) {
        struct in_addr address;

        // Not able to get a hostent, maybe the host is in the form w.x.y.z.
        if (inet_aton(host.c_str(), &address)) {
            he = gethostbyaddr(reinterpret_cast<char *>(&address),
                    sizeof(address), AF_INET);

            if (he == NULL) {
                // The host host may be incorrect.  Return an error.
                cerr << "cannot get hostent" << endl;
                return -1;
            }
        }
    }

    // Host found so connect to it.
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);

    memcpy(&sa.sin_addr, he->h_addr_list[0], sizeof(sa.sin_addr));

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock != -1) {
        if (connect(sock, (struct sockaddr *)(&sa), sizeof(sa)) == -1) {
            cerr << "connect() error" << endl;
            return -1;
        }
    } else {
        cerr << "socket() error" << endl;
    }

    // Set the send buffer size.
    bufferSize = 1460;
    if (setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &bufferSize, sizeof(int))
		!= 0) {
        cerr << "setsockopt(SO_SNDBUF) error" << endl;
        return -1;
    }

    // Set the receive buffer size.

    bufferSize = 1460;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &bufferSize, sizeof(int))
		!= 0) {
        cerr << "setsockopt(SO_RCVBUF) error" << endl;
        return -1;
    }

    // Set the SO_KEEPALIVE flag.
    if (setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &soKeepalive,
            sizeof(soKeepalive)) != 0) {
        cerr << "setsockopt(SO_KEEPALIVE) error" << endl;
        return -1;
    }

    return sock;
}
