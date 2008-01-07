-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  6 package Asis.Implementation
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

with Asis.Errors;
package Asis.Implementation is
   pragma Preelaborate;

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  Asis.Implementation provides queries to initialize, finalize, and query the
--  error status of the ASIS Implementation.
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
--  6.1 function ASIS_Version
-------------------------------------------------------------------------------

   function ASIS_Version return Wide_String;

-------------------------------------------------------------------------------
--  6.2 function ASIS_Implementor
-------------------------------------------------------------------------------

   function ASIS_Implementor return Wide_String;

-------------------------------------------------------------------------------
--  6.3 function ASIS_Implementor_Version
-------------------------------------------------------------------------------

   function ASIS_Implementor_Version return Wide_String;

-------------------------------------------------------------------------------
--  6.4 function ASIS_Implementor_Information
-------------------------------------------------------------------------------

   function ASIS_Implementor_Information return Wide_String;

-------------------------------------------------------------------------------
--  Returns values which identify:
--
--  ASIS_Version                 the version of the ASIS interface, e.g., "2.1"
--  ASIS_Implementor             the name of the implementor, e.g., "Ada Inc."
--  ASIS_Implementor_Version     the implementation's version, e.g., "5.2a"
--  ASIS_Implementor_Information implementation information, e.g., "Copyright."
--
-------------------------------------------------------------------------------
--  6.5 function Is_Initialized
-------------------------------------------------------------------------------

   function Is_Initialized return Boolean;

-------------------------------------------------------------------------------
--  Returns True if ASIS is currently initialized.
--
-------------------------------------------------------------------------------
--  6.6 procedure Initialize
-------------------------------------------------------------------------------

   procedure Initialize (Parameters : in Wide_String := "");

-------------------------------------------------------------------------------
--  Parameters  - Specifies implementation specific parameters.
--
--  Performs any necessary initialization activities.  This shall be invoked
--  at least once before any other ASIS services are used.  Parameter values
--  are implementation dependent.  The call is ignored if ASIS is already
--  initialized. All ASIS queries and services are ready for use once this
--  call completes.
--
--  Raises ASIS_Failed if ASIS failed to initialize or if the Parameters
--  argument is invalid.  Status is Environment_Error or Parameter_Error.
--
--  |AN Application Note:
--  |AN
--  |AN The ASIS implementation may be Initialized and Finalized any number of
--  |AN times during the operation of an ASIS program.   However, all existing
--  |AN Context, Compilation_Unit and Element values become invalid when
--  |AN ASIS Is_Finalized.  Subsequent calls to ASIS queries or services using
--  |AN such invalid Compilation_Unit or Element values will cause
--  |AN ASIS_Inappropriate_Context to be raised.
--
-------------------------------------------------------------------------------
--  6.7 function Is_Finalized
-------------------------------------------------------------------------------

   function Is_Finalized return Boolean;

-------------------------------------------------------------------------------
--  Returns True if ASIS is currently finalized or if ASIS has never been
--  initialized.
--
-------------------------------------------------------------------------------
--  6.8 procedure Finalize
-------------------------------------------------------------------------------

   procedure Finalize (Parameters : in Wide_String := "");

-------------------------------------------------------------------------------
--  Parameters  - Specifies any implementation required parameter values.
--
--  Performs any necessary ASIS termination activities.  This should be invoked
--  once following the last use of other ASIS queries.  Parameter values are
--  implementation dependent.  The call is ignored if ASIS is already
--  finalized. Subsequent calls to ASIS Environment, Compilation_Unit, and
--  Element queries, are erroneous while the environment Is_Finalized.
--
--  Raises ASIS_Failed if the ASIS implementation failed to finalize.  Status
--  is likely to be Internal_Error and will not be Not_An_Error.
--
-------------------------------------------------------------------------------
--  Whenever an error condition is detected, and any ASIS exception is raised,
--  an Asis.Errors.Error_Kinds value and a Diagnosis string is stored.  These
--  values can be retrieved by the Status and Diagnosis functions.  The
--  Diagnosis function will retrieve the diagnostic message describing
--  the error.
--
--  Error information always refers to the most recently recorded error.
--
--  Note that Diagnosis values are implementation dependent and may vary
--  greatly among ASIS implementations.
--
-------------------------------------------------------------------------------
--  6.9 function Status
-------------------------------------------------------------------------------

   function Status return Asis.Errors.Error_Kinds;

-------------------------------------------------------------------------------
--  Returns the Error_Kinds value for the most recent error.
--
-------------------------------------------------------------------------------
--  6.10 function Diagnosis
-------------------------------------------------------------------------------

   function Diagnosis return Wide_String;

-------------------------------------------------------------------------------
--  Returns a string value describing the most recent error.
--
--  Will typically return a null string if Status = Not_An_Error.
--
-------------------------------------------------------------------------------
--  6.11 procedure Set_Status
-------------------------------------------------------------------------------

   procedure Set_Status
        (Status    : in Asis.Errors.Error_Kinds := Asis.Errors.Not_An_Error;
         Diagnosis : in Wide_String        := "");

-------------------------------------------------------------------------------
--  Status      - Specifies the new status to be recorded
--  Diagnosis   - Specifies the new diagnosis to be recorded
--
--  Sets (clears, if the defaults are used) the Status and Diagnosis
--  information.  Future calls to Status will return this Status (Not_An_Error)
--  and this Diagnosis (a null string).
--
--  Raises ASIS_Failed, with a Status of Internal_Error and a Diagnosis of
--  a null string, if the Status parameter is Not_An_Error and the Diagnosis
--  parameter is not a null string.
--
-------------------------------------------------------------------------------

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
