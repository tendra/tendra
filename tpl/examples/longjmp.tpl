/* $Id$ */

/* A test for long jumps */

Iddec printf:proc;

Proc f = bottom(env:pointer(frame_alignment), lab:pointer(code_alignment) )
{
    long_jump(* env, * lab)
};

String s1 = "Should not reach here\n";
String s2 = "long-jump OK\n";

Proc main = top()
Labelled{
	f[bottom](current_env, make_local_lv(l));
	printf[top](s1);	/* should never reach here */
	return(make_top)

| :l:
	printf[top](s2);
	return(make_top)
};

Keep (main)

