DEFAULT_INCLUDES = -I@top_srcdir@ -I@top_builddir@

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

dist-hook:
	echo '*** /test dist-hook *******************************'
	chmod 644 $(distdir)/*.c
	$(SED) -i \
	   -e 's/ViewObjHandler/libGAP_ViewObjHandler/g' \
	   -e 's/ExecStatus/libGAP_ExecStatus/g' \
	   -e 's/BottomLVars/libGAP_BottomLVars/g' \
	   -e 's/CollectBags/libGAP_CollectBags/g' \
	   -e 's/ReadEvalCommand/libGAP_ReadEvalCommand/g' \
	   -e 's/ReadEvalResult/libGAP_ReadEvalResult/g' \
	   -e 's/GetSymbol/libGAP_GetSymbol/g' \
	   -e 's/\([^a-zA-Z0-9]\)Symbol/\1libGAP_Symbol/g' \
	   -e 's/STATUS_END/libGAP_STATUS_END/g' \
	   -e 's/S_SEMICOLON/libGAP_S_SEMICOLON/g' \
	   -e 's/S_EOF/libGAP_S_EOF/g' \
	   $(distdir)/*.c
	echo '***************************************************'

clean-local:
	-rm -rf tmp_file.txt

