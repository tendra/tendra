/* $Id$ */

/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

Tokdec .~abi_Set_signal_handler : [] EXP;
Tokdec .~abi_Sync_handler       : [] EXP;

Tokdef ~Set_signal_handler = [] EXP .~abi_Set_signal_handler;
Tokdef ~Sync_handler       = [] EXP .~abi_Sync_handler;

Keep (
	~Set_signal_handler, ~Sync_handler
)

