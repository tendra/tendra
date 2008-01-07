-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  7   package Asis.Implementation.Permissions
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

package Asis.Implementation.Permissions is

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  7.1 function Is_Formal_Parameter_Named_Notation_Supported
-------------------------------------------------------------------------------

   function Is_Formal_Parameter_Named_Notation_Supported return Boolean;

-------------------------------------------------------------------------------
--  Returns True if it is possible to detect usage of named notation.
--
--  Returns False if this implementation will always change parameter lists
--  using named notation to positional lists in function, subprogram, and
--  entry calls.  In that case, the Formal_Parameter query will always return
--  a Nil_Element unless the parameter list is obtained with Normalized = True.
--
--  This function affects association lists for aggregates, instantiations,
--  discriminant lists, entry calls, and subprogram calls.
--
-------------------------------------------------------------------------------
--  7.2 function Default_In_Mode_Supported
-------------------------------------------------------------------------------

   function Default_In_Mode_Supported return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the A_Default_In_Mode kind is supported by this
--  implementation.
--
-------------------------------------------------------------------------------
--  7.3 function Generic_Actual_Part_Normalized
-------------------------------------------------------------------------------

   function Generic_Actual_Part_Normalized return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the query Generic_Actual_Part will always return
--  artificial Is_Normalized associations using the defining_identifier
--  instead of the generic_formal_parameter_selector_name, and using
--  default_expression or default_name.
--
--  If Generic_Actual_Part_Normalized then the query Generic_Actual_Part will
--  always behave as if called with Normalized => True.
--
-------------------------------------------------------------------------------
--  7.4 function Record_Component_Associations_Normalized
-------------------------------------------------------------------------------

   function Record_Component_Associations_Normalized return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the query Record_Component_Associations will always return
--  artificial Is_Normalized associations using the defining_identifier
--  instead of the component_selector_name.
--
--  If Record_Component_Associations_Normalized then the query
--  Record_Component_Associations will always behave as if called with
--  Normalized => True.
--

-------------------------------------------------------------------------------
--  7.5 function Is_Prefix_Call_Supported
-------------------------------------------------------------------------------

   function Is_Prefix_Call_Supported return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the ASIS implementation has the ability to determine
--  whether calls are in prefix form.
--
-------------------------------------------------------------------------------
--  7.6 function Function_Call_Parameters_Normalized
-------------------------------------------------------------------------------

   function Function_Call_Parameters_Normalized return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the query Function_Call_Parameters will always return
--  artificial Is_Normalized associations using the defining_identifier
--  instead of the formal_parameter_selector_name, and using the
--  default_expression.
--
--  If Function_Call_Parameters_Normalized then the query
--  Function_Call_Parameters will always behave as if called with
--  Normalized => True.
--
-------------------------------------------------------------------------------
--  7.7 function Call_Statement_Parameters_Normalized
-------------------------------------------------------------------------------

   function Call_Statement_Parameters_Normalized return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the query Call_Statement_Parameters will always return
--  artificial Is_Normalized associations using the defining_identifier
--  instead of the formal_parameter_selector_name, and using the
--  default_expression.
--
--  If Call_Statement_Parameters_Normalized then the query
--  Call_Statement_Parameters will always behave as if called with
--  Normalized => True.
--
-------------------------------------------------------------------------------
--  It is not possible to obtain either a normalized or
--  unnormalized Discriminant_Association list for an unconstrained record
--  or derived subtype_indication where the discriminant_association is
--  supplied by default; there is no constraint to query, and a Nil_Element
--  is returned from the query Subtype_Constraint.
--
-------------------------------------------------------------------------------
--  7.8 function Discriminant_Associations_Normalized
-------------------------------------------------------------------------------

   function Discriminant_Associations_Normalized return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the query Discriminant_Associations will always return
--  artificial Is_Normalized associations using the defining_identifier
--  instead of the discriminant_selector_name.
--
--  If Discriminant_Associations_Normalized then the query
--  Discriminant_Associations will always behave as if called with
--  Normalized => True.
--

-------------------------------------------------------------------------------
--  7.9 function Is_Line_Number_Supported
-------------------------------------------------------------------------------

   function Is_Line_Number_Supported return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the implementation can return valid line numbers for
--  Elements.
--
--  An implementation may choose to ignore line number values in which case
--  this function returns False.
--
-------------------------------------------------------------------------------
--  7.10 function Is_Span_Column_Position_Supported
-------------------------------------------------------------------------------

   function Is_Span_Column_Position_Supported return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the implementation can return valid character positions for
--  elements.
--
--  An implementation may choose to ignore column character position values
--  within spans in which case this function returns False.  This function will
--  be False if Is_Line_Number_Supported = False.
--
-------------------------------------------------------------------------------
--  7.11 function Is_Commentary_Supported
-------------------------------------------------------------------------------

   function Is_Commentary_Supported return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the implementation can return comments.
--
--  An implementation may choose to ignore comments in the text in which case
--  the function Is_Commentary_Supported returns False.
--
-------------------------------------------------------------------------------
--  7.12 function Attributes_Are_Supported
-------------------------------------------------------------------------------

   function Attributes_Are_Supported return Boolean;

-------------------------------------------------------------------------------
--  Returns True if an implementation supports compilation unit attributes.
--  Returns False if all attributes will return Has_Attribute() = False.
--
-------------------------------------------------------------------------------
--  7.13 function Implicit_Components_Supported
-------------------------------------------------------------------------------

   function Implicit_Components_Supported return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the implementation provides elements representing
--  implicit implementation-defined record components.
--
-------------------------------------------------------------------------------
--  7.14 function Object_Declarations_Normalized
-------------------------------------------------------------------------------

   function Object_Declarations_Normalized return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the implementation normalizes multiple object declarations
--  to an equivalent sequence of single declarations.
--
-------------------------------------------------------------------------------
--  7.15 function Predefined_Operations_Supported
-------------------------------------------------------------------------------

   function Predefined_Operations_Supported return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the implementation supports queries of predefined
--  operations.
--
-------------------------------------------------------------------------------
--  7.16 function Inherited_Declarations_Supported
-------------------------------------------------------------------------------

   function Inherited_Declarations_Supported return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the implementation supports queries of inherited
--  declarations.
--
-------------------------------------------------------------------------------
--  7.17 function Inherited_Subprograms_Supported
-------------------------------------------------------------------------------

   function Inherited_Subprograms_Supported return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the implementation supports queries of inherited
--  subprograms.
--
-------------------------------------------------------------------------------
--  7.18 function Generic_Macro_Expansion_Supported
-------------------------------------------------------------------------------

   function Generic_Macro_Expansion_Supported return Boolean;

-------------------------------------------------------------------------------
--  Returns True if the implementation expands generics using macros to
--  supports queries.
-------------------------------------------------------------------------------

end Asis.Implementation.Permissions;


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
