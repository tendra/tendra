/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */

#include <stdlib.h>

#include "xalloc/xalloc.h"
#include "exds/common.h"
#include "exds/dstring.h"
#include "localnames.h"
#include "adt.h"

LocalNamesT* 
localnames_create(char c)
{
	LocalNamesT* locals = xmalloc_nof(LocalNamesT, 1);
	
	locals->c    = c;
	locals->next = NULL;
	locals->opt  = NULL;
	locals->type = NULL;

	return locals;
}

/* 
	Adding an entry to the trie
	
	This functions adds key "name" with value "type" to the trie.
	It return 1 upon success and 0 upon failure.
*/
int
localnames_add_nstring(LocalNamesT** locals, NStringT* name, struct EntryT* type)
{
	unsigned int i;
	/* TODO assert(locals!=NULL) */
	LocalNamesT** crt = locals;
	EntryT** entry ;
	char* p = nstring_contents(name); /* BEWARE: not zero terminated! */
	for (i = 0; i < nstring_length(name); ++i) {
		while ( (*crt)!=NULL && ((*crt)->c < p[i]) )
			crt=&((*crt)->opt);
		if ( (*crt==NULL) || ((*crt)->c != p[i])) {
			*crt = localnames_create(p[i]);
		}
		entry = &((*crt)->type);
		crt   = &((*crt)->next);
	}
	if(entry == NULL) {
		*entry = type;
		return 1; /* Success */
	} else {
		return 0; /* Failure: key already present in trie */
	}
}

/* 
	This function search for an entry name in the trie
	
	This functions search key "name" and return its value.
	It returns NULL if it cannot find the value.
*/
struct EntryT* 
localnames_get_type(LocalNamesT* locals, NStringT* name)
{
	unsigned int i;
	LocalNamesT* crt = locals;
	EntryT* entry;
	char* p = nstring_contents(name); /* BEWARE: not zero terminated! */
	for (i = 0; i < nstring_length(name); ++i) {
		while ( crt != NULL && (crt->c < p[i]) )
			crt=crt->opt;
		if(crt == NULL || crt->c != p[i])
			return NULL;
		else {
			entry = crt->type;
			crt = crt->next;
		}
	}
	return entry;
	
}

