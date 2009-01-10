------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  List of supported encodings

package Gela.Encodings is
   pragma Pure;

   type Encoding is
     (UTF_8,           UTF_16,
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
      KOI8_R,      AtariST);

   subtype Fixed_Width_Encoding is Encoding range ISO_8859_1 .. AtariST;

end Gela.Encodings;

------------------------------------------------------------------------------
--  Copyright (c) 2008, Maxim Reznik
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
--
------------------------------------------------------------------------------
