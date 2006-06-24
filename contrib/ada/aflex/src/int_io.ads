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

-- TITLE integer IO
-- AUTHOR: John Self (UCI)
-- DESCRIPTION instantiation of integer IO generic for integers
-- $Header: /co/ua/self/arcadia/aflex/ada/src/RCS/int_io.a,v 1.3 90/01/12 15:20:09 self Exp Locker: self $ 

with TEXT_IO; 
package INT_IO is 
  new TEXT_IO.INTEGER_IO(INTEGER); 
