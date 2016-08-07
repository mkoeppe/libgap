DEFAULT_INCLUDES = -I@top_builddir@

lib_LTLIBRARIES = libgap.la

libgap_la_LT_INFO = -version-info @LIBGAP_LT_VERSION@


libgap_la_SOURCES = \
  ariths.c    c_random.c  gmpints.c   objccoll.c  rational.c  system.c  \
  blister.c   c_type1.c   gvars.c     objcftl.c   read.c      tietze.c  \
  bool.c      cyclotom.c  integer.c   objects.c   records.c   vars.c    \
  calls.c     dt.c        intfuncs.c  objfgelm.c  saveload.c  vec8bit.c \
  c_filt1.c   dteval.c    intrprtr.c  objpcgel.c  scanner.c   vecffe.c  \
  c_meths1.c  exprs.c     iostream.c  objscoll.c  sctable.c   vecgf2.c  \
  code.c      finfield.c  libgap.c    opers.c     set.c       vector.c  \
  compiler.c  funcs.c     listfunc.c  permutat.c  stats.c     weakptr.c \
  compstat.c  gap.c       listoper.c  plist.c     streams.c   \
  c_oper1.c   lists.c     precord.c   string.c    \
  costab.c    gasman.c    macfloat.c  range.c     sysfiles.c \
  pperm.c     trans.c \
  profile.c

if NEED_ITANIUMOBJ
  libgap_la_SOURCES += itanium.s
endif

libgapincludedir = @includedir@/gap
libgapinclude_HEADERS = \
  ariths.h    cyclotom.h  integer.h   objcftl.h   rational.h  sysfiles.h \
  blister.h   dteval.h    intfuncs.h  objects.h   read.h      system.h   \
  bool.h      dt.h        intrprtr.h  objfgelm.h  records.h   tietze.h   \
  calls.h     exprs.h     iostream.h  objpcgel.h  saveload.h  vars.h     \
  code.h      finfield.h  objscoll.h  scanner.h   vec8bit.h              \
  compiled.h  funcs.h     listfunc.h  opers.h     sctable.h   vecffe.h   \
  compiler.h  gap.h       listoper.h  permutat.h  set.h       vecgf2.h   \
  compstat.h  gasman.h    lists.h     plist.h     stats.h     vector.h   \
  config.h    gmpints.h   macfloat.h  precord.h   streams.h   weakptr.h  \
  costab.h    gvars.h     objccoll.h  range.h     string.h               \
  pperm.h     trans.h \
  libgap.h    libgap_internal.h \
  aobjects.h  atomic.h    ffdata.h    objccoll-impl.h \
  objscoll-impl.h profile.h thread.h tls.h \
  gap_version.h


libgap_la_CFLAGS = $(AM_CFLAGS) \
  -DCONFIG_H @GMP_CFLAGS@ @SAGE_CFLAGS@

# the no-undefined is necessary for Cygwin
libgap_la_LDFLAGS = $(libgap_la_LT_INFO) -lm @GMP_LIBS@ -no-undefined


dist-hook:
	@echo '***************************************************'
	@echo '*** /src dist-hook *********************************'
	@echo '***************************************************'
	@echo '****** libGAPify'
	rm -f $(distdir)/config.h
	$(top_distdir)/scripts/libGAPify.py --modify $(distdir)
	chmod 755 $(top_distdir)/scripts $(top_distdir)/scripts/libGAPify.py
	rm -f $(top_distdir)/scripts/libGAPify.py
	cp $(top_distdir)/scripts/libGAPify_dummy.py $(top_distdir)/scripts/libGAPify.py
	@echo '****** patch version'
	echo "Version: $(PACKAGE)-$(VERSION)"
	$(SED) -i 's/SyKernelVersion = "4.dev"/SyKernelVersion = "$(VERSION)"/g' $(top_distdir)/src/system.c
	$(SED) -i 's/GAP_BUILD_VERSION  "4.dev"/GAP_BUILD_VERSION  "$(PACKAGE)-$(VERSION)"/g' $(top_distdir)/src/gap_version.h
	@echo '***************************************************'
