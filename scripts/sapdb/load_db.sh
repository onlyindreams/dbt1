#!/bin/sh
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d $SID1 -b country.sql
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d $SID1 -b author.sql 
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d $SID1 -b address.sql 
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d $SID1 -b customer.sql 
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d $SID1 -b orders.sql 
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d $SID1 -b order_line.sql 
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d $SID1 -b cc_xacts.sql 
/opt/sapdb/depend/bin/repmcli -u dbt,dbt -d $SID1 -b item.sql 
