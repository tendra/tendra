-- Copyright (c) 1990 Regents of the University of California.
-- All rights reserved.
--
--    The primary authors of ayacc were David Taback and Deepak Tolani.
--    Enhancements were made by Ronald J. Schmalz.
--
--    Send requests for ayacc information to ayacc-info@ics.uci.edu
--    Send bug reports for ayacc to ayacc-bugs@ics.uci.edu
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

-- Module       : symbol_info.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:37:08
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxsymbol_info.ada

-- $Header: symbol_info.a,v 0.1 86/04/01 15:13:15 ada Exp $ 
-- $Log:	symbol_info.a,v $
-- Revision 0.1  86/04/01  15:13:15  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:42:36  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  


with Symbol_Table, Rule_Table;
use  Symbol_Table, Rule_Table;
package Symbol_Info is

    --
    --  The following array declarations are used to compute the
    --  the rules that have a particular symbol on the left hand
    --  side. NONTERMINAL_YIELD contains the rules and
    --  NONTERMINAL_YIELD_OFFSET contains the offset into the first array
    --  indexed by a particular nonterminal.  The user of this package
    --  should not attempt to alter the contents of these arrays. They
    --  are visible in the spec only for efficiency reasons.
    --
    type Yield_Index      is  new Integer;
    type Rule_Array       is  array (Yield_Index range <>)    of Rule;
    type Offset_Array     is  array (Grammar_Symbol range <>) of Yield_Index;

    type Rule_Array_Pointer   is access Rule_Array;
    type Offset_Array_Pointer is access Offset_Array;

    Nonterminal_Yield           : Rule_Array_Pointer;
    Nonterminal_Yield_Index     : Offset_Array_Pointer;

    ---

    procedure Initialize;

    function Is_Nullable(Sym: Grammar_Symbol) return Boolean;

    Undefined_Nonterminal       : exception;
    -- raised if a nonterminal doesn't appear on left hand side of
    -- any rule.

--RJS    pragma inline(is_nullable);

end Symbol_Info;
