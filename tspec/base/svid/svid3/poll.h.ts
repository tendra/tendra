# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+FIELD struct pollfd {
    int fd ;
    short events ;
    short revents ;
} ;

+CONST int POLLIN, POLLRDNORM, POLLRDBAND, POLLPRI, POLLOUT, POLLWRNORM ;
+CONST int POLLWRBAND, POLLERR, POLLHUP, POLLNVAL ;

+FUNC int poll ( struct pollfd [], unsigned long, int ) ;
