# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.

+IMPLEMENT "c/c89", "errno.h.ts" ;

+SUBSET "enums" := {
    +IMPLEMENT "c/c89", "errno.h.ts", "enums" ;

    +CONST int E2BIG, EACCES, EAGAIN, EBADF, EBUSY, ECHILD, EDEADLK, EEXIST ;
    +CONST int EFAULT, EFBIG, EINTR, EINVAL, EIO, EISDIR, EMFILE, EMLINK ;
    +CONST int ENAMETOOLONG, ENFILE, ENODEV, ENOENT, ENOEXEC, ENOLCK, ENOMEM ;
    +CONST int ENOSPC, ENOSYS, ENOTDIR, ENOTEMPTY, ENOTTY, ENXIO, EPERM, EPIPE ;
    +CONST int EROFS, ESPIPE, ESRCH, EXDEV ;
} ;
