-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  5 package Asis.Exceptions
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

package Asis.Exceptions is
   pragma Preelaborate;

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  ASIS exceptions are:

   ASIS_Inappropriate_Context : exception;

-------------------------------------------------------------------------------
--  Raised when ASIS is passed a Context value that is not appropriate for the
--  operation.  This exception will typically indicate that a user error
--  has occurred within the application.
-------------------------------------------------------------------------------

   ASIS_Inappropriate_Container : exception;

-------------------------------------------------------------------------------
--  Raised when ASIS is passed a Container value that is not appropriate for
--  the operation.  This exception will typically indicate that a user error
--  has occurred within the application.
-------------------------------------------------------------------------------

   ASIS_Inappropriate_Compilation_Unit : exception;

-------------------------------------------------------------------------------
--  Raised when ASIS is passed a Compilation_Unit value that is not
--  appropriate.  This exception will typically indicate that a user
--  error has occurred within the application.
-------------------------------------------------------------------------------

   ASIS_Inappropriate_Element : exception;

-------------------------------------------------------------------------------
--  Raised when ASIS is given an Element value that is not appropriate.  This
--  exception will typically indicate that a user error has occurred within
--  the application.
-------------------------------------------------------------------------------

   ASIS_Inappropriate_Line : exception;

-------------------------------------------------------------------------------
--  Raised when ASIS is given a Line value that is not appropriate.
-------------------------------------------------------------------------------

   ASIS_Inappropriate_Line_Number : exception;

-------------------------------------------------------------------------------
--  Raised when ASIS is given a Line_Number value that is not appropriate.
--  This exception will typically indicate that a user error has occurred
--  within the application.
-------------------------------------------------------------------------------

   ASIS_Failed : exception;

-------------------------------------------------------------------------------
--  This is a catch-all exception that may be raised for different reasons
--  in different ASIS implementations.  All ASIS routines may raise ASIS_Failed
--  whenever they cannot normally complete their operation.  This exception
--  will typically indicate a failure of the underlying ASIS implementation.
-------------------------------------------------------------------------------

end Asis.Exceptions;


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
