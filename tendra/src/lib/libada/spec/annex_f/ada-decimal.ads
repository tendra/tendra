------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Decimal is

   pragma Pure (Decimal);

   Max_Scale : constant := implementation-defined;
   Min_Scale : constant := implementation-defined;

   Min_Delta : constant := 10.0**(-Max_Scale);
   Max_Delta : constant := 10.0**(-Min_Scale);

   Max_Decimal_Digits : constant := implementation-defined;

   generic
      type Dividend_Type is delta <> digits <>;
      type Divisor_Type is delta <> digits <>;
      type Quotient_Type is delta <> digits <>;
      type Remainder_Type is delta <> digits <>;

   procedure Divide (Dividend  : in     Dividend_Type;
                     Divisor   : in     Divisor_Type;
                     Quotient  :    out Quotient_Type;
                     Remainder :    out Remainder_Type);
   pragma Convention (Intrinsic, Divide);

end Ada.Decimal;
