# Copyright 2004-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_MAKEDEFS_MK_)
_TENDRA_MAKEDEFS_MK_=1


# Please note that blindly adding new OSes here is not enough to port TenDRA to
# a new system; the guide to porting covers the process in detail.


# We use ${UNAME_*} to tell us about the architecture we're building for. Those
# variables may be overridden for systems with an incompatible (or no) uname(1)
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


UNAME_MACHINE!= 	${UNAME} -m
UNAME_SYSTEM!=   	${UNAME} -s
UNAME_REVISION!= 	${UNAME} -r

HOSTARCH?=	${UNAME_MACHINE}
SYSTEM?=	${UNAME_SYSTEM}
VERSION?=	${UNAME_REVISION}


.if ${SYSTEM} == Linux

.if exists(/lib/libc.so.6)
LDD_BLURB?= /lib/libc.so.6 2>&1
.else
LDD_BLURB?= ldd --version  2>&1
.endif

LDD_NAME!=                       \
    ${LDD_BLURB}                 \
    | { read v && case "$$v" in  \
        *EGLIBC*) echo EGLIBC;;  \
        *GLIBC*)  echo GLIBC;;   \
        *GNU\ C*) echo GLIBC;;   \
        *musl*)   echo MUSL;;    \
        *)        echo unknown;; \
    esac }

LDD_VER!=                        \
    ${LDD_BLURB}                 \
    | { read v && case "$$v" in  \
        *GLIBC*)  echo "$$v" | sed -n 's/^ldd (\(GNU libc\|.* E\?GLIBC .*\)) //p';; \
        *GNU\ C*) echo "$$v" | sed -n 's/^.*version \(.*\), .*/\1/p';;              \
        MUSL)     echo "$$v" | sed -n 's/^Version \(.*\)/\1/p';;                    \
        *)        echo unknown;; \
    esac }                       \
    | tr . _

LIBC_VER?= ${LDD_NAME}_${LDD_VER}

.endif


# Platform-specific things
EXECFMT?=       ${MD_EXECFMT}
BLDARCH?=       ${MD_BLDARCH}
TRANSARCH?=     ${MD_TRANSARCH}
OSFAM?=         ${MD_OSFAM}
OSVER?=         ${MD_OSVER}
LIBCFAM?=       ${MD_LIBCFAM}
LIBCVER?=       ${MD_LIBCVER}
LIBCPREFIX?=    ${MD_LIBCPREFIX}

MD_EXECFMT!=                              \
    case "${SYSTEM}" in                   \
        Darwin)    echo mach;;            \
        FreeBSD)   echo elf;;             \
        Linux)     echo elf;;             \
        NetBSD)    echo elf;;             \
        OpenBSD)   echo elf;;             \
        SunOS)     echo elf;;             \
        HP-UX)     echo parisc;;          \
        *)         echo unknown;;         \
    esac;

MD_BLDARCH!=                              \
    case "${HOSTARCH}" in                 \
        alpha)         echo alpha;;       \
        amd64|x86_64)  echo x86_64;;      \
        BePC)          echo x86_32;;      \
        i?86|i86pc)    echo x86_32;;      \
        sparc|sparc64) echo sparc;;       \
        9000/7*)       echo hppa;;        \
        hppa)          echo hppa;;        \
        socppc|macppc) echo power;;       \
        mips)          echo mips;;        \
        *)             echo unknown;;     \
    esac;

MD_TRANSARCH!=                            \
    case "${BLDARCH}" in                  \
        x86_32|x32_64) echo x86;;         \
        x86_64)        echo x86;;         \
        *)             echo ${BLDARCH};;  \
    esac;

MD_OSFAM!=                                \
    case "${SYSTEM}" in                   \
        Darwin)    echo darwin;;          \
        FreeBSD)   echo freebsd;;         \
        Linux)     echo linux;;           \
        NetBSD)    echo netbsd;;          \
        OpenBSD)   echo openbsd;;         \
        SunOS)     echo solaris;;         \
        Haiku)     echo haiku;;           \
        HP-UX)     echo hpux;;            \
        *)         echo unknown;;         \
    esac;

MD_OSVER!=                                \
    case "${SYSTEM}.${VERSION}" in        \
        Darwin.10.3.*) echo DARWIN103;;   \
        FreeBSD.4*)    echo FREEBSD4;;    \
        FreeBSD.5*)    echo FREEBSD5;;    \
        FreeBSD.6*)    echo FREEBSD6;;    \
        FreeBSD.9.0*)  echo FREEBSD9_0;;  \
        FreeBSD.9.1*)  echo FREEBSD9_1;;  \
        FreeBSD.9.2*)  echo FREEBSD9_2;;  \
        FreeBSD.10.1*) echo FREEBSD10_1;; \
        FreeBSD.10.2*) echo FREEBSD10_2;; \
        FreeBSD.10.3*) echo FREEBSD10_3;; \
        FreeBSD.10.4*) echo FREEBSD10_4;; \
        FreeBSD.11.0*) echo FREEBSD11_0;; \
        FreeBSD.11.1*) echo FREEBSD11_1;; \
        FreeBSD.11.2*) echo FREEBSD11_2;; \
        FreeBSD.11.3*) echo FREEBSD11_3;; \
        Linux.2.4*)    echo LINUX24;;     \
        Linux.2.6*)    echo LINUX26;;     \
        Linux.3.0*)    echo LINUX30;;     \
        Linux.3.1*)    echo LINUX31;;     \
        Linux.3.7*)    echo LINUX37;;     \
        Linux.5.4*)    echo LINUX54;;     \
        NetBSD.4*)     echo NETBSD4;;     \
        NetBSD.5.1*)   echo NETBSD5_1;;   \
        OpenBSD.3*)    echo OPENBSD3;;    \
        OpenBSD.4*)    echo OPENBSD4;;    \
        OpenBSD.5.1)   echo OPENBSD5_1;;  \
        OpenBSD.5.2)   echo OPENBSD5_2;;  \
        OpenBSD.5.3)   echo OPENBSD5_3;;  \
        OpenBSD.5.4)   echo OPENBSD5_4;;  \
        OpenBSD.5.5)   echo OPENBSD5_5;;  \
        OpenBSD.5.6)   echo OPENBSD5_6;;  \
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
        MUSL_*)        echo musl;;        \
        *)             echo ${MD_OSFAM};; \
    esac;

MD_LIBCVER!=                              \
    case "${LIBC_VER}" in                 \
        EGLIBC_2_11_*) echo EGLIBC2_11;;  \
        EGLIBC_2_15*)  echo EGLIBC2_15;;  \
        EGLIBC_2_19*)  echo EGLIBC2_19;;  \
        GLIBC_2_3_*)   echo GLIBC2_3;;    \
        GLIBC_2_5)     echo GLIBC2_5;;    \
        GLIBC_2_7)     echo GLIBC2_7;;    \
        GLIBC_2_11_*)  echo GLIBC2_11;;   \
        GLIBC_2_12)    echo GLIBC2_12;;   \
        GLIBC_2_12_*)  echo GLIBC2_12;;   \
        GLIBC_2_14_*)  echo GLIBC2_14;;   \
        GLIBC_2_15*)   echo GLIBC2_15;;   \
        GLIBC_2_17*)   echo GLIBC2_17;;   \
        GLIBC_2_18*)   echo GLIBC2_18;;   \
        GLIBC_2_19*)   echo GLIBC2_19;;   \
        GLIBC_2_27*)   echo GLIBC2_27;;   \
        GLIBC_2_31*)   echo GLIBC2_31;;   \
        MUSL_1_1_5)    echo MUSL1_1_5;;   \
        *)             echo ${MD_OSVER};; \
    esac;

MD_LIBCPREFIX!=                           \
    case "${SYSTEM}" in                   \
        Haiku)     echo /boot;;           \
        *)         echo ;;                \
    esac;


.endif
