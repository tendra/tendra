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


#include "config.h"
#include "filename.h"
#include "list.h"
#include "archive.h"
#include "environ.h"
#include "flags.h"
#include "compile.h"
#include "execute.h"
#include "options.h"
#include "stages.h"
#include "startup.h"
#include "suffix.h"
#include "utility.h"
static filename *apply_unjoin PROTO_S ( ( filename *, int ) ) ;


/*
    CHECK IF ONE FILE IS THE C SPEC OF THE OTHER

    This macro checks if q is the C or C++ spec file corresponding to p.
    q must be of type C_SPEC and have the same uniq value as p.
*/

#define spec_of( p, q )\
	( ( q ) && ( ( q )->type == C_SPEC || ( q )->type == CPP_SPEC ) \
			 && ( q )->uniq == ( p )->uniq )


/*
    APPLY THE SYSTEM COMPILER

    This routine applies the system C compiler to the files, input,
    returning the result.
*/

static filename *apply_cc
    PROTO_N ( ( input ) )
    PROTO_T ( filename *input )
{
    filename *p = input ;
    filename *output = null ;
    while ( p != null ) {
	filename *ps = null ;
	filename *pn = p->next ;
	p->next = null ;
	switch ( p->type ) {

	    case C_SOURCE : {
		/* C source */
		if ( make_preproc || keeps [ PREPROC_C ] ) {
		    p = do_cc ( p, PREPROC_C ) ;
		    if ( stops [ PREPROC_C ] ) break ;
		}
		goto preproc_c_lab ;
	    }

	    case PREPROC_C :
	    preproc_c_lab : {
		/* Preprocessed C source */
		if ( use_system_cc == 1 ) {
		    ps = do_produce ( p ) ;
		    if ( ps == null ) {
			p = null ;
			break ;
		    } else {
			ps = ps->next ;
		    }
		}
		if ( stops [ DEP_TDF ] ) {
		    if ( ps != null ) p = null ;
		    break ;
		} else if ( stops [ AS_SOURCE ] ) {
		    p = do_cc ( p, AS_SOURCE ) ;
		    break ;
		} else if ( keeps [ AS_SOURCE ] ) {
		    p = do_cc ( p, AS_SOURCE ) ;
		} else {
		    p = do_cc ( p, binary_obj_type ) ;
		    break ;
		}
		goto as_source_lab ;
	    }

	    case CPP_SOURCE : {
		/* C++ source */
		if ( make_preproc || keeps [ PREPROC_CPP ] ) {
		    p = do_cc ( p, PREPROC_CPP ) ;
		    if ( stops [ PREPROC_CPP ] ) break ;
		}
		goto preproc_cpp_lab ;
	    }

	    case PREPROC_CPP :
	    preproc_cpp_lab : {
		/* Preprocessed C++ source */
		if ( use_system_cc == 1 ) {
		    ps = do_cpp_produce ( p ) ;
		    if ( ps == null ) {
			p = null ;
			break ;
		    } else {
			ps = ps->next ;
		    }
		}
		if ( stops [ DEP_TDF ] ) {
		    if ( ps != null ) p = null ;
		    break ;
		} else if ( stops [ AS_SOURCE ] ) {
		    p = do_cc ( p, AS_SOURCE ) ;
		    break ;
		} else if ( keeps [ AS_SOURCE ] ) {
		    p = do_cc ( p, AS_SOURCE ) ;
		} else {
		    p = do_cc ( p, binary_obj_type ) ;
		    break ;
		}
		goto as_source_lab ;
	    }

	    case AS_SOURCE :
	    as_source_lab : {
		/* Assembly source file */
		if ( !stops [ AS_SOURCE ] ) p = do_cc ( p, BINARY_OBJ ) ;
		break ;
	    }

	    case BINARY_OBJ : {
		/* Binary object file */
		break ;
	    }

	    case C_SPEC : {
		/* C spec file */
		if ( !allow_specs ) {
		    error ( WARNING, "'%s' is a C spec file", p->name ) ;
		    p->type = DEFAULT_TYPE ;
		} else {
		    if ( p->storage == INPUT_FILE &&
			 keeps_aux [ BINARY_OBJ ] == 1 &&
			 !stops [ AS_SOURCE ] ) {
			p = do_build_file ( p, BINARY_OBJ ) ;
		    }
		}
		break ;
	    }

	    case CPP_SPEC : {
		/* C++ spec file */
		if ( !allow_specs || !allow_cpp ) {
		    error ( WARNING, "'%s' is a C++ spec file", p->name ) ;
		    p->type = DEFAULT_TYPE ;
		} else {
		    if ( p->storage == INPUT_FILE &&
			 keeps_aux [ BINARY_OBJ ] == 1 &&
			 !stops [ AS_SOURCE ] ) {
			p = do_build_file ( p, BINARY_OBJ ) ;
		    }
		}
		break ;
	    }

	    default : {
		/* Other file types give an error */
		error ( WARNING, "TDF file '%s' not recognised in cc mode",
			p->name ) ;
		p->type = DEFAULT_TYPE ;
		break ;
	    }
	}
	if ( p && p->storage != INPUT_FILE && p->aux == null ) {
	    boolean have_spec = 0 ;
	    filename *p_archive = p ;
	    int t = p->type ;
	    if ( t == BINARY_OBJ && keeps [t] && binary_obj_type != t ) {
		if ( spec_of ( p_archive, ps ) ) {
		    p_archive->next = ps ;
		    p_archive = p_archive->next ;
		    ps = ps ->next ;
		    p_archive->next = null ;
		    have_spec = 1 ;
		}
		if ( have_spec ) {
		    p = do_build_file ( p, BINARY_OBJ ) ;
		}
	    }
	}
	output = add_filename ( output, p ) ;
	if ( ps ) output = add_filename ( output, ps ) ;
	p = pn ;
    }
    return ( output ) ;
}


/*
    APPLY THE TDF LINKER

    This routine applies the TDF linker to p, returning the result.
*/

static filename *apply_tdf_link
    PROTO_N ( ( p ) )
    PROTO_T ( filename *p )
{
    static boolean tried = 0 ;
    if ( p == null || stops [ INDEP_TDF ] ) return ( p ) ;
    if ( tokdef_name && tokdef_output == null && !tried ) {
	filename *q ;
	if ( !allow_notation ) read_env ( TNC_ENV ) ;
	q = find_filename ( tokdef_name, PRETTY_TDF ) ;
	q = do_notation ( q ) ;
	if ( q ) tokdef_output = q->name ;
	tried = 1 ;
    }
    return ( do_tdf_link ( p ) ) ;
}


/*
    APPLY THE MAIN COMPILATION STAGES

    This routine applies the main compilation phases to the input files
    input, and returns the corresponding output files.  If produce is
    true then the compilation stops at the target independent TDF stage.
    This, and all the routines in this module, needs to be kept in step
    with Table 1.
*/

static filename *apply_compile
    PROTO_N ( ( input, produce ) )
    PROTO_T ( filename *input X int produce )
{
    filename *p = input ;
    filename *output = null ;
    if ( use_system_cc ) return ( apply_cc ( input ) ) ;
    while ( p != null ) {
	filename *pc = p ;
	filename *pn = p->next ;
	p->next = null ;
	switch ( p->type ) {

	    case C_SOURCE : {
		/* C source */
		if ( keeps [ PREPROC_C ] ) {
		    p = do_preproc ( p ) ;
		} else {
		    p = do_produce ( p ) ;
		}
		if ( allow_specs && stops [ C_SPEC ] ) p = null ;
		if ( p != pc ) p = apply_compile ( p, produce ) ;
		break ;
	    }

	    case PREPROC_C : {
		/* Preprocessed C source */
		if ( stops [ PREPROC_C ] ) break ;
		p = do_produce ( p ) ;
		if ( allow_specs && stops [ C_SPEC ] ) p = null ;
		if ( p != pc ) p = apply_compile ( p, produce ) ;
		break ;
	    }

	    case CPP_SOURCE : {
		/* C++ source */
		if ( allow_cpp ) {
		    if ( keeps [ PREPROC_CPP ] ) {
			p = do_cpp_preproc ( p ) ;
		    } else {
			p = do_cpp_produce ( p ) ;
		    }
		    if ( allow_specs && stops [ CPP_SPEC ] ) p = null ;
		    if ( p != pc ) p = apply_compile ( p, produce ) ;
		} else {
		    error ( WARNING, "'%s' is a C++ source file",
			    p->name ) ;
		    p->type = DEFAULT_TYPE ;
		}
		break ;
	    }

	    case PREPROC_CPP : {
		/* Preprocessed C++ source */
		if ( stops [ PREPROC_CPP ] ) break ;
		if ( allow_cpp ) {
		    p = do_cpp_produce ( p ) ;
		    if ( allow_specs && stops [ CPP_SPEC ] ) p = null ;
		    if ( p != pc ) p = apply_compile ( p, produce ) ;
		} else {
		    error ( WARNING, "'%s' is a preprocessed C++ source file",
			    p->name ) ;
		    p->type = DEFAULT_TYPE ;
		}
		break ;
	    }

	    case INDEP_TDF : {
		/* Target independent TDF */
		if ( !produce ) {
		    p = apply_tdf_link ( p ) ;
		    if ( p != pc ) p = apply_compile ( p, produce ) ;
		}
		break ;
	    }

	    case DEP_TDF : {
		/* Target dependent TDF */
		if ( !produce ) {
		    p = do_translate ( p ) ;
		    if ( p != pc ) p = apply_compile ( p, produce ) ;
		}
		break ;
	    }

	    case AS_SOURCE : {
		/* Assembly source */
		if ( !produce ) {
		    p = do_assemble ( p ) ;
		    if ( p != pc ) p = apply_compile ( p, produce ) ;
		}
		break ;
	    }

	    case PRETTY_TDF : {
		/* TDF notation source */
		if ( allow_notation ) {
		    p = do_notation ( p ) ;
		    if ( p != pc ) p = apply_compile ( p, produce ) ;
		} else {
		    error ( WARNING, "'%s' is a TDF notation source file",
			    p->name ) ;
		    p->type = DEFAULT_TYPE ;
		}
		break ;
	    }

	    case PL_TDF : {
		/* PL_TDF source */
		if ( allow_pl_tdf ) {
		    p = do_pl_tdf ( p ) ;
		    if ( p != pc ) p = apply_compile ( p, produce ) ;
		} else {
		    error ( WARNING, "'%s' is a PL_TDF source file",
			    p->name ) ;
		    p->type = DEFAULT_TYPE ;
		}
		break ;
	    }

	    case C_SPEC : {
		/* C spec file */
		if ( !allow_specs ) {
		    error ( WARNING, "'%s' is a C spec file", p->name ) ;
		    p->type = DEFAULT_TYPE ;
		} else {
		    if ( p->storage == INPUT_FILE &&
			 keeps_aux [ BINARY_OBJ ] == 1 &&
			 !stops [ AS_SOURCE ] ) {
			p = do_build_file ( p, BINARY_OBJ ) ;
		    }
		}
		break ;
	    }

	    case CPP_SPEC : {
		/* C++ spec file */
		if ( !allow_specs || !allow_cpp ) {
		    error ( WARNING, "'%s' is a C++ spec file", p->name ) ;
		    p->type = DEFAULT_TYPE ;
		} else {
		    if ( p->storage == INPUT_FILE &&
			 keeps_aux [ BINARY_OBJ ] == 1 &&
			 !stops [ AS_SOURCE ] ) {
			p = do_build_file ( p, BINARY_OBJ ) ;
		    }
		}
		break ;
	    }
	}
	if ( p && p->storage != INPUT_FILE && p->aux == null ) {
	    boolean have_spec = 0 ;
	    filename *p_archive = p ;
	    if ( spec_of ( p_archive, p_archive->next ) ) {
		p_archive = p_archive->next ;
		have_spec = 1 ;
	    } else if ( spec_of ( p_archive, pn ) ) {
		p_archive->next = pn ;
		p_archive = p_archive->next ;
		pn = pn->next ;
		p_archive->next = null ;
		have_spec = 1 ;
	    }
	    if ( have_spec ) {
		int t = p->type ;
		if ( t == INDEP_TDF && checker && !stops [t] ) {
		    if ( stops [ BINARY_OBJ ] ||
			 keeps_aux [ BINARY_OBJ ] == 1 ) {
			p = do_build_file ( p->next, BINARY_OBJ ) ;
		    }
		}
		if ( t == BINARY_OBJ && keeps [t] ) {
		    p = do_build_file ( p, BINARY_OBJ ) ;
		}
	    }
	}
	output = add_filename ( output, p ) ;
	p = pn ;
    }
    return ( output ) ;
}


/*
    FILTER OUT LIST OF BINARY OBJECT FILES

    This routine picks out the TDF capsules from the input files, input,
    compiles them to binary object files, and returns them.
*/

static filename *filter_ofiles
    PROTO_N ( ( input ) )
    PROTO_T ( filename *input )
{
    filename *p = input ;
    filename *links = null ;
    while ( p != null ) {
	filename *pn = p->next ;
	p->next = null ;
	p->aux = pn ;
	if ( p->type == INDEP_TDF ) {
	    filename *q = apply_compile ( p, 0 ) ;
	    if ( q && q->type == BINARY_OBJ ) {
		links = add_filename ( links, q ) ;
	    }
	}
	p = pn ;
    }
    return ( links ) ;
}


/*
    APPLY THE SYSTEM LINKER

    This routine applies the system linker to the input files, input,
    and returns the corresponding output files.
*/

static filename *apply_link
    PROTO_N ( ( input ) )
    PROTO_T ( filename *input )
{
    filename *p = input ;
    int spec_out = C_SPEC_2 ;
    filename *links = null, *links_out = null ;
    filename *specs = null, *specs_out ;
    filename *others = null ;
    while ( p != null ) {
	filename *pn = p->next ;
	p->next = null ;
	p->aux = pn ;
	if ( p->type == BINARY_OBJ ) {
	    links = add_filename ( links, p ) ;
	} else if ( p->type == C_SPEC ) {
	    specs = add_filename ( specs, p ) ;
	} else if ( p->type == CPP_SPEC ) {
	    specs = add_filename ( specs, p ) ;
	    spec_out = CPP_SPEC_2 ;
	} else {
	    others = add_filename ( others, p ) ;
	}
	p = pn ;
    }
    last_return = 0 ;
    keeps [ binary_obj_type ] = 0 ;
    specs_out = do_link_specs ( specs, spec_out ) ;
    links = add_filename ( links, filter_ofiles ( specs_out ) ) ;
    if ( use_dynlink != 0 && use_system_cc == 0 ) links = do_dynlink ( links ) ;
    if ( links ) links_out = do_link ( links ) ;
    if ( specs_out && links_out ) specs_out->uniq = links_out->uniq ;
    p = add_filename ( links_out, specs_out ) ;
    p = add_filename ( p, others ) ;
    if ( last_return ) {
	/* If the linking failed, keep the .o files */
	filename *q = input ;
	boolean b = keeps [ BINARY_OBJ ] ;
	keeps [ BINARY_OBJ ] = 1 ;
	p = null ;
	while ( q != null ) {
	    filename *qa = q->aux ;
	    q->next = null ;
	    if ( q->type == C_SPEC || q->type == CPP_SPEC ) {
		q = null ;
	    } else if ( q->type == BINARY_OBJ ) {
		if ( q->storage == INPUT_FILE || b ) {
		    q = null ;
		} else if ( allow_specs ) {
		    if ( link_specs ) q = do_keep ( q ) ;
		    if ( spec_of ( q, qa ) ) {
			q->next = qa ;
			qa->next = null ;
			qa = qa->aux ;
			if ( link_specs ) q->next = do_keep ( q->next ) ;
		    }
		    q = do_build_file ( q, BINARY_OBJ ) ;
		} else {
		    q = do_keep ( q ) ;
		}
	    }
	    p = add_filename ( p, q ) ;
	    q = qa ;
	}
    }
    return ( p ) ;
}


/*
    SPLIT ALL TDF ARCHIVES

    This routine splits any TDF archives in the input files, input,
    and returns the corresponding output files.
*/

static filename *apply_split_arch
    PROTO_N ( ( input ) )
    PROTO_T ( filename *input )
{
    filename *p = input ;
    filename *output = null ;
    archive_type = TDF_ARCHIVE ;
    while ( p != null ) {
	filename *pn = p->next ;
	p->next = null ;
	if ( p->type == TDF_ARCHIVE ) {
	    if ( use_system_cc ) {
		error ( WARNING, "'%s' is a TDF archive", p->name ) ;
		p->type = DEFAULT_TYPE ;
	    } else {
		p = do_split_arch ( p ) ;
	    }
	}
	output = add_filename ( output, p ) ;
	p = pn ;
    }
    return ( output ) ;
}


/*
    BUILD A TDF ARCHIVE

    This routine creates a TDF archive from the input files, input,
    and returns the corresponding output files.
*/

static filename *apply_build_arch
    PROTO_N ( ( input ) )
    PROTO_T ( filename *input )
{
    filename *p = input ;
    filename *links = null ;
    filename *specs = null ;
    filename *others = null ;
    int spec_out = C_SPEC_1 ;
    while ( p != null ) {
	filename *pn = p->next ;
	p->next = null ;
	if ( p->type == INDEP_TDF ) {
	    links = add_filename ( links, p ) ;
	} else if ( p->type == C_SPEC ) {
	    specs = add_filename ( specs, p ) ;
	} else if ( p->type == CPP_SPEC ) {
	    specs = add_filename ( specs, p ) ;
	    spec_out = CPP_SPEC_1 ;
	} else {
	    others = add_filename ( others, p ) ;
	}
	p = pn ;
    }
    specs = do_link_specs ( specs, spec_out ) ;
    links = do_build_arch ( links ) ;
    if ( specs && links ) specs->uniq = links->uniq ;
    p = add_filename ( links, specs ) ;
    p = add_filename ( p, others ) ;
    return ( p ) ;
}


/*
    BUILD A TDF COMPLEX

    This routine creates a complex TDF capsule from the input files,
    input, and returns the corresponding output files.
*/

static filename *apply_build
    PROTO_N ( ( input ) )
    PROTO_T ( filename *input )
{
    filename *p = input ;
    filename *links = null ;
    filename *specs = null ;
    filename *others = null ;
    int spec_out = C_SPEC_1 ;
    while ( p != null ) {
	filename *pn = p->next ;
	p->next = null ;
	if ( p->type == INDEP_TDF ) {
	    links = add_filename ( links, p ) ;
	} else if ( p->type == C_SPEC ) {
	    specs = add_filename ( specs, p ) ;
	} else if ( p->type == CPP_SPEC ) {
	    specs = add_filename ( specs, p ) ;
	    spec_out = CPP_SPEC_1 ;
	} else {
	    others = add_filename ( others, p ) ;
	}
	p = pn ;
    }
    specs = do_link_specs ( specs, spec_out ) ;
    links = do_tdf_build ( links ) ;
    if ( specs && links ) specs->uniq = links->uniq ;
    p = add_filename ( links, specs ) ;
    p = add_filename ( p, others ) ;
    return ( p ) ;
}


/*
    APPLY THE PREPROCESSOR

    This routine applies the preprocessor to the input files, input,
    and returns the corresponding output files.
*/

static filename *apply_preproc
    PROTO_N ( ( input ) )
    PROTO_T ( filename *input )
{
    filename *p = input ;
    filename *output = null ;
    if ( use_system_cc ) return ( apply_cc ( input ) ) ;
    while ( p != null ) {
	filename *pn = p->next ;
	p->next = null ;
	if ( p->type == C_SOURCE ) p = do_preproc ( p ) ;
	else if ( p->type == CPP_SOURCE ) p = do_cpp_preproc ( p ) ;
	output = add_filename ( output, p ) ;
	p = pn ;
    }
    return ( output ) ;
}


/*
    APPLY THE TDF PRETTY PRINTER

    This routine applies the TDF pretty printer to the input files,
    input, and returns the corresponding output files.
*/

static filename *apply_pretty
    PROTO_N ( ( input ) )
    PROTO_T ( filename *input )
{
    filename *p = input ;
    filename *output = null ;
    while ( p != null ) {
	filename *pn = p->next ;
	p->next = null ;
	if ( make_tspec ) {
	    if ( p->type == C_SPEC ) p = do_pretty ( p ) ;
        } else if ( p->type == INDEP_TDF ) {
	    if ( make_pretty == 2 ) p = apply_tdf_link ( p ) ;
	    p = do_pretty ( p ) ;
	} else if ( p->type == DEP_TDF ) {
	    p = do_pretty ( p ) ;
	}
	output = add_filename ( output, p ) ;
	p = pn ;
    }
    return ( output ) ;
}


/*
    APPLY THE ARCHIVER TO UNJOIN C SPEC FILES

    This routine scans input for input archives of type t.  It splits these
    into their component files.  For internal archives the contents are
    in the aux field.
*/

static filename *apply_unjoin
    PROTO_N ( ( input, t ) )
    PROTO_T ( filename *input X int t )
{
    filename *p = input ;
    filename *output = null ;
    archive_type = t ;
    while ( p != null ) {
	filename *pn = p->next ;
	p->next = null ;
	if ( p->type == t ) {
	    if ( p->storage == INPUT_FILE ) {
		if ( is_archive ( p->name ) ) p = do_split_arch ( p ) ;
	    } else if ( p->aux != null ) {
		p = p->aux ;
	    }
	}
	output = add_filename ( output, p ) ;
	p = pn ;
    }
    return ( output ) ;
}


/*
    APPLY ALL THE COMPILATION STAGES

    This routine applies all the compilation stages to the input files,
    input, and returns the corresponding output files.
*/

filename *apply_all
    PROTO_N ( ( input ) )
    PROTO_T ( filename *input )
{
    filename *p = input ;

    /* Set up file types */
    if ( allow_specs ) binary_obj_type = BINARY_OBJ_AUX ;

    /* Preprocessing is a special case */
    if ( make_preproc ) return ( apply_preproc ( p ) ) ;

    /* Any TDF archives are split immediately */
    p = apply_split_arch ( input ) ;

    /* Deal with building TDF archive case */
    if ( make_archive ) {
	p = apply_compile ( p, 1 ) ;
	if ( make_complex ) p = apply_build ( p ) ;
	return ( apply_build_arch ( p ) ) ;
    }

    /* Deal with pretty printing case */
    if ( make_pretty ) {
	p = apply_compile ( p, 1 ) ;
	if ( make_complex ) p = apply_build ( p ) ;
	return ( apply_pretty ( p ) ) ;
    }

    /* Deal with building TDF complex */
    if ( make_complex ) {
	p = apply_compile ( p, 1 ) ;
	p = apply_build ( p ) ;
    }

    /* Main compilation phases */
    p = apply_compile ( p, ( int ) checker ) ;
    if ( allow_specs && !stops [ BINARY_OBJ ] ) {
	p = apply_unjoin ( p, BINARY_OBJ ) ;
    }
    p = apply_link ( p ) ;
    return ( p ) ;
}
