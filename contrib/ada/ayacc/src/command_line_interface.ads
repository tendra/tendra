-- Copyright (c) 1990 Regents of the University of California.
-- All rights reserved.
--
--    The primary authors of ayacc were David Taback and Deepak Tolani.
--    Enhancements were made by Ronald J. Schmalz.
--
--    Send requests for ayacc information to ayacc-info@ics.uci.edu
--    Send bug reports for ayacc to ayacc-bugs@ics.uci.edu
--
-- Redistribution and use in source and binary forms are permitted
-- provided that the above copyright notice and this paragraph are
-- duplicated in all such forms and that any documentation,
-- advertising materials, and other materials related to such
-- distribution and use acknowledge that the software was developed
-- by the University of California, Irvine.  The name of the
-- University may not be used to endorse or promote products derived
-- from this software without specific prior written permission.
-- THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
-- IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
-- WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.

-- Module       : command_line_interface_.ada
-- Component of : common_library
-- Version      : 1.2
-- Date         : 11/21/86  16:03:08
-- SCCS File    : disk21~/rschm/hasee/sccs/common_library/sccs/sxcommand_line_interface_.ada

with String_Lists;  use String_Lists;
with String_pkg;    use String_pkg;

--------------------------------------------------------------------

Package command_line_interface is
--| Provides primitives for getting at the command line arguments.

--| Overview
--| This package provides a universal and portable interface to 
--| the arguments typed on a command line when a program is invoked.
--| Each command line argument is either a Word (sequence of non-blank
--| characters) or a quoted string, with embedded quotes doubled.
--| 
--| Both named and positional arguments may be given on the command
--| line.  However, once a named parameter is used, all the subseqent
--| parameters on the command line must be named parameters.  For example, 
--| the commands
--|-
--|     compile  abc pqr xyz library => plib
--|     compile  abc,pqr,unit=>xyz,library=>plib
--|+
--| have one named argument and three positional arguments.  This
--| package separates the named parameters from the positional
--| parameters, ignores spaces around the "bound to" (=>) symbol, and
--| allows parameters to be separated by either spaces or commas,
--| so these command lines are indistinguishable.
--| 
--| At program elaboration time, the command line string is automatically
--| obtained from the host operating system and parsed into
--| individual arguments.  The following operations may then be used:
--|-
--| Named_arg_count()		Returns number of named arguments entered
--| Positional_arg_count()	Returns number of positional arguments
--| Positional_arg_value(N)	Returns the Nth positional argument
--| Named_arg_value(Name, Dflt)	Returns value of a named argument
--| Arguments()			Returns the entire command line 
--|+

----------------------------------------------------------------

max_args: constant := 255;
--| Maximum number of command line arguments (arbitrary).

subtype Argument_count is integer range 0..max_args;
--| For number of arguments
subtype Argument_index is Argument_count range 1..Argument_count'last;
--| Used to number the command line arguments.

no_arg: exception;	
  --| Raised when request made for nonexistent argument

missing_positional_arg: exception;
  --| Raised when command line is missing positional argument (A,,B)

invalid_named_association: exception;
  --| Raised when command line is missing named argument value (output=> ,A,B)

unreferenced_named_arg: exception;
  --| Raised when not all named parameters have been retrieved

invalid_parameter_order: exception;
  --| Raised when a positional parameter occurs after a named parameter
  --  in the command line

--Invalid_Aggregate : exception;
  --| Raised when an aggregate does not begin and end with parentheses
  --  in Parse_Aggregate.

Unbalanced_Parentheses : exception;
  --| Raised when the number of left paren's does not match the number
  --| of right paren's.

Invalid_Parameter : exception;
  --| Raised when the conversion of a string to a parameter type is not
  --| possible.

----------------------------------------------------------------

procedure Initialize (Tool_Name : in String);
  --| Initializes command_line_interface
  --| N/A: modifies, errors, raises

---------------------------------------------------------------------

function Named_arg_count	--| Return number of named arguments
  return Argument_count;
--| N/A: modifies, errors, raises


function Positional_arg_count	--| Return number of positional arguments
  return Argument_count;
--| N/A: modifies, errors, raises


----------------------------------------------------------------

function Positional_arg_value(	--| Return an argument value
  N: Argument_index	        --| Position of desired argument
  ) return string;              --| Raises: no_arg

--| Effects: Return the Nth argument.  If there is no argument at
--| position N, no_arg is raised.

--| N/A: modifies, errors


function Positional_arg_value(	    --| Return an argument value
  N: Argument_index	            --| Position of desired argument
  ) return String_type;             --| Raises: no_arg

--| Effects: Return the Nth argument.  If there is no argument at
--| position N, no_arg is raised.

--| N/A: modifies, errors

--------------------------------------------------------------------

function Named_arg_value(--| Return a named argument value
  Name: string;
  Default: string
  ) return string;

--| Effects: Return the value associated with Name on the command
--| line.  If there was none, return Default.

--| N/A: modifies, errors

function Named_arg_value(--| Return a named argument value
  Name: string;
  Default: string
  ) return String_Type;

--| Effects: Return the value associated with Name on the command
--| line.  If there was none, return Default.

--| N/A: modifies, errors


function Named_arg_value(--| Return a named argument value
  Name: string;
  Default: String_type
  ) return String_type;

--| Effects: Return the value associated with Name on the command
--| line.  If there was none, return Default.

--| N/A: modifies, errors

----------------------------------------------------------------

function Arguments	--| Return the entire argument string
  return string;
--| Effects: Return the entire command line, except for the name
--| of the command itself.

--| N/A: modifies, errors, raises

----------------------------------------------------------------

  function Parse_Aggregate (Aggregate_Text : in String_Type)
                                                return String_Lists.List;

  function Parse_Aggregate (Aggregate_Text : in String)
                                                return String_Lists.List;
  --| Effects: Returns components of Aggregate_Text as a String_List.
  --| Raises : Invalid_Aggregate

----------------------------------------------------------------

  generic
    type Parameter_Type is (<>);
    Type_Name : in String;
  function Convert (Parameter_Text : in String) return Parameter_Type;
  --| Raises: Invalid_Parameter

----------------------------------------------------------------

procedure Finalize ;    --| Raises: unrecognized parameters

--| Effects: If not all named parameters have been retrieved
--| unrecognized parameters is raised.
--| N/A: modifies, errors

end command_line_interface;

----------------------------------------------------------------
