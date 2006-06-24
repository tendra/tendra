
package body ascan_io is
-- gets input and stuffs it into 'buf'.  number of characters read, or YY_NULL,
-- is returned in 'result'.

procedure YY_INPUT(buf: out unbounded_character_array; result: out integer; max_size: in integer) is
    c : character;
    i : integer := 1;
    loc : integer := buf'first;
begin

    if (is_open(user_input_file)) then
      while ( i <= max_size ) loop
         if (end_of_line(user_input_file)) then -- Ada ate our newline, put it back on the end.
             buf(loc) := ASCII.LF;
             skip_line(user_input_file, 1);
         else
-- UCI CODES CHANGED:
--    The following codes are modified. Previous codes is commented out.
--    The purpose of doing this is to make it possible to set Temp_Line
--    in Ayacc-extension specific codes. Definitely, we can read the character
--    into the Temp_Line and then set the buf. But Temp_Line will only
--    be used in Ayacc-extension specific codes which makes this approach impossible.
           get(user_input_file, c);
           buf(loc) := c;
--         get(user_input_file, buf(loc));
         end if;

         loc := loc + 1;
         i := i + 1;
      end loop;
    else
      while ( i <= max_size ) loop
         if (end_of_line) then -- Ada ate our newline, put it back on the end.
             buf(loc) := ASCII.LF;
             skip_line(1);

         else
--    The following codes are modified. Previous codes is commented out.
--    The purpose of doing this is to make it possible to set Temp_Line
--    in Ayacc-extension specific codes. Definitely, we can read the character
--    into the Temp_Line and then set the buf. But Temp_Line will only
--    be used in Ayacc-extension specific codes which makes this approach impossible.
           get(c);
           buf(loc) := c;
--         get(buf(loc));
         end if; 

         loc := loc + 1;
         i := i + 1;
      end loop;
    end if; -- for input file being standard input

    result := i - 1; 
    exception
        when END_ERROR => result := i - 1;
    -- when we hit EOF we need to set yy_eof_has_been_seen
    yy_eof_has_been_seen := true;
end YY_INPUT;

-- yy_get_next_buffer - try to read in new buffer
--
-- returns a code representing an action
--     EOB_ACT_LAST_MATCH - 
--     EOB_ACT_RESTART_SCAN - restart the scanner
--     EOB_ACT_END_OF_FILE - end of file

function yy_get_next_buffer return eob_action_type is
    dest : integer := 0;
    source : integer := yytext_ptr - 1; -- copy prev. char, too
    number_to_move : integer;
    ret_val : eob_action_type;
    num_to_read : integer;
begin    
    if ( yy_c_buf_p > yy_n_chars + 1 ) then
        raise NULL_IN_INPUT;
    end if;

    -- try to read more data

    -- first move last chars to start of buffer
    number_to_move := yy_c_buf_p - yytext_ptr;

    for i in 0..number_to_move - 1 loop
        yy_ch_buf(dest) := yy_ch_buf(source);
    dest := dest + 1;
    source := source + 1;
    end loop;
        
    if ( yy_eof_has_been_seen ) then
    -- don't do the read, it's not guaranteed to return an EOF,
    -- just force an EOF

    yy_n_chars := 0;
    else
    num_to_read := YY_BUF_SIZE - number_to_move - 1;

    if ( num_to_read > YY_READ_BUF_SIZE ) then
        num_to_read := YY_READ_BUF_SIZE;
        end if;

    -- read in more data
    YY_INPUT( yy_ch_buf(number_to_move..yy_ch_buf'last), yy_n_chars, num_to_read );
    end if;
    if ( yy_n_chars = 0 ) then
    if ( number_to_move = 1 ) then
        ret_val := EOB_ACT_END_OF_FILE;
    else
        ret_val := EOB_ACT_LAST_MATCH;
        end if;

    yy_eof_has_been_seen := true;
    else
    ret_val := EOB_ACT_RESTART_SCAN;
    end if;
    
    yy_n_chars := yy_n_chars + number_to_move;
    yy_ch_buf(yy_n_chars) := YY_END_OF_BUFFER_CHAR;
    yy_ch_buf(yy_n_chars + 1) := YY_END_OF_BUFFER_CHAR;

    -- yytext begins at the second character in
    -- yy_ch_buf; the first character is the one which
    -- preceded it before reading in the latest buffer;
    -- it needs to be kept around in case it's a
    -- newline, so yy_get_previous_state() will have
    -- with '^' rules active

    yytext_ptr := 1;

    return ret_val;
end yy_get_next_buffer;

procedure yyunput( c : character; yy_bp: in out integer ) is
    number_to_move : integer;
    dest : integer;
    source : integer;
    tmp_yy_cp : integer;
begin
    tmp_yy_cp := yy_c_buf_p;
    yy_ch_buf(tmp_yy_cp) := yy_hold_char; -- undo effects of setting up yytext

    if ( tmp_yy_cp < 2 ) then
    -- need to shift things up to make room
    number_to_move := yy_n_chars + 2; -- +2 for EOB chars
    dest := YY_BUF_SIZE + 2;
    source := number_to_move;

    while ( source > 0 ) loop
        dest := dest - 1;
        source := source - 1;
            yy_ch_buf(dest) := yy_ch_buf(source);
    end loop;

    tmp_yy_cp := tmp_yy_cp + dest - source;
    yy_bp := yy_bp + dest - source;
    yy_n_chars := YY_BUF_SIZE;

    if ( tmp_yy_cp < 2 ) then
        raise PUSHBACK_OVERFLOW;
    end if;
    end if;

    if ( tmp_yy_cp > yy_bp and then yy_ch_buf(tmp_yy_cp-1) = ASCII.LF ) then
    yy_ch_buf(tmp_yy_cp-2) := ASCII.LF;
    end if;

    tmp_yy_cp := tmp_yy_cp - 1;
    yy_ch_buf(tmp_yy_cp) := c;

--  Note:  this code is the text of YY_DO_BEFORE_ACTION, only
--         here we get different yy_cp and yy_bp's
    yytext_ptr := yy_bp;
    yy_hold_char := yy_ch_buf(tmp_yy_cp);
    yy_ch_buf(tmp_yy_cp) := ASCII.NUL;
    yy_c_buf_p := tmp_yy_cp;
end yyunput;

procedure unput(c : character) is
begin
     yyunput( c, yy_bp );
end unput;

function input return character is
    c : character;
    yy_cp : integer := yy_c_buf_p;
begin
    yy_ch_buf(yy_cp) := yy_hold_char;

    if ( yy_ch_buf(yy_c_buf_p) = YY_END_OF_BUFFER_CHAR ) then
    -- need more input
    yytext_ptr := yy_c_buf_p;
    yy_c_buf_p := yy_c_buf_p + 1;

    case yy_get_next_buffer is
        -- this code, unfortunately, is somewhat redundant with
        -- that above

        when EOB_ACT_END_OF_FILE =>
        if ( yywrap ) then
            yy_c_buf_p := yytext_ptr;
            return ASCII.NUL;
        end if;

        yy_ch_buf(0) := ASCII.LF;
        yy_n_chars := 1;
        yy_ch_buf(yy_n_chars) := YY_END_OF_BUFFER_CHAR;
        yy_ch_buf(yy_n_chars + 1) := YY_END_OF_BUFFER_CHAR;
        yy_eof_has_been_seen := false;
        yy_c_buf_p := 1;
        yytext_ptr := yy_c_buf_p;
        yy_hold_char := yy_ch_buf(yy_c_buf_p);

        return ( input );
        when EOB_ACT_RESTART_SCAN =>
        yy_c_buf_p := yytext_ptr;

        when EOB_ACT_LAST_MATCH =>
        raise UNEXPECTED_LAST_MATCH;
        when others => null;
        end case;
    end if;

    c := yy_ch_buf(yy_c_buf_p);
    yy_c_buf_p := yy_c_buf_p + 1;
    yy_hold_char := yy_ch_buf(yy_c_buf_p);

    return c;
end input;

procedure output(c : character) is
begin
    if (is_open(user_output_file)) then
      text_io.put(user_output_file, c);
    else
      text_io.put(c);
    end if;
end output;

-- default yywrap function - always treat EOF as an EOF
function yywrap return boolean is
begin
    return true;
end yywrap;

procedure Open_Input(fname : in String) is
begin
    yy_init := true;
    open(user_input_file, in_file, fname);
end Open_Input;

procedure Create_Output(fname : in String := "") is
begin
    if (fname /= "") then
        create(user_output_file, out_file, fname);
    end if;
end Create_Output;

procedure Close_Input is
begin
   if (is_open(user_input_file)) then
     text_io.close(user_input_file);
   end if;
end Close_Input;

procedure Close_Output is
begin
   if (is_open(user_output_file)) then
     text_io.close(user_output_file);
   end if;
end Close_Output;


end ascan_io;
