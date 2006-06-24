
-- Module       : stack_pkg_.ada
-- Component of : common_library
-- Version      : 1.2
-- Date         : 11/21/86  16:33:02
-- SCCS File    : disk21~/rschm/hasee/sccs/common_library/sccs/sxstack_pkg_.ada

-- $Source: /nosc/work/abstractions/stack/RCS/stack.spc,v $
-- $Revision: 1.5 $ -- $Date: 85/02/01 09:57:17 $ -- $Author: ron $

-- $Source: /nosc/work/abstractions/stack/RCS/stack.spc,v $
-- $Revision: 1.5 $ -- $Date: 85/02/01 09:57:17 $ -- $Author: ron $

with lists;     --| Implementation uses lists.  (private)

generic
    type elem_type is private;   --| Component element type.

package stack_pkg is

--| Overview:
--| This package provides the stack abstract data type.  Element type is
--| a generic formal parameter to the package.  There are no explicit
--| bounds on the number of objects that can be pushed onto a given stack.
--| All standard stack operations are provided.
--|
--| The following is a complete list of operations, written in the order
--| in which they appear in the spec.  Overloaded subprograms are followed
--| by (n), where n is the number of subprograms of that name.
--|
--| Constructors:
--|        create 
--|        push
--|        pop (2)
--|        copy
--| Query Operations:
--|        top
--|        size
--|        is_empty
--| Heap Management: 
--|        destroy


--| Notes:
--| Programmer: Ron Kownacki

    type stack is private;       --| The stack abstract data type.
    
  -- Exceptions:
  
    uninitialized_stack: exception;
        --| Raised on attempt to manipulate an uninitialized stack object.
	--| The initialization operations are create and copy.

    empty_stack: exception;
        --| Raised by some operations when empty.


  -- Constructors:
    
    function create
        return stack;
	
      --| Effects:
      --| Return the empty stack.

    procedure push(s: in out stack;
                   e:        elem_type);

      --| Raises: uninitialized_stack
      --| Effects:
      --| Push e onto the top of s.
      --| Raises uninitialized_stack iff s has not been initialized.
      
    procedure pop(s: in out stack);
      
      --| Raises: empty_stack, uninitialized_stack
      --| Effects:
      --| Pops the top element from s, and throws it away.
      --| Raises empty_stack iff s is empty.
      --| Raises uninitialized_stack iff s has not been initialized.

    procedure pop(s: in out stack;
		  e: out    elem_type);

      --| Raises: empty_stack, uninitialized_stack
      --| Effects:
      --| Pops the top element from s, returns it as the e parameter.
      --| Raises empty_stack iff s is empty.
      --| Raises uninitialized_stack iff s has not been initialized.
      
    function copy(s: stack)
	return stack;
	  
      --| Raises: uninitialized_stack
      --| Return a copy of s.
      --| Stack assignment and passing stacks as subprogram parameters
      --| result in the sharing of a single stack value by two stack
      --| objects; changes to one will be visible through the others.
      --| copy can be used to prevent this sharing.
      --| Raises uninitialized_stack iff s has not been initialized.
  
      
  -- Queries:

    function top(s: stack)
        return elem_type;

      --| Raises: empty_stack, uninitialized_stack
      --| Effects:
      --| Return the element on the top of s.  Raises empty_stack iff s is
      --| empty.
      --| Raises uninitialized_stack iff s has not been initialized.
      
    function size(s: stack)
        return natural;

      --| Raises: uninitialized_stack
      --| Effects:
      --| Return the current number of elements in s.
      --| Raises uninitialized_stack iff s has not been initialized.

    function is_empty(s: stack)
        return boolean;

      --| Raises: uninitialized_stack
      --| Effects:
      --| Return true iff s is empty.
      --| Raises uninitialized_stack iff s has not been initialized.


  -- Heap Management:

    procedure destroy(s: in out stack);
    
      --| Effects:
      --| Return the space consumed by s to the heap.  No effect if s is
      --| uninitialized.  In any case, leaves s in uninitialized state.


private

    package elem_list_pkg is new lists(elem_type);
    subtype elem_list is elem_list_pkg.list;

    type stack_rec is
        record
            size: natural := 0;
            elts: elem_list := elem_list_pkg.create;
        end record;
	
    type stack is access stack_rec;

    --| Let an instance of the representation type, r, be denoted by the
    --| pair, <size, elts>.  Dot selection is used to refer to these
    --| components.
    --|
    --| Representation Invariants:
    --|     r /= null
    --|     elem_list_pkg.length(r.elts) = r.size.
    --|
    --| Abstraction Function:
    --|     A(<size, elem_list_pkg.create>) = stack_pkg.create.
    --|     A(<size, elem_list_pkg.attach(e, l)>) = push(A(<size, l>), e).

end stack_pkg;

