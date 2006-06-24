------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Helper procedures to implement down-to-up pass

package Asis.Gela.Overloads.Walk.Up is

   procedure Push_Single
     (Resolver : in out Up_Resolver;
      Item     : in     Up_Interpretation;
      Resolve  : in     Boolean := False);

   procedure Operator_Symbol_Or_String
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element);

   procedure Function_Call
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element);

   procedure Explicit_Dereference
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element);

   procedure Selected_Component
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element);

   procedure Simple_Range
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element);

   procedure Attribute_Reference
     (Resolver : in out Up_Resolver;
      Element  : in     Asis.Element);

   procedure Aggregate
     (Resolver  : in out Up_Resolver;
      Element   : in     Asis.Element;
      Extension : in     Boolean := False);

   procedure Membership
     (Resolver  : in out Up_Resolver;
      Element   : in     Asis.Element);

   procedure Short_Circuit
     (Resolver  : in out Up_Resolver;
      Element   : in     Asis.Element);

   procedure Qualified_Expression
     (Resolver  : in out Up_Resolver;
      Element   : in     Asis.Element);

   procedure Allocation
     (Resolver  : in out Up_Resolver;
      Element   : in     Asis.Element;
      From_Expr : in     Boolean := False);

   procedure Assignment
     (Resolver  : in out Up_Resolver;
      Element   : in     Asis.Element);

end Asis.Gela.Overloads.Walk.Up;


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
