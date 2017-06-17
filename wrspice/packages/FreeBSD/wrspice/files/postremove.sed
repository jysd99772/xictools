#! /bin/sh

if [ x"$PKG_PREFIX" = "x" ]; then
    prefix=/usr/local
else
    prefix=$PKG_PREFIX
fi

libdir=$prefix/xictools/wrspice
relnote=wrs@VERSION@

if [ -f $libdir/docs/$relnote.tmp ]; then
    mv -f $libdir/docs/$relnote.tmp $libdir/docs/$relnote
fi
