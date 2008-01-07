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

package body Asis.Statements is

   -------------------
   -- Aborted_Tasks --
   -------------------

   function Aborted_Tasks
     (Statement : in Asis.Statement)
      return Asis.Expression_List
   is
   begin
      Check_Nil_Element (Statement, "Aborted_Tasks");
      return Aborted_Tasks (Statement.all);
   end Aborted_Tasks;

   ------------------------------------
   -- Accept_Body_Exception_Handlers --
   ------------------------------------

   function Accept_Body_Exception_Handlers
     (Statement       : in Asis.Statement;
      Include_Pragmas : in Boolean := False)
      return Asis.Statement_List
   is
   begin
      Check_Nil_Element (Statement, "Accept_Body_Exception_Handlers");
      return Accept_Body_Exception_Handlers (Statement.all, Include_Pragmas);
   end Accept_Body_Exception_Handlers;

   ----------------------------
   -- Accept_Body_Statements --
   ----------------------------

   function Accept_Body_Statements
     (Statement       : in Asis.Statement;
      Include_Pragmas : in Boolean := False)
      return Asis.Statement_List
   is
   begin
      Check_Nil_Element (Statement, "Accept_Body_Statements");
      return Accept_Body_Statements (Statement.all, Include_Pragmas);
   end Accept_Body_Statements;

   ------------------------------
   -- Accept_Entry_Direct_Name --
   ------------------------------

   function Accept_Entry_Direct_Name
     (Statement : in Asis.Statement)
      return Asis.Name
   is
   begin
      Check_Nil_Element (Statement, "Accept_Entry_Direct_Name");
      return Accept_Entry_Direct_Name (Statement.all);
   end Accept_Entry_Direct_Name;

   ------------------------
   -- Accept_Entry_Index --
   ------------------------

   function Accept_Entry_Index
     (Statement : in Asis.Statement)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Statement, "Accept_Entry_Index");
      return Accept_Entry_Index (Statement.all);
   end Accept_Entry_Index;

   -----------------------
   -- Accept_Parameters --
   -----------------------

   function Accept_Parameters
     (Statement : in Asis.Statement)
      return Asis.Parameter_Specification_List
   is
   begin
      Check_Nil_Element (Statement, "Accept_Parameters");
      return Accept_Parameters (Statement.all);
   end Accept_Parameters;

   ---------------------------
   -- Assignment_Expression --
   ---------------------------

   function Assignment_Expression
     (Statement : in Asis.Statement)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Statement, "Assignment_Expression");
      return Assignment_Expression (Statement.all);
   end Assignment_Expression;

   ------------------------------
   -- Assignment_Variable_Name --
   ------------------------------

   function Assignment_Variable_Name
     (Statement : in Asis.Statement)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Statement, "Assignment_Variable_Name");
      return Assignment_Variable_Name (Statement.all);
   end Assignment_Variable_Name;

   -----------------------------
   -- Block_Declarative_Items --
   -----------------------------

   function Block_Declarative_Items
     (Statement       : in Asis.Statement;
      Include_Pragmas : in Boolean := False)
      return Asis.Declarative_Item_List
   is
   begin
      Check_Nil_Element (Statement, "Block_Declarative_Items");
      return Block_Declarative_Items (Statement.all, Include_Pragmas);
   end Block_Declarative_Items;

   ------------------------------
   -- Block_Exception_Handlers --
   ------------------------------

   function Block_Exception_Handlers
     (Statement : in Asis.Statement;
      Include_Pragmas : in Boolean := False)
      return Asis.Exception_Handler_List
   is
   begin
      Check_Nil_Element (Statement, "Block_Exception_Handlers");
      return Block_Exception_Handlers (Statement.all, Include_Pragmas);
   end Block_Exception_Handlers;

   ----------------------
   -- Block_Statements --
   ----------------------

   function Block_Statements
     (Statement       : in Asis.Statement;
      Include_Pragmas : in Boolean := False)
      return Asis.Statement_List
   is
   begin
      Check_Nil_Element (Statement, "Block_Statements");
      return Block_Statements (Statement.all, Include_Pragmas);
   end Block_Statements;

   -------------------------------
   -- Call_Statement_Parameters --
   -------------------------------

   function Call_Statement_Parameters
     (Statement  : in Asis.Statement;
      Normalized : in Boolean := False)
      return Asis.Association_List
   is
   begin
      Check_Nil_Element (Statement, "Call_Statement_Parameters");
      if Normalized then
         return Normalized_Call_Statement_Parameters (Statement.all);
      else
         return Call_Statement_Parameters (Statement.all);
      end if;
   end Call_Statement_Parameters;

   -----------------
   -- Called_Name --
   -----------------

   function Called_Name
     (Statement : in Asis.Statement)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Statement, "Called_Name");
      return Called_Name (Statement.all);
   end Called_Name;

   ---------------------
   -- Case_Expression --
   ---------------------

   function Case_Expression
     (Statement : in Asis.Statement)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Statement, "Case_Expression");
      return Case_Expression (Statement.all);
   end Case_Expression;

   ----------------------------------------
   -- Case_Statement_Alternative_Choices --
   ----------------------------------------

   function Case_Statement_Alternative_Choices
     (Path : in Asis.Path)
      return Asis.Element_List
   is
   begin
      Check_Nil_Element (Path, "Case_Statement_Alternative_Choices");
      return Case_Statement_Alternative_Choices (Path.all);
   end Case_Statement_Alternative_Choices;

   ------------------------------------
   -- Choice_Parameter_Specification --
   ------------------------------------

   function Choice_Parameter_Specification
     (Handler : in Asis.Exception_Handler)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Handler, "Choice_Parameter_Specification");
      return Choice_Parameter_Specification (Handler.all);
   end Choice_Parameter_Specification;

   --------------------------
   -- Condition_Expression --
   --------------------------

   function Condition_Expression
     (Path : in Asis.Path)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Path, "Condition_Expression");
      return Condition_Expression (Path.all);
   end Condition_Expression;

   ---------------------------------
   -- Corresponding_Called_Entity --
   ---------------------------------

   function Corresponding_Called_Entity
     (Statement : in Asis.Statement)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Statement, "Corresponding_Called_Entity");
      return Corresponding_Called_Entity (Statement.all);
   end Corresponding_Called_Entity;

   -----------------------------------------
   -- Corresponding_Destination_Statement --
   -----------------------------------------

   function Corresponding_Destination_Statement
     (Statement : in Asis.Statement)
      return Asis.Statement
   is
   begin
      Check_Nil_Element (Statement, "Corresponding_Destination_Statement");
      return Corresponding_Destination_Statement (Statement.all);
   end Corresponding_Destination_Statement;

   -------------------------
   -- Corresponding_Entry --
   -------------------------

   function Corresponding_Entry
     (Statement : in Asis.Statement)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Statement, "Corresponding_Entry");
      return Corresponding_Entry (Statement.all);
   end Corresponding_Entry;

   -------------------------------
   -- Corresponding_Loop_Exited --
   -------------------------------

   function Corresponding_Loop_Exited
     (Statement : in Asis.Statement)
      return Asis.Statement
   is
   begin
      Check_Nil_Element (Statement, "Corresponding_Loop_Exited");
      return Corresponding_Loop_Exited (Statement.all);
   end Corresponding_Loop_Exited;

   ----------------------
   -- Delay_Expression --
   ----------------------

   function Delay_Expression
     (Statement : in Asis.Statement)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Statement, "Delay_Expression");
      return Delay_Expression (Statement.all);
   end Delay_Expression;

   -----------------------
   -- Exception_Choices --
   -----------------------

   function Exception_Choices
     (Handler : in Asis.Exception_Handler)
      return Asis.Element_List
   is
   begin
      Check_Nil_Element (Handler, "Exception_Choices");
      return Exception_Choices (Handler.all);
   end Exception_Choices;

   --------------------
   -- Exit_Condition --
   --------------------

   function Exit_Condition
     (Statement : in Asis.Statement)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Statement, "Exit_Condition");
      return Exit_Condition (Statement.all);
   end Exit_Condition;

   --------------------
   -- Exit_Loop_Name --
   --------------------

   function Exit_Loop_Name
     (Statement : in Asis.Statement)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Statement, "Exit_Loop_Name");
      return Exit_Loop_Name (Statement.all);
   end Exit_Loop_Name;

   ----------------------------------------
   -- Extended_Return_Exception_Handlers --
   ----------------------------------------

   function Extended_Return_Exception_Handlers
     (Statement       : Asis.Statement;
      Include_Pragmas : Boolean := False)
      return Asis.Exception_Handler_List
   is
   begin
      Check_Nil_Element (Statement, "Extended_Return_Exception_Handlers");
      return Extended_Return_Exception_Handlers (Statement.all,
                                                 Include_Pragmas);
   end Extended_Return_Exception_Handlers;

   --------------------------------
   -- Extended_Return_Statements --
   --------------------------------

   function Extended_Return_Statements
     (Statement       : Asis.Statement;
      Include_Pragmas : Boolean := False)
      return Asis.Statement_List
   is
   begin
      Check_Nil_Element (Statement, "Extended_Return_Statements");
      return Extended_Return_Statements (Statement.all, Include_Pragmas);
   end Extended_Return_Statements;

   --------------------------------------
   -- For_Loop_Parameter_Specification --
   --------------------------------------

   function For_Loop_Parameter_Specification
     (Statement : in Asis.Statement)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Statement, "For_Loop_Parameter_Specification");
      return Loop_Parameter_Specification (Statement.all);
   end For_Loop_Parameter_Specification;

   ----------------
   -- Goto_Label --
   ----------------

   function Goto_Label
     (Statement : in Asis.Statement)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Statement, "Goto_Label");
      return Goto_Label (Statement.all);
   end Goto_Label;

   -----------
   -- Guard --
   -----------

   function Guard
     (Path : in Asis.Path)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Path, "Guard");
      return Guard (Path.all);
   end Guard;

   ------------------------
   -- Handler_Statements --
   ------------------------

   function Handler_Statements
     (Handler         : in Asis.Exception_Handler;
      Include_Pragmas : in Boolean := False)
      return Asis.Statement_List
   is
   begin
      Check_Nil_Element (Handler, "Handler_Statements");
      return Handler_Statements (Handler.all, Include_Pragmas);
   end Handler_Statements;

   --------------------------------------
   -- Is_Call_On_Dispatching_Operation --
   --------------------------------------

   function Is_Call_On_Dispatching_Operation
     (Call : in Asis.Element)
      return Boolean
   is
   begin
      Check_Nil_Element (Call, "Is_Call_On_Dispatching_Operation");
      return Is_Call_On_Dispatching_Operation (Call.all);
   end Is_Call_On_Dispatching_Operation;

   ----------------------
   -- Is_Declare_Block --
   ----------------------

   function Is_Declare_Block
     (Statement : in Asis.Statement)
      return Boolean
   is
   begin
      Check_Nil_Element (Statement, "Is_Declare_Block");
      return Is_Declare_Block (Statement.all);
   end Is_Declare_Block;

   -------------------------
   -- Is_Dispatching_Call --
   -------------------------

   function Is_Dispatching_Call (Call : in Asis.Element) return Boolean is
   begin
      Check_Nil_Element (Call, "Is_Dispatching_Call");
      return Is_Dispatching_Call (Call.all);
   end Is_Dispatching_Call;

   ----------------------
   -- Is_Name_Repeated --
   ----------------------

   function Is_Name_Repeated
     (Statement : in Asis.Statement)
      return Boolean
   is
   begin
      Check_Nil_Element (Statement, "Is_Name_Repeated");
      return Is_Name_Repeated (Statement.all);
   end Is_Name_Repeated;

   -----------------
   -- Label_Names --
   -----------------

   function Label_Names
     (Statement : in Asis.Statement)
      return Asis.Defining_Name_List
   is
   begin
      Check_Nil_Element (Statement, "Label_Names");
      return Label_Names (Statement.all);
   end Label_Names;

   ---------------------
   -- Loop_Statements --
   ---------------------

   function Loop_Statements
     (Statement       : in Asis.Statement;
      Include_Pragmas : in Boolean := False)
      return Asis.Statement_List
   is
   begin
      Check_Nil_Element (Statement, "Loop_Statements");
      return Loop_Statements (Statement.all, Include_Pragmas);
   end Loop_Statements;

   --------------------------
   -- Qualified_Expression --
   --------------------------

   function Qualified_Expression
     (Statement : in Asis.Statement)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Statement, "Qualified_Expression");
      return Qualified_Expression (Statement.all);
   end Qualified_Expression;

   ----------------------
   -- Raised_Exception --
   ----------------------

   function Raised_Exception
     (Statement : in Asis.Statement)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Statement, "Raised_Exception");
      return Raised_Exception (Statement.all);
   end Raised_Exception;

   -----------------------------
   -- Raise_Statement_Message --
   -----------------------------

   function Raise_Statement_Message  -- 13.3(2)
     (Statement : Asis.Statement)
     return Asis.Expression is
   begin
      Check_Nil_Element (Statement, "Raise_Statement_Message");
      return Raise_Statement_Message (Statement.all);
   end Raise_Statement_Message;

   ------------------------
   -- Requeue_Entry_Name --
   ------------------------

   function Requeue_Entry_Name
     (Statement : in Asis.Statement)
      return Asis.Name
   is
   begin
      Check_Nil_Element (Statement, "Requeue_Entry_Name");
      return Requeue_Entry_Name (Statement.all);
   end Requeue_Entry_Name;

   -----------------------
   -- Return_Expression --
   -----------------------

   function Return_Expression
     (Statement : in Asis.Statement)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Statement, "Return_Expression");
      return Return_Expression (Statement.all);
   end Return_Expression;

   ---------------------------------
   -- Return_Object_Specification --
   ---------------------------------

   function Return_Object_Specification
     (Statement : Asis.Statement)
      return Asis.Declaration
   is
   begin
      Check_Nil_Element (Statement, "Return_Object_Specification");
      return Return_Object_Specification (Statement.all);
   end Return_Object_Specification;

   ----------------------------
   -- Sequence_Of_Statements --
   ----------------------------

   function Sequence_Of_Statements
     (Path            : in Asis.Path;
      Include_Pragmas : in Boolean := False)
      return Asis.Statement_List
   is
   begin
      Check_Nil_Element (Path, "Sequence_Of_Statements");
      return Sequence_Of_Statements (Path.all, Include_Pragmas);
   end Sequence_Of_Statements;

   --------------------------
   -- Statement_Identifier --
   --------------------------

   function Statement_Identifier
     (Statement : in Asis.Statement)
      return Asis.Defining_Name
   is
   begin
      Check_Nil_Element (Statement, "Statement_Identifier");
      return Statement_Identifier (Statement.all);
   end Statement_Identifier;

   ---------------------
   -- Statement_Paths --
   ---------------------

   function Statement_Paths
     (Statement : in Asis.Statement;
      Include_Pragmas : in Boolean := False)
      return Asis.Path_List
   is
   begin
      Check_Nil_Element (Statement, "Statement_Paths");
      return Statement_Paths (Statement.all, Include_Pragmas);
   end Statement_Paths;

   ---------------------
   -- While_Condition --
   ---------------------

   function While_Condition
     (Statement : in Asis.Statement)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Statement, "While_Condition");
      return While_Condition (Statement.all);
   end While_Condition;

end Asis.Statements;


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
