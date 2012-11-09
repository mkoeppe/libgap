AC_PREREQ([2.66])

# Note: the version number must match the GAP version number
AC_INIT([libGAP], [4.5.6], [sage-devel@googlegroups.com])

AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR([src/gap.h])
AC_CONFIG_HEADERS([src/config.h])

AC_CONFIG_FILES([
  Makefile
  src/Makefile
  test/Makefile
])


dnl Find the GNU Multiple Precision Arithmetic Library
AC_ARG_WITH(gmp,
  [AS_HELP_STRING([--with-gmp=<path>],  
                  [prefix of GMP installation. e.g. /usr/local or /usr])],
  [GMP_PREFIX="$with_gmp"],
  [AC_CHECK_LIB([gmp], [__gmpz_init], ,
    AC_MSG_ERROR([GNU Multiple Precision Arithmetic Library not found.
    Maybe you want to call configure with the --with-gmp=<path> option?
    This tells configure where to find the GMP library and headers.
    e.g. --with-gmp=/usr/local or --with-gmp=/usr]))]
)
if test "x$GMP_PREFIX" != x ; then
  GMP_LIBS=" -L${GMP_PREFIX}/lib"
  GMP_CFLAGS=" -I${GMP_PREFIX}/include"
else
  GMP_LIBS=""
  GMP_CFLAGS=""
fi
GMP_LIBS="${GMP_LIBS} -lgmp"
AC_SUBST(GMP_LIBS)
AC_SUBST(GMP_CFLAGS)


dnl Find SAGE_LOCAL
AC_ARG_WITH(sage,
  [AS_HELP_STRING([--with-sage=<path>],  
                  [the SAGE_LOCAL path])],
  [SAGE_LOCAL_PREFIX="$with_sage"]
)
if test "x$SAGE_LOCAL_PREFIX" != x ; then
  SAGE_LOCAL="${SAGE_LOCAL_PREFIX}"
else
  SAGE_LOCAL=""
fi
AC_SUBST(SAGE_LOCAL)


# weird macros that GAP uses
AC_DEFINE_UNQUOTED([SYS_ARCH], ["sage-libGAP"], [arbitrary architecture name])
AC_DEFINE_UNQUOTED([CONFIGNAME], ["sage-libGAP"], [arbitrary name])
AC_DEFINE([HAVE_DOTGAPRC],[1],[define as 1 if the user resource file is .gaprc])
AC_DEFINE([HAVE_SLASH_SEPARATOR],[1],[if your directory separator is forward slash])

# Checks for programs.
AM_PROG_CC_C_O
AC_C_CONST
AC_C_INLINE
AC_C_BIGENDIAN
AC_CHECK_SIZEOF(void *, 4) # no space between 'void *' and ','
AC_CHECK_ALIGNOF([long])

# Checks for libraries.
LT_INIT([dlopen])

# Checks for header files.
AC_CHECK_HEADERS([math.h assert.h sys/sysmacros.h fcntl.h sys/stat.h mach/mach.h sys/mman.h])
AC_CHECK_HEADERS([sgtty.h stdlib.h string.h sys/ioctl.h sys/param.h sys/time.h sys/resource.h])
AC_CHECK_HEADERS([termio.h termios.h unistd.h signal.h stdio.h libc.h sys/times.h sys/wait.h])
AC_CHECK_HEADERS([vfork.h dirent.h errno.h setjmp.h])

AC_FUNC_VFORK
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_CHECK_FUNCS([getpseudotty _getpty getpt ptsname_r])
AC_CHECK_FUNCS([setpgid setjmp sigsetjmp sbrk])
AC_CHECK_FUNCS([rld_load])
AC_CHECK_FUNCS([times getrusage])
AC_CHECK_FUNCS([vm_allocate])
AC_CHECK_FUNCS([fork popen waitpid wait4])
AC_CHECK_FUNCS([dup2 floor memmove mkdir pow rint select strerror])
AC_CHECK_FUNCS([ttyname strerror select])
AC_CHECK_FUNCS([access stat fstat lstat unlink mkdir mkdtemp mkstemp rmdir link rename])
AC_CHECK_FUNCS([symlink readlink chmod fchmod chown fchown lchown dup dup2 mknod mkfifo])
AC_CHECK_FUNCS([socket listen accept connect bind getsockname recv recvfrom recvmsg send])
AC_CHECK_FUNCS([sendto sendmsg getsockopt setsockopt getprotobyname gethostbyname])
AC_CHECK_FUNCS([opendir closedir dirfd readdir rewinddir seekdir telldir])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_HEADER_DIRENT
AC_HEADER_MAJOR
AC_HEADER_STAT
AC_C_INLINE
AC_TYPE_SIZE_T
AC_TYPE_PID_T
AC_TYPE_SIGNAL
AC_CHECK_MEMBERS([struct stat.st_rdev])
 
# weird check for signal handling
AC_CHECK_FUNCS([signal])
AC_TYPE_SIGNAL
if test "$ac_cv_type_signal" = "void"; then
  AC_DEFINE([HAVE_SIGNAL_VOID], [1] ,[void as signal type??])
fi

dnl #########################################################################
dnl ##
dnl ## set features on systems we know for better performance
dnl ##

case "$host" in
  i386-*-* | i486-*-* | i586-*-* | i686-*-*)
    AC_DEFINE([C_STACK_ALIGN], [2], [align stack??])
    ;;
  *)
    AC_DEFINE_UNQUOTED([C_STACK_ALIGN], [$ac_cv_alignof_long], [align stack??])
    ;;
esac

case "$host" in 
  sparc-* )
    AC_DEFINE([SPARC], [1], [whether we are running on SPARC architecture])
    ;;
  ia64-* ) 
    AC_DEFINE([ITANIUM], [1], [whether we are runnig on Itanium architecture])
    ITANIUMOBJ=itanium.o
    ;;
  *-darwin* )
    AC_DEFINE([SYS_IS_DARWIN], [1], [whether we are running on OSX])
    ;;
  *)
    AC_DEFINE([SYS_IS_DARWIN], [0], [whether we are running on OSX])
    ;;
esac

AC_SUBST(ITANIUMOBJ)

AC_CYGWIN
if test "$CYGWIN" = "yes"; then
  AC_DEFINE([SYS_IS_CYGWIN32], [1], [whether we are running on Windows])
else
  AC_DEFINE([SYS_IS_CYGWIN32], [0], [whether we are running on Windows])
fi


#OUTPUT
AC_OUTPUT
