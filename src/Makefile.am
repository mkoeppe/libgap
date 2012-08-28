DEFAULT_INCLUDES = -I@top_builddir@

lib_LTLIBRARIES = libgap.la

libgap_la_SOURCES = \
  ariths.c    c_random.c  \
  ariths.h    c_type1.c   gvars.c     objfgelm.c  records.c   tietze.c    \
  blister.c   cyclotom.c  gvars.h     objfgelm.h  records.h   tietze.h    \
  blister.h   cyclotom.h  integer.c   objpcgel.c  saveload.c  vars.c      \
  bool.c      dt.c        integer.h   objpcgel.h  saveload.h  vars.h      \
  bool.h      dteval.c    intrprtr.c  objscoll.c  scanner.c   vec8bit.c   \
  calls.c     dteval.h    intrprtr.h  objscoll.h  vec8bit.h   \
  calls.h     dt.h        iostream.c  opers.c     sctable.c   vecffe.c    \
  c_filt1.c   exprs.c                 opers.h     sctable.h   vecffe.h    \
  c_meths1.c  exprs.h     listfunc.c  permutat.c  set.c       vecgf2.c    \
  code.c      finfield.c  listfunc.h  permutat.h  set.h       vecgf2.h    \
  code.h      finfield.h  listoper.c  plist.c     stats.c     vector.c    \
  compiled.h  listoper.h  stats.h     vector.h    macfloat.c  \
  compiler.c  lists.c     precord.c   streams.c   weakptr.c   macfloat.h  \
  compiler.h  funcs.c     lists.h     precord.h   streams.h   weakptr.h   \
  compstat.c  funcs.h     objccoll.c  range.c     string.c                \
  compstat.h  gap.c       objccoll.h  range.h     intfuncs.c intfuncs.h   \
  c_oper1.c   objcftl.c   rational.c  sysfiles.c              \
  costab.c                objcftl.h   rational.h              \
  costab.h    gasman.c    objects.c   read.c      system.c    \
  libgap.c

libgapincludedir = @includedir@/gap
libgapinclude_HEADERS = \
  libgap.h    \
  system.h    gap.h       scanner.h   sysfiles.h  plist.h     gasman.h    \
  string.h    iostream.h  read.h      objects.h   config.h


libgap_la_CFLAGS = \
  -DCONFIG_H @GMP_CFLAGS@ \
  -I@SAGE_LOCAL@/include/csage -I@SAGE_LOCAL@/include/python2.7


