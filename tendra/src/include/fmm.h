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

#ifndef TEN_FMM_H
#define TEN_FMM_H

/*
 * Define minimum amount of memory allocated by a call to malloc().
 * This value will be a power of two.
 */
#define	FMM_PAGE_SHIFT	12		/* log2(FMM_PAGE_SIZE) */
#define	FMM_PAGE_SIZE	(1 << FMM_PAGE_SHIFT)
#define	FMM_PAGE_MASK	(FMM_PAGE_SIZE - 1)

/*
 * Memory allocated by objects large than FMM_LARGE_ALLOC will be returned
 * to system after call to fm_free().  Pages allocated for smaller objects
 * are keept around and could be reclaimed by fm_gc().
 *
 * Correct selection of this value affects perfomance and mostly depends
 * on underlying memory allocator.
 *
 * Constraints: FMM_PAGE_SIZE <= FMM_LARGE_ALLOC < SHORT_MAX
 */
#ifndef	FMM_LARGE_ALLOC

#ifdef __WIN32__
#define	FMM_LARGE_ALLOC		512
#elif defined(__FreeBSD__)
#define	FMM_LARGE_ALLOC		1024
#else
#define	FMM_LARGE_ALLOC		1024
#endif

#endif /* FMM_LARGE_ALLOC */

#ifndef	FMM_MIN_ALLOC_SHIFT
#if defined(__alpha__)
#define	FMM_MIN_ALLOC_SHIFT	5	/* 32 bytes */
#else
#define	FMM_MIN_ALLOC_SHIFT	4	/* 16 bytes */
#endif
#endif	/* !FMM_MIN_ALLOC_SHIFT */

#define	FMM_MIN_ALLOC_SIZE	(1 << FMM_MIN_ALLOC_SHIFT)
#define	FMM_BUCKET_COUNT	(FMM_MIN_ALLOC_SHIFT + 16)

#ifdef FS_EMPTY_ARRAYS
#define	FMM_ZERO_ARRAY
#else
#define	FMM_ZERO_ARRAY	0
#endif

struct fmm_freelist;

/*
 * Set of buckets for each size of memory block that is retained
 */
struct fmm_bucket {
	struct fmm_blk_hdr* fb_next;	/* list of free blocks */
	long	fb_pagesize;		/* size of page for this allocator */
	short	fb_blkperpage;		/* number of blocks per bucket page */
	long	fb_blksize;		/* block size, including aux data */
	long	kb_calls;		/* total calls to allocate this size */
	long	fb_totalblk;		/* total number of blocks allocated */
	long	fb_freeblk;		/* number of free blocks */
	long	kb_highwat;		/* high water mark */
	long	kb_couldfree;		/* over high water mark and could free */
};

/*
 * Structure describing details of each memory type
 */
struct fmm_type {
	long 	ft_memuse;		/* total memory held in bytes */
	long	ft_size;		/* sizes used */
	long	ft_inuse;		/* number of blocks in use */
	long	ft_calls;		/* total malloc calls for this type */
	long	ft_maxused;		/* maximum number ever used */
	const char *ft_name;		/* short name */
	const char *ft_shortdesc;	/* short description */
	struct fmm_type *ft_next;	/* next in the list */
};

struct fmm_freelist {
#ifdef FMM_DEBUG
	unsigned long	spare0;
	unsigned long	spare1;
	struct fmm_type*type;
#endif
	struct fmm_blk_hdr *next;	/* next free block in the bucket */
};

struct fmm_blk_hdr {
	struct fmm_page_hdr *fbh_page;	/* back reference to the parent page */
};
#define	FMM_BLK_HDRSZ		(sizeof(struct fmm_blk_hdr))
#define	FMM_BLK_DATA(blkp)	((void*)((blkp) + 1))

struct fmm_page_hdr {
	struct fmm_page_hdr *fph_prev;
	struct fmm_page_hdr *fph_next;
	short	fph_bi;			/* bucket index */
	union {
		unsigned short	freecnt;
		size_t		pagesize;
	} fph_un;
};
#define fph_freecnt fph_un.freecnt
#define fph_pagesize fph_un.pagesize
#define	FMM_PAGE_HDRSZ		(sizeof(struct fmm_page_hdr))
#define	FMM_PAGE_DATA(pp)	((void*)((pp) + 1))

/*
 * A non-zero value indicates an error occured in the fmm function.
 */
extern int fmm_error;

/*
 * fmm_deftype catches all allocations for unknown types
 */
extern struct fmm_type *fmm_deftype;

struct fmm_type* fmm_type_add(const char *, const char *);
void fmm_type_remove(struct fmm_type *);

void *fmm_calloc(size_t, struct fmm_type *);
void *fmm_malloc(size_t, struct fmm_type *);
void *fmm_realloc(void *, size_t, struct fmm_type *);
void fmm_free(void *, struct fmm_type *);
void fmm_freeall(void);

void fmm_stat_by_bucket(void);
void fmm_stat_by_type(void);

/*
 * Some short hand macros
 */
#define	xalloc(size)		fmm_malloc((size), fmm_deftype)
#define	xcalloc(n,size)		fmm_calloc((n) * (size), fmm_deftype)
#define	xmalloc(size)		fmm_malloc((size), fmm_deftype)
#define	xrealloc(ptr, size)	fmm_realloc((ptr), (size), fmm_deftype)
#define	xmalloc_nof(T, N)	((T *)xalloc((long)(N) * (long)sizeof (T)))
#define	xfree(ptr)		fmm_free((ptr), fmm_deftype)

#endif /* !defined(TEN_FMM_H) */

