------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Our extension to ASIS standard

with Asis.Elements;
with Asis.Gela.Static;
with Asis.Gela.Elements;
with Asis.Gela.Visibility;

package body Asis.Extensions is

   --------------------------
   -- Is_Static_Expression --
   --------------------------

   function Is_Static_Expression (Element : Asis.Expression) return Boolean is
   begin
      if Asis.Elements.Element_Kind (Element) = An_Expression then
         declare
            use Asis.Gela.Elements;

            Node : Expression_Node'Class renames
              Expression_Node'Class (Element.all);
         begin
            case Is_Static_Expression (Node) is
               when Asis.Gela.Unknown =>
                  if Gela.Static.Is_Static_Expression (Element) then
                     Set_Is_Static_Expression (Node, Asis.Gela.True);
                     return True;
                  else
                     Set_Is_Static_Expression (Node, Asis.Gela.False);
                     return False;
                  end if;
               when Asis.Gela.True =>
                  return True;
               when Asis.Gela.False =>
                  return False;
            end case;
         end;
      else
         return False;
      end if;
   end Is_Static_Expression;

   -----------------
   -- Unique_Name --
   -----------------

   function Unique_Name (Name : Asis.Defining_Name) return Asis.Program_Text is
   begin
      if Asis.Elements.Element_Kind (Name) = A_Defining_Name then
         return Asis.Gela.Visibility.Unique_Name (Name);
      else
         return "";
      end if;
   end Unique_Name;

end Asis.Extensions;


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
