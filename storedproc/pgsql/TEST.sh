#!/bin/sh

psql -f test/drop_tables.sql
psql -f test/create_tables.sql
psql -f test/sequences.sql

##############################################################
#
#               Creating stored procedures
#
##############################################################
psql -f DigSyl.sql
psql -f InsertCust.sql
psql -f addToSC.sql
psql -f admin_confirm.sql
psql -f admin_request.sql
psql -f best_sellers.sql
psql -f best_sellers_new.sql
psql -f buy_confirm.sql
psql -f buy_request.sql
psql -f createSC.sql
psql -f getCustInfo.sql
psql -f getCustName.sql
psql -f getOrderItems.sql
psql -f getPromoImages.sql
psql -f getSCDetail.sql
psql -f getSCSubTotal.sql
psql -f home.sql
psql -f new_products.sql
psql -f order_display.sql
psql -f product_detail.sql
psql -f refreshSC.sql
psql -f search_results_author.sql
psql -f search_results_subject.sql
psql -f search_results_title.sql
psql -f shopping_cart.sql
psql -f updateSC.sql


##############################################################
#
#                      Tesitng all
#
##############################################################
psql -f test/test_InsertCust.sql
psql -f test/test_addToSC.sql
psql -f test/test_admin.sql
psql -f test/test_all.sh
psql -f test/test_best_sellers.sql
psql -f test/test_best_sellers_new.sql
psql -f test/test_buy_confirm.sql
psql -f test/test_buy_request.sql
psql -f test/test_getOrderItems.sql
psql -f test/test_getPromoImages.sql
psql -f test/test_getSCDetail.sql
psql -f test/test_getSCSubTotal.sql
psql -f test/test_home.sql
psql -f test/test_newproducts.sql
psql -f test/test_order_display.sql
psql -f test/test_product_detail.sql
psql -f test/test_refreshSC.sql
psql -f test/test_search_results_author.sql
psql -f test/test_search_results_subject.sql
psql -f test/test_search_results_title.sql
psql -f test/test_shopping_cart.sql
psql -f test/test_updateSC.sql
