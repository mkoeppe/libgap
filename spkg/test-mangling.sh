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

cd "$SPKG_ROOT/src/src"
"$CWD/libGAPify.py" "$SPKG_ROOT/src/src"
cd "$SPKG_ROOT/src"
make


