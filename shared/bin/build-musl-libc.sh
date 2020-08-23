#!/bin/sh -xv

mkdir -p tendra-musl-build || :
export CURDIR=`pwd`/tendra-musl-build

URLS=$(cat <<EOF
https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.gz@27e879dccc639cd7b0cc08ed575c1669492579529b53c9ff27b0b96265fa867d
https://ftp.gnu.org/gnu/mpc/mpc-1.2.0.tar.gz@e90f2d99553a9c19911abdb4305bf8217106a957e3994436428572c8dfe8fda6
https://ftp.gnu.org/gnu/gmp/gmp-6.2.0.tar.xz@258e6cd51b3fbdfc185c716d55f82c08aff57df0c6fbd143cf6ed561267a1526
https://ftp.gnu.org/gnu/mpfr/mpfr-4.1.0.tar.gz@3127fe813218f3a1f0adf4e8899de23df33b4cf4b4b3831a5314f78e65ffa2d6
https://www.musl-libc.org/releases/musl-1.1.5.tar.gz@352362b1724cc9740f4c3ce0fe02aae45e4de9809ea4ac961f31aedc11b87393
EOF
    )

PACKAGES=$(cat <<EOF
mpfr@4.1.0@
mpc@1.2.0@--prefix=${CURDIR}/gcc-libs --with-mpfr-include=${CURDIR}/gcc-libs/include --with-mpfr-lib=${CURDIR}/gcc-libs/lib
gmp@6.2.0@--prefix=${CURDIR}/gcc-libs --with-mpc=${CURDIR}/gcc-libs --with-mpfr=${CURDIR}/gcc-libs
gcc@10.2.0@--prefix=${CURDIR}/gcc-libs --with-mpc=${CURDIR}/gcc-libs --with-gmp=${CURDIR}/gcc-libs --with-mpfr=${CURDIR}/gcc-libs --enable-languages=c
musl@1.1.5@--prefix=${CURDIR}/gcc-libs/musl-1.1.5/usr --target=i386-unknown-linux-gnu@${CURDIR}/gcc-libs/bin/gcc -m32
EOF
    )

for urlhash in ${URLS} ; do
    url=`echo "${urlhash}" | awk -F@ '{print $1}'`
    hash=`echo "${urlhash}" | awk -F@ '{print $2}'`

    saveto=`basename "${url}"`
    if [ -e "${saveto}" ] ; then
        hashof=`sha256sum "${saveto}" | awk '{print $1}'`
        if [ "x${hash}" != "x${hashof}" ] ; then
            echo "bad download of ${url}"
            rm "${saveto}"
        else
            echo "good download of ${url}"
        fi
    else
        echo "need to download ${url}"
    fi

    if [ ! -e "${saveto}" ] ; then
        curl -o "${saveto}" "${url}" || ( echo "failed to download ${url}" && exit 1 )
    fi
done

cd tendra-musl-build && \
echo "${PACKAGES}" | while read pkgline ; do
    name=`echo "${pkgline}" | awk -F@ '{print $1}'`
    ver=`echo "${pkgline}" | awk -F@ '{print $2}'`
    config=`echo "${pkgline}" | awk -F@ '{print $3}'`
    cc=`echo "${pkgline}" | awk -F@ '{print $4}'`

    if [ "x${cc}" = x ] ; then
        export CC=gcc
    else
        export CC="${cc}"
    fi

    if [ ! -e ${name}-built ] ; then
        ( \
          if [ -e ../${name}-${ver}.tar.gz ] ; then
              gzip -d < ../${name}-${ver}.tar.gz
          else
              xzcat < ../${name}-${ver}.tar.xz
          fi | tar xvf - --skip-old-files && \
          cd ${name}-${ver} && \
          sh -c "./configure ${config}" && \
          make && \
          make install
        )
    else
        echo "${name} ${ver} completed"
    fi || exit 1
    touch ${name}-built
done && \
for incfile in bits/alltypes.h math.h ; do
    inc="${CURDIR}/gcc-libs/musl-1.1.5/usr/include/${incfile}"
    sed -e 's/__u/__musl_u/g' < ${inc} > ${inc}.fix
    mv ${inc}.fix ${inc}
done && \
( \
  cp -r ${CURDIR}/gcc-libs/lib/gcc/x86_64-pc-linux-gnu/10.2.0/32/libgcc.a ${CURDIR}/gcc-libs/musl-1.1.5/usr/lib && \
  cp -r ${CURDIR}/gcc-libs/musl-1.1.5 ./osdep/libc
)
