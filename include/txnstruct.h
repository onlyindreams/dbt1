/*
 *
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Mark Wong & Jenny Zhang &
 *                    Open Source Development Lab, Inc.
 *
 */
#ifndef __TXNSTRUCT_H
#define __TXNSTRUCT_H

#define MaxItem 100

struct SCRefreshItems
{
   int I_ID;
   int Qty;
};

struct SCListItems
{
   int I_ID;
   int Qty;
   double Cost;
   double SRP;
   char Title[60];
   char Backing[5];
};

struct OLItems
{
   int OL_I_ID;
   char Title[60];
   char Publisher[60];
   double cost;
   int OL_Qty;
   double OL_Discount;
   char OL_Comment[100];
};

struct HomeInfo
{
   //input
   int C_ID;
   //output
   char C_FName[15];
   char C_LName[15];
};

struct ShopCartInfo
{
   //input
   int AddFlag;
   struct SCRefreshItems RefreshItems[MaxItem];
   int Num_Refresh;
   int C_ID;
   int SC_ID;
   //output
   int PromoID1;
   int PromoID2;
   int PromoID3;
   int PromoID4;
   int PromoID5;
   struct SCListItems Items[MaxItem];
   int Num_SCL;
};

struct BuyReqInfo
{
   //input
   int ReturnFlag;
   char UName[20];
   char Passwd[20];
   // if ReturnFlag=1, output
   // if ReturnFlag=0, input
   char C_FName[15];
   char C_LName[15];
   char C_Street1[40];
   char C_Street2[40];
   char C_City[30];
   char C_State[20];
   char C_Zip[10];
   char C_Country[50];
   char C_Phone[16];
   char C_Email[50];
   char C_BirthDate[20];
   char C_Data[500];
   //output 
   int C_ID;
   double SC_Tax;
   double SC_ShipCost;
   double SC_Total;
   struct SCListItems Items[MaxItem];    
   int Num_Item;
};

struct BuyConfInfo
{
   //input
   char CX_Type[10];
   char CX_Number[16];
   char CX_Name[31];
   char CX_Expiry[20];
   char Street1[40];
   char Street2[40];
   char City[30];
   char State[20];
   char Zip[10];
   char Country[50];
   int SC_ID;
   int C_ID;
   //output
   struct SCListItems Items[MaxItem];
   double SC_SubTotal;
   double SC_Tax;
   double SC_ShipCost;
   double SC_Total;
   int Num_Item;
};

struct OrderInqInfo
{
   //input
   int C_ID;
   //output
   char C_UName[20];
};

struct OrderDispInfo
{
   //input
   char C_UName[20];
   char C_Passwd[20];
   //output
   int O_ID;
   char C_FName[15];
   char C_LName[15];
   char C_Phone[16];
   char C_Email[50];
   char O_Date[20];
   double O_SubTotal;
   double O_Tax;
   double O_Total;
   char O_ShipType[10];
   char O_ShipDate[20];
   char O_Status[15];
   char B_Street1[40];
   char B_Street2[40];
   char B_City[30];
   char B_State[20];
   char B_Zip[10];
   char B_Country[50];
   char S_Street1[40];
   char S_Street2[40];
   char S_City[30];
   char S_State[20];
   char S_Zip[10];
   char S_Country[50];
   struct OLItems OrderLineItems[MaxItem];
   int Num_OL;
   char CX_Type[10];
};

//NewProduc, BestSeller, SearchBySubject use the same structure
struct SearchSubInfo
{
   //input
   char SearchType;
   //may need to change later???
   char SearchString[40];
   //output
   char A_FName[20];
   char A_LName[20];
   char Title[60];
};

struct ProdDetailInfo
{
   //input
   int I_ID;
   //output
   char I_Title[60];
   char A_FName[20];
   char A_LName[20];
   char I_Publisher[60];
   char I_PubDate[20];
   char I_Subject[60];
   char I_Desc[500];
   double I_Cost;
   int I_Image;
   double I_SRP;
   char I_Avail[20];
   char I_ISBN[13];
   int I_Pages;
   char I_Backing[15];
   char I_Dimensions[25];
};
   
struct AdminConfInfo
{
   //input
   int I_ID;
   int I_NewImage;
   int I_NewThumbnail;
   double I_NewCost;
   //output
   char I_Title[60];
   char A_FName[20];
   char A_LName[20];
   char I_Subject[60];
   char I_Desc[500];
   double I_Cost;
   int I_Image;
   int I_Thumbnail;
   double I_SRP;
   char I_Backing[15];
   int I_Pages;
   char I_Publisher[60];
   char I_PubDate[20];
   char I_Dimensions[25];
   char I_ISBN[13];
};

struct AdminReqInfo
{
   //input
   int I_ID;
   //output
   double I_SRP;
   double I_Cost;
   char I_Title[60];
   int I_Image;
   int I_Thumbnail;
   char A_FName[20];
   char A_LName[20];
};

#endif //__TXNSTRUCT_H
