
-- Module       : stack_pkg.ada
-- Component of : common_library
-- Version      : 1.2
-- Date         : 11/21/86  16:32:31
-- SCCS File    : disk21~/rschm/hasee/sccs/common_library/sccs/sxstack_pkg.ada

-- $Source: /nosc/work/abstractions/stack/RCS/stack.bdy,v $
-- $Revision: 1.3 $ -- $Date: 85/02/01 10:19:36 $ -- $Author: ron $

-- $Source: /nosc/work/abstractions/stack/RCS/stack.bdy,v $
-- $Revision: 1.3 $ -- $Date: 85/02/01 10:19:36 $ -- $Author: ron $

with unchecked_deallocation;

package body stack_pkg is

  SCCS_ID : constant String := "@(#) stack_pkg.ada, Version 1.2";



--| Overview:
--| Implementation scheme is totally described by the statements of the
--| representation invariants and abstraction function that appears in
--| the package specification.  The implementation is so trivial that
--| further documentation is unnecessary.

    use elem_list_pkg;
    
    
  -- Constructors:
    
    function create
        return stack is
    begin
	return new stack_rec'(size => 0, elts => create);
    end create;
    
    procedure push(s: in out stack;
                   e:        elem_type) is
    begin
        s.size := s.size + 1;
        s.elts := attach(e, s.elts);
    exception
        when constraint_error =>
            raise uninitialized_stack;
    end push;

    procedure pop(s: in out stack) is
    begin
        DeleteHead(s.elts);
        s.size := s.size - 1;
    exception
        when EmptyList =>
            raise empty_stack;
	when constraint_error =>
	    raise uninitialized_stack;
    end pop;

    procedure pop(s: in out stack;
                  e: out    elem_type) is
    begin
        e := FirstValue(s.elts);
        DeleteHead(s.elts);
        s.size := s.size - 1;
    exception
        when EmptyList =>
            raise empty_stack;
	when constraint_error =>
	    raise uninitialized_stack;
    end pop;
    
    function copy(s: stack)
        return stack is
    begin
	if s = null then raise uninitialized_stack; end if;
	
	return new stack_rec'(size => s.size,
			      elts => copy(s.elts));
    end;

    
  -- Queries:

    function top(s: stack)
        return elem_type is
    begin
        return FirstValue(s.elts);
    exception
        when EmptyList =>
	    raise empty_stack;
	when constraint_error =>
	    raise uninitialized_stack;
    end top;

    function size(s: stack)
        return natural is
    begin
        return s.size;
    exception
        when constraint_error =>
	    raise uninitialized_stack;
    end size;

    function is_empty(s: stack)
        return boolean is
    begin
        return s.size = 0;
    exception
        when constraint_error =>
	    raise uninitialized_stack;
    end is_empty;


  -- Heap Management:
    
    procedure destroy(s: in out stack) is
        procedure free_stack is
	    new unchecked_deallocation(stack_rec, stack);
    begin
	destroy(s.elts);
	free_stack(s);
    exception
        when constraint_error =>    -- stack is null
            return; 
    end destroy;
   
end stack_pkg;
