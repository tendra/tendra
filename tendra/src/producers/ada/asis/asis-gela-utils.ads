------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Helper functions

package Asis.Gela.Utils is

   function Are_Homographs
     (Left  : Asis.Defining_Name;
      Right : Asis.Defining_Name;
      Place : Asis.Element)
     return Boolean;

   function Are_Type_Conformant
     (Left  : Asis.Element;
      Right : Asis.Element;
      Place : Asis.Element;
      Right_Is_Prefixed_View : Boolean := False)
     return Boolean;
   -- Left/Right is Defining_Name or Access_Definition

   function Is_Limited_Type (Tipe : Asis.Definition) return Boolean;

   function In_Visible_Part
     (Declaration : Asis.Declaration) return Boolean;

   function In_Context_Clause
     (Clause : Asis.Clause) return Boolean;

   generic
      Place : in Asis.Element;

      with procedure Walk_Variant
             (Item     : in     Asis.Variant;
              Continue :    out Boolean);
      with procedure Walk_Component
             (Item     : in     Asis.Declaration;
              Continue :    out Boolean);
   procedure Walk_Components
     (Item     : in     Asis.Element;
      Continue :    out Boolean);

end Asis.Gela.Utils;


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
