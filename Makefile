all: common_obj db_interface_obj dbdriver_exe appServer_exe tools_exe wgen_obj \
	datagen_exe

wgen_obj:
	cd wgen; $(MAKE)

datagen_exe:
	cd datagen; $(MAKE)

common_obj:
	cd common; $(MAKE)

db_interface_obj:
	cd interfaces/odbc; $(MAKE)

dbdriver_exe:
	cd dbdriver; $(MAKE)

appServer_exe:
	cd appServer; $(MAKE)

tools_exe:
	cd tools; $(MAKE)

clean:
	cd wgen; rm -f *.o tpcw
	cd interfaces/odbc; rm -f *.o datagen
	cd common; rm -f *.o
	cd db_interface; rm -f *.o
	cd dbdriver; rm -f *.o dbdriver_p1 dbdriver_p2
	cd appServer; rm -f *.o appServer
	cd tools; rm -f *.o odbc_test_p1 odbc_test_p2 load_db_proc results
