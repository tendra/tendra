/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/* 	ibinasm.h,v 1.2 1995/05/23 10:56:37 john Exp	 */
/*
  ibinasm.h
  
  This file provides information required for the alpha 
  binary assembler format.
*/

/*
ibinasm.h,v
 * Revision 1.2  1995/05/23  10:56:37  john
 * Reformatting
 *
 * Revision 1.1.1.1  1995/03/23  10:39:32  john
 * Entered into CVS
 *
 * Revision 1.4  1995/03/23  10:05:09  john
 * Added guard
 *
*/

#ifndef IBINASM_H
#define IBINASM_H

enum registers {
	xr0,	xr1,	xr2,	xr3,	xr4,	xr5,	xr6,	xr7,
	xr8,	xr9,	xr10,	xr11,	xr12,	xr13,	xr14,	xr15,
	xr16,	xr17,	xr18,	xr19,	xr20,	xr21,	xr22,	xr23,
	xr24,	xr25,	xr26,	xr27,	xr28,	xr29,	xr30,	xr31,
	xfr0,	xfr1,	xfr2,	xfr3,	xfr4,	xfr5,	xfr6,	xfr7,
	xfr8,	xfr9,	xfr10,	xfr11,	xfr12,	xfr13,	xfr14,	xfr15,
	xfr16,	xfr17,	xfr18,	xfr19,	xfr20,	xfr21,	xfr22,	xfr23,
	xfr24,	xfr25,	xfr26,	xfr27,	xfr28,	xfr29,	xfr30,	xfr31,
	xnoreg
	};

typedef unsigned asmopcode;
typedef unsigned asmformat;
typedef int asmreg;
typedef int asmint;
typedef unsigned asmuint;
typedef int asmlabel;
typedef int asmsym;

#define zero 0
#define float_register 32
/*#define xnoreg 64*/

#if 1
#define ilabel		0
/*#define isym		1*/
#define iglobal		2
#define iabort		3
#define ialign		4
#define iascii		5
#define iasciiz		6
#define ibyte		7
#define icomm		8
#define ilcomm		9
#define idata		10
#define idfloat		11
#define iffloat		12
#define igfloat		13
#define isfloat		14
#define itfloat		15
#define igprel32	16
#define ifile		17
#define ilong		18
/*#define iline		19*/
#define idead		20
#define inop		21
#define iweakext	22
#define iloopno		23
#define ispace		24
#define itext		25
#define iword		26
#define iocode		27
#define iend		28
#define isdata		29
#define irdata		30
#define ient		31
#define iloc		32
#define ibgnb		33
#define iendb		34
#define iasm0		35
#define iset		36
#define iorg		37
#define irep		38
#define iendrep		39
#define ilab		40
#define ivreg		41
#define imask		42
#define ifmask		43
#define ierr		44
#define iglobabs	45
#define iverstamp	46
#define iframe		47
#define iextended	48
#define iextern		49
#define iaent		50
#define ioption		51
#define inoalias	52
#define ialias		53
#define ilivereg	54
#define igjsrsaved	55
#define igjsrlive 	56
#define igjmplive 	57
#define irestext	58
#define iquad		59
#define iprologue 	60
#define iedata		61
#define imtag		62
#define imalias		63
#define ieflag		64
#define isave_ra	65
#define iconst		66
#define iugen		67
#define iident      68
#define irconst     69
#else 
#define ilabel		 0
/*#define isym		 1*/
#define iglobal		 2
#define iabort		 3
#define ialign		 4
#define iascii		 5
#define iasciiz		 6
#define ibyte		 7
#define icomm		 8
#define ilcomm		 9
#define idata		10
#define idouble		11
#define ifile		12
#define ifloat		13
#define ihalf		14
/*#define iline		15*/
#define idead		16
#define inop		17
#define iweakext	18
#define iloopno		19
#define ispace		20
#define itext		21
#define iword		22
#define iocode		23
#define iend		24
#define isdata		25
#define irdata		26
#define ient		27
#define iloc		28
#define ibgnb		29
#define iendb		30
#define iasm0		31
#define iset		32
#define iorg		33
#define irep		34
#define iendrep		35
#define ilab		36
#define ivreg		37
#define imask		38
#define ifmask		39
#define ierr		40
#define iglobabs	41
#define iverstamp	42
#define iframe		43
#define iextended	44
#define iextern		45
#define iaent		46
#define ioption		47
#define inoalias	48
#define ialias		49
#define imtag		50
#define imalias		51
#define iblank3		52
#define ilivereg	53
#define igjaldef	54
#define igjallive	55
#define igjrlive	56
#define ishift_addr	57
#define irestext	58
#define idword		59
#define iprologue       60
#define iedata          61
#endif

#if 1
#define zldl	0
#define zldq	1
#define zldl_l	2
#define zldq_l	3
#define zldq_u	4
#define zlda	5
#define zstl	6
#define zstq	7
#define zstl_c	8
#define zstq_c	9
#define zstq_u	10
#define zldah	11
#define zldf	12
#define zldg	13
#define zlds	14
#define zldt	15
#define zstf	16
#define zstg	17
#define zsts	18
#define zstt	19
#define zmb	20
#define zfetch	21
#define zrs	22
#define ztrapb	23
#define zfetch_m	24
#define zrpcc	25
#define zrc	26
#define zjsr	27
#define zbr	28
#define zbsr	29
#define zblbc	30
#define zblbs	31
#define zfbeq	32
#define zfbne	33
#define zbeq	34
#define zbne	35
#define zfblt	36
#define zfbge	37
#define zblt	38
#define zbge	39
#define zfble	40
#define zfbgt	41
#define zble	42
#define zbgt	43
#define zaddl	44
#define zaddlv	45
#define zaddq	46
#define zaddqv	47
#define zsubl	48
#define zsublv	49
#define zsubq	50
#define zsubqv	51
#define zs4addl	52
#define zs4addq	53
#define zs4subl	54
#define zs4subq	55
#define zs8addl	56
#define zs8addq	57
#define zs8subl	58
#define zs8subq	59
#define zcmpeq	60
#define zcmplt	61
#define zcmple	62
#define zcmpult	63
#define zcmpule	64
#define zcmpbge	65
#define zand	66
#define zbic	67
#define zcmoveq	68
#define zcmovne	69
#define zcmovlbs	70
#define zbis	71
#define zornot	72
#define zcmovlt	73
#define zcmovge	74
#define zcmovlbc	75
#define zxor	76
#define zeqv	77
#define zcmovle	78
#define zcmovgt	79
#define zsll	80
#define zsra	81
#define zsrl	82
#define zextbl	83
#define zextwl	84
#define zextll	85
#define zextql	86
#define zextwh	87
#define zextlh	88
#define zextqh	89
#define zinsbl	90
#define zinswl	91
#define zinsll	92
#define zinsql	93
#define zinswh	94
#define zinslh	95
#define zinsqh	96
#define zmskbl	97
#define zmskwl	98
#define zmskll	99
#define zmskql	100
#define zmskwh	101
#define zmsklh	102
#define zmskqh	103
#define zzap	104
#define zzapnot	105
#define zmull	106
#define zmulqv	107
#define zmullv	108
#define zumulh	109
#define zmulq	110
#define zcpys	111
#define zcvtlq	112
#define zfcmoveq	113
#define zfcmovne	114
#define zcpysn	115
#define zcvtql	116
#define zfcmovlt	117
#define zfcmovge	118
#define zcpyse	119
#define zcvtqlv	120
#define zmt_fpcr	121
#define zmf_fpcr	122
#define zcvtqlsv	123
#define zfcmovle	124
#define zfcmovgt	125
#define zcmpteq	126
#define zcmptlt	127
#define zcmptle	128
#define zcmptun	129
#define zcmpteqsu	130
#define zcmptltsu	131
#define zcmptlesu	132
#define zcmptunsu	133
#define zcvtqs	134
#define zcvtqsc	135
#define zcvtqsm	136
#define zcvtqsd	137
#define zcvtqssui	138
#define zcvtqssuic	139
#define zcvtqssuim	140
#define zcvtqssuid	141
#define zcvtqt	142
#define zcvtqtc	143
#define zcvtqtm	144
#define zcvtqtd	145
#define zcvtqtsui	146
#define zcvtqtsuic	147
#define zcvtqtsuim	148
#define zcvtqtsuid	149
#define zcvtts	150
#define zcvttsc	151
#define zcvttsm	152
#define zcvttsd	153
#define zcvttsu	154
#define zcvttsuc	155
#define zcvttsum	156
#define zcvttsud	157
#define zcvttssu	158
#define zcvttssuc	159
#define zcvttssum	160
#define zcvttssud	161
#define zcvttssui	162
#define zcvttssuic	163
#define zcvttssuim	164
#define zcvttssuid	165
#define zdivs	166
#define zdivsc	167
#define zdivsm	168
#define zdivsd	169
#define zdivsu	170
#define zdivsuc	171
#define zdivsum	172
#define zdivsud	173
#define zdivssu	174
#define zdivssuc	175
#define zdivssum	176
#define zdivssud	177
#define zdivssui	178
#define zdivssuic	179
#define zdivssuim	180
#define zdivssuid	181
#define zdivt	182
#define zdivtc	183
#define zdivtm	184
#define zdivtd	185
#define zdivtu	186
#define zdivtuc	187
#define zdivtum	188
#define zdivtud	189
#define zdivtsu	190
#define zdivtsuc	191
#define zdivtsum	192
#define zdivtsud	193
#define zdivtsui	194
#define zdivtsuic	195
#define zdivtsuim	196
#define zdivtsuid	197
#define zmuls	198
#define zmulsc	199
#define zmulsm	200
#define zmulsd	201
#define zmulsu	202
#define zmulsuc	203
#define zmulsum	204
#define zmulsud	205
#define zmulssu	206
#define zmulssuc	207
#define zmulssum	208
#define zmulssud	209
#define zmulssui	210
#define zmulssuic	211
#define zmulssuim	212
#define zmulssuid	213
#define zmult	214
#define zmultc	215
#define zmultm	216
#define zmultd	217
#define zmultu	218
#define zmultuc	219
#define zmultum	220
#define zmultud	221
#define zmultsu	222
#define zmultsuc	223
#define zmultsum	224
#define zmultsud	225
#define zmultsui	226
#define zmultsuic	227
#define zmultsuim	228
#define zmultsuid	229
#define zsubs	230
#define zsubsc	231
#define zsubsm	232
#define zsubsd	233
#define zsubsu	234
#define zsubsuc	235
#define zsubsum	236
#define zsubsud	237
#define zsubssu	238
#define zsubssuc	239
#define zsubssum	240
#define zsubssud	241
#define zsubssui	242
#define zsubssuic	243
#define zsubssuim	244
#define zsubssuid	245
#define zsubt	246
#define zsubtc	247
#define zsubtm	248
#define zsubtd	249
#define zsubtu	250
#define zsubtuc	251
#define zsubtum	252
#define zsubtud	253
#define zsubtsu	254
#define zsubtsuc	255
#define zsubtsum	256
#define zsubtsud	257
#define zsubtsui	258
#define zsubtsuic	259
#define zsubtsuim	260
#define zsubtsuid	261
#define zadds	262
#define zaddsc	263
#define zaddsm	264
#define zaddsd	265
#define zaddsu	266
#define zaddsuc	267
#define zaddsum	268
#define zaddsud	269
#define zaddssu	270
#define zaddssuc	271
#define zaddssum	272
#define zaddssud	273
#define zaddssui	274
#define zaddssuic	275
#define zaddssuim	276
#define zaddssuid	277
#define zaddt	278
#define zaddtc	279
#define zaddtm	280
#define zaddtd	281
#define zaddtu	282
#define zaddtuc	283
#define zaddtum	284
#define zaddtud	285
#define zaddtsu	286
#define zaddtsuc	287
#define zaddtsum	288
#define zaddtsud	289
#define zaddtsui	290
#define zaddtsuic	291
#define zaddtsuim	292
#define zaddtsuid	293
#define zcvttq	294
#define zcvttqc	295
#define zcvttqv	296
#define zcvttqvc	297
#define zcvttqsv	298
#define zcvttqsvc	299
#define zcvttqsvi	300
#define zcvttqsvic	301
#define zcvttqd	302
#define zcvttqvd	303
#define zcvttqsvd	304
#define zcvttqsvid	305
#define zcvttqm	306
#define zcvttqvm	307
#define zcvttqsvm	308
#define zcvttqsvim	309
#define zaddf	310
#define zaddfc	311
#define zaddfu	312
#define zaddfuc	313
#define zaddfs	314
#define zaddfsc	315
#define zaddfsu	316
#define zaddfsuc	317
#define zaddg	318
#define zaddgc	319
#define zaddgu	320
#define zaddguc	321
#define zaddgs	322
#define zaddgsc	323
#define zaddgsu	324
#define zaddgsuc	325
#define zcvtdg	326
#define zcvtdgc	327
#define zcvtdgu	328
#define zcvtdguc	329
#define zcvtdgs	330
#define zcvtdgsc	331
#define zcvtdgsu	332
#define zcvtdgsuc	333
#define zcvtgd	334
#define zcvtgdc	335
#define zcvtgdu	336
#define zcvtgduc	337
#define zcvtgds	338
#define zcvtgdsc	339
#define zcvtgdsu	340
#define zcvtgdsuc	341
#define zsubf	342
#define zsubfc	343
#define zsubfu	344
#define zsubfuc	345
#define zsubfs	346
#define zsubfsc	347
#define zsubfsu	348
#define zsubfsuc	349
#define zsubg	350
#define zsubgc	351
#define zsubgu	352
#define zsubguc	353
#define zsubgs	354
#define zsubgsc	355
#define zsubgsu	356
#define zsubgsuc	357
#define zmulf	358
#define zmulfc	359
#define zmulfu	360
#define zmulfuc	361
#define zmulfs	362
#define zmulfsc	363
#define zmulfsu	364
#define zmulfsuc	365
#define zmulg	366
#define zmulgc	367
#define zmulgu	368
#define zmulguc	369
#define zmulgs	370
#define zmulgsc	371
#define zmulgsu	372
#define zmulgsuc	373
#define zdivf	374
#define zdivfc	375
#define zdivfu	376
#define zdivfuc	377
#define zdivfs	378
#define zdivfsc	379
#define zdivfsu	380
#define zdivfsuc	381
#define zdivg	382
#define zdivgc	383
#define zdivgu	384
#define zdivguc	385
#define zdivgs	386
#define zdivgsc	387
#define zdivgsu	388
#define zdivgsuc	389
#define zcmpgeq	390
#define zcmpglt	391
#define zcmpgle	392
#define zcmpgeqs	393
#define zcmpglts	394
#define zcmpgles	395
#define zcvtgf	396
#define zcvtgfc	397
#define zcvtgfu	398
#define zcvtgfuc	399
#define zcvtgfs	400
#define zcvtgfsc	401
#define zcvtgfsu	402
#define zcvtgfsuc	403
#define zcvtqf	404
#define zcvtqfc	405
#define zcvtqg	406
#define zcvtqgc	407
#define zcvtgq	408
#define zcvtgqc	409
#define zcvtgqv	410
#define zcvtgqvc	411
#define zcvtgqs	412
#define zcvtgqsc	413
#define zcvtgqsv	414
#define zcvtgqsvc	415
#define zret	416
#define zjmp	417
#define zjsr_coroutine	418
#define zcall_pal	419
#define znop	420
#define zldiq	421
#define zldil	422
#define zldb	423
#define zldbu	424
#define zldw	425
#define zldwu	426
#define zuldw	427
#define zuldwu	428
#define zuldl	429
#define zuldq	430
#define zstb	431
#define zstw	432
#define zustw	433
#define zustl	434
#define zustq	435
#define zclr	436
#define zabsl	437
#define zabsq	438
#define zmov	439
#define znegl	440
#define zneglv	441
#define znegq	442
#define znegqv	443
#define zsextl	444
#define zdivl	445
#define zdivlu	446
#define zdivq	447
#define zdivqu	448
#define zreml	449
#define zremlu	450
#define zremq	451
#define zremqu	452
#define znot	453
#define zor	454
#define zandnot	455
#define zxornot	456
#define zldid	457
#define zldif	458
#define zldig	459
#define zldis	460
#define zldit	461
#define zfabs	462
#define znegf	463
#define znegg	464
#define znegs	465
#define znegt	466
#define zfmov	467
#define znegfs	468
#define zneggs	469
#define znegssu	470
#define znegtsu	471
#define zfneg	472
#define zldgp	473
#define zcia	474
#define zwmb	475
#define zcvtst	476
#define zcvtsts	477
#define zexcb	478
#define zunop	479
#define zfclr	480
#define zcall_xfloat	481
#define zbad	482
#define n_asmcodes	483
/*
#define frob	 0
#define fra	 1
#define fri	 2
#define frrr	 3
#define frir	 4
#define frr	 5
#define fi	 7
#define fr	 8
#define f_	 9
#define frcr	 10
*/

#else /* __mips */
#define zabs		  0
#define zadd		  1
#define zaddu		  2
#define zand		  3
#define zb		  4
#define zbc0f		  5
#define zbc0t		  6
#define zbc1f		  7
#define zbc1t		  8
#define zbc2f		  9
#define zbc2t		 10
#define z11		 11
#define z12		 12
#define zbeq		 13
#define zbge		 14
#define zbgeu		 15
#define zbgez		 16
#define zbgt		 17
#define zbgtu		 18
#define zbgtz		 19
#define zble		 20
#define zbleu		 21
#define zblez		 22
#define zblt		 23
#define zbltu		 24
#define zbltz		 25
#define zbne		 26
#define zbreak		 27
#define zc0		 28
#define zc1		 29
#define zc2		 30
#define z31		 31
#define zdiv		 32
#define zdivu		 33
#define zj		 34
#define zjal		 35
#define zla		 36
#define zlb		 37
#define zlbu		 38
#define zlh		 39
#define zlhu		 40
#define zli		 41
#define zlw		 42
#define z43		 43
#define zlwc1		 44
#define zlwc2		 45
#define z46		 46
#define zmfhi		 47
#define zmflo		 48
#define zmove		 49
#define z50		 50
#define zswc1		 51
#define zswc2		 52
#define z53		 53
#define zmthi		 54
#define zmtlo		 55
#define zmul		 56
#define zmulo		 57
#define zmulou		 58
#define zmult		 59
#define zmultu		 60
#define zneg		 61
#define znop		 62
#define znor		 63
#define zor		 64
#define zrem		 65
#define zremu		 66
#define zrfe		 67
#define zrol		 68
#define zror		 69
#define zsb		 70
#define zseq		 71
#define zsge		 72
#define zsgeu		 73
#define zsgt		 74
#define zsgtu		 75
#define zsh		 76
#define zsle		 77
#define zsleu		 78
#define zsll		 79
#define zslt		 80
#define zsltu		 81
#define zsne		 82
#define zsra		 83
#define zsrl		 84
#define zsub		 85
#define zsubu		 86
#define zsw		 87
#define zsyscall	 88
#define zxor		 89
#define znot		 90
#define zlwl		 91
#define zlwr		 92
#define zswl		 93
#define zswr		 94
#define zvcall		 95
#define zmfc0		 96
#define zmfc1		 97
#define zmfc2		 98
#define z99		 99
#define zmtc0		100
#define zmtc1		101
#define zmtc2		102
#define z103		103
#define ztlbr		104
#define ztlbwi		105
#define ztlbwr		106
#define ztlbp		107
#define zld		108
#define zsd		109
#define z110		110
#define zldc1		111
#define zldc2		112
#define z113		113
#define z114		114
#define zsdc1		115
#define zsdc2		116
#define z117		117
#define fl_s		118
#define fl_d		119
#define fl_e		120
#define fs_s		121
#define fs_d		122
#define fs_e		123
#define fadd_s		124
#define fadd_d		125
#define fadd_e		126
#define fsub_s		127
#define fsub_d		128
#define fsub_e		129
#define fmul_s		130
#define fmul_d		131
#define fmul_e		132
#define fdiv_s		133
#define fdiv_d		134
#define fdiv_e		135
#define fsqrt_s		136
#define fsqrt_d		137
#define fsqrt_e		138
#define fmov_s		139
#define fmov_d		140
#define fmov_e		141
#define fabs_s		142
#define fabs_d		143
#define fabs_e		144
#define fcvt_s_d	145
#define fcvt_s_e	146
#define fcvt_s_w	147
#define fcvt_d_s	148
#define fcvt_d_e	149
#define fcvt_d_w	150
#define fcvt_e_s	151
#define fcvt_e_d	152
#define fcvt_e_w	153
#define fcvt_w_s	154
#define fcvt_w_d	155
#define fcvt_w_e	156
#define fc_f_s		157
#define fc_f_d		158
#define fc_f_e		159
#define fc_un_s		160
#define fc_un_d		161
#define fc_un_e		162
#define fc_eq_s		163
#define fc_eq_d		164
#define fc_eq_e		165
#define fc_ueq_s	166
#define fc_ueq_d	167
#define fc_ueq_e	168
#define fc_olt_s	169
#define fc_olt_d	170
#define fc_olt_e	171
#define fc_ult_s	172
#define fc_ult_d	173
#define fc_ult_e	174
#define fc_ole_s	175
#define fc_ole_d	176
#define fc_ole_e	177
#define fc_ule_s	178
#define fc_ule_d	179
#define fc_ule_e	180
#define fc_sf_s		181
#define fc_sf_d		182
#define fc_sf_e		183
#define fc_ngle_s	184
#define fc_ngle_d	185
#define fc_ngle_e	186
#define fc_seq_s	187
#define fc_seq_d	188
#define fc_seq_e	189
#define fc_ngl_s	190
#define fc_ngl_d	191
#define fc_ngl_e	192
#define fc_lt_s		193
#define fc_lt_d		194
#define fc_lt_e		195
#define fc_nge_s	196
#define fc_nge_d	197
#define fc_nge_e	198
#define fc_le_s		199
#define fc_le_d		200
#define fc_le_e		201
#define fc_ngt_s	202
#define fc_ngt_d	203
#define fc_ngt_e	204
#define zlui		205
#define zulw		206
#define zulh		207
#define zulhu		208
#define zusw		209
#define zush		210
#define zaddi		211
#define zaddiu		212
#define zslti		213
#define zsltiu		214
#define zandi		215
#define zori		216
#define zxori		217
#define z218		218
#define znegu		219
#define zbeqz		220
#define zbnez		221
#define fneg_s		222
#define fneg_d		223
#define fneg_e		224
#define zcfc1		225
#define zctc1		226
#define zbal		227
#define zbgezal		228
#define zbltzal		229
#define zmtc1_d		230
#define zmfc1_d		231
#define ztrunc_w_s	232
#define ztrunc_w_d	233
#define ztrunc_w_e	234
#define zround_w_s	235
#define zround_w_d	236
#define zround_w_e	237
#define zaddou		238
#define zsubou		239
#define ztruncu_w_s	240
#define ztruncu_w_d	241
#define ztruncu_w_e	242
#define zroundu_w_s	243
#define zroundu_w_d	244
#define zroundu_w_e	245
#define zcfc0		246
#define zcfc2		247
#define z248		248
#define zctc0		249
#define zctc2		250
#define z251		251
#define fli_s		252
#define fli_d		253
#define fli_e		254
#define ztlt		255
#define ztltu		256
#define ztge		257
#define ztgeu		258
#define zteq		259
#define ztne		260
#define zll		261
#define zsc		262
#define zceil_w_s	263
#define zceil_w_d	264
#define zceil_w_e	265
#define zceilu_w_s	266
#define zceilu_w_d	267
#define zceilu_w_e	268
#define zfloor_w_s	269
#define zfloor_w_d	270
#define zfloor_w_e	271
#define zflooru_w_s	272
#define zflooru_w_d	273
#define zflooru_w_e	274
#define	zbeql		275
#define	zbeqzl		276
#define zbnel		277
#define zbnezl		278
#define	zblel		279
#define	zbleul		280
#define zblezl		281
#define	zbgtl		282
#define zbgtul		283
#define zbgtzl		284
#define	zbltl		285
#define zbltul		286
#define zbltzl		287
#define zbltzall	288
#define zbgel		289
#define zbgeul		290
#define zbgezl		291
#define zbgezall	292
#define zbc0fl		293
#define zbc0tl		294
#define zbc1fl		295
#define zbc1tl		296
#define zbc2fl		297
#define zbc2tl		298
#define z299		299
#define z300		300
#define zldl            301
#define zldr            302
#define zlld         	303  
#define zlwu         	304  
#define zsdl            305
#define zsdr            306
#define zscd	        307
#define zdaddi          308
#define zdaddiu       	309
#define zdadd	       	310
#define zdaddu		311
#define zdsub           312
#define zdsubu       	313
#define zdsll         	314
#define zdsrl           315
#define zdsra           316
#define zdsllv          317
#define zdsrlv          318
#define zdsrav       	319
#define zdmult        	320
#define zdmultu        	321
#define zddiv         	322
#define zddivu    	323
#define zlsc1         	324
#define zssc1        	325
#define zdmtc1         	326
#define zdmfc1   	327
#define zdmtc0         	328
#define zdmfc0   	329
#define zdmtc2         	330
#define zdmfc2   	331
#define zeret           334
#define ztrunc_l_s      335
#define zround_l_s      336
#define zceil_l_s       337
#define zfloor_l_s      338
#define ztrunc_l_d      339
#define zround_l_d      340
#define zceil_l_d       341
#define zfloor_l_d      342
#define ztrunc_l_e      343
#define zround_l_e      344
#define zceil_l_e       345
#define zfloor_l_e      346
#define fcvt_l_s        347
#define fcvt_l_d        348
#define fcvt_l_e        349
#define fcvt_l_w        350
#define fcvt_s_l        351
#define fcvt_d_l        352
#define fcvt_e_l        353
#define fcvt_w_l        354
#define zcache		355
#define zcia            356
#ifdef _DLI_DLA
/* 11/28/89 for mips-3 */
#define zdli   		332
#define zdla   		333
#endif
#define zuld            357
#define zusd            358
#define zdabs           359
#define zdneg           360
#define zdnegu          361
#define zdmul           362
#define zdmulo          363
#define zdmulou         364
#define zdrem           365
#define zdremu          366
#define zdrol           367
#define zdror           368
#define zdaddou         369
#define zdsubou         370
#define zulwu		371
#ifdef _MAD_MSB
#define fmad_s		372
#define fmad_d		373
#define fmad_e		374
#define fmsb_s		375
#define fmsb_d		376
#define fmsb_e		377
#endif
#define zbad		378
#define n_asmcodes	379

#define frob	 0
#define fra	 1
#define fri	 2
#define frrr	 3
#define frri	 4
#define frr	 5
#define fa	 6
#define fr	 7
#define frrl	 8
#define frl	 9
#define fl	10
#define forrr	11
#define fril	12
#define fi	13
#define foa	14
#ifdef _MAD_MSB
#define frrrr	15
#endif
#endif

#define set_undefined	 0
#define set_reorder	 1
#define set_noreorder	 2
#define set_macro	 3
#define set_nomacro	 4
#define set_at		 5
#define set_noat	 6
#define set_move	 7
#define set_nomove	 8
#define set_bopt	 9
#define set_nobopt	10

#define o_undefined	 0
#define o_optimize	 1
#define o_pic		 2

#define opt_none	 0
#define opt_int		 1
#define opt_float	 2
#define opt_string	 3

#define call_addx	 0
#define call_addxc	 1
#define call_addxm	 2
#define call_addxp	 3
#define call_addxd	 4
#define call_subx	 5
#define call_subxc	 6
#define call_subxm	 7
#define call_subxp	 8
#define call_subxd	 9
#define call_mulx	10
#define call_mulxc	11
#define call_mulxm	12
#define call_mulxp	13
#define call_mulxd	14
#define call_divx	15
#define call_divxc	16
#define call_divxm	17
#define call_divxp	18
#define call_divxd	19
#define call_cmpxeq	20
#define call_cmpxne	21
#define call_cmpxle	22
#define call_cmpxlt	23
#define call_cvttx	24
#define call_cvtxt	25
#define call_cvtqx	26
#define call_cvtuqx	27
#define call_cvtxq	28
#define call_cvtxqc	29
#define call_cvtxqm	30
#define call_cvtxqp	31
#define call_cvtxqd	32
#define call_cvtxqv	33
#define call_cvtxqvc	34
#define call_cvtxqvm	35
#define call_cvtxqvp	36
#define call_cvtxqvd	37
#define call__last	38		/* e.g. array declarations */



#define binasm_record_length 24 
/* #define binasm_record_length 16 */

#ifndef _REG_SET_C
#define _REG_SET_C 1
typedef unsigned regset[2];
#endif /* _REG_SET_C */


#define FROB 0	/* memory fmt reg, offset(+/-32K), base */
#define FRA 1	/* memory fmt reg, [sym]+offset */
#define FRI 2	/* pseudo inst reg, immed (64 bit) */
#define FRRR 3  /* operate fmt reg,reg,reg */
#define FRIR 4  /* literal format reg, immed (64 bit), reg */
#define FRR 5	/* convert/jump ins reg,reg */
#define FRL 6	/* branch format reg, sym */
#define FTI 7 	/* pal format immed */
#define FR 8	/* for fetch, rcc instructions */
#define FRCR 10	/* literal format reg, condtant d, reg */
	
#define _BINASM_FILL0A_BITSIZE	9
#define _BINASM_ASMTYPE_BITSIZE 7

typedef union {
  char data[binasm_record_length];
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
  } common;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    unsigned lexlev;
  } ent;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    asmint frameoffset;
    asmreg framereg : 7;
    asmreg pcreg : 7;
  } frame;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    unsigned regmask;
    asmint regoffset;
  } mask;
  /* 9/21/89 add ".gjaldef", ".gjallive", ".gjrlive" directive */
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    regset gjmask;
  } gmask;
  struct {
    asmsym symno;		/* handler */
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    int      flag;
    int      data;
  } edata;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    int      eflag;
  } eflag;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    int loopnum;
    unsigned lflag;
  } loopno;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    int majornumber;
    int minornumber;
  } verstamp;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    unsigned filenumber;
    unsigned linenumber;
  } loc;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    unsigned gpmask;
    unsigned fpmask;
  } livereg;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    long length;
    unsigned repeat;
  } chars;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    long  expression;
    unsigned repeat;
  } value;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    unsigned option : 2;
    unsigned fill04 : 30;
    asmint opt_int_value;
  } voption;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    unsigned option : 2;
    unsigned fill04 : 30;
    asmint opt_len;
  } loption;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    asmreg basereg1 : 7;
    asmreg basereg2 : 7;
  } alias;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    int tagnumber;
    int tagtype;
  } mtag;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    int memtag1;
    int memtag2;
  } malias;

  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    unsigned fill03 : 6;
    asmopcode op : 9;		/* 9 bits plus alignment in pascal */
    asmreg reg1 : 7;
    asmreg reg2 : 7;
    asmformat form : 4;
    asmreg reg3 : 7;
  } rinst;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    unsigned fill03 : 6;
    asmopcode op : 9;		/* 9 bits plus alignment in pascal */
    asmreg reg1 : 7;
    asmreg reg2 : 7;
    asmformat form : 4;
    unsigned mem_tag : 14;
    long  immediate;
  } iinst;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    unsigned fill03 : 6;
    asmopcode op : 9;		/* 9 bits plus alignment in pascal */
    asmreg reg1 : 7;
    asmreg reg2 : 7;
    asmformat form : 4;
    asmint imm;
  } linst;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    long	constant_value;
  } constant;
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    asmreg      save_ra_reg;
  } save_ra;
#ifdef _MAD_MSB
  struct {
    asmsym symno;
    unsigned fill0a : _BINASM_FILL0A_BITSIZE;
    unsigned asmtype : _BINASM_ASMTYPE_BITSIZE;
    unsigned fill03 : 6;
    asmopcode op : 9; 
    asmreg reg1 : 7;
    asmreg reg2 : 7;
    asmformat form : 4;
    asmreg reg3 : 7;
    asmreg reg4 : 7;
  } rrinst;
#endif
} binasm;

#endif /* IBINASM_H */

