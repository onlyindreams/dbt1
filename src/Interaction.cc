/*
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2004 Mark Wong & Open Source Development Labs, Inc.
 *
 * 8 May 2004
 */

#include "Interaction.h"

Interaction::Interaction(int seed)
{
    int j;
    srand(seed);

    interactionName[ADMIN_CONFIRM] = "ADMIN_CONFIRM";
    interactionName[ADMIN_REQUEST] = "ADMIN_REQUEST";
    interactionName[BEST_SELLERS] = "BEST_SELLERS";
    interactionName[BUY_CONFIRM] = "BUY_CONFIRM";
    interactionName[BUY_REQUEST] = "BUY_REQUEST";
    interactionName[CUSTOMER_REGISTRATION] = "CUSTOMER_REGISTRATION";
    interactionName[HOME] = "HOME";
    interactionName[NEW_PRODUCTS] = "NEW_PRODUCTS";
    interactionName[ORDER_DISPLAY] = "ORDER_DISPLAY";
    interactionName[ORDER_INQUIRY] = "ORDER_INQUIRY";
    interactionName[PRODUCT_DETAIL] = "PRODUCT_DETAIL";
    interactionName[SEARCH_REQUEST] = "SEARCH_REQUEST";
    interactionName[SEARCH_RESULT] = "SEARCH_RESULT";
    interactionName[SHOPPING_CART] = "SHOPPING_CART";

    j = 0;
    co_name[j++] = "Algeria";
    co_name[j++] = "Argentina";
    co_name[j++] = "Armenia";
    co_name[j++] = "Australia";
    co_name[j++] = "Austria";
    co_name[j++] = "Azerbaijan";
    co_name[j++] = "Bahamas";
    co_name[j++] = "Bahrain";
    co_name[j++] = "Bangla Desh";
    co_name[j++] = "Barbados";
    co_name[j++] = "Belarus";
    co_name[j++] = "Belgium";
    co_name[j++] = "Bermuda";
    co_name[j++] = "Bolivia";
    co_name[j++] = "Botswana";
    co_name[j++] = "Brazil";
    co_name[j++] = "Bulgaria";
    co_name[j++] = "Canada";
    co_name[j++] = "Cayman Islands";
    co_name[j++] = "Chad";
    co_name[j++] = "Chile";
    co_name[j++] = "China";
    co_name[j++] = "Christmas Island";
    co_name[j++] = "Colombia";
    co_name[j++] = "Croatia";
    co_name[j++] = "Cuba";
    co_name[j++] = "Cyprus";
    co_name[j++] = "Czech Republic";
    co_name[j++] = "Denmark";
    co_name[j++] = "Dominican Republic";
    co_name[j++] = "Eastern Caribbean";
    co_name[j++] = "Ecuador";
    co_name[j++] = "Egypt";
    co_name[j++] = "El Salvador";
    co_name[j++] = "Estonia";
    co_name[j++] = "Ethiopia";
    co_name[j++] = "Falkland Island";
    co_name[j++] = "Faroe Island";
    co_name[j++] = "Fiji";
    co_name[j++] = "Finland";
    co_name[j++] = "France";
    co_name[j++] = "Gabon";
    co_name[j++] = "Germany";
    co_name[j++] = "Gibraltar";
    co_name[j++] = "Greece";
    co_name[j++] = "Guam";
    co_name[j++] = "Hong Kong";
    co_name[j++] = "Hungary";
    co_name[j++] = "Iceland";
    co_name[j++] = "India";
    co_name[j++] = "Indonesia";
    co_name[j++] = "Iran";
    co_name[j++] = "Iraq";
    co_name[j++] = "Ireland";
    co_name[j++] = "Israel";
    co_name[j++] = "Italy";
    co_name[j++] = "Jamaica";
    co_name[j++] = "Japan";
    co_name[j++] = "Jordan";
    co_name[j++] = "Kazakhstan";
    co_name[j++] = "Kuwait";
    co_name[j++] = "Lebanon";
    co_name[j++] = "Luxembourg";
    co_name[j++] = "Malaysia";
    co_name[j++] = "Mauritius";
    co_name[j++] = "Mexico";
    co_name[j++] = "Netherlands";
    co_name[j++] = "New Zealand";
    co_name[j++] = "Norway";
    co_name[j++] = "Pakistan";
    co_name[j++] = "Philippines";
    co_name[j++] = "Poland";
    co_name[j++] = "Portugal";
    co_name[j++] = "Romania";
    co_name[j++] = "Russia";
    co_name[j++] = "Saudi Arabia";
    co_name[j++] = "Singapore";
    co_name[j++] = "Slovakia";
    co_name[j++] = "South Africa";
    co_name[j++] = "South Korea";
    co_name[j++] = "Spain";
    co_name[j++] = "Sudan";
    co_name[j++] = "Sweden";
    co_name[j++] = "Switzerland";
    co_name[j++] = "Taiwan";
    co_name[j++] = "Thailand";
    co_name[j++] = "Trinidad";
    co_name[j++] = "Turkey";
    co_name[j++] = "United Kingdom";
    co_name[j++] = "United States";
    co_name[j++] = "Venezuela";
    co_name[j++] = "Zambia";

    cx_type[0] = "VISA";
    cx_type[1] = "MASTERCARD";
    cx_type[2] = "DISCOVER";
    cx_type[3] = "AMEX";
    cx_type[4] = "DINERS";

    i_subject[0] = "ARTS";
    i_subject[1] = "BIOGRAPHIES";
    i_subject[2] = "BUSINESS";
    i_subject[3] = "CHILDREN";
    i_subject[4] = "COMPUTERS";
    i_subject[5] = "COOKING";
    i_subject[6] = "HEALTH";
    i_subject[7] = "HISTORY";
    i_subject[8] = "HOME";
    i_subject[9] = "HUMOR";
    i_subject[10] = "LITERATURE";
    i_subject[11] = "MYSTERY";
    i_subject[12] = "NON-FICTION";
    i_subject[13] = "PARENTING";
    i_subject[14] = "POLITICS";
    i_subject[15] = "REFERENCE";
    i_subject[16] = "RELIGION";
    i_subject[17] = "ROMANCE";
    i_subject[18] = "SELF-HELP";
    i_subject[19] = "SCIENCE-NATURE";
    i_subject[20] = "SCIENCE-FICTION";
    i_subject[21] = "SPORTS";
    i_subject[22] = "TRAVEL";
    i_subject[23] = "YOUTH";

    o_ship_type[0] = "AIR";
    o_ship_type[1] = "FEDEX";
    o_ship_type[2] = "SHIP";
    o_ship_type[3] = "COURIER";
    o_ship_type[4] = "MAIL";

    searchType[SEARCH_AUTHOR] = "author";
    searchType[SEARCH_SUBJECT] = "subject";
    searchType[SEARCH_TITLE] = "title";

    // Initialize the interaction mix.
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            mixMatrix[i][j] = 0;
        }
    }

    mixMatrix[ADMIN_CONFIRM][HOME] = 9952;
    mixMatrix[ADMIN_CONFIRM][SEARCH_REQUEST] = 9999;

    mixMatrix[ADMIN_REQUEST][ADMIN_CONFIRM] = 8999;
    mixMatrix[ADMIN_REQUEST][HOME] = 9999;

    mixMatrix[BEST_SELLERS][HOME] = 167;
    mixMatrix[BEST_SELLERS][PRODUCT_DETAIL] = 472;
    mixMatrix[BEST_SELLERS][SEARCH_REQUEST] = 9927;
    mixMatrix[BEST_SELLERS][SHOPPING_CART] = 9999;

    mixMatrix[BUY_CONFIRM][HOME] = 84;
    mixMatrix[BUY_CONFIRM][SEARCH_REQUEST] = 9999;

    mixMatrix[BUY_REQUEST][BUY_CONFIRM] = 4614;
    mixMatrix[BUY_REQUEST][HOME] = 6546;
    mixMatrix[BUY_REQUEST][SHOPPING_CART] = 9999;

    mixMatrix[CUSTOMER_REGISTRATION][BUY_REQUEST] = 8666;
    mixMatrix[CUSTOMER_REGISTRATION][HOME] = 8760;
    mixMatrix[CUSTOMER_REGISTRATION][SEARCH_RESULT] = 9999;

    mixMatrix[HOME][BEST_SELLERS] = 8666;
    mixMatrix[HOME][NEW_PRODUCTS] = 8760;
    mixMatrix[HOME][ORDER_INQUIRY] = 8666;
    mixMatrix[HOME][SEARCH_REQUEST] = 8760;
    mixMatrix[HOME][SHOPPING_CART] = 9999;

    mixMatrix[NEW_PRODUCTS][HOME] = 8760;
    mixMatrix[NEW_PRODUCTS][PRODUCT_DETAIL] = 8666;
    mixMatrix[NEW_PRODUCTS][SEARCH_REQUEST] = 8760;
    mixMatrix[NEW_PRODUCTS][SHOPPING_CART] = 9999;

    mixMatrix[ORDER_DISPLAY][HOME] = 69;
    mixMatrix[ORDER_DISPLAY][SEARCH_REQUEST] = 9999; 

    mixMatrix[ORDER_INQUIRY][HOME] = 8666;
    mixMatrix[ORDER_INQUIRY][ORDER_DISPLAY] = 8760;
    mixMatrix[ORDER_INQUIRY][SEARCH_REQUEST] = 9999;

    mixMatrix[PRODUCT_DETAIL][ADMIN_REQUEST] = 58;
    mixMatrix[PRODUCT_DETAIL][HOME] = 832;
    mixMatrix[PRODUCT_DETAIL][PRODUCT_DETAIL] = 1288;
    mixMatrix[PRODUCT_DETAIL][SEARCH_REQUEST] = 8603;
    mixMatrix[PRODUCT_DETAIL][SHOPPING_CART] = 9999;

    mixMatrix[SEARCH_REQUEST][HOME] = 635;
    mixMatrix[SEARCH_REQUEST][SEARCH_RESULT] = 9135;
    mixMatrix[SEARCH_REQUEST][SHOPPING_CART] = 9999;

    mixMatrix[SEARCH_RESULT][HOME] = 2657; 
    mixMatrix[SEARCH_RESULT][PRODUCT_DETAIL] = 9294;
    mixMatrix[SEARCH_RESULT][SEARCH_REQUEST] = 9304;
    mixMatrix[SEARCH_RESULT][SHOPPING_CART] = 9999;

    mixMatrix[SHOPPING_CART][CUSTOMER_REGISTRATION] = 9294;
    mixMatrix[SHOPPING_CART][HOME] = 9304;
    mixMatrix[SHOPPING_CART][SHOPPING_CART] = 9999;
}

int Interaction::nextInteraction(int previousInteraction)
{
    int threshold = rand() % 9999 + 1;

    for (int i = 0; i < 14; i++) {
        if (mixMatrix[previousInteraction][i] != 0
                && threshold < mixMatrix[previousInteraction][i]) {
            return i;
        }
    }
    return -1;
}
