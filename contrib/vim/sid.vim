" ex:syntax=vim
"
" Vim syntax file
" Language: SID (Parser generator)
" Maintainer: Jeroen Ruigrok van der Werven <asmodai@tendra.org>
"
" NOTE: TenDRA SID parser generator syntax file.
"
"----------------------------------------------------------------------------
"                                 CREDITS
"----------------------------------------------------------------------------
" Jeroen Ruigrok van der Werven <asmodai@tendra.org>
"----------------------------------------------------------------------------
"
" $TenDRA$
"

" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded
if version <  600
	syntax clear
elseif exists("b:current_syntax")
	finish
endif

"============================================================================
" SID MATCHES
"============================================================================
" COMMENTS

syn region sidComment	start="^\s*\/\*" end="\*\/\s*"
syn match  sidComment	"\/\/.*"

" SECTION HEADERS

syn match sidSecHeader	"%types%"
syn match sidSecHeader	"%terminals%"
syn match sidSecHeader	"%productions%"
syn match sidSecHeader	"%entry%"

" IDENTIFIERS

syn match sidIdentifier	"[a-zA-Z_-][a-zA-Z0-9_-]*"

syn match sidNotUsed	"![a-zA-Z_-][a-zA-Z0-9_-]*"

"============================================================================
" COLOUR ASSIGNMENT
"============================================================================
" Define the default highlighting.
" For version 5.7 and earlier: only when not done already
" For version 5.8 and later: only when an item doesn't have highlighting yet
if version >= 508 || !exists("did_c_syn_inits")
	if version < 508
		let did_c_syn_inits = 1
		command -nargs=+ HiLink hi link <args>
	else
		command -nargs=+ HiLink hi def link <args>
	endif

	HiLink sidComment	Comment
	HiLink sidIdentifier	Identifier
	HiLink sidNotUsed	Error
	HiLink sidSecHeader	Statement

	delcommand HiLink
endif

let b:current_syntax = "sid"
