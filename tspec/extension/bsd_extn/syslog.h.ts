# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# Functions
+FUNC void syslog ( int, const char *, ... ) ;
+FUNC void openlog ( const char *, int, int ) ;
+FUNC void closelog ( void ) ;
+FUNC int setlogmask ( int ) ;

# Priority codes
+CONST int LOG_EMERG, LOG_ALERT, LOG_CRIT, LOG_ERR, LOG_WARNING ;
+CONST int LOG_NOTICE, LOG_INFO, LOG_DEBUG ;

# Arguments for openlog
+CONST int LOG_PID, LOG_CONS, LOG_ODELAY, LOG_NDELAY, LOG_NOWAIT ;

# Facility codes
+CONST int LOG_KERN, LOG_USER, LOG_MAIL, LOG_DAEMON, LOG_AUTH ;
+CONST int LOG_SYSLOG, LOG_LPR ;
+CONST int LOG_LOCAL0, LOG_LOCAL1, LOG_LOCAL2, LOG_LOCAL3 ;
+CONST int LOG_LOCAL4, LOG_LOCAL5, LOG_LOCAL6, LOG_LOCAL7 ;
# not used LOG_NEWS, LOG_UUCP, LOG_LFMT, LOG_CRON

# Arguments for setlogmask
+MACRO int LOG_MASK ( int ) ;
+MACRO int LOG_UPTO ( int ) ;
