include $(top_srcdir)/Makefile.activity

SUBDIRS = resources

if PLATFORM_WIN32
shared = -shared
no_undefined = -no-undefined
gc_libs = $(GCOMPRIS_LIBS)
dll_export = -DBOARD_DLL_EXPORT
else
shared =
no_undefined =
gc_libs =
dll_export =
endif

lib_LTLIBRARIES = \
	libphotohunter.la

libdir = $(plugindir)
INCLUDES = 	-I$(top_srcdir)/src \
	-I$(top_srcdir)/intl \
	-I$(top_srcdir)/src/goocanvas/src \
	$(GCOMPRIS_CFLAGS) \
	$(XML_CFLAGS) \
	$(dll_export)



libphotohunter_la_LDFLAGS = $(shared) $(no_undefined) -module -avoid-version $(gc_libs) $(XML_LIBS)
libphotohunter_la_LIBADD =
libphotohunter_la_SOURCES = photohunter.c

xmldir = $(pkgdatadir)/@PACKAGE_DATA_DIR@

xml_in_files = \
	photohunter.xml.in


xml_DATA = $(xml_in_files:.xml.in=.xml)

# Do not use the INTLTOOL_XML_RULE, we don't need to embed the translations
# in the file themselves. GCompris pick the translations from the po file at
# runtime.
#
$(xml_DATA): %.xml: %.xml.in
	sed -e "s/\(<\{1\}\/*\)_/\1/g" $< > $@

# Use this directive and instead of the one above to embed the translations
# in the xml files directly, this is needed for the tool gcompris2spip
#@INTLTOOL_XML_RULE@


icondir = $(pkgdatadir)/@PACKAGE_DATA_DIR@
icon_DATA = photohunter.svg

EXTRA_DIST = $(icon_DATA) ${xml_in_files} init_path.sh
CLEANFILES = $(xml_DATA)
