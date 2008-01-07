# $TenDRA$

# Platform settings.
PREFIX?=	/usr/local
MAN_COMPRESS=	yes
MAN_INSTALL=	yes
TMP_DIR=	/tmp


# SRC_ENV corresponds to the hierarchy in tendra/src/lib/env.
SRC_ENV=	${BUILD_OS}/common/${MACH_CPU}
# SRC_MACHINES corresponds to the hierarchy in tendra/src/lib/machines.
SRC_MACHINES=	${BUILD_OS}/${MACH_CPU}


# GETCONF?=	/usr/bin/getconf
#get_cpu_type()
#{
#        CPU_TYPE=`${GETCONF} CPU_VERSION`
#
#        if [ $CPU_TYPE -ge 768 ]; then ARCHITECTURE=ia64rev0
#                # unistd.h: CPU_IA64_ARCHREV_0
#        elif [ $CPU_TYPE -eq 532 ]; then ARCHITECTURE=hpparisc2x
#                # unistd.h: CPU_PA_RISC2_0
#        elif [ $CPU_TYPE -eq 529 ]; then ARCHITECTURE=hpparisc12
#                # unistd.h: CPU_PA_RISC1_2
#        elif [ $CPU_TYPE -eq 528 ]; then ARCHITECTURE=hpparisc11
#                # unistd.h: CPU_PA_RISC1_1
#        elif [ $CPU_TYPE -eq 526 ]; then ARCHITECTURE=mc68020
#                # unistd.h: CPU_HP_MC68020
#        elif [ $CPU_TYPE -eq 525 ]; then ARCHITECTURE=mc68030
#                # unistd.h: CPU_HP_MC68030
#        elif [ $CPU_TYPE -eq 524 ]; then ARCHITECTURE=mc68040
#                # unistd.h: CPU_HP_MC68040
#        elif [ $CPU_TYPE -eq 523 ]; then ARCHITECTURE=hpparisc10
#                # unistd.h: CPU_PA_RISC1_0
#        fi
#}

MACH_CPU=	hppa # Be lame for now and hardwire it, until above works.
MACH_OS!=	${BIN_UNAME}
MACH_VERS!=	${BIN_UNAME} -r

# Not sure of the best way to get the exec type, suggestions?
MACH_EXEC=	elf

.include "config.common.mk"
