# $Id$

# Copyright 2010-2011, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.


.if !defined(_TENDRA_SITU_MK_)
_TENDRA_SITU_MK_=1

.include <tendra.base.mk>
.include <tendra.functions.mk>

.if !defined(TCC)
.BEGIN:
	@${ECHO} '$${TCC} must be set'
	@${EXIT} 1;
.endif


#
# This warrants a little explanation.
#
# Under bootstrap, TCCOPTS contains -Ybootstrap_env, which is required for (at
# least) specifying the location of tcc's 'startup' files and suchlike. We need
# to keep that here, because there's no way osdep/ itself can know where those
# are. So TCCOPTS cannot be overridden here.
#
# At the time of running ${TCC} for osdep's needs, the environments have not
# yet been installed under $PREFIX.
#
# The TCCENV= is because ${TCC} is actually a wrapper shell script, which
# always attempts to load -Ydefault from $PREFIX's env directory. TCCENV= takes
# precidence over that, and will keep tcc quiet about not finding -Ydefault.
#
# If you can think of a simpler way to do this, then please do let me know.
# (The need to set TCCENV= could be eliminated by passing in TCC=libexec/tcc
# instead, however that breaks the abstraction the wrapper script provides, and
# that could cause inconsistencies against a user-specified ${TCC}.)
#
#TCC_IN_SITU?= TCCENV=${OBJ_DIR}/env ${TCC}
TCC_IN_SITU?= ${TCC}



#
# User-facing targets
#

all::


clean::


install::



.endif	# !defined(_TENDRA_WORK_ENV_MK_)
