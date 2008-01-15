with System.Storage_Elements;

package body Gela.Source_Buffers.Unix is
   use Interfaces;

   function open
     (path  : C.char_array;
      flags : C.int)
     return HANDLE;
   pragma Import (C, open, "open");

   function close
     (fd : HANDLE)
     return C.int;
   pragma Import (C, close, "close");

   O_RDONLY    : constant := 0;
   OPEN_FAILED : constant := -1;
   SEEK_END    : constant := 2;

   --type off_t is range -2 ** 63 .. 2 ** 63 - 1;
   type off_t is range -2 ** 31 .. 2 ** 31 - 1;

   function lseek
     (filedes : HANDLE;
      Offset  : off_t;
      whence  : C.int)
     return off_t;
   pragma Import (C, lseek, "lseek");

   function mmap
     (start  : System.Address;
      length : C.size_t;
      prot   : C.int;
      flags  : C.int;
      fd     : HANDLE;
      offset : C.ptrdiff_t)
     return System.Address;
   pragma Import (C, mmap, "mmap");

   PROT_READ   : constant := 1;
   MAP_PRIVATE : constant := 2;

   function munmap
     (start  : System.Address;
      length : C.size_t)
     return C.int;
   pragma Import (C, munmap, "munmap");

   ----------
   -- Open --
   ----------

   procedure Open
     (This : in out Source_Buffer;
      Name : in     String)
   is
      use Interfaces.C;
      use System;

      use type Storage_Elements.Integer_Address;

      MAP_FAILED  : constant System.Address :=
        Storage_Elements.To_Address (-1);

      Size : off_t;
   begin
      This.Internal_File := open (To_C (Name), O_RDONLY);

      if This.Internal_File = OPEN_FAILED then
         raise Use_Error;
      end if;

      Size := lseek (This.Internal_File, 0, SEEK_END);

      if Size = -1 or Size > off_t (Offset'Last) then
         Close (This);
         raise Use_Error;
      else
         This.Internal_Size := Offset (Size);
      end if;

      if This.Internal_Size = 0 then
         return;
      end if;

      This.Internal_Data := mmap
        (System.Null_Address, Interfaces.C.size_t (This.Internal_Size),
         PROT_READ, MAP_PRIVATE, This.Internal_File, 0);

      if This.Internal_Data = MAP_FAILED then
         This.Internal_Data := System.Null_Address;
         Close (This);
         raise Use_Error;
      end if;
   end Open;

   -----------
   -- Close --
   -----------

   procedure Close (This : in out Source_Buffer) is
      use System;
      use Interfaces.C;
      Raise_Exception : Boolean := False;
   begin
      if This.Internal_Data /= System.Null_Address then
         if munmap (This.Internal_Data,
                    Interfaces.C.size_t (This.Internal_Size)) /= 0
         then
            Raise_Exception := True;
         else
            This.Internal_Data := System.Null_Address;
         end if;
      end if;

      if This.Internal_File /= -1 then
         if close (This.Internal_File) /= 0 then
            Raise_Exception := True;
         else
            This.Internal_File := -1;
         end if;
      end if;

      if Raise_Exception then
         raise Use_Error;
      end if;
   end Close;

end Gela.Source_Buffers.Unix;

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
--  Authors:
--    Andry Ogorodnik
--    Maxim Reznik
--    Vadim Godunko
------------------------------------------------------------------------------
