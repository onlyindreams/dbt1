#!/bin/sh
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d DBT1 -b country.sql
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d DBT1 -b author.sql 
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d DBT1 -b address.sql 
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d DBT1 -b customer.sql 
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d DBT1 -b orders.sql 
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d DBT1 -b order_line.sql 
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d DBT1 -b cc_xacts.sql 
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d DBT1 -b item.sql 
