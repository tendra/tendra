# Copyright 2014, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+TYPE (unsigned) socklen_t; # at least 32 bits

+TYPEDEF socklen_t ~socklen_t;

+IMPLEMENT "cae/xns4-socket", "sys/socket.h.ts", "sock_generic";

+CONST int SO_DONTROUTE, SO_RCVLOWAT, SO_RCVTIMEO, SO_SNDLOWAT, SO_SNDTIMEO;

