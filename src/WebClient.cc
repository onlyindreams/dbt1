/*
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2004 Mark Wong & Open Source Development Labs, Inc.
 *
 * 7 May 2004
 */

////
// WebClient.cc
//
// 5 October 2000
// Mark Wong (markw@osdl.org)
////

#include <iostream>
#include <string>
#include <sstream>

#include "WebClient.h"

using namespace std;

////
// Title: WebClient
//
// Description:
//
//     Constructor for the emulated browser.  Determines the hostname.
//
// Inputs:
//
// Outputs:
//
// Examples: new WebClient;
//
// Date: 7 October 2000
//
// Author: Mark Wong (markw@osdl.org)
////
WebClient::WebClient(int id) {
    // Initialize veriables.
    verboseFlag = 0;
    imageFlag = 0;

    currentServerAddress = "";
    gethostname(hostname, HOSTNAME_LEN);

    currentSocket = NULL;

    // Set the logfile name and open it.
    stringstream s;
    s << id;
    string filename = "WebClient" + s.str() + ".log";
    logfile.open(filename.c_str());
    logfile.setf(ios_base::fixed, ios_base::floatfield);
}

string WebClient::getHttpBody()
{
    return httpBody;
}

string WebClient::getHttpHeader()
{
    return httpHeader;
}

////
// Title: getImgLinks
//
// Description:
//
//     Determine all the <img> tags in an html string.
//
// Inputs: string httpBody - The HTML page to parse.
//
// Outputs: vector<string> - Array of all the image links URL's.
//
// Examples: getImgLinks(httpBody)
//
// Date: 7 October 2000
//
// Author: Mark Wong (markw@osdl.org)
////
vector<string> *WebClient::getImgLinks(string httpBody) {
    vector<string> *imgLinks = new vector<string>;
    string::size_type start, pos1, pos2 = 0;

    // Strip out the src field for eact <img> tag.
    while ((start = httpBody.find("<img", pos2)) != string::npos) {
        // Find the src field.  It should be in the format: src=img.jpg or
        // src="img.jpg".
        pos1 = httpBody.find("src=\"", start);
        if (pos1 != string::npos) {
            pos1 += 5;
            pos2 = httpBody.find("\"", pos1 + 1);
        } else {
            pos1 = httpBody.find("src=");
            if (pos1 != string::npos) {
                pos1 += 4;
            pos2 = httpBody.find(SP, pos1);
            } else {
                return NULL;
            }
        }

        // Save each link into a the vector<string> to return.
        imgLinks->push_back(httpBody.substr(pos1, pos2 - pos1));
        if (verboseFlag > 3) {
            logfile << "*** [" << imgLinks->size() << "] "
                    << httpBody.substr(pos1, pos2 - pos1) << endl;
        }
    }

    return imgLinks;
}

////
// Title: getLinks
//
// Description:
//
//     Identify all the <a href> tags from a HTTP response.
//
// Inputs: 
//
// Outputs: 
//
// Examples: getLinks
//
// Date: 8 October 2000
//
// Author: Mark Wong (markw@osdl.org)
////
void WebClient::getLinks()
{
    string::size_type start, pos1, pos2 = 0;

    links.clear();
    while ((start = httpBody.find("<a", pos2)) != string::npos) {
        pos1 = httpBody.find("href=\"", start);
        if (pos1 != string::npos) {
            pos1 += 6;
            pos2 = httpBody.find("\"", pos1 + 1);
        } else {
            pos1 = httpBody.find("href=");
            if (pos1 != string::npos) {
                pos1 += 5;
            pos2 = httpBody.find(SP, pos1);
            } else {
                return;
            }
        }

        if (pos2 == string::npos) {
            logfile << "*** couldn't find end of a href" << endl;
            logfile << httpHeader << endl;
            logfile << httpBody << endl;
            return;
        }

        // Save each link into a the vector<string> to return.
        links.push_back(httpBody.substr(pos1, pos2 - pos1));
        if (verboseFlag > 3) {
            logfile << "*** [" << links.size() << "] "
                    << httpBody.substr(pos1, pos2 - pos1) << endl;
        }
    }
}

////
// Title: httpGet
//
// Description:
//
//     Make an HTTP GET request.
//
// Inputs: string url - The object to retrieve of the Web server.
//
// Outputs: int - Status-Code of the HTTP request.
//
// Examples: get(url);
//
// Date: 6 October 2000
//
// Author: Mark Wong (markw@osdl.org)
////
int WebClient::httpGet(string url) {
    int status;

    int httpLength;
    string httpReq;

    string::size_type pos1, pos2;
    string serverAddress = "";

    int *sock = NULL;
    int rc;

    int messageLength;
    char *msg;

    string uri;

    httpHeader.erase(0, httpHeader.length());
    httpBody.erase(0, httpBody.length());

    // Extracted the HTTP server address out of the url.  
    // For an absolute link, it is in the form:
    //
    //        http://serverAddressess/uri
    //
    // Otherwise is may be in the form:
    //
    //        uri
    pos1 = url.find(URL_PREFIX);
    if (pos1 != string::npos) {
        // Handle an absolute URL.
        if (verboseFlag > 4) {
            logfile << " [absolute link]" << endl;
        }
        pos1 += 7;
        pos2 = url.find("/", pos1);
        serverAddress = url.substr(pos1, pos2 - pos1);
        if (currentServerAddress.size() == 0) {
            currentServerAddress = serverAddress;
        }

        uri = url.substr(pos2);

        // Get a handle for a socket connected to serverAddress.
        sock = socketTable.getSocket(serverAddress);
        if (sock == NULL) {
            logfile << "*** Socket lookup error: " << serverAddress << endl;
            return -1;
        }
        if (verboseFlag > 4) {
            logfile << "*** socket descriptor: " << sock << endl;
        }

        // If no current socket is set, set it to this socket.
        if (currentSocket == NULL) {
            currentSocket = sock;
        }
    } else {
        // Handle a relative URL.
        uri = url;
        if (verboseFlag > 4) {
            logfile << " [relative link]" << endl;
        }
        if (currentSocket == NULL) {
            sock = socketTable.getSocket(currentServerAddress);
            if (sock != NULL) {
                currentSocket = sock;
            } else {
                logfile << "*** No current socket: " << url << endl;
                return -1;
            }
        }

        if (sock == NULL) {
            logfile << "*** Socket lookup error: " << serverAddress << endl;
            return -1;
        }
        sock = currentSocket;
        if (verboseFlag > 4) {
            logfile << "*** socket descriptor: " << sock << endl;
        }
    }

    // Generate the HTTP request with the 'Connection: Keep-Alive' directive as
    // recommended by RFC 2616.
    httpReq = "GET " + uri + " HTTP/1.1" + CRLF +
        "User-Agent: OSDL/3.0 DBT-1 Web Client" + string(CRLF) +
        "Accept: */*" + CRLF +
        "Accept-Language: en-us" + CRLF +
        "Accept-Encoding: gzip, deflate" + CRLF;

    if (currentServerAddress != "") {
        httpReq += "Host: " + string(currentServerAddress) + CRLF;
    }
    httpReq += "Connection: Keep-Alive" + string(CRLFCRLF);

    if (verboseFlag > 3) {
        logfile << "*** HTTP GET Request:\n" << httpReq << endl;
    }

    // Send the request.
    if ((rc = send(*sock, httpReq.c_str(), httpReq.length(), MSG_NOSIGNAL))
            == -1) {
        logfile << "*** send() error: " << errno << endl;
        socketTable.closeSocket(serverAddress);
        return -1;
    }
    if (verboseFlag > 3) {
        logfile << "*** bytes sent: " << rc << endl;
    }

    // Retrieve the response.  We know the first part of the response will be
    // the HTTP header in ascii text.  Begin by identifying the HTTP header.
    httpLength = 0;
    msg = new char[MSS + 1];
    while ((messageLength = recv(*sock, msg, MSS, 0)) != 0) {
        if (verboseFlag > 4) {
            logfile << "*** bytes received: " << messageLength << endl;
        }
        if (messageLength == -1) {
            logfile << "*** recv() error: " << errno << " [" << messageLength
                    << "] [" << httpLength << "]" << endl;

            return -1;
        }
        httpLength += messageLength;
        msg[messageLength] = '\0';
        httpHeader += msg;

        // The header is terminated by CRLF CRLF.
        if ((pos1 = httpHeader.find(CRLFCRLF)) != string::npos) {

            // Truncate everthing from the CRLF CRLF.
            httpHeader = httpHeader.substr(0, pos1);
            if (verboseFlag > 4) {
                logfile << "*** Response HTTP header:\n" << httpHeader << endl;
                logfile << "*** header length: " << httpHeader.length() + 4
                         << endl;
            }
            break;
        }
    }
    // I think if httpHeader turns out to be zero, the socket closed
    // gracefully for some reason.
    if (httpHeader.length() == 0) {
        socketTable.closeSocket(serverAddress);
        return -1;
    }
    if (verboseFlag > 1) {
        logfile << "*** http header length: " << httpHeader.length() << endl;
    }

    // Handle retrieving the body differently depending on whether it is test
    // or not.
    if (httpHeader.find("text/html") != string::npos) {
        // If the response is text/html, put the rest of the data into a string.
        vector<string> *imgLinks;

        // Extract the portion of the HTTP body that was attached to the end
        // of the recv that trailed the HTTP header.
        httpBody += strstr(msg, CRLFCRLF) + 4;

        // Handle receiving the data depending on whether there is a
        // Content-Length directive or not.
        pos1 = httpHeader.find("Content-Length");
        if (pos1 == string::npos) {
            // There is no Content-Length directive.  So don't bother looking
            // and just wait until recv() errors.
            while ((messageLength = recv(*sock, msg, MSS, 0)) != 0) {
                if (verboseFlag > 4) {
                    logfile << "*** bytes received: " << messageLength << endl;
                }
                if (messageLength == -1) {
                    logfile << "*** recv() error: " << errno << " [" <<
                            messageLength << "] [" << httpLength << "]" << endl;

                    return -1;
                }
                httpLength += messageLength;
                msg[messageLength] = '\0';
                httpBody += msg;

                // Close the socket and break if </html> has been read.
                pos2 = httpBody.find("</html>");
                if (pos2 == string::npos) {
                    currentSocket = NULL;
                    break;
                }
            }
            // If there's no Content-Length field, then there can't be
            // keep-alives, so close the socket.
            socketTable.closeSocket(serverAddress);
        } else {
            // Retrieve the amount specified by the Content-Length directive.
            int mss, contentLength;
            pos1 += 16;

            pos2 = httpHeader.find(CRLF, pos1 + 1);
            if (pos2 == string::npos) {
                return -1;
            }

            contentLength = atoi(httpHeader.substr(pos1, pos2 - pos1).c_str());

            if (verboseFlag > 4) {
                logfile << "*** Content-Length: " << contentLength << endl;
            }
            contentLength -= (httpLength - (httpHeader.length() + 4));
            if (verboseFlag > 4) {
                logfile << "*** Content-Length [remaining]: " << contentLength
                         << endl;
            }

            mss = contentLength < MSS ? contentLength : MSS;
            while (contentLength > 0 &&
                    (messageLength = recv(*sock, msg, mss, 0)) != 0) {
                if (verboseFlag > 4) {
                    logfile << "*** Content-Length [remaining]: "
                             << contentLength << endl;
                    logfile << "*** bytes expected: " << mss << endl;
                    logfile << "*** bytes received: " << messageLength << endl;
                }

                // Just ignore the data received.
                if (messageLength == -1) {
                    logfile << "*** recv() error: " << errno << " ["
                            << messageLength << "] [" << httpLength << "]"
                            << endl;
                    return -1;
                }
                httpLength += messageLength;
                msg[messageLength] = '\0';
                httpBody += msg;

                // Recalculate how much data needs to be retrieved.
                contentLength -= messageLength;
                mss = contentLength < MSS ? contentLength : MSS;
            }
        }
        if (verboseFlag > 4) {
            logfile << "*** HTTP text/html body:\n" << httpBody << endl;
            logfile << "*** body length: " << httpBody.length() << endl;
        }

        // Retrieve all the image links.
        if (verboseFlag > 3) {
            logfile << "*** <img> links:" << endl;
        }
        imgLinks = getImgLinks(httpBody);
        if (imageFlag && imgLinks != NULL) {
            for (unsigned int i = 0; i < imgLinks->size(); i++) {
                if (httpGet((*imgLinks)[i]) == -1) {
                    return -1;
                }
            }

            // Clean up the img link data.
            imgLinks->clear();
            delete imgLinks;
        } else {
            if (verboseFlag > 3) {
                logfile << "\tNo img links retrieved.\n" << endl;
            }
        }
    } else {
        // Else fill up a vector to delete immediately.
        int mss, contentLength;

        // Extract the content length from the HTTP header.
        pos1 = httpHeader.find("Content-Length");
        if (pos1 == string::npos) {
            return -1;
        }
        pos1 += 16;

        pos2 = httpHeader.find(CRLF, pos1 + 1);
        if (pos2 == string::npos) {
            return -1;
        }

        contentLength = atoi(httpHeader.substr(pos1, pos2 - pos1).c_str());

        if (verboseFlag > 4) {
            logfile << "*** Content-Length: " << contentLength << endl;
        }
        contentLength -= (httpLength - (httpHeader.length() + 4));
        if (verboseFlag > 4) {
            logfile << "*** Content-Length [remaining]: " << contentLength
                     << endl;
        }

        mss = contentLength < MSS ? contentLength : MSS;
        while (contentLength > 0
                && (messageLength = recv(*sock, msg, mss, 0)) != 0) {
            if (verboseFlag > 4) {
                logfile << "*** Content-Length [remaining]: "
                         << contentLength << endl;
                logfile << "*** bytes expected: " << mss << endl;
                logfile << "*** bytes received: " << messageLength << endl;
            }

            // Just ignore the data received.
            if (messageLength == -1) {
                logfile << "*** recv() error: [" << messageLength << "] ["
                         << httpLength << "]" << endl;
                return -1;
            }

            // Recalculate how much data needs to be retrieved.
            contentLength -= messageLength;
            mss = contentLength < MSS ? contentLength : MSS;
        }
    }
    delete msg;
    if (httpBody.length() == 0) {
        socketTable.closeSocket(serverAddress);
        return -1;
    }
    if (verboseFlag > 1) {
        logfile << "*** http body length: " << httpBody.length() << endl;
    }

    // Strip out the Status-Code from the HTTP response.  It's in the format:
    //
    // HTTP-Version SP Status-Code SP Reason-Phrase CRLF
    //
    // on the first line.  See RFC 2616 for more details.
    pos1 = httpHeader.find(SP);
    if (pos1 == string::npos) {
        return -1;
    }

    pos2 = httpHeader.find(SP, pos1 + 1);
    if (pos2 == string::npos) {
        return -1;
    }

    status = atoi(httpHeader.substr(pos1, pos2 - pos1).c_str());

    return status;
}

void WebClient::verbose(int level)
{
    verboseFlag = level;
}
