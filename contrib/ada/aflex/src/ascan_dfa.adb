
with ascan_dfa; use ascan_dfa; 
package body ascan_dfa is
function YYText return string is
    i : integer;
    str_loc : integer := 1;
    buffer : string(1..1024);
    EMPTY_STRING : constant string := "";
begin
    -- find end of buffer
    i := yytext_ptr;
    while ( yy_ch_buf(i) /= ASCII.NUL ) loop
    buffer(str_loc ) := yy_ch_buf(i);
        i := i + 1;
    str_loc := str_loc + 1;
    end loop;
--    return yy_ch_buf(yytext_ptr.. i - 1);

    if (str_loc < 2) then
        return EMPTY_STRING;
    else
      return buffer(1..str_loc-1);
    end if;

end;

-- returns the length of the matched text
function YYLength return integer is
begin
    return yy_cp - yy_bp;
end YYLength;

-- done after the current pattern has been matched and before the
-- corresponding action - sets up yytext

procedure YY_DO_BEFORE_ACTION is
begin
    yytext_ptr := yy_bp;
    yy_hold_char := yy_ch_buf(yy_cp);
    yy_ch_buf(yy_cp) := ASCII.NUL;
    yy_c_buf_p := yy_cp;
end YY_DO_BEFORE_ACTION;

end ascan_dfa;
