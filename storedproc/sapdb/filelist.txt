getPromoImages.sql:	get related items for the item.
DigSyl.sql:		generate u_name and password according to c_id
getSCSubTotal.sql:	for the given shopping_cart id, calculate sub_total according	to the cost and quantity of each item in the shopping_cart.
addToSC.sql:		add an item to the shopping_cart.
createSC.sql:		create a new shopping_cart
refreshSC.sql:		update shopping_cart_line info
getCustInfo.sql:	get customer information
InsertCust.sql:		create a new customer
updateSC.sql:		calculate and update sub_tatol, tax, ship_cost, total for the shopping cart
initSCItems.sql:	set output variables(hopefully we do not need this when bug is fixed). called by getSCDetail.sql
getSCDetail.sql:	get shopping cart line info. 
initOrderItems.sql:	set output variables(hopefully we do not need this when bug is fixed). 
getOrderItems.sql:	get order line info
home.sql:		get customer name if user is known customer
				call getPromoImages(to get related item info)
buyrequest.sql:		implement buy_request, 
			if user is a returning customer, call getCustInfo, 
			else call InserCust 
			     update shopping_cart created by shopping_cart transaction.
			call updateSC
			call getSCDetail
buyconfirm.sql:		execute buyconfirm, 
			create order record, 
			for each item in the order, create an order_line record, 
			create credit card record for this order.
			call getSCDetail
shoppingcart.sql:	execute shoppingcart
			if sc_id in UNKNOWN, call createSC
			if not refreshing shopping cart, call addToSC
			if refreshing shopping cart, call refreshSC
			call getSCDetail
			call getPromoImages
order_inquiry.sql:	return c_uname for user
order_display.sql:	get order info for the user
			call getOrderItems(to get order line info)
admin_request.sql:	implement Admin Request interaction.
admin_confirm.sql:	implement Admin Confirm interaction.
new_products.sql:	implement New Products interaction.
best_sellers.sql:	implement Best Sellers interaction.
search_results_author.sql:	implement Search Results (search by author) interaction
search_results_subject.sq:	 implement Search Results (search by subject) interaction
search_results_title.sql:	 implement Search Results (search by title) interaction
