#
# WARNING: do not run this directly, it should be run by the main Makefile

include ../../Makefile.defs
auto_gen=
NAME=db_unixodbc.so

ifeq ($(CROSS_COMPILE),)
ODBCCFG=$(shell which odbc_config)
endif

ifneq ($(ODBCCFG),)

	DEFS += $(shell $(ODBCCFG) --cflags )
	LIBS += $(shell $(ODBCCFG) --libs)

else

	# sql.h locations (freebsd,openbsd  solaris)
	DEFS += -I$(LOCALBASE)/include

	# libodbc locations on RH/Suse, Solaris /OpenBSD, FreeBSD
	# (Debian does the right thing and puts it in /usr/lib)
	LIBS= -L$(LOCALBASE)/lib -lodbc
endif

include ../../Makefile.modules
