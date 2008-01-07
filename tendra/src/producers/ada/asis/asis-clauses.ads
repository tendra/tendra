------------------------------------------------------------------------------
------------------------------------------------------------------------------
--  19 package Asis.Clauses
------------------------------------------------------------------------------
------------------------------------------------------------------------------

package Asis.Clauses is
   pragma Preelaborate;

------------------------------------------------------------------------------
------------------------------------------------------------------------------
--  Asis.Clauses
--
--  This package encapsulates a set of queries that operate on A_Clause
--  elements.
--
--  |ER-----------------------------------------------------------------------
--  |ER A_Use_Package_Clause - 8.4
--  |ER A_Use_Type_Clause    - 8.4
--  |ER A_With_Clause        - 10.1.2
--  |CR
--  |CR Child elements returned by:
--  |CR    function Clause_Names
--  |CR
------------------------------------------------------------------------------
------------------------------------------------------------------------------
--  19.1 function Clause_Names
------------------------------------------------------------------------------

   function Clause_Names (Clause : in Asis.Element)
                          return Asis.Name_List;

------------------------------------------------------------------------------
--  Clause  - Specifies the with_clause or use_clause to query
--
--  Returns a list of the names that appear in the given clause.
--  The names in the list should be in their order of appearance in the
--  original clauses from the compilation text.
--
--  Results of this query may vary across ASIS implementations.  Some
--  implementations normalize all clauses containing multiple names
--  into an equivalent sequence of corresponding single clauses.
--  Similarly, an implementation may keep a name only once even though that
--  name can appear more than once in a clause.
--
--  Appropriate Element_Kinds:
--      A_Use_Package_Clause
--      A_Use_Type_Clause
--      A_With_Clause
--
--  Returns Expression_Kinds:
--      An_Identifier
--      A_Selected_Component
--      An_Attribute_Reference
--
--  |ER-----------------------------------------------------------------------
--  |ER A_Representation_Clause - 13.1
--  |ER-----------------------------------------------------------------------
--  |ER An_Attribute_Definition_Clause - 13.3
--  |ER An_Enumeration_Representation_Clause - 13.4
--  |ER An_At_Clause - J.7
--  |CR
--  |CR Child elements returned by:
--  |CR    function Representation_Clause_Name
--  |CR    function Representation_Clause_Expression
--
------------------------------------------------------------------------------
--  19.2 function Representation_Clause_Name
------------------------------------------------------------------------------

   function Representation_Clause_Name (Clause : in Asis.Clause)
                                        return Asis.Name;

------------------------------------------------------------------------------
--  Clause  - Specifies the representation_clause to query
--
--  Returns the direct_name expression following the reserved word "for".
--
--  Appropriate Clause_Kinds:
--      A_Representation_Clause
--      A_Component_Clause
--
--  Returns Expression_Kinds:
--      An_Identifier
--      An_Attribute_Reference
--
------------------------------------------------------------------------------
--  19.3 function Representation_Clause_Expression
------------------------------------------------------------------------------

   function Representation_Clause_Expression
               (Clause : in Asis.Representation_Clause)
                return Asis.Expression;

------------------------------------------------------------------------------
--  Clause  - Specifies the representation_clause to query
--
--  Returns the expression following the reserved word "use" or the reserved
--  words "use at".
--
--  Appropriate Representation_Clause_Kinds:
--      An_Attribute_Definition_Clause
--      An_Enumeration_Representation_Clause
--      An_At_Clause
--
--  Returns Element_Kinds:
--      An_Expression
--
--  |ER-----------------------------------------------------------------------
--  |ER A_Record_Representation_Clause - 13.5.1
--  |CR
--  |CR Child elements returned by:
--  |CR    function Representation_Clause_Name
--  |CR    function Mod_Clause_Expression
--  |CR    function Component_Clauses
--
------------------------------------------------------------------------------
--  19.4 function Mod_Clause_Expression
------------------------------------------------------------------------------

   function Mod_Clause_Expression (Clause : in Asis.Representation_Clause)
                                   return Asis.Expression;

------------------------------------------------------------------------------
--  Clause  - Specifies the record representation clause to query
--
--  Returns the static_expression appearing after the reserved words "at mod".
--
--  Returns a Nil_Element if a mod_clause is not present.
--
--  Appropriate Representation_Clause_Kinds:
--      A_Record_Representation_Clause
--
--  Returns Element_Kinds:
--      Not_An_Element
--      An_Expression
--
------------------------------------------------------------------------------
--  19.5 function Component_Clauses
------------------------------------------------------------------------------

   function Component_Clauses (Clause : in Asis.Representation_Clause;
                               Include_Pragmas : in Boolean := False)
                               return Asis.Component_Clause_List;

------------------------------------------------------------------------------
--  Clause          - Specifies the record representation clause to query
--  Include_Pragmas - Specifies whether pragmas are to be returned
--
--  Returns the component_clause and pragma elements from the
--  record_representation_clause, in their order of appearance.
--
--  Returns a Nil_Element_List if the record_representation_clause has no
--  component_clause or pragma elements.
--
--  Appropriate Representation_Clause_Kinds:
--      A_Record_Representation_Clause
--
--  Returns Element_Kinds:
--      A_Clause
--      A_Pragma
--
--  Returns Clause_Kinds:
--      A_Component_Clause
--
--  |ER-----------------------------------------------------------------------
--  |ER A_Component_Clause - 13.5.1
--  |CR
--  |CR Child elements returned by:
--  |CR    function Representation_Clause_Name
--  |CR    function Component_Clause_Position
--  |CR    function Component_Clause_Range
--
------------------------------------------------------------------------------
--  19.6 function Component_Clause_Position
------------------------------------------------------------------------------

   function Component_Clause_Position (Clause : in Asis.Component_Clause)
                                       return Asis.Expression;

------------------------------------------------------------------------------
--  Clause  - Specifies the component_clause to query
--
--  Returns the position expression for the component_clause.
--
--  Appropriate Clause_Kinds:
--      A_Component_Clause
--
--  Returns Element_Kinds:
--      An_Expression
--
------------------------------------------------------------------------------
--  19.7 function Component_Clause_Range
------------------------------------------------------------------------------

   function Component_Clause_Range (Clause : in Asis.Component_Clause)
                                    return Asis.Discrete_Range;

------------------------------------------------------------------------------
--  Clause  - Specifies the component_clause to query
--
--  Returns the first_bit .. last_bit range for the component_clause.
--
--  Appropriate Clause_Kinds:
--      A_Component_Clause
--
--  Returns Discrete_Range_Kinds:
--      A_Discrete_Simple_Expression_Range
--
------------------------------------------------------------------------------

end Asis.Clauses;


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
