/* $Id$ */

/*
 * Copyright 2002-2012, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stddef.h>
#include <string.h>

#include <shared/error.h>

#include <reader/externs.h>
#include <reader/table_fns.h>
#include <reader/basicread.h>

#include <construct/installglob.h>
#include <construct/exp.h>
#include <construct/tags.h>
#include <construct/shape.h>

#include <main/flags.h>

#include <refactor/const.h>
#include <refactor/optimise.h>
#include <refactor/refactor_ext.h>

void
rec_inl(exp p)
{
	if (pt(p) != NULL) {
		rec_inl(pt(p));
	}

	inline_exp(father(p));
}

/*
 * This function replaces calls to the strcpy function
 * with a direct mem -> mem copy.
 */
static void
global_opt(dec *dp)
{
	if (!writable_strings && 0 == strcmp(dp->dec_u.dec_val.dec_id, "strcpy")) {
		exp i = dp->dec_u.dec_val.dec_exp;
		exp t;

		for (t = pt(i); t != NULL; t = pt(t)) {
			if (!last(t) && !last(bro(t)) && last(bro(bro(t))) &&
			    name(bro(bro(bro(t)))) == apply_tag &&
			    son(bro(bro(bro(t)))) == t)
			{
				exp dst = bro(t);
				exp src = bro(dst);

				if (name(src) == name_tag && isglob(son(src)) &&
				    isvar(son(src)) && no(son(src)) == 1)
				{
					dec *src_dec = brog(son(src));

					if (!src_dec->dec_u.dec_val.extnamed &&
					    son(src_dec->dec_u.dec_val.dec_exp) != NULL)
					{
						exp src_def = son(son(src));
						shape sha = sh(src_def);

						if (name(src_def) == string_tag &&
						    props(src_def) == 8)
						{
							char *s = nostr(src_def);
							size_t l = shape_size(sha) / 8;
							size_t j;

							for (j = 0; j < l && s[j] != 0; j++)
								;

							if (j < l) {
								exp q;
								exp to_change = bro(src);
								exp idsc = getexp(sh(bro(src)), NULL, 0, dst, NULL, 0, 2, ident_tag);
								exp n1 = getexp(sh(dst), NULL, 0, idsc, NULL, 0, 0, name_tag);
								exp n2 = getexp(sh(dst), NULL, 0, idsc, n1, 0, 0, name_tag);
								exp_list el;

								pt(idsc) = n2;

								q = f_assign(n1, f_contents(sha, src));
								el.start = q;
								el.end = q;
								el.number = 1;

								q = f_sequence(el, n2);
								clearlast(dst);
								bro(dst) = q;
								setfather(idsc, q);
								kill_exp(t, t);
								replace(to_change, idsc, idsc);
								t = pt(i);
							}
						}
					}
				}
			}
		}
	}

	if (!writable_strings && 0 == strcmp(dp->dec_u.dec_val.dec_id, "strlen")) {
		exp i = dp->dec_u.dec_val.dec_exp;
		exp t;

		for (t = pt(i); t != NULL; t = pt(t)) {
			if (!last(t) && last(bro(t)) &&
			    name(bro(bro(t))) == apply_tag &&
			    son(bro(bro(t))) == t)
			{
				exp st = bro(t);

				if (name(st) == name_tag && isglob(son(st)) &&
				    isvar(son(st)) && no(son(st)) == 1)
				{
					dec *src_dec = brog(son(st));
					if (!src_dec->dec_u.dec_val.extnamed &&
					    son(src_dec->dec_u.dec_val.dec_exp) != NULL)
					{
						exp st_def = son(son(st));
						shape sha = sh(st_def);

						if (name(st_def) == string_tag &&
						    props(st_def) == 8)
						{
							char *s = nostr(st_def);
							size_t l = shape_size(sha) / 8;
							size_t j;

							for (j = 0; j < l && s[j] != 0; j++)
								;

							if (j < l) {
								exp to_change = bro(st);
								exp res = getexp(sh(to_change), NULL, 0, NULL, NULL, 0, j, val_tag);
								kill_exp(t, t);
								replace(to_change, res, NULL);
								t = pt(i);
							}
						}
					}
				}
			}
		}
	}
}

void
opt_all_exps(void)
{
	dec *d;

#if 0
	/* take constant expression out of loops */
	if (optim & OPTIM_LOOPCONSTS)
		repeat_consts();
#endif

	if (optim & OPTIM_UNROLL) {
		unroller();
	}

	for (d = top_def; d != NULL; d = d->def_next) {
		exp crt_exp = d->dec_u.dec_val.dec_exp;
		refactor_ext(crt_exp);
		global_opt(d);
	}

	normalised_inlining();

#if 1
	/* take constant expression out of loops */
	if (optim & OPTIM_LOOPCONSTS) {
		repeat_consts();
	}
#endif

	/* replace indexing on loop variable by incremented pointer access */
	if (optim & OPTIM_FORALLS) {
		forall_opt();
	}
}

