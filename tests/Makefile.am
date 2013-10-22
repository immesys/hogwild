## Process this file with automake to produce Makefile.in

TESTS = check_primitives check_correlation
check_PROGRAMS = check_primitives check_correlation
check_primitives_SOURCES = check_primitives.cpp $(top_builddir)/src/primitives.h $(top_builddir)/src/primitives.cpp
check_primitives_CFLAGS = @CHECK_CFLAGS@
check_primitives_LDADD = @CHECK_LIBS@

check_correlation_SOURCES = check_correlation.cpp $(top_builddir)/src/primitives.h $(top_builddir)/src/primitives.cpp $(top_builddir)/src/hw_correlation_behavioral.cpp
check_correlation_CFLAGS = @CHECK_CFLAGS@
check_correlation_LDADD = @CHECK_LIBS@

