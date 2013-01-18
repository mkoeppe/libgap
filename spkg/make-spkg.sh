#!/bin/sh

PATCHLEVEL=""

set -e
if [ ! -f make-spkg.sh ] ; then
    echo "You must run this script in the spkg directory of the libGAP repository."
    exit 1
fi

rm -rf libgap-*

CWD=`pwd`
cd ..

VERSION=`grep AC_INIT configure.ac | cut -d \] -f 2 | cut -d \[ -f 2`
LIBGAP_DIR="libgap-$VERSION$PATCHLEVEL"
SPKG_ROOT="$CWD/$LIBGAP_DIR"

rm -rf "$SPKG_ROOT"
mkdir -p "$SPKG_ROOT"

rm libgap-$VERSION.tar.gz
make dist

cd "$SPKG_ROOT"
tar xf ../../libgap-$VERSION.tar.gz
mv libgap-$VERSION src

cd "$SPKG_ROOT/src/src"
"$CWD/libGAPify.py" --modify "$SPKG_ROOT/src/src"

cd "$CWD"
cp spkg-install "$SPKG_ROOT"
cp SPKG.txt "$SPKG_ROOT"

cd "$SPKG_ROOT"
echo 'src' > .hgignore
hg init .
hg add
hg commit -m 'This is not the true repository, read SPKG.txt'

cd "$CWD"
sage -pkg_nc "$LIBGAP_DIR"
export SAGE_DEBUG=yes
sage -f -s "./$LIBGAP_DIR.spkg"



