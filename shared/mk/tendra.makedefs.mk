# $Id$

# Copyright 2004-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_MAKEDEFS_MK_)
_TENDRA_MAKEDEFS_MK_=1


# Please note that blindly adding new OSes here is not enough to port TenDRA to
# a new system; the guide to porting covers the process in detail.


# We use ${UNAME} to tell us about the architecture we're building for. That
# variable may be overridden for systems with an incompatible (or no) uname(1)
# output.
#
# This is flawed in that it assumes the version of the kernel (as reported by
# uname) is the same as the version of the libraries present in /usr/include
# (as used for API building), which is not always true. However, for the rare
# situations where they differ, the user may explicitly override variables
# accordingly.
#
# In Linux's case, instead of the kernel version, we attempt to find the libc
# version; the same caveat applies.
#
# The idea here is that these variables are only assigned if required, and that
# the majority of projects do not use them (as they typically do not require
# knowledge of any particular machine). In this way we attempt to avoid
# inconveniencing the user with running a `makedefs` script per-project.


HOSTARCH!=	${UNAME} -m
SYSTEM!=	${UNAME} -s
VERSION!=	${UNAME} -r


.if ${SYSTEM} == Linux
. if (exists(/lib/libc.so.6))
GLIBC_VER!= /lib/libc.so.6 | sed -n 's/^.* version \(.*\), .*$$/\1/p' | tr . _
GLIBC_NAME!= /lib/libc.so.6 | grep EGLIBC > /dev/null && echo -n E; echo GLIBC
. else
GLIBC_VER!= ldd --version | sed -n 's/^ldd (\(GNU libc\|.* EGLIBC .*\)) //p' | tr . _
GLIBC_NAME!= ldd --version | grep EGLIBC > /dev/null && echo -n E; echo GLIBC
. endif

LIBC_VER?= ${GLIBC_NAME}_${GLIBC_VER}
.endif

MD_EXECFMT!=                              \
    case "${SYSTEM}" in                   \
        Darwin)    echo mach;;            \
        DragonFly) echo elf;;             \
        FreeBSD)   echo elf;;             \
        Linux)     echo elf;;             \
        NetBSD)    echo elf;;             \
        OpenBSD)   echo elf;;             \
        AerieBSD)  echo elf;;             \
        SunOS)     echo elf;;             \
        HP-UX)     echo parisc;;          \
        *)         echo unknown;;         \
    esac;

MD_BLDARCH!=                              \
    case "${HOSTARCH}" in                 \
        alpha)         echo alpha;;       \
        amd64|x86_64)  echo amd64;;       \
        BePC)          echo 80x86;;       \
        i?86|i86pc)    echo 80x86;;       \
        sparc|sparc64) echo sparc;;       \
        9000/7*)       echo hppa;;        \
        hppa)          echo hppa;;        \
        socppc|macppc) echo ppc601;;      \
        mips)          echo mips;;        \
        *)             echo unknown;;     \
    esac;

MD_BLDARCHBITS!=                          \
    case "${HOSTARCH}" in                 \
        alpha)         echo 64;;          \
        amd64|x86_64)  echo 64;;          \
        BePC)          echo 32;;          \
        i?86|i86pc)    echo 32;;          \
        sparc)         echo 32;;          \
        sparc64)       echo 64;;          \
        9000/7*)       echo 64;;          \
        hppa)          echo 32;;          \
        socppc|macppc) echo 32;;          \
        *)             echo unknown;;     \
    esac;

MD_OSFAM!=                                \
    case "${SYSTEM}" in                   \
        Darwin)    echo darwin;;          \
        DragonFly) echo dragonfly;;       \
        FreeBSD)   echo freebsd;;         \
        Linux)     echo linux;;           \
        NetBSD)    echo netbsd;;          \
        OpenBSD)   echo openbsd;;         \
        AerieBSD)  echo aerielbsd;;       \
        SunOS)     echo solaris;;         \
        Haiku)     echo haiku;;           \
        HP-UX)     echo hpux;;            \
        *)         echo unknown;;         \
    esac;

MD_OSVER!=                                \
    case "${SYSTEM}.${VERSION}" in        \
        Darwin.10.3.*) echo DARWIN103;;   \
        DragonFly.1*)  echo DRAGONFLY1;;  \
        FreeBSD.4*)    echo FREEBSD4;;    \
        FreeBSD.5*)    echo FREEBSD5;;    \
        FreeBSD.6*)    echo FREEBSD6;;    \
        FreeBSD.9.0*)  echo FREEBSD9_0;;  \
        FreeBSD.9.1*)  echo FREEBSD9_1;;  \
        FreeBSD.9.2*)  echo FREEBSD9_2;;  \
        FreeBSD.10.1*) echo FREEBSD10_1;; \
        Linux.2.4*)    echo LINUX24;;     \
        Linux.2.6*)    echo LINUX26;;     \
        Linux.3.0*)    echo LINUX30;;     \
        Linux.3.1*)    echo LINUX31;;     \
        Linux.3.7*)    echo LINUX37;;     \
        NetBSD.4*)     echo NETBSD4;;     \
        NetBSD.5.1*)   echo NETBSD5_1;;   \
        OpenBSD.3*)    echo OPENBSD3;;    \
        OpenBSD.4*)    echo OPENBSD4;;    \
        OpenBSD.5.1)   echo OPENBSD5_1;;  \
        OpenBSD.5.2)   echo OPENBSD5_2;;  \
        OpenBSD.5.3)   echo OPENBSD5_3;;  \
        OpenBSD.5.4)   echo OPENBSD5_4;;  \
        AerieBSD.1*)   echo AERIELBSD1;;  \
        SunOS.5.10*)   echo SUNOS510;;    \
        SunOS.5.11*)   echo SUNOS511;;    \
        Haiku.1*)      echo HAIKU1;;      \
        HP-UX.B.11.11) echo HPUX11i;;     \
        *)             echo unknown;;     \
    esac;

MD_LIBCFAM!=                              \
    case "${LIBC_VER}" in                 \
        EGLIBC_*)      echo eglibc;;      \
        GLIBC_*)       echo glibc;;       \
        *)             echo ${MD_OSFAM};; \
    esac;

MD_LIBCVER!=                              \
    case "${LIBC_VER}" in                 \
        EGLIBC_2_11_*) echo EGLIBC2_11;;  \
        EGLIBC_2_15*)  echo EGLIBC2_15;;  \
        GLIBC_2_3_*)   echo GLIBC2_3;;    \
        GLIBC_2_5)     echo GLIBC2_5;;    \
        GLIBC_2_7)     echo GLIBC2_7;;    \
        GLIBC_2_11_*)  echo GLIBC2_11;;   \
        GLIBC_2_12_*)  echo GLIBC2_12;;   \
        GLIBC_2_14_*)  echo GLIBC2_14;;   \
        GLIBC_2_15*)   echo GLIBC2_15;;   \
        GLIBC_2_17*)   echo GLIBC2_17;;   \
        *)             echo ${MD_OSVER};; \
    esac;

.endif
