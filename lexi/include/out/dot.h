/* $Id$ */

/*
 * Copyright 2008-2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_DOT_OUTPUT_H
#define LEXI_DOT_OUTPUT_H

struct ast;
struct options;

/*
 * Render the generated lexical analyser in Graphviz Dot format.
 * This is a visualisation showing the structure and types of nodes
 * in the trie formed by tokens.
 *
 * The trie is an associative array consisting of hetereogenous nodes
 * keyed by the token definitions mapping to the lexemes yielded per
 * token. For example, a node may be a single letter, or a reference
 * to a group; the intention of this visualisation is to make these
 * distinctions clear.
 */
void
dot_out_all(struct options *opt, struct ast *ast);

#endif

