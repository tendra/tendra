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


/* 	$Id: version.h,v 1.1.1.1 1998/01/17 15:56:01 release Exp $	 */
/*
  version.h

  This file contains the current version number of the alpha installer
*/

/*
$Log: version.h,v $
 * Revision 1.1.1.1  1998/01/17  15:56:01  release
 * First version to be checked into rolling release.
 *
 * Revision 1.56  1997/09/05  12:26:01  john
 * New version
 *
 * Revision 1.55  1996/11/27  17:58:04  john
 * Changed case behaviour
 *
 * Revision 1.54  1996/06/20  09:15:34  john
 * Changed register allocation
 *
 * Revision 1.53  1996/06/19  15:15:15  john
 * Fix for discarded operations
 *
 * Revision 1.52  1996/03/25  14:55:59  john
 * introduced do_extern_adds
 *
 * Revision 1.51  1996/03/18  17:03:15  john
 * Fix to rem operation
 *
 * Revision 1.50  1996/03/15  11:19:58  john
 * Fix to char & short ops
 *
 * Revision 1.49  1996/02/29  17:36:41  john
 * Fix to shift op
 *
 * Revision 1.48  1996/02/19  09:25:30  john
 * Fixed postlude with call
 *
 * Revision 1.47  1996/02/15  09:58:56  john
 * Fixes to initialisation procedures & general procs
 *
 * Revision 1.46  1996/01/23  16:59:36  john
 * Fix to diagnostics
 *
 * Revision 1.45  1996/01/17  09:32:02  john
 * Fix to diagnostics
 *
 * Revision 1.44  1995/12/06  13:51:27  john
 * Minor changes
 *
 * Revision 1.43  1995/12/04  09:14:25  john
 * Fix to diagnostics
 *
 * Revision 1.42  1995/11/23  16:56:19  john
 * Fix for diagnostics (parameters to functions)
 *
 * Revision 1.41  1995/11/21  17:01:42  john
 * Change to general procs
 *
 * Revision 1.40  1995/11/14  15:40:36  john
 * Implemented dynamic initialisations
 *
 * Revision 1.39  1995/11/13  12:45:21  john
 * Minor change
 *
 * Revision 1.38  1995/10/27  16:22:43  john
 * Change to general procs
 *
 * Revision 1.37  1995/10/27  13:00:06  john
 * Fix to general procs
 *
 * Revision 1.36  1995/10/24  09:29:02  john
 * Fix for bootstrap
 *
 * Revision 1.35  1995/10/19  16:37:25  john
 * Fix to error treatments
 *
 * Revision 1.34  1995/10/18  09:30:05  john
 * Fix to round_tag
 *
 * Revision 1.33  1995/10/16  12:09:33  john
 * Change to alignment calculation
 *
 * Revision 1.32  1995/09/29  15:53:50  john
 * Changes for general procs
 *
 * Revision 1.31  1995/09/22  16:03:02  john
 * Changed special id's
 *
 * Revision 1.30  1995/09/21  15:42:51  john
 * Various improvements to error handling
 *
 * Revision 1.29  1995/09/20  10:47:19  john
 * Change to common flag
 *
 * Revision 1.28  1995/09/15  16:24:51  john
 * New exception handling
 *
 * Revision 1.27  1995/09/13  16:33:56  john
 * Added special_tag to scan
 *
 * Revision 1.26  1995/09/13  11:03:59  john
 * Compilation changes
 *
 * Revision 1.25  1995/09/13  08:23:59  john
 * Addition for exception handling
 *
 * Revision 1.24  1995/09/07  12:30:12  john
 * Changes to general procs
 *
 * Revision 1.23  1995/09/06  09:01:21  john
 * removed old command line argument parsing
 *
 * Revision 1.22  1995/09/04  16:33:01  john
 * Fix to general procs
 *
 * Revision 1.21  1995/09/01  09:11:06  john
 * Fix to mult_tag
 *
 * Revision 1.20  1995/08/31  15:48:00  john
 * Added fmax_tag
 *
 * Revision 1.19  1995/08/30  16:15:40  john
 * Various fixes
 *
 * Revision 1.18  1995/08/23  16:06:46  john
 * New version
 *
 * Revision 1.17  1995/08/21  13:38:46  john
 * Changed handling of caller_tag
 *
 * Revision 1.16  1995/08/21  10:46:13  john
 * Added trap_tag
 *
 * Revision 1.15  1995/08/21  09:02:46  john
 * Changed include files
 *
 * Revision 1.14  1995/08/04  15:51:50  john
 * Fixes to general proc handling
 *
 * Revision 1.13  1995/07/27  10:10:23  john
 * Changes to register needs & general procs
 *
 * Revision 1.12  1995/07/04  09:08:22  john
 * Some fixes to spec 4.0 features
 *
 * Revision 1.11  1995/06/30  08:02:26  john
 * Fixes to tail_call
 *
 * Revision 1.10  1995/06/28  10:28:12  john
 * Improved diagnostic support + minor bug fixes
 *
 * Revision 1.9  1995/06/21  14:26:28  john
 * Reformatting & change to spec 4
 *
 * Revision 1.8  1995/06/15  08:36:20  john
 * New version : support for 'trap' error treatment and fix to general_procs
 *
 * Revision 1.7  1995/05/25  15:34:05  john
 * New patch : fix to register allocation in reg_alloc.c
 *
 * Revision 1.6  1995/05/23  13:31:36  john
 * New version
 *
 * Revision 1.5  1995/05/16  10:56:41  john
 * Changes for spec 3.1
 *
 * Revision 1.4  1995/04/10  14:15:32  john
 * Added new division code, + other minor changes
 *
 * Revision 1.3  1995/04/07  11:06:41  john
 * Changes to floating point exceptions and more scheduling support.
 *
 * Revision 1.2  1995/03/29  10:32:52  john
 * New version: scheduling & floating point improvements
 *
 * Revision 1.1.1.1  1995/03/23  10:39:37  john
 * Entered into CVS
 *
 * Revision 1.21  1995/03/23  10:21:58  john
 * Fixes for AVS test suite
 *
 * Revision 1.20  1995/03/09  14:09:18  john
 * Patch: fix to test_tag
 *
 * Revision 1.19  1995/03/08  12:03:33  john
 * First version using scheduler modification
 *
 * Revision 1.18  1995/02/09  17:17:55  john
 * Fix to implementation of local_free construct
 *
 * Revision 1.17  1995/01/31  11:23:57  john
 * Reformatting and improved portability
 *
 * Revision 1.16  1995/01/20  13:44:22  john
 * Patch for Change request CR_93.AVS Flow return
 *
 * Revision 1.15  1995/01/17  14:00:25  john
 * New patch
 *
 * Revision 1.14  1995/01/12  15:11:17  john
 * New patch
 *
 * Revision 1.13  1995/01/12  15:11:05  john
 * New patch
 *
*/

#ifndef VERSION_H
#define VERSION_H

/* installer version */
#define target_version 2
#define target_revision	4
#define target_patchlevel 11
#define target_system "Digital Unix (OSF/1)"

#ifdef RELEASE
#define RELEASE_INFO RELEASE
#else
#define RELEASE_INFO "private"
#endif



#endif

