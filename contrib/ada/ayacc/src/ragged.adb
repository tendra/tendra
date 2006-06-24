

with Unchecked_Deallocation; 
package body Ragged is 

  SCCS_ID : constant String := "@(#) ragged.ada, Version 1.2";



    -- The ragged array is implemented as a vector indexed by row 
    -- of linked lists of (column,value) pairs in sorted order. 

 
    type Cells is array( Row_Index range<> ) of Index; 
    type Cells_Ptr is access Cells; 
    pragma Controlled(Cells_Ptr); 

    Vector : Cells_Ptr; 
   
    procedure Make_Array(Lower, Upper: Row_Index) is 
    begin 
       Vector  := new Cells(Lower..Upper); 
       for I in Vector.all'range loop 
           Vector(I) := null; 
       end loop;
    end Make_Array; 


    function New_Cell(Column : Col_Index; Next : Index) return Index is 
        Temp : Index; 
    begin 
        Temp := new Cell; 
        Temp.Hidden.Column := Column; 
        Temp.Hidden.Next   := Next; 

        -- Will this work or do I need to null_value vector ? 
        Null_Value(Temp.Value); 
        return Temp;
    end New_Cell; 


    function Lval(X: Row_Index; Y: Col_Index) return Index is 
        Ptr, Last : Index;    
    begin 

        -- If a new cell is created its value field is uninitialized.

        -- Add to the beginning of the list ?  
        if Vector(X) = null or else Vector(X).Hidden.Column > Y then 
            Ptr        := Vector(X); 
            Vector(X)  := New_Cell(Y,Ptr); 
            return Vector(X); 
        end if; 

        -- Add in the middle of the list ?  
        Ptr  := Vector(X); 
        while Ptr /= null loop 

            if Ptr.Hidden.Column = Y then 
                return Ptr; 
            elsif Ptr.Hidden.Column > Y then   
                Last.Hidden.Next := New_Cell(Y,Ptr); 
                return Last.Hidden.Next; 
            end if; 
            Last := Ptr; 
            Ptr  := Ptr.Hidden.Next; 
        end loop; 
                 
        -- Add at the end of the list
        Last.Hidden.Next := New_Cell(Y,null); 
        return Last.Hidden.Next; 
    end Lval; 


    function  Rval(X: Row_Index; Y: Col_Index) return Index is 
        Ptr : Index; 
    begin 
        Ptr := Vector(X); 
        while Ptr /= null and then Ptr.Hidden.Column < Y loop 
            Ptr := Ptr.Hidden.Next; 
        end loop;
        if Ptr = null or else Ptr.Hidden.Column > Y then 
            raise Value_Range_Error; 
        else -- ptr.hidden.column = y 
            return Ptr;
        end if; 
    end Rval; 


    procedure Initialize(Iterator : out Index; Row : Row_Index)  is 
    begin 
        Iterator := Vector(Row);
    end; 


    procedure Next(Iterator : in out Index) is 
    begin 
        Iterator := Iterator.Hidden.Next; 
    end;  


    -- procedure free(i: index);  
    -- pragma interface(c,free); 

    procedure Free is new Unchecked_Deallocation(Cell, Index); 
    
    procedure Free is new Unchecked_Deallocation(Cells, Cells_Ptr); 
    
    procedure Free_Array is 
        Traverse : Index; 
    begin 
        for I in Vector.all'range loop 
            while Vector(I) /= null loop 
                Traverse  := Vector(I); 
                Vector(I) := Vector(I).Hidden.Next; 
		Null_Value(Traverse.Value); -- free value if its a ptr
                Free(Traverse); 
            end loop; 
        end loop; 
 
        Free(Vector);
    end Free_Array; 

end Ragged; 
