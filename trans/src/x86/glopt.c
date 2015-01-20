/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <string.h>

#include <reader/externs.h>
#include <reader/table_fns.h>
#include <reader/basicread.h>

#include <construct/tags.h>
#include <construct/shape.h>
#include <construct/exp.h>
#include <construct/installglob.h>

#include <refactor/glopt.h>

#include <main/flags.h>

/* PROCEDURES */

void glopt
(dec * dp)
{
  if (!writable_strings && !strcmp(dp -> dec_u.dec_val.dec_id, "strcpy"))
   {
     exp i = dp -> dec_u.dec_val.dec_exp;
     exp t = pt(i);
     if (t == NULL)
       return;

     while (1)
      {
        if (!last(t) && !last(bro(t)) && last(bro(bro(t))) &&
            name(bro(bro(bro(t)))) == apply_tag &&
            son(bro(bro(bro(t)))) == t)
          {
            exp dest = bro(t);
            exp source = bro(dest);

            if (name(source) == name_tag && isglob(son(source)) &&
                isvar(son(source)) && no(son(source)) == 1)
              {
                dec * source_dec = brog(son(source));
                if (!source_dec -> dec_u.dec_val.extnamed &&
                    son(source_dec -> dec_u.dec_val.dec_exp)!= NULL)
                  {
                    exp source_def = son(son(source));
                    shape sha = sh(source_def);
                    if (name(source_def) == string_tag &&
                         props(source_def) == 8)
                     {
                       char * s = nostr(source_def);
                       int j;
                       int l = shape_size(sha) / 8;
                       for (j=0; j < l && s[j]!= 0; ++j);
                       if (j < l)
                        {
	                   exp q;
                           exp to_change = bro(source);
	                   exp idsc = getexp(sh(bro(source)), NULL, 0,
                                              dest, NULL,
                                              0, 2, ident_tag);
	                   exp n1 = getexp(sh(dest), NULL, 0, idsc,
                                             NULL, 0, 0,
						 name_tag);
	                   exp n2 = getexp(sh(dest), NULL, 0, idsc, n1,
                                             0, 0, name_tag);
                           exp_list el;

                           pt(idsc) = n2;

                           q = f_assign(n1, f_contents(sha, source));
                           el.start = q;
                           el.end = q;
                           el.number = 1;
                           q = f_sequence(el, n2);
                           clearlast(dest);
                           bro(dest) = q;
                           setfather(idsc, q);
                           kill_exp(t, t);
                           replace(to_change, idsc, idsc);
                           t = i;
                        };
                     };
                  };
              };
          };

        if (pt(t) == NULL)
          return;
        t = pt(t);
      };
   };

  if (!writable_strings && !strcmp(dp -> dec_u.dec_val.dec_id, "strlen"))
   {
     exp i = dp -> dec_u.dec_val.dec_exp;
     exp t = pt(i);
     if (t == NULL)
       return;

     while (1)
      {
        if (!last(t) && last(bro(t)) &&
            name(bro(bro(t))) == apply_tag &&
            son(bro(bro(t))) == t)
          {
            exp st = bro(t);

            if (name(st) == name_tag && isglob(son(st)) &&
                isvar(son(st)) && no(son(st)) == 1)
              {
                dec * source_dec = brog(son(st));
                if (!source_dec -> dec_u.dec_val.extnamed &&
                    son(source_dec -> dec_u.dec_val.dec_exp)!= NULL)
                  {
                    exp st_def = son(son(st));
                    shape sha = sh(st_def);
                    if (name(st_def) == string_tag &&
                         props(st_def) == 8)
                     {
                       char * s = nostr(st_def);
                       int j;
                       int l = shape_size(sha) / 8;
                       for (j=0; j < l && s[j]!= 0; ++j);
                       if (j < l)
                        {
                           exp to_change = bro(st);
                           exp res = getexp(sh(to_change), NULL, 0,
                               NULL, NULL, 0, j, val_tag);
                           kill_exp(t, t);
                           replace(to_change, res, NULL);
                           t = i;
                        };
                     };
                  };
              };
          };

        if (pt(t) == NULL)
          return;
        t = pt(t);
      };
   };



  return;
}
