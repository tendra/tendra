-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  8 package Asis.Ada_Environments
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------

package Asis.Ada_Environments is

-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--  Asis.Ada_Environments encapsulates a set of queries that map physical Ada
--  compilation and program execution environments to logical ASIS
--  environments.
-------------------------------------------------------------------------------
--  8.1 function Default_Name
-------------------------------------------------------------------------------

   function Default_Name return Wide_String;

-------------------------------------------------------------------------------
--  Returns the default context name.  If there is no default context name, a
--  null string is returned.
--
-------------------------------------------------------------------------------
--  8.2 function Default_Parameters
-------------------------------------------------------------------------------

   function Default_Parameters return Wide_String;

-------------------------------------------------------------------------------
--  Returns the default context parameters.  If there are no default context
--  parameters, a null string is returned.
--
-------------------------------------------------------------------------------
--  8.3 procedure Associate
-------------------------------------------------------------------------------

   procedure Associate
                 (The_Context : in out Asis.Context;
                  Name        : in     Wide_String;
                  Parameters  : in     Wide_String := Default_Parameters);

-------------------------------------------------------------------------------
--  The_Context - Specifies the Context to associate
--  Name        - Specifies the name for the Context association
--  Parameters  - Specifies parameters to use when opening the Context
--
--  Used to give name and parameter associations to a Context.  The
--  Has_Associations query is used to test whether or not a Context has
--  been given name and parameter associations.  The Name and Parameters
--  queries are used to examine name and parameter associations.
--
--  A Context has at most one set of name/parameter values associated with
--  it at any time.  Name and parameter associations cannot be modified while a
--  Context is open  Previous name and parameters associations for this Context
--  are replaced by this call.
--
--  ASIS implementations are encouraged, but not required, to validate the
--  Parameters string immediately.  It is recognized that some options cannot
--  be completely validated until the Open is performed.  An invalid Parameters
--  value is reported by raising ASIS_Failed with a Status of Parameter_Error.
--
--  Raises ASIS_Inappropriate_Context if The_Context is open.
--

-------------------------------------------------------------------------------
--  8.4 procedure Open
-------------------------------------------------------------------------------

   procedure Open (The_Context : in out Asis.Context);

-------------------------------------------------------------------------------
--  The_Context - Specifies the Context to open
--
--  Opens the ASIS Context using the Context's associated name and parameter
--  values.
--
--  Raises ASIS_Inappropriate_Context if The_Context is already open or if it
--  is uninitialized (does not have associated name and parameter values).
--
--  Raises ASIS_Failed if The_Context could not be opened for any reason.  The
--  most likely Status values are Name_Error, Use_Error, Data_Error, and
--  Parameter_Error.  Other possibilities include Storage_Error and
--  Capacity_Error.
--
-------------------------------------------------------------------------------
--  8.5 procedure Close
-------------------------------------------------------------------------------

   procedure Close (The_Context : in out Asis.Context);

-------------------------------------------------------------------------------
--  The_Context - Specifies the Context to close
--
--  Closes the ASIS Context.  Any previous Context name and parameter
--  associations are retained.  This allows the same Context to be re-opened
--  later with the same associations.
--
--  All Compilation_Unit and Element values obtained from The_Context become
--  invalid when it is closed.  Subsequent calls to ASIS services using such
--  invalid Compilation_Unit or Element values are erroneous.  ASIS
--  implementations will attempt to detect such usage and raise ASIS_Failed in
--  response.  Applications should be aware that the ability to detect the use
--  of such "dangling references" is implementation specific and not all
--  implementations are able to raise ASIS_Failed at the appropriate
--  points.  Thus, applications that attempt to utilize invalid values may
--  exhibit unpredictable behavior.
--
--  Raises ASIS_Inappropriate_Context if The_Context is not open.
--
-------------------------------------------------------------------------------
--  8.6 procedure Dissociate
-------------------------------------------------------------------------------

   procedure Dissociate (The_Context : in out Asis.Context);

-------------------------------------------------------------------------------
--  The_Context - Specifies the Context whose name and parameter associations
--                are to be cleared
--
--  Severs all previous associations for The_Context.  A Context that does not
--  have associations (is uninitialized) is returned unchanged.  The
--  variable The_Context is returned to its uninitialized state.
--
--  Contexts that have been given Names and Parameters should be Dissociated
--  when they are no longer necessary.  Some amount of program storage can be
--  tied up by the stored Name and Parameter strings.  This space is only
--  freed when a Context is Dissociated or when ASIS is Finalized.
--
--  This operation has no physical affect on any implementor's Ada environment.
--
--  Raises ASIS_Inappropriate_Context if The_Context is open.
--

-------------------------------------------------------------------------------
--  8.7 function Is_Equal
-------------------------------------------------------------------------------

   function Is_Equal (Left  : in Asis.Context;
                      Right : in Asis.Context) return Boolean;

-------------------------------------------------------------------------------
--  Left    - Specifies the first Context
--  Right   - Specifies the second Context
--
--  Returns True if Left and Right designate the same set of associated
--  compilation units.  The Context variables may be open or closed.
--
--  Unless both Contexts are open, this operation is implemented as a pair of
--  simple string comparisons between the Name and Parameter associations for
--  the two Contexts.  If both Contexts are open, this operation acts as a
--  set comparison and returns True if both sets contain the same units (all
--  unit versions are included in the comparison).
--
--  |AN Application Note:
--  |AN
--  |AN With some implementations, Is_Equal may be True before the Contexts
--  |AN are opened, but may be False after the Contexts are open.
--  |AN One possible cause for this is a sequence of events such as:
--  |AN
--  |AN a) ASIS program A opens the Left Context for READ,
--  |AN
--  |AN b) non-ASIS program B opens the Context for UPDATE, and creates a new
--  |AN    version of the implementor Context,
--  |AN
--  |AN c) ASIS program A opens the Right Context for READ, and gets the new
--  |AN    version.
--
-------------------------------------------------------------------------------
--  8.8 function Is_Identical
-------------------------------------------------------------------------------

   function Is_Identical (Left  : in Asis.Context;
                          Right : in Asis.Context) return Boolean;

-------------------------------------------------------------------------------
--  Left    - Specifies the first Context
--  Right   - Specifies the second Context
--
--  Returns True if Left and Right both designate the value associated with
--  one specific ASIS Context variable.
--
--  Returns False otherwise or if either Context is not open.
--
--  |AN Application Note:
--  |AN
--  |AN No two physically separate open Context variables are ever
--  |AN Is_Identical.  The value associated with an open ASIS Context variable
--  |AN is also directly associated with every Compilation_Unit or Element
--  |AN derived from that Context.  It is possible to obtain these Context
--  |AN values by way of the Enclosing_Context and the
--  |AN Enclosing_Compilation_Unit queries.  These Context values can be
--  |AN tested for identity with each other or with
--  |AN specific Context variables.  An open ASIS Context variable and an
--  |AN Enclosing_Context value are only Is_Identical if the Compilation_Unit
--  |AN in question was derived specifically from that open ASIS Context
--  |AN variable.
--

-------------------------------------------------------------------------------
--  8.9 function Exists
-------------------------------------------------------------------------------

   function Exists (The_Context : in Asis.Context) return Boolean;

-------------------------------------------------------------------------------
--  The_Context - Specifies a Context with associated name and parameter values
--
--  Returns True if The_Context is open or if The_Context designates an Ada
--  environment that can be determined to exist.
--
--  Returns False for any uninitialized The_Context variable.
--
--  |IP Implementation Permissions:
--  |IP
--  |IP No guarantee is made that The_Context is readable or that an Open
--  |IP operation on The_Context would succeed.  The associated
--  |IP parameter value for The_Context may not be fully validated by this
--  |IP simple existence check.  It may contain information that can only be
--  |IP verified by an Open.
--
-------------------------------------------------------------------------------
--  8.10 function Is_Open
-------------------------------------------------------------------------------

   function Is_Open (The_Context : in Asis.Context) return Boolean;

-------------------------------------------------------------------------------
--  The_Context - Specifies the Context to check
--
--  Returns True if The_Context is currently open.
--
-------------------------------------------------------------------------------
--  8.11 function Has_Associations
-------------------------------------------------------------------------------

   function Has_Associations (The_Context : in Asis.Context) return Boolean;

-------------------------------------------------------------------------------
--  The_Context - Specifies the Context to check
--
--  Returns True if name and parameter values have been associated with
--  The_Context.
--
--  Returns False if The_Context is uninitialized.
--
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
--  8.12 function Name
-------------------------------------------------------------------------------

   function Name (The_Context : in Asis.Context) return Wide_String;

-------------------------------------------------------------------------------
--  The_Context - Specifies the Context to check
--
--  Returns the Name value associated with The_Context.
--
--  Returns a null string if The_Context is uninitialized.
--

-------------------------------------------------------------------------------
--  8.13 function Parameter
-------------------------------------------------------------------------------

   function Parameters (The_Context : in Asis.Context) return Wide_String;

-------------------------------------------------------------------------------
--  The_Context - Specifies the Context to check
--
--  Returns the Parameters value associated with The_Context.
--
--  Returns a null string if The_Context is uninitialized.
--
-------------------------------------------------------------------------------
--  8.14 function Debug_Image
-------------------------------------------------------------------------------

   function Debug_Image (The_Context : in Asis.Context) return Wide_String;

-------------------------------------------------------------------------------
--  The_Context - Specifies the Context to represent
--
--  Returns a string value containing implementation-defined debugging
--  information associated with The_Context.
--
--  The return value uses Asis.Text.Delimiter_Image to separate lines in
--  multi-line results.  The return value is not terminated with
--  Asis.Text.Delimiter_Image.
--
--  Returns a null string if The_Context is uninitialized.
--
--  These values are intended for two purposes.  They are suitable for
--  inclusion in problem reports sent to the ASIS implementor.  They can be
--  presumed to contain information useful when debugging the implementation
--  itself. They are also suitable for use by the ASIS application when
--  printing simple application debugging messages during application
--  development. They are intended to be, to some worthwhile degree,
--  intelligible to the user.
--

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
