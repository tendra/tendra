/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef EXECUTE_H
#define EXECUTE_H


/*
 * PROCEDURE DECLARATIONS
 *
 * These routines are concerned with building up the current command and then
 * executing it.
 */

extern void	 enable_delayed_signal(void);
extern void	 disable_delayed_signal(void);
extern void	 process_delayed_signal(void);
extern void	 reset_exec_error(void);
extern void	 cmd_string(const char *);
extern void	 cmd_filename(const filename *);
extern void	 cmd_env(const char *name);
extern void	 kill_stray(void);
extern void	 remove_junk(void);
extern filename *execute(filename *, filename *);


/*
 * LAST COMMAND
 *
 * These variables give the details of the last command executed.
 */

extern const char	*last_command;
extern int	 last_return;
extern bool	 exec_error;


#endif /* EXECUTE_H */
