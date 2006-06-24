------------------------------------------------------------------------------
--                           G E L A   X A S I S                            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $
--  Purpose:
--  Collect basic type declaration
--  Should be initialized manualy

with Asis;

package XASIS.Types is

   function Universal_Integer return Asis.Declaration;
   function Universal_Real    return Asis.Declaration;
   function Universal_Fixed   return Asis.Declaration;
   function Root_Integer      return Asis.Declaration;
   function Root_Real         return Asis.Declaration;
   function System_Address    return Asis.Declaration;
   function System_Bit_Order  return Asis.Declaration;
   function Integer           return Asis.Declaration;
   function String            return Asis.Declaration;
   function Wide_String       return Asis.Declaration;
   function Boolean           return Asis.Declaration;
   function Exception_Id      return Asis.Declaration;
   function Task_Id           return Asis.Declaration;
   function Root_Storage_Pool return Asis.Declaration;
   function Tag               return Asis.Declaration;
   function Natural           return Asis.Declaration;
   function Duration          return Asis.Declaration;
   function Wide_Character    return Asis.Declaration;
   function Character         return Asis.Declaration;
   function Root_Stream_Type  return Asis.Declaration;

   procedure Initialize
     (Universal_Integer : Asis.Declaration;
      Universal_Real    : Asis.Declaration;
      Universal_Fixed   : Asis.Declaration;
      Root_Integer      : Asis.Declaration;
      Root_Real         : Asis.Declaration;
      String            : Asis.Declaration;
      Wide_String       : Asis.Declaration;
      Float             : Asis.Declaration;
      Boolean           : Asis.Declaration;
      Duration          : Asis.Declaration;
      Integer           : Asis.Declaration;
      Natural           : Asis.Declaration;
      Wide_Character    : Asis.Declaration;
      Character         : Asis.Declaration);

   procedure Initialize
     (System_Address   : Asis.Declaration;
      System_Bit_Order : Asis.Declaration);

   procedure Initialize (Root_Storage_Pool : Asis.Declaration);
   procedure Initialize_Task_Id (Task_Id : Asis.Declaration);
   procedure Initialize_Exception_Id (Exception_Id : Asis.Declaration);
   procedure Initialize_Tag (Tag : Asis.Declaration);
   procedure Initialize_Root_Stream (Root : Asis.Declaration);

end XASIS.Types;


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
