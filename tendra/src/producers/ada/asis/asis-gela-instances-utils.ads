------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Helper subprograms to build instances of generics

package Asis.Gela.Instances.Utils is

   procedure Set_Instance (Item, Source : Asis.Element);

   procedure Set_Corresponding_Declaration  (Item, Source : Asis.Element);
   procedure Set_Corresponding_Body (Item, Source : Asis.Element);

   procedure Set_Generic_Element (Item, Source : Asis.Element);

   function Make_Constant
     (Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in     Asis.Expression) return Asis.Defining_Name;

   function Make_Object
     (Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in     Asis.Expression) return Asis.Defining_Name;

   function Make_Type
     (Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in     Asis.Expression) return Asis.Defining_Name;

   function Make_Procedure
     (Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in     Asis.Expression) return Asis.Defining_Name;

   function Make_Function
     (Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in     Asis.Expression) return Asis.Defining_Name;

   function Make_Package_Renaming
     (Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in     Asis.Expression) return Asis.Defining_Name;

   procedure New_Normalized_Association
     (Inst   : in     Asis.Declaration;
      Name   : in     Asis.Defining_Name;
      Actual : in out Asis.Expression);

   function Clone_Declaration
     (Item   : Asis.Element;
      Parent : Asis.Element) return Asis.Element;

   procedure Clone_Views
     (Object : in     Cloner_Class;
      Inst   : in     Asis.Declaration;
      Target : in     Asis.Declaration);

end Asis.Gela.Instances.Utils;


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
