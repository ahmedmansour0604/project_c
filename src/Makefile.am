## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = project_c

project_c_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	citoyen.c citoyen.h \
	avis.c avis.h \
	parking.c parking.h \
	crud.c crud.h \
	reservation.c reservation.h


project_c_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

