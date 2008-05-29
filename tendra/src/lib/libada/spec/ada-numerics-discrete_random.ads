------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

generic
   type Result_Subtype is (<>);
package Ada.Numerics.Discrete_Random is

   -- Basic facilities

   type Generator is limited private;

   function Random (Gen : Generator) return Result_Subtype;

   procedure Reset (Gen       : in Generator;
                    Initiator : in Integer);
   procedure Reset (Gen       : in Generator);

   -- Advanced facilities

   type State is private;

   procedure Save  (Gen        : in  Generator;
                    To_State   : out State);
   procedure Reset (Gen        : in  Generator;
                    From_State : in  State);

   Max_Image_Width : constant := implementation-defined;

   function Image (Of_State    : State)  return String;
   function Value (Coded_State : String) return State;

private

   pragma Import (Ada, State);
   pragma Import (Ada, Generator);

end Ada.Numerics.Discrete_Random;



