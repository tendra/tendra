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

-- Module       : set_pack_body.ada
-- Component of : ayacc
-- Version      : 1.2
-- Date         : 11/21/86  12:35:14
-- SCCS File    : disk21~/rschm/hasee/sccs/ayacc/sccs/sxset_pack_body.ada

-- $Header: set_pack_body.a,v 0.1 86/04/01 15:11:59 ada Exp $ 
-- $Log:	set_pack_body.a,v $
-- Revision 0.1  86/04/01  15:11:59  ada
--  This version fixes some minor bugs with empty grammars 
--  and $$ expansion. It also uses vads5.1b enhancements 
--  such as pragma inline. 
-- 
-- 
-- Revision 0.0  86/02/19  18:41:30  ada
-- 
-- These files comprise the initial version of Ayacc
-- designed and implemented by David Taback and Deepak Tolani.
-- Ayacc has been compiled and tested under the Verdix Ada compiler
-- version 4.06 on a vax 11/750 running Unix 4.2BSD.
--  

package body Set_Pack is

  SCCS_ID : constant String := "@(#) set_pack_body.ada, Version 1.2";



  Rcs_ID : constant String := "$Header: set_pack_body.a,v 0.1 86/04/01 15:11:59 ada Exp $";


    type Cell is
	record
	    Value : Universe;
	    Next  : Link;
	end record;

    Extras : Link; -- For garbage collection.

    function Get_Node return Link;
--RJS    pragma inline(get_node);


    function Get_Node return Link is
	Temp_Link : Link;
    begin
	if Extras = null then
	    return new Cell;
	else
	    Temp_Link := Extras;
	    Extras := Extras.Next;
	    Temp_Link.Next := null;
	    return Temp_Link;
	end if;
    end Get_Node;
	    

    procedure Make_Null (Set_1: in out Set) is
	Temp_Link : Link;
    begin

	if Set_1.Head = null then
	    Set_1.Size := 0;
	    return;
	end if;

	    -- Find tail of set_1 --

	Temp_Link := Set_1.Head;
	while Temp_Link.Next /= null loop
	    Temp_Link := Temp_Link.Next;
	end loop;

	    -- Add set_1 elements to the extras stack --

	Temp_Link.Next := Extras;
	Extras := Set_1.Head;
	Set_1 := (Size => 0, Head => null);

    end Make_Null;

    procedure Assign (Object  : in out Set;  Value : in Set) is
	Temp_1, Temp_2: Link;
    begin

	if Object = Value then
	    return;
        else 
            Make_Null(Object); 
	end if;

	if Value.Head = null then
	    return;
	end if;

	Object.Head := Get_Node;
	Object.Head.Value := Value.Head.Value;
	Object.Head.Next := null;
	Temp_1 := Object.Head;
	Temp_2 := Value.Head.Next;

	while Temp_2 /= null loop
	    Temp_1.Next := Get_Node;
	    Temp_1.Next.all := (Value => Temp_2.Value, Next => null);
	    Temp_1 := Temp_1.Next;
	    Temp_2 := Temp_2.Next;
	end loop;
	Temp_1.Next := null;
	Object.Size := Value.Size;

    end Assign;

    procedure Insert (Element : in Universe; Into  : in out Set) is
       Temp_Link   : Link;
       Temp_Link_2 : Link;
    begin

	if Into.Head = null or else Element < Into.Head.Value then
	    Temp_Link := Get_Node;
	    Temp_Link.all := (Value => Element, Next => Into.Head);
	    Into.Head := Temp_Link;
	    Into.Size := Into.Size + 1;
	    return;
	end if;

        if Into.Head.Value = Element then
	    return;
	end if;

	Temp_Link := Into.Head;
	while Temp_Link.Next /= null loop
	    if Element = Temp_Link.Next.Value then -- Already in the list.
		return; 
	    elsif Element < Temp_Link.Next.Value then
		exit;  -- Found place to insert.
	    else
		Temp_Link := Temp_Link.Next;
	    end if;
	end loop;

            --  insert element  --

	Temp_Link_2 := Get_Node;
	Temp_Link_2.Next := Temp_Link.Next;
	Temp_Link_2.Value := Element;
	Temp_Link.Next := Temp_Link_2;
	Into.Size := Into.Size + 1;
	    
    end Insert;


    procedure Insert (Set_1   : in Set;      Into  : in out Set) is
  	Temp, Trav1, Trav2 : Link;
        
    begin
        if  Set_1.Head = null then 
            return; 
        elsif Set_1.Head = Into.Head then 
            return; 
        elsif Into.Head = null then 
            Assign(Into, Set_1); 
            return;
        end if;

        if Set_1.Head.Value < Into.Head.Value then
            Temp          := Into.Head;
            Into.Head     := Get_Node;
            Into.Head.all := (Set_1.Head.Value, Temp);   
            Trav1         := Set_1.Head.Next;
            Into.Size     := Into.Size + 1;
        elsif Set_1.Head.Value = Into.Head.Value then 
            Trav1 := Set_1.Head.Next;
        else 
            Trav1 := Set_1.Head;
        end if; 

        Trav2 := Into.Head;
  
        while Trav1 /= null loop 

            while Trav2.Next /= null and then 
                  Trav2.Next.Value < Trav1.Value loop
                Trav2 := Trav2.Next; 
            end loop;
  
            if Trav2.Next = null then  
                while Trav1 /= null loop
                    Trav2.Next      := Get_Node; 
                    Trav2.Next.all  := (Trav1.Value, null); 
                    Trav1           := Trav1.Next;
                    Trav2           := Trav2.Next;
                    Into.Size       := Into.Size + 1;
                end loop;
                return;
            end if;
 
            if Trav2.Next.Value /= Trav1.Value then 
                Temp           := Trav2.Next;
                Trav2.Next     :=  Get_Node;
                Trav2.Next.all := (Trav1.Value, Temp); 
                Trav2          := Trav2.Next;
                Into.Size  := Into.Size + 1;
            end if;
 
            Trav1 := Trav1.Next;
        end loop;
    end Insert;


  

    procedure Delete (Element : in Universe; From  : in out Set) is
	Temp_Link : Link;
	T : Link;
    begin
	if From.Head = null then
	    return;
	elsif Element < From.Head.Value then
	    return;
	elsif Element = From.Head.Value then
	    Temp_Link := From.Head;
	    From.Head := From.Head.Next;
	    From.Size := From.Size - 1;
	    Temp_Link.Next := Extras;
	    Extras := Temp_Link;
	    return;
	end if;

	Temp_Link := From.Head;

	while Temp_Link.Next /= null and then
	      Temp_Link.Next.Value < Element
	loop
	    Temp_Link := Temp_Link.Next;
	end loop;

	if Temp_Link.Next /= null and then
	   Temp_Link.Next.Value = Element
	then
	    T := Temp_Link.Next;
	    Temp_Link.Next := Temp_Link.Next.Next;
	    T.Next := Extras;
	    Extras := T;
	    From.Size := From.Size - 1;
	end if;

    end Delete;


    procedure Fassign (Object : in out Set; Value : in out Set) is 
    begin 
	-- Free the contents of OBJECT first.
        Object := Value; 
        Value  := (Head => null, Size => 0); 
    end Fassign; 

    function  Is_Member (Element: Universe; Of_Set: Set) return Boolean is
	Temp_Link : Link;
    begin

	Temp_Link := Of_Set.Head;
	while Temp_Link /= null and then Temp_Link.Value < Element loop
	    Temp_Link := Temp_Link.Next;
	end loop;

	return Temp_Link /= null and then Temp_Link.Value = Element;

    end Is_Member;

    function  Is_Empty  (Set_1: Set) return Boolean is
    begin
	return Set_1.Head = null;
    end Is_Empty;


    function  Size_of   (Set_1: Set) return Natural is
    begin
	return Set_1.Size;
    end Size_of;


    function "=" (Set_1 : Set; Set_2 : Set) return Boolean is
	Link_1, Link_2: Link;
    begin
    
	if Set_1.Size /= Set_2.Size then
	    return False;
	end if;

	Link_1 := Set_1.Head;
	Link_2 := Set_2.Head;
	while Link_1 /= null and then Link_2 /= null loop
	    if Link_1.Value /= Link_2.Value then
		exit;
	    end if;
	    Link_1 := Link_1.Next;
	    Link_2 := Link_2.Next;
	end loop;

	return Link_1 = Link_2;  -- True if both equal to null

    end "=";


    procedure Initialize (Iterator : in out Set_Iterator; Using : in Set) is
    begin
	Iterator := Set_Iterator(Using.Head);
    end Initialize;

    function  More (Iterator: Set_Iterator) return Boolean is
    begin
	return Iterator /= null;
    end More;

    procedure Next (Iterator: in out Set_Iterator; Element: out Universe) is
    begin
	Element := Iterator.Value;
	Iterator := Set_Iterator(Iterator.Next);
    exception
	when Constraint_Error =>
	    raise No_More_Elements;
    end Next;

end Set_Pack;
