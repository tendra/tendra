with Asis.Iterator;
with Asis.Elements;
with Traversing_Actions;

procedure Process_Unit (The_Unit : Asis.Compilation_Unit) is

   procedure Walk is new
      Asis.Iterator.Traverse_Element
        (State_Information => Traversing_Actions.Traversal_State,
         Pre_Operation     => Traversing_Actions.Pre_Action,
         Post_Operation    => Traversing_Actions.Post_Action);

   Process_Control : Asis.Traverse_Control := Asis.Continue;

   Unit_Decl : Asis.Element := Asis.Elements.Unit_Declaration (The_Unit);
   Clauses   : constant Asis.Element_List :=
     Asis.Elements.Context_Clause_Elements (The_Unit, True);


begin
   for I in Clauses'Range loop
      Walk (Clauses (I), Process_Control, Traversing_Actions.Global_State);
   end loop;

   Walk (Unit_Decl, Process_Control, Traversing_Actions.Global_State);
end Process_Unit;


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
