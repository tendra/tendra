/*
    		 Crown Copyright (c) 1996

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
/*
			    VERSION INFORMATION
			    ===================

--------------------------------------------------------------------------
$Header: /u/g/release/CVSROOT/Source/src/installers/680x0/common/mach_ins.c,v 1.1.1.1 1998/01/17 15:55:49 release Exp $
--------------------------------------------------------------------------
$Log: mach_ins.c,v $
 * Revision 1.1.1.1  1998/01/17  15:55:49  release
 * First version to be checked into rolling release.
 *
Revision 1.4  1997/11/13 08:27:13  ma
All avs test passed (except add_to_ptr).

Revision 1.3  1997/11/10 15:38:06  ma
.

Revision 1.2  1997/11/09 14:13:58  ma
comment.

Revision 1.1.1.1  1997/10/13 12:42:55  ma
First version.

Revision 1.5  1997/10/13 08:49:35  ma
Made all pl_tests for general proc & exception handling pass.

Revision 1.4  1997/06/18 10:09:36  ma
Checking in before merging with Input Baseline changes.

Revision 1.3  1997/05/13 11:30:34  ma
Introduced make_comment for debug.

Revision 1.2  1997/04/20 11:30:31  ma
Introduced gcproc.c & general_proc.[ch].
Added cases for apply_general_proc next to apply_proc in all files.

Revision 1.1.1.1  1997/03/14 07:50:14  ma
Imported from DRA

 * Revision 1.1.1.1  1996/09/20  10:56:55  john
 *
 * Revision 1.2  1996/07/05  14:22:21  john
 * Changes for spec 3.1
 *
 * Revision 1.1.1.1  1996/03/26  15:45:14  john
 *
 * Revision 1.2  94/02/21  15:59:49  15:59:49  ra (Robert Andrews)
 * Add a couple of explicit casts.  Some flags which used to be bool are
 * now int.
 *
 * Revision 1.1  93/02/22  17:16:02  17:16:02  ra (Robert Andrews)
 * Initial revision
 *
--------------------------------------------------------------------------
*/


#include "config.h"
#include "common_types.h"
#include "instrs.h"
#include "mach.h"
#include "mach_ins.h"
#include "mach_op.h"
#include "codex.h"
#include "output.h"
#include "utility.h"
extern bool have_cond ;

#ifdef EBUG
extern bool seek_label ;
extern bool seek_extern ;
extern int seek_label_no ;
extern char *seek_extern_id ;
#endif


/*
    OUTPUT FLAG

    If this is true, all instructions are output immediately.  This
    effectively switches off all peephole optimizations.
*/

int output_immediately = 0 ;

/*
    LIST OF ALL INSTRUCTIONS

    A list of all instructions in maintained.  The current instruction is
    given by current_ins.
*/

mach_ins *all_mach_ins = null ;
mach_ins *current_ins = null ;


/*
    RECORD OF LAST JUMP AND REGISTERS CHANGED SINCE

    This is used to help get a more accurate idea of which registers
    are known during the peephole optimizations.
*/

long last_jump = -1 ;
bitpattern last_jump_regs = 0 ;


/*
    LIST OF FREE INSTRUCTIONS

    A list of free mach_ins's, linked by their next field, is maintained.
*/

static mach_ins *mach_ins_list = null ;


/*
    FREE A SINGLE INSTRUCTION AND ITS OPERANDS

    The operands of the instruction are freed and the instruction
    itself is added to the list of all free instructions.
*/

void reclaim_ins
    PROTO_N ( ( p ) )
    PROTO_T ( mach_ins *p )
{
    if ( p->op1 ) free_mach_op ( p->op1 ) ;
    if ( p->op2 ) free_mach_op ( p->op2 ) ;
    p->next = mach_ins_list ;
    mach_ins_list = p ;
    return ;
}


/*
    FREE ALL INSTRUCTIONS AND THEIR OPERANDS

    All the instructions in the list of all instructions are freed and
    the list is reset to zero length.
*/

void free_all_ins
    PROTO_Z ()
{
    mach_ins *p = all_mach_ins, *q = null ;
    if ( p == null ) return ;
    while ( p != null ) {
	if ( p->op1 ) free_mach_op ( p->op1 ) ;
	if ( p->op2 ) free_mach_op ( p->op2 ) ;
	q = p ;
	p = p->next ;
    }
    q->next = mach_ins_list ;
    mach_ins_list = all_mach_ins ;
    all_mach_ins = null ;
    current_ins = null ;
    last_jump = -1 ;
    last_jump_regs = 0 ;
    return ;
}


/*
    CREATE A NEW INSTRUCTION

    A new instruction, with instruction number insno and operands op1 and
    op2 is added to the list of all instructions.  ch gives the mask of
    all registers changed by the instruction.  If susp is true then
    this instruction is never output immediately.  This only occurs in
    tmp_reg.

    This routine is usual called via the macro make_instr which has the
    same first four arguments, but has susp always false.
*/

#ifdef EBUG
static int next_id = 0 ;
#endif

void make_instr_aux
    PROTO_N ( ( insno, op1, op2, ch, susp ) )
    PROTO_T ( int insno X mach_op *op1 X mach_op *op2 X bitpattern ch X int susp )
{
    mach_ins *p ;
    if (insno != m_comment) {
      if ( stack_change ) update_stack () ;
    }
    if ( mach_ins_list == null ) {
	int i, n = 1000 ;
	mach_ins_list = alloc_nof ( mach_ins, n ) ;
	for ( i = 0 ; i < n - 1 ; i++ ) {
	    ( mach_ins_list + i )->next = mach_ins_list + ( i + 1 ) ;
	}
	( mach_ins_list + ( n - 1 ) )->next = null ;
    }
    p = mach_ins_list ;
    mach_ins_list = p->next ;
#ifdef EBUG
    p->id = ++ next_id ;
#if 1
    if(p->id == 4803) {
       int found = 1 ;
    }
#endif
#endif
    p->ins_no = insno ;
    p->op1 = op1 ;
    p->op2 = op2 ;
    p->changed = ch ;
    last_jump_regs |= ch ;
    if ( current_ins == null ) {
	p->next = all_mach_ins ;
	all_mach_ins = p ;
    } else {
	p->next = current_ins->next ;
	current_ins->next = p ;
    }
    current_ins = p ;

    if ( insno != m_comment ) {
      /* Clear the temporary register status */
      tmp_reg_status = 0 ;
      tmp_reg_prefer = 0 ;
    }

    if ( output_immediately && !susp ) {
	output_all () ;
	free_all_ins () ;
    }
    return ;
}


/*
    CREATE A LABEL

    A label is added to the list of all instructions.  This has the effect
    of marking all registers as changed.
*/

void make_label
    PROTO_N ( ( n ) )
    PROTO_T ( long n )
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_LABQ ;
    p->def.num = n ;
    make_instr_aux ( m_label_ins, p, null, ( bitpattern ) 0xffff, 0 ) ;
    have_cond = 0 ;
#ifdef EBUG
    if ( seek_label && n == ( long ) seek_label_no ) {
	warning ( "Label %ld used", n ) ;
	breakpoint () ;
    }
#endif
    return ;
}

#ifdef EBUG

void make_comment
    PROTO_N ( ( comment ) )
    PROTO_T ( char* comment )
{
    mach_op *p;

    p = new_mach_op () ;
    p->type = MACH_COMMENT ;
    p->def.str = comment ;
    make_instr_aux ( m_comment, p, null, ( bitpattern ) 0x0000, 0 ) ;

    return ;
}
#endif

/*
    CREATE AN EXTERNAL LABEL

    An external label is added to the list of all instructions.  This has
    the effect of marking all registers as changed.
*/

void make_external_label
    PROTO_N ( ( nm ) )
    PROTO_T ( char *nm )
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_EXTQ ;
    p->def.str = nm ;
    make_instr_aux ( m_extern_ins, p, null, ( bitpattern ) 0xffff, 0 ) ;
    have_cond = 0 ;
#ifdef EBUG
    if ( seek_extern && eq ( nm, seek_extern_id ) ) {
	warning ( "Label %s used", nm ) ;
	breakpoint () ;
    }
#endif
    return ;
}


/*
    CREATE A JUMP

    A jump, instruction number insno, to label n, is added to the list
    of all instructions.
*/

void make_jump
    PROTO_N ( ( insno, n ) )
    PROTO_T ( int insno X long n )
{
    mach_op *p = new_mach_op () ;
    p->type = MACH_LABQ ;
    p->def.num = n ;
    make_instr_aux ( insno, p, null, ( bitpattern ) 0, 0 ) ;
    if ( n != last_jump ) {
	last_jump = n ;
	last_jump_regs = 0 ;
    }
    return ;
}


/*
    SET A SPECIAL LABEL VALUE

    The special label with identifier nm is set equal to the given value.
*/

void set_special
    PROTO_N ( ( nm, op ) )
    PROTO_T ( char *nm X mach_op *op )
{
    mach_op *op1 = make_special_data ( nm ) ;
    make_instr_aux ( m_as_assign, op1, op, ( bitpattern ) 0, 0 ) ;
    return ;
}


/*
    OUTPUT AN IDENTIFICATION OF TWO NAMES

    This is not required, since all link information is known by the
    time I get round to code production.
*/

void out_rename
    PROTO_N ( ( old_nm, nm ) )
    PROTO_T ( char *old_nm X char *nm )
{
#if 0
    mach_op *op1 = make_extern_data ( old_nm, 0 ) ;
    mach_op *op2 = make_extern_data ( nm, 0 ) ;
    make_instr_aux ( m_as_assign, op1, op2, 0, 0 ) ;
#endif
    return ;
}
