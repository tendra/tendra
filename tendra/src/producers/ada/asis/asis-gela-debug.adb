with Asis.Elements;

with Ada.Wide_Text_IO;
with Ada.Strings.Wide_Maps;
with Ada.Strings.Wide_Fixed;

package body Asis.Gela.Debug is

   type Condition_Kinds is (None, Any, Hash, Parent);

   type Action_Kinds is (Debug_Image, Hash, Continue);

   type Condition_Data (Condition : Condition_Kinds) is record
      case Condition is
         when Hash | Parent =>
            Hash_Value : Asis.ASIS_Integer;
         when others =>
            null;
      end case;
   end record;

   type Rule (Condition : Condition_Kinds := None) is record
      Filter : Condition_Data (Condition);
      Action : Action_Kinds;
   end record;

   Rules : array (Execution_Point) of Rule;

   ----------
   -- Dump --
   ----------

   function Dump (List : Asis.Element_List) return Boolean is
   begin
      Ada.Wide_Text_IO.Put_Line ("Debug.Dump_List:");

      for J in List'Range loop
         Ada.Wide_Text_IO.Put_Line
           (Asis.List_Index'Wide_Image (J) & " => "
            & Asis.Elements.Debug_Image (List (J)));
      end loop;

      Ada.Wide_Text_IO.Put_Line ("Debug.Dump_List: done");

      return True;
   end Dump;

   ----------
   -- Dump --
   ----------

   function Dump (Text : Wide_String) return Boolean is
   begin
      Ada.Wide_Text_IO.Put_Line ("Debug.Dump:" & Text);

      return True;
   end Dump;

   -------------
   -- Execute --
   -------------

   function Execute
     (Element : Asis.Element;
      Action  : Action_Kinds;
      Point   : Execution_Point) return Boolean is
   begin
      case Action is
         when Debug_Image =>
            Ada.Wide_Text_IO.Put_Line
              ("Debug:" & Execution_Point'Wide_Image (Point)
               & ":" & Asis.Elements.Debug_Image (Element));
         when Hash =>
            Ada.Wide_Text_IO.Put_Line
              ("Debug:" & Execution_Point'Wide_Image (Point)
               & ":" & Asis.Elements.Debug_Image (Element)
               & " Hash ="
               & Asis.ASIS_Integer'Wide_Image (Asis.Elements.Hash (Element)));
         when Continue =>
            Ada.Wide_Text_IO.Put_Line
              ("Debug.Continue:" & Execution_Point'Wide_Image (Point)
               & ":" & Asis.Elements.Debug_Image (Element));
            return False;
      end case;

      return True;
   end Execute;

   ---------
   -- Fit --
   ---------

   function Fit (Element : Asis.Element;
                 Check   : Condition_Data)
                return Boolean
   is
   begin
      case Check.Condition is
         when None =>
            return False;
         when Any =>
            return True;
         when Hash =>
            return Check.Hash_Value = Asis.Elements.Hash (Element);
         when Parent =>
            return Assigned (Element) and then
              (Check.Hash_Value = Asis.Elements.Hash (Element) or else
               Fit (Enclosing_Element (Element.all), Check));
      end case;
   end Fit;

   ---------
   -- Set --
   ---------

   function Set (Assertion : Wide_String) return Boolean is
      use Ada.Strings.Wide_Fixed;

      Dots   : constant Ada.Strings.Wide_Maps.Wide_Character_Set :=
        Ada.Strings.Wide_Maps.To_Set (Sequence => ":");
      First  : Positive;
      Last   : Natural;
      Point  : Execution_Point;
   begin
      Find_Token (Assertion, Dots, Ada.Strings.Outside, First, Last);

      Point := Execution_Point'Wide_Value (Assertion (First .. Last));

      Find_Token (Assertion (Last + 1 .. Assertion'Last),
                  Dots, Ada.Strings.Outside, First, Last);

      declare
         Condition : constant Condition_Kinds :=
           Condition_Kinds'Wide_Value (Assertion (First .. Last));
         Value     : Rule (Condition);
      begin
         case Condition is
            when Hash | Parent =>
               Find_Token (Assertion (Last + 1 .. Assertion'Last),
                           Dots, Ada.Strings.Outside, First, Last);
               Value.Filter.Hash_Value :=
                 Asis.ASIS_Integer'Wide_Value (Assertion (First .. Last));
            when others =>
               null;
         end case;

         Find_Token (Assertion (Last + 1 .. Assertion'Last),
                     Dots, Ada.Strings.Outside, First, Last);

         Value.Action := Action_Kinds'Wide_Value (Assertion (First .. Last));

         Rules (Point) := Value;
      end;

      return True;
   end Set;

   ---------
   -- Set --
   ---------

   function Run
     (Element : Asis.Element;
      Point   : Execution_Point) return Boolean is
   begin
      if Fit (Element, Rules (Point).Filter) then
         return Execute (Element, Rules (Point).Action, Point);
      end if;

      return True;
   end Run;

end Asis.Gela.Debug;

------------------------------------------------------------------------------
--  Copyright (c) 2007, Maxim Reznik
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
