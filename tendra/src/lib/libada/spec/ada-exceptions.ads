------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Exceptions is

   type Exception_Id is private;

   Null_Id : constant Exception_Id;

   function Exception_Name (Id : Exception_Id) return String;

   type Exception_Occurrence is limited private;
   type Exception_Occurrence_Access is access all Exception_Occurrence;

   Null_Occurrence : constant Exception_Occurrence;

   procedure Raise_Exception
     (E       : in Exception_Id;
      Message : in String := "");

   function Exception_Message   (X :    Exception_Occurrence) return String;
   procedure Reraise_Occurrence (X : in Exception_Occurrence);

   function Exception_Identity
     (X : Exception_Occurrence)
     return Exception_Id;

   function Exception_Name
     (X : Exception_Occurrence)
     return String;
   --  Same as Exception_Name(Exception_Identity(X)).

   function Exception_Information
     (X : Exception_Occurrence) return String;

   procedure Save_Occurrence
     (Target : out Exception_Occurrence;
      Source : in Exception_Occurrence);

   function Save_Occurrence
     (Source : Exception_Occurrence)
     return Exception_Occurrence_Access;

private

   pragma Import (Ada, Exception_Id);
   pragma Import (Ada, Exception_Occurrence);
   pragma Import (Ada, Null_Id);
   pragma Import (Ada, Null_Occurrence);

end Ada.Exceptions;


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
