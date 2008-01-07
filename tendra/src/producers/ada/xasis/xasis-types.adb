package body XASIS.Types is

   The_Universal_Integer       : Asis.Declaration;
   The_Universal_Real          : Asis.Declaration;
   The_Universal_Fixed         : Asis.Declaration;
   The_Universal_Access        : Asis.Declaration;
   The_Root_Integer            : Asis.Declaration;
   The_Root_Real               : Asis.Declaration;
   The_System_Address          : Asis.Declaration;
   The_System_Bit_Order        : Asis.Declaration;
   The_String                  : Asis.Declaration;
   The_Wide_String             : Asis.Declaration;
   The_Wide_Wide_String        : Asis.Declaration;
   The_Float                   : Asis.Declaration;
   The_Boolean                 : Asis.Declaration;
   The_Duration                : Asis.Declaration;
   The_Task_Id                 : Asis.Declaration;
   The_Exception_Id            : Asis.Declaration;
   The_Root_Storage_Pool       : Asis.Declaration;
   The_Tag                     : Asis.Declaration;
   The_Integer                 : Asis.Declaration;
   The_Natural                 : Asis.Declaration;
   The_Character               : Asis.Declaration;
   The_Wide_Character          : Asis.Declaration;
   The_Wide_Wide_Character     : Asis.Declaration;
   The_Root_Stream_Type        : Asis.Declaration;

   -------------
   -- Boolean --
   -------------

   function Boolean return Asis.Declaration is
   begin
      return The_Boolean;
   end Boolean;

   ---------------
   -- Character --
   ---------------

   function Character return Asis.Declaration is
   begin
      return The_Character;
   end Character;

   --------------
   -- Duration --
   --------------

   function Duration return Asis.Declaration is
   begin
      return The_Duration;
   end Duration;

   ------------------
   -- Exception_Id --
   ------------------

   function Exception_Id return Asis.Declaration is
   begin
      return The_Exception_Id;
   end Exception_Id;

   ----------------
   -- Initialize --
   ----------------

   procedure Initialize
     (Universal_Integer   : Asis.Declaration;
      Universal_Real      : Asis.Declaration;
      Universal_Fixed     : Asis.Declaration;
      Universal_Access    : Asis.Declaration;
      Root_Integer        : Asis.Declaration;
      Root_Real           : Asis.Declaration;
      String              : Asis.Declaration;
      Wide_String         : Asis.Declaration;
      Wide_Wide_String    : Asis.Declaration;
      Float               : Asis.Declaration;
      Boolean             : Asis.Declaration;
      Duration            : Asis.Declaration;
      Integer             : Asis.Declaration;
      Natural             : Asis.Declaration;
      Wide_Wide_Character : Asis.Declaration;
      Wide_Character      : Asis.Declaration;
      Character           : Asis.Declaration) is
   begin
      The_Universal_Integer   := Universal_Integer;
      The_Universal_Real      := Universal_Real;
      The_Universal_Fixed     := Universal_Fixed;
      The_Universal_Access    := Universal_Access;
      The_Root_Integer        := Root_Integer;
      The_Root_Real           := Root_Real;
      The_String              := String;
      The_Wide_String         := Wide_String;
      The_Wide_Wide_String    := Wide_Wide_String;
      The_Float               := Float;
      The_Boolean             := Boolean;
      The_Duration            := Duration;
      The_Integer             := Integer;
      The_Natural             := Natural;
      The_Character           := Character;
      The_Wide_Character      := Wide_Character;
      The_Wide_Wide_Character := Wide_Character;
   end Initialize;

   procedure Initialize
     (System_Address   : Asis.Declaration;
      System_Bit_Order : Asis.Declaration) is
   begin
      The_System_Address   := System_Address;
      The_System_Bit_Order := System_Bit_Order;
   end Initialize;

   procedure Initialize_Task_Id (Task_Id : Asis.Declaration) is
   begin
      The_Task_Id   := Task_Id;
   end Initialize_Task_Id;

   procedure Initialize_Exception_Id (Exception_Id : Asis.Declaration) is
   begin
      The_Exception_Id := Exception_Id;
   end Initialize_Exception_Id;

   procedure Initialize (Root_Storage_Pool : Asis.Declaration) is
   begin
      The_Root_Storage_Pool := Root_Storage_Pool;
   end Initialize;

   procedure Initialize_Tag (Tag : Asis.Declaration) is
   begin
      The_Tag := Tag;
   end Initialize_Tag;

   procedure Initialize_Root_Stream (Root : Asis.Declaration) is
   begin
      The_Root_Stream_Type := Root;
   end Initialize_Root_Stream;

   -------------
   -- Integer --
   -------------

   function Integer return Asis.Declaration is
   begin
      return The_Integer;
   end Integer;

   -------------
   -- Natural --
   -------------

   function Natural return Asis.Declaration is
   begin
      return The_Natural;
   end Natural;

   -----------------------
   -- Root_Storage_Pool --
   -----------------------

   function Root_Storage_Pool return Asis.Declaration is
   begin
      return The_Root_Storage_Pool;
   end Root_Storage_Pool;

   ------------------
   -- Root_Integer --
   ------------------

   function Root_Integer return Asis.Declaration is
   begin
      return The_Root_Integer;
   end Root_Integer;

   ------------------
   -- Root_Integer --
   ------------------

   function Root_Real return Asis.Declaration is
   begin
      return The_Root_Real;
   end Root_Real;

   ----------------------
   -- Root_Stream_Type --
   ----------------------

   function Root_Stream_Type  return Asis.Declaration is
   begin
      return The_Root_Stream_Type;
   end Root_Stream_Type;

   ------------
   -- String --
   ------------

   function String return Asis.Declaration is
   begin
      return The_String;
   end String;

   --------------------
   -- System_Address --
   --------------------

   function System_Address return Asis.Declaration is
   begin
      return The_System_Address;
   end System_Address;

   ----------------------
   -- System_Bit_Order --
   ----------------------

   function System_Bit_Order return Asis.Declaration is
   begin
      return The_System_Bit_Order;
   end System_Bit_Order;

   ---------
   -- Tag --
   ---------

   function Tag return Asis.Declaration is
   begin
      return The_Tag;
   end Tag;

   -------------
   -- Task_Id --
   -------------

   function Task_Id return Asis.Declaration is
   begin
      return The_Task_Id;
   end Task_Id;

   ----------------------
   -- Universal_Access --
   ----------------------

   function Universal_Access return Asis.Declaration is
   begin
      return The_Universal_Access;
   end Universal_Access;

   ---------------------
   -- Universal_Fixed --
   ---------------------

   function Universal_Fixed return Asis.Declaration is
   begin
      return The_Universal_Fixed;
   end Universal_Fixed;

   -----------------------
   -- Universal_Integer --
   -----------------------

   function Universal_Integer return Asis.Declaration is
   begin
      return The_Universal_Integer;
   end Universal_Integer;

   -----------------------
   -- Universal_Real --
   -----------------------

   function Universal_Real return Asis.Declaration is
   begin
      return The_Universal_Real;
   end Universal_Real;

   --------------------
   -- Wide_Character --
   --------------------

   function Wide_Character return Asis.Declaration is
   begin
      return The_Wide_Character;
   end Wide_Character;

   -------------------------
   -- Wide_Wide_Character --
   -------------------------

   function Wide_Wide_Character return Asis.Declaration is
   begin
      return The_Wide_Wide_Character;
   end Wide_Wide_Character;

   -----------------
   -- Wide_String --
   -----------------

   function Wide_String return Asis.Declaration is
   begin
      return The_Wide_String;
   end Wide_String;

   ----------------------
   -- Wide_Wide_String --
   ----------------------

   function Wide_Wide_String return Asis.Declaration is
   begin
      return The_Wide_Wide_String;
   end Wide_Wide_String;

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
