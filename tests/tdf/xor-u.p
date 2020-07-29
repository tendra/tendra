( include "c-types.p" )

( make_id_tagdef main
  -
  ( make_proc
    ( integer
      ~signed_int ) |
    -
    ( sequence
      ( conditional
        .fail
        ( sequence

          # 1u == 5u xor 4u
          ( integer_test equal .fail
            ( make_int ~unsigned_int 1 )
            ( xor
              ( make_int ~unsigned_int 5 )
              ( make_int ~unsigned_int 4 ) ) )

          # 0u == 4u xor 4u
          ( integer_test equal .fail
            ( make_int ~unsigned_int 0 )
            ( xor
              ( make_int ~unsigned_int 4 )
              ( make_int ~unsigned_int 4 ) ) )

          # 7u == 2u xor 5u
          ( integer_test equal .fail
            ( make_int ~unsigned_int 7 )
            ( xor
              ( make_int ~unsigned_int 2 )
              ( make_int ~unsigned_int 5 ) ) )

      )

      # failure
      ( return
        ( make_int
          ~signed_int
          1 ) ) ) |

      # success
      ( return
        ( make_int
          ~signed_int
          0 ) ) ) ) )

