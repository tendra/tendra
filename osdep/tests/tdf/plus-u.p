# $Id$

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

          # 9u == 5u + 4u
          ( integer_test equal .fail
            ( make_int ~unsigned_int 9 )
            ( plus
              ( error_jump .fail )
              ( make_int ~unsigned_int 5 )
              ( make_int ~unsigned_int 4 ) ) )

          # 8u == 4u + 4u
          ( integer_test equal .fail
            ( make_int ~unsigned_int 8 )
            ( plus
              ( error_jump .fail )
              ( make_int ~unsigned_int 4 )
              ( make_int ~unsigned_int 4 ) ) )

          # 7u == 2u + 5u
          ( integer_test equal .fail
            ( make_int ~unsigned_int 7 )
            ( plus
              ( error_jump .fail )
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

