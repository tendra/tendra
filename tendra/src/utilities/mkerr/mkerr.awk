#!/usr/bin/awk -f

#
#  Copyright (c) 2003-2004, Boris Popov
#  Copyright (c) 2004, The Tendra Project <http://www.ten15.org/>
#  All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice unmodified, this list of conditions, and the following
#    disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# $TenDRA$
#

function usage()
{
	print "usage: " script_name " [-d defnfile] [-l declfile] [-n numfile]";
	print "            [-u usagefile] [-c compfile] [-hv] srcfile [srcfile...]";
	print "where compfile	compound .c file";
	print "      defnfile   errors definition file name";
	print "      declfile   errors declaration file name";
	print "      numfile    errors numbers file name";
	print "      usagefile  errors usage file name";
	print "      -h         this help screen";
	print "      -v         increase debug level";
	exit 1;
}

function chr(c)
{
	return sprintf("%c", c + 0)
}

function warn(msg)
{
	print "Warning: ", msg > "/dev/stderr";
}

function err(msg)
{
	print "Error: ", msg > "/dev/stderr";
	exit(1);
}

function errsrc(msg)
{
	err(srcfile ":" lineno ":" linepos ": " msg);
}

function debug(level, msg)
{
	if (verbose >= level)
		print "Debug: ", msg > "/dev/stderr";
}

function err_syntax()
{
	errsrc("Syntax error.");
}

function err_unexpected_eof()
{
	errsrc("Unexpected end of file.");
}

function printc(str)
{
	print str > outfilename;
}

function lex_get_char()
{
	while (1) {
		if (linepos > linelen) {
			if ((getline < srcfile) <= 0) {
				lex_eof = 1;
				return 0;
			}
			lineno++;
			linepos = 1;
			sub(/[ 	]+$/, "");	# remove trailing whitespace
			linelen = length();
			if (incomment) {
				comment = comment "\n";
				continue;
			}
			sub(/^[ 	]+/, "");	# remove leading whitespace
			linelen = length();
			ch = " ";
			return 1;
		}
		ch = substr($0, linepos, 1);
		linepos++;
		if (linepos <= linelen)
			nextch = substr($0, linepos, 1);
		else
			nextch = "";
		if (incomment) {
			if (ch == "*" && nextch == "/") {
				comment = comment "*/\n";
				incomment = 0;
				if (!have1st_comment) {
					first_comment = comment;
					have1st_comment = 1;
				}
				ch = " ";	# treat comments as single whitespace
				nextch = " ";
				linepos++;
				return 1;
			}
			comment = comment ch;
			continue;
		}
		if (!instring && (ch == "/" && nextch == "*")) {
			if (incomment)
				errsrc("Nested comments not allowed.");
			comment = "/*";
			incomment = 1;
			continue;
		}
		if (ch == "\"") {
			instring = instring ? 0 : 1;
		}
		return 1;
	}
}

function lex_reset()
{
	lex_eof = 0;
	lineno = 0;
	linepos = 1;
	linelen = 0;
	ch = " ";
	instring = 0;
	ttUnknown = 0;
	ttIdent = 1;
	ttString = 2;
	ttOr = 3;
	ttColon = 4;
	ttComma = 5;
	ttKW_DBNAME = 6;
	ttOpenRound = 7;
	ttCloseRound = 8;
	ttOpenBrace = 9;
	ttCloseBrace = 10;
	ttEqual = 11;
	ttArrow = 12;
	ttKW_RIG = 13;
	ttKW_PREFIX = 14;
	ttKW_TYPES = 15;
	ttKW_PROPERTIES = 16;
	ttKW_KEYS = 17;
	ttKW_KEY = 18;
	ttKW_USAGE = 19;
	ttKW_ENTRIES = 20;
	ttKW_COMP_OUT = 21;
	ttKW_FROM_COMP = 22;
	ttKW_FROM_DB = 23;
	ttKW_GLOBALS = 24;
	lex_keywords["DATABASE_NAME"] = ttKW_DBNAME;
	lex_keywords["RIG"] = ttKW_RIG;
	lex_keywords["PREFIX"] = ttKW_PREFIX;
	lex_keywords["TYPES"] = ttKW_TYPES;
	lex_keywords["PROPERTIES"] = ttKW_PROPERTIES;
	lex_keywords["KEYS"] = ttKW_KEYS;
	lex_keywords["KEY"] = ttKW_KEY;
	lex_keywords["USAGE"] = ttKW_USAGE;
	lex_keywords["ENTRIES"] = ttKW_ENTRIES;
	lex_keywords["GLOBALS"] = ttKW_GLOBALS;
	lex_keywords["compiler_output"] = ttKW_COMP_OUT;
	lex_keywords["from_compiler"] = ttKW_FROM_COMP;
	lex_keywords["from_database"] = ttKW_FROM_DB;
	lex_tt = ttUnknown;
	lex_token = "";
	lex_unget = 0;
}

function lex_get_token(expected)
{
	if (lex_unget) {
		lex_unget = 0;
		if (expected != "" && expected != lex_tt)
			errsrc("Unexpected token (" lex_tt " != " expected ").");	# todo: elaborate more
		return 1;
	}
	lex_tt = ttUnkown;
	lex_token = "";
	while (ch ~ /[	 ]/)
		if (!lex_get_char()) {
			if (expected != "")
				err_unexpected_eof();
			return 0;
		}
	if (ch == "\"") {
		lex_tt = ttString;
		for (;;) {
			if (!lex_get_char())
				errsrc("Unterminated string constant");
			if (ch == "\"")
				break;
			lex_token = lex_token ch;
		}
		lex_get_char();
	} else if (ch ~ /[A-Za-z_]/) {
		for (;;) {
			lex_token = lex_token ch;
			if (!lex_get_char())
				break;
			if (ch !~ /[A-Za-z0-9_]/)
				break;
		}
		if (lex_token in lex_keywords) {
			lex_tt = lex_keywords[lex_token];
		} else
			lex_tt = ttIdent;
	} else if (ch == "|") {
		lex_tt = ttOr;
		lex_token = ch;
		lex_get_char();
	} else if (ch == ":") {
		lex_tt = ttColon;
		lex_token = ch;
		lex_token = ch;
		lex_get_char();
	} else if (ch == ",") {
		lex_tt = ttComma;
		lex_token = ch;
		lex_get_char();
	} else if (ch == "{") {
		lex_tt = ttOpenBrace;
		lex_token = ch;
		lex_get_char();
	} else if (ch == "}") {
		lex_tt = ttCloseBrace;
		lex_token = ch;
		lex_get_char();
	} else if (ch == "(") {
		lex_tt = ttOpenRound;
		lex_token = ch;
		lex_get_char();
	} else if (ch == ")") {
		lex_tt = ttCloseRound;
		lex_token = ch;
		lex_get_char();
	} else if (ch == "=") {
		lex_tt = ttEqual;
		lex_token = ch;
		lex_get_char();
	} else if (ch == "-") {
		if (!lex_get_char() || ch != ">")
			errsrc("'>' expected, but '" ch "' found.");
		lex_tt = ttArrow;
		lex_token = "->";
		lex_get_char();
	} else
		errsrc("Lexer error.");
	if (expected != ""  && expected != lex_tt)
		errsrc("Unexpected token (" lex_tt " != " expected ").");	# todo: elaborate more
	return 1;
}

function lex_unget_token()
{
	lex_unget = 1;
}

#
# Syntax: DATABASE_NAME: dbname [| altdbname]
#
function process_database()
{
	if (db_defined)
		errsrc("Database name can be defined only once.");
	lex_get_token(ttIdent);
	db_name = lex_token;
	lex_get_token();
	if (lex_tt == ttOr) {
		lex_get_token(ttIdent);
		db_name_alt = lex_token;
	} else {
		lex_unget_token();
		db_name_alt = db_name;
	}
	db_defined = 1;
	debug(1, "Database name: " db_name " | " db_name_alt);
}

#
# Syntax: RIG: rig_name
#
# Although we accept the "RIG" keyword, its value never used.
#
function process_rig()
{
	lex_get_token(ttIdent);
	rig_name = lex_token;
	debug(1, "Rig name: " rig_name);
}

#
# Syntax:
# PREFIX: compiler_output -> PX1  from_compiler -> PX2  from_database -> PX3
#
function process_prefix()
{
	if (prefix_defined)
		errsrc("Prefixes can be defined only once.");
	for (;;) {
		lex_get_token();
		pxdst = lex_tt;
		if (pxdst != ttKW_COMP_OUT && pxdst != ttKW_FROM_COMP && pxdst != ttKW_FROM_DB) {
			lex_unget_token();
			return;
		}
		px_dest = lex_token;
		lex_get_token(ttArrow);
		lex_get_token(ttIdent);
		px_val = lex_token;
		debug(1, "Prefix: " px_dest " -> " px_val);
		if (pxdst == ttKW_COMP_OUT) {
			rig_comp_output = px_val;
		} else if (pxdst == ttKW_FROM_COMP) {
			rig_from_comp = px_val;
		} else
			rig_from_db = px_val;
	}
}

#
# Syntax: TYPES: type1 [, typeN]
#
function process_types()
{
	for (;;) {
		lex_get_token(ttIdent);
		types[type_count++] = lex_token;
		debug(1, "Collect type: " lex_token);
		lex_get_token();
		if (lex_tt != ttComma) {
			lex_unget_token();
			break;
		}
	}
}

function lookup_type(atype,    i)
{
	for (i = 0; i < type_count; i++) {
		if (atype == types[i])
			return i;
	}
	return -1;
}

#
# Syntax: GLOBALS: type1: var1 [, typeN: varN]
#
function process_globals()
{
	for (;;) {
		lex_get_token(ttIdent);
		ptype = lex_token;
		lex_get_token(ttColon);
		lex_get_token(ttIdent);
		pname = lex_token;
		typeno = lookup_type(ptype);
		if (i < 0)
			errsrc("Undeclared type '" ptype "' .");
		globals_type[global_count] = ptype;
		globals_name[global_count] = pname;
		global_count++;
		debug(1, "Collect global: " pname);
		lex_get_token();
		if (lex_tt != ttComma) {
			lex_unget_token();
			break;
		}
	}
}

function lookup_global(aname,    i)
{
	for (i = 0; i < global_count; i++) {
		debug(1, "Checking global: " globals_name[i]);
		if (aname == globals_name[i])
			return i;
	}
	return -1;
}

#
# Syntax: PROPERTIES: prop1 [, propN]
#
function process_properties()
{
	prop_count = 0;
	for (;;) {
		lex_get_token(ttIdent);
		props_val[lex_token] = 2 ^ prop_count;
		props[prop_count++] = lex_token;
		debug(1, "Property: " lex_token);
		lex_get_token();
		if (lex_tt != ttComma) {
			lex_unget_token();
			break;
		}
	}
}

function lookup_key(akey,     i)
{
	for (i = 0; i < key_count; i++) {
		if (akey == keys[i])
			return i;
	}
	errsrc("Unknown key '" akey "'");
}

#
# Syntax: KEYS: key1 [, keyN]
#
function process_keys()
{
	for (;;) {
		lex_get_token(ttIdent);
		keys[key_count++] = lex_token;
		debug(1, "Key: " lex_token);
		lex_get_token();
		if (lex_tt != ttComma) {
			lex_unget_token();
			break;
		}
	}
}

#
# Syntax: USAGES: usage1 [, usageN] where usage: name [= auxname [| altname]]
#
function process_usages()
{
	for (;;) {
		lex_get_token(ttIdent);
		usages[usage_count] = lex_token;
		usages_aux[usage_count] = lex_token;
		debug(1, "Usage: " lex_token);
		lex_get_token();
		if (lex_tt == ttEqual) {
			lex_get_token(ttIdent);
			usages_aux[usage_count] = lex_token;
			debug(1, "Usage2: " lex_token);
			lex_get_token();
			if (lex_tt == ttOr) {
				lex_get_token(ttIdent);
				usages_alt[usage_count] = lex_token;
				debug(1, "Usage3: " lex_token);
				lex_get_token();	# lookup next
			}
		}
		usage_count++;
		if (lex_tt != ttComma) {
			lex_unget_token();
			break;
		}
	}
}

function entry_lookup_param(entry, pname,    i)
{
	pcount = entry_param_count[entry];

	for (i = 0; i < pcount; i++) {
		if (pname == entry_param_names[entry, i])
			return i;
	}
	i = lookup_global(pname);
	if (i >= 0)
		return chr(i + 97);	# 'a'
	errsrc("Unknown parameter '" pname "'.");
}

function process_entry_body(entry)
{
	lex_get_token(ttOpenBrace);
	while (1) { # entry body
		lex_get_token();
		kw = lex_tt;
		if (kw == ttCloseBrace)
			break;
		kwname = lex_token;
		lex_get_token();
		if (lex_tt == ttColon) {
			if (kw == ttKW_USAGE) {
				alt = 0;
				for (;;alt++) {
					lex_get_token(ttIdent);
					debug(2, "Entry usage: " entry ":" lex_token);
					if (alt)
						entry_usage_alt[entry] = lex_token;
					else {
						entry_usage[entry] = lex_token;
						entry_usage_alt[entry] = lex_token;
					}
					lex_get_token();
					if (lex_tt != ttOr) {
						lex_unget_token();
						break;
					}
				}
			} else if (kw == ttKW_PROPERTIES) {
				prcount = 0;
				for (;;) {
					lex_get_token(ttIdent);
					debug(2, "Entry property: " lex_token);
					entry_props[entry, prcount++] = lex_token;
					lex_get_token();
					if (lex_tt != ttComma) {
						lex_unget_token();
						break;
					}
				}
				entry_prcount[entry] = prcount;
			} else
				errsrc("Unexpected keyword " kwname ".");
		} else  if (lex_tt == ttOpenRound) {
			if (kw != ttKW_KEY)
				err_syntax();
			lex_get_token(ttIdent);
			keyid = lookup_key(lex_token);
			entry_key[entry, lex_token] = 1;
			debug(2, "Entry key: " lex_token);
			lex_get_token(ttCloseRound);
			lex_get_token();
			if (lex_tt != ttIdent && lex_tt != ttString) {
				entry_key_msg[entry, keyid] = "";
				lex_unget_token();
				continue;	# empty key
			}
			msg = "";
			altmsg = "";
			alt = 0;
			for (;;) {
				if (lex_tt == ttString) {
					debug(3, "String: \"" lex_token "\"");
					if (alt == 0)
						msg = msg lex_token;
					else
						altmsg = altmsg lex_token;
				} else if (lex_tt == ttIdent) {
					debug(3, "Param ref name: " lex_token);
					pn = entry_lookup_param(entry, lex_token);
					if (alt == 0)
						msg = msg "%" pn;
					else
						altmsg = altmsg "%" pn;
				} else if (lex_tt == ttOr) {
					alt = 1;
					debug(3, "switch to alternate");
				} else {
					lex_unget_token();
					break;
				}
				lex_get_token();
			}
			entry_key_msg[entry, keyid] = msg;
			if (altmsg != "")
				entry_key_altmsg[entry, keyid] = altmsg;
		} # key()
	} # entry body loop
}

function process_entries()
{
	for (;;) {
		lex_get_token();
		if (lex_eof)
			break;
		if (lex_tt == ttKW_ENTRIES)
			break;
		if (lex_tt != ttIdent)
			errsrc("Entry name or keyword expected.");
		entry = lex_token;
		entries[entry_count++] = entry;
		debug(1, "Entry: " entry);
		lex_get_token(ttOpenRound);
		lex_get_token();
		pcount = 0;
		if (lex_tt == ttIdent) {
			for (;;) {	# parameters loop
				ptype = lex_token;
				lex_get_token(ttColon);
				lex_get_token(ttIdent);
				pname = lex_token;
				debug(3, "Param: " ptype ":" pname);
				typeno = lookup_type(ptype);
				if (typeno < 0)
					errsrc("Undeclared type '" ptype "' .");
				entry_param_types[entry, pcount] = typeno;
				entry_param_names[entry, pcount] = pname;
				pcount++;
				lex_get_token();
				if (lex_tt == ttCloseRound) {
					break;	# EOP
				} else if (lex_tt != ttComma)
					errsrc("Comma expected but " lex_token " found.");
				lex_get_token(ttIdent);
			} # parameters loop
		} else if (lex_tt != ttCloseRound)
			errsrc("'(' expected, but " lex_token " found.");
		entry_param_count[entry] = pcount;
		process_entry_body(entry);
	} # entries loop
}

function process_catalog()
{
	lex_reset();

	while (!lex_eof) {
		if (!lex_get_token())
			break;
		tt = lex_tt;
		kw = lex_token;
		if (!lex_get_token())
			err_syntax();
		if (lex_tt != ttColon)
			err_syntax();
		if (tt == ttKW_DBNAME) {
			process_database();
		} else if (tt == ttKW_RIG) {
			process_rig();
		} else if (tt == ttKW_PREFIX) {
			process_prefix();
		} else if (tt == ttKW_TYPES) {
			process_types();
		} else if (tt == ttKW_PROPERTIES) {
			process_properties();
		} else if (tt == ttKW_KEYS) {
			process_keys();
		} else if (tt == ttKW_USAGE) {
			process_usages();
		} else if (tt == ttKW_ENTRIES) {
			process_entries();
		} else if (tt == ttKW_GLOBALS) {
			process_globals();
		} else {
			errsrc("Unknown keyword '" kw "'");
		}
	}
}

function code_letter(n)
{
	if (n < 10)
		return "0" + n;
	if (n < 36)
		return chr(n + 65 - 10);
	if (n < 72)
		return chr(n + 97 - 36);
	return chr(n + 128);
}

function out_decl()
{
	pre = rig_comp_output;
	pre_comp = rig_from_comp;

	# Print main types definition

	printc("#ifndef " pre "INCLUDED");
	printc("#define " pre "INCLUDED\n\n");
	printc("/* Error data structure */\n");
	printc("#ifndef " pre "CONST");
	printc("#define " pre "CONST");
	printc("#endif\n");
	if (props_count < 16) {
		printc("typedef unsigned " pre "PROPS ;\n");
	} else {
		printc("typedef unsigned long " pre "PROPS ;\n");
	}
	printc("typedef struct {");
	printc("    " pre "CONST char *name ;");
	printc("    " pre "CONST char *signature ;");
	printc("    int usage ;");
	printc("    " pre "PROPS props ;");

	for (i = 0; i < key_count; i++) {
		printc("    " pre "CONST char *key_" keys[i] " ;");
	}
	printc("} " pre "DATA ;\n") ;
	printc("extern " pre "DATA " pre "CATALOG [] ;");
	printc("extern " pre "CONST char *" pre "NAME ;\n\n");

	# Print type keys
	printc("/* Error type keys */\n");
	for (i = 0; i < type_count; i++) {
		n = code_letter(i) ;
		printc("#define " pre "KEY_" types[i] " '" n "'");
	}
	printc("\n");

	# Print usage keys
	printc("/* Error usage keys */\n");
	printc("#ifndef " pre "USE");
	for (i = 0; i < usage_count; i++) {
		printc("#define " pre_comp usages[i] " " i);
	}
	printc("#endif\n\n");

	# Print property keys
	printc("/* Error property keys */\n");
	printc("#ifndef " pre "PROP");
	for (i = 0; i < prop_count; i++) {
		u = 2 ^ i;

		printc(sprintf("#define %sPROP_%s ( ( %sPROPS ) 0x%x )",
		    pre, props[i], pre, u));
	}
	printc("#endif\n\n");

	if (global_count > 0) {
		# Print global variables
		printc("/* Global variables */\n");
		for (i = 0; i < global_count; i++) {
			n = chr(i + 97);
			printc("#define\t" pre "GLOB_" globals_name[i] "\t'" n "'");
		}
		printc("\n");
	}

	# Print type checking macros */
	printc("/* Error type checking */\n");
	printc("#if defined ( " pre "CHECK ) && defined ( __STDC__ )");
	for (i = 0; i < type_count; i++) {
		n = code_letter(i) ;
		tn = types[i];
		printc(sprintf("extern %s chk_%s ( %s ) ;", tn, n, tn ));
	}
	printc("#else");
	for (i = 0; i < type_count; i++) {
		n = code_letter(i) ;
		printc("#define chk_" n "( A ) ( A )");
	}
	printc("#endif\n\n");

	# Print error macros
	printc("/* Error message macros */\n");
	printc("#ifdef " pre "GEN\n");

	for (i = 0; i < entry_count; i++) {
		entry = entries[i];
		endef = "#define "pre entry "(";
		pcount = entry_param_count[entry];
		# Print parameter list
		if (pcount) {
			for (arg = 0; arg < pcount; arg++) {
				if (arg)
					endef = endef ",";
				endef = endef " " chr(65 + arg);
			}
			endef = endef " ";
		}
		endef = endef ")\\\n";
		endef = endef sprintf("\t%sGEN ( %d", pre, i);
		for (arg = 0; arg < pcount; arg++) {
			an = code_letter(entry_param_types[entry, arg]);
			endef = endef ", chk_" an " ( " chr(65 + arg) " )";
		}
		endef = endef " )\n";
		printc(endef);
	}
	printc("\n#endif\n#endif");
}

#
# Output error definitions
#
function out_defn()
{
	d1 = db_name;
	d2 = db_name_alt;
	pre = rig_comp_output;
	pre_comp = rig_from_comp;

	# Print each catalogue entry
	printc("/* Error catalogue */\n") ;
	if (d1 == d2) {
		printc(pre "CONST char *" pre "NAME = \"" d1 "\" ;");
	} else {
		printc("#ifndef " pre "ALTERNATE") ;
		printc(pre "CONST char *" pre "NAME = \"" d1 "\" ;");
		printc("#else");
		printc(pre "CONST char *" pre "NAME = \"" d2 "\" ;");
		printc("#endif");
	}
	printc("\n" pre "DATA " pre "CATALOG [] = {");
	for (eid = 0; eid < entry_count; eid++) {
		entry = entries[eid];

		# Print error name
		printc("    {\n\t\"" entry "\",");

		# Print error signature
		pcount = entry_param_count[entry];
		if (pcount == 0) {
			printc("\tNULL,");
		} else {
			tstr = "\t\"";
			for (arg = 0; arg < pcount; arg++) {
				tstr = tstr code_letter(entry_param_types[entry, arg]);
			}
			tstr = tstr "\",";
			printc(tstr);
		}

		# Print error usage
		eu = entry_usage[entry];
		ev = entry_usage_alt[entry];
		if (eu != ev) {
			printc("#ifndef " pre "ALTERNATE");
		}
		if (eu == "") {
			printc("\t0,");
		} else {
			printc("\t" pre_comp eu",");
		}
		if (eu != ev) {
			printc("#else");
			if (ev == "") {
				printc("\t0,");
			} else {
				printc("\t" pre_comp ev",");
			}
			printc("#endif");
		}

		# Print error properties
		suff = ",";
		if (key_count == 0)
			suff = "";
		prcount = entry_prcount[entry];
		u = 0;
		for (i = 0; i < prcount; i++) {
	 		u += props_val[entry_props[entry, i]];
		}
		printc("\t" u suff);

		# Print error keys
		for (kid = 0; kid < key_count; kid++) {
			suff = kid == (key_count - 1) ? "" : ",";
			if (!((entry, kid) in entry_key_msg)) {
				printc("\tNULL" suff) ;
	    		} else {
				msg = entry_key_msg[entry, kid];
				havealt = (entry, kid) in entry_key_altmsg;
				altmsg = entry_key_altmsg[entry, kid];
				if (havealt) {
			    		printc("#ifndef " pre "ALTERNATE");
				}
				tmsg = "\t\"" msg "\"" suff;
				printc(tmsg);
				if (havealt) {
		    			printc("#else");
					tmsg = "\t\"" altmsg "\"" suff;
					printc(tmsg);
			   		printc("#endif");
				}
	    		}
		}

		printc("    },");

	} #entry loop

	# Print dummy end marker
    	printc("    {");
    	printc("\tNULL,");
    	printc("\tNULL,");
    	printc("\t0,");
    	tmsg = "\t0";
	for (kid = 0; kid < key_count; kid++) {
		tmsg = tmsg ",\n\tNULL";
	}
	printc(tmsg);
	printc("    }");
	printc("} ;");
	return;
}

#
# Output error numbers
#
function out_number()
{
	pre = rig_comp_output;
	pre_db = rig_from_db;
    	printc("#ifndef " pre "NO_INCLUDED");
    	printc("#define " pre "NO_INCLUDED\n\n");
    	printc("/* Error message macros */\n" );
	for (eid = 0; eid < entry_count; eid++) {
		entry = entries[eid];
		printc("#define " pre_db entry " " eid);
    	}
    	printc("\n#endif");
}

#
# Output usages
#
function out_usage(	pre, pre_comp, uid, us, aux, alt, havealt)
{
    	pre = rig_comp_output;
    	pre_comp = rig_from_comp;

	for (uid = 0; uid < usage_count; uid++) {
		us = usages[uid];
		aux = usages_aux[uid];
		alt = usages_alt[uid];
		havealt = alt != "";
		if (havealt) {
	    		printc("#ifndef " pre "ALTERNATE");
		}
		printc("{ \"" us "\", " pre_comp "VALUE_" aux " },");
		if (havealt) {
	    		printc("#else" ) ;
			printc("{ \"" us "\", " pre_comp "VALUE_" alt " },");
			printc("#endif");
		}
    	}
}

#
# An attempt to emulate getopt()
#
function getopt(argc, argv, options,
	arg, i, opt, opta)
{
	arg = argv[optind];
	if (arg == "--") {
		optind++;
		opt_argpos = 0;
		return 0;
	} else if (arg !~ /^-[^: \t]/) {
		opt_argpos = 0;
		return 0;
	}

	if (opt_argpos == 0)
		opt_argpos = 2;
	opt = substr(arg, opt_argpos, 1);
	i = index(options, opt);
	if (i == 0) {
		err("Unknown option " opt);
	}
	optopt = opt;
     	if (substr(options, i + 1, 1) == ":") {
		optarg = substr(arg, opt_argpos + 1);
		if (optarg == "")
			optarg = argv[++optind];
		opt_argpos = 0;
	} else
		optarg = "";
	if (opt_argpos == 0 || opt_argpos >= length(argv[optind])) {
		optind++;
		opt_argpos = 0;
	} else
		opt_argpos++;
	return 1;
}

#
#  Begin of the main program.
#
BEGIN {

	script_name = "mkerr.awk";
	optind = 1;
	gerror = 0;
	files_count = 0;

	while (getopt(ARGC, ARGV, "c:d:hl:n:u:v")) {
		if (optopt == "c") {
			comp_file = optarg;
		} else if (optopt == "d") {
			defn_file = optarg;
		} else if (optopt == "l") {
			decl_file = optarg;
		} else if (optopt == "n") {
			num_file = optarg;
		} else if (optopt == "u") {
			usage_file = optarg;
		} else if (optopt == "h") {
			usage();
		} else if (optopt == "v") {
			verbose++;
		}
	}
	if (optind >= ARGC)
		err("No input file specified");

	if (defn_file == "" && decl_file == "" &&
	    num_file == "" && usage_file == "" && comp_file == "") {
		warn("No output files specified. Will perform only syntax check.");
	} else
		debug(1, "Output: " defn_file ", " decl_file ", " num_file ", " usage_file);
	entry_count = 0;
	type_count = 0;
	key_count = 0;
	usage_count = 0;
	global_count = 0;
	db_name = "ERRORS";
	db_name_alt = "ERRORS";
	rig_name = "ERR_";
	rig_comp_output = "ERR_";
	rig_from_comp = "ERR_USE_";
	rig_from_db = "ERR_NO_";

	autoheader = "/*\n";
	for (; optind < ARGC; optind++) {
		srcfile = ARGV[optind];
		debug(1, "Source file: " srcfile " " ARGC " " optind);

		autoheader = autoheader \
		    " * AUTOMATICALLY GENERATED BY " script_name " FROM " srcfile "\n";
		process_catalog();
		close(srcfile);
	}
	autoheader = autoheader " */\n";
	first_comment = first_comment "\n" autoheader;
	if (decl_file != "") {
		outfilename = decl_file;
		printc(first_comment);
		out_decl();
		close(outfilename);
	}
	if (defn_file != "") {
		outfilename = defn_file;
		printc(first_comment);
		out_defn();
		close(outfilename);
	}
	if (num_file != "") {
		outfilename = num_file;
		printc(first_comment);
		out_number();
		close(outfilename);
	}
	if (usage_file != "") {
		outfilename = usage_file;
		printc(first_comment);
		out_usage();
		close(outfilename);
	}
	if (comp_file != "") {
		outfilename = comp_file;
		printc(first_comment);
		printc("#include <stddef.h>");
		printc("#include \"catstd.h\"");
		out_defn();
	}
	exit 0;
}

