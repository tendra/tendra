/*
 * Copyright (c) 2003-2004, by Boris Popov
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
 * $TenDRA$
 */

/*
 * FMM is a simple memory manager implemented on top of existing memory allocator.
 * The main goals of FMM are:
 *
 * 	improve allocation speed for small chunks of memory;
 *	classify allocated memory by types;
 *	provide a way to examine dynamic memory usage by memory type;
 *	provide a way to examine dynamic memory usage by memory size;
 *	give the ability to free memory allocated for small objects at once;
 *
 * General idea (and some code) are taken from FreeBSD's 4.x kernel memory manager.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fmm.h"
#include "msgcat.h"
#include "catstd.h"

#if ((FMM_LARGE_ALLOC & (FMM_LARGE_ALLOC - 1)) != 0)
#error "FMM_LARGE_ALLOC is not a power of 2"
#endif

#if (FMM_LARGE_ALLOC > FMM_MIN_ALLOC_SIZE * 32768)
#error "FMM_LARGE_ALLOC too big"
#endif

#ifdef FMM_DEBUG
#define	FMM_SIGNATURE	0xdeadc0de
#define	FMM_SIGNSIZE	64
#endif

#define	BLK2FL(blkp)	((struct fmm_freelist*)FMM_BLK_DATA(blkp))
#define	ADDR2BLK(addr)	((struct fmm_blk_hdr *)(addr) - 1)

struct fmm_type *fmm_deftype, *fmm_freetype;

/*
 * An array of buckets for each memory size
 */
static struct fmm_bucket bucket[FMM_BUCKET_COUNT];

/*
 * List of allocation types
 */
static struct fmm_type *fmm_typelist;

/*
 * List of all allocated pages with sizes less or equal than FMM_LARGE_ALLOC
 */
static struct fmm_page_hdr *fmm_pagelist;

static int fmm_initialized;

static void
fmm_init(void)
{
	struct fmm_bucket *fbp;
	unsigned long bsize, blksize, pagesize;
	short bi, blkperpage;

	fbp = bucket;
	for (bi = 0, bsize = 1; bi < FMM_BUCKET_COUNT; bi++, bsize <<= 1, fbp++) {
		if (bsize > FMM_LARGE_ALLOC) {
			blkperpage = 1;
			pagesize = 0;
			blksize = bsize;
		} else {
			blksize = (bsize + FMM_BLK_HDRSZ);
			blkperpage = (short)((FMM_PAGE_SIZE - FMM_PAGE_HDRSZ) / blksize);
			if (blkperpage == 1)
				blkperpage++;
			pagesize = FMM_PAGE_HDRSZ + blksize * blkperpage;
		}
		fbp->fb_blkperpage = blkperpage;
		fbp->fb_pagesize = pagesize;
		fbp->fb_blksize = blksize;
		fbp->kb_highwat = 5 * blkperpage;
	}
	fmm_initialized = 1;
	fmm_deftype = fmm_type_add("Untyped", "General memory");
}

struct fmm_type*
fmm_type_add(const char *name, const char *desc)
{
	struct fmm_type *ftp;

	if (!fmm_initialized)
		fmm_init();
	ftp = calloc(1, sizeof(*ftp));
	if (ftp == NULL)
		return NULL;
	ftp->ft_name = name;
	ftp->ft_shortdesc = desc;
	ftp->ft_next = fmm_typelist;
	fmm_typelist = ftp;
	return ftp;
}


void
fmm_type_remove(struct fmm_type *ftp)
{
	struct fmm_type *f;
#ifdef FMM_DEBUG
	struct fmm_bucket *fbp;
	struct fmm_blk_hdr *blkp;
	struct fmm_freelist *freep;
	short bi;
#endif

#ifdef FMM_DEBUG
	for (bi = 0, fbp = bucket; bi < FMM_BUCKET_COUNT; bi++, fbp++) {
		blkp = fbp->fb_next;
		while (blkp) {
			freep = BLK2FL(blkp);
			if (freep->type == ftp)
				freep->type = fmm_freetype;
			blkp = freep->next;
		}
	}
	if (ftp->ft_memuse != 0)
		MSG_fmm_frt_still_allocated(ftp->ft_memuse, ftp->ft_name);
#endif

	if (ftp != fmm_typelist) {
		for (f = fmm_typelist; f->ft_next; f = f->ft_next) {
			if (f->ft_next == ftp) {
				f->ft_next = ftp->ft_next;
				break;
			}
		}
	} else
		fmm_typelist = ftp->ft_next;
	free(ftp);
}

static short
size2bucket(size_t size)
{
	if (size <= FMM_MIN_ALLOC_SIZE * 128) {
		if (size <= FMM_MIN_ALLOC_SIZE * 8) {
			if (size <= FMM_MIN_ALLOC_SIZE * 2) {
				if (size <= FMM_MIN_ALLOC_SIZE)
					return FMM_MIN_ALLOC_SHIFT + 0;
				return FMM_MIN_ALLOC_SHIFT + 1;
			}
			if (size <= FMM_MIN_ALLOC_SIZE * 4) {
				return FMM_MIN_ALLOC_SHIFT + 2;
			}
			return FMM_MIN_ALLOC_SHIFT + 3;
		} else if (size <= FMM_MIN_ALLOC_SIZE * 32) {
			if (size <= FMM_MIN_ALLOC_SIZE * 16)
				return FMM_MIN_ALLOC_SHIFT + 4;
			return FMM_MIN_ALLOC_SHIFT + 5;
		} else if (size <= FMM_MIN_ALLOC_SIZE * 64)
			return FMM_MIN_ALLOC_SHIFT + 6;
		return FMM_MIN_ALLOC_SHIFT + 7;
	}
	if (size <= FMM_MIN_ALLOC_SIZE * 2048) {
		if (size <= FMM_MIN_ALLOC_SIZE * 512) {
			if (size <= FMM_MIN_ALLOC_SIZE * 256)
				return FMM_MIN_ALLOC_SHIFT + 8;
			return FMM_MIN_ALLOC_SHIFT + 9;
		}
		if (size <= FMM_MIN_ALLOC_SIZE * 1024)
			return FMM_MIN_ALLOC_SHIFT + 10;
		return FMM_MIN_ALLOC_SHIFT + 11;
	}
	if (size <= FMM_MIN_ALLOC_SIZE * 8192) {
		if (size <= FMM_MIN_ALLOC_SIZE * 4096)
			return FMM_MIN_ALLOC_SHIFT + 12;
		return FMM_MIN_ALLOC_SHIFT + 13;
	}
	if (size <= FMM_MIN_ALLOC_SIZE * 16384)
		return FMM_MIN_ALLOC_SHIFT + 14;
	return FMM_MIN_ALLOC_SHIFT + 15;
}

#ifdef FMM_DEBUG
static void
fmm_datamod(struct fmm_freelist *fp, struct fmm_type *ftp, size_t size,
	unsigned long *data, unsigned long expect)
{
	MSG_fmm_data_modified((void *)fp, ftp->ft_name,
		(long)(data - (unsigned long *)fp), (long)size, *data, expect);
}
#endif

/*
 * Allocate a block of memory.
 */
void *
fmm_malloc(size_t size, struct fmm_type *ftp)
{
	struct fmm_bucket *fbp;
	struct fmm_page_hdr *pp, *opp;
	struct fmm_blk_hdr *blkp;
	struct fmm_freelist *freep;
	long allocsize, sizeup;
	short bi, blkcnt;
	char *cp;
#ifdef FMM_DEBUG
	unsigned long *lp;
	int copysize, cc;
#endif

	if (!fmm_initialized)
		fmm_init();

	bi = size2bucket(size);
	fbp = bucket + bi;
	sizeup = 1 << bi;

	ftp->ft_size |= sizeup;
#ifdef FMM_DEBUG
	copysize = (sizeup < FMM_SIGNSIZE ? sizeup : FMM_SIGNSIZE) / sizeof(long);
#endif
	if (fbp->fb_next == NULL) {
		if (size > FMM_LARGE_ALLOC)
			allocsize = FMM_PAGE_HDRSZ + FMM_BLK_HDRSZ + size;
		else
			allocsize = fbp->fb_pagesize;
		pp = (struct fmm_page_hdr*)malloc(allocsize);
		if (pp == NULL) {
			MSG_fmm_malloc_failed(size);
			/*NOTREACHED*/
			return NULL;
		}
		pp->fph_bi = bi;
		pp->fph_prev = NULL;
		opp = fmm_pagelist;
		if (opp)
			opp->fph_prev = pp;
		pp->fph_next = opp;
		fmm_pagelist = pp;
		blkcnt = fbp->fb_blkperpage;
		fbp->fb_totalblk += blkcnt;
		if (size > FMM_LARGE_ALLOC) {
			pp->fph_pagesize = allocsize;
			ftp->ft_memuse += allocsize;
			blkp = (struct fmm_blk_hdr*)FMM_PAGE_DATA(pp);
			blkp->fbh_page = pp;
			goto out;
		}
		pp->fph_freecnt = blkcnt;
		fbp->fb_freeblk += blkcnt;
		cp = FMM_PAGE_DATA(pp);
		fbp->fb_next = (struct fmm_blk_hdr*)cp;
		for (;;) {
			blkp = (struct fmm_blk_hdr*)cp;
			blkp->fbh_page = pp;
			freep = BLK2FL(blkp);
#ifdef FMM_DEBUG
			/*
			 * Copy in known text to detect modification
			 * after freeing.
			 */
			for (cc = 0, lp = (unsigned long *)freep; cc < copysize; cc++, lp++)
				*lp = FMM_SIGNATURE;
			freep->type = fmm_freetype;
#endif /* FMM_DEBUG */
			if (--blkcnt == 0)
				break;
			cp += fbp->fb_blksize;
			freep->next = (struct fmm_blk_hdr*)cp;
		}
		freep->next = NULL;
	}
	blkp = (struct fmm_blk_hdr *)fbp->fb_next;
	freep = BLK2FL(blkp);
	fbp->fb_next = freep->next;
#ifdef FMM_DEBUG
	if (freep->spare0 != FMM_SIGNATURE)
		fmm_datamod(freep, freep->type, size, &freep->spare0, FMM_SIGNATURE);
	if (freep->spare1 != FMM_SIGNATURE)
		fmm_datamod(freep, freep->type, size, &freep->spare1, FMM_SIGNATURE);
	lp = (unsigned long *)&freep->next;
	for (++lp, cc = sizeof(*freep); cc < copysize; cc++, lp++) {
		if (*lp == FMM_SIGNATURE)
			continue;
		fmm_datamod(freep, freep->type, size, lp, FMM_SIGNATURE);
		break;
	}
	freep->spare0 = 0;
#endif /* FMM_DEBUG */
	pp = blkp->fbh_page;
	if (pp->fph_bi != bi)
		MSG_fmm_wrong_bucket();
	if (pp->fph_freecnt == 0)
		MSG_fmm_lost_data();
	pp->fph_freecnt--;
	fbp->fb_freeblk--;
	ftp->ft_memuse += sizeup;
out:
	fbp->kb_calls++;
	ftp->ft_inuse++;
	ftp->ft_calls++;
	if (ftp->ft_memuse > ftp->ft_maxused)
		ftp->ft_maxused = ftp->ft_memuse;
	cp = FMM_BLK_DATA(blkp);
	return (void *)cp;
}

/*
 * Change size of previously allocated block.
 */
void *
fmm_realloc(void *addr, size_t size, struct fmm_type *ftp)
{
	struct fmm_blk_hdr *blkp;
	struct fmm_page_hdr *pp, *prevp, *nextp;
	unsigned long allocsize;
	void *newaddr;

	/* realloc(NULL, ...) is equivalent to malloc(...) */
	if (addr == NULL)
		return fmm_malloc(size, ftp);

	/* Get the size of the original block */
	blkp = ADDR2BLK(addr);
	pp = blkp->fbh_page;
	allocsize = 1 << pp->fph_bi;
	if (allocsize > FMM_LARGE_ALLOC) {
		allocsize = FMM_PAGE_HDRSZ + FMM_BLK_HDRSZ + size;;
		prevp = pp->fph_prev;
		nextp = pp->fph_next;
		ftp->ft_memuse -= pp->fph_pagesize;
		pp = realloc(pp, allocsize);
		if (pp == NULL) {
			MSG_fmm_malloc_failed(size);
			/*NOTREACHED*/
			return NULL;
		}
		pp->fph_pagesize = allocsize;
		ftp->ft_memuse += allocsize;
		blkp = (struct fmm_blk_hdr*)FMM_PAGE_DATA(pp);
		blkp->fbh_page = pp;
		if (prevp)
			prevp->fph_next = pp;
		else
			fmm_pagelist = pp;
		if (nextp)
			nextp->fph_prev = pp;
		if (ftp->ft_memuse > ftp->ft_maxused)
			ftp->ft_maxused = ftp->ft_memuse;
		return FMM_BLK_DATA(blkp);
	}
	/* Reuse the original block if appropriate */
	if (size <= allocsize &&
	    (size > (allocsize / 2) || allocsize == FMM_MIN_ALLOC_SIZE))
		return addr;

	newaddr = fmm_malloc(size, ftp);
	/* Copy over original contents */
	memcpy(newaddr, addr, allocsize);
	fmm_free(addr, ftp);
	return newaddr;
}

/*
 * Allocate block of memory and fill it with zeros
 */
void *
fmm_calloc(size_t size, struct fmm_type *ftp)
{
	void *rp;

	rp = fmm_malloc(size, ftp);
	if (rp)
		memset(rp, 0, size);
	return rp;
}

/*
 * Free a block of memory allocated by fm_malloc().
 */
void
fmm_free(void *addr, struct fmm_type *ftp)
{
	struct fmm_blk_hdr *blkp;
	struct fmm_page_hdr *pp, *opp;
	struct fmm_bucket *fbp;
	struct fmm_freelist *freep;
	long size;
#ifdef FMM_DEBUG
	struct fmm_blk_hdr *bp;
	struct fmm_freelist *fp;
	unsigned long *lp, cc, copysize;
#endif

	if (addr == NULL)
		return;		/* nothing special */

	blkp = ADDR2BLK(addr);
	pp = blkp->fbh_page;
	size = 1 << pp->fph_bi;
	fbp = bucket + pp->fph_bi;
	if (size > FMM_LARGE_ALLOC) {
		ftp->ft_memuse -= pp->fph_pagesize;
		if (fmm_pagelist == pp) {
			opp = pp->fph_next;
			fmm_pagelist = opp;
			if (opp)
				opp->fph_prev = NULL;
		} else {
			opp = pp->fph_next;
			pp->fph_prev->fph_next = opp;
			if (opp)
				opp->fph_prev = pp->fph_prev;
		}
		free(pp);
		ftp->ft_inuse--;
		fbp->fb_totalblk--;
		return;
	}
	freep = BLK2FL(blkp);
#ifdef FMM_DEBUG
	/*
	 * Check for multiple frees. Use a quick check to see if
	 * it looks free before laboriously searching the freelist.
	 */
	if (freep->spare0 == FMM_SIGNATURE) {
		bp = fbp->fb_next;
		while (bp) {
			fp = BLK2FL(bp);
			if (fp->spare0 != FMM_SIGNATURE)
				MSG_fmm_free_modified(fp);
			else if (addr == (void *)fp)
				MSG_fmm_multiple_free(addr);
			bp = fp->next;
		}
	}
	/*
	 * Copy in known text to detect modification after freeing
	 * and to make it look free. Also, save the type being freed
	 * so we can list likely culprit if modification is detected
	 * when the object is reallocated.
	 */
	copysize = (size < FMM_SIGNSIZE ? size : FMM_SIGNSIZE) / sizeof(long);
	for (cc = 0, lp = (unsigned long *)freep; cc < copysize; cc++, lp++)
		*lp = FMM_SIGNATURE;
	freep->type = ftp;
#endif /* FMM_DEBUG */
	pp->fph_freecnt++;
	if (pp->fph_freecnt >= fbp->fb_blkperpage) {
		if (pp->fph_freecnt > fbp->fb_blkperpage)
			MSG_fmm_multiple_free(NULL);
		else if (fbp->fb_freeblk > fbp->kb_highwat)
			fbp->kb_couldfree++;
	}
	fbp->fb_freeblk++;
	ftp->ft_memuse -= size;
	ftp->ft_inuse--;
	if (fbp->fb_next == NULL) {
		freep->next = NULL;
	} else {
		freep->next = fbp->fb_next;
	}
	fbp->fb_next = blkp;
}

/*
 * Free all allocated pages.
 * Note: this procedure doesn't maintain statistics counters.
 */
void
fmm_freeall(void)
{
	struct fmm_bucket *fbp;
	struct fmm_page_hdr *pp, *nextp;

	for (pp = fmm_pagelist; pp; pp = nextp) {
		nextp = pp->fph_next;
		fbp = pp->fph_bi + bucket;
		fbp->fb_next = 0;
		free(pp);
	}
	fmm_pagelist = NULL;
}


void
fmm_stat_by_bucket(void)
{
	struct fmm_bucket *fbp;
	long size;
	int i;

	printf("\nMemory usage statistics by bucket size:\n");
	printf("Size   In Use   Free   Requests  HighWater  Couldfree\n");
	for (i = FMM_MIN_ALLOC_SHIFT, fbp = bucket + i; i < FMM_BUCKET_COUNT; i++, fbp++) {
		if (fbp->kb_calls == 0)
			continue;
		size = 1 << i;
		if (size < 1024)
			printf("%4ld", size);
		else
			printf("%3ldK", size >> 10);
		printf(" %8ld %6ld %10ld %7ld %10ld\n",
			fbp->fb_totalblk - fbp->fb_freeblk,
			fbp->fb_freeblk, fbp->kb_calls,
			fbp->kb_highwat, fbp->kb_couldfree);
	}

}

void
fmm_stat_by_type(void)
{
	struct fmm_type *ftp;
	int j, first;

	printf("\nMemory statistics by type\n");
	(void)printf(
  "         Type   InUse   MemUse  HighUse Requests  Size(s)\n");
	for (ftp = fmm_typelist; ftp; ftp = ftp->ft_next) {
		if (ftp->ft_calls == 0)
			continue;
		printf("%13s%8ld%8ldK%8ldK%9ld",
		    ftp->ft_name,
		    ftp->ft_inuse, (ftp->ft_memuse + 1023) / 1024,
		    (ftp->ft_maxused + 1023) / 1024,
		    ftp->ft_calls);
		first = 1;
		for (j =  1 << FMM_MIN_ALLOC_SHIFT; j < (1 << (FMM_BUCKET_COUNT)); j <<= 1) {
			if ((ftp->ft_size & j) == 0)
				continue;
			if (first)
				printf("  ");
			else
				printf(",");
			if (j < 1024)
				printf("%d", j);
			else
				printf("%dK", j >> 10);
			first = 0;
		}
		printf("\n");
	}
}



