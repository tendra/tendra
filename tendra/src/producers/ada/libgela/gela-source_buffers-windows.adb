package body Gela.Source_Buffers.Windows is

   pragma Linker_Options ("-lkernel32");

   type BOOL is new Boolean;
   for BOOL'Size use Interfaces.C.unsigned_long'Size;

   type SECURITY_ATTRIBUTES
      is record
         nLength              : Interfaces.C.unsigned_long;
         lpSecurityDescriptor : System.Address;
         bInheritHandle       : BOOL;
      end record;
   pragma Convention (C, SECURITY_ATTRIBUTES);

   type SECURITY_ATTRIBUTES_Access is access all SECURITY_ATTRIBUTES;
   pragma Convention (C, SECURITY_ATTRIBUTES_Access);

   PAGE_READONLY : constant := 2;

   function CreateFileMapping
     (hFile                   : HANDLE;
      lpFileMappingAttributes : SECURITY_ATTRIBUTES_Access;
      flProtect               : Interfaces.C.unsigned_long;
      dwMaximumSizeHigh       : Interfaces.C.unsigned_long;
      dwMaximumSizeLow        : Interfaces.C.unsigned_long;
      lpName                  : Interfaces.C.char_array)
      return HANDLE;
   pragma Import (Stdcall, CreateFileMapping, "CreateFileMappingA");

   function MapViewOfFile
     (hFileMappingObject   : HANDLE;
      dwDesiredAccess      : Interfaces.C.unsigned_long;
      dwFileOffsetHigh     : Interfaces.C.unsigned_long;
      dwFileOffsetLow      : Interfaces.C.unsigned_long;
      dwNumberOfBytesToMap : Interfaces.C.unsigned_long)
      return System.Address;
   pragma Import (Stdcall, MapViewOfFile, "MapViewOfFile");

   FILE_MAP_READ : constant := 4;

   function UnmapViewOfFile
     (lpBaseAddress : System.Address)
      return BOOL;
   pragma Import (Stdcall, UnmapViewOfFile, "UnmapViewOfFile");

   function CloseHandle
     (hObject : HANDLE)
      return BOOL;
   pragma Import (Stdcall, CloseHandle, "CloseHandle");

   type OFSTRUCT is record
      cBytes     : Interfaces.C.unsigned_short;
      fFixedDisk : Interfaces.C.unsigned_short;
      nErrCode   : Interfaces.C.unsigned;
      Reserved1  : Interfaces.C.unsigned;
      Reserved2  : Interfaces.C.unsigned;
      szPathName : Interfaces.C.char_array (1 .. 128);
   end record;
   pragma Convention (C, OFSTRUCT);

   type POFSTRUCT is access all OFSTRUCT;
   pragma Convention (C, POFSTRUCT);

   function OpenFile
     (lpFileName   : Interfaces.C.char_array;
      lpReOpenBuff : POFSTRUCT;
      uStyle       : Interfaces.C.unsigned_long)
     return HANDLE;
   pragma Import (Stdcall, OpenFile, "OpenFile");

   OF_READ     : constant := 0;
   HFILE_ERROR : constant := -1;

   function GetFileSize
     (File           : HANDLE;
      lpFileSizeHigh : System.Address)
      return Interfaces.C.unsigned_long;
   pragma Import (Stdcall, GetFileSize, "GetFileSize");

   ----------
   -- Open --
   ----------

   procedure Open
     (This : in out Source_Buffer;
      Name : in     String)
   is
      use Interfaces.C;
      use System;

      Size      : unsigned_long := 0;
      vOfStruct : aliased OFSTRUCT;
   begin
      This.Internal_File :=
        OpenFile (To_C (Name), vOfStruct'Unchecked_Access, OF_READ);

      if This.Internal_File = 0 then
         raise Use_Error;
      end if;

      Size := GetFileSize (This.Internal_File, System.Null_Address);

      if Size > unsigned_long (Offset'Last) then
         Close (This);
         raise Use_Error;
      else
         This.Internal_Size := Offset (Size);
      end if;

      if This.Internal_Size = 0 then
         return;
      end if;

      This.Internal_WMF := CreateFileMapping
        (This.Internal_File, null, PAGE_READONLY,
         0, Size, To_C ("Source_Data"));

      if This.Internal_WMF = 0 then
         Close (This);
         raise Use_Error;
      end if;

      This.Internal_Data := MapViewOfFile
        (This.Internal_WMF, FILE_MAP_READ, 0, 0, 0);

      if This.Internal_Data = System.Null_Address then
         Close (This);
         raise Use_Error;
      end if;
   end Open;

   -----------
   -- Close --
   -----------

   procedure Close (This : in out Source_Buffer) is
      use System;
      use type HANDLE;
      Raise_Exception : Boolean := False;
   begin
      if This.Internal_Data /= System.Null_Address then
         if not UnmapViewOfFile (This.Internal_Data) then
            Raise_Exception := True;
         else
            This.Internal_Data := System.Null_Address;
         end if;
      end if;

      if This.Internal_WMF /= 0 then
         if not CloseHandle (This.Internal_WMF) then
            Raise_Exception := True;
         else
            This.Internal_WMF := 0;
         end if;
      end if;

      if This.Internal_File /= 0 then
         if not CloseHandle (This.Internal_File) then
            Raise_Exception := True;
         else
            This.Internal_File := 0;
         end if;
      end if;

      if Raise_Exception then
         raise Use_Error;
      end if;
   end Close;

end Gela.Source_Buffers.Windows;

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
