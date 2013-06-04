DEFAULT_INCLUDES = -I@top_builddir@/src -I@top_srcdir@

TESTS = test shell error_handler

check_PROGRAMS = test shell error_handler

test_SOURCES = test.c
test_CFLAGS = @GMP_CFLAGS@
test_LDADD = @top_builddir@/src/libgap.la
test_LDFLAGS = -lgmp -lm

shell_SOURCES = shell.c
shell_CFLAGS = @GMP_CFLAGS@
shell_LDADD = @top_builddir@/src/libgap.la
shell_LDFLAGS = -lgmp -lm

error_handler_SOURCES = error_handler.c
error_handler_CFLAGS = @GMP_CFLAGS@
error_handler_LDADD = @top_builddir@/src/libgap.la
error_handler_LDFLAGS = -lgmp -lm
