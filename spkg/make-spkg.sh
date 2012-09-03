#!/bin/sh

set -e
if [ ! -f make-spkg.sh ] ; then
    echo "You must run this script in the spkg directory of the libGAP repository."
    exit 1
fi

rm -rf libgap-*

CWD=`pwd`
cd ..

VERSION=`grep AC_INIT configure.ac | cut -d \] -f 2 | cut -d \[ -f 2`
LIBGAP_DIR="libgap-$VERSION"
SPKG_ROOT="$CWD/$LIBGAP_DIR"

rm -rf "$SPKG_ROOT"
mkdir -p "$SPKG_ROOT/src"
cp -rp `ls | grep -v spkg` "$SPKG_ROOT/src"

cd "$SPKG_ROOT/src"
[ -x Makefile ] && make distclean

cd "$SPKG_ROOT"
find -name '*~' -exec rm '{}' ';'

cd "$SPKG_ROOT/src/src"
"$CWD/libGAPify.py" "$SPKG_ROOT/src/src"

cd "$CWD"
cp spkg-install "$SPKG_ROOT"
cp SPKG.txt "$SPKG_ROOT"

cd "$SPKG_ROOT"
echo 'src' > .hgignore
hg init .
hg add
hg commit -m 'This is not the true repository, read SPKG.txt'

cd "$CWD"
# export CFLAGS="-O0 -g3 -DDEBUG_MASTERPOINTERS -DDEBUG_GLOBAL_BAGS -DDEBUG_FUNCTIONS_BAGS -DDEBUG_DEADSONS_BAGS"
sage -pkg_nc "$LIBGAP_DIR"
export SAGE_DEBUG=yes
sage -f -s "$LIBGAP_DIR.spkg"



