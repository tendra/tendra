with Interfaces;
with Ada.Text_IO;
with TenDRA.Output;

package body TenDRA.Streams is

   type    Byte_Count is range 0 .. 1024;
   subtype Byte_Index is Byte_Count range 1 .. Byte_Count'Last;
   type    Bytes is array (Byte_Index) of Byte;

   type Buffer is record
      Length : Byte_Count := 0;
      Next   : Buffer_Access;
      Buffer : Bytes;
   end record;

   procedure Print
     (Stack : in out Stacks.Stack;
      Top   : in     Check_Item;
      Item  : in     Types.Construct := Types.Dummy);

   -------------
   -- Aligned --
   -------------

   function Aligned (Object : Stream) return Boolean is
   begin
      return Object.Free = 8;
   end Aligned;

   -----------
   -- Check --
   -----------

   procedure Check
     (Object : in out Stream;
      Item   : in     Types.Construct)
   is
      use TenDRA.Types;
      Sort : constant Sort_Kind := Result (Item);
   begin
      Check (Object, Sort, Item);
   end Check;

   -----------
   -- Check --
   -----------

   procedure Check
     (Object : in out Stream;
      Sort   : in     Types.Sort_Kind;
      Item   : in     Types.Construct := Types.Dummy)
   is
      use TenDRA.Types;

      Top  : Check_Item;
   begin
      Stacks.Pop (Object.Stack, Top);

      if Top.Sort /= Sort then
         Print (Object.Stack, Top, Item);
         raise Syntax_Error;
      end if;

      if Top.Align then
         Output.BYTE_ALIGN (Object);
      end if;

      case Top.Mode is
         when Optional =>
            Write (Object, 1, 1);

         when List_Element | SList_Element =>
            if Top.Count > 1 then
               Top.Count := Top.Count - 1;
               Stacks.Push (Object.Stack, Top);
            elsif Top.Count = 0 then
               Print (Object.Stack, Top, Item);
               raise Syntax_Error;
            end if;
         when Singular =>
            null;
      end case;
   end Check;

   ------------
   -- Create --
   ------------

   procedure Create
     (Object :    out File_Stream;
      Name   : in     String)
   is
      use Byte_IO;
   begin
      Create (Object.File, Name => Name);
   end Create;

   ------------
   -- Expect --
   ------------

   procedure Expect
     (Object : in out Stream;
      Parent : in     Types.Construct;
      List   : in     Types.Argument_List)
   is
      Item : Check_Item;
   begin
      Item.Parent := Parent;
      Item.Count  := 0;

      for J in reverse List'Range loop
         Item.Sort  := List (J).Sort;
         Item.Mode  := List (J).Mode;
         Item.Align := List (J).Align;
         Stacks.Push (Object.Stack, Item);
      end loop;
   end Expect;

   ----------------
   -- Flush_Byte --
   ----------------

   procedure Flush_Byte (Object : in out Stream'Class) is
   begin
      if Object.Free /= 8 then
         Save (Object, Object.Current);
         Object.Free    := 8;
         Object.Current := 0;
      end if;
   end Flush_Byte;

   -------------
   -- Next_Id --
   -------------

   Stream_Id : Natural := 0;

   function Next_Id return Positive is
   begin
      Stream_Id := Stream_Id + 1;
      return Stream_Id;
   end Next_Id;

   ---------
   -- Pos --
   ---------

   function Pos (Object : Stream) return String is
      Id     : constant String := Positive'Image (Object.Id);
      Spaces : constant String := "                                  ";
      Count  : constant String := Positive'Image (Object.Count);
      Bit    : constant String := Natural'Image (8 - Natural (Object.Free));
      Pad    : constant String :=
        Spaces (1 .. 2 * Stacks.Length (Object.Stack));
   begin
      return Id (2 .. Id'Last) & Pad & Count (2 .. Count'Last)
        & ':' & Bit (2 .. Bit'Last);
   end Pos;

   -------------
   -- Prepend --
   -------------

   procedure Prepend
     (Object : in out Memory_Stream;
      Value  : in out Memory_Stream)
   is
      Ptr : Buffer_Access := Object.Next;
   begin
      if not Aligned (Value) then
         Ada.Text_IO.Put_Line ("Prepend not aligned");
         raise Syntax_Error;
      end if;

      if Ptr = null then
         Object.Next := Value.Next;
      else
         while Ptr.Next /= null loop
            Ptr := Ptr.Next;
         end loop;

         Ptr.Next := Value.Next;
      end if;

      Object.Length   := Object.Length + Value.Length;
      Value.Length    := 0;
      Value.Next      := null;
   end Prepend;

   -----------
   -- Print --
   -----------

   procedure Print
     (Stack : in out Stacks.Stack;
      Top   : in     Check_Item;
      Item  : in     Types.Construct := Types.Dummy)
   is
      use Types;
      use Ada.Text_IO;

      procedure Print (Item : Check_Item) is
      begin
         Put_Line ("Sort = " & Sort_Kind'Image (Item.Sort)
                   & " Mode = " & Argument_Mode'Image (Item.Mode)
                   & " Count =" & Small'Image (Item.Count)
                   & " Parent = " & Construct'Image (Item.Parent));
      end Print;
      Next  : Check_Item := Top;
   begin
      Put_Line ("Unexpected " & Construct'Image (Item)
                & " -> " & Sort_Kind'Image (Result (Item))
                & " :");

      loop
         Print (Next);
         exit when not Stacks.Is_Empty (Stack);
         Stacks.Pop (Stack, Next);
      end loop;
   end Print;

   -----------
   -- Reset --
   -----------

   procedure Reset (Object :    out Memory_Stream) is
   begin
      Object.Current := 0;
      Object.Free    := 8;
      Object.Length  := 0;
      if Object.Next /= null then
         Object.Next.Length := 0;
         Object.Next.Next   := null;
      end if;
   end Reset;

   ----------
   -- Save --
   ----------

   procedure Save
     (Object : in out Memory_Stream;
      Value  : in     Byte)
   is
      procedure New_Buffer is
         Result : constant Buffer_Access := new Buffer;
      begin
         Result.Next := Object.Next;
         Object.Next := Result;
      end New_Buffer;
   begin
--      Ada.Text_IO.Put_Line (Byte'Image(Value));
      if Object.Length = 0 or else Object.Next.Length = Bytes'Last then
         New_Buffer;
      end if;

      Object.Count       := Object.Count + 1;
      Object.Length      := Object.Length + 1;
      Object.Next.Length := Object.Next.Length + 1;
      Object.Next.Buffer (Object.Next.Length) := Value;
   end Save;

   ----------
   -- Save --
   ----------

   procedure Save
     (Object : in out File_Stream;
      Value  : in     Byte)
   is
   begin
      Object.Count := Object.Count + 1;
      Byte_IO.Write (Object.File, Value);
   end Save;

   ------------------
   -- TDFBITSTREAM --
   ------------------

   procedure TDFBITSTREAM
     (Object : in out Stream'Class;
      Value  : in     Memory_Stream)
   is
      use Interfaces;

      procedure Put_Buffer (Current : Buffer_Access) is
      begin
         if Current /= null then
            Put_Buffer (Current.Next);

            for I in 1 .. Current.Length loop
               Write (Object, Word (Current.Buffer (I)), 8);
            end loop;
         end if;
      end Put_Buffer;

      procedure Put_Rest is
         Rest   : constant Bit_Count := 8 - Value.Free;
         Result : Word;
      begin
         if Rest = 0 then
            return;
         end if;

         Result := Word (Shift_Right (Unsigned_8 (Value.Current),
                                      Natural (Value.Free)));

         Write (Object, Result, Rest);
      end Put_Rest;

      Size : constant Small :=
        Small (Value.Length) * 8 + (8 - Small (Value.Free));
   begin
      Check (Object, Types.BITSTREAM_SORT);
      Output.TDFINT (Object, Size, Check => False);
      Put_Buffer (Value.Next);
      Put_Rest;
   end TDFBITSTREAM;

   -------------------
   -- TDFBYTESTREAM --
   -------------------

   procedure TDFBYTESTREAM
     (Object : in out Stream'Class;
      Value  : in out Memory_Stream)
   is
      procedure Put_Buffer (Current : Buffer_Access) is
      begin
         if Current /= null then
            Put_Buffer (Current.Next);

            for I in 1 .. Current.Length loop
               Save (Object, Current.Buffer (I));
            end loop;
         end if;
      end Put_Buffer;

   begin
      Check (Object, Types.BYTESTREAM_SORT);
      Flush_Byte (Value);
      Output.TDFINT (Object, Small (Value.Length), Check => False);
      Flush_Byte (Object);
      Put_Buffer (Value.Next);
   end TDFBYTESTREAM;

   -----------
   -- Write --
   -----------

   procedure Write
     (Object : in out Stream'Class;
      Value  : in     Word;
      Length : in     Bit_Count)
   is
      use Interfaces;

      function Left (Value : Word; Count : Bit_Index) return Byte is
      begin
         return Byte (Shift_Left (Unsigned_32 (Value), Natural (Count)));
      end Left;

      function Right (Value : Word; Count : Bit_Count) return Byte is
      begin
         return Byte (Shift_Right (Unsigned_32 (Value), Natural (Count)));
      end Right;

      function Mask (Value : Word; Count : Bit_Count) return Word is
      begin
         return Value and (2 ** Integer (Count) - 1);
      end Mask;

      Rest : Bit_Count;
   begin
      if Length < Object.Free then
         Object.Free    := Object.Free - Length;
         Object.Current := Object.Current or Left (Value, Object.Free);
      elsif Length = Object.Free then
         Object.Current := Object.Current or Byte (Value);
         Save (Object, Object.Current);
         Object.Free    := 8;
         Object.Current := 0;
      else
         Rest := Length - Object.Free;
         Object.Current := Object.Current or Right (Value, Rest);
         Save (Object, Object.Current);
         Object.Free    := 8;
         Object.Current := 0;

         Write (Object, Mask (Value, Rest), Rest);
      end if;
   end Write;

   ----------------------
   -- Write_List_Count --
   ----------------------

   procedure Write_List_Count
     (Object : in out Stream'Class;
      Value  : in     Small := Unknown_Length)
   is
      use TenDRA.Types;
      Top : Check_Item;
   begin
      Stacks.Pop (Object.Stack, Top);

      if Top.Mode = List_Element then
         Write (Object, 0, 1);
      end if;

      if Top.Count = 0
        and then (Top.Mode = List_Element or Top.Mode = SList_Element)
      then
         if Value /= Unknown_Length then
            Output.TDFINT (Object, Value, Check => False);
         end if;

         Top.Count := Value;

         if Value /= 0 then
            Stacks.Push (Object.Stack, Top);
         end if;
      else
         Print (Object.Stack, Top);
         raise Syntax_Error;
      end if;
   end Write_List_Count;

   ---------------------
   -- Write_No_Option --
   ---------------------

   procedure Write_No_Option (Object : in out Stream'Class) is
      use TenDRA.Types;

      Top : Check_Item;
   begin
      Stacks.Pop (Object.Stack, Top);

      if Top.Mode = Optional then
         Write (Object, 0, 1);
      else
         Print (Object.Stack, Top);
         raise Syntax_Error;
      end if;
   end Write_No_Option;

end TenDRA.Streams;



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
