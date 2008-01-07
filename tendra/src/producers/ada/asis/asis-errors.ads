-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  4 package Asis.Errors
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

package Asis.Errors is
   pragma Preelaborate;

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--
--  ASIS reports all operational errors by raising an exception.  Whenever an
--  ASIS implementation raises one of the exceptions declared in package
--  Asis.Exceptions, it will previously have set the values returned by the
--  Status and Diagnosis queries to indicate the cause of the error.  The
--  possible values for Status are indicated in the definition of Error_Kinds
--  below, with suggestions for the associated contents of the Diagnosis
--  string as a comment.
--
--  The Diagnosis and Status queries are provided in the Asis.Implementation
--  package to supply more information about the reasons for raising any
--  exception.
--
--  ASIS applications are encouraged to follow this same convention whenever
--  they explicitly raise any ASIS exception--always record a Status and
--  Diagnosis prior to raising the exception.
-------------------------------------------------------------------------------
--  4.1 type Error_Kinds
-------------------------------------------------------------------------------
--  This enumeration type describes the various kinds of errors.
--

   type Error_Kinds is (

        Not_An_Error,               --  No error is presently recorded
        Value_Error,                --  Routine argument value invalid
        Initialization_Error,       --  ASIS is uninitialized
        Environment_Error,          --  ASIS could not initialize
        Parameter_Error,            --  Bad Parameter given to Initialize
        Capacity_Error,             --  Implementation overloaded
        Name_Error,                 --  Context/unit not found
        Use_Error,                  --  Context/unit not use/open-able
        Data_Error,                 --  Context/unit bad/invalid/corrupt
        Text_Error,                 --  The program text cannot be located
        Storage_Error,              --  Storage_Error suppressed
        Obsolete_Reference_Error,   --  Argument or result is invalid due to
                                    --  and inconsistent compilation unit
        Unhandled_Exception_Error,  --  Unexpected exception suppressed
        Not_Implemented_Error,      --  Functionality not implemented
        Internal_Error);            --  Implementation internal failure

-------------------------------------------------------------------------------

end Asis.Errors;


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
