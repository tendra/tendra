with Unchecked_Deallocation;

package body Lists is


    procedure Free is
        new Unchecked_Deallocation (Element_Type, Element_Pointer);

    --------------------------------------------------------------------------

    procedure Attach (List1 : in out List; 
                      List2 : in List) is

        Endoflist1 : Element_Pointer;

        --| Attach List2 to List1.
        --| If List1 is null return List2
        --| If List1 equals List2 then raise CircularList
        --| Otherwise get the pointer to the last element of List1 and change
        --| its Next field to be List2.

    begin
        if List1.Head = null then
            List1 := List2;
        elsif List1 = List2 then
            raise Circularlist;
        else
            Endoflist1      := List1.Tail;
            Endoflist1.Next := List2.Head;
            List1.Tail      := List2.Tail;
        end if;
    end Attach;

    --------------------------------------------------------------------------

    procedure Attach (L : in out List; 
                      Element : in Itemtype) is

        Old_Tail, New_Element : Element_Pointer;

        --| Create a list containing Element and attach it to the end of L

    begin
        New_Element := new Element_Type'(Item => Element, Next => null);
        if L.Head = null then
          L.Head := New_Element;
          L.Tail := New_Element;
        else
          Old_Tail      := L.Tail;
          Old_Tail.Next := New_Element;
          L.Tail        := New_Element;
        end if;
      end Attach;

    --------------------------------------------------------------------------

    function Attach (Element1 : in Itemtype; 
                     Element2 : in Itemtype) return List is

        Newlist : List;

        --| Create a new list containing the information in Element1 and
        --| attach Element2 to that list.

    begin
        Newlist.Head := new Element_Type'(Item => Element1, Next => null);
        Newlist.Tail := NewList.Head;
        Attach (Newlist, Element2);
        return Newlist;
    end Attach;

    --------------------------------------------------------------------------

    procedure Attach (Element : in Itemtype; 
                      L : in out List) is

        --|  Create a new cell whose information is Element and whose Next
        --|  field is the list L.  This prepends Element to the List L.

        Old_Head, New_Head : Element_Pointer;

    begin
        if L.Head = null then
          L.Head := new Element_Type'(Item => Element, Next => null);
          L.Tail := L.Head;
        else
          Old_Head := L.Head;
          New_Head := new Element_Type'(Item => Element, Next => Old_Head);
          L.Head   := New_Head;
        end if;
    end Attach;

    --------------------------------------------------------------------------

    function Attach (List1 : in List; 
                     List2 : in List) return List is

        --| Attach List2 to List1.
        --| If List1 is null return List2
        --| If List1 equals List2 then raise CircularList
        --| Otherwise get the pointer to the last element of List1 and change
        --| its Next field to be List2.

        End_Of_List1 : Element_Pointer;
        New_List     : List;

    begin
        if List1.Head = null then
            return List2;
        elsif List1 = List2 then
            raise Circularlist;
        else
            End_Of_List1      := List1.Tail;
            End_Of_List1.Next := List2.Head;
            New_List.Head     := List1.Head;
            New_List.Tail     := List2.Tail;
            return New_List;
        end if;
    end Attach;

    -------------------------------------------------------------------------

    function Attach (L : in List; 
                     Element : in Itemtype) return List is

        New_Element : Element_Pointer;
        New_List    : List;
        End_Of_List : Element_Pointer;

        --| Create a list called New_List and attach it to the end of L.
        --| If L is null return New_List
        --| Otherwise get the last element in L and make its Next field
        --| New_List.

    begin
        New_Element := new Element_Type'(Item => Element, Next => null);
        if L.Head = null then
            New_List := (Head => New_Element, Tail => New_Element);
        else
            End_Of_List      := L.Tail;
            End_Of_List.Next := New_Element;
            New_List         := (Head => L.Head, Tail => New_Element);
        end if;
        return New_List;
    end Attach;

    --------------------------------------------------------------------------

    function Attach (Element : in Itemtype; 
                     L : in List) return List is

        New_Element : Element_Pointer;

    begin
        if L.Head = null then
          New_Element := new Element_Type'(Item => Element, Next => null);
          return (Head => New_Element, Tail => New_Element);
        else
          New_Element := new Element_Type'(Item => Element, Next => L.Head);
          return (Head => New_Element, Tail => L.Tail);
        end if;
    end Attach;

    --------------------------------------------------------------------------

    function Copy (L : in List) return List is

        --| If L is null return null
        --| Otherwise recursively copy the list by first copying the information
        --| at the head of the list and then making the Next field point to
        --| a copy of the tail of the list.

        Current_Element : Element_Pointer := L.Head;
        New_List        : List := (Head => null, Tail => null);

    begin
        while Current_Element /= null loop
            Attach (New_List, Current_Element.Item);
            Current_Element := Current_Element.Next;
        end loop;
        return New_List;
    end Copy;


    --------------------------------------------------------------------------

    --generic
    --  with function Copy (I : in Itemtype) return Itemtype;
    function Copydeep (L : in List) return List is

        --|  If L is null then return null.
        --|  Otherwise copy the first element of the list into the head of the
        --|  new list and copy the tail of the list recursively using CopyDeep.

        Current_Element : Element_Pointer := L.Head;
        New_List        : List := (Head => null, Tail => null);

    begin
        while Current_Element /= null loop
            Attach (New_List, Copy (Current_Element.Item));
            Current_Element := Current_Element.next;
        end loop;
        return New_List;
    end Copydeep;

    --------------------------------------------------------------------------

    function Create return List is

        --| Return the empty list.

    begin
        return (Head => null, Tail => null);
    end Create;

    --------------------------------------------------------------------------
    procedure Deletehead (L : in out List) is

        New_Head : Element_Pointer;

        --| Remove the element of the head of the list and return it to the heap.
        --| If L is null EmptyList.
        --| Otherwise save the Next field of the first element, remove the first
        --| element and then assign to L the Next field of the first element.

    begin
        if L.Head = null then
            raise Emptylist;
        else
            New_Head := L.Head.Next;
            Free (L.Head);
            L.Head := New_Head;
        end if;
    end Deletehead;

    --------------------------------------------------------------------------

    procedure Deleteitem (L : in out List; 
                          Element : in Itemtype) is


        --| Remove the first element in the list with the value Element.
        --| If the first element of the list is equal to element then
        --| remove it.  Otherwise, recurse on the tail of the list.

        Current_Element, Previous_Element : Element_Pointer;

    begin
        if L.Head = null then
            raise Itemnotpresent;
        elsif Equal (L.Head.Item, Element) then
            Deletehead (L);
        else
            Current_Element  := L.Head.Next;
            Previous_Element := L.Head;

            while Current_Element /= null and then 
                not Equal (Current_Element.Item, Element) loop

                Previous_Element := Current_Element;
                Current_Element  := Current_Element.Next;

            end loop;

            if Current_Element = null then
                raise Itemnotpresent;
            else

                if Current_Element = L.Tail then
                    L.Tail := Previous_Element;
                end if;

                Previous_Element.Next := Current_Element.Next;
                Free (Current_Element);

            end if;
        end if;
    end Deleteitem;

    --------------------------------------------------------------------------

    procedure Deleteitems (L : in out List; 
                           Element : in Itemtype) is

        Delete_List_Is_Empty  : Boolean := True;
        New_List_Is_Empty     : Boolean := True;
        Old_Tail              : Element_Pointer;
        Current_Element       : Element_Pointer := L.Head;
        New_List, Delete_List : List;

        procedure Append (Element : in out Element_Pointer;
                          To_List : in out List) is
	begin
            if To_List.Head = null then
                To_List.Head := Element;
                To_List.Tail := Element;
            else
                Old_Tail      := To_List.Tail;
                To_List.Tail  := Element;
                Old_Tail.Next := To_List.Tail;
	    end if;
	end Append;

    begin
        while Current_Element /= null loop
            if Equal (Current_Element.Item, Element) then
                Append (Element => Current_Element,
                        To_List => Delete_List);
                Delete_List_Is_Empty := False;
            else
                Append (Element => Current_Element,
                        To_List => New_List);
                New_List_Is_Empty := False;
            end if;

            Current_Element := Current_Element.Next;
        end loop;

        if Delete_List_Is_Empty then
            raise Itemnotpresent;
        else
            Delete_List.Tail.Next := null;
            Destroy (Delete_List);
        end if;

        if not New_List_Is_Empty then
            New_List.Tail.Next := null;
	end if;

        L := New_List;
    end Deleteitems;

    --------------------------------------------------------------------------

    procedure Destroy (L : in out List) is

        Current_Element   : Element_Pointer := L.Head;
        Element_To_Delete : Element_Pointer;

        --| Walk down the list removing all the elements and set the list to
        --| the empty list.

    begin
        if L.Head /= null then
            while Current_Element /= null loop
                Element_To_Delete := Current_Element;
                Current_Element   := Current_Element.Next;
                Free (Element_To_Delete);
            end loop;
            L := (Head => null, Tail => null);
        end if;
    end Destroy;

    --------------------------------------------------------------------------

    function Firstvalue (L : in List) return Itemtype is

        --| Return the first value in the list.

    begin
        if L.Head = null then
            raise Emptylist;
        else
            return L.Head.Item;
        end if;
    end Firstvalue;

    --------------------------------------------------------------------------

    function Isinlist (L : in List; 
                       Element : in Itemtype) return Boolean is

        Current_Element : Element_Pointer := L.Head;

        --| Check if Element is in L.  If it is return true otherwise return false.

    begin
        while Current_Element /= null and then
            not Equal (Current_Element.Item, Element) loop
                Current_Element := Current_Element.Next;
        end loop;
        return Current_Element /= null;
    end Isinlist;

    --------------------------------------------------------------------------

    function Isempty (L : in List) return Boolean is

        --| Is the list L empty.

    begin
        return L.Head = null;
    end Isempty;

    --------------------------------------------------------------------------

    function Lastvalue (L : in List) return Itemtype is


        --| Return the value of the last element of the list. Get the pointer
        --| to the last element of L and then return its information.

    begin
        if L.Head = null then
            raise Emptylist;
        else
            return L.Tail.Item;
        end if;
    end Lastvalue;

    --------------------------------------------------------------------------

    function Length (L : in List) return Integer is

        --| Recursively compute the length of L.  The length of a list is
        --| 0 if it is null or  1 + the length of the tail.

        Current_Element : Element_Pointer := L.Head;
        List_Length     : Natural := 0;

    begin
        while Current_Element /= null loop
            List_Length     := List_Length + 1;
            Current_Element := Current_Element.Next;
        end loop;

        return List_Length;
    end Length;

    --------------------------------------------------------------------------

    function Makelistiter (L : in List) return Listiter is

        --| Start an iteration operation on the list L.  Do a type conversion
        --| from List to ListIter.

    begin
        return Listiter (L);
    end Makelistiter;

    --------------------------------------------------------------------------

    function More (L : in Listiter) return Boolean is

        --| This is a test to see whether an iteration is complete.

    begin
        return L.Head /= null;
    end More;

    --------------------------------------------------------------------------

    procedure Next (Place : in out Listiter; 
                    Info : out Itemtype) is

        --| This procedure gets the information at the current place in the List
        --| and moves the ListIter to the next postion in the list.
        --| If we are at the end of a list then exception NoMore is raised.

        Next_Element : Element_Pointer := Place.Head;

    begin
        if Next_Element = null then
            raise Nomore;
        else
            Info       := Next_Element.Item;
            Place.Head := Next_Element.Next;
        end if;
    end Next;

    --------------------------------------------------------------------------

    procedure Replacehead (L : in out List; 
                           Info : in Itemtype) is

        --| This procedure replaces the information at the head of a list
        --| with the given information. If the list is empty the exception
        --| EmptyList is raised.

    begin
        if L.Head = null then
            raise Emptylist;
        else
            L.Head.Item := Info;
        end if;
    end Replacehead;

    --------------------------------------------------------------------------

    procedure Replacetail (L : in out List; 
                           Newtail : in List) is

        List_Head_Item : Itemtype;

        --| This destroys the tail of a list and replaces the tail with
        --| NewTail.  If L is empty EmptyList is raised.

    begin
        if L.Head = null then
            raise Emptylist;
        else
            List_Head_Item := L.Head.Item;
            Destroy (L);
            L := Attach (List_Head_Item, Newtail);
        end if;
    end Replacetail;

    --------------------------------------------------------------------------

    function Tail (L : in List) return List is

        --| This returns the list which is the tail of L.  If L is null Empty
        --| List is raised.

    begin
        if L.Head = null then
            raise Emptylist;
        else
            return (Head => L.Head.Next, Tail => L.Tail);
        end if;
    end Tail;

    --------------------------------------------------------------------------
    function Equal (List1 : in List; 
                    List2 : in List) return Boolean is

        Placeinlist1 : Element_Pointer := List1.Head;
        Placeinlist2 : Element_Pointer := List2.Head;
        Contents1    : Itemtype;
        Contents2    : Itemtype;

        --| This function tests to see if two lists are equal.  Two lists
        --| are equal if for all the elements of List1 the corresponding
        --| element of List2 has the same value.  Thus if the 1st elements
        --| are equal and the second elements are equal and so up to n.
        --|  Thus a necessary condition for two lists to be equal is that
        --| they have the same number of elements.

        --| This function walks over the two list and checks that the
        --| corresponding elements are equal.  As soon as we reach
        --| the end of a list (PlaceInList = null) we fall out of the loop.
        --| If both PlaceInList1 and PlaceInList2 are null after exiting the loop
        --| then the lists are equal.  If they both are not null the lists aren't
        --| equal.  Note that equality on elements is based on a user supplied
        --| function Equal which is used to test for item equality.

    begin
        while (Placeinlist1 /= null) and then (Placeinlist2 /= null) loop
            if not Equal (Placeinlist1.Item, Placeinlist2.Item) then
                return False;
            end if;
            Placeinlist1 := Placeinlist1.Next;
            Placeinlist2 := Placeinlist2.Next;
        end loop;
        return ((Placeinlist1 = null) and then (Placeinlist2 = null));
    end Equal;


end Lists;
