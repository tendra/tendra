
with Unchecked_Deallocation;
package body Stack_Pack is 

  SCCS_ID : constant String := "@(#) stack.ada, Version 1.2";



    type Node is 
        record 
            Datum : Element; 
            Next  : Link; 
        end record; 

    function Top_Value (S: in Stack) return Element is 
    begin 
        if S.Top = null then 
            raise Stack_Underflow; 
        else 
            return S.Top.Datum; 
        end if; 
    end Top_Value;  
 

    function Depth_of_Stack (S: in Stack) return Natural is 
    begin 
        return S.Tos; 
    end Depth_of_Stack;  


    procedure Make_Stack(S: out Stack) is 
    begin 
        S := (Tos => 0, Top | Extras => null); 
    end Make_Stack; 

 
    procedure Push(S: in out Stack; Value: in Element) is 
        New_Node : Link; 
    begin 
        S.Tos := S.Tos + 1; 
        if S.Extras = null then  
            New_Node := new Node;  
        else 
            New_Node := S.Extras; 
            S.Extras := S.Extras.Next;  
        end if; 
        New_Node.all := (Datum => Value, Next => S.Top);  
        S.Top := New_Node; 
    end Push; 


    procedure Pop (S: in out Stack; Value: out Element) is 
        Temp : Link;
    begin 
        if S.Tos = 0 then 
            raise Stack_Underflow; 
        end if; 

        Value := S.Top.Datum; 

        Temp       := S.Top.Next; 
        S.Top.Next := S.Extras; 
        S.Extras   := S.Top;  
        S.Top      := Temp; 

        S.Tos := S.Tos - 1;  
    end Pop; 

    procedure Free is new Unchecked_Deallocation(Node, Link); 

    -- procedure free(x : link); 
    -- pragma interface(c , free); 

    procedure Free_List(List: in out Link) is 
        Temp : Link; 
    begin 
        Temp := List; 
        while Temp /= null loop 
            List := List.Next; 
            Free(Temp); 
            Temp := List; 
        end loop; 
    end Free_List; 

    procedure Free_Stack(S: in out Stack) is 
    begin 
        Free_List(S.Top); 
        Free_List(S.Extras); 
    end Free_Stack; 

end Stack_Pack; 
