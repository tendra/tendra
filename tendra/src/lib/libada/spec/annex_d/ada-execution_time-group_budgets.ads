------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with System;

package Ada.Execution_Time.Group_Budgets is

   type Group_Budget is tagged limited private;

   type Group_Budget_Handler is
     access protected procedure (GB : in out Group_Budget);

   type Task_Array is
     array (Positive range <>) of Ada.Task_Identification.Task_Id;

   Min_Handler_Ceiling : constant System.Any_Priority
     := implementation-defined;

   procedure Add_Task (GB : in out Group_Budget;
                       T  : in     Ada.Task_Identification.Task_Id);

   procedure Remove_Task (GB : in out Group_Budget;
                          T  : in     Ada.Task_Identification.Task_Id);

   function Is_Member (GB : in Group_Budget;
                       T  : in Ada.Task_Identification.Task_Id)
     return Boolean;

   function Is_A_Group_Member (T : in Ada.Task_Identification.Task_Id)
     return Boolean;

   function Members (GB : in Group_Budget) return Task_Array;

   procedure Replenish (GB : in out Group_Budget;
                        To : in     Ada.Real_Time.Time_Span);

   procedure Add (GB       : in out Group_Budget;
                  Interval : in     Ada.Real_Time.Time_Span);

   function Budget_Has_Expired (GB : in Group_Budget) return Boolean;

   function Budget_Remaining (GB : in Group_Budget)
     return Ada.Real_Time.Time_Span;

   procedure Set_Handler (GB      : in out Group_Budget;
                          Handler : in     Group_Budget_Handler);

   function Current_Handler (GB : in Group_Budget) return Group_Budget_Handler;

   procedure Cancel_Handler (GB        : in out Group_Budget;
                             Cancelled : out    Boolean);

   Group_Budget_Error : exception;

private

   pragma Import (Ada, Group_Budget);

end Ada.Execution_Time.Group_Budgets;
