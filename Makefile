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
	cd wgen; $(MAKE) clean
	cd interfaces/odbc; $(MAKE) clean
	cd common; $(MAKE) clean
	cd interfaces/odbc; $(MAKE) clean
	cd dbdriver; $(MAKE) clean
	cd appServer; $(MAKE) clean
	cd tools; $(MAKE) clean
	cd datagen; $(MAKE) clean
