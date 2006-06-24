package body Asis.Gela.Elements.Expr.Utils is

   ----------------------------------------------------
   -- Remove_From_Corresponding_Name_Definition_List --
   ----------------------------------------------------

   procedure Remove_From_Corresponding_Name_Definition_List
     (Node : in out Base_Identifier_Node;
      Name : in     Asis.Element)
   is
      use Lists.Secondary_Definition_Lists;
   begin
      Remove (Node.Corresponding_Name_Definition_List, Name);
   end Remove_From_Corresponding_Name_Definition_List;

   ----------------------------
   -- Remove_From_References --
   ----------------------------

   procedure Remove_From_References
     (Node    : in out Defining_Name_Node;
      Item    : in     Asis.Element)
   is
      use Lists.Secondary_Reference_Lists;
   begin
      Remove (Node.References, Item);
   end Remove_From_References;

end Asis.Gela.Elements.Expr.Utils;



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
