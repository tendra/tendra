-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  12   package Asis.Compilation_Units.Relations
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

package Asis.Compilation_Units.Relations is

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  Asis.Compilation_Units.Relations encapsulates semantic relationship
--  concepts used in ASIS.
-------------------------------------------------------------------------------
--  12.1 type Relationship
-------------------------------------------------------------------------------
--  Relationship queries provide references to compilation units that are
--  related, in some specific fashion, to one or more given compilation units.
--  Compilation units located by these queries are returned as a set of
--  ordered lists.

   type Relationship (Consistent_Length   : Asis.ASIS_Natural;
                      Inconsistent_Length : Asis.ASIS_Natural;
                      Missing_Length      : Asis.ASIS_Natural;
                      Circular_Length     : Asis.ASIS_Natural) is
      record
         Consistent   : Asis.Compilation_Unit_List (1 .. Consistent_Length);
         Inconsistent : Asis.Compilation_Unit_List (1 .. Inconsistent_Length);
         Missing      : Asis.Compilation_Unit_List (1 .. Missing_Length);
         Circular     : Asis.Compilation_Unit_List (1 .. Circular_Length);
      end record;

--  The following describes the semantics of the unit lists returned by the
--  queries Semantic_Dependence_Order and Elaboration_Order:
--
--  Each query returns a set of four lists.  Every unit returned will have the
--  same Enclosing_Context.  The lists are:
--
--  - Consistent: A list of consistent ordered units.
--
--  - Inconsistent: A list of units that are inconsistent with one or more
--    units on which they semantically depend.
--
--  - Missing: A list of units that have missing (nonexistent) related units.
--
--  - Circular: A list of circular semantic dependencies between units.
--
--  These lists are further described as:
--
--  a) Consistent units list:
--
--     The semantics for the ordering of units in the first list are defined by
--     the individual queries.
--
--     Every unit in this list is unique.  No duplicates are returned; no
--     two units in the list are Is_Equal or Is_Identical.
--
--  b) Inconsistent units list:
--
--     The second list is made up of unit pairs.
--
--     Each pairing defines an inconsistent semantic dependence relationship.
--     The right unit of each pair semantically depends on the preceding left
--     unit. All rightmost units of each pair are always inconsistent, and will
--     not appear in the consistent units list.  The leftmost unit can be
--     either consistent or inconsistent. If a leftmost units is consistent,
--     then it also appears in the consistent units list; otherwise the unit
--     is part of an inconsistent transitive relationship.
--
--     The unit pairs are ordered such that there are no forward semantic
--     dependencies between the inconsistent units.  Each inconsistent unit's
--     supporters always precede it in the list.
--
--     As an example, given four units, A withs B, B withs C, and C withs D;
--     if D is replaced, the inconsistent list contains six units with the
--     three pairs:
--
--        DC  CB  BA
--
--     The list indicates that units C, B, and A are inconsistent (the
--     rightmost units of each pair).  Semantic dependencies such as B depends
--     on C also are indicated.  The units C, B, and A are in an order that
--     could be submitted to the compiler (a possible recompilation order).
--
--     If a unit is inconsistent because the source for the unit has been
--     edited (or otherwise been made inconsistent by some action of the user
--     or implementation) then the unit references Nil_Compilation_Unit as the
--     cause of the inconsistency (e.g., (Nil A Nil B) is a list of two
--     inconsistent units, neither of which can point to a third unit as the
--     cause for their being inconsistent).
--
--  |IP Implementation Permissions
--  |IP
--  |IP An implementation is allowed to use Nil_Compilation_Unit value for
--  |IP the first unit of each pair if it cannot determine the supporting unit
--  |IP causing the inconsistent semantic dependence.
--
--     For the above example, the list returned is:
--
--           DC DB DA CB CA BA
--
--     This list reports all dependencies:
--
--           D withed by C withed by B withed by A => DC DB DA
--                       C withed by B withed by A => CB CA
--                                   B withed by A => BA
--
--  c) Missing dependence list:
--
--     The third list is made up of unit pairs.   Each pairing consists of a
--     unit followed by a missing related unit needed by the first unit.
--     A missing unit is a required Compilation_Unit, with a known name, with a
--     Unit_Kind that is either A_Nonexistent_Declaration or
--     A_Nonexistent_Body.
--
--     For example:
--
--     Given a list containing the units:  AB AC
--
--       If Unit_Kind(B) = A_Nonexistent_Declaration and
--          Unit_Kind(C) = A_Nonexistent_Body then
--
--       It can be deduced that:
--          A is missing a needed supporter B (A depends semantically on B).
--          A is missing a needed related unit body C (depending on the kind
--          for A, C can be A's required body or some subunit of A).
--
--     A unit is reported as missing only if the Post-Compilation Rules of Ada
--     determine it to be needed.  Reference Manual 10.2.
--
--  d) Circular dependence list:
--
--     Circular dependencies between compilation units are provided in the
--     fourth list.  There may be more than one set of circular dependencies.
--     The ordering of distinct sets in the list is implementation-defined.
--     This list will never contain nonexistent units.
--
--     The list is made up of unit pairs.  The second unit of each pair depends
--     semantically on the first unit.  A circularity is established when the
--     first unit of a pair also appears as the second unit of a later pair.
--     (See the unit A in the example below; it is the first unit of the first
--     pair and is the second unit of the third pair).  The next set of
--     circular dependent units, if any, starts with the next unit in the list
--     (the unit D in the example below).
--
--     For example:
--
--     Given a list containing the units:  AC CB BA DG GF FE ED
--
--       It can be determined that there are two sets of circularly dependent
--       units:
--          {A, B, C} and {D, E, F, G}
--
--       The dependencies are:  A depends on B, B depends on C, C depends on A.
--              D depends on E, E depends on F, F depends on G, G depends on D.
--
--     Each circle of dependence is reported exactly once.  It is not reported
--     once for each unit in the circle.
--
-------------------------------------------------------------------------------
--  12.2 constant Nil_Relationship
-------------------------------------------------------------------------------

   Nil_Relationship : constant Relationship :=
     (Consistent_Length   => 0,
      Inconsistent_Length => 0,
      Missing_Length      => 0,
      Circular_Length     => 0,
      Consistent          => Asis.Nil_Compilation_Unit_List,
      Inconsistent        => Asis.Nil_Compilation_Unit_List,
      Missing             => Asis.Nil_Compilation_Unit_List,
      Circular            => Asis.Nil_Compilation_Unit_List);

-------------------------------------------------------------------------------
--  12.3 function Semantic_Dependence_Order
-------------------------------------------------------------------------------
--      Semantic Dependence Relationships    - Reference Manual 10.1.1(24).
--      Elaboration Dependence Relationships - Reference Manual 10.1.1(25).
--
--  |AN Application Note:
--  |AN
--  |AN To properly determine unit consistency, use one of the two semantic
--  |AN dependence queries: Elaboration_Order or Semantic_Dependence_Order.
--  |AN These queries return a value of the type Relationship, which contains
--  |AN lists of consistent, inconsistent, missing and circular units.
--  |AN
--  |AN For these two queries, the existence of units in one or more of the
--  |AN inconsistent, missing, or circular units list means that the consistent
--  |AN unit list may not be complete.
--  |AN
--  |AN Applications that do not check for inconsistent, missing, or circular
--  |AN units before using the consistent list might not operate as expected.
--
-------------------------------------------------------------------------------

   function Semantic_Dependence_Order
     (Compilation_Units : in Asis.Compilation_Unit_List;
      Dependent_Units   : in Asis.Compilation_Unit_List;
      The_Context       : in Asis.Context;
      Relation          : in Asis.Relation_Kinds)
     return Relationship;

-------------------------------------------------------------------------------
--  Compilation_Units   - Specifies a list of pertinent units
--  Dependent_Units     - Specifies dependents used to limit the query
--  The_Context         - Specifies a program Context for context
--  Relation            - Specifies the relationship to query
--
--  Produces a Relationship value containing compilation_unit elements related
--  to the given Compilation_Units by the specified relation.
--
--  The compilation_unit elements in the consistent units list are ordered
--  such that there are no forward semantic dependencies.
--
--  Dependent_Units are ignored unless the Relation is Descendants or
--  Dependents.  The union of units in the needed units of the Dependent_Units
--  list provide a limiting context for the query.  Only members of these
--  needed units are present in the result.
--
--  If the Dependent_Units list is Is_Nil, the context for the search is the
--  entire Context.  The result of such a query is the full (unlimited)
--  list of Dependents for the Compilation_Units.
--

--  All units in the result will have an Enclosing_Context value that
--  Is_Identical to The_Context.
--
--  Appropriate Unit_Kinds:
--       A_Procedure
--       A_Function
--       A_Package
--       A_Generic_Procedure
--       A_Generic_Function
--       A_Generic_Package
--       A_Procedure_Instance
--       A_Function_Instance
--       A_Package_Instance
--       A_Procedure_Renaming
--       A_Function_Renaming
--       A_Package_Renaming
--       A_Generic_Procedure_Renaming
--       A_Generic_Function_Renaming
--       A_Generic_Package_Renaming
--       A_Procedure_Body
--       A_Function_Body
--       A_Package_Body
--       A_Procedure_Body_Subunit
--       A_Function_Body_Subunit
--       A_Package_Body_Subunit
--       A_Task_Body_Subunit
--       A_Protected_Body_Subunit
--       An_Unknown_Unit            --  See Implementation Permissions
--
--  The Semantic_Dependence_Order query should never raise an exception
--  when processing inconsistent unit (sub)sets.  This query is the only
--  means for an application to know if a given unit is consistent with
--  (some of) its supporters (dependents), and therefore the related
--  semantic processing can give valuable results for this unit.
--
--  |IP Implementation Permissions:
--  |IP
--  |IP The handling of An_Unknown_Unit is implementation specific.  It can be
--  |IP possible to obtain Semantic Dependence Relationships when starting
--  |IP with a list containing one or more units that are An_Unknown_Unit.
--  |IP However, results may vary across ASIS implementations.
--
--  |AN Application Note:
--  |AN
--  |AN Semantic_Dependence_Order defines consistent units to be ordered such
--  |AN that there are no forward semantic dependencies.
--
-------------------------------------------------------------------------------
--  12.4 function Elaboration_Order
-------------------------------------------------------------------------------

   function Elaboration_Order
     (Compilation_Units : in Asis.Compilation_Unit_List;
      The_Context       : in Asis.Context)
     return Relationship;

-------------------------------------------------------------------------------
--  Compilation_Units   - Specifies a list of units to elaborate
--  The_Context         - Specifies a program Context for context
--
--  Produces, in elaboration order, a Relationship value containing compilation
--  units required to elaborate the given compilation units.
--
--  The return value contains the set of ordered lists described above for the
--  queries on Semantic Dependence Relationships.  If the inconsistent,
--  missing, and circular lists are empty, the consistent list will contain
--  all units required to elaborate the arguments.
--
--  |IP Implementation Permissions:
--  |IP
--  |IP The Relationship value may include any number of
--  |IP implementation-specific runtime support packages.
--
--  The first unit in the Consistent units list will always be the
--  specification for package Standard.  The list will contain all units
--  required to elaborate the arguments.
--
--  Use the Context_Clause_Elements query to get pragma Elaborate elements
--  for a compilation unit.
--
--  Appropriate Unit_Kinds:
--       A_Procedure
--       A_Function
--       A_Package
--       A_Generic_Procedure
--       A_Generic_Function
--       A_Generic_Package
--       A_Procedure_Instance
--       A_Function_Instance
--       A_Package_Instance
--       A_Procedure_Renaming
--       A_Function_Renaming
--       A_Package_Renaming
--       A_Generic_Procedure_Renaming
--       A_Generic_Function_Renaming
--       A_Generic_Package_Renaming
--       A_Procedure_Body
--       A_Function_Body
--       A_Package_Body
--       A_Procedure_Body_Subunit
--       A_Function_Body_Subunit
--       A_Package_Body_Subunit
--       A_Task_Body_Subunit
--       A_Protected_Body_Subunit
--       An_Unknown_Unit            -- See Implementation Permissions
--
--  |IP Implementation Permissions:
--  |IP
--  |IP The handling of An_Unknown_Unit is implementation specific.  It can
--  |IP be possible to obtain Semantic Dependence Relationships when starting
--  |IP with a list containing one or more units that are An_Unknown_Unit.
--  |IP However, results may vary across ASIS implementations.
--
-------------------------------------------------------------------------------

end Asis.Compilation_Units.Relations;


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
