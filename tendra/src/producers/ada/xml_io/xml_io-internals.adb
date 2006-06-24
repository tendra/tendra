package body XML_IO.Internals is

   ---------------
   -- Get_Class --
   ---------------

   function Get_Class
     (Char : in Unicode_Character)
      return Character_Class
   is
   begin
      case Char is
         when  9
           |  10
           |  13
           |  32 =>
            return ' ';
         when  33 => return '!';
         when  34 => return '"';
         when  35 => return '#';

         when  36 .. 37
           |  40 .. 44
           |  64
           |  92
           |  94
           |  96
           |  123 .. 182
           |  184 .. 191
           |  215
           |  247
           |  306 .. 307
           |  319 .. 320
           |  329
           |  383
           |  452 .. 460
           |  497 .. 499
           |  502 .. 505
           |  536 .. 591
           |  681 .. 698
           |  706 .. 719
           |  722 .. 767
           |  838 .. 863
           |  866 .. 901
           |  907
           |  909
           |  930
           |  975
           |  983 .. 985
           |  987
           |  989
           |  991
           |  993
           |  1012 .. 1024
           |  1037
           |  1104
           |  1117
           |  1154
           |  1159 .. 1167
           |  1221 .. 1222
           |  1225 .. 1226
           |  1229 .. 1231
           |  1260 .. 1261
           |  1270 .. 1271
           |  1274 .. 1328
           |  1367 .. 1368
           |  1370 .. 1376
           |  1415 .. 1424
           |  1442
           |  1466
           |  1470
           |  1472
           |  1475
           |  1477 .. 1487
           |  1515 .. 1519
           |  1523 .. 1568
           |  1595 .. 1599
           |  1619 .. 1631
           |  1642 .. 1647
           |  1720 .. 1721
           |  1727
           |  1743
           |  1748
           |  1769
           |  1774 .. 1775
           |  1786 .. 2304
           |  2308
           |  2362 .. 2363
           |  2382 .. 2384
           |  2389 .. 2391
           |  2404 .. 2405
           |  2416 .. 2432
           |  2436
           |  2445 .. 2446
           |  2449 .. 2450
           |  2473
           |  2481
           |  2483 .. 2485
           |  2490 .. 2491
           |  2493
           |  2501 .. 2502
           |  2505 .. 2506
           |  2510 .. 2518
           |  2520 .. 2523
           |  2526
           |  2532 .. 2533
           |  2546 .. 2561
           |  2563 .. 2564
           |  2571 .. 2574
           |  2577 .. 2578
           |  2601
           |  2609
           |  2612
           |  2615
           |  2618 .. 2619
           |  2621
           |  2627 .. 2630
           |  2633 .. 2634
           |  2638 .. 2648
           |  2653
           |  2655 .. 2661
           |  2677 .. 2688
           |  2692
           |  2700
           |  2702
           |  2706
           |  2729
           |  2737
           |  2740
           |  2746 .. 2747
           |  2758
           |  2762
           |  2766 .. 2783
           |  2785 .. 2789
           |  2800 .. 2816
           |  2820
           |  2829 .. 2830
           |  2833 .. 2834
           |  2857
           |  2865
           |  2868 .. 2869
           |  2874 .. 2875
           |  2884 .. 2886
           |  2889 .. 2890
           |  2894 .. 2901
           |  2904 .. 2907
           |  2910
           |  2914 .. 2917
           |  2928 .. 2945
           |  2948
           |  2955 .. 2957
           |  2961
           |  2966 .. 2968
           |  2971
           |  2973
           |  2976 .. 2978
           |  2981 .. 2983
           |  2987 .. 2989
           |  2998
           |  3002 .. 3005
           |  3011 .. 3013
           |  3017
           |  3022 .. 3030
           |  3032 .. 3046
           |  3056 .. 3072
           |  3076
           |  3085
           |  3089
           |  3113
           |  3124
           |  3130 .. 3133
           |  3141
           |  3145
           |  3150 .. 3156
           |  3159 .. 3167
           |  3170 .. 3173
           |  3184 .. 3201
           |  3204
           |  3213
           |  3217
           |  3241
           |  3252
           |  3258 .. 3261
           |  3269
           |  3273
           |  3278 .. 3284
           |  3287 .. 3293
           |  3295
           |  3298 .. 3301
           |  3312 .. 3329
           |  3332
           |  3341
           |  3345
           |  3369
           |  3386 .. 3389
           |  3396 .. 3397
           |  3401
           |  3406 .. 3414
           |  3416 .. 3423
           |  3426 .. 3429
           |  3440 .. 3584
           |  3631
           |  3643 .. 3647
           |  3663
           |  3674 .. 3712
           |  3715
           |  3717 .. 3718
           |  3721
           |  3723 .. 3724
           |  3726 .. 3731
           |  3736
           |  3744
           |  3748
           |  3750
           |  3752 .. 3753
           |  3756
           |  3759
           |  3770
           |  3774 .. 3775
           |  3781
           |  3783
           |  3790 .. 3791
           |  3802 .. 3863
           |  3866 .. 3871
           |  3882 .. 3892
           |  3894
           |  3896
           |  3898 .. 3901
           |  3912
           |  3946 .. 3952
           |  3973
           |  3980 .. 3983
           |  3990
           |  3992
           |  4014 .. 4016
           |  4024
           |  4026 .. 4255
           |  4294 .. 4303
           |  4343 .. 4351
           |  4353
           |  4356
           |  4360
           |  4362
           |  4365
           |  4371 .. 4411
           |  4413
           |  4415
           |  4417 .. 4427
           |  4429
           |  4431
           |  4433 .. 4435
           |  4438 .. 4440
           |  4442 .. 4446
           |  4450
           |  4452
           |  4454
           |  4456
           |  4458 .. 4460
           |  4463 .. 4465
           |  4468
           |  4470 .. 4509
           |  4511 .. 4519
           |  4521 .. 4522
           |  4524 .. 4525
           |  4528 .. 4534
           |  4537
           |  4539
           |  4547 .. 4586
           |  4588 .. 4591
           |  4593 .. 4600
           |  4602 .. 7679
           |  7836 .. 7839
           |  7930 .. 7935
           |  7958 .. 7959
           |  7966 .. 7967
           |  8006 .. 8007
           |  8014 .. 8015
           |  8024
           |  8026
           |  8028
           |  8030
           |  8062 .. 8063
           |  8117
           |  8125
           |  8127 .. 8129
           |  8133
           |  8141 .. 8143
           |  8148 .. 8149
           |  8156 .. 8159
           |  8173 .. 8177
           |  8181
           |  8189 .. 8399
           |  8413 .. 8416
           |  8418 .. 8485
           |  8487 .. 8489
           |  8492 .. 8493
           |  8495 .. 8575
           |  8579 .. 12292
           |  12294
           |  12296 .. 12320
           |  12336
           |  12342 .. 12352
           |  12437 .. 12440
           |  12443 .. 12444
           |  12447 .. 12448
           |  12539
           |  12543 .. 12548
           |  12589 .. 19967
           |  40870 .. 44031
           |  55204 .. 55295
           |  57344 .. 65533
           |  65536 .. 1114111 =>
            return '$';

         when  38 => return '&';
         when  39 => return ''';
         when  45 => return '-';
         when  46
           |  183
           |  720
           |  721
           |  768 .. 837
           |  864 .. 865
           |  903
           |  1155 .. 1158
           |  1425 .. 1441
           |  1443 .. 1465
           |  1467 .. 1469
           |  1471
           |  1473 .. 1474
           |  1476
           |  1600
           |  1611 .. 1618
           |  1632 .. 1641
           |  1648
           |  1750 .. 1756
           |  1757 .. 1759
           |  1760 .. 1764
           |  1767 .. 1768
           |  1770 .. 1773
           |  1776 .. 1785
           |  2305 .. 2307
           |  2364
           |  2366 .. 2380
           |  2381
           |  2385 .. 2388
           |  2402 .. 2403
           |  2406 .. 2415
           |  2433 .. 2435
           |  2492
           |  2494
           |  2495
           |  2496 .. 2500
           |  2503 .. 2504
           |  2507 .. 2509
           |  2519
           |  2530 .. 2531
           |  2534 .. 2543
           |  2562
           |  2620
           |  2622
           |  2623
           |  2624 .. 2626
           |  2631 .. 2632
           |  2635 .. 2637
           |  2662 .. 2671
           |  2672 .. 2673
           |  2689 .. 2691
           |  2748
           |  2750 .. 2757
           |  2759 .. 2761
           |  2763 .. 2765
           |  2790 .. 2799
           |  2817 .. 2819
           |  2876
           |  2878 .. 2883
           |  2887 .. 2888
           |  2891 .. 2893
           |  2902 .. 2903
           |  2918 .. 2927
           |  2946 .. 2947
           |  3006 .. 3010
           |  3014 .. 3016
           |  3018 .. 3021
           |  3031
           |  3047 .. 3055
           |  3073 .. 3075
           |  3134 .. 3140
           |  3142 .. 3144
           |  3146 .. 3149
           |  3157 .. 3158
           |  3174 .. 3183
           |  3202 .. 3203
           |  3262 .. 3268
           |  3270 .. 3272
           |  3274 .. 3277
           |  3285 .. 3286
           |  3302 .. 3311
           |  3330 .. 3331
           |  3390 .. 3395
           |  3398 .. 3400
           |  3402 .. 3405
           |  3415
           |  3430 .. 3439
           |  3633
           |  3636 .. 3642
           |  3654
           |  3655 .. 3662
           |  3664 .. 3673
           |  3761
           |  3764 .. 3769
           |  3771 .. 3772
           |  3782
           |  3784 .. 3789
           |  3792 .. 3801
           |  3864 .. 3865
           |  3872 .. 3881
           |  3893
           |  3895
           |  3897
           |  3902
           |  3903
           |  3953 .. 3972
           |  3974 .. 3979
           |  3984 .. 3989
           |  3991
           |  3993 .. 4013
           |  4017 .. 4023
           |  4025
           |  8400 .. 8412
           |  8417
           |  12293
           |  12330 .. 12335
           |  12337 .. 12341
           |  12441
           |  12442
           |  12445 .. 12446
           |  12540 .. 12542 =>
            return '.';

         when  47 => return '/';
         when  48 .. 57 => return '0';

         when  59 => return ';';
         when  60 => return '<';
         when  61 => return '=';
         when  62 => return '>';
         when  63 => return '?';

         when  65 .. 70
           |  97 .. 102
           =>
         return 'A';

         when  58
           |  71 .. 90
           |  95
           |  103 .. 119
           |  192 .. 214
           |  216 .. 246
           |  248 .. 255
           |  256 .. 305
           |  308 .. 318
           |  321 .. 328
           |  330 .. 382
           |  384 .. 451
           |  461 .. 496
           |  500 .. 501
           |  506 .. 535
           |  592 .. 680
           |  699 .. 705
           |  902
           |  904 .. 906
           |  908
           |  910 .. 929
           |  931 .. 974
           |  976 .. 982
           |  986
           |  988
           |  990
           |  992
           |  994 .. 1011
           |  1025 .. 1036
           |  1038 .. 1103
           |  1105 .. 1116
           |  1118 .. 1153
           |  1168 .. 1220
           |  1223 .. 1224
           |  1227 .. 1228
           |  1232 .. 1259
           |  1262 .. 1269
           |  1272 .. 1273
           |  1329 .. 1366
           |  1369
           |  1377 .. 1414
           |  1488 .. 1514
           |  1520 .. 1522
           |  1569 .. 1594
           |  1601 .. 1610
           |  1649 .. 1719
           |  1722 .. 1726
           |  1728 .. 1742
           |  1744 .. 1747
           |  1749
           |  1765 .. 1766
           |  2309 .. 2361
           |  2365
           |  2392 .. 2401
           |  2437 .. 2444
           |  2447 .. 2448
           |  2451 .. 2472
           |  2474 .. 2480
           |  2482
           |  2486 .. 2489
           |  2524 .. 2525
           |  2527 .. 2529
           |  2544 .. 2545
           |  2565 .. 2570
           |  2575 .. 2576
           |  2579 .. 2600
           |  2602 .. 2608
           |  2610 .. 2611
           |  2613 .. 2614
           |  2616 .. 2617
           |  2649 .. 2652
           |  2654
           |  2674 .. 2676
           |  2693 .. 2699
           |  2701
           |  2703 .. 2705
           |  2707 .. 2728
           |  2730 .. 2736
           |  2738 .. 2739
           |  2741 .. 2745
           |  2749
           |  2784
           |  2821 .. 2828
           |  2831 .. 2832
           |  2835 .. 2856
           |  2858 .. 2864
           |  2866 .. 2867
           |  2870 .. 2873
           |  2877
           |  2908 .. 2909
           |  2911 .. 2913
           |  2949 .. 2954
           |  2958 .. 2960
           |  2962 .. 2965
           |  2969 .. 2970
           |  2972
           |  2974 .. 2975
           |  2979 .. 2980
           |  2984 .. 2986
           |  2990 .. 2997
           |  2999 .. 3001
           |  3077 .. 3084
           |  3086 .. 3088
           |  3090 .. 3112
           |  3114 .. 3123
           |  3125 .. 3129
           |  3168 .. 3169
           |  3205 .. 3212
           |  3214 .. 3216
           |  3218 .. 3240
           |  3242 .. 3251
           |  3253 .. 3257
           |  3294
           |  3296 .. 3297
           |  3333 .. 3340
           |  3342 .. 3344
           |  3346 .. 3368
           |  3370 .. 3385
           |  3424 .. 3425
           |  3585 .. 3630
           |  3632
           |  3634 .. 3635
           |  3648 .. 3653
           |  3713 .. 3714
           |  3716
           |  3719 .. 3720
           |  3722
           |  3725
           |  3732 .. 3735
           |  3737 .. 3743
           |  3745 .. 3747
           |  3749
           |  3751
           |  3754 .. 3755
           |  3757 .. 3758
           |  3760
           |  3762 .. 3763
           |  3773
           |  3776 .. 3780
           |  3904 .. 3911
           |  3913 .. 3945
           |  4256 .. 4293
           |  4304 .. 4342
           |  4352
           |  4354 .. 4355
           |  4357 .. 4359
           |  4361
           |  4363 .. 4364
           |  4366 .. 4370
           |  4412
           |  4414
           |  4416
           |  4428
           |  4430
           |  4432
           |  4436 .. 4437
           |  4441
           |  4447 .. 4449
           |  4451
           |  4453
           |  4455
           |  4457
           |  4461 .. 4462
           |  4466 .. 4467
           |  4469
           |  4510
           |  4520
           |  4523
           |  4526 .. 4527
           |  4535 .. 4536
           |  4538
           |  4540 .. 4546
           |  4587
           |  4592
           |  4601
           |  7680 .. 7835
           |  7840 .. 7929
           |  7936 .. 7957
           |  7960 .. 7965
           |  7968 .. 8005
           |  8008 .. 8013
           |  8016 .. 8023
           |  8025
           |  8027
           |  8029
           |  8031 .. 8061
           |  8064 .. 8116
           |  8118 .. 8124
           |  8126
           |  8130 .. 8132
           |  8134 .. 8140
           |  8144 .. 8147
           |  8150 .. 8155
           |  8160 .. 8172
           |  8178 .. 8180
           |  8182 .. 8188
           |  8486
           |  8490 .. 8491
           |  8494
           |  8576 .. 8578
           |  12295
           |  12321 .. 12329
           |  12353 .. 12436
           |  12449 .. 12538
           |  12549 .. 12588
           |  19968 .. 40869
           |  44032 .. 55203 =>
            return 'X';

         when  91 => return '[';
         when  93 => return ']';

         when  120 => return 'x';

         when  121 .. 122 => return 'z';
         when others =>
            return Bad_Character;
      end case;
   end Get_Class;

   --------------------
   -- Implementation --
   --------------------

   package body Implementation is

      procedure Invalidate
        (Buffer : in     XML_String;
         State  : in out Reader_State'Class;
         From   : in     Positive;
         To     : in     Positive);

      procedure Invalidate
        (Value  : in out Token_Value;
         Buffer : in     XML_String;
         From   : in     Positive;
         To     : in     Positive);

      procedure Next_Class
        (Buffer : in out XML_String;
         Parser : in out Reader'Class;
         Result :    out Character_Class);

      procedure Next_Token
        (Buffer : in out XML_String;
         Parser : in out Reader'Class);

      Xml_Literal          : constant XML_Unbounded :=
        To_XML_String ("xml");
      Doctype_Literal      : constant XML_Unbounded :=
        To_XML_String ("DOCTYPE");
      Cdata_Literal        : constant XML_Unbounded :=
        To_XML_String ("CDATA");
      Version_Literal      : constant XML_Unbounded :=
        To_XML_String ("version");
      Encoding_Literal     : constant XML_Unbounded :=
        To_XML_String ("encoding");
      Standalone_Literal   : constant XML_Unbounded :=
        To_XML_String ("standalone");
      Yes_Literal          : constant XML_Unbounded :=
        To_XML_String ("yes");
      No_Literal           : constant XML_Unbounded :=
        To_XML_String ("no");
      One_Dot_Zero_Literal : constant XML_Unbounded :=
        To_XML_String ("1.0");
      Lt_Literal           : constant XML_Unbounded :=
        To_XML_String ("&lt;");
      Gt_Literal           : constant XML_Unbounded :=
        To_XML_String ("&gt;");
      Amp_Literal          : constant XML_Unbounded :=
        To_XML_String ("&amp;");

      Empty : constant Token_Value :=
        (0, 0, To_Unbounded_String (Nil_Literal));

      ---------------------
      -- Attribute_Count --
      ---------------------

      function Attribute_Count (Parser : in Reader) return List_Count is
      begin
         return Parser.The.Piece.Count;
      end Attribute_Count;

      --------------------
      -- Attribute_Name --
      --------------------

      function Attribute_Name
        (Parser : in Reader;
         Index  : in List_Index)
         return Token_Value
      is
      begin
         if Index > Parser.The.Piece.Count then
            raise Constraint_Error;
         elsif Index <= Embeded_Attr then
            return Parser.The.Piece.Names (Index);
         else
            return Parser.The.Extra_Names (Index);
         end if;
      end Attribute_Name;

      ---------------------
      -- Attribute_Value --
      ---------------------

      function Attribute_Value
        (Parser : in Reader;
         Index  : in List_Index)
         return Token_Value
      is
      begin
         if Index > Parser.The.Piece.Count then
            raise Constraint_Error;
         elsif Index <= Embeded_Attr then
            return Parser.The.Piece.Values (Index);
         else
            return Parser.The.Extra_Values (Index);
         end if;
      end Attribute_Value;

      --------------
      -- Encoding --
      --------------

      function Encoding (Parser : in Reader) return Token_Value is
      begin
         return Parser.The.Piece.Encoding;
      end Encoding;

      --------------
      -- Encoding --
      --------------

      function Encoding (Parser : in Reader) return Encodings.Encoding is
      begin
         return Parser.The.Input.Encoding;
      end Encoding;

      ----------------
      -- Initialize --
      ----------------

      procedure Initialize
        (Buffer : in out XML_String;
         Parser : in out Reader)
      is
      begin
         Parser.The.Input.Encoding := Encodings.UTF_8;
         Parser.The.Input.Index := Buffer'First;
         Parser.The.Input.Free  := Buffer'First;
         Parser.The.Token.Prev  := End_Of_Buffer;
         Parser.The.Token.X     := 0;
         Parser.The.In_State    := In_Misc;
         Parser.The.Deep        := 0;
         Next (Buffer, Parser);
      end Initialize;

      ----------------
      -- Invalidate --
      ----------------

      procedure Invalidate
        (Value  : in out Token_Value;
         Buffer : in     XML_String;
         From   : in     Positive;
         To     : in     Positive) is
      begin
         if Value.From in From .. To then
            if Value.To in From .. To then
               Value.Stored := Value.Stored
                 & Buffer (Value.From .. Value.To);
               Value.From   := 0;
            else
               Value.Stored := Value.Stored & Buffer (Value.From .. To);

               if To = Buffer'Last then
                  Value.From := Buffer'First;
               else
                  Value.From := To + 1;
               end if;
            end if;
         end if;
      end Invalidate;

      ----------------
      -- Invalidate --
      ----------------

      procedure Invalidate
        (Buffer : in     XML_String;
         State  : in out Reader_State'Class;
         From   : in     Positive;
         To     : in     Positive)
      is
         procedure Invalidate
           (Value  : in out Token_Value) is
         begin
            Invalidate (Value, Buffer, From, To);
         end Invalidate;
      begin
         Invalidate (State.Token.Value);
         Invalidate (State.Token.Amp);

         case State.Piece.Kind is
            when Start_Document =>
               Invalidate (State.Piece.Encoding);

            when Start_Element
              | Entity_Reference
              | End_Element
              | Processing_Instruction
              | Attribute
              | Namespace
              =>
               Invalidate (State.Piece.Name);

               case State.Piece.Kind is
                  when Start_Element =>
                     for I in 1 .. State.Piece.Count loop
                        if I <= Embeded_Attr then
                           Invalidate (State.Piece.Names (I));
                           Invalidate (State.Piece.Values (I));
                        else
                           Invalidate (State.Extra_Names (I));
                           Invalidate (State.Extra_Values (I));
                        end if;
                     end loop;

                  when Processing_Instruction =>
                     Invalidate (State.Piece.PI_Text);

                  when Attribute | Namespace =>
                     Invalidate (State.Piece.Value);

                  when others =>
                     null;
               end case;

            when Comment | Characters | CDATA_Section =>
               Invalidate (State.Piece.Text);

            when DTD | End_Document =>
               null;
         end case;
      end Invalidate;

      -----------------
      -- More_Pieces --
      -----------------

      function More_Pieces (Parser : in Reader) return Boolean is
      begin
         return Parser.The.Piece.Kind /= End_Document;
      end More_Pieces;

      ----------
      -- Name --
      ----------

      function Name (Parser : in Reader) return Token_Value is
      begin
         return Parser.The.Piece.Name;
      end Name;

      ----------
      -- Next --
      ----------

      procedure Next
        (Buffer : in out XML_String;
         Parser : in out Reader)
      is
         use type XML_String;

         procedure Error is
            X : exception;
         begin
            raise X;
         end Error;

         procedure Check_Token (Next : Token) is
         begin
            if Parser.The.Token.Kind /= Next then
               Error;
            end if;
         end Check_Token;

         function Val return Xml_String is
         begin
            return Value (Buffer, Parser.The.Token.Value);
         end Val;

         function Token_Kind return Token is
         begin
            return Parser.The.Token.Kind;
         end Token_Kind;

         procedure Skip_Space is
         begin
            if Token_Kind = Space_Token then
               --  Allow_XML_Decl := False;
               Next_Token (Buffer, Parser);
            end if;
         end Skip_Space;

         procedure Do_Eq_Value is
         begin
            Next_Token (Buffer, Parser);
            Skip_Space;
            Check_Token (Eq_Token);
            Next_Token (Buffer, Parser);
            Skip_Space;

            if Token_Kind = Apostrophe_Token then
               Parser.The.In_State := In_Apostrophes;
            elsif Token_Kind = Quote_Token then
               Parser.The.In_State := In_Quotes;
            else
               Error;
            end if;

            Next_Token (Buffer, Parser);
            Check_Token (Value_Token);
            Parser.The.In_State := In_Element;
         end Do_Eq_Value;

         procedure Do_Pi is
            Prev_State : constant Internal_State := Parser.The.In_State;
         begin
            Parser.The.In_State := In_Element;
            Next_Token (Buffer, Parser);
            Check_Token (Name_Token);

            if Val = Xml_Literal then
               Parser.The.Piece := (Kind       => Start_Document,
                                    Standalone => True,
                                    Encoding   => Empty);

               Next_Token (Buffer, Parser);
               Skip_Space;
               Check_Token (Name_Token);

               if Val = Version_Literal then
                  Do_Eq_Value;

                  if Val = One_Dot_Zero_Literal then
                     Next_Token (Buffer, Parser);
                     Skip_Space;
                  else
                     Error;
                  end if;
               else
                  Error;
               end if;

               if Token_Kind = Name_Token and then Val = Encoding_Literal then
                  Do_Eq_Value;
                  Parser.The.Piece.Encoding := Parser.The.Token.Value;
                  Parser.The.Input.Encoding := To_Encoding (Val);
                  Next_Token (Buffer, Parser);
                  Skip_Space;
               end if;

               if Token_Kind = Name_Token and then Val = Standalone_Literal
               then
                  Do_Eq_Value;

                  if Val = Yes_Literal then
                     Parser.The.Piece.Standalone := True;
                  elsif Val = No_Literal then
                     Parser.The.Piece.Standalone := False;
                  else
                     Error;
                  end if;

                  Next_Token (Buffer, Parser);
                  Skip_Space;
               end if;

               Check_Token (PI_End_Token);
            else
               Parser.The.Piece := (Kind    => Processing_Instruction,
                                    Name    => Parser.The.Token.Value,
                                    PI_Text => Empty);

               Next_Token (Buffer, Parser);
               Parser.The.In_State := In_PI;
               Skip_Space;

               case Token_Kind is
                  when PI_End_Token =>
                     null;
                  when PI_Text_Token =>
                     Parser.The.Piece.PI_Text := Parser.The.Token.Value;
                  when others =>
                     Error;
               end case;
            end if;

            Parser.The.In_State := Prev_State;
         end Do_Pi;

         procedure Do_Comment is
            Prev_State : constant Internal_State := Parser.The.In_State;
         begin
            Parser.The.In_State := In_Comment;
            Next_Token (Buffer, Parser);
            Check_Token (Comment_Text_Token);
            Parser.The.Piece := (Kind    => Comment,
                                 Text    => Parser.The.Token.Value);
            Parser.The.In_State := Prev_State;
         end Do_Comment;

         procedure Do_Element is
            Count : List_Count := 0;
         begin
            Parser.The.In_State := In_Element;
            Next_Token (Buffer, Parser);
            Check_Token (Name_Token);

            Parser.The.Piece := (Kind    => Start_Element,
                                 Name    => Parser.The.Token.Value,
                                 Count   => Count,
                                 Names   => (others => Empty),
                                 Values  => (others => Empty));


            Next_Token (Buffer, Parser);
            Skip_Space;

            while Token_Kind = Name_Token loop
               Count := Count + 1;
               Parser.The.Piece.Count := Count;
               Parser.The.Piece.Names (Count) := Parser.The.Token.Value;
               Do_Eq_Value;
               Parser.The.Piece.Values (Count) := Parser.The.Token.Value;
               Next_Token (Buffer, Parser);
               Skip_Space;
            end loop;

            if Token_Kind = End_Token then
               Parser.The.Deep := Parser.The.Deep + 1;
               Parser.The.In_State := In_Content;
            elsif Token_Kind = Empty_End_Token then
               Parser.The.In_State := In_Empty_Element;
            else
               Error;
            end if;
         end Do_Element;

         procedure Do_Document_Def is
         begin
            Parser.The.In_State := In_Element;

            while Token_Kind /= End_Token loop
               Next_Token (Buffer, Parser);
            end loop;

            Parser.The.In_State := In_Misc;
            Parser.The.Piece    := (Kind    => DTD);
         end Do_Document_Def;

         procedure Do_Misc is
         begin
            Skip_Space;

            case Token_Kind is
               when PI_Token =>
                  Do_Pi;
               when Comment_Token =>
                  Do_Comment;
               when Start_Token =>
                  Do_Element;
               when Doctype_Token =>
                  Do_Document_Def;
               when End_Of_Buffer =>
                  Parser.The.Piece := (Kind    => End_Document);
               when others =>
                  Error;
            end case;
         end Do_Misc;

         procedure Do_End_Element is
         begin
            Parser.The.In_State := In_Element;
            Next_Token (Buffer, Parser);
            Check_Token (Name_Token);

            Parser.The.Piece := (Kind    => End_Element,
                                 Name    => Parser.The.Token.Value);

            Next_Token (Buffer, Parser);
            Skip_Space;
            Check_Token (End_Token);

            if Parser.The.Deep = 0 then
               Parser.The.In_State := In_Misc;
            else
               Parser.The.In_State := In_Content;
            end if;
         end Do_End_Element;

         procedure Do_CData is
         begin
            Parser.The.In_State := In_Element;
            Next_Token (Buffer, Parser);
            Check_Token (Name_Token);

            if Val /= Cdata_Literal then
               Error;
            end if;

            Parser.The.In_State := In_CD_Start;
            Next_Token (Buffer, Parser);
            Check_Token (Square_Token);

            Parser.The.In_State := In_CD;
            Next_Token (Buffer, Parser);
            Check_Token (CData_Token);

            Parser.The.Piece := (CDATA_Section, Parser.The.Token.Value);
            Parser.The.In_State := In_Content;
         end Do_CData;

         procedure Do_Content is
         begin
            case Token_Kind is
               when PI_Token =>
                  Do_Pi;
               when Comment_Token =>
                  Do_Comment;
               when Start_Token =>
                  Do_Element;
               when End_Of_Buffer =>
                  Parser.The.Piece := (Kind    => End_Document);
               when Char_Data_Token =>
                  Parser.The.Piece := (Characters, Parser.The.Token.Value);
               when Entity_Reference_Token =>
                  Parser.The.Piece := (Entity_Reference,
                                       Parser.The.Token.Value);
               when Char_Reference_Token =>
                  Parser.The.Piece := (Characters, Parser.The.Token.Value);
               when CD_Start_Token =>
                  Do_CData;
               when End_Element_Token =>
                  Do_End_Element;
               when others =>
                  Error;
            end case;
         end Do_Content;

      begin
         if Parser.The.In_State = In_Empty_Element then
            Parser.The.Piece := (Kind    => End_Element,
                                 Name    => Parser.The.Piece.Name);

            if Parser.The.Deep = 0 then
               Parser.The.In_State := In_Misc;
            else
               Parser.The.In_State := In_Content;
            end if;

            return;
         end if;

         Next_Token (Buffer, Parser);

         case Parser.The.In_State is
            when In_Misc =>
               Do_Misc;
            when In_Content =>
               Do_Content;
            when others =>
               Error;
         end case;
      end Next;

      ----------------
      -- Next_Class --
      ----------------

      procedure Next_Class
        (Buffer : in out XML_String;
         Parser : in out Reader'Class;
         Result :    out Character_Class)
      is
         use type Unicode_Character;

         Index  : Positive renames Parser.The.Input.Index;
         Free   : Positive renames Parser.The.Input.Free;
         Char   : Unicode_Character;
      begin
         loop
            if Index /= Free then
               Parser.The.Input.Prev := Index;
               Decode (Buffer, Index, Free,
                       Encoding => Parser.The.Input.Encoding,
                       Char     => Char);
            else
               Char := Invalid_Character;
            end if;

            if Char /= Invalid_Character then
               Result := Get_Class (Char);

               return;
            end if;

            Read_Some_Data :
               declare
                  Half : constant Positive := (Buffer'First + Buffer'Last) / 2;
                  Next : Positive;
               begin
                  if Free <= Half then
                     if Free = 1 then
                        Invalidate (Buffer, Parser.The, Free, Half);
                     end if;

                     Read (Parser, Buffer (Free .. Half), Next);
                  else
                     if Free = Half + 1 then
                        Invalidate (Buffer, Parser.The, Free, Buffer'Last);
                     end if;

                     Read (Parser, Buffer (Free .. Buffer'Last), Next);
                  end if;

                  if Next < Free then
                     Result := End_Of_Buffer;

                     return;
                  elsif Next = Buffer'Last then
                     Free := Buffer'First;
                  else
                     Free := Next + 1;
                  end if;
               end Read_Some_Data;
         end loop;
      end Next_Class;

      ----------------
      -- Next_Token --
      ----------------

      procedure Next_Token
        (Buffer : in out XML_String;
         Parser : in out Reader'Class)
      is
         procedure Start_Token is
         begin
            Parser.The.Token.Value      := Empty;
            Parser.The.Token.Value.From := Parser.The.Input.Prev;
         end Start_Token;

         procedure End_Token (Back : Integer) is
         begin
            --  Actualy Back is in XML_Characters not in Characters. FIXME
            if Parser.The.Input.Prev + Back < Buffer'First then
               Parser.The.Token.Value.To :=
                 Buffer'Last + Parser.The.Input.Prev + Back;
            else
               Parser.The.Token.Value.To := Parser.The.Input.Prev + Back;
            end if;
         end End_Token;

         procedure On_Reference is
            function Value return XML_Unbounded is
               Val : constant XML_String :=
                 Value (Buffer, Parser.The.Token.Value);
            begin
               if Val = Lt_Literal then
                  return To_XML_String ("<");
               elsif Val = Gt_Literal then
                  return To_XML_String (">");
               elsif Val = Amp_Literal then
                  return To_XML_String ("&");
               else
                  return To_Unbounded_String (Val);
               end if;
            end Value;
         begin
            Invalidate
              (Parser.The.Token.Amp, Buffer, Buffer'First, Buffer'Last);
            Parser.The.Token.Value.Stored := Parser.The.Token.Amp.Stored
              & Value;
            Parser.The.Token.Value.From   := Parser.The.Input.Index;
            Parser.The.Token.Value.To     := 0;
            Parser.The.Token.Amp.From     := 0;
         end On_Reference;

         Char   : Character_Class;
         Data   : Tokenizer_State renames Parser.The.Token;
      begin
         loop
            if Data.Prev = End_Of_Buffer then
               Next_Class (Buffer, Parser, Char);

               if Char = End_Of_Buffer then
                  Data.Kind := End_Of_Buffer;
                  return;
               end if;
            else
               Char      := Data.Prev;
               Data.Prev := End_Of_Buffer;
            end if;

            case Parser.The.In_State is
               when In_Empty_Element =>
                  Data.Kind := Error;
                  exit;

               when In_Misc =>
                  case Data.X is
                     when 0 =>
                        case Char is
                           when ' ' =>
                              Data.X := 1;
                           when '<' =>
                              Data.X := 2;
                           when others =>
                              Data.Kind := Error;
                              exit;
                        end case;

                     when 1 =>  --  ' '
                        if Char /= ' ' then
                           Data.Prev := Char;
                           Data.Kind := Space_Token;
                           exit;
                        end if;

                     when 2 =>  --  '<'
                        case Char is
                           when '?' =>
                              Data.Kind := PI_Token;
                              exit;
                           when '!' =>
                              Data.X := 3;
                           when others =>
                              Data.Prev := Char;
                              Data.Kind := Start_Token;
                              exit;
                        end case;

                     when 3 =>  --  '<!'
                        case Char is
                           when '-' =>
                              Data.X := 4;
                           when others =>
                              Data.Prev := Char;
                              Data.Kind := Doctype_Token;
                              exit;
                        end case;

                     when 4 =>  --  '<!-'
                        if Char = '-' then
                           Data.Kind := Comment_Token;
                           exit;
                        else
                           Data.Kind := Error;
                           exit;
                        end if;

                     when others =>
                        Data.Kind := Error;
                        exit;
                  end case;

               when In_Element =>
                  case Data.X is
                     when 0 =>
                        case Char is
                           when ' ' =>
                              Data.X := 1;
                           when '=' =>
                              Data.Kind := Eq_Token;
                              exit;
                           when ''' =>
                              Data.Kind := Apostrophe_Token;
                              exit;
                           when '"' =>
                              Data.Kind := Quote_Token;
                              exit;
                           when '?' =>
                              Data.X := 2;
                           when '/' =>
                              Data.X := 4;
                           when '>' =>
                              Data.Kind := End_Token;
                              exit;
                           when 'A' | 'X' | 'x' | 'z' =>
                              Start_Token;
                              Data.X := 3;
                           when others =>
                              Data.Kind := Error;
                              exit;
                        end case;

                     when 1 =>  --  ' '
                        if Char /= ' ' then
                           Data.Prev := Char;
                           Data.Kind := Space_Token;
                           exit;
                        end if;

                     when 2 =>  --  '?'
                        if Char = '>' then
                            Data.Kind := PI_End_Token;
                            exit;
                        else
                           Data.Kind := Error;
                           exit;
                        end if;

                     when 3 =>  --  'X'
                        case Char is
                           when 'A' | 'X' | 'x' | 'z' | '0' | '.' | '-' =>
                              null;
                           when others =>
                              Data.Prev := Char;
                              Data.Kind := Name_Token;
                              End_Token (-1);
                              exit;
                        end case;

                     when 4 =>  --  '/'
                        if Char = '>' then
                           Data.Kind := Empty_End_Token;
                           exit;
                        else
                           Data.Kind := Error;
                           exit;
                        end if;

                     when others =>
                        Data.Kind := Error;
                        exit;
                  end case;

               when In_PI =>
                  case Data.X is
                     when 0 =>
                        Start_Token;

                        case Char is
                           when '?' =>
                              Data.X := 1;
                           when others =>
                              Data.X := 2;
                        end case;

                     when 1 =>  --  '?'
                        if Char = '>' then
                           Data.Kind := PI_End_Token;
                           End_Token (-2);
                           exit;
                        else
                           Data.X := 2;
                        end if;

                     when 2 =>  --  ...[^?]
                        if Char = '?' then
                           Data.X := 3;
                        end if;

                     when 3 =>  --  ...?
                        if Char = '>' then
                           Data.Kind := PI_Text_Token;
                           End_Token (-2);
                           exit;
                        else
                           Data.X := 2;
                        end if;

                     when others =>
                        Data.Kind := Error;
                        exit;
                  end case;

               when In_Content =>
                  case Data.X is
                     when 0 =>
                        case Char is
                           when '<' =>
                              Data.X := 1;
                           when '&' =>
                              Start_Token;
                              Data.X := 4;
                           when ']' =>
                              Data.X := 11;
                           when others =>
                              Start_Token;
                              Data.X := 10;
                        end case;

                     when 1 =>  --  '<'
                        case Char is
                           when '?' =>
                              Data.Kind := PI_Token;
                              exit;
                           when '/' =>
                              Data.Kind := End_Element_Token;
                              exit;
                           when '!' =>
                              Data.X := 2;
                           when others =>
                              Data.Prev := Char;
                              Data.Kind := Start_Token;
                              exit;
                        end case;

                     when 2 =>  --  '<!'
                        case Char is
                           when '-' =>
                              Data.X := 3;
                           when '[' =>
                              Data.Kind := CD_Start_Token;
                              exit;
                           when others =>
                              Data.Prev := Char;
                              Data.Kind := Doctype_Token;
                              exit;
                        end case;

                     when 3 =>  --  '<!-'
                        if Char = '-' then
                           Data.Kind := Comment_Token;
                           exit;
                        else
                           Data.Kind := Error;
                           exit;
                        end if;

                     when 4 =>  --  '&'
                        case Char is
                           when '#' =>
                              Data.X := 5;
                           when 'A' | 'X' | 'x' | 'z'  =>
                              Data.X := 9;
                              Start_Token;
                           when others =>
                              Data.Kind := Error;
                              End_Token (0);
                              exit;
                        end case;

                     when 5 =>  --  '&#'
                        case Char is
                           when '0' =>
                              Data.X := 6;
                           when 'x' =>
                              Data.X := 7;
                           when others =>
                              Data.Kind := Error;
                              exit;
                        end case;

                     when 6 =>  --  '&#[0-9]+'
                        case Char is
                           when '0' =>
                              null;
                           when ';' =>
                              Data.Kind := Char_Reference_Token;
                              End_Token (0);
                              exit;
                           when others =>
                              Data.Kind := Error;
                              End_Token (0);
                              exit;
                        end case;

                     when 7 =>  --  '&#x'
                        case Char is
                           when '0' | 'A' =>
                              Data.X := 8;
                           when others =>
                              Data.Kind := Error;
                              exit;
                        end case;

                     when 8 =>  --  '&#[0-9A-Fa-f]+'
                        case Char is
                           when '0' | 'A' =>
                              null;
                           when ';' =>
                              Data.Kind := Char_Reference_Token;
                              End_Token (0);
                              exit;
                           when others =>
                              Data.Kind := Error;
                              End_Token (0);
                              exit;
                        end case;

                     when 9 =>  --  &X+
                        case Char is
                           when 'A' | 'X' | 'x' | 'z' | '0' | '.' | '-' =>
                              null;
                           when ';' =>
                              Data.Kind := Entity_Reference_Token;
                              End_Token (-1);
                              exit;
                           when others =>
                              Data.Kind := Error;
                              End_Token (0);
                              exit;
                        end case;

                     when 10 =>  --  ^]
                        case Char is
                           when ']'  =>
                              Data.X := 11;
                           when '<' | '&' =>
                              Data.Prev := Char;
                              Data.Kind := Char_Data_Token;
                              End_Token (-1);
                              exit;
                           when others =>
                              null;
                        end case;

                     when 11 =>  --  .]
                        case Char is
                           when ']'  =>
                              Data.X := 12;
                           when '<' | '&' =>
                              Data.Prev := Char;
                              Data.Kind := Char_Data_Token;
                              End_Token (-1);
                              exit;
                           when others =>
                              Data.X := 10;
                        end case;

                     when 12 =>  --  .]]
                        case Char is
                           when ']'  =>
                              null;
                           when '<' | '&' =>
                              Data.Prev := Char;
                              Data.Kind := Char_Data_Token;
                              End_Token (-3);
                              exit;
                           when '>' =>
                              Data.Kind := Error;
                              End_Token (0);
                              exit;
                           when others =>
                              Data.X := 10;
                        end case;

                     when others =>
                        Data.Kind := Error;
                        exit;
                  end case;

               when In_Comment =>
                  case Data.X is
                     when 0 =>
                        Start_Token;

                        case Char is
                           when '-' =>
                              Data.X := 1;
                           when others =>
                              Data.X := 3;
                        end case;

                     when 1 =>  --  -
                        case Char is
                           when '-' =>
                              Data.X := 2;
                           when others =>
                              Data.X := 3;
                        end case;

                     when 2 =>  --  --
                        case Char is
                           when '>' =>
                              Data.Kind := Comment_Text_Token;
                              End_Token (-3);
                              exit;
                           when others =>
                              End_Token (0);
                              Data.Kind := Error;
                              exit;
                        end case;

                     when 3 =>
                        case Char is
                           when '-'=>
                              Data.X := 1;
                           when others =>
                              null;
                        end case;

                     when others =>
                        Data.Kind := Error;
                        exit;
                  end case;

               when In_CD_Start =>
                  if Char = '[' then
                     Data.Kind := Square_Token;
                     exit;
                  else
                     Data.Kind := Error;
                     exit;
                  end if;

               when In_CD =>
                  case Data.X is
                     when 0 =>
                        Start_Token;

                        case Char is
                           when ']' =>
                              Data.X := 1;
                           when others =>
                              Data.X := 3;
                        end case;

                     when 1 =>  --  .]
                        case Char is
                           when ']'  =>
                              Data.X := 2;
                           when others =>
                              Data.X := 3;
                        end case;

                     when 2 =>  --  .]]
                        case Char is
                           when ']'  =>
                              null;
                           when '>' =>
                              Data.Kind := CData_Token;
                              End_Token (-3);
                              exit;
                           when others =>
                              Data.X := 3;
                        end case;

                     when 3 =>
                        case Char is
                           when ']' =>
                              Data.X := 1;
                           when others =>
                              null;
                        end case;

                     when others =>
                        Data.Kind := Error;
                        exit;
                  end case;

               when In_Apostrophes | In_Quotes =>
                  case Data.X is
                     when 0 =>
                        Start_Token;

                        case Char is
                           when '<' =>
                              Data.Kind := Error;
                              End_Token (0);
                              exit;
                           when '&' =>
                              End_Token (-1);
                              Parser.The.Token.Amp := Parser.The.Token.Value;
                              Start_Token;
                              Data.X := 4;
                           when ''' =>
                              if Parser.The.In_State = In_Apostrophes then
                                 Data.Kind := Value_Token;
                                 End_Token (-1);
                                 exit;
                              else
                                 Data.X := 1;
                              end if;
                           when '"' =>
                              if Parser.The.In_State = In_Quotes then
                                 Data.Kind := Value_Token;
                                 End_Token (-1);
                                 exit;
                              else
                                 Data.X := 1;
                              end if;
                           when others =>
                              Data.X := 1;
                        end case;

                     when 1 =>
                        case Char is
                           when '<' =>
                              Data.Kind := Error;
                              End_Token (0);
                              exit;
                           when '&' =>
                              End_Token (-1);
                              Parser.The.Token.Amp := Parser.The.Token.Value;
                              Start_Token;
                              Data.X := 4;
                           when ''' =>
                              if Parser.The.In_State = In_Apostrophes then
                                 Data.Kind := Value_Token;
                                 End_Token (-1);
                                 exit;
                              end if;
                           when '"' =>
                              if Parser.The.In_State = In_Quotes then
                                 Data.Kind := Value_Token;
                                 End_Token (-1);
                                 exit;
                              end if;
                           when others =>
                              null;
                        end case;

                     when 4 =>  --  '&'
                        case Char is
                           when '#' =>
                              Data.X := 5;
                           when 'A' | 'X' | 'x' | 'z'  =>
                              Data.X := 9;
                           when others =>
                              Data.Kind := Error;
                              End_Token (0);
                              exit;
                        end case;

                     when 5 =>  --  '&#'
                        case Char is
                           when '0' =>
                              Data.X := 6;
                           when 'x' =>
                              Data.X := 7;
                           when others =>
                              Data.Kind := Error;
                              End_Token (0);
                              exit;
                        end case;

                     when 6 =>  --  '&#[0-9]+'
                        case Char is
                           when '0' =>
                              null;
                           when ';' =>
                              End_Token (0);
                              On_Reference;
                              Data.X := 1;
                           when others =>
                              Data.Kind := Error;
                              End_Token (0);
                              exit;
                        end case;

                     when 7 =>  --  '&#x'
                        case Char is
                           when '0' | 'A' =>
                              Data.X := 8;
                           when others =>
                              Data.Kind := Error;
                              End_Token (0);
                              exit;
                        end case;

                     when 8 =>  --  '&#[0-9A-Fa-f]+'
                        case Char is
                           when '0' | 'A' =>
                              null;
                           when ';' =>
                              End_Token (0);
                              On_Reference;
                              Data.X := 1;
                           when others =>
                              Data.Kind := Error;
                              End_Token (0);
                              exit;
                        end case;

                     when 9 =>  --  &X+
                        case Char is
                           when 'A' | 'X' | 'x' | 'z' | '0' | '.' | '-' =>
                              null;
                           when ';' =>
                              End_Token (0);
                              On_Reference;
                              Data.X := 1;
                           when others =>
                              Data.Kind := Error;
                              End_Token (0);
                              exit;
                        end case;

                     when others =>
                        Data.Kind := Error;
                        exit;
                  end case;

            end case;
         end loop;

         Data.X := 0;
      end Next_Token;

      ----------------
      -- Piece_Kind --
      ----------------

      function Piece_Kind (Parser : in Reader) return Piece_Kinds is
      begin
         return Parser.The.Piece.Kind;
      end Piece_Kind;

      ----------------
      -- Standalone --
      ----------------

      function Standalone (Parser : in Reader) return Boolean is
      begin
         return Parser.The.Piece.Standalone;
      end Standalone;

      ----------
      -- Text --
      ----------

      function Text (Parser : in Reader) return Token_Value is
      begin
         if Parser.The.Piece.Kind = Processing_Instruction then
            return Parser.The.Piece.PI_Text;
         else
            return Parser.The.Piece.Text;
         end if;
      end Text;

      -----------
      -- Value --
      -----------

      function Value
        (Buffer : in XML_String;
         Data   : in Token_Value)
         return XML_String
      is
         use type XML_String;
      begin
         if Data.From = 0 then
            return To_String (Data.Stored);
         elsif Nil_Literal /= Data.Stored then
            return To_String (Data.Stored & Buffer (Data.From .. Data.To));
         elsif Data.From > Data.To then
            return Buffer (Data.From .. Buffer'Last)
              & Buffer (Buffer'First .. Data.To);
         else
            return Buffer (Data.From .. Data.To);
         end if;
      end Value;

   end Implementation;

end XML_IO.Internals;

