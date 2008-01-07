------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Procedural wrapper over Object-Oriented ASIS implementation

with Asis.Errors;
with Asis.Exceptions;
with Asis.Implementation;

with Asis.Gela.Contexts;
with Ada.Exceptions;
with Ada.Characters.Handling;
with Ada.Unchecked_Deallocation;

package body Asis.Ada_Environments is

   type Context_Ptr is access all Context_Node'Class;

   ---------------
   -- Associate --
   ---------------

   procedure Associate
     (The_Context : in out Asis.Context;
      Name        : in     Wide_String;
      Parameters  : in     Wide_String := Default_Parameters)
  is
   begin
      if not Implementation.Is_Initialized
         or Implementation.Is_Finalized
      then
         Implementation.Set_Status (
            Status    => Asis.Errors.Initialization_Error,
            Diagnosis => "ASIS is not initialized");

         raise Exceptions.ASIS_Failed;
      end if;

      if Is_Open (The_Context) then
         Implementation.Set_Status (
            Status    => Asis.Errors.Value_Error,
            Diagnosis => "Context has alredy been opened");

         raise Exceptions.ASIS_Inappropriate_Context;
      end if;

      begin
         if not Assigned (The_Context) then
            The_Context := new Asis.Gela.Contexts.Concrete_Context_Node;
         end if;

         Asis.Associate
           (The_Context => The_Context,
            Name        => Name,
            Parameters  => Parameters);
      end;
   end Associate;

   -----------
   -- Close --
   -----------

   procedure Close (The_Context : in out Asis.Context) is
   begin
      if not Is_Open (The_Context) then
         Implementation.Set_Status (
            Status    => Asis.Errors.Value_Error,
            Diagnosis => "Context is not opened");

         raise Exceptions.ASIS_Inappropriate_Context;
      end if;
      Close (The_Context.all);
   end Close;

   -----------------
   -- Debug_Image --
   -----------------

   function Debug_Image (The_Context : in Asis.Context) return Wide_String is
   begin
      if not Assigned (The_Context) then
         return "[null]";
      else
         return Debug_Image (The_Context.all);
      end if;
   end Debug_Image;

   ------------------
   -- Default_Name --
   ------------------

   function Default_Name return Wide_String is
   begin
      return "";
   end Default_Name;

   ------------------------
   -- Default_Parameters --
   ------------------------

   function Default_Parameters return Wide_String is
   begin
      return "";
   end Default_Parameters;

   ----------------
   -- Dissociate --
   ----------------

   procedure Dissociate (The_Context : in out Asis.Context) is
      procedure Free is new Ada.Unchecked_Deallocation
        (Asis.Context_Node'Class, Asis.Context);
   begin
      if Assigned (The_Context) then
         Dissociate (The_Context.all);
         Free (The_Context);
         The_Context := null;
      end if;
   end Dissociate;

   ------------
   -- Exists --
   ------------

   function Exists (The_Context : in Asis.Context) return Boolean is
   begin
      return Has_Associations (The_Context);
   end Exists;

   ----------------------
   -- Has_Associations --
   ----------------------

   function Has_Associations (The_Context : in Asis.Context)
      return Boolean is
   begin
      if Assigned (The_Context) then
         return Has_Associations (The_Context.all);
      else
         return False;
      end if;
   end Has_Associations;

   --------------
   -- Is_Equal --
   --------------

   function Is_Equal
     (Left  : in Asis.Context;
      Right : in Asis.Context) return Boolean is
   begin
      if not Assigned (Left) and not Assigned (Right) then
         return True;
      elsif Assigned (Left) and then
        Assigned (Right) and then
        Is_Equal (Left.all, Right.all)
      then
         return True;
      else
         return False;
      end if;
   end Is_Equal;

   ------------------
   -- Is_Identical --
   ------------------

   function Is_Identical
     (Left  : in Asis.Context;
      Right : in Asis.Context) return Boolean
   is
   begin
      return Is_Open (Left) and Is_Open (Right)
        and Context_Ptr (Left) = Context_Ptr (Right);
   end Is_Identical;

   -------------
   -- Is_Open --
   -------------

   function Is_Open (The_Context : in Asis.Context) return Boolean is
   begin
      return Assigned (The_Context) and then Is_Open (The_Context.all);
   end Is_Open;

   ----------
   -- Name --
   ----------

   function Name (The_Context : in Asis.Context) return Wide_String is
   begin
      if Assigned (The_Context) then
         return Context_Name (The_Context.all);
      else
         return "";
      end if;
   end Name;

   ----------
   -- Open --
   ----------

   procedure Open (The_Context : in out Asis.Context) is
      use Ada.Exceptions;
      use Asis.Exceptions;
      use Ada.Characters.Handling;
   begin
      if Is_Open (The_Context) then
         Implementation.Set_Status (
            Status    => Asis.Errors.Value_Error,
            Diagnosis => "Context has alredy been opened");

         raise ASIS_Inappropriate_Context;
      end if;

      if not Has_Associations (The_Context) then
         Implementation.Set_Status (
            Status    => Asis.Errors.Value_Error,
            Diagnosis => "Context has no association");

         raise ASIS_Inappropriate_Context;
      end if;

      Open (The_Context.all);

   exception
      when E : ASIS_Inappropriate_Context
        | ASIS_Failed =>
         Reraise_Occurrence (E);
      when E : others =>
         Implementation.Set_Status
           (Status    => Asis.Errors.Internal_Error,
            Diagnosis => "Asis.Ada_Environments.Open: "
            & To_Wide_String (Exception_Information (E)));
         raise ASIS_Failed;
   end Open;

   ----------------
   -- Parameters --
   ----------------

   function Parameters (The_Context : in Asis.Context) return Wide_String is
   begin
      if Assigned (The_Context) then
         return Parameters (The_Context.all);
      else
         return "";
      end if;
   end Parameters;

end Asis.Ada_Environments;



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
