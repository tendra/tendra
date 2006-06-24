-- Copyright (c) 1990 Regents of the University of California.
-- All rights reserved.
--
-- This software was developed by John Self of the Arcadia project
-- at the University of California, Irvine.
--
-- Redistribution and use in source and binary forms are permitted
-- provided that the above copyright notice and this paragraph are
-- duplicated in all such forms and that any documentation,
-- advertising materials, and other materials related to such
-- distribution and use acknowledge that the software was developed
-- by the University of California, Irvine.  The name of the
-- University may not be used to endorse or promote products derived
-- from this software without specific prior written permission.
-- THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
-- IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
-- WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.

-- TITLE symbol table routines
-- AUTHOR: John Self (UCI)
-- DESCRIPTION implements only a simple symbol table using open hashing
-- NOTES could be faster, but it isn't used much
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/symS.a,v 1.4 90/01/12 15:20:42 self Exp Locker: self $ 

with TSTRING; 
with MISC_DEFS; 
package SYM is 

  use TSTRING; 
  use MISC_DEFS; 

  procedure ADDSYM(SYM, STR_DEF : in VSTRING; 
                   INT_DEF      : in INTEGER; 
                   TABLE        : in out HASH_TABLE; 
                   TABLE_SIZE   : in INTEGER; 
                   RESULT       : out BOOLEAN); 
  -- result indicates success
  procedure CCLINSTAL(CCLTXT : in VSTRING; 
                      CCLNUM : in INTEGER); 
  function CCLLOOKUP(CCLTXT : in VSTRING) return INTEGER; 
  function FINDSYM(SYMBOL     : in VSTRING; 
                   TABLE      : in HASH_TABLE; 
                   TABLE_SIZE : in INTEGER) return HASH_LINK; 

  function HASHFUNCT(STR       : in VSTRING; 
                     HASH_SIZE : in INTEGER) return INTEGER; 
  procedure NDINSTAL(ND, DEF : in VSTRING); 
  function NDLOOKUP(ND : in VSTRING) return VSTRING; 
  procedure SCINSTAL(STR     : in VSTRING; 
                     XCLUFLG : in BOOLEAN); 
  function SCLOOKUP(STR : in VSTRING) return INTEGER; 
end SYM; 
