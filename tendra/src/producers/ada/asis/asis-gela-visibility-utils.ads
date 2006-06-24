------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $
--  Purpose:
--  Helper subprograms of lookup

private
package Asis.Gela.Visibility.Utils is

   function Is_Top_Declaration (Element : Asis.Element) return Boolean;

   function Need_New_Region (Element : Asis.Element) return Boolean;

   procedure Find_Parent_Region
     (Unit      : in     Asis.Compilation_Unit;
      Point     :    out Visibility.Point);

   procedure Unhide_Declaration
     (Element : in     Asis.Element;
      Point   : in     Visibility.Point);

   function Find_Name
     (Name             : Asis.Program_Text;
      Point            : Visibility.Point;
      With_Private     : Boolean := True;
      From_Visible     : Boolean := False;
      No_Parent_Region : Boolean := False)
      return Region_Item_Access;

   procedure Find_All
     (Item             : in     Region_Item_Access;
      Index            : in out ASIS_Natural;
      Result           : in out Asis.Defining_Name_List;
      Unit             : in     Asis.Compilation_Unit;
      Point            : in     Visibility.Point;
      No_Parent_Region : in     Boolean := False);

   procedure Strip_Homograph
     (Index            : in out Asis.List_Index;
      Result           : in out Asis.Defining_Name_List;
      Place            : in     Asis.Element);

   function Find_Region (Element : Asis.Element) return Visibility.Point;

   procedure Check_Completion
     (Declaration : Asis.Declaration;
      Point       : Visibility.Point);

   function Visible_From
     (Name  : in Region_Item_Access;
      Place : in Region_Item_Access) return Boolean;

   function Visible_From
     (Name  : in Asis.Defining_Name;
      Point : in Asis.Element) return Boolean;

   procedure Set_Place
     (Element : in Asis.Element;
      Point   : in Visibility.Point);

   procedure Set_Name_Place
     (Element : in Asis.Defining_Name;
      Point   : in Visibility.Point);

   function Goto_Enclosing_Region
     (Stmt  : in Asis.Statement) return Visibility.Point;

   function Is_Template (Decl : Asis.Declaration) return Boolean;

   function Is_Visible_Decl (Tipe : in Asis.Declaration) return Boolean;

   Top_Region : aliased Region_Node;

end Asis.Gela.Visibility.Utils;



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
