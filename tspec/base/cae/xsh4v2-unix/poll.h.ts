# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+FIELD struct pollfd {
    int fd ;
    short events ;
    short revents ;
} ;

+TYPE ( unsigned ) nfds_t ;

+CONST short POLLIN, POLLRDNORM, POLLRDBAND, POLLPRI, POLLOUT, POLLWRNORM ;
+CONST short POLLERR, POLLHUP, POLLNVAL ;

# POLLWRBAND missed out on <poll.h> page, but defined on poll() page
+CONST short POLLWRBAND ;

+FUNC int poll ( struct pollfd [], unsigned long, int ) ;
