# Copyright 2002-2014, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+CONST int LOG_PID, LOG_CONS, LOG_NDELAY, LOG_ODELAY, LOG_NOWAIT ;

+CONST int LOG_KERN, LOG_USER, LOG_MAIL, LOG_NEWS, LOG_UUCP ;
+CONST int LOG_DAEMON, LOG_AUTH, LOG_CRON, LOG_LPR ;
+CONST int LOG_LOCAL0, LOG_LOCAL1, LOG_LOCAL2, LOG_LOCAL3 ;
+CONST int LOG_LOCAL4, LOG_LOCAL5, LOG_LOCAL6, LOG_LOCAL7 ;

+MACRO int LOG_MASK ( int ) ;
+MACRO int LOG_UPTO ( int ) ;

+CONST int LOG_EMERG, LOG_ALERT, LOG_CRIT, LOG_ERR ;
+CONST int LOG_WARNING, LOG_NOTICE, LOG_INFO, LOG_DEBUG ;

+FUNC void closelog ( void ) ;
+FUNC void openlog ( const char *, int, int ) ;
+FUNC int setlogmask ( int ) ;
+FUNC void syslog ( int, const char *, ... ) ;
