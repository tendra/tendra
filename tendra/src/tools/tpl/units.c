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


/**********************************************************************
$Author: release $
$Date: 1998/02/04 10:46:41 $
$Revision: 1.2 $
$Log: units.c,v $
 * Revision 1.2  1998/02/04  10:46:41  release
 * Changes during testing.
 *
 * Revision 1.1.1.1  1998/01/17  15:57:25  release
 * First version to be checked into rolling release.
 *
 * Revision 1.4  1995/09/05  16:27:54  currie
 * include files + 2r lex
 *
 * Revision 1.3  1995/09/04  10:29:24  currie
 * tld units instead of tld2
 *
 * Revision 1.2  1995/08/21  16:00:59  currie
 * put <stdlib> at top of headers
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.1  1995/04/07  14:29:07  currie
 * Initial revision
 *
 * Revision 1.2  1994/07/21  10:36:40  currie
 * Added banner
 *
***********************************************************************/
#include "config.h"
#include "util.h"
#include "readstreams.h"
#include "streams.h"
#include "units.h"
#include "encodings.h"
#include "enc_nos.h"
#include "includes.h"
#include "errors.h"
#include "defs.h"
#include "syntax.h"


FILE *out_file ;
Unit units[NO_OF_UNITS];
int current_Unit;
int capsule_names[NO_OF_ENTITIES];
TDF lk_externs[NO_OF_ENTITIES];
char * ent_names[NO_OF_ENTITIES] = {"token","tag","alignment"};
char * unit_names[NO_OF_UNITS] =
	{"tld", "versions", "tokdec", "tokdef", "aldef", "tagdec",
	"tagdef"};

int line_no_tok = -1;


int next_label
    PROTO_Z ()
{
	return (units[current_Unit].no_labs++);
}


int next_unit_name
    PROTO_N ( (ent) )
    PROTO_T ( int ent )
{
	return ((units[current_Unit].no_entity)[ent]++);
}


Name next_name
    PROTO_N ( (ent) )
    PROTO_T ( int ent )
{
	Name ans;
	ans.unit_no = current_Unit;
	ans.unit_name = next_unit_name(ent);
	return ans;
}


int next_capsule_name
    PROTO_N ( (ent) )
    PROTO_T ( int ent )
{
	return (capsule_names[ent]++);
}


int capsule_name
    PROTO_N ( (n, ent) )
    PROTO_T ( Name * n X int ent )
{
	Unit * nl_unit = & units[n->unit_no];
	Link * nl_links = (nl_unit->links)[ent];
	while(nl_links != (Link*)0) {
		if (n->unit_name == nl_links->unit_name)
			return nl_links->capsule_name;
		nl_links = nl_links->next;
	}
	Assert(n->unit_name < (nl_unit->no_entity)[ent]);
	nl_links = MALLOC(Link);
	nl_links->capsule_name = next_capsule_name(ent);
	nl_links->unit_name = n->unit_name;
	nl_links->next = (nl_unit->links)[ent];
	(nl_unit->links)[ent] = nl_links;
	return nl_links->capsule_name;
}


int cname_to_lname
    PROTO_N ( (c_name, ent) )
    PROTO_T ( int c_name X int ent )
{
	Link * links = (units[current_Unit].links)[ent];
	while( links != (Link*)0) {
		if (c_name == links->capsule_name) return links->unit_name;
		links = links->next;
	}
	links = MALLOC(Link);
	links->capsule_name = c_name;
	links->unit_name = next_unit_name(ent);
	links->next = (units[current_Unit].links)[ent];
	(units[current_Unit].links)[ent] = links;
	return links->unit_name;
}


int non_local
    PROTO_N ( (n, ent) )
    PROTO_T ( Name * n X int ent )
{
	return cname_to_lname(capsule_name(n, ent),ent) ;
}


void make_tag
    PROTO_N ( (n) )
    PROTO_T ( Name * n )
{
  	int loc_name = (current_Unit == n->unit_no)? n->unit_name:
				non_local(n, tag_ent);
	Assert(loc_name<(units[current_Unit].no_entity)[tag_ent]);
	o_make_tag(out_tdfint32(UL(loc_name)));
}


void make_tok
    PROTO_N ( (n) )
    PROTO_T ( Name * n )
{
  	int loc_name = (current_Unit == n->unit_no)? n->unit_name:
				non_local(n, tok_ent);
	Assert(loc_name<(units[current_Unit].no_entity)[tok_ent]);
	o_make_tok(out_tdfint32(UL(loc_name)));
}


void make_al_tag
    PROTO_N ( (n) )
    PROTO_T ( Name * n )
{
  	int loc_name = (current_Unit == n->unit_no)? n->unit_name:
				non_local(n, al_tag_ent);
	Assert(loc_name<(units[current_Unit].no_entity)[al_tag_ent]);
	o_make_al_tag(out_tdfint32(UL(loc_name)));
}


long local_name
    PROTO_N ( (n, ent) )
    PROTO_T ( Name * n X int ent )
{
	int loc_name = (current_Unit == n->unit_no)? n->unit_name:
				non_local(n, ent);
	Assert(loc_name<(units[current_Unit].no_entity)[ent]);
	return loc_name;
}


void FILENAME
    PROTO_Z ()
{
	o_make_filename(
	  o_make_nat(out_tdfint32(UL(0))),
	  out_tdfstring_bytes("?",8,1),
	  out_tdfstring_bytes(file_name, 8, UI(strlen(file_name)))
	);
}


void init_units
    PROTO_Z ()
{
	int i,j;
	if (MAJOR_NO == 4 && MINOR_NO == 1) {
		MINOR_NO = 0;
	}
	for(i=0; i<NO_OF_UNITS; i++) {
		Unit * u = & units[i];
		INIT_TDF(&u->tdf);
		u->no_labs = 0;
		u->present = (i==version_unit || i == tld2_unit);
		for(j=0; j<NO_OF_ENTITIES; j++) {
			(u->no_entity)[j] = 0;
			(u->links)[j] = (Link*)0;
		}
	}
}


static void make_links
    PROTO_N ( (l) )
    PROTO_T ( Link * l )
{
	o_make_links(
	   { while(l!=(Link*)0) {
	   	LIST_ELEM(
	   	   o_make_link(out_tdfint32(UL(l->unit_name)),
	   	   		out_tdfint32(UL(l->capsule_name))
	   	   	      )
	   	  );
	   	l = l->next;
	     }
	   }
	);
}


static void props
    PROTO_N ( (unit_no) )
    PROTO_T ( int unit_no )
{
  Unit * u = units+unit_no;
  TDF temp;
  NEW_STREAM ( &temp,
  switch(unit_no) {
    case version_unit:
    	o_make_versions(
    	   { LIST_ELEM(o_make_version(out_tdfint32(MAJOR_NO),
    				      out_tdfint32(MINOR_NO)
    				     )
    		       );
    	   }
        );
     	break;
    case tokdec_unit:
    	o_make_tokdecs({ append_TDF(&u->tdf, 1);
    			 current_TDF->no = u->tdf.no;
    			}
    		       );
        break;
    case tokdef_unit:
    	o_make_tokdefs( out_tdfint32(UL(u->no_labs)),
			{ append_TDF(&u->tdf, 1);
    			 current_TDF->no = u->tdf.no;
    			}
    		       );
    	break;
    case tagdec_unit:
    	o_make_tagdecs( out_tdfint32(UL(u->no_labs)),
			{ append_TDF(&u->tdf, 1);
    			 current_TDF->no = u->tdf.no;
    			}
    		       );
    	break;
    case tagdef_unit:
    	o_make_tagdefs( out_tdfint32(UL(u->no_labs)),
			{ append_TDF(&u->tdf, 1);
    			 current_TDF->no = u->tdf.no;
    			}
    		       );
    	break;
    case al_tagdef_unit:
    	o_make_al_tagdefs( out_tdfint32(UL(u->no_labs)),
			{ append_TDF(&u->tdf, 1);
    			 current_TDF->no = u->tdf.no;
    			}
    		       );
    	break;
    default: fail("Don't know unit type");
  }
 );
 append_bytestream(&temp,1);
}


void make_unit
    PROTO_N ( (unit_no) )
    PROTO_T ( int unit_no )
{
	Unit * u = units+unit_no;
	int i;
	o_make_unit(
	  if (unit_no != tld2_unit)
	  { for(i=0; i<NO_OF_ENTITIES; i++) {
	   	LIST_ELEM( out_tdfint32(UL(u->no_entity[i])) );
	     }
	  },
	  if (unit_no != tld2_unit)
	  { for(i=0; i<NO_OF_ENTITIES; i++) {
	   	LIST_ELEM(make_links(u->links[i]));
	     }
	  },
	  if (unit_no != tld2_unit)
	  	{ props(unit_no); }
	  else { append_bytestream(&u->tdf, 1);	}
	);
}


static int get_byte
    PROTO_Z ()
{
  unsigned int x=0;
  int i;
  for(i=7; i>=0; i--) {
     unsigned int y = get_bit();
     if(y>1) return -1;
     x+= (y<<i);
  }
  return (int)x;
}


void make_tdf_file
    PROTO_N ( (s, file) )
    PROTO_T ( TDF * s X FILE * file )
{
  	Instream ins;
  	Chunk * ch = s->first;
  	int offst = 0;
  	int x;
	curin = &ins;
	curin->ch = ch;
	curin->byte_pos = 0;
	curin->bit_pos = 0;

	while (ch != (Chunk*)0)	{
	   offst += ch->offst;
	   offst &= 7;
	   if (ch->next == (Chunk*)0 || ch->next->aligned) {
	   	if (offst !=0) {
	   	   ch->offst += (unsigned char)(8-offst);
	   	   if (ch->offst >= 8) { ch->usage+=1; ch->offst-=8; }
	   	   offst=0;
	   	}
	   }
	   ch = ch->next;
	}

    	while((x = get_byte())>=0 ) {
    		IGNORE fputc(x, file);
    	}
}
