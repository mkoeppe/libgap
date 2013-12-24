#!/bin/sh

set -e
if [ ! -f configure.ac ] ; then
    echo "You must run this script in the libGAP root directory."
    exit 1
fi

VERSION=`autoconf --trace='AC_INIT:$2'`

diff -urd upstream-gap-$VERSION/src src > patches/gap-$VERSION.patch




