# TenDRA make build infrastructure
#
# $Id$

.if !defined(_TENDRA_SRCBASE_MK_)
_TENDRA_SRCBASE_MK_=1


APIS=         	src/lib/apis
ENVIRONMENT=  	src/lib/env
INCLUDE=      	src/include
STARTUP=      	src/lib/startup
STARTUP_MACH= 	src/lib/machines/${OSFAM}/${BLDARCH}/startup
TOKENS_COMMON=	src/lib/machines/common/tokens
TOKENS_MACH=  	src/lib/machines/${OSFAM}/${BLDARCH}/tokens
TOOLS=        	src/tools
UTILITIES=    	src/utilities


.endif	# !defined(_TENDRA_SRCBASE_MK_)
