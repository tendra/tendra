/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/**********************************************************************
$Author: release $
$Date: 1998/01/17 15:55:47 $
$Revision: 1.1.1.1 $
$Log: shapemacs.h,v $
 * Revision 1.1.1.1  1998/01/17  15:55:47  release
 * First version to be checked into rolling release.
 *
 * Revision 1.1  1995/04/06  10:44:05  currie
 * Initial revision
 *
***********************************************************************/
#ifndef bothd



#define bothd  1
#define tophd  2
#define scharhd  3
#define ucharhd  4
#define swordhd  5
#define uwordhd  6
#define slonghd  7
#define ulonghd  8
#define s64hd 9
#define u64hd 10



#define shcomplexhd  17
#define complexhd  18
#define complexdoublehd  19
#define shrealhd  20
#define realhd  21
#define doublehd  22
#define bitfhd 23
#define prokhd  24
#define ptrhd  25
#define offsethd  26
#define sizehd  27
#define cpdhd  28


#define nofhd  29
#define tokhd  30


#define shrealfv  0
#define realfv  1
#define doublefv  2
#define shcomplexfv  3
#define complexfv  4
#define complexdoublefv  5


#define is_floating(x) ((x)>=shrealhd && (x)<= doublehd)



#endif
