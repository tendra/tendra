------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $
--  Purpose:
--  Implement Asis.Implementation

--with XASIS.Log;
with Asis.Exceptions;

package body Asis.Implementation is

   Initialized        : Boolean := False;
   Finalized          : Boolean := True;
   Max_Current        : constant := 2048;
   Current_Parameters : Wide_String (1 .. Max_Current);
   Parameters_Length  : Natural := 0;
   Current_Status     : Asis.Errors.Error_Kinds;
   Current_Diagnosis  : Wide_String (1 .. Max_Current);
   Diagnosis_Length   : Natural := 0;

   function ASIS_Version return Wide_String is
   begin
      return "ASIS 2.0s";
   end ASIS_Version;

   function ASIS_Implementor return Wide_String is
   begin
      return "Gela: An Ada Compiler";
   end ASIS_Implementor;

   function ASIS_Implementor_Version return Wide_String is
   begin
      return "0.0.1";
   end ASIS_Implementor_Version;

   function ASIS_Implementor_Information return Wide_String is
   begin
      return "Copyright (C) 2006, Maxim Reznik";
   end ASIS_Implementor_Information;

   function Is_Initialized return Boolean is
   begin
      return Initialized;
   end Is_Initialized;

   procedure Initialize (Parameters : in Wide_String := "") is
   begin
      if not Initialized then
         Initialized := True;
         Finalized   := False;
         Current_Parameters (1 .. Parameters'Length) := Parameters;
         Parameters_Length := Parameters'Length;
--         XASIS.Log.Init;
      end if;
   end Initialize;

   function Is_Finalized return Boolean is
   begin
      return Finalized;
   end Is_Finalized;

   procedure Finalize (Parameters : in Wide_String := "") is
   begin
      if not Finalized then
         Finalized   := True;
         Initialized := False;
      end if;
   end Finalize;

   function Status return Asis.Errors.Error_Kinds is
   begin
      return Current_Status;
   end Status;

   function Diagnosis return Wide_String is
   begin
      return Current_Diagnosis (1 .. Diagnosis_Length);
   end Diagnosis;

   procedure Set_Status
        (Status    : in Asis.Errors.Error_Kinds := Asis.Errors.Not_An_Error;
         Diagnosis : in Wide_String        := "")
   is
      use type Asis.Errors.Error_Kinds;
   begin
      if Status = Errors.Not_An_Error and Diagnosis /= "" then
         Current_Status   := Errors.Internal_Error;
         Diagnosis_Length := 0;

         raise Exceptions.ASIS_Failed;
      end if;

      Current_Status := Status;
      Current_Diagnosis (1 .. Diagnosis'Length) := Diagnosis;
      Diagnosis_Length := Diagnosis'Length;
   end Set_Status;

end Asis.Implementation;


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
