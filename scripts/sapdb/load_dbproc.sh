#!/bin/sh

dbmcli -d DBT1 -u dba,dba -uSQL dbt,dbt -i create_sequence.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/getPromoImages.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/DigSyl.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/getSCSubTotal.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/addToSC.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/createSC.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/refreshSC.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/getCustInfo.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/InsertCust.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/updateSC.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/initSCItems.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/getSCDetail.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/initOrderItems.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/getOrderItems.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/home.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/buyrequest.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/buyconfirm.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/shoppingcart.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/order_inquiry.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/order_display.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/product_detail.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/admin_request.sql
/opt/sapdb/depend/bin/repmcli -d DBT1 -u dbt,dbt -b ../../storedproc/sapdb/admin_confirm.sql

cd ../../tools
./load_db_proc localhost:DBT1 dbt dbt ../storedproc/sapdb/new_products.sql
./load_db_proc localhost:DBT1 dbt dbt ../storedproc/sapdb/best_sellers.sql
./load_db_proc localhost:DBT1 dbt dbt ../storedproc/sapdb/search_results_author.sql
./load_db_proc localhost:DBT1 dbt dbt ../storedproc/sapdb/search_results_subject.sql
./load_db_proc localhost:DBT1 dbt dbt ../storedproc/sapdb/search_results_title.sql
