------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Helper procedures to create dynamic structures of declarative region

private
package Asis.Gela.Visibility.Create is

   procedure Region
     (Element : in     Asis.Element;
      Point   : in out Visibility.Point);

   procedure Region_Items
     (Element    : in     Asis.Element;
      Point      : in out Visibility.Point;
      Tipe       : in     Asis.Declaration;
      Overridden :    out Boolean);

   procedure Completion_Region
     (Element     : in     Asis.Element;
      Point       : in out Visibility.Point;
      Is_Instance : in     Boolean;
      RR_Clause   : in     Boolean);

   procedure Use_Clause
     (Element : in     Asis.Element;
      Point   : in out Visibility.Point);

   procedure New_Part
     (Region        : in  Region_Access;
      Kind          : in  Part_Kinds;
      Parent_Item   : in  Region_Item_Access;
      Element       : in  Asis.Element;
      Check_Private : in  Boolean;
      Result        : out Part_Access);

end Asis.Gela.Visibility.Create;


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
