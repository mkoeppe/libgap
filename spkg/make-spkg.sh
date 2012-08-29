#!/bin/sh

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

mkdir -p "$SPKG_ROOT/src"
cp -rp `ls | grep -v spkg` "$SPKG_ROOT/src"

cd $CWD
cp spkg-install "$SPKG_ROOT"
cp SPKG.txt "$SPKG_ROOT"
sage -pkg_nc "$LIBGAP_DIR"

export CFLAGS="-O0 -g3 -DDEBUG_MASTERPOINTERS -DDEBUG_GLOBAL_BAGS -DDEBUG_FUNCTIONS_BAGS"
sage -f -s "$LIBGAP_DIR.spkg"


