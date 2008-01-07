with Gela.Embeded_Links.Lists;

generic
   type Element_Type is private;
package Gela.Containers.Stacks is
   pragma Preelaborate (Stacks);

   type Stack is limited private;

   function Is_Empty (Container : Stack) return Boolean;
   function Length   (Container : Stack) return Natural;

   procedure Clear (Container : in out Stack);

   procedure Push  (Container : in out Stack;
                    Item      : in     Element_Type);

   procedure Pop   (Container : in out Stack;
                    Item      :    out Element_Type);

   procedure Pop   (Container : in out Stack);

   function Top    (Container : Stack) return Element_Type;

private
   type Node;

   type Node_Access is access all Node;

   type Node is record
      Next : Node_Access;
      Data : Element_Type;
   end record;

   function  Get_Next (Item : Node_Access) return Node_Access;
   procedure Set_Next (Item, Next : Node_Access);

   pragma Inline (Get_Next, Set_Next);

   package E is new Gela.Embeded_Links.Lists (Node, Node_Access);

   type Stack is new E.List;

end Gela.Containers.Stacks;

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
