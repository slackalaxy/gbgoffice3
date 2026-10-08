bin_PROGRAMS = gbgoffice

gbgoffice_SOURCES = \
	database.cpp \
	history.cpp \
	translator.cpp \
	properties.cpp \
	translator_manager.cpp \
	gbgoffice_tools.cpp \
	trayicon.cpp \
	splash.cpp \
	prefsdialog.cpp \
	exam.cpp \
	workhelper.cpp \
	dictgui.cpp \
	main.cpp

noinst_HEADERS = \
	config.h \
	database.h \
	translator.h \
	translator_manager.h \
	properties.h \
	defaults.h \
	gbgoffice_tools.h \
	trayicon.h \
	prefsdialog.h \
	exam.h \
	splash.h \
	workhelper.h \
	dictgui.h \
	language_tools.h 

gbgoffice_LDADD = @LIBS@ @GTKMM_LIBS@ 

AM_CXXFLAGS = @GTKMM_CFLAGS@ 
AM_CPPFLAGS = -DDATA_DIR_CONFIG=\"$(datadir)/bgoffice/\" @CPPFLAGS@

