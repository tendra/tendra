define name
p (enum_tag_name) $->namef
p $$
end

define son
p (enum_tag_name) ($->sonf.e)->namef
p *($$->sonf.e)
end

define bro
p (enum_tag_name) ($->brof.e)->namef
p *($$->brof.e)
end

define pt
p (enum_tag_name) ($->ptf.e)->namef
p *($$->ptf.e)
end

define shape
p (enum_shape_name) $->shf->namef
p $$
end

define uses
p *((USES) ($->ptf.e))
p $$
end

define al2
p (unsigned long) $->ptf.ald->al.al_val.al
p $$
end

define glob
p $->sonf.e->brof.glob->dec_u.dec_val.dec_id
p $$
end

break failer
break alphafail
