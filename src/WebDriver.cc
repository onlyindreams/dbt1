/*
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2004 Mark Wong & Open Source Development Labs, Inc.
 *
 * 9 May 2004
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#include <sys/time.h>

#include "WebDriver.h"

WebDriver::WebDriver(int id, int items, int customers, string url,
        time_t stopTime, int usmd, int thinktime)
    : WebClient(id)
{
    baseUrl = url;
    this->stopTime = stopTime;
    averageUsmd = usmd;
    averageThinktime = thinktime;
    this->items = items;
    this->customers = customers;

    interaction = new Interaction(id);

    // Assign the method pointers.
    interactionFunction[Interaction::ADMIN_CONFIRM] =
        &WebDriver::doAdminConfirm;
    interactionFunction[Interaction::ADMIN_REQUEST] =
        &WebDriver::doAdminRequest;
    interactionFunction[Interaction::BEST_SELLERS] = &WebDriver::doBestSellers;
    interactionFunction[Interaction::BUY_CONFIRM] = &WebDriver::doBuyConfirm;
    interactionFunction[Interaction::BUY_REQUEST] = &WebDriver::doBuyRequest;
    interactionFunction[Interaction::CUSTOMER_REGISTRATION] =
        &WebDriver::doCustomerRegistration;
    interactionFunction[Interaction::HOME] = &WebDriver::doHome;
    interactionFunction[Interaction::NEW_PRODUCTS] = &WebDriver::doNewProducts;
    interactionFunction[Interaction::ORDER_DISPLAY] =
        &WebDriver::doOrderDisplay;
    interactionFunction[Interaction::ORDER_INQUIRY] =
        &WebDriver::doOrderInquiry;
    interactionFunction[Interaction::PRODUCT_DETAIL] =
        &WebDriver::doProductDetail;
    interactionFunction[Interaction::SEARCH_REQUEST] =
        &WebDriver::doSearchRequest;
    interactionFunction[Interaction::SEARCH_RESULT] =
        &WebDriver::doSearchResult;
    interactionFunction[Interaction::SHOPPING_CART] =
        &WebDriver::doShoppingCart;

    syllable[0] = "BA";
    syllable[1] = "OG";
    syllable[2] = "AL";
    syllable[3] = "RI";
    syllable[4] = "RE";
    syllable[5] = "SE";
    syllable[6] = "AT";
    syllable[7] = "UL";
    syllable[8] = "IN";
    syllable[9] = "NG";

    if (customers < 10000) {
        a = 1023; 
    } else if (customers < 40000) {
        a = 4095; 
    } else if (customers < 160000) {
        a = 16383;
    } else if (customers < 640000) {
        a = 65535;
    } else if (customers < 2560000) {
        a = 262143; 
    } else if (customers < 10240000) {
        a = 1048575;
    } else if (customers < 40960000) {
        a = 4194303;
    } else if (customers < 163840000) {
        a = 16777215;
    } else if (customers >= 163840000) {
        a = 67108863;
    } 

    aStringChar = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_-=+{}[]|:;,.?/~ ";
    nStringChar = "0123456789";
}

WebDriver::~WebDriver()
{
    delete interaction;
}

// Clause 4.6.2.2
string WebDriver::astring(int min, int max)
{
    int length;
    string str = "";

    length = min + (rand() % (max - min + 1)) + 1;

    for (int i = 0; i < length - 1; i++) {
        str += aStringChar.c_str()[rand() % aStringChar.length()];
    }

    return str;
}

double WebDriver::difftimeval(struct timeval *end, struct timeval *start)
{
    return static_cast<double>(end->tv_sec - start->tv_sec)
        + static_cast<double>(end->tv_usec - start->tv_usec) / 1000000.0;
}

// Clause 2.16
int WebDriver::doAdminConfirm()
{
    string i_id, i_cost, i_image, i_thumbnail;
    stringstream image, thumb;
    int tries = 0;

    i_id = getProductDetailIid();

    image << rand() % items;
    i_image = image.str();
    thumb << rand() % items;
    i_thumbnail = thumb.str();
    // I think this needs to be pulled from the web page.
    i_cost = "1.1";

    request = baseUrl + "adminconfirm?sc_id=" + sc_id + "&c_id="
        + c_id + "&i_id=" + i_id + "&i_cost=" + i_cost + "&i_image="
        + i_image + "&i_thumbnail=" + i_thumbnail;
    if (verboseFlag > 0) {
        logfile << "*** " << interaction->interactionName[currentInteraction]
                << " " << request << endl;
    }
    do {
        status = httpGet(request);
        if (status != 200) {
            logfile << "STATUS " << status << " "
                    << interaction->interactionName[currentInteraction]
                    << endl;
        }
    }
    while (status != 200 && tries++ < retryMax);
    getCid();
    getScid();

    return 1;
}

// Clause 2.15
int WebDriver::doAdminRequest()
{
    int tries = 0;

    request = baseUrl + links.at(4);
    if (verboseFlag > 0) {
        logfile << "*** " << interaction->interactionName[currentInteraction]
                << " " << request << endl;
    }
    do {
        status = httpGet(request);
        if (status != 200) {
            logfile << "STATUS " << status  << " "
                    << interaction->interactionName[currentInteraction]
                    << endl;
        }
    }
    while (status != 200 && tries++ < retryMax);
    getCid();
    getScid();

    return 1;
}

// Clause 2.13
int WebDriver::doBestSellers()
{
    int tries = 0;

    request = baseUrl + "bestsellers?i_subject="
        + interaction->i_subject[rand() % 24] + "&sc_id=" + sc_id
        + "&c_id=" + c_id;
    if (verboseFlag > 0) {
        logfile << "*** " << interaction->interactionName[currentInteraction]
                << " " << request << endl;
    }
    do {
        status = httpGet(request);
        if (status != 200) {
            logfile << "STATUS " << status  << " "
                    << interaction->interactionName[currentInteraction]
                    << endl;
        }
        getProductLinks();
    }
    while ((status != 200 || productLinks.size() == 0)
        && tries++ < retryMax);
    getCid();
    getScid();

    return 1;
}

// Clause 2.7
int WebDriver::doBuyConfirm()
{
    string request = baseUrl + "buyconfirm?sc_id=" + sc_id + "&c_id=" + c_id;
    string c_fname, c_lname;
    string::size_type start, end;
    time_t t1;
    struct tm *tm1;
    stringstream year, month, day;
    int tries = 0;

    // Extract c_fname and c_lname from the Buy Request response page.
    start = httpBody.find("<td>First name:</td>", 0) + 5;
    start = httpBody.find("<td>", start) + 5;
    end = httpBody.find("</td>", start);
    c_fname = httpBody.substr(start, end - start);
    start = httpBody.find("<td>Last name:</td>", end) + 5;
    start = httpBody.find("<td>", start) + 5;
    end = httpBody.find("</td>", start);
    c_lname = httpBody.substr(start, end - start);

    if ((static_cast<double>(rand()) / static_cast<double>(RAND_MAX)) > 0.05) {
        request += "&addr_street1=&addr_street2=&addr_city=&addr_state=&addr_zip=&co_name=";
    } else {
        request += "&addr_street1="
            + escape(astring(15, Interaction::ADDR_STREET1_LEN));
        request += "&addr_street2="
            + escape(astring(15, Interaction::ADDR_STREET2_LEN));
        request += "&addr_city="
            + escape(astring(4, Interaction::ADDR_CITY_LEN));
        request += "&addr_state="
            + escape(astring(2, Interaction::ADDR_STATE_LEN));
        request += "&addr_zip=" + escape(astring(5, Interaction::ADDR_ZIP_LEN));
        request += "&co_name=" + interaction->co_name[rand() % 92];
    }
    request += "&cx_type=" + interaction->cx_type[rand() % 5];
    request += "&cx_name=" + escape(c_fname) + "+" + escape(c_lname);
    request += "&cx_num=" + nstring(16, 16);

    time(&t1);
    t1 += 86400 + (rand() % 63158400);
    tm1 = localtime(&t1);
    year << tm1->tm_year + 1900;
    request += "&cx_expiry=" + year.str() + "%2F";
    // There must be a better way to pad these numbers with 0's.
    month << tm1->tm_mon + 1;
    if (month.str().length() == 1) {
        request += "0";
    }
    request += month.str() + "%2F";
    day << tm1->tm_mday;
    if (day.str().length() == 1) {
        request += "0";
    }
    request += day.str();

    request += "&o_ship_type=" + interaction->o_ship_type[rand() % 5];

    if (verboseFlag > 0) {
        logfile << "*** " << interaction->interactionName[currentInteraction]
                << " " << request << endl;
    }
    do {
        status = httpGet(request);
        if (status != 200) {
            logfile << "STATUS " << status  << " "
                    << interaction->interactionName[currentInteraction]
                    << endl;
        }
    } while (status != 200 && tries++ < retryMax);
    getCid();
    getScid();

    return 1;
}

// Clause 2.6
int WebDriver::doBuyRequest()
{
    string request = baseUrl + "buyrequest?sc_id=" + sc_id + "&c_id=" + c_id;
    int tries = 0;

    if (c_id.compare("0") != 0) {
        // Returning customer.
        string c_uname, c_passwd = "";

        c_uname = digsyl(atoi(c_id.c_str()), 0);
        for (unsigned int i = 0; i < c_uname.length(); i++) {
            c_passwd += tolower(c_uname.c_str()[i]);
        }
        request += "&returning=y&c_uname=" + c_uname
            + "&c_passwd=" + c_passwd
            + "&c_birthdate=&c_fname=&c_lname=&addr_street1=&addr_street2="
            + "&addr_city=&addr_state=&addr_zip=&co_name=&c_phone=&c_email="
            + "&c_data=";
    } else {
        // New customer.
        time_t t1, t2, t3;
        struct tm tm1, *tm2, *tm3;
        stringstream year, month, day;
        string c_fname, c_lname;

        request += "&returning=n&c_uname=&c_passwd=&c_birthdate=";

        // The date is being calculated from 1900 instead of 1880.
        tm1.tm_year = 0;
        tm1.tm_mon = 0;
        tm1.tm_mday = 1;
        tm1.tm_sec = 0;
        tm1.tm_min = 0;
        tm1.tm_hour = 0;
        t1 = mktime(&tm1);
        time(&t2);
        tm2 = localtime(&t2);
        t3 = static_cast<time_t>((static_cast<double>(rand())
            / static_cast<double>(RAND_MAX))
            * static_cast<double>(static_cast<long long>(t2)
            - static_cast<long long>(t1) + static_cast<long long>(86400))) + t1;
        tm3 = localtime(&t3);
        year << tm3->tm_year + 1900;
        request += year.str() + "%2F";
        // There must be a better way to pad these numbers with 0's.
        month << tm3->tm_mon + 1;
        if (month.str().length() == 1) {
            request += "0";
        }
        request += month.str() + "%2F";
        day << tm3->tm_mday;
        if (day.str().length() == 1) {
            request += "0";
        }
        request += day.str();

        c_fname = escape(astring(8, Interaction::C_FNAME_LEN));
        c_lname = escape(astring(8, Interaction::C_LNAME_LEN));
        request += "&c_fname=" + c_fname + "&c_lname=" + c_lname;
        request += "&addr_street1="
            + escape(astring(15, Interaction::ADDR_STREET1_LEN));
        request += "&addr_street2="
            + escape(astring(15, Interaction::ADDR_STREET2_LEN));
        request += "&addr_city="
            + escape(astring(4, Interaction::ADDR_CITY_LEN));
        request += "&addr_state="
            + escape(astring(2, Interaction::ADDR_STATE_LEN));
        request += "&addr_zip=" + escape(astring(5, Interaction::ADDR_ZIP_LEN));
        request += "&co_name=" + interaction->co_name[rand() % 92];
        request += "&c_phone=" + nstring(9, Interaction::C_PHONE_LEN);
        request += "&c_email=" + c_fname + "%40" + c_lname + ".com";
        request += "&c_data=" + escape(astring(100, Interaction::C_DATA_LEN));
    }
    if (verboseFlag > 0) {
        logfile << "*** " << interaction->interactionName[currentInteraction]
                << " " << request << endl;
    }
    do {
        status = httpGet(request);
        if (status != 200) {
            logfile << "STATUS " << status  << " "
                    << interaction->interactionName[currentInteraction]
                    << endl;
        }
    } while (status != 200 && tries++ < retryMax);
    getCid();
    getScid();

    return 1;
}

// Clause 2.3
int WebDriver::doCustomerRegistration()
{
    int tries = 0;

    request = baseUrl + "adjustment?sc_id=" + sc_id + "&c_id="
        + c_id + "&submit=checkout";
    if (verboseFlag > 0) {
        logfile << "*** " << interaction->interactionName[currentInteraction]
                << " " << request << endl;
    }
    do {
        status = httpGet(request);
        if (status != 200) {
            logfile << "STATUS " << status  << " "
                    << interaction->interactionName[currentInteraction]
                    << endl;
        }
    } while (status != 200 && tries++ < retryMax);
    getCid();
    getScid();

    return 1;
}

// Clause 2.12
int WebDriver::doHome()
{
    int tries = 0;

/*
    // lastInteraction == Interaction::HOME if this is the very first
    // interaction for this user session.
    if (lastInteraction == Interaction::HOME) {
        request = baseUrl;
    } else {
*/
        request = baseUrl + "home?sc_id=" + sc_id + "&c_id=" + c_id;
/*
    }
*/
    if (verboseFlag > 0) {
        logfile << "*** " << interaction->interactionName[currentInteraction]
                << " " << request << endl;
    }
    do {
        status = httpGet(request);
        if (status != 200) {
            logfile << "STATUS " << status  << " "
                    << interaction->interactionName[currentInteraction]
                    << endl;
        }
    } while (status != 200 && tries++ < retryMax);
    getCid();
    getScid();
    getProductLinks();

    return 1;
}

// Clause 2.12
int WebDriver::doNewProducts()
{
    int tries = 0;

    request = baseUrl + "newproducts?i_subject="
        + interaction->i_subject[rand() % 24] + "&sc_id=" + sc_id
        + "&c_id=" + c_id;
    if (verboseFlag > 0) {
        logfile << "*** " << interaction->interactionName[currentInteraction]
                << " " << request << endl;
    }
    do {
        status = httpGet(request);
        if (status != 200) {
            logfile << "STATUS " << status  << " "
                    << interaction->interactionName[currentInteraction]
                    << endl;
        }
        getProductLinks();
    } while ((status != 200 || productLinks.size() == 0) && tries++ < retryMax);
    getCid();
    getScid();

    return 1;
}

// Clause 2.9
int WebDriver::doOrderDisplay()
{
    string c_uname, c_passwd = "";
    int tries = 0;

    c_uname = digsyl(atoi(c_id.c_str()), 0);
    for (unsigned int i = 0; i < c_uname.length(); i++) {
        c_passwd += tolower(c_uname.c_str()[i]);
    }
    request = baseUrl + "orderdisplay?sc_id=" + sc_id + "&c_id="
        + c_id + "&c_uname=" + c_uname + "&c_passwd=" + c_passwd;
    if (verboseFlag > 0) {
        logfile << "*** " << interaction->interactionName[currentInteraction]
                << " " << request << endl;
    }
    do {
        status = httpGet(request);
        if (status != 200) {
            logfile << "STATUS " << status  << " "
                    << interaction->interactionName[currentInteraction]
                    << endl;
        }
    } while (status != 200 && tries++ < retryMax);
    getCid();
    getScid();

    return 1;
}

// Clause 2.8
int WebDriver::doOrderInquiry()
{
    int tries = 0;

    request = baseUrl + "orderinquiry?sc_id=" + sc_id + "&c_id=" + c_id;
    if (verboseFlag > 0) {
        logfile << "*** " << interaction->interactionName[currentInteraction]
                << " " << request << endl;
    }
    do {
        status = httpGet(request);
        if (status != 200) {
            logfile << "STATUS " << status  << " "
                    << interaction->interactionName[currentInteraction]
                    << endl;
        }
    } while (status != 200 && tries++ < retryMax);
    getCid();
    getScid();

    return 1;
}

// Clause 2.14
int WebDriver::doProductDetail()
{
    int size;
    int tries = 0;

    size = productLinks.size();
    if (size == 0) {
        logfile << "*** no products, don't know what to do, last interaction: "
                << interaction->interactionName[lastInteraction] << endl;
        logfile << httpHeader << endl;
        logfile << httpBody << endl;
        return 0;
    }

    request = baseUrl + productLinks.at(rand() % size);
    if (verboseFlag > 0) {
        logfile << "*** " << interaction->interactionName[currentInteraction]
                << " " << request << endl;
    }
    do {
        status = httpGet(request);
        if (status != 200) {
            logfile << "STATUS " << status  << " "
                    << interaction->interactionName[currentInteraction]
                    << endl;
        }
    } while (status != 200 && tries++ < retryMax);
    getCid();
    getScid();

    return 1;
}

int WebDriver::doSearchRequest()
{
    int tries = 0;

    request = baseUrl + "searchrequest?sc_id=" + sc_id + "&c_id=" + c_id;
    if (verboseFlag > 0) {
        logfile << "*** " << interaction->interactionName[currentInteraction]
                << " " << request << endl;
    }
    do {
        status = httpGet(request);
        if (status != 200) {
            logfile << "STATUS " << status  << " "
                    << interaction->interactionName[currentInteraction]
                    << endl;
        }
        getProductLinks();
    } while ((status != 200 || productLinks.size() == 0) && tries++ < retryMax);
    getCid();
    getScid();

    return 1;
}

// Clause 2.8
int WebDriver::doSearchResult()
{
    int searchType;
    string searchField;
    int tries = 0;

    searchType = rand() % 3;
    switch (searchType) {
    case Interaction::SEARCH_AUTHOR:
        searchField = digsyl(nuRand(a, 1, items / 10), 7);
        break;
    case Interaction::SEARCH_SUBJECT:
        searchField = interaction->i_subject[rand() % 24];
        break;
    case Interaction::SEARCH_TITLE:
        searchField = digsyl(nuRand(a, 1, items / 5), 7);
        break;
    }

    request = baseUrl + "searchresults?sc_id=" + sc_id + "&c_id="
        + c_id + "&type=" + interaction->searchType[searchType] + "&field="
        + searchField;
    if (verboseFlag > 0) {
        logfile << "*** " << interaction->interactionName[currentInteraction]
                << " " << request << endl;
    }
    do {
        status = httpGet(request);
        if (status != 200) {
            logfile << "STATUS " << status  << " "
                    << interaction->interactionName[currentInteraction]
                    << endl;
        }
        getProductLinks();
    } while ((status != 200 || productLinks.size() == 0) && tries++ < retryMax);
    getCid();
    getScid();

    return 1;
}

// Clause 2.4
int WebDriver::doShoppingCart()
{
    int tries = 0;

    if (lastInteraction == Interaction::SHOPPING_CART) {
        request = getRefreshRequest();
        if (request.length() == 0) {
            logfile << "*** couldn't generate refresh request" << endl;
            logfile << httpHeader << endl;
            logfile << httpBody << endl;
        }
    } else if (lastInteraction == Interaction::PRODUCT_DETAIL) {
        string i_id = getProductDetailIid();
        if (i_id.length() == 0) {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " don't know what to do..." << endl;
            return 0;
        }

        request = baseUrl + "shoppingcart?add_flag=y&i_id=" + i_id + "&sc_id="
            + sc_id + "&c_id=" + c_id;
    } else {
        request = baseUrl + "shoppingcart?add_flag=n&sc_id=" + sc_id
            + "&c_id=" + c_id;
    }
    if (verboseFlag > 0) {
        logfile << "*** " << interaction->interactionName[currentInteraction]
                << " " << request << endl;
    }
    do {
        status = httpGet(request);
        if (status != 200) {
            logfile << "STATUS " << status  << " "
                    << interaction->interactionName[currentInteraction]
                    << endl;
        }
    } while (status != 200 && tries++ < retryMax);
    getCid();
    getScid();
    getProductLinks();

    return 1;
}

string WebDriver::digsyl(long long d, long long n)
{
    string str = "";
    char dig[32];
    long long pad;
    long long length;

    if (d < 0) {   
        return str; 
    }   

    sprintf(dig, "%lld", d); 
    length = strlen(dig);
    pad = n - length;
    if (pad < 0) {   
        pad = 0;
    }   
    for (int i = 0; i < pad; i++) {   
        str += syllable[0];
    }   
    for (int i = 0; i < length; i++) {   
        str += syllable[dig[i] - '0'];
    }   
    return str;
}

string WebDriver::escape(string html)
{
    string str = "";

    for (unsigned int i = 0; i < html.length(); i++) {
        char c = html.c_str()[i];
        if (c == '!') {
            str += "%21";
        } else if (c == '@') {
            str += "%40";
        } else if (c == '#') {
            str += "%23";
        } else if (c == '$') {
            str += "%24";
        } else if (c == '%') {
            str += "%25";
        } else if (c == '^') {
            str += "%5E";
        } else if (c == '&') {
            str += "%26";
        } else if (c == '(') {
            str += "%28";
        } else if (c == ')') {
            str += "%29";
        } else if (c == '=') {
            str += "%3D";
        } else if (c == '+') {
            str += "%2B";
        } else if (c == '{') {
            str += "%7B";
        } else if (c == '}') {
            str += "%7D";
        } else if (c == '[') {
            str += "%5B";
        } else if (c == ']') {
            str += "%5D";
        } else if (c == '|') {
            str += "%7C";
        } else if (c == ':') {
            str += "%3A";
        } else if (c == ';') {
            str += "%3B";
        } else if (c == ',') {
            str += "%2C";
        } else if (c == '?') {
            str += "%3F";
        } else if (c == '/') {
            str += "%2F";
        } else if (c == '~') {
            str += "%7E";
        } else if (c == ' ') {
            str += "+";
        } else {
            str += c;
        }
    }

    return str;
}

int WebDriver::getCid()
{
    string::size_type start, end;
    string::size_type tagEnd;

    // Is there a better way to do pattern matching?
    start = httpBody.find("<a href", 0);
    if (start == string::npos) {
        logfile << "*** "
                << interaction->interactionName[currentInteraction]
                << " could not find start of tag for c_id" << endl;
        logfile << httpHeader << endl;
        logfile << httpBody << endl;
        return 0;
    }
    start = httpBody.find("&c_id=", start);
    if (start == string::npos) {
        start = httpBody.find("?c_id=", start);
        if (start == string::npos) {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " could not find c_id in tag" << endl;
            return 0;
        }
    }
    if (start != string::npos) {
        start += 6;
        // Find the end of the tag.
        tagEnd = httpBody.find(">", start);
        if (tagEnd == string::npos) {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " could not find end of tag for c_id" << endl;
            return 0;
        }
        end = httpBody.substr(start, tagEnd - start).find("&", 0);
        if (end == string::npos) {
            end = httpBody.substr(start, tagEnd - start).find("\"", 0);
        }
        if (end == string::npos) {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " could not parse c_id: "
                    << httpBody.substr(start, tagEnd - start) << endl;
            return 0;
        }
        c_id = httpBody.substr(start, end);
        if (verboseFlag > 3) {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " c_id = " << c_id << endl;
        }
    } else {
        logfile << "*** "
                << interaction->interactionName[currentInteraction]
                << " could not find start of tag for c_id" << endl;
        return 0;
    }
    return 1;
}

string WebDriver::getProductDetailIid()
{
    string i_id = "";
    string::size_type start, end;
    string::size_type tagEnd;

    // Is there a better way to do pattern matching?
    start = httpBody.find("<a href=\"shoppingcart?add_flag=y&i_id=", 0);
    if (start != string::npos) {
        start += 38;
        // Find the end of the tag.
        tagEnd = httpBody.find(">", start);
        if (tagEnd == string::npos) {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " could not find end of tag for i_id" << endl;
            return i_id;
        }
        end = httpBody.substr(start, tagEnd - start).find("&", 0);
        if (end == string::npos) {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " could not parse i_id: "
                    << httpBody.substr(start, tagEnd - start) << endl;
            return i_id;
        }
        i_id = httpBody.substr(start, end);
        if (verboseFlag > 3) {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " i_id = " << i_id << endl;
        }
    } else {
        logfile << "*** "
                << interaction->interactionName[currentInteraction]
                << " could not find start of tag for i_id" << endl;
        logfile << httpHeader << endl;
        logfile << httpBody << endl;
        return i_id;
    }

    return i_id;
}

void WebDriver::getProductLinks()
{
    getLinks();
    productLinks.clear();
    for (unsigned int i = 0; i < links.size(); i++) {
        string tmpLink = links.at(i);
        if (tmpLink.find("productdetail", 0) != string::npos) {
            productLinks.push_back(tmpLink);
        }
    }
    if (verboseFlag > 2) {
        logfile << "*** " << productLinks.size() << " product links found"
                << endl;
    }
}

// Clause 2.4.5.1
// Not exactly following the spec, for each pair, determine (50% change)
// if the qty should be changed.
string WebDriver::getRefreshRequest()
{
    string request = baseUrl + "adjustment?&sc_id=" + sc_id + "&c_id=" + c_id;
    string i_id, qty;
    string::size_type start = 0, end;
    string::size_type tagEnd;

    while (1) {
        // Get the i_id.
        start = httpBody.find("<input type=\"hidden\" name=\"i_id\"", start);
        if (start == string::npos) {
            // In this case, we're done.
            return request + "&submit=refresh";
        }
        start = httpBody.find("value=", start);
        if (start != string::npos) {
            start += 7;
            // Find the end of the tag.
            tagEnd = httpBody.find(">", start);
            if (tagEnd == string::npos) {
                logfile << "*** "
                        << interaction->interactionName[currentInteraction]
                        << " could not find end of tag for i_id" << endl;
                return "";
            }
            end = httpBody.substr(start, tagEnd - start).find("\"", 0);
            if (end == string::npos) {
                logfile << "*** "
                        << interaction->interactionName[currentInteraction]
                        << " could not parse i_id: "
                        << httpBody.substr(start, tagEnd - start) << endl;
                return "";
            }
            i_id = httpBody.substr(start, end);
            if (verboseFlag > 3) {
                logfile << "*** "
                        << interaction->interactionName[currentInteraction]
                        << " i_id = " << i_id << endl;
            }
        } else {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " could not find start of tag for i_id" << endl;
            return "";
        }

        // Get the qty.
        start = httpBody.find("<input name=\"qty\"", tagEnd);
        if (start == string::npos) {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " could not find start of tag for qty" << endl;
            logfile << httpHeader << endl;
            logfile << httpBody << endl;
            return "";
        }
        start = httpBody.find("value=", start);
        if (start != string::npos) {
            start += 7;
            // Find the end of the tag.
            tagEnd = httpBody.find(">", start);
            if (tagEnd == string::npos) {
                logfile << "*** "
                        << interaction->interactionName[currentInteraction]
                        << " could not find end of tag for qty" << endl;
                return "";
            }
            end = httpBody.substr(start, tagEnd - start).find("\"", 0);
            if (end == string::npos) {
                logfile << "*** "
                        << interaction->interactionName[currentInteraction]
                        << " could not parse qty: "
                        << httpBody.substr(start, tagEnd - start) << endl;
                return "";
            }
            qty = httpBody.substr(start, end);
            if (verboseFlag > 3) {
                logfile << "*** "
                        << interaction->interactionName[currentInteraction]
                        << " qty = " << qty << endl;
            }
        } else {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " could not find start of tag for qty" << endl;
            return "";
        }

        if ((rand() % 1000) > 500) {
            stringstream s;
            s << (rand() % 9) + 1;
            qty = s.str();
        }

        request += "&i_id=" + i_id + "&qty=" + qty;
        start = tagEnd;
    }

    return request;
}

int WebDriver::getScid()
{
    string::size_type start, end;
    string::size_type tagEnd;

    // Is there a better way to do pattern matching?
    start = httpBody.find("<a href", 0);
    if (start == string::npos) {
        logfile << "*** "
                << interaction->interactionName[currentInteraction]
                << " could not find start of tag for sc_id" << endl;
        logfile << httpHeader << endl;
        logfile << httpBody << endl;
        return 0;
    }
    start = httpBody.find("&sc_id=", start);
    if (start == string::npos) {
        start = httpBody.find("?sc_id=", start);
        if (start == string::npos) {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " could not find sc_id in tag" << endl;
            return 0;
        }
    }
    if (start != string::npos) {
        start += 7;
        // Find the end of the tag.
        tagEnd = httpBody.find(">", start);
        if (tagEnd == string::npos) {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " could not find end of tag for sc_id" << endl;
            return 0;
        }
        end = httpBody.substr(start, tagEnd - start).find("&", 0);
        if (end == string::npos) {
            end = httpBody.substr(start, tagEnd - start).find("\"", 0);
        }
        if (end == string::npos) {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " could not parse sc_id: "
                    << httpBody.substr(start, tagEnd - start) << endl;
            return 0;
        }
        sc_id = httpBody.substr(start, end);
        if (verboseFlag > 3) {
            logfile << "*** "
                    << interaction->interactionName[currentInteraction]
                    << " sc_id = " << sc_id << endl;
        }
    } else {
        logfile << "*** "
                << interaction->interactionName[currentInteraction]
                << " could not find start of tag for sc_id" << endl;
        return 0;
    }
    return 1;
}

////
// Title:       getThinktime
//              
// Description:
// 
//     Think time generator, in milliseconds.
//     Clause 5.3.1.1.  The precision of the number to normalize
//     has a profound affect on the mean of the distribution.
//     I've been able to tune the calculations to be about .1 seconds
//     above the targeted think time.  Since this is fairly good precision,
//     I'll leave the target as a runtime adjustable setting.
// 
// Inputs:
// 
// Outputs: double - Think time in milliseconds.
//
// Example: getThinktime
//
// Date: 9 November 2000
//
// Author: Mark Wong (markw@osdl.org)
////
double WebDriver::getThinktime()
{
    double value = -1 * log((static_cast<double>(rand() % 99999999) + 1.0)
        / 100000000.0) * static_cast<double>(averageThinktime);

    if (value > (static_cast<double>(averageThinktime) * 10.0)) {
        return static_cast<double>(averageThinktime) * 10.0;
    }

    return value;

}

////
// Title:   getUsmd
//
// Description:
//
//      User Session Minimum Duration in seconds.
//      Clause 6.2.1.2.
//
// Inputs:
//
// Outputs: double - User session duration in seconds.
//
// Example: getUsmd
//
// Date: 26 September 2000
//
// Author: Mark Wong (markw@osdl.org)
////
double WebDriver::getUsmd()
{
    double value = -1 * log((static_cast<double>(rand() % 100000000) + 1.0)
        / 100000000.0) * static_cast<double>(averageUsmd);

    if (value > 3600.0) {
        return 3600.0;
    }

    return value;
}

// Clause 4.6.2.3
string WebDriver::nstring(int min, int max)
{
    int length;
    string str = "";
    
    length = min + (rand() % (max - min + 1)) + 1; 
    
    for (int i = 0; i < length - 1; i++) {
        str += nStringChar[rand() % nStringChar.length()];
    }
    
    return str;
}

// Clause 2.1.13
int WebDriver::nuRand(int a, int x, int y)
{ 
    return (((rand() % a + 1) | (x + rand() % y + 1)) % (y - x + 1)) + x;
}

void WebDriver::start()
{
    double usmd;
    double thinktime;
    struct timeval sessionStartTime;
    struct timeval tvStart;
    struct timeval tvEnd;
    struct timezone tz;

    do {
        // Get this user's minimum duration time.
        c_id = "0";
        sc_id = "0";
        usmd = getUsmd();
        logfile << "USMD " << usmd << endl;
        gettimeofday(&sessionStartTime, &tz);

	// Predetermine if this a returning customer.
        if ((static_cast<double>(rand()) / static_cast<double>(RAND_MAX))
                <= 0.80) {
            stringstream s;

            s << (rand() % customers) + 1;
            c_id = s.str();
        }

        // Request the first Home interaction.
        currentInteraction = lastInteraction = Interaction::HOME;
        gettimeofday(&tvStart, &tz);
        if ((this->*interactionFunction[Interaction::HOME])() == 0) {
            continue;
        }
        gettimeofday(&tvEnd, &tz);
        logfile << "RESPONSE_TIME " << time(NULL) << " "
                << interaction->interactionName[currentInteraction] << " "
                << difftimeval(&tvEnd, &tvStart) << endl;
        currentInteraction = interaction->nextInteraction(lastInteraction);
        thinktime = static_cast<unsigned int>(getThinktime());
        logfile << "THINKTIME " << thinktime << endl;
        usleep(static_cast<unsigned int>(thinktime) * 1000);

        // Continue the rest of the this user's interaction requests.
        gettimeofday(&tvStart, &tz);
        while (usmd > difftimeval(&tvStart, &sessionStartTime)
                || lastInteraction != Interaction::HOME) {
            currentInteraction = interaction->nextInteraction(lastInteraction);
            if ((this->*interactionFunction[currentInteraction])() == 0) {
                break;
            }
            gettimeofday(&tvEnd, &tz);
            logfile << "RESPONSE_TIME " << time(NULL) << " "
                    << interaction->interactionName[currentInteraction] << " "
                    << difftimeval(&tvEnd, &tvStart) << endl;
            lastInteraction = currentInteraction;
            if (usmd > difftimeval(&tvEnd, &sessionStartTime)
                    || lastInteraction != Interaction::HOME) {
                thinktime = static_cast<unsigned int>(getThinktime());
                logfile << "THINKTIME " << thinktime << endl;
                usleep(static_cast<unsigned int>(thinktime) * 1000);
            }
            gettimeofday(&tvStart, &tz);
        }
    } while (time(NULL) < stopTime);
}
