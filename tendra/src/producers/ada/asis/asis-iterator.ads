-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  14	package Asis.Iterator
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

package Asis.Iterator is

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  Asis.Iterator encapsulates the generic procedure Traverse_Element which
--  allows an ASIS application to perform an iterative traversal of a
--  logical syntax tree. It requires the use of two generic procedures,
--  Pre_Operation, which identifies processing for the traversal, and
--  Post_Operation, which identifies processing after the traversal.
--  The State_Information allows processing state to be passed during the
--  iteration of Traverse_Element.
--
--  Package Asis.Iterator is established as a child package to highlight the
--  iteration capability and to facilitate the translation of ASIS to IDL.
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  14.1 procedure Traverse_Element
-------------------------------------------------------------------------------

   generic

      type State_Information is limited private;

      with procedure Pre_Operation
                        (Element : in     Asis.Element;
                         Control : in out Traverse_Control;
                         State   : in out State_Information) is <>;

      with procedure Post_Operation
                        (Element : in     Asis.Element;
                         Control : in out Traverse_Control;
                         State   : in out State_Information) is <>;

   procedure Traverse_Element
               (Element : in     Asis.Element;
                Control : in out Traverse_Control;
                State   : in out State_Information);

-------------------------------------------------------------------------------
--  Element             - Specifies the initial element in the traversal
--  Control             - Specifies what next to do with the traversal
--  State_Information   - Specifies other information for the traversal
--
--  Traverses the element and all its component elements, if any.
--  Component elements are all elements that can be obtained by a combination
--  of the ASIS structural queries appropriate for the given element.
--
--  If an element has one or more component elements, each is called a child
--  element.  An element's parent element is its Enclosing_Element.  Children
--  with the same parent are sibling elements.  The type Traverse_Control uses
--  the terms children and siblings to control the traverse.
--
--  For each element, the formal procedure Pre_Operation is called when first
--  visiting the element.  Each of that element's children are then visited
--  and finally the formal procedure Post_Operation is called for the element.
--
--  The order of Element traversal is in terms of the textual representation of
--  the Elements.  Elements are traversed in left-to-right and top-to-bottom
--  order.
--
--  Traversal of Implicit Elements:
--
--  Implicit elements are not traversed by default.  However, they may be
--  explicitly queried and then passed to the traversal instance.  Implicit
--  elements include implicit predefined operator declarations, implicit
--  inherited subprogram declarations, implicit expanded generic specifications
--  and bodies, default expressions supplied to procedure, function, and entry
--  calls, etc.
--
--  Applications that wish to traverse these implicit Elements shall query for
--  them at the appropriate places in a traversal and then recursively call
--  their instantiation of the traversal generic.  (Implicit elements provided
--  by ASIS do not cover all possible Ada implicit constructs.  For example,
--  implicit initializations for variables of an access type are not provided
--  by ASIS.)
--
--  Traversal of Association lists:
--
--  Argument and association lists for procedure calls, function calls, entry
--  calls, generic instantiations, and aggregates are traversed in their
--  unnormalized forms, as if the Normalized parameter was False for those
--  queries.  Implementations that always normalize certain associations may
--  return Is_Normalized associations.  See the Implementation Permissions
--  for the queries Discriminant_Associations, Generic_Actual_Part,
--  Call_Statement_Parameters, Record_Component_Associations, or
--  Function_Call_Parameters.
--
--  Applications that wish to explicitly traverse normalized associations can
--  do so by querying the appropriate locations in order to obtain the
--  normalized list.  The list can then be traversed by recursively calling
--  the traverse instance.  Once that sub-traversal is finished, the Control
--  parameter can be set to Abandon_Children to skip processing of the
--  unnormalized argument list.
--
--  Traversal can be controlled with the Control parameter.
--
--  A call to an instance of Traverse_Element will not result in calls to
--  Pre_Operation or Post_Operation unless Control is set to Continue.
--
--  The subprograms matching Pre_Operation and Post_Operation can set
--  their Control parameter to affect the traverse:
--
--  - Continue
--
--    o Continues the normal depth-first traversal.
--
--  - Abandon_Children
--
--    o Prevents traversal of the current element's children.
--
--    o If set in a Pre_Operation, traversal picks up with the next sibling
--      element of the current element.
--
--    o If set in a Post_Operation, this is the same as Continue, all children
--      will already have been traversed.  Traversal picks up with the
--      Post_Operation of the parent.
--
--  - Abandon_Siblings
--
--    o Prevents traversal of the current element's children and remaining
--      siblings.
--
--    o If set in a Pre_Operation, this abandons the associated Post_Operation
--      for the current element.  Traversal picks up with the Post_Operation
--      of the parent.
--
--    o If set in a Post_Operation, traversal picks up with the Post_Operation
--      of the parent.
--
--  - Terminate_Immediately
--
--    o Does exactly that.
--
--  Raises ASIS_Inappropriate_Element if the element is a Nil_Element
--
-------------------------------------------------------------------------------

end Asis.Iterator;


------------------------------------------------------------------------------
--  Copyright (c) 2006, Maxim Reznik
--  All rights reserved.
--
--  Redistribution and use in source and binary forms, with or without
--  modification, are permitted provided that the following conditions are met:
--
--     * Redistributions of source code must retain the above copyright notice,
--     * this list of conditions and the following disclaimer.
--     * Redistributions in binary form must reproduce the above copyright
--     * notice, this list of conditions and the following disclaimer in the
--     * documentation and/or other materials provided with the distribution.
--
--  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
--  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
--  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
--  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
--  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
--  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
--  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
--  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
--  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
--  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
--  POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------
