package Gramar_Items.Code is

   procedure Read_Code_File (Name : String);

   Not_Found : exception;

   function Node_Name
     (Rule_Name : String;
      Seq       : Sequence) return String;

   function True_Node
     (Rule_Name : String;
      Seq       : Sequence) return String;

   function False_Node
     (Rule_Name : String;
      Seq       : Sequence) return String;

   function Pass_Throgh
     (Rule_Name : String;
      Seq       : Sequence) return Boolean;

   function Inline_Option
     (Rule_Name : String;
      Seq       : Sequence) return Boolean;

   function Infix
     (Rule_Name : String;
      Seq       : Sequence) return String;

   function User_Wraps
     (Rule_Name : String;
      Seq       : Sequence) return Natural;

   function User_Wrap_Node
     (Rule_Name : String;
      Seq       : Sequence;
      Index     : Positive) return String;

   function Wrap_Item_Name
     (Rule_Name : String;
      Seq       : Sequence;
      Index     : Positive) return String;

   function Wrap_Attr_Name
     (Rule_Name : String;
      Seq       : Sequence;
      Index     : Positive) return String;

   function Get_Use_Attr
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String;
      Instance  : Positive) return String;

   function Alternative_Node_Name
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String) return String;

   function Trait_Name
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String) return String;

   function Value
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String) return String;

   function Created_Node_Name
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String) return String;

   function Choise
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String) return String;

   function Wrapper_Index
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String;
      Instance  : Positive) return Natural;

   function Wrapper_Index
     (Rule_Name : String;
      Seq       : Sequence;
      Wrapper   : Positive) return Natural;

   function Wrapper_Position
     (Rule_Name : String;
      Seq       : Sequence;
      Wrapper   : Positive) return String;

   function Wrapper_Instance
     (Rule_Name : String;
      Seq       : Sequence;
      Wrapper   : Positive) return Positive;

   function Conflict_Name (Rule_Name : String) return Boolean;

   function Skip_Rule (Rule_Name : String) return Boolean;

end Gramar_Items.Code;


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
