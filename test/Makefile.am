DEFAULT_INCLUDES = -I@top_builddir@

check_PROGRAMS = test shell

test_SOURCES = test.c
test_CFLAGS = @GMP_CFLAGS@
test_LDADD = @top_builddir@/src/libgap.la
test_LDFLAGS = -lgmp -lm


shell_SOURCES = shell.c
shell_CFLAGS = @GMP_CFLAGS@
shell_LDADD = @top_builddir@/src/libgap.la
shell_LDFLAGS = -lgmp -lm
