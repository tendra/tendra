# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+SUBSET "pid_t" := { +TYPE ( signed ) pid_t ; } ;

+SUBSET "stat_t" := {
    # as needed for cose:sys/stat.h

    +SUBSET "guid" := {
	+TYPE ( arith ) uid_t ;
	+TYPE ( arith ) gid_t ;
    } ;

    +TYPE ( arith ) dev_t ;
    +SUBSET "ino_t" := { +TYPE ( arith ) ino_t ; } ;
    +SUBSET "mode_t" := { +TYPE ( arith ) mode_t ; } ;
    +TYPE ( arith ) nlink_t ;
    +SUBSET "off_t" := { +TYPE ( signed ) off_t ; } ;
} ;
