--------------------------------------------------------
--                E n c o d i n g s                   --
--                                                    --
-- Tools for convertion strings between Unicode and   --
-- national/vendor character sets.                    --
--                - - - - - - - - -                   --
-- Read copyright and license at the end of this file --
--------------------------------------------------------

package Encodings is

   type Encoding is
     (Unknown,
      ISO_8859_1,      ISO_8859_2,
      ISO_8859_3,      ISO_8859_4,
      ISO_8859_5,      ISO_8859_6,
      ISO_8859_7,      ISO_8859_8,
      ISO_8859_9,      ISO_8859_10,
      ISO_8859_11,     ISO_8859_13,
      ISO_8859_14,     ISO_8859_15,
      ISO_8859_16,
      CP_037,      CP_424,      CP_437,      CP_500,
      CP_875,      CP_737,      CP_775,      CP_850,
      CP_852,      CP_855,      CP_856,      CP_857,
      CP_860,      CP_861,      CP_862,      CP_863,
      CP_864,      CP_865,      CP_866,      CP_869,
      CP_874,      CP_1006,     CP_1026,     CP_1250,
      CP_1251,     CP_1252,     CP_1253,     CP_1254,
      CP_1255,     CP_1256,     CP_1257,     CP_1258,
      KOI8_R,      AtariST,     UTF_8);

   subtype Raw_String is String;

   function Encode
     (Text : Wide_String;
      Map  : Encoding) return Raw_String;

   function Decode
     (Text : Raw_String;
      Map  : Encoding) return Wide_String;

   procedure Encode
     (Text        : in     Wide_String;
      Text_Last   :    out Natural;
      Result      :    out Raw_String;
      Result_Last :    out Natural;
      Map         : in     Encoding);

   procedure Decode
     (Text        : in     Raw_String;
      Text_Last   :    out Natural;
      Result      :    out Wide_String;
      Result_Last :    out Natural;
      Map         : in     Encoding);

   function To_Encoding (Name : String) return Encoding;

   Invalid_Encoding : exception;

private

   type Encoder is access procedure
     (Text        : in     Wide_String;
      Text_Last   :    out Natural;
      Result      :    out Raw_String;
      Result_Last :    out Natural;
      Map         : in     Encoding);

   type Decoder is access procedure
     (Text        : in     Raw_String;
      Text_Last   :    out Natural;
      Result      :    out Wide_String;
      Result_Last :    out Natural;
      Map         : in     Encoding);

   Encoder_List : array (Encoding) of Encoder;
   Decoder_List : array (Encoding) of Decoder;

   Undefined : constant Wide_Character := Wide_Character'Last;

end Encodings;

------------------------------------------------------------------------------
--  Copyright (c) 2005, Maxim Reznik
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
