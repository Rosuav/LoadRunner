WT3_Travel(){ // call from within Action.c.
	int rc=LR_PASS; int i=0;

	// WT3_T20_Travel_Data()
	// WT3_T21_Travel_Home()
	// WT3_T22_Travel_Search_Flight()
	// WT3_T23_Travel_Flight_Lookup()
	// WT3_T24_Find_Flight()
	// WT3_T25_Travel_Payment_Details()
	// WT3_T26_Travel_Invoice()
	// WT3_T27_Travel_Click_Book_Another()
	// WT3_T33_Travel_Check_Itinerary()

	WT3_T20_Travel_Data();
	
	// Search UseCase
	// Book UseCase
	// Itinerary UseCase
	// No check-in UseCase
	
	if( stricmp("All",LPCSTR_UseCase ) == FOUND
	||  stricmp("Search",LPCSTR_UseCase ) == FOUND
	||  stricmp("Book",LPCSTR_UseCase ) == FOUND
	){
			lr_save_string("WT3_T22_Travel_Search_Flight","pTransName");
			web_reg_find("Text=Find Flight", "Fail=NotFound", LAST);
			rc=WT3_T22_Travel_Search_Flight();
			if( rc != LR_PASS ){ return rc; }
	}

	if( stricmp("Search",LPCSTR_UseCase ) == FOUND
	){
		
			//lr_save_string("WT3_T22_Travel_Search_Flight","pTransName");
			//web_reg_find("Text=Find Flight", "Fail=NotFound", LAST);
			//rc=WT3_T22_Travel_Search_Flight();
			//if( rc != LR_PASS ){ return rc; }
			

			lr_save_string("WT3_T23_Travel_Flight_Lookup","pTransName");
			web_reg_find("Text=Flight departing from", "Fail=NotFound", LAST);
			rc=WT3_T23_Travel_Flight_Lookup();
			if( rc != LR_PASS ){ return rc; }
			
			lr_save_string("WT3_T24_Find_Flight","pTransName");
			web_reg_find("Text=Payment Details", "Fail=NotFound", LAST);
			rc=WT3_T24_Find_Flight();
			if( rc != LR_PASS ){ return rc; }
		}

	if( stricmp("All",LPCSTR_UseCase ) == FOUND
	||  stricmp("Book",LPCSTR_UseCase ) == FOUND
	){

		// TODO: Loop through several flights before checkout.
		
		for(i=1; i<2; i++){ // 1,2,3 (3 times)
			
			lr_save_string("WT3_T23_Travel_Flight_Lookup","pTransName");
			web_reg_find("Text=Flight departing from", "Fail=NotFound", LAST);
			rc=WT3_T23_Travel_Flight_Lookup();
			if( rc != LR_PASS ){ return rc; }
			
			lr_save_string("WT3_T24_Find_Flight","pTransName");
			web_reg_find("Text=Payment Details", "Fail=NotFound", LAST);
			rc=WT3_T24_Find_Flight();
			if( rc != LR_PASS ){ return rc; }
			
			lr_save_string("WT3_T25_Travel_Payment_Details","pTransName");
			web_reg_find("Text=Invoice", "Fail=NotFound", LAST);
			 rc=WT3_T25_Travel_Payment_Details();
			if( rc != LR_PASS ){ return rc; }
			
			//rc=WT3_T26_Travel_Invoice(); // does not send data to server.

			lr_save_string("WT3_T27_Travel_Click_Book_Another","pTransName");
			web_reg_find("Text=Find Flight", "Fail=NotFound", LAST);
			rc=WT3_T27_Travel_Click_Book_Another();
			if( rc != LR_PASS ){ return rc; }
				
		}//for(i=1; i<2; i++){ // 1,2,3 (3 times)
	}
		
		if( stricmp("All",LPCSTR_UseCase ) == FOUND
		||  stricmp("Book",LPCSTR_UseCase ) == FOUND
		||  stricmp("Itinerary",LPCSTR_UseCase ) == FOUND
   		){
			lr_save_string("WT3_T33_Travel_Check_Itinerary","pTransName");
			web_reg_find("Text=Itinerary", "Fail=NotFound", LAST);
			rc=WT3_T33_Travel_Check_Itinerary();			
			if( rc != LR_PASS ){ return rc; }
		}
				
		if( stricmp("All",LPCSTR_UseCase ) == FOUND
		||  stricmp("Home",LPCSTR_UseCase ) == FOUND
   		){
			lr_save_string("WT3_T21_Travel_Home","pTransName");
			web_reg_find("Text=Welcome", "Fail=NotFound", LAST);
			rc=WT3_T21_Travel_Home();
			if( rc != LR_PASS ){ return rc; }
		}
	
	return rc;
}

WT3_T20_Travel_Data(){
	
	lr_save_datetime("%m/%d/%Y", DATE_NOW   ,"parm_departDate"); // 04/14/2015 format
	lr_save_datetime("%m/%d/%Y", DATE_NOW +7,"parm_returnDate");
	
	// TODO: Vary departCity and returnCity each sub-iteration.

	return 0;
}

WT3_T21_Travel_Home(){
int rc=LR_PASS;	
	wi_start_transaction();
	web_image("Home Button", 
		"Alt=Home Button", 
		"Snapshot=t32.inf", 
		LAST);
	rc=wi_end_transaction();
	return rc;
} //WT3_T21_Travel_Home
		
WT3_T22_Travel_Search_Flight(){
int rc=LR_PASS;
	web_reg_find("Text=Find Flight", LAST);
	wi_start_transaction();
	web_image("Search Flights Button", 
		"Alt=Search Flights Button", 
		"Snapshot=t33.inf", 
		LAST);
	rc=wi_end_transaction();

	return rc;
} //WT3_T22_Travel_Search_Flight
	
WT3_T23_Travel_Flight_Lookup(){
int rc=LR_PASS;
//TODO: WT3_T23_Travel_Flight_Lookup Add Airport starting and endeing route in this function.
//	web_reg_find("Text=Flight departing from",LAST);
	  wi_start_transaction();
	web_submit_form("reservations.pl",
		"Snapshot=t34.inf",
		ITEMDATA,
		"Name=depart", "Value=Denver", ENDITEM,
		"Name=departDate", "Value={parm_departDate}", ENDITEM,
		"Name=arrive", "Value=Los Angeles", ENDITEM,
		"Name=returnDate", "Value={parm_returnDate}", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=roundtrip", "Value=<OFF>", ENDITEM,
		"Name=seatPref", "Value=None", ENDITEM,
		"Name=seatType", "Value=Coach", ENDITEM,
		"Name=findFlights.x", "Value=40", ENDITEM,
		"Name=findFlights.y", "Value=6", ENDITEM,
		LAST);
	   rc=wi_end_transaction();
	return rc;
} //WT3_T23_Travel_Flight_Lookup
	
WT3_T24_Find_Flight(){
int rc=LR_PASS;
	web_reg_find("Text=Payment Details",LAST);
	 wi_start_transaction();
	web_submit_form("reservations.pl_2", 
		"Snapshot=t35.inf", 
		ITEMDATA, 
		"Name=outboundFlight", "Value=030;251;{parm_departDate}", ENDITEM, 
		"Name=reserveFlights.x", "Value=46", ENDITEM, 
		"Name=reserveFlights.y", "Value=11", ENDITEM, 
		LAST);
	 rc=wi_end_transaction();
	return rc;
	} //WT3_T24_Find_Flight

WT3_T25_Travel_Payment_Details(){
	int rc=LR_PASS;
		
	web_reg_find("Text=Invoice",LAST);
	   wi_start_transaction();
	web_submit_form("reservations.pl_3", 
		"Snapshot=t36.inf", 
		ITEMDATA, 
		"Name=firstName", "Value=whatever", ENDITEM, 
		"Name=lastName", "Value=whatever", ENDITEM, 
		"Name=address1", "Value=whatever", ENDITEM, 
		"Name=address2", "Value=whatever", ENDITEM, 
		"Name=pass1", "Value=whatever whatever", ENDITEM, 
		"Name=creditCard", "Value=12345678", ENDITEM, 
		"Name=expDate", "Value=15/16", ENDITEM, 
		"Name=saveCC", "Value=<OFF>", ENDITEM, 
		"Name=buyFlights.x", "Value=41", ENDITEM, 
		"Name=buyFlights.y", "Value=9", ENDITEM, 
		LAST);
	  rc=wi_end_transaction();
	return rc;
	} //WT3_T25_Travel_Payment_Details

WT3_T26_Travel_Invoice(){
	int rc=LR_PASS;
	lr_start_transaction("WT3_T26_Travel_Invoice");

	// Clicking on Invoice does not cause request to server.
	
	lr_end_transaction("WT3_T26_Travel_Invoice",LR_AUTO);
	return rc;
} //WT3_T26_Travel_Invoice
	
WT3_T27_Travel_Click_Book_Another(){
	int rc=LR_PASS;
	web_reg_find("Text=Find Flight", 
		LAST);
	wi_start_transaction();
	web_submit_form("reservations.pl_4", 
		"Snapshot=t37.inf", 
		ITEMDATA, 
		"Name=Book Another.x", "Value=43", ENDITEM, 
		"Name=Book Another.y", "Value=6", ENDITEM, 
		LAST);
	rc=wi_end_transaction();
	return rc;
	} //WT3_T27_Travel_Click_Book_Another
	
	
WT3_T33_Travel_Check_Itinerary(){
	int rc=LR_PASS;
	web_reg_find("Text=Itinerary",LAST);
	wi_start_transaction();
	web_image("Itinerary Button", 
		"Alt=Itinerary Button", 
		"Snapshot=t42.inf", 
		LAST);
	rc=wi_end_transaction();
	return rc;
}//WT3_T33_Travel_Check_Itinerary	
	
