
-- Module       : string_pkg.ada
-- Component of : common_library
-- Version      : 1.2
-- Date         : 11/21/86  16:35:20
-- SCCS File    : disk21~/rschm/hasee/sccs/common_library/sccs/sxstring_pkg.ada

-- $Source: /nosc/work/abstractions/string/RCS/string.bdy,v $
-- $Revision: 1.3 $ -- $Date: 85/02/01 10:58:51 $ -- $Author: ron $

-- $Source: /nosc/work/abstractions/string/RCS/string.bdy,v $
-- $Revision: 1.3 $ -- $Date: 85/02/01 10:58:51 $ -- $Author: ron $

with unchecked_deallocation;
with lists, stack_pkg;

package body string_pkg is

  SCCS_ID : constant String := "@(#) string_pkg.ada, Version 1.2";



--| Overview:
--| The implementation for most operations is fairly straightforward.
--| The interesting aspects involve the allocation and deallocation of
--| heap space.  This is done as follows:
--|
--|     1. A stack of accesses to lists of string_type values is set up
--|        so that the top of the stack always refers to a list of values
--|        that were allocated since the last invocation of mark.
--|        The stack is called scopes, referring to the dynamic scopes
--|        defined by the invocations of mark and release.
--|        There is an implicit invocation of mark when the
--|        package body is elaborated; this is implemented with an explicit 
--|        invocation in the package initialization code.
--|
--|     2. At each invocation of mark, a pointer to an empty list
--|        is pushed onto the stack.
--|
--|     3. At each invocation of release, all of the values in the
--|        list referred to by the pointer at the top of the stack are
--|        returned to the heap.  Then the list, and the pointer to it,
--|        are returned to the heap.  Finally, the stack is popped.

    package string_list_pkg is new lists(string_type);
    subtype string_list is string_list_pkg.list;

    type string_list_ptr is access string_list;

    package scope_stack_pkg is new stack_pkg(string_list_ptr);
    subtype scope_stack is scope_stack_pkg.stack;

    use string_list_pkg;
    use scope_stack_pkg;

    scopes: scope_stack;     -- See package body overview.


    -- Utility functions/procedures:

    function enter(s: string_type)
        return string_type;

      --| Raises: illegal_alloc
      --| Effects:
      --| Stores s, the address of s.all, in current scope list (top(scopes)),
      --| and returns s.  Useful for functions that create and return new
      --| string_type values.
      --| Raises illegal_alloc if the scopes stack is empty.

    function match_string(s1, s2: string; start: positive := 1)
        return natural;

      --| Raises: no_match
      --| Effects:
      --| Returns the minimum index, i, in s1'range such that
      --| s1(i..i + s2'length - 1) = s2.  Returns 0 if no such index.
      --| Requires:
      --| s1'first = 1.

-- Constructors:

    function Empty_String return String_Type is
    begin
      return Create ("");
    end Empty_String;


    function create(s: string)
        return string_type is
        subtype constr_str is string(1..s'length);
        dec_s: constr_str := s;
    begin
          return enter(new constr_str'(dec_s));
-- DECada bug; above code (and decl of dec_s) replaces the following: 
--        return enter(new constr_str'(s));
    end create;

    function "&"(s1, s2: string_type)
        return string_type is
    begin
	if is_empty(s1) then return enter(make_persistent(s2)); end if;
	if is_empty(s2) then return enter(make_persistent(s1)); end if; 
        return create(s1.all & s2.all);
    end "&";

    function "&"(s1: string_type; s2: string)
        return string_type is
    begin
	if s1 = null then return create(s2); end if; 
	return create(s1.all & s2); 
    end "&";

    function "&"(s1: string; s2: string_type)
        return string_type is
    begin
	if s2 = null then return create(s1); end if; 
	return create(s1 & s2.all); 
    end "&";
    
    function substr(s: string_type; i: positive; len: natural)
        return string_type is
    begin
        if len = 0 then return null; end if; 
        return create(s(i..(i + len - 1)));
    exception
	when constraint_error =>      -- on array fetch or null deref
	    raise bounds;
    end substr;

    function splice(s: string_type; i: positive; len: natural)
        return string_type is
    begin
        if len = 0 then return enter(make_persistent(s)); end if;
        if i + len - 1 > length(s) then raise bounds; end if; 

        return create(s(1..(i - 1)) & s((i + len)..length(s)));
    end splice;

    function insert(s1, s2: string_type; i: positive)
        return string_type is
    begin
        if i > length(s1) then raise bounds; end if;
	if is_empty(s2) then return create(s1.all); end if;

        return create(s1(1..(i - 1)) & s2.all & s1(i..s1'last));
    end insert;

    function insert(s1: string_type; s2: string; i: positive)
        return string_type is
    begin
        if i > length(s1) then raise bounds; end if;

        return create(s1(1..(i - 1)) & s2 & s1(i..s1'last));
    end insert;

    function insert(s1: string; s2: string_type; i: positive)
        return string_type is
    begin
        if not (i in s1'range) then raise bounds; end if;
	if s2 = null then return create(s1); end if; 

        return create(s1(s1'first..(i - 1)) & s2.all & s1(i..s1'last));
    end insert;

	procedure lc(c: in out character) is
	begin 
	    if ('A' <= c) and then (c <= 'Z') then
		c := character'val(character'pos(c) - character'pos('A')
						    + character'pos('a'));
	    end if; 
	end lc; 

	procedure uc(c: in out character) is
	begin 
	    if ('a' <= c) and then (c <= 'z') then
		c := character'val(character'pos(c) - character'pos('a')
						    + character'pos('A'));
	    end if; 
	end uc; 

    function lower(s: string)
	return string_type is  
	s2: string_type := create(s); 

    begin
	for i in s2'range loop
	    lc(s2(i));
	end loop;
	return s2; 
    end lower; 

    function lower(s: string_type)
	return string_type is
    begin
	if s = null then return null; end if; 
	return lower(s.all);
    end lower;

    function Mixed (S: String) return String_Type is
      Mixed_String : String_Type := Create (S);
    begin
      if Mixed_String'Length /= 0 then
        UC (Mixed_String(Mixed_String'First));
        for i in Mixed_String'First + 1 .. Mixed_String'Last 
        loop
          if Mixed_String(i-1) = '_' or else Mixed_String(i-1) = '.' then
            UC (Mixed_String(i));
          else
            LC (Mixed_String(i));
          end if;
        end loop;
        return Mixed_String;
      else
        return Empty_String;
      end if;
    end Mixed;

    function Mixed (S : String_Type) return String_Type is
    begin
      if s = null then 
        return Empty_String; 
      else
        return Mixed (S.all);
      end if; 
    end Mixed;

    function upper(s: string)
	return string_type is
	s2: string_type := create(s); 

    begin
	for i in s2'range loop
	    uc(s2(i));
	end loop;
	return s2; 
    end upper; 

    function upper(s: string_type)
	return string_type is
    begin
	if s = null then return null; end if; 
	return upper(s.all);
    end upper;
      
    
-- Heap Management:

    function make_persistent(s: string_type)
	return string_type is
        subtype constr_str is string(1..length(s));
    begin
        if s = null or else s.all = "" then return null;
        else return new constr_str'(s.all);
        end if; 
    end make_persistent; 
    
    function make_persistent(s: string)
	return string_type is
        subtype constr_str is string(1..s'length);
    begin
	if s = "" then return null; 
        else return new constr_str'(s); end if; 
    end make_persistent; 
    
    procedure real_flush is new unchecked_deallocation(string,
                                                       string_type);
      --| Effect:
      --| Return space used by argument to heap.  Does nothing if null.
      --| Notes:
      --| This procedure is actually the body for the flush procedure,
      --| but a generic instantiation cannot be used as a body for another
      --| procedure.  You tell me why.

    procedure flush(s: in out string_type) is
    begin
        if s /= null then real_flush(s); end if;
        -- Actually, the if isn't needed; however, DECada compiler chokes
        -- on deallocation of null.
    end flush;

    procedure mark is
    begin
        push(scopes, new string_list'(create));
    end mark;

    procedure release is
        procedure flush_list_ptr is
            new unchecked_deallocation(string_list, string_list_ptr);
        iter: string_list_pkg.ListIter;
        top_list: string_list_ptr;
        s: string_type;
    begin
        pop(scopes, top_list);
        iter := MakeListIter(top_list.all);
        while more(iter) loop
            next(iter, s);
            flush(s);             -- real_flush is bad, DECada bug
--          real_flush(s);            
        end loop;
        destroy(top_list.all);
        flush_list_ptr(top_list);
    exception
        when empty_stack =>
            raise illegal_dealloc;
    end release;
    
    
-- Queries:

    function is_empty(s: string_type)
        return boolean is
    begin
        return (s = null) or else (s.all = "");
    end is_empty;

    function length(s: string_type)
        return natural is
    begin
	if s = null then return 0; end if; 
        return(s.all'length);
    end length;

    function value(s: string_type)
        return string is
        subtype null_range is positive range 1..0;
        subtype null_string is string(null_range);
    begin
	if s = null then return null_string'(""); end if; 
        return s.all;
    end value;

    function fetch(s: string_type; i: positive)
        return character is
    begin
	if is_empty(s) or else (not (i in s'range)) then raise bounds; end if; 
        return s(i);
    end fetch;

    function equal(s1, s2: string_type)
        return boolean is
    begin
        if is_empty(s1) then return is_empty(s2); end if; 
        return (s2 /= null) and then (s1.all = s2.all); 
-- The above code replaces the following.  (DECada buggy)
--        return s1.all = s2.all;
--    exception
--	when constraint_error =>     -- s is null
--	    return is_empty(s1) and is_empty(s2);
    end equal;

    function equal(s1: string_type; s2: string)
        return boolean is
    begin
	if s1 = null then return s2 = ""; end if; 
        return s1.all = s2;
    end equal;

    function equal(s1: string; s2: string_type)
        return boolean is
    begin
	if s2 = null then return s1 = ""; end if; 
        return s1 = s2.all;
    end equal;

--|========================================================================

  function Equivalent (Left, Right : in String_Type) return Boolean is
  begin
    return Equal (Upper (Left), Upper (Right));
  end Equivalent;

  function Equivalent (Left  : in String;
                       Right : in String_Type) return Boolean is
  begin
    return Equivalent (Create (Left), Right);
  end Equivalent;

  function Equivalent (Left  : in String_Type;
                       Right : in String) return Boolean is
  begin
    return Equivalent (Left, Create (Right));
  end Equivalent;

--|========================================================================

    function "<" (s1: string_type; s2: string_type)
        return boolean is
    begin
        if is_empty(s1) then 
		return (not is_empty(s2)); 
	    else 
		return (s1.all < s2); 
	    end if; 
-- Got rid of the following code:  (Think that DECada is buggy)
        --return s1.all < s2.all; 
    --exception
        --when constraint_error =>   -- on null deref
	    --return (not is_empty(s2)); 
		   -- one of them must be empty
    end "<";

    function "<"(s1: string_type; s2: string)
        return boolean is 
    begin
	if s1 = null then return s2 /= ""; end if; 
        return s1.all < s2; 
    end "<";

    function "<"(s1: string; s2: string_type)
        return boolean is 
    begin
	if s2 = null then return false; end if; 
        return s1 < s2.all; 
    end "<";

    function "<="(s1: string_type; s2: string_type)
        return boolean is 
    begin
	if is_empty(s1) then return true; end if; 
	return (s1.all <= s2); 

    -- Replaces the following:  (I think DECada is buggy)
        --return s1.all <= s2.all; 
    --exception
        --when constraint_error =>   -- on null deref
            --return is_empty(s1);   -- one must be empty, so s1<=s2 iff s1 = ""
    end "<=";

    function "<="(s1: string_type; s2: string)
        return boolean is 
    begin
	if s1 = null then return true; end if; 
        return s1.all <= s2; 
    end "<=";

    function "<="(s1: string; s2: string_type)
        return boolean is 
    begin
	if s2 = null then return s1 = ""; end if; 
        return s1 <= s2.all; 
    end "<=";

    function match_c(s: string_type; c: character; start: positive := 1)
        return natural is
    begin
	if s = null then return 0; end if; 
        for i in start..s.all'last loop
            if s(i) = c then
                return i;
            end if;
        end loop;
        return 0;
    end match_c;

    function match_not_c(s: string_type; c: character; start: positive := 1)
        return natural is
    begin
	if s = null then return 0; end if; 
        for i in start..s.all'last loop
	    if s(i) /= c then
		return i;
	    end if;
        end loop;
    return 0;
    end match_not_c;

    function match_s(s1, s2: string_type; start: positive := 1)
        return natural is
    begin
	if (s1 = null) or else (s2 = null) then return 0; end if; 
        return match_string(s1.all, s2.all, start);
    end match_s;

    function match_s(s1: string_type; s2: string; start: positive := 1)
        return natural is
    begin
	if s1 = null then return 0; end if; 
        return match_string(s1.all, s2, start);
    end match_s;

    function match_any(s, any: string_type; start: positive := 1)
        return natural is
    begin
	if any = null then raise any_empty; end if; 
        return match_any(s, any.all, start);
    end match_any;

    function match_any(s: string_type; any: string; start: positive := 1)
        return natural is
    begin
        if any = "" then raise any_empty; end if;
        if s = null then return 0; end if;

        for i in start..s.all'last loop
            for j in any'range loop
                if s(i) = any(j) then
                    return i;
                end if;
            end loop;
        end loop;
        return 0;
    end match_any;

    function match_none(s, none: string_type; start: positive := 1)
        return natural is
    begin
	if is_empty(s) then return 0; end if; 
	if is_empty(none) then return 1; end if; 

        return match_none(s, none.all, start);
    end match_none;

    function match_none(s: string_type; none: string; start: positive := 1)
        return natural is
        found: boolean;
    begin
	if is_empty(s) then return 0; end if; 

        for i in start..s.all'last loop
            found := true;
            for j in none'range loop
                if s(i) = none(j) then
                    found := false;
                    exit;
                end if;
            end loop;
            if found then return i; end if;
        end loop;
        return 0;
    end match_none;


    -- Utilities:

    function enter(s: string_type)
        return string_type is
    begin
-- ATTACHING TO THE END OF THE LIST IS ENTIRELY TOO SLOW AND UNNECESSARY
--        top(scopes).all := attach(top(scopes).all, s);
        top(scopes).all := attach(s, top(scopes).all);
        return s;
    exception
        when empty_stack =>
            raise illegal_alloc;
    end enter;

    function match_string(s1, s2: string; start: positive := 1)
        return natural is
        offset: natural;
    begin
        offset := s2'length - 1;
        for i in start..(s1'last - offset) loop
            if s1(i..(i + offset)) = s2 then
                return i;
            end if;
        end loop;
        return 0; 
    exception when constraint_error =>    -- on offset := s2'length (= 0)
        return 0; 
    end match_string;

begin    -- Initialize the scopes stack with an implicit mark.
    scopes := create;
    mark;
end string_pkg;

