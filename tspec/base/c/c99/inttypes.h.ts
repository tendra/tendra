# Copyright 2015, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+USE "c/c89", "stddef.h.ts", "wchar_t";

# 7.8 p1
+IMPLEMENT "c/c99", "stdint.h.ts";

# 7.8 p2
+TYPE (struct) imaxdiv_t;

# 7.8 p1 mandatory signed types
+DEFINE PRIdLEAST8  %% __PRIdLEAST8  %%;
+DEFINE PRIdFAST8   %% __PRIdFAST8   %%;
+DEFINE PRIiLEAST8  %% __PRIiLEAST8  %%;
+DEFINE PRIiFAST8   %% __PRIiFAST8   %%;
+DEFINE PRIdLEAST16 %% __PRIdLEAST16 %%;
+DEFINE PRIdFAST16  %% __PRIdFAST16  %%;
+DEFINE PRIiLEAST16 %% __PRIiLEAST16 %%;
+DEFINE PRIiFAST16  %% __PRIiFAST16  %%;
+DEFINE PRIdLEAST32 %% __PRIdLEAST32 %%;
+DEFINE PRIdFAST32  %% __PRIdFAST32  %%;
+DEFINE PRIiLEAST32 %% __PRIiLEAST32 %%;
+DEFINE PRIiFAST32  %% __PRIiFAST32  %%;
+DEFINE PRIdLEAST64 %% __PRIdLEAST64 %%;
+DEFINE PRIdFAST64  %% __PRIdFAST64  %%;
+DEFINE PRIiLEAST64 %% __PRIiLEAST64 %%;
+DEFINE PRIiFAST64  %% __PRIiFAST64  %%;

# 7.8 p1 optional signed types
+IFDEF ~have_int8_t
+DEFINE PRId8       %% __PRId8       %%;
+DEFINE PRIi8       %% __PRIi8       %%;
+ENDIF
+IFDEF ~have_int16_t
+DEFINE PRId16      %% __PRId16      %%;
+DEFINE PRIi16      %% __PRIi16      %%;
+ENDIF
+IFDEF ~have_int24_t
+DEFINE PRId24      %% __PRId24      %%;
+DEFINE PRIdLEAST24 %% __PRIdLEAST24 %%;
+DEFINE PRIdFAST24  %% __PRIdFAST24  %%;
+DEFINE PRIi24      %% __PRIi24      %%;
+DEFINE PRIiLEAST24 %% __PRIiLEAST24 %%;
+DEFINE PRIiFAST24  %% __PRIiFAST24  %%;
+ENDIF
+IFDEF ~have_int32_t
+DEFINE PRId32      %% __PRId32      %%;
+DEFINE PRIi32      %% __PRIi32      %%;
+ENDIF
+IFDEF ~have_int48_t
+DEFINE PRId48      %% __PRId48      %%;
+DEFINE PRIdLEAST48 %% __PRIdLEAST48 %%;
+DEFINE PRIdFAST48  %% __PRIdFAST48  %%;
+DEFINE PRIi48      %% __PRIi48      %%;
+DEFINE PRIiLEAST48 %% __PRIiLEAST48 %%;
+DEFINE PRIiFAST48  %% __PRIiFAST48  %%;
+ENDIF
+IFDEF ~have_int64_t
+DEFINE PRId64      %% __PRId64      %%;
+DEFINE PRIi64      %% __PRIi64      %%;
+ENDIF

# 7.8 p3 mandatory unsigned types
+DEFINE PRIoLEAST8  %% __PRIoLEAST8  %%;
+DEFINE PRIoFAST8   %% __PRIoFAST8   %%;
+DEFINE PRIuLEAST8  %% __PRIuLEAST8  %%;
+DEFINE PRIuFAST8   %% __PRIuFAST8   %%;
+DEFINE PRIxLEAST8  %% __PRIxLEAST8  %%;
+DEFINE PRIxFAST8   %% __PRIxFAST8   %%;
+DEFINE PRIXLEAST8  %% __PRIXLEAST8  %%;
+DEFINE PRIXFAST8   %% __PRIXFAST8   %%;
+DEFINE PRIoLEAST16 %% __PRIoLEAST16 %%;
+DEFINE PRIoFAST16  %% __PRIoFAST16  %%;
+DEFINE PRIuLEAST16 %% __PRIuLEAST16 %%;
+DEFINE PRIuFAST16  %% __PRIuFAST16  %%;
+DEFINE PRIxLEAST16 %% __PRIxLEAST16 %%;
+DEFINE PRIxFAST16  %% __PRIxFAST16  %%;
+DEFINE PRIXLEAST16 %% __PRIXLEAST16 %%;
+DEFINE PRIXFAST16  %% __PRIXFAST16  %%;
+DEFINE PRIoLEAST32 %% __PRIoLEAST32 %%;
+DEFINE PRIoFAST32  %% __PRIoFAST32  %%;
+DEFINE PRIuLEAST32 %% __PRIuLEAST32 %%;
+DEFINE PRIuFAST32  %% __PRIuFAST32  %%;
+DEFINE PRIxLEAST32 %% __PRIxLEAST32 %%;
+DEFINE PRIxFAST32  %% __PRIxFAST32  %%;
+DEFINE PRIXLEAST32 %% __PRIXLEAST32 %%;
+DEFINE PRIXFAST32  %% __PRIXFAST32  %%;
+DEFINE PRIoLEAST64 %% __PRIoLEAST64 %%;
+DEFINE PRIoFAST64  %% __PRIoFAST64  %%;
+DEFINE PRIuLEAST64 %% __PRIuLEAST64 %%;
+DEFINE PRIuFAST64  %% __PRIuFAST64  %%;
+DEFINE PRIxLEAST64 %% __PRIxLEAST64 %%;
+DEFINE PRIxFAST64  %% __PRIxFAST64  %%;
+DEFINE PRIXLEAST64 %% __PRIXLEAST64 %%;
+DEFINE PRIXFAST64  %% __PRIXFAST64  %%;

# 7.8 p3 optional unsigned types
+IFDEF ~have_uint8_t
+DEFINE PRIo8       %% __PRIo8       %%;
+DEFINE PRIu8       %% __PRIu8       %%;
+DEFINE PRIx8       %% __PRIx8       %%;
+DEFINE PRIX8       %% __PRIX8       %%;
+ENDIF
+IFDEF ~have_uint16_t
+DEFINE PRIo16      %% __PRIo16      %%;
+DEFINE PRIu16      %% __PRIu16      %%;
+DEFINE PRIx16      %% __PRIx16      %%;
+DEFINE PRIX16      %% __PRIX16      %%;
+ENDIF
+IFDEF ~have_uint24_t
+DEFINE PRIo24      %% __PRIo24      %%;
+DEFINE PRIoLEAST24 %% __PRIoLEAST24 %%;
+DEFINE PRIoFAST24  %% __PRIoFAST24  %%;
+DEFINE PRIu24      %% __PRIu24      %%;
+DEFINE PRIuLEAST24 %% __PRIuLEAST24 %%;
+DEFINE PRIuFAST24  %% __PRIuFAST24  %%;
+DEFINE PRIx24      %% __PRIx24      %%;
+DEFINE PRIxLEAST24 %% __PRIxLEAST24 %%;
+DEFINE PRIxFAST24  %% __PRIxFAST24  %%;
+DEFINE PRIX24      %% __PRIX24      %%;
+DEFINE PRIXLEAST24 %% __PRIXLEAST24 %%;
+DEFINE PRIXFAST24  %% __PRIXFAST24  %%;
+ENDIF
+IFDEF ~have_uint32_t
+DEFINE PRIo32      %% __PRIo32      %%;
+DEFINE PRIu32      %% __PRIu32      %%;
+DEFINE PRIx32      %% __PRIx32      %%;
+DEFINE PRIX32      %% __PRIX32      %%;
+ENDIF
+IFDEF ~have_uint48_t
+DEFINE PRIo48      %% __PRIo48      %%;
+DEFINE PRIoLEAST48 %% __PRIoLEAST48 %%;
+DEFINE PRIoFAST48  %% __PRIoFAST48  %%;
+DEFINE PRIu48      %% __PRIu48      %%;
+DEFINE PRIuLEAST48 %% __PRIuLEAST48 %%;
+DEFINE PRIuFAST48  %% __PRIuFAST48  %%;
+DEFINE PRIx48      %% __PRIx48      %%;
+DEFINE PRIxLEAST48 %% __PRIxLEAST48 %%;
+DEFINE PRIxFAST48  %% __PRIxFAST48  %%;
+DEFINE PRIX48      %% __PRIX48      %%;
+DEFINE PRIXLEAST48 %% __PRIXLEAST48 %%;
+DEFINE PRIXFAST48  %% __PRIXFAST48  %%;
+ENDIF
+IFDEF ~have_uint64_t
+DEFINE PRIo64      %% __PRIo64      %%;
+DEFINE PRIu64      %% __PRIu64      %%;
+DEFINE PRIx64      %% __PRIx64      %%;
+DEFINE PRIX64      %% __PRIX64      %%;
+ENDIF

# 7.8 p4 mandatory signed types
+DEFINE SCNdLEAST8  %% __SCNdLEAST8  %%;
+DEFINE SCNdFAST8   %% __SCNdFAST8   %%;
+DEFINE SCNiLEAST8  %% __SCNiLEAST8  %%;
+DEFINE SCNiFAST8   %% __SCNiFAST8   %%;
+DEFINE SCNdLEAST16 %% __SCNdLEAST16 %%;
+DEFINE SCNdFAST16  %% __SCNdFAST16  %%;
+DEFINE SCNiLEAST16 %% __SCNiLEAST16 %%;
+DEFINE SCNiFAST16  %% __SCNiFAST16  %%;
+DEFINE SCNdLEAST32 %% __SCNdLEAST32 %%;
+DEFINE SCNdFAST32  %% __SCNdFAST32  %%;
+DEFINE SCNiLEAST32 %% __SCNiLEAST32 %%;
+DEFINE SCNiFAST32  %% __SCNiFAST32  %%;
+DEFINE SCNdLEAST64 %% __SCNdLEAST64 %%;
+DEFINE SCNdFAST64  %% __SCNdFAST64  %%;
+DEFINE SCNiLEAST64 %% __SCNiLEAST64 %%;
+DEFINE SCNiFAST64  %% __SCNiFAST64  %%;

# 7.8 p4 optional signed types
+IFDEF ~have_uint8_t
+DEFINE SCNd8       %% __SCNd8       %%;
+DEFINE SCNi8       %% __SCNi8       %%;
+ENDIF
+IFDEF ~have_uint16_t
+DEFINE SCNd16      %% __SCNd16      %%;
+DEFINE SCNi16      %% __SCNi16      %%;
+ENDIF
+IFDEF ~have_uint24_t
+DEFINE SCNd24      %% __SCNd24      %%;
+DEFINE SCNdLEAST24 %% __SCNdLEAST24 %%;
+DEFINE SCNdFAST24  %% __SCNdFAST24  %%;
+DEFINE SCNi24      %% __SCNi24      %%;
+DEFINE SCNiLEAST24 %% __SCNiLEAST24 %%;
+DEFINE SCNiFAST24  %% __SCNiFAST24  %%;
+ENDIF
+IFDEF ~have_uint32_t
+DEFINE SCNd32      %% __SCNd32      %%;
+DEFINE SCNi32      %% __SCNi32      %%;
+ENDIF
+IFDEF ~have_uint48_t
+DEFINE SCNd48      %% __SCNd48      %%;
+DEFINE SCNdLEAST48 %% __SCNdLEAST48 %%;
+DEFINE SCNdFAST48  %% __SCNdFAST48  %%;
+DEFINE SCNi48      %% __SCNi48      %%;
+DEFINE SCNiLEAST48 %% __SCNiLEAST48 %%;
+DEFINE SCNiFAST48  %% __SCNiFAST48  %%;
+ENDIF
+IFDEF ~have_uint64_t
+DEFINE SCNd64      %% __SCNd64      %%;
+DEFINE SCNi64      %% __SCNi64      %%;
+ENDIF

# 7.8 p5 mandatory unsigned types
+DEFINE SCNoLEAST8  %% __SCNoLEAST8  %%;
+DEFINE SCNoFAST8   %% __SCNoFAST8   %%;
+DEFINE SCNuLEAST8  %% __SCNuLEAST8  %%;
+DEFINE SCNuFAST8   %% __SCNuFAST8   %%;
+DEFINE SCNxLEAST8  %% __SCNxLEAST8  %%;
+DEFINE SCNxFAST8   %% __SCNxFAST8   %%;
+DEFINE SCNoLEAST16 %% __SCNoLEAST16 %%;
+DEFINE SCNoFAST16  %% __SCNoFAST16  %%;
+DEFINE SCNuLEAST16 %% __SCNuLEAST16 %%;
+DEFINE SCNuFAST16  %% __SCNuFAST16  %%;
+DEFINE SCNxLEAST16 %% __SCNxLEAST16 %%;
+DEFINE SCNxFAST16  %% __SCNxFAST16  %%;
+DEFINE SCNoLEAST32 %% __SCNoLEAST32 %%;
+DEFINE SCNoFAST32  %% __SCNoFAST32  %%;
+DEFINE SCNuLEAST32 %% __SCNuLEAST32 %%;
+DEFINE SCNuFAST32  %% __SCNuFAST32  %%;
+DEFINE SCNxLEAST32 %% __SCNxLEAST32 %%;
+DEFINE SCNxFAST32  %% __SCNxFAST32  %%;
+DEFINE SCNoLEAST64 %% __SCNoLEAST64 %%;
+DEFINE SCNoFAST64  %% __SCNoFAST64  %%;
+DEFINE SCNuLEAST64 %% __SCNuLEAST64 %%;
+DEFINE SCNuFAST64  %% __SCNuFAST64  %%;
+DEFINE SCNxLEAST64 %% __SCNxLEAST64 %%;
+DEFINE SCNxFAST64  %% __SCNxFAST64  %%;

# 7.8 p5 optional unsigned types
+IFDEF ~have_uint8_t
+DEFINE SCNo8       %% __SCNo8       %%;
+DEFINE SCNu8       %% __SCNu8       %%;
+DEFINE SCNx8       %% __SCNx8       %%;
+ENDIF
+IFDEF ~have_uint16_t
+DEFINE SCNo16      %% __SCNo16      %%;
+DEFINE SCNu16      %% __SCNu16      %%;
+DEFINE SCNx16      %% __SCNx16      %%;
+ENDIF
+IFDEF ~have_uint24_t
+DEFINE SCNo24      %% __SCNo24      %%;
+DEFINE SCNoLEAST24 %% __SCNoLEAST24 %%;
+DEFINE SCNoFAST24  %% __SCNoFAST24  %%;
+DEFINE SCNu24      %% __SCNu24      %%;
+DEFINE SCNuLEAST24 %% __SCNuLEAST24 %%;
+DEFINE SCNuFAST24  %% __SCNuFAST24  %%;
+DEFINE SCNx24      %% __SCNx24      %%;
+DEFINE SCNxLEAST24 %% __SCNxLEAST24 %%;
+DEFINE SCNxFAST24  %% __SCNxFAST24  %%;
+ENDIF
+IFDEF ~have_uint32_t
+DEFINE SCNo32      %% __SCNo32      %%;
+DEFINE SCNu32      %% __SCNu32      %%;
+DEFINE SCNx32      %% __SCNx32      %%;
+ENDIF
+IFDEF ~have_uint48_t
+DEFINE SCNo48      %% __SCNo48      %%;
+DEFINE SCNoLEAST48 %% __SCNoLEAST48 %%;
+DEFINE SCNoFAST48  %% __SCNoFAST48  %%;
+DEFINE SCNu48      %% __SCNu48      %%;
+DEFINE SCNuLEAST48 %% __SCNuLEAST48 %%;
+DEFINE SCNuFAST48  %% __SCNuFAST48  %%;
+DEFINE SCNx48      %% __SCNx48      %%;
+DEFINE SCNxLEAST48 %% __SCNxLEAST48 %%;
+DEFINE SCNxFAST48  %% __SCNxFAST48  %%;
+ENDIF
+IFDEF ~have_uint64_t
+DEFINE SCNo64      %% __SCNo64      %%;
+DEFINE SCNu64      %% __SCNu64      %%;
+DEFINE SCNx64      %% __SCNx64      %%;
+ENDIF

# 7.8 p1
+DEFINE PRIdMAX     %% __PRIdMAX     %%;
+DEFINE PRIdPTR     %% __PRIdPTR     %%;
+DEFINE PRIiMAX     %% __PRIiMAX     %%;
+DEFINE PRIiPTR     %% __PRIiPTR     %%;

# 7.8 p3
+DEFINE PRIoMAX     %% __PRIoMAX     %%;
+DEFINE PRIoPTR     %% __PRIoPTR     %%;
+DEFINE PRIuMAX     %% __PRIuMAX     %%;
+DEFINE PRIuPTR     %% __PRIuPTR     %%;
+DEFINE PRIxMAX     %% __PRIxMAX     %%;
+DEFINE PRIxPTR     %% __PRIxPTR     %%;
+DEFINE PRIXMAX     %% __PRIXMAX     %%;
+DEFINE PRIXPTR     %% __PRIXPTR     %%;

# 7.8 p4
+DEFINE SCNdMAX     %% __SCNdMAX     %%;
+DEFINE SCNdPTR     %% __SCNdPTR     %%;
+DEFINE SCNiMAX     %% __SCNiMAX     %%;
+DEFINE SCNiPTR     %% __SCNiPTR     %%;

# 7.8 p5
+DEFINE SCNoMAX     %% __SCNoMAX     %%;
+DEFINE SCNoPTR     %% __SCNoPTR     %%;
+DEFINE SCNuMAX     %% __SCNuMAX     %%;
+DEFINE SCNuPTR     %% __SCNuPTR     %%;
+DEFINE SCNxMAX     %% __SCNxMAX     %%;
+DEFINE SCNxPTR     %% __SCNxPTR     %%;

# 7.8.2.n
+FUNC intmax_t  imaxabs(intmax_t);
+FUNC imaxdiv_t imaxdiv(intmax_t, intmax_t);
+FUNC intmax_t  strtoimax(const char * restrict, char ** restrict, int);
+FUNC uintmax_t strtoumax(const char * restrict, char ** restrict, int);
+FUNC intmax_t  wcstoimax(const wchar_t * restrict, wchar_t ** restrict, int);
+FUNC uintmax_t wcstoumax(const wchar_t * restrict, wchar_t ** restrict, int);

