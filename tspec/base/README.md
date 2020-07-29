# Base API Specifications

This directory contains the specifications for various standard base APIs
as tspec descriptions.  They are used to generate the API token headers
which are used in the compiler's API checking.


                 ansi
                  |
          +-------+-------+
          |               |
          |             posix
          |               |
          |       +-------+
          |       |       |
          |      xpg3   posix1
          |       |       |
          |       |       |
          |       |       |
         iso      |     posix2
          |       |      |  |
          +-------+------+  |
                  |         |
                 xpg4     posix3
                  |
                  |
                  |
                unix95
