/*
 * Copyright (c) 2002, The Tendra Project <http://www.tendra.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 *    		 Crown Copyright (c) 1997
 *    
 *    This TenDRA(r) Computer Program is subject to Copyright
 *    owned by the United Kingdom Secretary of State for Defence
 *    acting through the Defence Evaluation and Research Agency
 *    (DERA).  It is made available to Recipients with a
 *    royalty-free licence for its use, reproduction, transfer
 *    to other parties and amendment for any purpose not excluding
 *    product development provided that any such use et cetera
 *    shall be deemed to be acceptance of the following conditions:-
 *    
 *        (1) Its Recipients shall ensure that this Notice is
 *        reproduced upon any copies or amended versions of it;
 *    
 *        (2) Any amended version of it shall be clearly marked to
 *        show both the nature of and the organisation responsible
 *        for the relevant amendment or amendments;
 *    
 *        (3) Its onward transfer from a recipient to another
 *        party shall be deemed to be that party's acceptance of
 *        these conditions;
 *    
 *        (4) DERA gives no warranty or assurance as to its
 *        quality or suitability for any purpose and DERA accepts
 *        no liability whatsoever in relation to any use to which
 *        it may be put.
 *
 * $TenDRA$
 */


/**********************************************************************
 *$Author$
 *$Date$
 *$Revision$*/
sc[0]="Nil";
sc[1]="Text";
sc[2]="Data";
sc[3]="Bss";
sc[4]="Reg";
sc[5]="Abs";
sc[6]="Undef'd";
sc[7]="CdbLoc";
sc[8]="Bits";
sc[9]="CdbSys";
/* #define Dbx		9	overlap dbx internal use */
sc[10]="RegIm";
sc[11]="Info";
sc[12]="UserStru";
sc[13]="SData";
sc[14]="SBss";
sc[15]="RData";
sc[16]="Var";
sc[17]="Common";
sc[18]="SCommon";
sc[19]="VarReg";
sc[20]="Variant";
sc[21]="SUndef";
sc[22]="Init";



st[0]="Nil";
st[1]="Global";
st[2]="Static";
st[3]="Param";
st[4]="Local";	
st[5]="Label";
st[6]="Proc";
st[7]="Block";
st[8]="End";
st[9]="Member";	
st[10]="Typedef";
st[11]="File";	
st[12]="RegRel";
st[13]="Forward	";
st[14]="StatPro";
st[15]="Constant";



bt[0]="Nil";
bt[1]="Adr";
bt[2]="Char";
bt[3]="UChar";
bt[4]="Short";
bt[5]="UShort";
bt[6]="Int";
bt[7]="UInt";
bt[8]="Long";
bt[9]="ULong";
bt[10]="Float";
bt[11]="Double";
bt[12]="Struct";
bt[13]="Union";
bt[14]="Enum";
bt[15]="Typedef";
bt[16]="Range";
bt[17]="Set";
bt[18]="Complex";
bt[19]="DComplex";
bt[20]="Indirect";
bt[21]="FixedDec";
bt[22]="FloatDec";
bt[23]="String";
bt[24]="Bit";
bt[25]="Picture";
bt[26]= "Void" ; 	
bt[27]= "PtrMem";
bt[28] = "Vptr"	;	
bt[29] = "Class";
bt[30] = "Long64";	
bt[31] = "ULong64";	
bt[32] = "LongLong64";	
bt[33] = "ULongLong64";	
bt[34] =  "Adr64";	
bt[35] ="PlainChar";
bt[36] ="LongDouble"; 

tq[0]="\b";
tq[1]="Ptr";
tq[2]="Proc";
tq[3]="Array";
tq[4]="Vol";
