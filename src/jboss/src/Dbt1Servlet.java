/*
 * This file is released under the terms of the Artistic License.  Please see
 * the file LICENSE, included in this package, for details.
 *
 * Copyright (C) 2002 Open Source Development Lab, Inc.
 * History:
 * 2004 Created by Mark Wong
 */

import java.io.*;
import java.util.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

import org.postgresql.jdbc3.*;

/**
 * DBT-1 servlet class.
 */
public class Dbt1Servlet extends HttpServlet
{

    /* Constants */
    public static final String Adjustment = "adjustment";
    public static final String ShoppingCartRefresh = "refresh";
    public static final String ShoppingCartCheckout = "checkout";
    public static final String AStringSet =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*()_-=+{}[]|:;,.?/~ ";

    public static final String AdminConfirmInteraction = "adminconfirm";
    public static final String AdminRequestInteraction = "adminrequest";
    public static final String BestSellersInteraction = "bestsellers";
    public static final String BuyConfirmInteraction = "buyconfirm";
    public static final String BuyRequestInteraction = "buyrequest";
    public static final String HomeInteraction = "home";
    public static final String NewProductsInteraction = "newproducts";
    public static final String OrderDisplayInteraction = "orderdisplay";
    public static final String OrderInquiryInteraction = "orderinquiry";
    public static final String ProductDetailInteraction = "productdetail";
    public static final String SearchRequestInteraction = "searchrequest";
    public static final String SearchResultsInteraction = "searchresults";
    public static final String ShoppingCartInteraction = "shoppingcart";

    /* Other variables... */
    private Jdbc3PoolingDataSource source = new Jdbc3PoolingDataSource();

    private Random random = new Random(0);

    private int items;

    /**
     * Admin Confirm interaction.
     * Clause 2.16
     */
    private void doAdminConfirm(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        /* Data from the request. */
        String c_id = request.getParameter("c_id");
        String sc_id = request.getParameter("sc_id");
        String i_id = request.getParameter("i_id");
        String i_cost = request.getParameter("i_cost");
        String i_image = request.getParameter("i_image");
        String i_thumbnail = request.getParameter("i_thumbnail");
        if (c_id == null) {
            c_id = "0";
        }
        if (sc_id == null) {
            sc_id = "0";
        }
        if (i_id == null) {
            doError(request, response, "No i_id.");
            return;
        }
        if (i_cost == null) {
            doError(request, response, "No i_cost.");
            return;
        }
        if (i_image == null) {
            doError(request, response, "No i_image.");
            return;
        }
        if (i_thumbnail == null) {
            doError(request, response, "No i_thumbnail.");
            return;
        }

        /* Data from the database. */
        String i_title = "";
        String a_fname = "";
        String a_lname = "";
        String i_subject = "";
        String i_desc = "";
        String i_srp = "";
        String i_backing = "";
        String i_page = "";
        String i_publisher = "";
        String i_pub_date = "";
        String i_dimensions = "";
        String i_isbn = "";

        Connection con = null;
        String query = "";
        try {
            con = source.getConnection();
            con.setAutoCommit(false);

            Statement st = con.createStatement();
            st.setFetchSize(1);
            query = "SELECT admin_confirm.* " +
                "FROM admin_confirm ( " + i_id + ", " +
                    i_image + ", " + i_thumbnail + ", " +
                    i_cost + " ) " +
                "AS ( i_image NUMERIC, " +
                "     i_thumbnail NUMERIC, " +
                "     i_cost NUMERIC, " +
                "     i_title VARCHAR, " +
                "     a_fname VARCHAR, " +
                "     a_lname VARCHAR, " +
                "     i_subject VARCHAR, " +
                "     i_desc VARCHAR, " +
                "     i_srp NUMERIC, " +
                "     i_backing VARCHAR, " +
                "     i_page NUMERIC, " +
                "     i_publisher VARCHAR, " +
                "     i_pub_date DATE, " +
                "     i_dimensions VARCHAR, " +
                "     i_isbn CHAR(13) )";
            ResultSet rs = st.executeQuery(query);
            rs.next();
            i_image = rs.getString(1);
            i_thumbnail = rs.getString(2);
            i_cost = rs.getString(3);
            i_title = rs.getString(4);
            a_fname = rs.getString(5);
            a_lname = rs.getString(6);
            i_subject = rs.getString(7);
            i_desc = rs.getString(8);
            i_srp = rs.getString(9);
            i_backing = rs.getString(10);
            i_page = rs.getString(11);
            i_publisher = rs.getString(12);
            i_pub_date = rs.getString(13);
            i_dimensions = rs.getString(14);
            i_isbn = rs.getString(15);
            rs.close();
            st.close();
            con.commit();
            con.close();
         } catch (SQLException e) {
            e.printStackTrace();
            doError(request, response, query);
            return;
         }

	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Admin Confirm Page</title>\n" +
            "<style type=\"text/css\">\n" +
            "h1 { text-align: center }\n" +
            "h2 { text-align: center }\n" +
            "h3 { text-align: center }\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "<h1>OSDL Web Commerce Workload (DBT-1)</h1>\n" +
            "<hr />\n" +
            "<p align=\"center\">\n" +
            "<img src=\"tpclogo.gif\" width=\"288\" height=\"67\" />\n" +
            "</p>" +
            "<h2>Admin Confirm Page</h2>\n" +
            "<h2>Product Updated</h2>\n" +
            "<h2>Title: " + i_title + "</h2>\n" +
            "<p>Author " + a_fname + " " + a_lname + "</p>\n" +
            "<p>Description " + i_desc + "</p>\n" +
            "<img src=\"" + i_image + ".jpg\" width=\"200\" " +
                "height=\"200\" />\n" +
            "<p>\n" +
            "<strong>Suggested Retail:</strong> $ " + i_srp + "<br />\n" +
            "<strong>Our Price:</strong> $ " + i_cost + "<br />\n" +
            "<strong>You Save:</strong> $ " +
                Float.toString(Float.parseFloat(i_srp) -
                    Float.parseFloat(i_cost)) + "\n" +
            "</p>\n" +
            "<dl>\n" +
            "<dt>\n" +
            i_backing + ", " + i_page + " pages<br />\n" +
            "Published by " + i_publisher + "<br />\n" +
            "Publication date: " + i_pub_date + "<br />\n" +
            "Dimensions (in inches): " + i_dimensions + "<br />\n" +
            "ISBN: " + i_isbn + "</dt>\n" +
            "</dt>\n" +
            "</dl>\n" +
            "<p align=\"center\">\n" +
            "<a href=\"" + SearchRequestInteraction + "&sc_id=" +
                sc_id + "&c_id=" + c_id + "\">" +
                "<img src=\"search.gif\" alt=\"Search\" " +
                    "border=\"0\" width=\"120\" height=\"30\" /></a>\n" +
            "<a href=\"" + HomeInteraction + "?sc_id=" + sc_id +
                "&c_id=" + c_id + "\">\n" +
                "<img src=\"home.gif\" alt=\"Home\" border=\"0\" " +
                    "width=\"120\" height=\"30\" /></a>\n" +
            "</p>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     * Admin Request interaction.
     * Clause 2.15
     */
    private void doAdminRequest(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        /* Data from the request. */
        String c_id = request.getParameter("c_id");
        String sc_id = request.getParameter("sc_id");
        String i_id = request.getParameter("i_id");
        if (c_id == null) {
            c_id = "0";
        }
        if (sc_id == null) {
            sc_id = "0";
        }
        if (i_id == null) {
            doError(request, response, "No i_id.");
            return;
        }

        /* Data from the database. */
        String i_srp;
        String i_cost;
        String i_title;
        String i_image;
        String i_thumbnail;
        String a_fname;
        String a_lname;

        Connection con = null;
        String query = "";
        try {
            con = source.getConnection();
            con.setAutoCommit(false);

            Statement st = con.createStatement();
            st.setFetchSize(1);
            query = "SELECT admin_request.* " +
                "FROM admin_request ( " + i_id + " ) " +
                "AS ( i_srp NUMERIC, " +
                "     i_cost NUMERIC, " +
                "     i_title VARCHAR, " +
                "     i_image NUMERIC, " +
                "     i_thumbnail NUMERIC, " +
                "     a_fname VARCHAR, " +
                "     a_lname VARCHAR )";
            ResultSet rs = st.executeQuery(query);
            rs.next();
            i_srp = rs.getString(1);
            i_cost = rs.getString(2);
            i_title = rs.getString(3);
            i_image = rs.getString(4);
            i_thumbnail = rs.getString(5);
            a_fname = rs.getString(6);
            a_lname = rs.getString(7);
            rs.close();
            st.close();
            con.commit();
            con.close();
         } catch (SQLException e) {
            e.printStackTrace();
            doError(request, response, query);
            return;
         }

	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Admin Request Page</title>\n" +
            "<style type=\"text/css\">\n" +
            "h1 { text-align: center }\n" +
            "h2 { text-align: center }\n" +
            "h3 { text-align: center }\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "<h1>OSDL Web Commerce Workload (DBT-1)</h1>\n" +
            "<hr />\n" +
            "<p align=\"center\">\n" +
            "<img src=\"tpclogo.gif\" width=\"288\" " +
                "height=\"67\" />\n" +
            "</p>" +
            "<h2>Admin Request Page</h2>\n" +
            "<h2>Title: " + i_title + "</h2>\n" +
            "<p>Author " + a_fname + " " + a_lname + "</p>\n" +
            "<img src=\"" + i_image + ".jpg\" width=\"200\" " +
                "height=\"200\" />\n" +
            "<img src=\"" + i_thumbnail + ".jpg\" border=\"0\" " +
                "width=\"100\" height=\"150\" />\n" +
            "<form action=\"" + AdminConfirmInteraction +
                "\" method=\"get\">\n" +
            "<input type=\"hidden\" name=\"sc_id\" value=\"" + sc_id +"\">\n" +
            "<input type=\"hidden\" name=\"c_id\" value=\"" + c_id + "\">\n" +
            "<input type=\"hidden\" name=\"i_id\" value=\"" + i_id + "\">\n" +
            "<table border=\"0\">\n" +
            "<tr>\n" +
            "<td><strong>Suggested Retail:</strong></td>\n" +
            "<td><strong>$" + i_srp + "</strong></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td><strong>Our Current Price:</strong></td>\n" +
            "<td><strong>$" + i_cost + "</strong></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td><strong>Enter New Price</strong></td>\n" +
            "<td align=\"right\">$<input type=\"text\" " +
                "name=\"i_cost\"></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td><strong>Enter New Picture</strong></td>\n" +
            "<td align=\"right\"><input type=\"text\" " +
                "name=\"i_image\"></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td><strong>Enter New Thumbnail</strong></td>\n" +
            "<td align=\"right\"><input type=\"text\" " +
                "name=\"i_thumbnail\"></td>\n" +
            "</tr>\n" +
            "</table>\n" +
            "<p align=\"center\">\n" +
            "<input type=\"image\" name=\"Submit Changes\" " +
                "src=\"changes.gif\" border=\"0\" " +
                "height=\"30\" width=\"130\">" +
            "<a href=\"" + SearchRequestInteraction + "&sc_id=" +
                    sc_id + "&c_id=" + c_id + "\">" +
                "<img src=\"search.gif\" alt=\"Search\" " +
                    "border=\"0\" width=\"120\" height=\"30\" /></a>" +
            "<a href=\"" + HomeInteraction + "?sc_id=" + sc_id +
                    "&c_id=" + c_id + "\">" +
                "<img src=\"home.gif\" alt=\"Home\" border=\"0\" " +
                    "width=\"120\" height=\"30\" /></a>\n" +
            "</p>\n" +
            "</form>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     * Best Sellers interaction.
     * Clause 2.13
     */
    private void doBestSellers(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        /* Data from the request. */
        String c_id = request.getParameter("c_id");
        String sc_id = request.getParameter("sc_id");
        String i_subject = request.getParameter("i_subject");

        if (c_id == null) {
            c_id = "0";
        }
        if (sc_id == null) {
            sc_id = "0";
        }
        if (i_subject == null) {
            doError(request, response, "No i_subject.");
            return;
        }

        /* Data from the database. */
        int count = 0;
        String[] pp_i_id = new String[] { "", "", "", "", "" };
        String[] pp_t_id = new String[] { "", "", "", "", "" };
        String[] i_id;
        String[] i_title;
        String[] a_fname;
        String[] a_lname;

        Connection con = null;
        String query = "";
        try {
            con = source.getConnection();
            con.setAutoCommit(false);

            Statement st = con.createStatement();
            st.setFetchSize(1);
            query =
                "SELECT best_sellers.* " +
                "FROM best_sellers ( '" + i_subject +
                    "', "+ Integer.toString(
                    random.nextInt(items) + 1) + " )" +
                " AS (i_related1 NUMERIC, " +
                "     i_related2 NUMERIC, " +
                "     i_related3 NUMERIC, " +
                "     i_related4 NUMERIC, " +
                "     i_related5 NUMERIC, " +
                "     i_thumbnail1 NUMERIC, " +
                "     i_thumbnail2 NUMERIC, " +
                "     i_thumbnail3 NUMERIC, " +
                "     i_thumbnail4 NUMERIC, " +
                "     i_thumbnail5 NUMERIC, " +
                "     items NUMERIC, " +
                "     i_id1 NUMERIC, " +
                "     i_title1 VARCHAR, " +
                "     a_fname1 VARCHAR, " +
                "     a_lname1 VARCHAR, " +
                "     i_id2 NUMERIC, " +
                "     i_title2 VARCHAR, " +
                "     a_fname2 VARCHAR, " +
                "     a_lname2 VARCHAR, " +
                "     i_id3 NUMERIC, " +
                "     i_title3 VARCHAR, " +
                "     a_fname3 VARCHAR, " +
                "     a_lname3 VARCHAR, " +
                "     i_id4 NUMERIC, " +
                "     i_title4 VARCHAR, " +
                "     a_fname4 VARCHAR, " +
                "     a_lname4 VARCHAR, " +
                "     i_id5 NUMERIC, " +
                "     i_title5 VARCHAR, " +
                "     a_fname5 VARCHAR, " +
                "     a_lname5 VARCHAR, " +
                "     i_id6 NUMERIC, " +
                "     i_title6 VARCHAR, " +
                "     a_fname6 VARCHAR, " +
                "     a_lname6 VARCHAR, " +
                "     i_id7 NUMERIC, " +
                "     i_title7 VARCHAR, " +
                "     a_fname7 VARCHAR, " +
                "     a_lname7 VARCHAR, " +
                "     i_id8 NUMERIC, " +
                "     i_title8 VARCHAR, " +
                "     a_fname8 VARCHAR, " +
                "     a_lname8 VARCHAR, " +
                "     i_id9 NUMERIC, " +
                "     i_title9 VARCHAR, " +
                "     a_fname9 VARCHAR, " +
                "     a_lname9 VARCHAR, " +
                "     i_id10 NUMERIC, " +
                "     i_title10 VARCHAR, " +
                "     a_fname10 VARCHAR, " +
                "     a_lname10 VARCHAR, " +
                "     i_id11 NUMERIC, " +
                "     i_title11 VARCHAR, " +
                "     a_fname11 VARCHAR, " +
                "     a_lname11 VARCHAR, " +
                "     i_id12 NUMERIC, " +
                "     i_title12 VARCHAR, " +
                "     a_fname12 VARCHAR, " +
                "     a_lname12 VARCHAR, " +
                "     i_id13 NUMERIC, " +
                "     i_title13 VARCHAR, " +
                "     a_fname13 VARCHAR, " +
                "     a_lname13 VARCHAR, " +
                "     i_id14 NUMERIC, " +
                "     i_title14 VARCHAR, " +
                "     a_fname14 VARCHAR, " +
                "     a_lname14 VARCHAR, " +
                "     i_id15 NUMERIC, " +
                "     i_title15 VARCHAR, " +
                "     a_fname15 VARCHAR, " +
                "     a_lname15 VARCHAR, " +
                "     i_id16 NUMERIC, " +
                "     i_title16 VARCHAR, " +
                "     a_fname16 VARCHAR, " +
                "     a_lname16 VARCHAR, " +
                "     i_id17 NUMERIC, " +
                "     i_title17 VARCHAR, " +
                "     a_fname17 VARCHAR, " +
                "     a_lname17 VARCHAR, " +
                "     i_id18 NUMERIC, " +
                "     i_title18 VARCHAR, " +
                "     a_fname18 VARCHAR, " +
                "     a_lname18 VARCHAR, " +
                "     i_id19 NUMERIC, " +
                "     i_title19 VARCHAR, " +
                "     a_fname19 VARCHAR, " +
                "     a_lname19 VARCHAR, " +
                "     i_id20 NUMERIC, " +
                "     i_title20 VARCHAR, " +
                "     a_fname20 VARCHAR, " +
                "     a_lname20 VARCHAR, " +
                "     i_id21 NUMERIC, " +
                "     i_title21 VARCHAR, " +
                "     a_fname21 VARCHAR, " +
                "     a_lname21 VARCHAR, " +
                "     i_id22 NUMERIC, " +
                "     i_title22 VARCHAR, " +
                "     a_fname22 VARCHAR, " +
                "     a_lname22 VARCHAR, " +
                "     i_id23 NUMERIC, " +
                "     i_title23 VARCHAR, " +
                "     a_fname23 VARCHAR, " +
                "     a_lname23 VARCHAR, " +
                "     i_id24 NUMERIC, " +
                "     i_title24 VARCHAR, " +
                "     a_fname24 VARCHAR, " +
                "     a_lname24 VARCHAR, " +
                "     i_id25 NUMERIC, " +
                "     i_title25 VARCHAR, " +
                "     a_fname25 VARCHAR, " +
                "     a_lname25 VARCHAR, " +
                "     i_id26 NUMERIC, " +
                "     i_title26 VARCHAR, " +
                "     a_fname26 VARCHAR, " +
                "     a_lname26 VARCHAR, " +
                "     i_id27 NUMERIC, " +
                "     i_title27 VARCHAR, " +
                "     a_fname27 VARCHAR, " +
                "     a_lname27 VARCHAR, " +
                "     i_id28 NUMERIC, " +
                "     i_title28 VARCHAR, " +
                "     a_fname28 VARCHAR, " +
                "     a_lname28 VARCHAR, " +
                "     i_id29 NUMERIC, " +
                "     i_title29 VARCHAR, " +
                "     a_fname29 VARCHAR, " +
                "     a_lname29 VARCHAR, " +
                "     i_id30 NUMERIC, " +
                "     i_title30 VARCHAR, " +
                "     a_fname30 VARCHAR, " +
                "     a_lname30 VARCHAR, " +
                "     i_id31 NUMERIC, " +
                "     i_title31 VARCHAR, " +
                "     a_fname31 VARCHAR, " +
                "     a_lname31 VARCHAR, " +
                "     i_id32 NUMERIC, " +
                "     i_title32 VARCHAR, " +
                "     a_fname32 VARCHAR, " +
                "     a_lname32 VARCHAR, " +
                "     i_id33 NUMERIC, " +
                "     i_title33 VARCHAR, " +
                "     a_fname33 VARCHAR, " +
                "     a_lname33 VARCHAR, " +
                "     i_id34 NUMERIC, " +
                "     i_title34 VARCHAR, " +
                "     a_fname34 VARCHAR, " +
                "     a_lname34 VARCHAR, " +
                "     i_id35 NUMERIC, " +
                "     i_title35 VARCHAR, " +
                "     a_fname35 VARCHAR, " +
                "     a_lname35 VARCHAR, " +
                "     i_id36 NUMERIC, " +
                "     i_title36 VARCHAR, " +
                "     a_fname36 VARCHAR, " +
                "     a_lname36 VARCHAR, " +
                "     i_id37 NUMERIC, " +
                "     i_title37 VARCHAR, " +
                "     a_fname37 VARCHAR, " +
                "     a_lname37 VARCHAR, " +
                "     i_id38 NUMERIC, " +
                "     i_title38 VARCHAR, " +
                "     a_fname38 VARCHAR, " +
                "     a_lname38 VARCHAR, " +
                "     i_id39 NUMERIC, " +
                "     i_title39 VARCHAR, " +
                "     a_fname39 VARCHAR, " +
                "     a_lname39 VARCHAR, " +
                "     i_id40 NUMERIC, " +
                "     i_title40 VARCHAR, " +
                "     a_fname40 VARCHAR, " +
                "     a_lname40 VARCHAR, " +
                "     i_id41 NUMERIC, " +
                "     i_title41 VARCHAR, " +
                "     a_fname41 VARCHAR, " +
                "     a_lname41 VARCHAR, " +
                "     i_id42 NUMERIC, " +
                "     i_title42 VARCHAR, " +
                "     a_fname42 VARCHAR, " +
                "     a_lname42 VARCHAR, " +
                "     i_id43 NUMERIC, " +
                "     i_title43 VARCHAR, " +
                "     a_fname43 VARCHAR, " +
                "     a_lname43 VARCHAR, " +
                "     i_id44 NUMERIC, " +
                "     i_title44 VARCHAR, " +
                "     a_fname44 VARCHAR, " +
                "     a_lname44 VARCHAR, " +
                "     i_id45 NUMERIC, " +
                "     i_title45 VARCHAR, " +
                "     a_fname45 VARCHAR, " +
                "     a_lname45 VARCHAR, " +
                "     i_id46 NUMERIC, " +
                "     i_title46 VARCHAR, " +
                "     a_fname46 VARCHAR, " +
                "     a_lname46 VARCHAR, " +
                "     i_id47 NUMERIC, " +
                "     i_title47 VARCHAR, " +
                "     a_fname47 VARCHAR, " +
                "     a_lname47 VARCHAR, " +
                "     i_id48 NUMERIC, " +
                "     i_title48 VARCHAR, " +
                "     a_fname48 VARCHAR, " +
                "     a_lname48 VARCHAR, " +
                "     i_id49 NUMERIC, " +
                "     i_title49 VARCHAR, " +
                "     a_fname49 VARCHAR, " +
                "     a_lname49 VARCHAR, " +
                "     i_id50 NUMERIC, " +
                "     i_title50 VARCHAR, " +
                "     a_fname50 VARCHAR, " +
                "     a_lname50 VARCHAR )";
            ResultSet rs = st.executeQuery(query);
            rs.next();
            for (int i = 0, j = 1; i < 5; i++) {
                pp_i_id[i] = rs.getString(j++);
                pp_t_id[i] = rs.getString(j++);
            }
            count = rs.getInt(11);
            i_id = new String[count];
            i_title = new String[count];
            a_fname = new String[count];
            a_lname = new String[count];
            for (int i = 0, j = 12; i < count; i++) {
                i_id[i] = rs.getString(j++);
                i_title[i] = rs.getString(j++);
                a_fname[i] = rs.getString(j++);
                a_lname[i] = rs.getString(j++);
            }
            rs.close();
            st.close();
            con.commit();
            con.close();
         } catch (SQLException e) {
            e.printStackTrace();
            doError(request, response, query);
            return;
         }

	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Best Sellers Page: Subject: " +
                i_subject + "</title>\n" +
            "<style type=\"text/css\">\n" +
            "h1 { text-align: center }\n" +
            "h2 { text-align: center }\n" +
            "h3 { text-align: center }\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "<h1>OSDL Web Commerce Workload (DBT-1)</h1>\n" +
            "<hr />\n" +
            "<p align=\"center\">\n" +
            "<img src=\"tpclogo.gif\" align=\"bottom\" " +
                "border=\"0\" width=\"288\" height=\"67\">\n " +
            "</p>\n" +
            "<h2>Best Sellers Page</h2>\n";
        html += getPromotionalProcessing(c_id, sc_id, pp_i_id, pp_t_id);
        html +=
            "<table border=\"1\" cellpadding=\"1\" " + "cellspacing=\"1\">\n" +
            "<tr>\n" +
            "<th>Author</th>\n" +
            "<th>Title</th>\n" +
            "</tr>\n";
        for (int i = 0; i < count; i++) {
            html +=
                "<tr>\n" +
                "<td><em>" + a_fname[i] + " " + a_lname[i] + "</em></td>\n" +
                "<td><a href=\"" + ProductDetailInteraction +
                    "?i_id=" + i_id[i] + "&sc_id=" + sc_id +
                    "&c_id=" + c_id + "\">" + i_title[i] + "</a></td>\n" +
                "</tr>\n";
        }
        html +=
            "</table>\n" +
            "<p align=\"center\">\n" +
            "<a href=\"" + ShoppingCartInteraction +
                "?add_flag=n&sc_id=" + sc_id + "&c_id=" + c_id + "\">" +
            "<img alt=\"Shopping Cart\" border=\"0\" " +
            "height=\"30\" src=\"cart.gif\" width=\"120\">" +
            "</a><a href=\"" + SearchRequestInteraction +
                "?sc_id=" + sc_id + "&c_id=" + c_id +"\">" +
            "<img alt=\"Search\" border=\"0\" height=\"30\" " +
                "src=\"search.gif\" width=\"120\"></a>" +
            "<a href=\"" + HomeInteraction + "?sc_id=" + sc_id +
                "&c_id=" + c_id + "\">" +
            "<img alt=\"Home\" border=\"0\" height=\"30\" " +
                "src=\"home.gif\" width=\"120\"></a></p>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     * Buy Confirm interaction.
     * Clause 2.7
     */
    public void doBuyConfirm(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        /* Data from the request. */
        String c_id = request.getParameter("c_id");
        String sc_id = request.getParameter("sc_id");
        String cx_type = request.getParameter("cx_type");
        String cx_num = request.getParameter("cx_num");
        String cx_name = request.getParameter("cx_name");
        String cx_expiry = request.getParameter("cx_expiry");
        String addr_street1 = request.getParameter("addr_street1");
        String addr_street2 = request.getParameter("addr_street2");
        String addr_city = request.getParameter("addr_city");
        String addr_state = request.getParameter("addr_state");
        String addr_zip = request.getParameter("addr_zip");
        String co_name = request.getParameter("co_name");

        /* Randomly generated data. */
        String ol_comment = getAString(20, 100);
        String days = Integer.toString(random.nextInt(7) + 1);
        String cx_auth_id = "";

        /* Data from the database. */
        int count = 0;
        String c_discount = "0";
        String sc_sub_total = "0";
        String sc_tax = "0";
        String sc_ship_cost = "0";
        String sc_total = "0";
        String[] scl_i_id;
        String[] scl_title;
        String[] scl_cost;
        String[] scl_srp;
        String[] scl_backing;
        String[] scl_qty;
        String o_id;

        /* Simulate the 2 second credit card authorization. */
        try {
            cx_auth_id = "123456789012345";
            Thread.sleep(2000, 1);
        } catch (InterruptedException e) {
            e.printStackTrace();
            doError(request, response, "Sleep failed.");
            return;
        }

        Connection con = null;
        String query = "";
        try {
            con = source.getConnection();
            con.setAutoCommit(false);

            Statement st = con.createStatement();
            st.setFetchSize(1);
            query = "SELECT buy_confirm.* " +
                "FROM buy_confirm ( '" + cx_type + "', " +
                "                   " + cx_num + ", " +
                "                   '" + cx_name + "', " +
                "                   '" + cx_expiry + "', " +
                "                   " + sc_id + ", " +
                "                   " + c_id + ", " +
                "                   " + days + ", " +
                "                   '" + ol_comment + "', " +
                "                   '" + cx_auth_id + "', " +
                "                   '" + addr_street1 + "', " +
                "                   '" + addr_street2 + "', " +
                "                   '" + addr_city + "', " +
                "                   '" + addr_state + "', " +
                "                   '" + addr_zip + "', " +
                "                   '" + co_name + "') " +
                "AS ( c_discount NUMERIC, " +
                "     sc_sub_total NUMERIC, " +
                "     sc_tax NUMERIC, " +
                "     sc_ship_cost NUMERIC, " +
                "     sc_total NUMERIC, " +
                "     count NUMERIC, " +
                "     scl_i_id1 NUMERIC, " +
                "     scl_title1 VARCHAR, " +
                "     scl_cost1 NUMERIC, " +
                "     scl_srp1 NUMERIC, " +
                "     scl_backing1 VARCHAR, " +
                "     scl_qty1 NUMERIC, " +
                "     scl_i_id2 NUMERIC, " +
                "     scl_title2 VARCHAR, " +
                "     scl_cost2 NUMERIC, " +
                "     scl_srp2 NUMERIC, " +
                "     scl_backing2 VARCHAR, " +
                "     scl_qty2 NUMERIC, " +
                "     scl_i_id3 NUMERIC, " +
                "     scl_title3 VARCHAR, " +
                "     scl_cost3 NUMERIC, " +
                "     scl_srp3 NUMERIC, " +
                "     scl_backing3 VARCHAR, " +
                "     scl_qty3 NUMERIC, " +
                "     scl_i_id4 NUMERIC, " +
                "     scl_title4 VARCHAR, " +
                "     scl_cost4 NUMERIC, " +
                "     scl_srp4 NUMERIC, " +
                "     scl_backing4 VARCHAR, " +
                "     scl_qty4 NUMERIC, " +
                "     scl_i_id5 NUMERIC, " +
                "     scl_title5 VARCHAR, " +
                "     scl_cost5 NUMERIC, " +
                "     scl_srp5 NUMERIC, " +
                "     scl_backing5 VARCHAR, " +
                "     scl_qty5 NUMERIC, " +
                "     scl_i_id6 NUMERIC, " +
                "     scl_title6 VARCHAR, " +
                "     scl_cost6 NUMERIC, " +
                "     scl_srp6 NUMERIC, " +
                "     scl_backing6 VARCHAR, " +
                "     scl_qty6 NUMERIC, " +
                "     scl_i_id7 NUMERIC, " +
                "     scl_title7 VARCHAR, " +
                "     scl_cost7 NUMERIC, " +
                "     scl_srp7 NUMERIC, " +
                "     scl_backing7 VARCHAR, " +
                "     scl_qty7 NUMERIC, " +
                "     scl_i_id8 NUMERIC, " +
                "     scl_title8 VARCHAR, " +
                "     scl_cost8 NUMERIC, " +
                "     scl_srp8 NUMERIC, " +
                "     scl_backing8 VARCHAR, " +
                "     scl_qty8 NUMERIC, " +
                "     scl_i_id9 NUMERIC, " +
                "     scl_title9 VARCHAR, " +
                "     scl_cost9 NUMERIC, " +
                "     scl_srp9 NUMERIC, " +
                "     scl_backing9 VARCHAR, " +
                "     scl_qty9 NUMERIC, " +
                "     scl_i_id10 NUMERIC, " +
                "     scl_title10 VARCHAR, " +
                "     scl_cost10 NUMERIC, " +
                "     scl_srp10 NUMERIC, " +
                "     scl_backing10 VARCHAR, " +
                "     scl_qty10 NUMERIC, " +
                "     scl_i_id11 NUMERIC, " +
                "     scl_title11 VARCHAR, " +
                "     scl_cost11 NUMERIC, " +
                "     scl_srp11 NUMERIC, " +
                "     scl_backing11 VARCHAR, " +
                "     scl_qty11 NUMERIC, " +
                "     scl_i_id12 NUMERIC, " +
                "     scl_title12 VARCHAR, " +
                "     scl_cost12 NUMERIC, " +
                "     scl_srp12 NUMERIC, " +
                "     scl_backing12 VARCHAR, " +
                "     scl_qty12 NUMERIC, " +
                "     scl_i_id13 NUMERIC, " +
                "     scl_title13 VARCHAR, " +
                "     scl_cost13 NUMERIC, " +
                "     scl_srp13 NUMERIC, " +
                "     scl_backing13 VARCHAR, " +
                "     scl_qty13 NUMERIC, " +
                "     scl_i_id14 NUMERIC, " +
                "     scl_title14 VARCHAR, " +
                "     scl_cost14 NUMERIC, " +
                "     scl_srp14 NUMERIC, " +
                "     scl_backing14 VARCHAR, " +
                "     scl_qty14 NUMERIC, " +
                "     scl_i_id15 NUMERIC, " +
                "     scl_title15 VARCHAR, " +
                "     scl_cost15 NUMERIC, " +
                "     scl_srp15 NUMERIC, " +
                "     scl_backing15 VARCHAR, " +
                "     scl_qty15 NUMERIC, " +
                "     scl_i_id16 NUMERIC, " +
                "     scl_title16 VARCHAR, " +
                "     scl_cost16 NUMERIC, " +
                "     scl_srp16 NUMERIC, " +
                "     scl_backing16 VARCHAR, " +
                "     scl_qty16 NUMERIC, " +
                "     scl_i_id17 NUMERIC, " +
                "     scl_title17 VARCHAR, " +
                "     scl_cost17 NUMERIC, " +
                "     scl_srp17 NUMERIC, " +
                "     scl_backing17 VARCHAR, " +
                "     scl_qty17 NUMERIC, " +
                "     scl_i_id18 NUMERIC, " +
                "     scl_title18 VARCHAR, " +
                "     scl_cost18 NUMERIC, " +
                "     scl_srp18 NUMERIC, " +
                "     scl_backing18 VARCHAR, " +
                "     scl_qty18 NUMERIC, " +
                "     scl_i_id19 NUMERIC, " +
                "     scl_title19 VARCHAR, " +
                "     scl_cost19 NUMERIC, " +
                "     scl_srp19 NUMERIC, " +
                "     scl_backing19 VARCHAR, " +
                "     scl_qty19 NUMERIC, " +
                "     scl_i_id20 NUMERIC, " +
                "     scl_title20 VARCHAR, " +
                "     scl_cost20 NUMERIC, " +
                "     scl_srp20 NUMERIC, " +
                "     scl_backing20 VARCHAR, " +
                "     scl_qty20 NUMERIC )";
            ResultSet rs = st.executeQuery(query);
            rs.next();
            c_discount = rs.getString(1);
            sc_sub_total = rs.getString(2);
            sc_tax = rs.getString(3);
            sc_ship_cost = rs.getString(4);
            sc_total = rs.getString(5);
            count = rs.getInt(6);
            scl_i_id = new String[count];
            scl_title = new String[count];
            scl_cost = new String[count];
            scl_srp = new String[count];
            scl_backing = new String[count];
            scl_qty = new String[count];
            for (int i = 0, j = 7; i < count; i++) {
                scl_i_id[i] = rs.getString(j++);
                scl_title[i] = rs.getString(j++);
                scl_cost[i] = rs.getString(j++);
                scl_srp[i] = rs.getString(j++);
                scl_backing[i] = rs.getString(j++);
                scl_qty[i] = rs.getString(j++);
            }
            rs.close();
            st.close();
            con.commit();
            con.close();
         } catch (SQLException e) {
            e.printStackTrace();
            doError(request, response, query);
            return;
        }
        o_id = sc_id;
        sc_id = "0";

	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Buy Confirm Page</title>\n" +
            "<style type=\"text/css\">\n" +
            "h1 { text-align: center }\n" +
            "h2 { text-align: center }\n" +
            "h3 { text-align: center }\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "<h1>OSDL Web Commerce Workload (DBT-1)</h1>\n" +
            "<hr />\n" +
            "<h2>Buy Confirm Page</h2>" +
            "<strong>Order Information:</strong>" +
            "<table>\n" +
            "<tr>\n" +
            "<th>Qty</th><th>Product</th>\n" +
            "</tr>\n";
        for (int i = 0; i < count; i++) {
            html +=
                "<tr>\n" +
                "<td valign=\"top\">" + scl_qty[i] + "</td>\n" +
                "<td valign=\"top\">Title: " +
                "<em>" + scl_title[i] + "</em> Backing: " +
                    scl_backing[i] + "<br />\n" +
                "SRP: $" + scl_srp[i] +", <strong>Your " +
                    "Price: $" + scl_cost[i] + "</strong>\n" +
                "</td>\n" +
                "</tr>\n";
        }
        html +=
            "</table>\n" +
            "<p>\n" +
            "<strong>Your order has been processed.</strong>\n " +
            "</p>\n" +
            "<table border=\"1\">\n" +
            "<tr>\n" +
            "<td><strong>Subtotal with discount (" +
                Float.toString(Float.parseFloat(c_discount) * 100) +
                "%):</strong></td>" +
            "<td><strong>$" + sc_sub_total + "</strong></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td><strong>Tax (8.25%)</strong></td>\n" +
            "<td><strong>$" + sc_tax + "</strong></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td><strong>Total:</strong></td>\n" +
            "<td><strong>$" + sc_total + "</strong></td>\n" +
            "</tr>\n" +
            "</table>\n" +
            "<p>\n" +
            "Order Number: " + o_id + "<br />\n" +
            "Thanks you for shopping at OSDL DBT-1!\n" +
            "</p>\n" +
            "<p align=\"center\">\n" +
            "<a href=\"" + SearchRequestInteraction +
                "?sc_id=" + sc_id + "&c_id=" + c_id +"\">" +
            "<img alt=\"Search\" border=\"0\" height=\"30\" " +
                "src=\"search.gif\" width=\"120\"></a>" +
            "<a href=\"" + HomeInteraction + "?sc_id=" + sc_id +
                "&c_id=" + c_id + "\">" +
            "<img alt=\"Home\" border=\"0\" height=\"30\" " +
                "src=\"home.gif\" width=\"120\"></a>\n" +
            "</p>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     * Buy Request interaction.
     * Clause 2.6
     */
    public void doBuyRequest(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        /* Data from the request. */
        String c_id = request.getParameter("c_id");
        String sc_id = request.getParameter("sc_id");
        String c_uname = request.getParameter("c_uname");
        String c_discount = request.getParameter("c_discount");
        String c_fname = request.getParameter("c_fname");
        String c_lname = request.getParameter("c_lname");
        String addr_street1 = request.getParameter("addr_street1");
        String addr_street2 = request.getParameter("addr_street2");
        String addr_city = request.getParameter("addr_city");
        String addr_state = request.getParameter("addr_state");
        String addr_zip = request.getParameter("addr_zip");
        String co_name = request.getParameter("co_name");
        String c_phone = request.getParameter("c_phone");
        String c_email = request.getParameter("c_email");
        String c_birthday = request.getParameter("c_birthdate");
        String c_data = request.getParameter("c_data");
        String returning = request.getParameter("returning");
        if (c_id == null) {
            c_id = "0";
        }
        if (sc_id == null) {
            sc_id = "0";
        }
        if (c_uname == null) {
            c_uname = "";
        }
        if (c_discount == null) {
            c_discount = "0";
        }
        if (c_fname == null) {
            c_fname = "";
        }
        if (c_lname == null) {
            c_lname = "";
        }
        if (addr_street1 == null) {
            addr_street1 = "";
        }
        if (addr_street2 == null) {
            addr_street2 = "";
        }
        if (addr_city == null) {
            addr_city = "";
        }
        if (addr_state == null) {
            addr_state = "";
        }
        if (addr_zip == null) {
            addr_zip = "";
        }
        if (co_name == null) {
            co_name = "";
        }
        if (c_phone == null) {
            c_phone = "";
        }
        if (c_email == null) {
            c_email = "";
        }
        if (c_birthday == null) {
            c_birthday = "";
        }
        if (c_data == null) {
            c_data = "";
        }
        if (returning == null) {
            doError(request, response, "No returning.");
            return;
        }
        if (returning.equals("y")) {
            returning = "1";
        } else if (returning.equals("n")) {
            returning = "0";
        } else {
            doError(request, response, "returning: " + returning);
            return;
        }

        /* Data from the database. */
        int count = 0;
        String c_passwd;
        String sc_sub_total = "0";
        String sc_tax = "0";
        String sc_ship_cost = "0";
        String sc_total = "0";
        String[] scl_i_id;
        String[] scl_title;
        String[] scl_cost;
        String[] scl_srp;
        String[] scl_backing;
        String[] scl_qty;

        Connection con = null;
        String query = "";
        try {
            con = source.getConnection();
            con.setAutoCommit(false);

            Statement st = con.createStatement();
            st.setFetchSize(1);
            query = "SELECT buy_request.* " +
                "FROM buy_request ( " + returning + ", " +
                "                   '" + c_uname + "', " +
                "                   " + sc_id + ", " +
                "                   " + c_discount + ", " +
                "                   '" + c_fname + "', " +
                "                   '" + c_lname + "', " +
                "                   '" + addr_street1 + "', " +
                "                   '" + addr_street2 + "', " +
                "                   '" + addr_city + "', " +
                "                   '" + addr_state + "', " +
                "                   '" + addr_zip + "', " +
                "                   '" + co_name + "', " +
                "                   '" + c_phone + "', " +
                "                   '" + c_email + "', " +
                "                   '" + c_birthday + "', " +
                "                   '" + c_data + "' ) " +
                "AS ( c_discount NUMERIC, " +
                "     c_fname VARCHAR, " +
                "     c_lname VARCHAR, " +
                "     addr_street1 VARCHAR, " +
                "     addr_street2 VARCHAR, " +
                "     addr_city VARCHAR, " +
                "     addr_state VARCHAR, " +
                "     addr_zip VARCHAR, " +
                "     co_name VARCHAR, " +
                "     c_phone VARCHAR, " +
                "     c_email VARCHAR, " +
                "     c_birthday CHAR, " +
                "     c_data VARCHAR, " +
                "     c_passwd VARCHAR, " +
                "     c_id NUMERIC, " +
                "     sc_sub_total NUMERIC, " +
                "     sc_tax NUMERIC, " +
                "     sc_ship_cost NUMERIC, " +
                "     sc_total NUMERIC, " +
                "     count NUMERIC, " +
                "     scl_i_id1 NUMERIC, " +
                "     scl_title1 VARCHAR, " +
                "     scl_cost1 NUMERIC, " +
                "     scl_srp1 NUMERIC, " +
                "     scl_backing1 VARCHAR, " +
                "     scl_qty1 NUMERIC, " +
                "     scl_i_id2 NUMERIC, " +
                "     scl_title2 VARCHAR, " +
                "     scl_cost2 NUMERIC, " +
                "     scl_srp2 NUMERIC, " +
                "     scl_backing2 VARCHAR, " +
                "     scl_qty2 NUMERIC, " +
                "     scl_i_id3 NUMERIC, " +
                "     scl_title3 VARCHAR, " +
                "     scl_cost3 NUMERIC, " +
                "     scl_srp3 NUMERIC, " +
                "     scl_backing3 VARCHAR, " +
                "     scl_qty3 NUMERIC, " +
                "     scl_i_id4 NUMERIC, " +
                "     scl_title4 VARCHAR, " +
                "     scl_cost4 NUMERIC, " +
                "     scl_srp4 NUMERIC, " +
                "     scl_backing4 VARCHAR, " +
                "     scl_qty4 NUMERIC, " +
                "     scl_i_id5 NUMERIC, " +
                "     scl_title5 VARCHAR, " +
                "     scl_cost5 NUMERIC, " +
                "     scl_srp5 NUMERIC, " +
                "     scl_backing5 VARCHAR, " +
                "     scl_qty5 NUMERIC, " +
                "     scl_i_id6 NUMERIC, " +
                "     scl_title6 VARCHAR, " +
                "     scl_cost6 NUMERIC, " +
                "     scl_srp6 NUMERIC, " +
                "     scl_backing6 VARCHAR, " +
                "     scl_qty6 NUMERIC, " +
                "     scl_i_id7 NUMERIC, " +
                "     scl_title7 VARCHAR, " +
                "     scl_cost7 NUMERIC, " +
                "     scl_srp7 NUMERIC, " +
                "     scl_backing7 VARCHAR, " +
                "     scl_qty7 NUMERIC, " +
                "     scl_i_id8 NUMERIC, " +
                "     scl_title8 VARCHAR, " +
                "     scl_cost8 NUMERIC, " +
                "     scl_srp8 NUMERIC, " +
                "     scl_backing8 VARCHAR, " +
                "     scl_qty8 NUMERIC, " +
                "     scl_i_id9 NUMERIC, " +
                "     scl_title9 VARCHAR, " +
                "     scl_cost9 NUMERIC, " +
                "     scl_srp9 NUMERIC, " +
                "     scl_backing9 VARCHAR, " +
                "     scl_qty9 NUMERIC, " +
                "     scl_i_id10 NUMERIC, " +
                "     scl_title10 VARCHAR, " +
                "     scl_cost10 NUMERIC, " +
                "     scl_srp10 NUMERIC, " +
                "     scl_backing10 VARCHAR, " +
                "     scl_qty10 NUMERIC, " +
                "     scl_i_id11 NUMERIC, " +
                "     scl_title11 VARCHAR, " +
                "     scl_cost11 NUMERIC, " +
                "     scl_srp11 NUMERIC, " +
                "     scl_backing11 VARCHAR, " +
                "     scl_qty11 NUMERIC, " +
                "     scl_i_id12 NUMERIC, " +
                "     scl_title12 VARCHAR, " +
                "     scl_cost12 NUMERIC, " +
                "     scl_srp12 NUMERIC, " +
                "     scl_backing12 VARCHAR, " +
                "     scl_qty12 NUMERIC, " +
                "     scl_i_id13 NUMERIC, " +
                "     scl_title13 VARCHAR, " +
                "     scl_cost13 NUMERIC, " +
                "     scl_srp13 NUMERIC, " +
                "     scl_backing13 VARCHAR, " +
                "     scl_qty13 NUMERIC, " +
                "     scl_i_id14 NUMERIC, " +
                "     scl_title14 VARCHAR, " +
                "     scl_cost14 NUMERIC, " +
                "     scl_srp14 NUMERIC, " +
                "     scl_backing14 VARCHAR, " +
                "     scl_qty14 NUMERIC, " +
                "     scl_i_id15 NUMERIC, " +
                "     scl_title15 VARCHAR, " +
                "     scl_cost15 NUMERIC, " +
                "     scl_srp15 NUMERIC, " +
                "     scl_backing15 VARCHAR, " +
                "     scl_qty15 NUMERIC, " +
                "     scl_i_id16 NUMERIC, " +
                "     scl_title16 VARCHAR, " +
                "     scl_cost16 NUMERIC, " +
                "     scl_srp16 NUMERIC, " +
                "     scl_backing16 VARCHAR, " +
                "     scl_qty16 NUMERIC, " +
                "     scl_i_id17 NUMERIC, " +
                "     scl_title17 VARCHAR, " +
                "     scl_cost17 NUMERIC, " +
                "     scl_srp17 NUMERIC, " +
                "     scl_backing17 VARCHAR, " +
                "     scl_qty17 NUMERIC, " +
                "     scl_i_id18 NUMERIC, " +
                "     scl_title18 VARCHAR, " +
                "     scl_cost18 NUMERIC, " +
                "     scl_srp18 NUMERIC, " +
                "     scl_backing18 VARCHAR, " +
                "     scl_qty18 NUMERIC, " +
                "     scl_i_id19 NUMERIC, " +
                "     scl_title19 VARCHAR, " +
                "     scl_cost19 NUMERIC, " +
                "     scl_srp19 NUMERIC, " +
                "     scl_backing19 VARCHAR, " +
                "     scl_qty19 NUMERIC, " +
                "     scl_i_id20 NUMERIC, " +
                "     scl_title20 VARCHAR, " +
                "     scl_cost20 NUMERIC, " +
                "     scl_srp20 NUMERIC, " +
                "     scl_backing20 VARCHAR, " +
                "     scl_qty20 NUMERIC )";
            ResultSet rs = st.executeQuery(query);
            rs.next();
            c_discount = rs.getString(1);
            c_fname = rs.getString(2);
            c_lname = rs.getString(3);
            addr_street1 = rs.getString(4);
            addr_street2 = rs.getString(5);
            addr_city = rs.getString(6);
            addr_state = rs.getString(7);
            addr_zip = rs.getString(8);
            co_name = rs.getString(9);
            c_phone = rs.getString(10);
            c_email = rs.getString(11);
            c_birthday = rs.getString(12);
            c_data = rs.getString(13);
            c_passwd = rs.getString(14);
            c_id = rs.getString(15);
            sc_sub_total = rs.getString(16);
            sc_tax = rs.getString(17);
            sc_ship_cost = rs.getString(18);
            sc_total = rs.getString(19);
            count = rs.getInt(20);
            scl_i_id = new String[count];
            scl_title = new String[count];
            scl_cost = new String[count];
            scl_srp = new String[count];
            scl_backing = new String[count];
            scl_qty = new String[count];
            for (int i = 0, j = 21; i < count; i++) {
                scl_i_id[i] = rs.getString(j++);
                scl_title[i] = rs.getString(j++);
                scl_cost[i] = rs.getString(j++);
                scl_srp[i] = rs.getString(j++);
                scl_backing[i] = rs.getString(j++);
                scl_qty[i] = rs.getString(j++);
            }
            rs.close();
            st.close();
            con.commit();
            con.close();
         } catch (SQLException e) {
            e.printStackTrace();
            doError(request, response, query);
            return;
         }

	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Buy Request Page</title>\n" +
            "<style type=\"text/css\">\n" +
            "h1 { text-align: center }\n" +
            "h2 { text-align: center }\n" +
            "h3 { text-align: center }\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "<h1>OSDL Web Commerce Workload (DBT-1)</h1>\n" +
            "<hr />\n" +
            "<h2>Buy Request Page</h2>" +
            "<hr />\n" +
            "<form action=\"" + BuyConfirmInteraction + "\" method=\"get\">\n" +
            "<input type=\"hidden\" name=\"sc_id\" value=\"" + sc_id +"\">\n" +
            "<input type=\"hidden\" name=\"c_id\" value=\"" + c_id + "\">\n" +
            "<table border=\"0\" width=\"90%\">\n" +
            "<tr>\n" +
            "<td valign=\"top\">\n" +
            "<strong>Billing Information:</strong>\n" +
            "<table border=\"0\" width=\"100%\">\n" +
            "<tr>\n" +
            "<td>First name:</td>\n" +
            "<td>" + c_fname + "</td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Last name:</td>\n" +
            "<td>" + c_lname + "</td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Street 1:</td>\n" +
            "<td>" + addr_street1 + "</td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Street 2:</td>\n" +
            "<td>" + addr_street2 + "</td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>City:</td>\n" +
            "<td>" + addr_city + "</td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>State:</td>\n" +
            "<td>" + addr_state + "</td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Zip:</td>\n" +
            "<td>" + addr_zip + "</td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Country:</td>\n" +
            "<td>" + co_name + "</td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Email:</td>\n" +
            "<td>" + c_email + "</td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Phone:</td>\n" +
            "<td>" + c_phone + "</td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Username:</td>\n" +
            "<td>" + c_uname + "</td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>C_ID:</td>\n" +
            "<td>" + c_id + "</td>\n" +
            "</tr>\n" +
            "</table>\n" +
            "</td>\n" +
            "<td valign=\"top\">\n" +
            "<strong>Shipping Information:</strong>\n" +
            "<table border=\"0\" width=\"100%\">\n" +
            "<tr>\n" +
            "<td>Street 1:</td>\n" +
            "<td><input name=\"addr_street1\" size=\"40\" /></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Street 2:</td>\n" +
            "<td><input name=\"addr_street2\" size=\"40\" /></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>City:</td>\n" +
            "<td><input name=\"addr_city\" size=\"30\" /></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>State:</td>\n" +
            "<td><input name=\"addr_state\" size=\"20\" /></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Zip:</td>\n" +
            "<td><input name=\"addr_zip\" size=\"10\" /></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Country:</td>\n" +
            "<td><input name=\"co_name\" size=\"40\" /></td>\n" +
            "</tr>\n" +
            "</table>\n" +
            "</td>\n" +
            "</tr>\n" +
            "</table>\n" +
            "<hr />\n" +
            "<h2>Order Information</h2>\n" +
            "<table border=\"1\">\n" +
            "<tr>\n" +
            "<th>Qty</th><th>Product</th>\n" +
            "</tr>\n";
        for (int i = 0; i < count; i++) {
            html +=
                "<tr>\n" +
                "<td valign=\"top\">" + scl_qty[i] + "</td>\n" +
                "<td valign=\"top\">Title: " +
                "<em>" + scl_title[i] + "</em> Backing: " +
                    scl_backing[i] + "<br />\n" +
                "SRP: $" + scl_srp[i] +", <strong>Your " +
                    "Price: $" + scl_cost[i] + "</strong>\n" +
                "</td>\n" +
                "</tr>\n";
        }
        html +=
            "</table>\n" +
            "<table border=\"0\">\n" +
            "<tr>\n" +
            "<td><strong>Subtotal with discount " +
                "(" + Float.toString(Float.parseFloat(
                    c_discount) * 100) + "%):</strong></td>\n" +
            "<td align=\"right\"><strong>$" + sc_sub_total +
                "</strong></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td><strong>Tax:</strong></td>\n" +
            "<td align=\"right\"><strong>$" + sc_tax + "</strong></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td><strong>Shipping &amp; Handling:</strong></td>\n" +
            "<td align=\"right\"><strong>$" + sc_ship_cost +
                "</strong></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td><strong>Total</strong></td>\n" +
            "<td align=\"right\"><strong>$" + sc_total + "</strong></td>\n" +
            "</tr>\n" +
            "</table>\n" +
            "<hr />\n" +
            "<table>\n" +
            "<tr>\n" +
            "<td>Credit Card Type:</td>\n" +
            "<td>" +
            "<input type=\"radio\" name=\"cx_type\" value=\"VISA\" " +
                "checked>VISA</input>\n" +
            "<input type=\"radio\" name=\"cx_type\" " +
                "value=\"MASTERCARD\">MASTERCARD</input>\n" +
            "<input type=\"radio\" name=\"cx_type\" " +
                "value=\"DISCOVER\">DISCOVER</input>\n" +
            "<input type=\"radio\" name=\"cx_type\" " +
                "value=\"AMEX\">AMERICAN EXPRESS</input>\n" +
            "<input type=\"radio\" name=\"cx_type\" " +
                "value=\"DINERS\">DINERS</input>\n" +
            "</td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Name of Credit Card:</td>\n" +
            "<td><input name=\"cx_name\" size=\"30\" /></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Credit Card Number:</td>\n" +
            "<td><input name=\"cx_num\" size=\"16\" /></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Credit Card Expiration Date (yyyy/mm/dd):</td>\n" +
            "<td><input name=\"cx_expiry\" size=\"16\" /></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Shipping Method:</td>\n" +
            "<td><input type=\"radio\" name=\"o_ship_type\" value=\"AIR\" " +
                "checked>AIR</input>" +
            "<input type=\"radio\" name=\"o_ship_type\" " +
                "value=\"UPS\">UPS</input>\n" +
            "<input type=\"radio\" name=\"o_ship_type\" " +
                "value=\"FEDEX\">FEDEX</input>\n" +
            "<input type=\"radio\" name=\"o_ship_type\" " +
                "value=\"SHIP\">SHIP</input>\n" +
            "<input type=\"radio\" name=\"o_ship_type\" " +
                "value=\"COURIER\">COURIER</input>\n" +
            "<input type=\"radio\" name=\"o_ship_type\" " +
                "value=\"MAIL\">MAIL</input>\n" +
            "</td>\n" +
            "</tr>\n" +
            "</table>\n" +
            "<p align=\"center\">\n" +
            "<input type=\"image\" name=\"submit\" " +
                "src=\"process.gif\" " +
                "height=\"30\" width=\"120\">" +
            "<a href=\"" + ShoppingCartInteraction +
                "?add_flag=n&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">" +
                "<img src=\"cart.gif\" alt=\"Shopping Cart\" " +
                "border=\"0\" width=\"120\" height=\"30\"></a>" +
            "<a href=\"" + HomeInteraction + "?sc_id=" + sc_id +
                "&c_id=" + c_id + "\">" +
            "<img alt=\"Home\" border=\"0\" height=\"30\" " +
                "src=\"home.gif\" width=\"120\"></a>\n" +
            "</p>\n" +
            "</form>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     * Customer Registration interaction.
     * Clause 2.5
     */
    public void doCustomerRegistration(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        /* Data from the request. */
        String c_id = request.getParameter("c_id");
        String sc_id = request.getParameter("sc_id");
        if (c_id == null) {
            c_id = "0";
        }
        if (sc_id == null) {
            sc_id = "0";
        }

	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Customer Registration Page</title>\n" +
            "<style type=\"text/css\">\n" +
            "h1 { text-align: center }\n" +
            "h2 { text-align: center }\n" +
            "h3 { text-align: center }\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "<h1>OSDL Web Commerce Workload (DBT-1)</h1>\n" +
            "<hr />\n" +
            "<p align=\"center\">\n" +
            "<img src=\"tpclogo.gif\" width=\"288\" " +
                "height=\"67\" />\n" +
            "</p>\n" +
            "<h2>Customer Registration Page</h2>" +
            "<hr />\n" +
            "<form action=\""+ BuyRequestInteraction + "\" " +
                "method=\"get\">\n" +
            "<input type=\"hidden\" name=\"sc_id\" value=\"" + sc_id +"\">\n" +
            "<input type=\"hidden\" name=\"c_id\" value=\"" + c_id + "\">\n" +
            "<table>\n" +
            "<tr>\n" +
            "<td><input checked name=\"returning\" "+
                "type=\"radio\" value=\"y\">I am an existing customer.</td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td><input name=\"returning\" type=\"radio\" " +
                "value=\"n\">I am a first time customer.</td>\n" +
            "</tr>\n" +
            "</table>\n" +
            "<hr />\n" +
            "<p>\n" +
            "<strong>If you're an existing customer, enter your " +
            "Username and Password:</strong>\n" +
            "</p>\n" +
            "<table>\n" +
            "<tr>\n" +
            "<td>Username: <input name=\"c_uname\" size=\"23\"></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Password: <input name=\"c_passwd\" " +
                "type=\"password\" size=\"23\"</td>\n" +
            "</tr>\n" +
            "</table>\n" +
            "<hr />\n" +
            "<p>\n" +
            "<strong>If you're a first time customer, enter the " +
            "details below:</strong>\n" +
            "</p>\n" +
            "<table>\n" +
            "<tr>\n" +
            "<td>Enter your birth date (yyyy/mm/dd):</td>\n" +
            "<td><input name=\"c_birthdate\" size=\"10\"></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Enter your First Name:</td>\n" +
            "<td><input name=\"c_fname\" size=\"15\"></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Enter your Last Name:</td>\n" +
            "<td><input name=\"c_lname\" size=\"15\"></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Enter your Address 1:</td>\n" +
            "<td><input name=\"addr_street1\" size=\"40\"></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Enter your Address 2:</td>\n" +
            "<td><input name=\"addr_street2\" size=\"40\"></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Enter your City, State, Zip:</td>\n" +
            "<td><input name=\"addr_city\" size=\"30\">" +
                "<input name=\"addr_state\" size=\"20\">" +
                "<input name=\"addr_zip\" size=\"10\"></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Enter your Country:</td>\n" +
            "<td><input name=\"co_name\" size=\"50\"></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Enter your Phone:</td>\n" +
            "<td><input name=\"c_phone\" size=\"16\"></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td>Enter your E-mail:</td>\n" +
            "<td><input name=\"c_email\" size=\"50\"></td>\n" +
            "</tr>\n" +
            "</table>\n" +
            "<hr />\n" +
            "Other Customer Data:<br />\n" +
            "<textarea cols=\"65\" name=\"c_data\" rows=\"4\"></textarea>\n" +
            "<hr />\n" +
            "<p align=\"center\">\n" +
            "<input type=\"image\" name=\"submit\" src=\"submit.gif\" " +
                "border=\"0\" height=\"30\" width=\"120\">" +
            "<a href=\"" + SearchRequestInteraction +
                    "?sc_id=" + sc_id + "&c_id=" + c_id +"\">" +
                "<img alt=\"Search\" border=\"0\" height=\"30\" " +
                    "src=\"search.gif\" width=\"120\"></a>" +
            "<a href=\"" + HomeInteraction + "?sc_id=" + sc_id +
                    "&c_id=" + c_id + "\">" +
                "<img alt=\"Home\" border=\"0\" height=\"30\" " +
                    "src=\"home.gif\" width=\"120\"></a>\n" +
            "</p>\n" +
            "</form>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     *
     */
    public void doGet(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException
    {
        /*
         * Determine the interaction to execute based on
         * request.getServletPath().
         */
        if (request.getServletPath().equals("/") ||
                request.getServletPath().equals("/" +
                    HomeInteraction)) {
            doHome(request, response);
        } else if (request.getServletPath().equals( "/" +
                BestSellersInteraction)) {
            doBestSellers(request, response);
        } else if (request.getServletPath().equals( "/" +
                OrderDisplayInteraction)) {
            doOrderDisplay(request, response);
        } else if (request.getServletPath().equals( "/" +
                BuyRequestInteraction)) {
            doBuyRequest(request, response);
        } else if (request.getServletPath().equals( "/" +
                AdminRequestInteraction)) {
            doAdminRequest(request, response);
        } else if (request.getServletPath().equals( "/" +
                AdminConfirmInteraction)) {
            doAdminConfirm(request, response);
        } else if (request.getServletPath().equals( "/" +
                ShoppingCartInteraction)) {
            doShoppingCart(request, response);
        } else if (request.getServletPath().equals( "/" +
                Adjustment)) {
            String submit = request.getParameter("submit");
            if (submit.equals(ShoppingCartRefresh)) {
                doShoppingCart(request, response);
            } else if (submit.equals(ShoppingCartCheckout)) {
                doCustomerRegistration(request, response);
            } else {
                doError(request, response);
            }
        } else if (request.getServletPath().equals( "/" +
                SearchRequestInteraction)) {
            doSearchRequest(request, response);
        } else if (request.getServletPath().equals( "/" +
                ProductDetailInteraction)) {
            doProductDetail(request, response);
        } else if (request.getServletPath().equals( "/" +
                BuyConfirmInteraction)) {
            doBuyConfirm(request, response);
        } else if (request.getServletPath().equals( "/" +
                OrderInquiryInteraction)) {
            doOrderInquiry(request, response);
        } else if (request.getServletPath().equals( "/" +
                NewProductsInteraction)) {
            doNewProducts(request, response);
        } else if (request.getServletPath().equals(
                "/" + SearchResultsInteraction)) {
            doSearchResults(request, response);
        } else {
            doError(request, response);
        }
    }

    /**
     *  Display an error page.
     */
    private void doError(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        Cookie[] cookies = request.getCookies();
	response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        Enumeration parameterNames = request.getParameterNames();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Error</title>\n" +
            "</head>\n" +
            "<body>\n" +
            "<p>\n" +
            "getMethod(): " + request.getMethod() + "\n" +
            "</p>\n" +
            "<p>\n" +
            "getPathInfo(): " + request.getPathInfo() + "\n" +
            "</p>\n" +
            "<p>\n" +
            "getParameterNames(): \n";
        while (parameterNames.hasMoreElements()) {
            html += (String) parameterNames.nextElement() + "<br />\n";
        }
        html +=
            "</p>\n" +
            "<p>\n" +
            "<table borders=\"1\">\n" +
            "<caption>getCookies()</caption>\n";
        if (cookies != null) {
            for (int i = 0; i < cookies.length; i++) {
                html += "<td>" + cookies[i].getName() +
                    "</td><td>" + cookies[i].getValue() + "</td>\n";
            }
        }
        html +=
            "</table>\n" +
            "</p>\n" +
            "<p>\n" +
            "getQueryString(): " + request.getQueryString() + "\n" +
            "</p>\n" +
            "<p>\n" +
            "getRequestURI(): " + request.getRequestURI() + "\n" +
            "</p>\n" +
            "<p>\n" +
            "getServletPath(): " + request.getServletPath() + "\n" +
            "</p>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     *  Display an error page with a message.
     */
    private void doError(HttpServletRequest request,
            HttpServletResponse response, String message)
        throws ServletException, IOException
    {
	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Error</title>\n" +
            "</head>\n" +
            "<body>\n" +
            message + "\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     * Home interaction.
     * Clause 2.3
     */
    private void doHome(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        /* Data from the request. */
        String c_id = request.getParameter("c_id");
        String sc_id = request.getParameter("sc_id");
        if (c_id == null) {
            c_id = "0";
        }
        if (sc_id == null) {
            sc_id = "0";
        }

        /* Data from the database. */
        String c_fname = "";
        String c_lname = "";
        String[] pp_i_id = new String[] { "", "", "", "", "" };
        String[] pp_t_id = new String[] { "", "", "", "", "" };

        Connection con = null;
        String query = "";
        try {
            con = source.getConnection();
            con.setAutoCommit(false);

            Statement st = con.createStatement();
            st.setFetchSize(1);
            query =
                "SELECT home.* " +
                "FROM home(" + c_id + " , " + Integer.toString(
                        random.nextInt(items) + 1) +
                    ")" +
                " AS (" +
                "   c_fname CHAR," +
                "   c_lname CHAR," +
                "   pp_i_id1 NUMERIC, " +
                "   pp_t_id1 NUMERIC, " +
                "   pp_i_id2 NUMERIC, " +
                "   pp_t_id2 NUMERIC, " +
                "   pp_i_id3 NUMERIC, " +
                "   pp_t_id3 NUMERIC, " +
                "   pp_i_id4 NUMERIC, " +
                "   pp_t_id4 NUMERIC, " +
                "   pp_i_id5 NUMERIC, " +
                "   pp_t_id5 NUMERIC )";
            ResultSet rs = st.executeQuery(query);
            rs.next();
            c_fname = rs.getString(1);
            c_lname = rs.getString(2);
            for (int i = 0, j = 3; i < 5; i++) {
                pp_i_id[i] = rs.getString(j++);
                pp_t_id[i] = rs.getString(j++);
            }
            rs.close();
            st.close();
            con.commit();
            con.close();
         } catch (SQLException e) {
            e.printStackTrace();
            doError(request, response, query);
            return;
         }

	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Home Page</title>\n" +
            "<style type=\"text/css\">\n" +
            "h1 { text-align: center }\n" +
            "h2 { text-align: center }\n" +
            "h3 { text-align: center }\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "<h1>OSDL Web Commerce Workload (DBT-1)</h1>\n" +
            "<hr />\n" +
            "<p align=\"center\">\n" +
            "<img src=\"tpclogo.gif\" width=\"288\" height=\"67\" />\n" +
            "</p>\n" +
            "<h2>Home Page</h2>\n";
            if (!c_id.equals("0")) {
                html +=
                    "<h3>Welcome back " + c_fname + " " + c_lname + "</h3>\n";
            }
        html += getPromotionalProcessing(c_id, sc_id, pp_i_id, pp_t_id);
        html +=
            "<p align=\"center\">\n" +
            "<table border=\"0\" cellpadding=\"6\" " +
                "cellspacing=\"0\" width=\"700\">\n" +
            "<tr align=\"center\" valign=\"top\">\n" +
            "<td colspan=\"2\" valign=\"middle\" "+
                "width=\"300\"><img src=\"new.gif\" " +
                "alt=\"New Product\" width=\"300\" /></td>\n" +
            "<td width=\"100\"></td>\n" + 
            "<td colspan=\"2\" width=\"300\"><img " +
                "src=\"best.gif\" alt=\"Best Seller\" " +
                "width=\"300\" /></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=ARTS&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">ARTS</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=NON-FICTION&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">NON-FICTION</a></td>\n" +
            "<td width=\"50\"></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=ARTS&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">ARTS</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=NON-FICTION&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">NON-FICTION</a></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=BIOGRAPHIES&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">BIOGRAPHIES</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=PARENTING&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">PARENTING</a></td>\n" +
            "<td width=\"50\"></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=BIOGRAPHIES&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">BIOGRAPHIES</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=PARENTING&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">PARENTING</a></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=BUSINESS&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">BUSINESS</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=POLITICS&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">POLITICS</a></td>\n" +
            "<td width=\"50\"></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=BUSINESS&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">BUSINESS</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=POLITICS&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">POLITICS</a></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=CHILDREN&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">CHILDREN</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=REFERENCE&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">REFERENCE</a></td>\n" +
            "<td width=\"50\"></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=CHILDREN&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">CHILDREN</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=REFERENCE&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">REFERENCE</a></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=COMPUTERS&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">COMPUTERS</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=RELIGION&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">RELIGION</a></td>\n" +
            "<td width=\"50\"></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=COMPUTERS&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">COMPUTERS</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=RELIGION&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">RELIGION</a></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=COOKING&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">COOKING</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=ROMANCE&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">ROMANCE</a></td>\n" +
            "<td width=\"50\"></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=COOKING&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">COOKING</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=ROMANCE&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">ROMANCE</a></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=HEALTH&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">HEALTH</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=SELF-HELP&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">SELFHELP</a></td>\n" +
            "<td width=\"50\"></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=HEALTH&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">HEALTH</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=SELF-HELP&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">SELF-HELP</a></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=HISTORY&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">HISTORY</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=SCIENCE-NATURE&sc_id=" + sc_id +
                "&c_id=" + c_id +
                "\">SCIENCE-NATURE</a></td>\n" +
            "<td width=\"50\"></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=HISTORY&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">HISTORY</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=SCIENCE-NATURE&sc_id=" +
                sc_id + "&c_id=" + c_id +
                "\">SCIENCE-NATURE</a></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=HOME&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">HOME</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=SCIENCE-FICTION&sc_id=" +
                sc_id + "&c_id=" + c_id +
                "\">SCIENCE-FICTION</a></td>\n" +
            "<td width=\"50\"></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=HOME&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">HOME</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=SCIENCE-FICTION&sc_id=" +
                sc_id + "&c_id=" + c_id +
                "\">SCIENCE-FICTION</a></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=HUMOR&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">HUMOR</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=SPORTS&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">SPORTS</a></td>\n" +
            "<td width=\"50\"></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=HUMOR&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">HUMOR</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=SPORTS&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">SPORTS</a></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=LITERATURE&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">LITERATURE</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=TRAVEL&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">TRAVEL</a></td>\n" +
            "<td width=\"50\"></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=LITERATURE&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">LITERATURE</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=TRAVEL&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">TRAVEL</a></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=MYSTERY&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">MYSTERY</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + NewProductsInteraction +
                "?i_subject=YOUTH&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">YOUTH</a></td>\n" +
            "<td width=\"50\"></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=MYSTERY&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">MYSTERY</a></td>\n" +
            "<td align=\"center\">" +
            "<a href=\"" + BestSellersInteraction +
                "?i_subject=TRAVEL&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">YOUTH</a></td>\n" +
            "</tr>\n" +
            "</table>\n" +
            "</p>\n" +
            "<p align=\"center\">" +
            "<a href=\"" + ShoppingCartInteraction +
                "?add_flag=n&sc_id=" + sc_id +
                "&c_id=" + c_id + "\">" +
                "<img src=\"cart.gif\" alt=\"Shopping Cart\" " +
                "border=\"0\" width=\"120\" height=\"30\">" +
                "</a><a href=\"" + SearchRequestInteraction +
                "?sc_id=" + sc_id +
                "&c_id=" + c_id + "\"><img " +
                "src=\"search.gif\" alt=\"Search\" " +
                "border=\"0\" width=\"120\" height=\"30\">" +
                "</a><a href=\"" + OrderInquiryInteraction +
                    "?sc_id=" + sc_id + "&c_id=" + c_id +
                    "\">" +
                "<img src=\"status.gif\" " +
                "alt=\"Order Status\" border=\"0\" " +
                "width=\"120\" height=\"30\"></a></p>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     * New Products interaction.
     * Clause 2.12
     */
    private void doNewProducts(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        /* Data from the request. */
        String c_id = request.getParameter("c_id");
        String sc_id = request.getParameter("sc_id");
        String i_subject = request.getParameter("i_subject");
        if (c_id == null) {
            c_id = "0";
        }
        if (sc_id == null) {
            sc_id = "0";
        }
        if (i_subject == null) {
            doError(request, response, "No i_subject.");
            return;
        }

        /* Data from the database. */
        String[] pp_i_id = new String[] { "", "", "", "", "" };
        String[] pp_t_id = new String[] { "", "", "", "", "" };
        int count = 0;
        String[] i_id;
        String[] i_title;
        String[] a_fname;
        String[] a_lname;

        Connection con = null;
        String query = "";
        try {
            con = source.getConnection();
            con.setAutoCommit(false);

            Statement st = con.createStatement();
            st.setFetchSize(1);
            query =
                "SELECT new_products.* " +
                "FROM new_products ( '" + i_subject +
                    "', "+ Integer.toString(
                    random.nextInt(items) + 1) + " )" +
                " AS (i_related1 NUMERIC, " +
                "     i_related2 NUMERIC, " +
                "     i_related3 NUMERIC, " +
                "     i_related4 NUMERIC, " +
                "     i_related5 NUMERIC, " +
                "     i_thumbnail1 NUMERIC, " +
                "     i_thumbnail2 NUMERIC, " +
                "     i_thumbnail3 NUMERIC, " +
                "     i_thumbnail4 NUMERIC, " +
                "     i_thumbnail5 NUMERIC, " +
                "     items NUMERIC, " +
                "     i_id1 NUMERIC, " +
                "     i_title1 VARCHAR, " +
                "     a_fname1 VARCHAR, " +
                "     a_lname1 VARCHAR, " +
                "     i_id2 NUMERIC, " +
                "     i_title2 VARCHAR, " +
                "     a_fname2 VARCHAR, " +
                "     a_lname2 VARCHAR, " +
                "     i_id3 NUMERIC, " +
                "     i_title3 VARCHAR, " +
                "     a_fname3 VARCHAR, " +
                "     a_lname3 VARCHAR, " +
                "     i_id4 NUMERIC, " +
                "     i_title4 VARCHAR, " +
                "     a_fname4 VARCHAR, " +
                "     a_lname4 VARCHAR, " +
                "     i_id5 NUMERIC, " +
                "     i_title5 VARCHAR, " +
                "     a_fname5 VARCHAR, " +
                "     a_lname5 VARCHAR, " +
                "     i_id6 NUMERIC, " +
                "     i_title6 VARCHAR, " +
                "     a_fname6 VARCHAR, " +
                "     a_lname6 VARCHAR, " +
                "     i_id7 NUMERIC, " +
                "     i_title7 VARCHAR, " +
                "     a_fname7 VARCHAR, " +
                "     a_lname7 VARCHAR, " +
                "     i_id8 NUMERIC, " +
                "     i_title8 VARCHAR, " +
                "     a_fname8 VARCHAR, " +
                "     a_lname8 VARCHAR, " +
                "     i_id9 NUMERIC, " +
                "     i_title9 VARCHAR, " +
                "     a_fname9 VARCHAR, " +
                "     a_lname9 VARCHAR, " +
                "     i_id10 NUMERIC, " +
                "     i_title10 VARCHAR, " +
                "     a_fname10 VARCHAR, " +
                "     a_lname10 VARCHAR, " +
                "     i_id11 NUMERIC, " +
                "     i_title11 VARCHAR, " +
                "     a_fname11 VARCHAR, " +
                "     a_lname11 VARCHAR, " +
                "     i_id12 NUMERIC, " +
                "     i_title12 VARCHAR, " +
                "     a_fname12 VARCHAR, " +
                "     a_lname12 VARCHAR, " +
                "     i_id13 NUMERIC, " +
                "     i_title13 VARCHAR, " +
                "     a_fname13 VARCHAR, " +
                "     a_lname13 VARCHAR, " +
                "     i_id14 NUMERIC, " +
                "     i_title14 VARCHAR, " +
                "     a_fname14 VARCHAR, " +
                "     a_lname14 VARCHAR, " +
                "     i_id15 NUMERIC, " +
                "     i_title15 VARCHAR, " +
                "     a_fname15 VARCHAR, " +
                "     a_lname15 VARCHAR, " +
                "     i_id16 NUMERIC, " +
                "     i_title16 VARCHAR, " +
                "     a_fname16 VARCHAR, " +
                "     a_lname16 VARCHAR, " +
                "     i_id17 NUMERIC, " +
                "     i_title17 VARCHAR, " +
                "     a_fname17 VARCHAR, " +
                "     a_lname17 VARCHAR, " +
                "     i_id18 NUMERIC, " +
                "     i_title18 VARCHAR, " +
                "     a_fname18 VARCHAR, " +
                "     a_lname18 VARCHAR, " +
                "     i_id19 NUMERIC, " +
                "     i_title19 VARCHAR, " +
                "     a_fname19 VARCHAR, " +
                "     a_lname19 VARCHAR, " +
                "     i_id20 NUMERIC, " +
                "     i_title20 VARCHAR, " +
                "     a_fname20 VARCHAR, " +
                "     a_lname20 VARCHAR, " +
                "     i_id21 NUMERIC, " +
                "     i_title21 VARCHAR, " +
                "     a_fname21 VARCHAR, " +
                "     a_lname21 VARCHAR, " +
                "     i_id22 NUMERIC, " +
                "     i_title22 VARCHAR, " +
                "     a_fname22 VARCHAR, " +
                "     a_lname22 VARCHAR, " +
                "     i_id23 NUMERIC, " +
                "     i_title23 VARCHAR, " +
                "     a_fname23 VARCHAR, " +
                "     a_lname23 VARCHAR, " +
                "     i_id24 NUMERIC, " +
                "     i_title24 VARCHAR, " +
                "     a_fname24 VARCHAR, " +
                "     a_lname24 VARCHAR, " +
                "     i_id25 NUMERIC, " +
                "     i_title25 VARCHAR, " +
                "     a_fname25 VARCHAR, " +
                "     a_lname25 VARCHAR, " +
                "     i_id26 NUMERIC, " +
                "     i_title26 VARCHAR, " +
                "     a_fname26 VARCHAR, " +
                "     a_lname26 VARCHAR, " +
                "     i_id27 NUMERIC, " +
                "     i_title27 VARCHAR, " +
                "     a_fname27 VARCHAR, " +
                "     a_lname27 VARCHAR, " +
                "     i_id28 NUMERIC, " +
                "     i_title28 VARCHAR, " +
                "     a_fname28 VARCHAR, " +
                "     a_lname28 VARCHAR, " +
                "     i_id29 NUMERIC, " +
                "     i_title29 VARCHAR, " +
                "     a_fname29 VARCHAR, " +
                "     a_lname29 VARCHAR, " +
                "     i_id30 NUMERIC, " +
                "     i_title30 VARCHAR, " +
                "     a_fname30 VARCHAR, " +
                "     a_lname30 VARCHAR, " +
                "     i_id31 NUMERIC, " +
                "     i_title31 VARCHAR, " +
                "     a_fname31 VARCHAR, " +
                "     a_lname31 VARCHAR, " +
                "     i_id32 NUMERIC, " +
                "     i_title32 VARCHAR, " +
                "     a_fname32 VARCHAR, " +
                "     a_lname32 VARCHAR, " +
                "     i_id33 NUMERIC, " +
                "     i_title33 VARCHAR, " +
                "     a_fname33 VARCHAR, " +
                "     a_lname33 VARCHAR, " +
                "     i_id34 NUMERIC, " +
                "     i_title34 VARCHAR, " +
                "     a_fname34 VARCHAR, " +
                "     a_lname34 VARCHAR, " +
                "     i_id35 NUMERIC, " +
                "     i_title35 VARCHAR, " +
                "     a_fname35 VARCHAR, " +
                "     a_lname35 VARCHAR, " +
                "     i_id36 NUMERIC, " +
                "     i_title36 VARCHAR, " +
                "     a_fname36 VARCHAR, " +
                "     a_lname36 VARCHAR, " +
                "     i_id37 NUMERIC, " +
                "     i_title37 VARCHAR, " +
                "     a_fname37 VARCHAR, " +
                "     a_lname37 VARCHAR, " +
                "     i_id38 NUMERIC, " +
                "     i_title38 VARCHAR, " +
                "     a_fname38 VARCHAR, " +
                "     a_lname38 VARCHAR, " +
                "     i_id39 NUMERIC, " +
                "     i_title39 VARCHAR, " +
                "     a_fname39 VARCHAR, " +
                "     a_lname39 VARCHAR, " +
                "     i_id40 NUMERIC, " +
                "     i_title40 VARCHAR, " +
                "     a_fname40 VARCHAR, " +
                "     a_lname40 VARCHAR, " +
                "     i_id41 NUMERIC, " +
                "     i_title41 VARCHAR, " +
                "     a_fname41 VARCHAR, " +
                "     a_lname41 VARCHAR, " +
                "     i_id42 NUMERIC, " +
                "     i_title42 VARCHAR, " +
                "     a_fname42 VARCHAR, " +
                "     a_lname42 VARCHAR, " +
                "     i_id43 NUMERIC, " +
                "     i_title43 VARCHAR, " +
                "     a_fname43 VARCHAR, " +
                "     a_lname43 VARCHAR, " +
                "     i_id44 NUMERIC, " +
                "     i_title44 VARCHAR, " +
                "     a_fname44 VARCHAR, " +
                "     a_lname44 VARCHAR, " +
                "     i_id45 NUMERIC, " +
                "     i_title45 VARCHAR, " +
                "     a_fname45 VARCHAR, " +
                "     a_lname45 VARCHAR, " +
                "     i_id46 NUMERIC, " +
                "     i_title46 VARCHAR, " +
                "     a_fname46 VARCHAR, " +
                "     a_lname46 VARCHAR, " +
                "     i_id47 NUMERIC, " +
                "     i_title47 VARCHAR, " +
                "     a_fname47 VARCHAR, " +
                "     a_lname47 VARCHAR, " +
                "     i_id48 NUMERIC, " +
                "     i_title48 VARCHAR, " +
                "     a_fname48 VARCHAR, " +
                "     a_lname48 VARCHAR, " +
                "     i_id49 NUMERIC, " +
                "     i_title49 VARCHAR, " +
                "     a_fname49 VARCHAR, " +
                "     a_lname49 VARCHAR, " +
                "     i_id50 NUMERIC, " +
                "     i_title50 VARCHAR, " +
                "     a_fname50 VARCHAR, " +
                "     a_lname50 VARCHAR )";
            ResultSet rs = st.executeQuery(query);
            rs.next();
            for (int i = 0, j = 1; i < 5; i++) {
                pp_i_id[i] = rs.getString(j++);
                pp_t_id[i] = rs.getString(j++);
            }
            count = rs.getInt(11);
            i_id = new String[count];
            i_title = new String[count];
            a_fname = new String[count];
            a_lname = new String[count];
            for (int i = 0, j = 12; i < count; i++) {
                i_id[i] = rs.getString(j++);
                i_title[i] = rs.getString(j++);
                a_fname[i] = rs.getString(j++);
                a_lname[i] = rs.getString(j++);
            }
            rs.close();
            st.close();
            con.commit();
            con.close();
         } catch (SQLException e) {
            e.printStackTrace();
            doError(request, response, query);
            return;
         }

	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 New Products Page: Subject: " +
                i_subject + "</title>\n" +
            "<style type=\"text/css\">\n" +
            "h1 { text-align: center }\n" +
            "h2 { text-align: center }\n" +
            "h3 { text-align: center }\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "<h1>OSDL Web Commerce Workload (DBT-1)</h1>\n" +
            "<hr />\n" +
            "<p align=\"center\">\n" +
            "<img src=\"tpclogo.gif\" align=\"bottom\" " +
                "border=\"0\" width=\"288\" height=\"67\">\n " +
            "</p>\n" +
            "<h2>New Products Page</h2>\n";
        html += getPromotionalProcessing(c_id, sc_id, pp_i_id, pp_t_id);
        html +=
            "<table border=\"1\" cellpadding=\"1\" " + "cellspacing=\"1\">\n" +
            "<tr>\n" +
            "<th>Author</th>\n" +
            "<th>Title</th>\n" +
            "</tr>\n";
        for (int i = 0; i < count; i++) {
            html +=
                "<tr>\n" +
                "<td><em>" + a_fname[i] + " " + a_lname[i] + "</em></td>\n" +
                "<td><a href=\"" + ProductDetailInteraction +
                    "?i_id=" + i_id[i] + "&sc_id=" + sc_id +
                    "&c_id=" + c_id + "\">" + i_title[i] + "</a></td>\n" +
                "</tr>\n";
        }
        html +=
            "</table>\n" +
            "<p align=\"center\">\n" +
            "<a href=\"" + ShoppingCartInteraction +
                "?add_flag=n&sc_id=" + sc_id + "&c_id=" + c_id + "\">" +
            "<img alt=\"Shopping Cart\" border=\"0\" " +
            "height=\"30\" src=\"cart.gif\" width=\"120\">" +
            "</a><a href=\"" + SearchRequestInteraction +
                "?sc_id=" + sc_id + "&c_id=" + c_id +"\">" +
            "<img alt=\"Search\" border=\"0\" height=\"30\" " +
                "src=\"search.gif\" width=\"120\"></a>" +
            "<a href=\"" + HomeInteraction + "?sc_id=" + sc_id +
                "&c_id=" + c_id + "\">" +
            "<img alt=\"Home\" border=\"0\" height=\"30\" " +
                "src=\"home.gif\" width=\"120\"></a></p>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     * Order Display interaction.
     * Clause 2.9
     */
    private void doOrderDisplay(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        /* Data from the request. */
        String c_id = request.getParameter("c_id");
        String sc_id = request.getParameter("sc_id");
        String c_uname = request.getParameter("c_uname");
        String c_passwd = request.getParameter("c_passwd");
        if (c_id == null) {
            c_id = "0";
        }
        if (sc_id == null) {
            sc_id = "0";
        }
        if (c_uname == null) {
            doError(request, response, "No c_uname.");
            return;
        }
        if (c_passwd == null) {
            doError(request, response, "No c_passwd.");
            return;
        }

        /* Data from the database. */
        int count = 0;
        String c_fname = "";
        String c_lname = "";
        String c_phone = "";
        String c_email = "";
        String o_id = "";
        String o_date = "";
        String o_sub_total = "";
        String o_tax = "";
        String o_total = "";
        String o_ship_type = "";
        String o_ship_date = "";
        String o_status = "";
        String cx_type = "";
        String cx_auth_id = "";
        String bill_addr_street1 = "";
        String bill_addr_street2 = "";
        String bill_addr_city = "";
        String bill_addr_state = "";
        String bill_addr_zip = "";
        String bill_co_name = "";
        String ship_addr_street1 = "";
        String ship_addr_street2 = "";
        String ship_addr_city = "";
        String ship_addr_state = "";
        String ship_addr_zip = "";
        String ship_co_name = "";
        String[] i_id;
        String[] i_title;
        String[] i_publisher;
        String[] i_cost;
        String[] ol_qty;
        String[] ol_discount;
        String[] ol_comments;

        Connection con = null;
        String query = "";
        try {
            con = source.getConnection();
            con.setAutoCommit(false);

            Statement st = con.createStatement();
            st.setFetchSize(1);
            query = "SELECT order_display.* " +
                "FROM order_display ( '" + c_uname + "', '" +
                    c_passwd + "') " +
                "AS ( c_fname VARCHAR, " +
                "     c_lname VARCHAR, " +
                "     c_phone VARCHAR, " +
                "     c_email VARCHAR, " +
                "     o_id NUMERIC, " +
                "     o_date CHAR, " +
                "     o_sub_total NUMERIC, " +
                "     o_tax NUMERIC, " +
                "     o_total NUMERIC, " +
                "     o_ship_type VARCHAR, " +
                "     o_ship_date CHAR(26), " +
                "     o_status VARCHAR, " +
                "     cx_type VARCHAR, " +
                "     cx_auth_id VARCHAR, " +
                "     bill_addr_street1 VARCHAR, " +
                "     bill_addr_street2 VARCHAR, " +
                "     bill_addr_city VARCHAR, " +
                "     bill_addr_state VARCHAR, " +
                "     bill_addr_zip VARCHAR, " +
                "     bill_co_name VARCHAR, " +
                "     ship_addr_street1 VARCHAR, " +
                "     ship_addr_street2 VARCHAR, " +
                "     ship_addr_city VARCHAR, " +
                "     ship_addr_state VARCHAR, " +
                "     ship_addr_zip VARCHAR, " +
                "     ship_co_name VARCHAR, " +
                "     num_item NUMERIC, " +
                "     i_id1 NUMERIC, " +
                "     i_title1 VARCHAR, " +
                "     i_publisher1 VARCHAR, " +
                "     i_cost1 NUMERIC, " +
                "     ol_qty1 NUMERIC, " +
                "     ol_discount1 NUMERIC, " +
                "     ol_comments1 VARCHAR, " +
                "     i_id2 NUMERIC, " +
                "     i_title2 VARCHAR, " +
                "     i_publisher2 VARCHAR, " +
                "     i_cost2 NUMERIC, " +
                "     ol_qty2 NUMERIC, " +
                "     ol_discount2 NUMERIC, " +
                "     ol_comments2 VARCHAR, " +
                "     i_id3 NUMERIC, " +
                "     i_title3 VARCHAR, " +
                "     i_publisher3 VARCHAR, " +
                "     i_cost3 NUMERIC, " +
                "     ol_qty3 NUMERIC, " +
                "     ol_discount3 NUMERIC, " +
                "     ol_comments3 VARCHAR, " +
                "     i_id4 NUMERIC, " +
                "     i_title4 VARCHAR, " +
                "     i_publisher4 VARCHAR, " +
                "     i_cost4 NUMERIC, " +
                "     ol_qty4 NUMERIC, " +
                "     ol_discount4 NUMERIC, " +
                "     ol_comments4 VARCHAR, " +
                "     i_id5 NUMERIC, " +
                "     i_title5 VARCHAR, " +
                "     i_publisher5 VARCHAR, " +
                "     i_cost5 NUMERIC, " +
                "     ol_qty5 NUMERIC, " +
                "     ol_discount5 NUMERIC, " +
                "     ol_comments5 VARCHAR, " +
                "     i_id6 NUMERIC, " +
                "     i_title6 VARCHAR, " +
                "     i_publisher6 VARCHAR, " +
                "     i_cost6 NUMERIC, " +
                "     ol_qty6 NUMERIC, " +
                "     ol_discount6 NUMERIC, " +
                "     ol_comments6 VARCHAR, " +
                "     i_id7 NUMERIC, " +
                "     i_title7 VARCHAR, " +
                "     i_publisher7 VARCHAR, " +
                "     i_cost7 NUMERIC, " +
                "     ol_qty7 NUMERIC, " +
                "     ol_discount7 NUMERIC, " +
                "     ol_comments7 VARCHAR, " +
                "     i_id8 NUMERIC, " +
                "     i_title8 VARCHAR, " +
                "     i_publisher8 VARCHAR, " +
                "     i_cost8 NUMERIC, " +
                "     ol_qty8 NUMERIC, " +
                "     ol_discount8 NUMERIC, " +
                "     ol_comments8 VARCHAR, " +
                "     i_id9 NUMERIC, " +
                "     i_title9 VARCHAR, " +
                "     i_publisher9 VARCHAR, " +
                "     i_cost9 NUMERIC, " +
                "     ol_qty9 NUMERIC, " +
                "     ol_discount9 NUMERIC, " +
                "     ol_comments9 VARCHAR, " +
                "     i_id10 NUMERIC, " +
                "     i_title10 VARCHAR, " +
                "     i_publisher10 VARCHAR, " +
                "     i_cost10 NUMERIC, " +
                "     ol_qty10 NUMERIC, " +
                "     ol_discount10 NUMERIC, " +
                "     ol_comments10 VARCHAR, " +
                "     i_id11 NUMERIC, " +
                "     i_title11 VARCHAR, " +
                "     i_publisher11 VARCHAR, " +
                "     i_cost11 NUMERIC, " +
                "     ol_qty11 NUMERIC, " +
                "     ol_discount11 NUMERIC, " +
                "     ol_comments11 VARCHAR, " +
                "     i_id12 NUMERIC, " +
                "     i_title12 VARCHAR, " +
                "     i_publisher12 VARCHAR, " +
                "     i_cost12 NUMERIC, " +
                "     ol_qty12 NUMERIC, " +
                "     ol_discount12 NUMERIC, " +
                "     ol_comments12 VARCHAR, " +
                "     i_id13 NUMERIC, " +
                "     i_title13 VARCHAR, " +
                "     i_publisher13 VARCHAR, " +
                "     i_cost13 NUMERIC, " +
                "     ol_qty13 NUMERIC, " +
                "     ol_discount13 NUMERIC, " +
                "     ol_comments13 VARCHAR, " +
                "     i_id14 NUMERIC, " +
                "     i_title14 VARCHAR, " +
                "     i_publisher14 VARCHAR, " +
                "     i_cost14 NUMERIC, " +
                "     ol_qty14 NUMERIC, " +
                "     ol_discount14 NUMERIC, " +
                "     ol_comments14 VARCHAR, " +
                "     i_id15 NUMERIC, " +
                "     i_title15 VARCHAR, " +
                "     i_publisher15 VARCHAR, " +
                "     i_cost15 NUMERIC, " +
                "     ol_qty15 NUMERIC, " +
                "     ol_discount15 NUMERIC, " +
                "     ol_comments15 VARCHAR, " +
                "     i_id16 NUMERIC, " +
                "     i_title16 VARCHAR, " +
                "     i_publisher16 VARCHAR, " +
                "     i_cost16 NUMERIC, " +
                "     ol_qty16 NUMERIC, " +
                "     ol_discount16 NUMERIC, " +
                "     ol_comments16 VARCHAR, " +
                "     i_id17 NUMERIC, " +
                "     i_title17 VARCHAR, " +
                "     i_publisher17 VARCHAR, " +
                "     i_cost17 NUMERIC, " +
                "     ol_qty17 NUMERIC, " +
                "     ol_discount17 NUMERIC, " +
                "     ol_comments17 VARCHAR, " +
                "     i_id18 NUMERIC, " +
                "     i_title18 VARCHAR, " +
                "     i_publisher18 VARCHAR, " +
                "     i_cost18 NUMERIC, " +
                "     ol_qty18 NUMERIC, " +
                "     ol_discount18 NUMERIC, " +
                "     ol_comments18 VARCHAR, " +
                "     i_id19 NUMERIC, " +
                "     i_title19 VARCHAR, " +
                "     i_publisher19 VARCHAR, " +
                "     i_cost19 NUMERIC, " +
                "     ol_qty19 NUMERIC, " +
                "     ol_discount19 NUMERIC, " +
                "     ol_comments19 VARCHAR, " +
                "     i_id20 NUMERIC, " +
                "     i_title20 VARCHAR, " +
                "     i_publisher20 VARCHAR, " +
                "     i_cost20 NUMERIC, " +
                "     ol_qty20 NUMERIC, " +
                "     ol_discount20 NUMERIC, " +
                "     ol_comments20 VARCHAR )";
            ResultSet rs = st.executeQuery(query);
            rs.next();
            c_fname = rs.getString(1);
            c_lname = rs.getString(2);
            c_phone = rs.getString(3);
            c_email = rs.getString(4);
            o_id = rs.getString(5);
            o_date = rs.getString(6);
            o_sub_total = rs.getString(7);
            o_tax = rs.getString(8);
            o_total = rs.getString(9);
            o_ship_type = rs.getString(10);
            o_ship_date = rs.getString(11);
            o_status = rs.getString(12);
            cx_type = rs.getString(13);
            cx_auth_id = rs.getString(14);
            bill_addr_street1 = rs.getString(15);
            bill_addr_street2 = rs.getString(16);
            bill_addr_city = rs.getString(17);
            bill_addr_state = rs.getString(18);
            bill_addr_zip = rs.getString(19);
            bill_co_name = rs.getString(20);
            ship_addr_street1 = rs.getString(21);
            ship_addr_street2 = rs.getString(22);
            ship_addr_city = rs.getString(23);
            ship_addr_state = rs.getString(24);
            ship_addr_zip = rs.getString(25);
            ship_co_name = rs.getString(26);
            count = rs.getInt(27);
            i_id = new String[count];
            i_title = new String[count];
            i_publisher = new String[count];
            i_cost = new String[count];
            ol_qty = new String[count];
            ol_discount = new String[count];
            ol_comments = new String[count];
            for (int i = 0, j = 28; i < count; i++) {
                i_id[i] = rs.getString(j++);
                i_title[i] = rs.getString(j++);
                i_publisher[i] = rs.getString(j++);
                i_cost[i] = rs.getString(j++);
                ol_qty[i] = rs.getString(j++);
                ol_discount[i] = rs.getString(j++);
                ol_comments[i] = rs.getString(j++);
            }
            rs.close();
            st.close();
            con.commit();
            con.close();
         } catch (SQLException e) {
            e.printStackTrace();
            doError(request, response, query);
            return;
         }

	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Order Display Page</title>\n" +
            "<style type=\"text/css\">\n" +
            "h1 { text-align: center }\n" +
            "h2 { text-align: center }\n" +
            "h3 { text-align: center }\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "<h1>OSDL Web Commerce Workload (DBT-1)</h1>\n" +
            "<hr />\n" +
            "<h2>Ordery Display Page</h2>\n" +
            "<hr />\n" +
            "<p>\n" +
            "Order ID: " + o_id + "<br />\n" +
            "Authorization ID: " + cx_auth_id + "<br />\n" +
            "Order Placed on = " + o_date + "<br />\n" +
            "Shipping Type: " + o_ship_type + "<br/>\n" +
            "Ship Date: " + o_ship_date + "<br/>\n" +
            "Order Subtotal: $" + o_sub_total + "<br/>\n" +
            "Order Tax: $" + o_tax + "<br/>\n" +
            "Order Total: $" + o_total + "<br/>\n" +
            "</p>\n" +
            "<p align=\"center\">\n" +
            "<table border=\"0\" width=\"80%\">\n" +
            "<tr>\n" +
            "<th>Bill To:</th>\n" +
            "<th>Ship To:</th>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td colspan=\"2\"><strong>" + c_fname + " " + c_lname +
                "</strong></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td width=\"50%\">" + bill_addr_street1 + "<br />\n" +
                bill_addr_street2 + "<br />\n" +
                bill_addr_city + "<br />\n" +
                bill_addr_state + "<br />\n" +
                bill_addr_zip + "<br />\n" +
                bill_co_name + "<br />\n" +
                "Email: " + c_email + "<br />\n" +
                "Phone: " + c_phone + "<br />\n" +
                "Credit Card Type: " + cx_type + "<br />\n" +
                "Order Status: " + o_status + "</td>\n" +
            "<td width=\"50%\" valign=\"top\">" +
                ship_addr_street1 + "<br />\n" +
                ship_addr_street2 + "<br />\n" +
                ship_addr_city + "<br />\n" +
                ship_addr_state + "<br />\n" +
                ship_addr_zip + "<br />\n" +
                ship_co_name + "</td>\n" +
            "</tr>\n" +
            "</table>\n" +
            "<table border=\"1\" cellpadding=\"5\">\n" +
            "<tr>\n" +
            "<th>Item #</th>\n" +
            "<th>Title</th>\n" +
            "<th>Cost</th>\n" +
            "<th>Qty</th>\n" +
            "<th>Discount</th>\n" +
            "<th>Comment</th>\n" +
            "</tr>\n";
        for (int i = 0; i < count; i++) {
            html +=
                "<tr>\n" +
                "<td>" + i_id[i] + "</td>\n" +
                "<td><strong>Title:" + i_title[i] +
                    "</strong><br />\n<em>Publisher: " + i_publisher[i] +
                    "</em></td>\n" +
                "<td>$" + i_cost[i] + "</td>\n" +
                "<td>" + ol_qty[i] + "</td>\n" +
                "<td>$" + ol_discount[i] + "</td>\n" +
                "<td>" + ol_comments[i] + "</td>\n" +
                "</tr>\n";
        }
        html +=
            "</table>\n" +
            "<a href=\"" + SearchRequestInteraction + "?sc_id=" +
                    sc_id + "&c_id=" + c_id + "\">" +
                "<img src=\"search.gif\" alt=\"Search\" " +
                    "border=\"0\" width=\"120\" height=\"30\"></a>" +
            "<a href=\"" + HomeInteraction + "?sc_id=" + sc_id +
                    "&c_id=" + c_id + "\">" +
                "<img src=\"home.gif\" alt=\"Home\" border=\"0\" " +
                    "width=\"120\" height=\"30\"></a>\n" +
            "</p>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     * Order Inquiry interaction.
     * Clause 2.8
     */
    private void doOrderInquiry(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        /* Data from the request. */
        String c_id = request.getParameter("c_id");
        String sc_id = request.getParameter("sc_id");
        if (c_id == null) {
            c_id = "0";
        }
        if (sc_id == null) {
            sc_id = "0";
        }

        /* Data from the database. */
        String c_uname = "";

        Connection con = null;
        String query = "";
        if (!c_id.equals("0")) {
            try {
                con = source.getConnection();
                con.setAutoCommit(false);

                CallableStatement proc = con.prepareCall(
                    "{ ? = call order_inquiry( ? ) }");
                proc.registerOutParameter(1, Types.VARCHAR);
                proc.setString(2, c_id);
                proc.execute();
                c_uname = proc.getString(1);
                proc.close();
                con.commit();
                con.close();
             } catch (SQLException e) {
                e.printStackTrace();
                doError(request, response, query);
                return;
             }
        }

	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Order Inquiry Page</title>\n" +
            "<style type=\"text/css\">\n" +
            "h1 { text-align: center }\n" +
            "h2 { text-align: center }\n" +
            "h3 { text-align: center }\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "<h1>OSDL Web Commerce Workload (DBT-1)</h1>\n" +
            "<hr />\n" +
            "<h2>Ordery Inquiry Page</h2>\n" +
            "<form action=\"" + OrderDisplayInteraction + "\" " +
                "method=\"get\">\n" +
            "<input type=\"hidden\" name=\"sc_id\" value=\"" + sc_id +"\">\n" +
            "<input type=\"hidden\" name=\"c_id\" value=\"" + c_id + "\">\n" +
            "<table>\n" +
            "<tr>\n" +
            "<td><strong>Username:</strong></td>\n" +
            "<td><input name=\"c_uname\" size=\"23\" value=\"" +
                c_uname +"\"></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td><strong>Password:</strong></td>\n" +
            "<td><input name=\"c_passwd\" size=\"23\" " +
                "type=\"password\"></td>\n" +
            "</tr>\n" +
            "</table>\n" +
            "<p align=\"center\">\n" +
            "<input type=\"image\" name=\"Display Last Order\" " +
                "src=\"ord_sta.gif\" height=\"30\" width=\"120\" />" +
            "<a href=\"" + SearchRequestInteraction + "?sc_id=" +
                    sc_id + "&c_id=" + c_id +"\">" +
                "<img src=\"search.gif\" alt=\"Search\" border=\"0\" " +
                    "width=\"120\" height=\"30\"></a>" +
            "<a href=\"" + HomeInteraction + "?sc_id=" + sc_id +
                    "&c_id=" + c_id +"\">" +
                "<img src=\"home.gif\" alt=\"Home\" border=\"0\" " +
                    "width=\"120\" height=\"30\"></a>" +
            "</p>\n" +
            "</form>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     * Product Detail interaction.
     * Clause 2.14
     */
    private void doProductDetail(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        /* Data from the request. */
        String c_id = request.getParameter("c_id");
        String sc_id = request.getParameter("sc_id");
        String i_id = request.getParameter("i_id");
        if (c_id == null) {
            c_id = "0";
        }
        if (sc_id == null) {
            sc_id = "0";
        }
        if (i_id == null) {
            doError(request, response, "No i_id.");
            return;
        }

        /* Data from the database. */
        String i_title = "";
        String a_fname = "";
        String a_lname = "";
        String i_pub_date = "";
        String i_publisher = "";
        String i_subject = "";
        String i_desc = "";
        String i_image = "";
        String i_cost = "";
        String i_srp = "";
        String i_avail = "";
        String i_isbn = "";
        String i_page = "";
        String i_backing = "";
        String i_dimensions = "";

        Connection con = null;
        String query = "";
        try {
            con = source.getConnection();
            con.setAutoCommit(false);

            Statement st = con.createStatement();
            st.setFetchSize(1);
            query =
                "SELECT product_detail.* " +
                "FROM product_detail( " + i_id + " )" +
                "  AS ( i_title VARCHAR, " +
                "       a_fname VARCHAR, " +
                "       a_lname VARCHAR, " +
                "       i_pub_date VARCHAR, " +
                "       i_publisher VARCHAR, " +
                "       i_subject VARCHAR, " +
                "       i_desc VARCHAR, " +
                "       i_image NUMERIC, " +
                "       i_cost NUMERIC, " +
                "       i_srp NUMERIC, " +
                "       i_avail VARCHAR, " +
                "       i_isbn VARCHAR, " +
                "       i_page NUMERIC, " +
                "       i_backing VARCHAR, " +
                "       i_dimensions VARCHAR)";
            ResultSet rs = st.executeQuery(query);
            rs.next();
            i_title = rs.getString(1);
            a_fname = rs.getString(2);
            a_lname = rs.getString(3);
            i_pub_date = rs.getString(4);
            i_publisher = rs.getString(5);
            i_subject = rs.getString(6);
            i_desc = rs.getString(7);
            i_image = rs.getString(8);
            i_cost = rs.getString(9);
            i_srp = rs.getString(10);
            i_avail = rs.getString(11);
            i_isbn = rs.getString(12);
            i_page = rs.getString(13);
            i_backing = rs.getString(14);
            i_dimensions = rs.getString(15);
            rs.close();
            st.close();
            con.commit();
            con.close();
         } catch (SQLException e) {
            e.printStackTrace();
            doError(request, response, query);
            return;
         }

	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Product Detail Page</title>\n" +
            "<style type=\"text/css\">\n" +
            "h1 { text-align: center }\n" +
            "h2 { text-align: center }\n" +
            "h3 { text-align: center }\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "<h1>OSDL Web Commerce Workload (DBT-1)</h1>\n" +
            "<img align=\"bottom\" height=\"67\" " +
                "src=\"tpclogo.gif\" " + "width=\"288\" />\n" +
            "<h2>Product Detail Page</h2>\n" +
            "<h2>Title: " + i_title + "</h2>\n " +
            "<p>Author: " + a_fname + " " + a_lname + "<br />\n" +
            "Subject: " + i_subject + "</p>\n" +
            "<p>" +
            "<img align=\"right\" height=\"200\" src=\"" +
                 i_image + ".jpg\" width=\"200\" />" +
            "Description: <em>" + i_desc + "</em></p>\n" +
            "<p><blockquote><strong>Suggested Retail: $" + i_srp +
                "</strong><br />\n" +
            "<strong>Our Price: $" + i_cost + "</strong><br />\n" +
            "<strong>You Save: $" +
                Float.toString(Float.parseFloat(i_srp) -
                    Float.parseFloat(i_cost)) +
                "</strong></blockquote></p>" +
            "<dl>\n" +
            "<dt>Backing: " + i_backing + ", " + i_page +
                " pages<br />\n" +
            "Published by " + i_publisher + "<br />\n" +
            "Publication date: " + i_pub_date + "<br />\n" +
            "Avail date: " + i_avail + "<br />\n" +
            "Dimensions (in inches): " + i_dimensions + "<br />\n" +
            "ISBN: " + i_isbn + "<br />\n" +
            "</dt>\n" +
            "</dl>\n" +
            "<p align=\"center\">\n" +
            "<a href=\"" + ShoppingCartInteraction +
                    "?add_flag=y&i_id=" + i_id +
                    "&i_title=" + i_title + "&i_srp=" + i_srp +
                    "&i_cost=" + i_cost + "&i_backing=" +
                    i_backing + "&sc_id=" + sc_id + "&c_id=" +
                    c_id + "&QTY=1\">" +
                "<img src=\"add.gif\" alt=\"Add to Basket\" " +
                    "border=\"0\" width=\"120\" height=\"30\" /></a>" +
            "<a href=\"" + SearchRequestInteraction +
                    "?sc_id=" + sc_id + "&c_id=" + c_id + "\">" +
                "<img src=\"search.gif\" alt=\"Search\" border=\"0\" " +
                    "width=\"120\" height=\"30\" /></a>" +
            "<a href=\"" + HomeInteraction + "?sc_id=" + sc_id +
                    "&c_id=" + c_id + "\">" +
                "<img src=\"home.gif\" alt=\"Home\" border=\"0\" " +
                    "width=\"120\" height=\"30\" /></a>" +
            "<a href=\"" + AdminRequestInteraction + "?i_id=" +
                    i_id + "&sc_id=" + sc_id + "&c_id=" + c_id + "\">" +
                "<img src=\"update.gif\" alt=\"Update\" border=\"0\" " +
                    "width=\"120\" height=\"30\" /></a>" +
            "</p>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    private String getPromotionalProcessing(String c_id, String sc_id,
            String[] pp_i_id, String[] pp_t_id) 
        throws IOException
    {
        String html =
            "<table border=\"0\" width=\"660\">\n" +
            "<tr align=\"center\" valign=\"top\">\n" +
            "<td colspan=\"5\"><b>Click on one of our latest " +
                "books to find out more!</b></td>\n" +
            "</tr>\n" +
            "<tr align=\"center\" valign=\"top\">\n" +
            "<td><a href=\"" + ProductDetailInteraction +
                "?i_id=" + pp_i_id[0] + "&sc_id=" + sc_id + "&c_id=" + c_id +
                "\"><img src=\"" + pp_t_id[0] +
                ".jpg\" alt=\"Book #" + pp_i_id[0] + "\" width=\"100\" " +
                "height=\"150\" /></a></td>\n" +
            "<td><a href=\"" + ProductDetailInteraction +
                "?i_id=" + pp_i_id[1] + "&sc_id=" + sc_id + "&c_id=" + c_id +
                "\"><img src=\"" + pp_t_id[1] +
                ".jpg\" alt=\"Book #" + pp_i_id[1] + "\" width=\"100\" " +
                "height=\"150\" /></a></td>\n" +
            "<td><a href=\"" + ProductDetailInteraction +
                "?i_id=" + pp_i_id[2] + "&sc_id=" + sc_id + "&c_id=" + c_id +
                "\"><img src=\"" + pp_t_id[2] +
                ".jpg \" alt=\"Book #" + pp_i_id[2] + "\" width=\"100\" " +
                "height=\"150\" /></a></td>\n" +
            "<td><a href=\"" + ProductDetailInteraction +
                "?i_id=" + pp_i_id[3] + "&sc_id=" + sc_id + "&c_id=" + c_id +
                "\"><img src=\"" + pp_t_id[3] +
                ".jpg \" alt=\"Book #" + pp_i_id[3] + "\" width=\"100\" " +
                "height=\"150\" /></a></td>\n" +
            "<td><a href=\"" + ProductDetailInteraction +
                "?i_id=" + pp_i_id[4] + "&sc_id=" + sc_id + "&c_id=" + c_id +
                "\"><img src=\"" + pp_t_id[4] +
                ".jpg\" alt=\"Book #" + pp_i_id[4] +
                "\" width=\"100\" height=\"150\" /></a></td>" +
            "</tr>\n" +
            "</table>\n";
        return html;
    }

    /**
     * Shopping Cart interaction.
     * Clause 2.4
     */
    private void doShoppingCart(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        float sc_sub_total = 0;

        /* Data from the request. */
        String c_id = request.getParameter("c_id");
        String sc_id = request.getParameter("sc_id");
        String add_flag = request.getParameter("add_flag");
        String submit = request.getParameter("submit");
        String single_i_id = "";
        if (c_id == null) {
            c_id = "0";
        }
        if (sc_id == null) {
            sc_id = "0";
        }

        /* Only one of these can be null. */
        if (add_flag == null && submit == null) {
            doError(request, response, "No add_flag or submit.");
            return;
        }

        /* Make sure add_flag has a valid value. */
        if (add_flag != null) {
            if (add_flag.equals("y")) {
                add_flag = "1";
            } else if (add_flag.equals("n")) {
                add_flag = "0";
            }
        } else {
            add_flag = "0";
        }

        /* Add a random item to the shopping cart if it is empty. */
        int count = 0;
        String[] qty = request.getParameterValues("qty");
        String[] i_id = request.getParameterValues("i_id");
        if (i_id == null && add_flag.equals("0")) {
            single_i_id = Integer.toString(random.nextInt(items));
        } else {
            single_i_id = request.getParameter("i_id");
            if (single_i_id == null) {
                single_i_id = "0";
            }
        }
        if (i_id != null) {
            count = i_id.length;
        }

        /* Data from the database. */
        String[] pp_i_id = new String[] { "", "", "", "", "" };
        String[] pp_t_id = new String[] { "", "", "", "", "" };
        String[] scl_i_id;
        String[] scl_title;
        String[] scl_cost;
        String[] scl_srp;
        String[] scl_backing;
        String[] scl_qty;

        Connection con = null;
        String query = "";
        try {
            con = source.getConnection();
            con.setAutoCommit(false);

            Statement st = con.createStatement();
            st.setFetchSize(1);
            query = "SELECT shopping_cart.* " +
                "FROM shopping_cart ( " + c_id + ", " + sc_id +
                    ", " + Integer.toString(count) +
                    ", " + add_flag + ", " + single_i_id +
                    ", " + Integer.toString(
                        random.nextInt(items) + 1) +
                    ", '{ ";
            if (i_id != null) {
                query = query.concat(i_id[0]);
            } else {
                query = query.concat("0");
            }
            for (int i = 1; i < count; i ++) {
                query = query.concat(", " + i_id[i]);
            }
            for (int i = count; i < 20; i++) {
                query = query.concat(", 0");
            }
            query = query.concat(" }', '{ ");
            if (qty != null) {
                query = query.concat(qty[0]);
            } else {
                query = query.concat("0");
            }
            for (int i = 1; i < count; i ++) {
                query = query.concat(", " + qty[i]);
            }
            for (int i = count; i < 20; i++) {
                query = query.concat(", 0");
            }
            query = query.concat(
                "}' ) " +
                "AS ( sc_id NUMERIC, " +
                "     itemcount NUMERIC, " +
                "     pp_i_id1 NUMERIC, " +
                "     pp_t_id1 NUMERIC, " +
                "     pp_i_id2 NUMERIC, " +
                "     pp_t_id2 NUMERIC, " +
                "     pp_i_id3 NUMERIC, " +
                "     pp_t_id3 NUMERIC, " +
                "     pp_i_id4 NUMERIC, " +
                "     pp_t_id4 NUMERIC, " +
                "     pp_i_id5 NUMERIC, " +
                "     pp_t_id5 NUMERIC, " +
                "     scl_i_id1 NUMERIC, " +
                "     scl_title1 VARCHAR, " +
                "     scl_cost1 NUMERIC, " +
                "     scl_srp1 NUMERIC, " +
                "     scl_backing1 VARCHAR, " +
                "     scl_qty1 NUMERIC, " +
                "     scl_i_id2 NUMERIC, " +
                "     scl_title2 VARCHAR, " +
                "     scl_cost2 NUMERIC, " +
                "     scl_srp2 NUMERIC, " +
                "     scl_backing2 VARCHAR, " +
                "     scl_qty2 NUMERIC, " +
                "     scl_i_id3 NUMERIC, " +
                "     scl_title3 VARCHAR, " +
                "     scl_cost3 NUMERIC, " +
                "     scl_srp3 NUMERIC, " +
                "     scl_backing3 VARCHAR, " +
                "     scl_qty3 NUMERIC, " +
                "     scl_i_id4 NUMERIC, " +
                "     scl_title4 VARCHAR, " +
                "     scl_cost4 NUMERIC, " +
                "     scl_srp4 NUMERIC, " +
                "     scl_backing4 VARCHAR, " +
                "     scl_qty4 NUMERIC, " +
                "     scl_i_id5 NUMERIC, " +
                "     scl_title5 VARCHAR, " +
                "     scl_cost5 NUMERIC, " +
                "     scl_srp5 NUMERIC, " +
                "     scl_backing5 VARCHAR, " +
                "     scl_qty5 NUMERIC, " +
                "     scl_i_id6 NUMERIC, " +
                "     scl_title6 VARCHAR, " +
                "     scl_cost6 NUMERIC, " +
                "     scl_srp6 NUMERIC, " +
                "     scl_backing6 VARCHAR, " +
                "     scl_qty6 NUMERIC, " +
                "     scl_i_id7 NUMERIC, " +
                "     scl_title7 VARCHAR, " +
                "     scl_cost7 NUMERIC, " +
                "     scl_srp7 NUMERIC, " +
                "     scl_backing7 VARCHAR, " +
                "     scl_qty7 NUMERIC, " +
                "     scl_i_id8 NUMERIC, " +
                "     scl_title8 VARCHAR, " +
                "     scl_cost8 NUMERIC, " +
                "     scl_srp8 NUMERIC, " +
                "     scl_backing8 VARCHAR, " +
                "     scl_qty8 NUMERIC, " +
                "     scl_i_id9 NUMERIC, " +
                "     scl_title9 VARCHAR, " +
                "     scl_cost9 NUMERIC, " +
                "     scl_srp9 NUMERIC, " +
                "     scl_backing9 VARCHAR, " +
                "     scl_qty9 NUMERIC, " +
                "     scl_i_id10 NUMERIC, " +
                "     scl_title10 VARCHAR, " +
                "     scl_cost10 NUMERIC, " +
                "     scl_srp10 NUMERIC, " +
                "     scl_backing10 VARCHAR, " +
                "     scl_qty10 NUMERIC, " +
                "     scl_i_id11 NUMERIC, " +
                "     scl_title11 VARCHAR, " +
                "     scl_cost11 NUMERIC, " +
                "     scl_srp11 NUMERIC, " +
                "     scl_backing11 VARCHAR, " +
                "     scl_qty11 NUMERIC, " +
                "     scl_i_id12 NUMERIC, " +
                "     scl_title12 VARCHAR, " +
                "     scl_cost12 NUMERIC, " +
                "     scl_srp12 NUMERIC, " +
                "     scl_backing12 VARCHAR, " +
                "     scl_qty12 NUMERIC, " +
                "     scl_i_id13 NUMERIC, " +
                "     scl_title13 VARCHAR, " +
                "     scl_cost13 NUMERIC, " +
                "     scl_srp13 NUMERIC, " +
                "     scl_backing13 VARCHAR, " +
                "     scl_qty13 NUMERIC, " +
                "     scl_i_id14 NUMERIC, " +
                "     scl_title14 VARCHAR, " +
                "     scl_cost14 NUMERIC, " +
                "     scl_srp14 NUMERIC, " +
                "     scl_backing14 VARCHAR, " +
                "     scl_qty14 NUMERIC, " +
                "     scl_i_id15 NUMERIC, " +
                "     scl_title15 VARCHAR, " +
                "     scl_cost15 NUMERIC, " +
                "     scl_srp15 NUMERIC, " +
                "     scl_backing15 VARCHAR, " +
                "     scl_qty15 NUMERIC, " +
                "     scl_i_id16 NUMERIC, " +
                "     scl_title16 VARCHAR, " +
                "     scl_cost16 NUMERIC, " +
                "     scl_srp16 NUMERIC, " +
                "     scl_backing16 VARCHAR, " +
                "     scl_qty16 NUMERIC, " +
                "     scl_i_id17 NUMERIC, " +
                "     scl_title17 VARCHAR, " +
                "     scl_cost17 NUMERIC, " +
                "     scl_srp17 NUMERIC, " +
                "     scl_backing17 VARCHAR, " +
                "     scl_qty17 NUMERIC, " +
                "     scl_i_id18 NUMERIC, " +
                "     scl_title18 VARCHAR, " +
                "     scl_cost18 NUMERIC, " +
                "     scl_srp18 NUMERIC, " +
                "     scl_backing18 VARCHAR, " +
                "     scl_qty18 NUMERIC, " +
                "     scl_i_id19 NUMERIC, " +
                "     scl_title19 VARCHAR, " +
                "     scl_cost19 NUMERIC, " +
                "     scl_srp19 NUMERIC, " +
                "     scl_backing19 VARCHAR, " +
                "     scl_qty19 NUMERIC, " +
                "     scl_i_id20 NUMERIC, " +
                "     scl_title20 VARCHAR, " +
                "     scl_cost20 NUMERIC, " +
                "     scl_srp20 NUMERIC, " +
                "     scl_backing20 VARCHAR, " +
                "     scl_qty20 NUMERIC )");
            ResultSet rs = st.executeQuery(query);
            rs.next();
            sc_id = rs.getString(1);
            count = rs.getInt(2);
            for (int i = 0, j = 3; i < 5; i++) {
                pp_i_id[i] = rs.getString(j++);
                pp_t_id[i] = rs.getString(j++);
            }
            scl_i_id = new String[count];
            scl_title = new String[count];
            scl_cost = new String[count];
            scl_srp = new String[count];
            scl_backing = new String[count];
            scl_qty = new String[count];
            for (int i = 0, j = 13; i < count; i++) {
                scl_i_id[i] = rs.getString(j++);
                scl_title[i] = rs.getString(j++);
                scl_cost[i] = rs.getString(j++);
                scl_srp[i] = rs.getString(j++);
                scl_backing[i] = rs.getString(j++);
                scl_qty[i] = rs.getString(j++);

                sc_sub_total += Float.parseFloat(scl_srp[i])
                    * Float.parseFloat(scl_qty[i]);
            }
            rs.close();
            st.close();
            con.commit();
            con.close();
         } catch (SQLException e) {
            e.printStackTrace();
            doError(request, response, query);
            return;
         }

	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Shopping Cart Page</title>\n" +
            "<style type=\"text/css\">\n" +
            "h1 { text-align: center }\n" +
            "h2 { text-align: center }\n" +
            "h3 { text-align: center }\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "<h1>OSDL Web Commerce Workload (DBT-1)</h1>\n" +
            "<hr />\n" +
            "<p align=\"center\">\n" +
            "<img src=\"tpclogo.gif\" align=\"bottom\" " +
            "</p>\n" +
            "<h2>Shopping Cart Page</h2>\n";
        html += getPromotionalProcessing(c_id, sc_id, pp_i_id, pp_t_id);
        html +=
            "<form action=\"" + Adjustment +"\" method=\"get\">\n" +
            "<input type=\"hidden\" name=\"sc_id\" value=\"" + sc_id +"\">\n" +
            "<input type=\"hidden\" name=\"c_id\" value=\"" + c_id + "\">\n" +
            "<table border=\"0\">\n" +
            "<tr>\n" +
            "<th>Qty</th><th>Product</th>\n" +
            "</tr>\n";
        for (int i = 0; i < count; i++) {
            html +=
                "<tr>\n" +
                "<td valign=\"top\"><input type=\"hidden\" " +
                    "name=\"i_id\" value=\"" + scl_i_id[i] + "\"><input " +
                    "name=\"qty\" value=\"" + scl_qty[i] +
                    "\" size=\"3\"></td>\n" +
                "<td valign=\"top\">\n" +
                "<em>" + scl_title[i] + "</em> Backing: " +
                    scl_backing[i] + "<br />\n" +
                "SRP: $" + scl_srp[i] +", <strong>Your " +
                    "Price: $" + scl_cost[i] + "</strong>\n" +
                "</td>\n" +
                "</tr>\n";
        }
        html +=
            "</table>\n" +
            "<em>Subtotal Price: $" +
                Float.toString(sc_sub_total) + "</em><br />\n" +
            "<em>Last Updated: </em><br />\n" +
            "<p>\n" +
            "<input type=\"image\" name=\"submit\" " +
                "value=\"" + ShoppingCartCheckout + "\" " +
                "src=\"checkout.gif\" height=\"30\" " + "width=\"120\">" +
            "<a href=\"" + HomeInteraction + "?sc_id=" + sc_id +
                    "&c_id=" + c_id + "\">\n" +
                "<img src=\"home.gif\" height=\"30\" width=\"120\" " +
                    "alt=\"Home\" border=\"0\"></a>\n" +
            "</p>\n" +
            "<p>\n" +
            "If you have changed the quantities and/or taken " +
            "anything out of your shopping cart, click here to " +
            "refresh your shopping cart:" +
            "<input type=\"image\" name=\"submit\" " +
                "value=\"" + ShoppingCartRefresh + "\" " +
                "src=\"refresh.gif\" height=\"30\" width=\"120\">" +
            "</p>\n" +
            "</form>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     * Search Request interaction.
     * Clause 2.10
     */
    private void doSearchRequest(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        /* Data from the request. */
        String c_id = request.getParameter("c_id");
        String sc_id = request.getParameter("sc_id");
        if (c_id == null) {
            c_id = "0";
        }
        if (sc_id == null) {
            sc_id = "0";
        }

        /* Data from the database. */
        String[] pp_i_id = new String[] { "", "", "", "", "" };
        String[] pp_t_id = new String[] { "", "", "", "", "" };

        Connection con = null;
        String query = "";
        try {
            con = source.getConnection();
            con.setAutoCommit(false);

            Statement st = con.createStatement();
            st.setFetchSize(1);
            query =
                "SELECT GetPromoImages.* " +
                "FROM GetPromoImages( "+ Integer.toString(
                    random.nextInt(items) + 1) + " ) " +
                "AS ( pp_i_id1 NUMERIC, " +
                "     pp_t_id1 NUMERIC, " +
                "     pp_i_id2 NUMERIC, " +
                "     pp_t_id2 NUMERIC, " +
                "     pp_i_id3 NUMERIC, " +
                "     pp_t_id3 NUMERIC, " +
                "     pp_i_id4 NUMERIC, " +
                "     pp_t_id4 NUMERIC, " +
                "     pp_i_id5 NUMERIC, " +
                "     pp_t_id5 NUMERIC )";
            ResultSet rs = st.executeQuery(query);
            rs.next();
            for (int i = 0, j = 1; i < 5; i++) {
                pp_i_id[i] = rs.getString(j++);
                pp_t_id[i] = rs.getString(j++);
            }
            rs.close();
            st.close();
            con.commit();
            con.close();
         } catch (SQLException e) {
            e.printStackTrace();
            doError(request, response, query);
            return;
         }

	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Search Request Page</title>\n" +
            "<style type=\"text/css\">\n" +
            "h1 { text-align: center }\n" +
            "h2 { text-align: center }\n" +
            "h3 { text-align: center }\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "<h1>OSDL Web Commerce Workload (DBT-1)</h1>\n" +
            "<hr />\n" +
            "<p align=\"center\">\n" +
            "<img src=\"tpclogo.gif\" align=\"bottom\" " +
                "border=\"0\" width=\"288\" height=\"67\">\n " +
            "</p>\n" +
            "<h2>Search Request Page</h2>\n";
        html += getPromotionalProcessing(c_id, sc_id, pp_i_id, pp_t_id);
        html +=
            "<form action=\"" + SearchResultsInteraction +
                "\" method=\"get\">\n" +
            "<input type=\"hidden\" name=\"sc_id\" value=\""+ sc_id + "\" />" +
            "<input type=\"hidden\" name=\"c_id\" value=\""+ c_id + "\" />" +
            "<table>\n" +
            "<tr>\n" +
            "<td align=\"right\"><strong>Search by:</strong></td>\n" +
            "<td width=\"100\"></td>\n" +
            "</tr>\n" +
            "<tr>\n" +
            "<td align=\"right\">\n" +
            "<select name=\"type\" size=\"1\">\n" +
            "<option selected=\"selected\" " +
                "value=\"author\">Author</option>\n" +
            "<option value=\"title\">Title</option>\n" +
            "<option value=\"subject\">Subject</option>\n" +
            "</select></td>\n" +
            "<td><input name=\"field\" size=\"30\"></td>\n" +
            "</tr>\n" +
            "</table>\n" +
            "<p align=\"center\">\n" +
            "<input type=\"image\" name=\"search\" " +
                "src=\"submit.gif\" height=\"30\" width=\"120\" />" +
            "<a href=\"" + HomeInteraction + "?sc_id=" + sc_id +
                "&c_id=" + c_id + "\">\n" +
            "<img src=\"home.gif\" alt=\"Home\" border=\"0\" " +
                "width=\"120\" height=\"30\"></a>" +
            "<a href=\"" + ShoppingCartInteraction +
                "?add_flag=n&sc_id=" + sc_id + "&c_id=" +
                c_id + "\"><img src=\"cart.gif\" " +
                "alt=\"Shopping Cart\" border=\"0\" " +
                "width=\"120\" height=\"30\"></a>" +
            "</p>\n" +
            "</form>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     * Search Result interaction.
     * Clause 2.11
     */
    private void doSearchResults(HttpServletRequest request,
            HttpServletResponse response)
        throws ServletException, IOException
    {
        /* Data from the request. */
        String c_id = request.getParameter("c_id");
        String sc_id = request.getParameter("sc_id");
        String type = request.getParameter("type");
        String field = request.getParameter("field");
        if (c_id == null) {
            c_id = "0";
        }
        if (sc_id == null) {
            sc_id = "0";
        }
        if (type == null) {
            doError(request, response, "No type.");
            return;
        }
        if (field == null) {
            doError(request, response, "No field.");
            return;
        }

        /* Data from the database. */
        int count;
        String[] pp_i_id = new String[] { "", "", "", "", "" };
        String[] pp_t_id = new String[] { "", "", "", "", "" };
        String[] i_id;
        String[] i_title;
        String[] a_fname;
        String[] a_lname;

        Connection con = null;
        String query = "";
        try {
            con = source.getConnection();
            con.setAutoCommit(false);

            Statement st = con.createStatement();
            st.setFetchSize(1);
            query =
                " SELECT search_results_" + type + ".* " +
                " FROM search_results_" + type + " ( '" +
                    field + "', " + Integer.toString(
                        random.nextInt(items) + 1) +
                    " ) " +
                " AS (i_related1 NUMERIC, " +
                "     i_related2 NUMERIC, " +
                "     i_related3 NUMERIC, " +
                "     i_related4 NUMERIC, " +
                "     i_related5 NUMERIC, " +
                "     i_thumbnail1 NUMERIC, " +
                "     i_thumbnail2 NUMERIC, " +
                "     i_thumbnail3 NUMERIC, " +
                "     i_thumbnail4 NUMERIC, " +
                "     i_thumbnail5 NUMERIC, " +
                "     items NUMERIC, " +
                "     i_id1 NUMERIC, " +
                "     i_title1 VARCHAR, " +
                "     a_fname1 VARCHAR, " +
                "     a_lname1 VARCHAR, " +
                "     i_id2 NUMERIC, " +
                "     i_title2 VARCHAR, " +
                "     a_fname2 VARCHAR, " +
                "     a_lname2 VARCHAR, " +
                "     i_id3 NUMERIC, " +
                "     i_title3 VARCHAR, " +
                "     a_fname3 VARCHAR, " +
                "     a_lname3 VARCHAR, " +
                "     i_id4 NUMERIC, " +
                "     i_title4 VARCHAR, " +
                "     a_fname4 VARCHAR, " +
                "     a_lname4 VARCHAR, " +
                "     i_id5 NUMERIC, " +
                "     i_title5 VARCHAR, " +
                "     a_fname5 VARCHAR, " +
                "     a_lname5 VARCHAR, " +
                "     i_id6 NUMERIC, " +
                "     i_title6 VARCHAR, " +
                "     a_fname6 VARCHAR, " +
                "     a_lname6 VARCHAR, " +
                "     i_id7 NUMERIC, " +
                "     i_title7 VARCHAR, " +
                "     a_fname7 VARCHAR, " +
                "     a_lname7 VARCHAR, " +
                "     i_id8 NUMERIC, " +
                "     i_title8 VARCHAR, " +
                "     a_fname8 VARCHAR, " +
                "     a_lname8 VARCHAR, " +
                "     i_id9 NUMERIC, " +
                "     i_title9 VARCHAR, " +
                "     a_fname9 VARCHAR, " +
                "     a_lname9 VARCHAR, " +
                "     i_id10 NUMERIC, " +
                "     i_title10 VARCHAR, " +
                "     a_fname10 VARCHAR, " +
                "     a_lname10 VARCHAR, " +
                "     i_id11 NUMERIC, " +
                "     i_title11 VARCHAR, " +
                "     a_fname11 VARCHAR, " +
                "     a_lname11 VARCHAR, " +
                "     i_id12 NUMERIC, " +
                "     i_title12 VARCHAR, " +
                "     a_fname12 VARCHAR, " +
                "     a_lname12 VARCHAR, " +
                "     i_id13 NUMERIC, " +
                "     i_title13 VARCHAR, " +
                "     a_fname13 VARCHAR, " +
                "     a_lname13 VARCHAR, " +
                "     i_id14 NUMERIC, " +
                "     i_title14 VARCHAR, " +
                "     a_fname14 VARCHAR, " +
                "     a_lname14 VARCHAR, " +
                "     i_id15 NUMERIC, " +
                "     i_title15 VARCHAR, " +
                "     a_fname15 VARCHAR, " +
                "     a_lname15 VARCHAR, " +
                "     i_id16 NUMERIC, " +
                "     i_title16 VARCHAR, " +
                "     a_fname16 VARCHAR, " +
                "     a_lname16 VARCHAR, " +
                "     i_id17 NUMERIC, " +
                "     i_title17 VARCHAR, " +
                "     a_fname17 VARCHAR, " +
                "     a_lname17 VARCHAR, " +
                "     i_id18 NUMERIC, " +
                "     i_title18 VARCHAR, " +
                "     a_fname18 VARCHAR, " +
                "     a_lname18 VARCHAR, " +
                "     i_id19 NUMERIC, " +
                "     i_title19 VARCHAR, " +
                "     a_fname19 VARCHAR, " +
                "     a_lname19 VARCHAR, " +
                "     i_id20 NUMERIC, " +
                "     i_title20 VARCHAR, " +
                "     a_fname20 VARCHAR, " +
                "     a_lname20 VARCHAR, " +
                "     i_id21 NUMERIC, " +
                "     i_title21 VARCHAR, " +
                "     a_fname21 VARCHAR, " +
                "     a_lname21 VARCHAR, " +
                "     i_id22 NUMERIC, " +
                "     i_title22 VARCHAR, " +
                "     a_fname22 VARCHAR, " +
                "     a_lname22 VARCHAR, " +
                "     i_id23 NUMERIC, " +
                "     i_title23 VARCHAR, " +
                "     a_fname23 VARCHAR, " +
                "     a_lname23 VARCHAR, " +
                "     i_id24 NUMERIC, " +
                "     i_title24 VARCHAR, " +
                "     a_fname24 VARCHAR, " +
                "     a_lname24 VARCHAR, " +
                "     i_id25 NUMERIC, " +
                "     i_title25 VARCHAR, " +
                "     a_fname25 VARCHAR, " +
                "     a_lname25 VARCHAR, " +
                "     i_id26 NUMERIC, " +
                "     i_title26 VARCHAR, " +
                "     a_fname26 VARCHAR, " +
                "     a_lname26 VARCHAR, " +
                "     i_id27 NUMERIC, " +
                "     i_title27 VARCHAR, " +
                "     a_fname27 VARCHAR, " +
                "     a_lname27 VARCHAR, " +
                "     i_id28 NUMERIC, " +
                "     i_title28 VARCHAR, " +
                "     a_fname28 VARCHAR, " +
                "     a_lname28 VARCHAR, " +
                "     i_id29 NUMERIC, " +
                "     i_title29 VARCHAR, " +
                "     a_fname29 VARCHAR, " +
                "     a_lname29 VARCHAR, " +
                "     i_id30 NUMERIC, " +
                "     i_title30 VARCHAR, " +
                "     a_fname30 VARCHAR, " +
                "     a_lname30 VARCHAR, " +
                "     i_id31 NUMERIC, " +
                "     i_title31 VARCHAR, " +
                "     a_fname31 VARCHAR, " +
                "     a_lname31 VARCHAR, " +
                "     i_id32 NUMERIC, " +
                "     i_title32 VARCHAR, " +
                "     a_fname32 VARCHAR, " +
                "     a_lname32 VARCHAR, " +
                "     i_id33 NUMERIC, " +
                "     i_title33 VARCHAR, " +
                "     a_fname33 VARCHAR, " +
                "     a_lname33 VARCHAR, " +
                "     i_id34 NUMERIC, " +
                "     i_title34 VARCHAR, " +
                "     a_fname34 VARCHAR, " +
                "     a_lname34 VARCHAR, " +
                "     i_id35 NUMERIC, " +
                "     i_title35 VARCHAR, " +
                "     a_fname35 VARCHAR, " +
                "     a_lname35 VARCHAR, " +
                "     i_id36 NUMERIC, " +
                "     i_title36 VARCHAR, " +
                "     a_fname36 VARCHAR, " +
                "     a_lname36 VARCHAR, " +
                "     i_id37 NUMERIC, " +
                "     i_title37 VARCHAR, " +
                "     a_fname37 VARCHAR, " +
                "     a_lname37 VARCHAR, " +
                "     i_id38 NUMERIC, " +
                "     i_title38 VARCHAR, " +
                "     a_fname38 VARCHAR, " +
                "     a_lname38 VARCHAR, " +
                "     i_id39 NUMERIC, " +
                "     i_title39 VARCHAR, " +
                "     a_fname39 VARCHAR, " +
                "     a_lname39 VARCHAR, " +
                "     i_id40 NUMERIC, " +
                "     i_title40 VARCHAR, " +
                "     a_fname40 VARCHAR, " +
                "     a_lname40 VARCHAR, " +
                "     i_id41 NUMERIC, " +
                "     i_title41 VARCHAR, " +
                "     a_fname41 VARCHAR, " +
                "     a_lname41 VARCHAR, " +
                "     i_id42 NUMERIC, " +
                "     i_title42 VARCHAR, " +
                "     a_fname42 VARCHAR, " +
                "     a_lname42 VARCHAR, " +
                "     i_id43 NUMERIC, " +
                "     i_title43 VARCHAR, " +
                "     a_fname43 VARCHAR, " +
                "     a_lname43 VARCHAR, " +
                "     i_id44 NUMERIC, " +
                "     i_title44 VARCHAR, " +
                "     a_fname44 VARCHAR, " +
                "     a_lname44 VARCHAR, " +
                "     i_id45 NUMERIC, " +
                "     i_title45 VARCHAR, " +
                "     a_fname45 VARCHAR, " +
                "     a_lname45 VARCHAR, " +
                "     i_id46 NUMERIC, " +
                "     i_title46 VARCHAR, " +
                "     a_fname46 VARCHAR, " +
                "     a_lname46 VARCHAR, " +
                "     i_id47 NUMERIC, " +
                "     i_title47 VARCHAR, " +
                "     a_fname47 VARCHAR, " +
                "     a_lname47 VARCHAR, " +
                "     i_id48 NUMERIC, " +
                "     i_title48 VARCHAR, " +
                "     a_fname48 VARCHAR, " +
                "     a_lname48 VARCHAR, " +
                "     i_id49 NUMERIC, " +
                "     i_title49 VARCHAR, " +
                "     a_fname49 VARCHAR, " +
                "     a_lname49 VARCHAR, " +
                "     i_id50 NUMERIC, " +
                "     i_title50 VARCHAR, " +
                "     a_fname50 VARCHAR, " +
                "     a_lname50 VARCHAR)";
            ResultSet rs = st.executeQuery(query);
            rs.next();
            for (int i = 0, j = 1; i < 5; i++) {
                pp_i_id[i] = rs.getString(j++);
                pp_t_id[i] = rs.getString(j++);
            }
            count = rs.getInt(11);
            i_id = new String[count];
            i_title = new String[count];
            a_fname = new String[count];
            a_lname = new String[count];
            for (int i = 0, j = 12; i < count; i++) {
                i_id[i] = rs.getString(j++);
                i_title[i] = rs.getString(j++);
                a_fname[i] = rs.getString(j++);
                a_lname[i] = rs.getString(j++);
            }
            rs.close();
            st.close();
            con.commit();
            con.close();
         } catch (SQLException e) {
            e.printStackTrace();
            doError(request, response, query);
            return;
         }


	response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        String html =
            "<!DOCTYPE html " +
            "PUBLIC \"-//W3C//Dtd XHTML 1.0 Strict//EN\" " +
            "\"http://www.w3.org/tr/xhtml1/Dtd/xhtml1-strict.dtd\">\n" +
            "<html>\n" +
            "<head>\n" +
            "<title>DBT-1 Search Results Page</title>\n" +
            "<style type=\"text/css\">\n" +
            "h1 { text-align: center }\n" +
            "h2 { text-align: center }\n" +
            "h3 { text-align: center }\n" +
            "</style>\n" +
            "</head>\n" +
            "<body>\n" +
            "<h1>OSDL Web Commerce Workload (DBT-1)</h1>\n" +
            "<hr />\n" +
            "<p align=\"center\">\n" +
            "<img src=\"tpclogo.gif\" align=\"bottom\" " +
                "border=\"0\" width=\"288\" height=\"67\">\n " +
            "</p>\n" +
            "<h2>Search Request Page</h2>\n";
        html += getPromotionalProcessing(c_id, sc_id, pp_i_id, pp_t_id);
        html +=
            "<table border=\"1\" cellpadding=\"1\" cellspacing=\"1\">\n" +
            "<tr>\n" +
            "<th>Author</th>\n" +
            "<th>Title</th>\n" +
            "</tr>\n";
        for (int i = 0; i < count; i++) {
            html +=
                "<tr>\n" +
                "<td><em>" + a_fname[i] + " " + a_lname[i] + "</em></td>\n" +
                "<td><a href=\"" + ProductDetailInteraction +
                    "?i_id=" + i_id[i] + "&sc_id=" + sc_id +
                    "&c_id=" + c_id + "\">" + i_title[i] + "</a></td>\n" +
                "</tr>\n";
        }
        html +=
            "</table>\n" +
            "<p align=\"center\">\n" +
            "<a href=\"" + ShoppingCartInteraction +
                "?add_flag=n&sc_id=" + sc_id + "&c_id=" + c_id + "\">" +
            "<img src=\"cart.gif\" alt=\"Shopping Cart\" " +
                "border=\"0\" width=\"120\" height=\"30\" /></a>" +
            "<a href=\"" + SearchRequestInteraction +
                "?sc_id=" + sc_id + "&c_id=" + c_id +"\">" +
            "<img src=\"search.gif\" alt=\"Search\" " +
                "border=\"0\" width=\"120\" height=\"30\" /></a>" +
            "<a href=\"" + HomeInteraction + "?sc_id=" + sc_id +
                "&c_id=" + c_id + "\">" +
            "<img src=\"home.gif\" alt=\"Home\" border=\"0\" " +
                "width=\"120\" height=\"30\">" +
            "</a>\n" +
            "</p>\n" +
            "</body>\n" +
            "</html>";
        response.setContentLength(html.length());
        out.println(html);
    }

    /**
     * getAString
     * Clause 4.6.2.2
     * A random string generator.
     */
    private String getAString(int min, int max) {
        String astring = "";
        int length = min + random.nextInt(max - min + 1);

        for (int i = 0; i < length - 1; i++) {
            astring = astring.concat(String.valueOf(
                AStringSet.charAt(random.nextInt(
                    AStringSet.length()))));
        }
        return astring;
    }

    /**
     *
     */
    public String getServletInfo() {
        return "Database Test 1";
    }

    public void init() throws ServletException {
        items = 1000;

         source.setDataSourceName("Database Test 1");
         source.setServerName("localhost");
         source.setDatabaseName("dbt1");
         source.setUser("pgsql");
         source.setPassword("pgsql");
         source.setMaxConnections(10);
    }
}
