/*
 * Copyright (c) 2002, The Tendra Project <http://www.ten15.org/>
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


/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header$
--------------------------------------------------------------------------*/

#include "config.h"
#include "dw2_config.h"
#include "translat.h"
#include "eval.h"
#include "flags.h"
#include "labels.h"
#include "basicread.h"
#include "target_v.h"

long dwarf_lab_num = 0;

void out8 
    PROTO_Z ()
{
  outs ( "\t.byte " ) ;
  return;
}

void out16 
    PROTO_Z ()
{
#ifdef NEEDS_DEBUG_ALIGN
  dot_align(2);
#endif
  outs ( "\t.half " ) ;
  return;
}

void out32 
    PROTO_Z ()
{
#ifdef NEEDS_DEBUG_ALIGN
  dot_align(4);
#endif
  outs ( "\t.word " ) ;
  return;
}

void dot_align 
    PROTO_N ( ( n ) )
    PROTO_T ( long n )
{
  outs ( "\t.align " ) ;
  outn (n);
  outnl();
  return;
}

void out_string 
    PROTO_N ( ( s ) )
    PROTO_T ( char * s )
{
  outs ("\t.asciz \"");
  outs (s);
  outs ("\"");
  d_outnl ();
  return;
}

void start_string
    PROTO_N ( (s) )
    PROTO_T ( char * s )
{
  outs ("\t.asciz \"");
  outs (s);
  return;
}

void end_string
    PROTO_Z ()
{
  outs ("\"");
  d_outnl ();
  return;
}

void enter_section 
    PROTO_N ( ( s ) )
    PROTO_T ( char * s )
{
  outs ("\t.section \".");
  outs (s);
  outs ("\"");
  d_outnl ();
  return;
}

void exit_section 
    PROTO_Z ()
{
  enum section old = current_section;
  current_section = no_section;
  insection (old);
  return;
}

void outnl_comment 
    PROTO_N ( ( s ) )
    PROTO_T ( char * s )
{
  outs ("\t!");
  outs (s);
  d_outnl ();
  return;
}

void outnl_comment_i 
    PROTO_N ( ( s, i ) )
    PROTO_T ( char * s X long i )
{
  outs ("\t!");
  outs (s);
  outs (" ");
  outn (i);
  d_outnl ();
  return;
}

void out_dwf_label 
    PROTO_N ( ( l, set ) )
    PROTO_T ( long l X int set )
{
  if (!l)
    failer ("unknown label");
  outs (".Ldw");
  outn (l);
  if (set) {
    outs (":");
    d_outnl ();
  }
  return;
}

void out_code_label
    PROTO_N ( ( l ) )
    PROTO_T ( long l )
{
  outs (lab_prefix);
  outn (l);
  return;
}

void out_dwf_dist_to_label 
    PROTO_N ( ( l ) )
    PROTO_T ( long l )
{
  out_dwf_label (l, 0);
  outs (" - . - 4");
  return;
}

void out_dwf_labdiff 
    PROTO_N ( ( lo, hi ) )
    PROTO_T ( long lo X long hi )
{
  if (hi == lo)
    outn ((long)0);
  else {
    out_dwf_label (hi, 0); 
    outs (" - ");
    out_dwf_label (lo, 0);
  }
  return;
}

void out_ext_label
    PROTO_N ( ( s ) )
    PROTO_T ( char * s )
{
  outs ("\t.global\t");
  outs (s);
  d_outnl ();
  outs (s);
  outs(":");
  d_outnl ();
  return;
}

void out_producer 
    PROTO_N ( ( s ) )
    PROTO_T ( char * s )
{
  outs ("\t.asciz \"");
  outs (s);
  outs ("   with TenDRA SPARC/Solaris installer ");
  outn ( target_version ) ;
  outs ( "." ) ;
  outn ( target_revision ) ;
  outs ("\"");
  d_outnl ();
  return;
}


static int first_data = 0;
static int first_ro = 0;

void note_data 
    PROTO_N ( ( ll, ro ) )
    PROTO_T ( int ll X bool ro )
{
  if (ro) {
    if (!first_ro)
      first_ro = ll;
  }
  else {
    if (!first_data)
      first_data = ll;
  }
  return;
}

void dw2_data_aranges 
    PROTO_Z ()
{
  long lab_data, lab_ro;
  if (first_data) {
    lab_data = next_dwarf_label ();
    if (do_prom) {
      outs ("\t.reserve\t");
      out_dwf_label (lab_data, 0);
      outs (", 0,\".bss\",4");
      d_outnl();
    }
    else {
      insection (data_section);
      out_dwf_label (lab_data, 1);
    }
  }
  if (first_ro) {
    lab_ro = next_dwarf_label ();
    insection (rodata_section);
    out_dwf_label (lab_ro, 1);
  }
  insection (text_section);
  enter_section ("debug_aranges");
  if (first_data) {
    out32 (); outlab (first_data); d_outnl ();
    out32 (); out_dwf_label (lab_data, 0); outs (" - ");
	outlab (first_data); d_outnl ();
  }
  if (first_ro) {
    out32 (); outlab (first_ro); d_outnl ();
    out32 (); out_dwf_label (lab_ro, 0); outs (" - ");
	outlab (first_ro); d_outnl ();
  }
  exit_section ();
  return;
}
