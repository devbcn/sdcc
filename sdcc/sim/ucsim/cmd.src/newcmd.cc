/*
 * Simulator of microcontrollers (cmd.src/newcmd.cc)
 *
 * Copyright (C) 1999,99 Drotos Daniel, Talker Bt.
 * Copyright (C) 2006, Borut Razem - borut.razem@siol.net
 *
 * To contact author send email to drdani@mazsola.iit.uni-miskolc.hu
 *
 */

/* This file is part of microcontroller simulator: ucsim.

UCSIM is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

UCSIM is distributed in the hope that it will be useful,
but WITHOUT ANY RANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with UCSIM; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA. */
/*@1@*/

#include "ddconfig.h"

#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include "i_string.h"

#include "cmdlexcl.h"

// prj
#include "globals.h"
#include "utils.h"
#include "fiocl.h"

// sim
#include "simcl.h"
#include "argcl.h"
#include "appcl.h"

// local
#include "newcmdcl.h"
#include "cmdutil.h"


/*
 * Options of console
 */

cl_prompt_option::cl_prompt_option(class cl_console_base *console):
  cl_optref(console)
{
  con= console;
}

int
cl_prompt_option::init(void)
{
  char *help;
  help= format_string("Prompt string of console%d", con->get_id());
  create(con, string_opt, "prompt", help);
  free(help);
  default_option("prompt");
  return(0);
}

void
cl_prompt_option::option_changed(void)
{
  if (!con)
    return;
  char *s;
  option->get_value(&s);
  con->set_prompt(s);
}


cl_debug_option::cl_debug_option(class cl_console_base *console):
  cl_prompt_option(console)
{}

int
cl_debug_option::init(void)
{
  char *help;
  help= format_string("Debug messages to console%d", con->get_id());
  create(con, bool_opt, "debug", help);
  free(help);
  default_option("debug");
  return(0);
}

void
cl_debug_option::option_changed(void)
{
  if (!con)
    return;
  bool b;
  option->get_value(&b);
  con->set_flag(CONS_DEBUG, b);
}


/*
 * Command console
 *____________________________________________________________________________
 */

cl_console_base::cl_console_base(void):
  cl_base()
{
  app= 0;
  flags= 0;
  prompt= 0;
  nl= 0;
  lbuf= 0;
}

int
cl_console_base::init(void)
{
  cl_base::init();
  prompt_option= new cl_prompt_option(this);
  prompt_option->init();
  null_prompt_option= new cl_optref(this);
  null_prompt_option->init();
  null_prompt_option->use("null_prompt");
  debug_option= new cl_debug_option(this);
  debug_option->init();
  welcome();
  print_prompt();
  last_command= 0;
  last_cmdline= 0;
  return(0);
}

void
cl_console_base::welcome(void)
{
  if (!(flags & CONS_NOWELCOME))
    {
      dd_printf("uCsim %s, Copyright (C) 1997 Daniel Drotos.\n"
        "uCsim comes with ABSOLUTELY NO WARRANTY; for details type "
        "`show w'.\n"
        "This is free software, and you are welcome to redistribute it\n"
        "under certain conditions; type `show c' for details.\n",
        VERSIONSTR);
    }
}

void
cl_console_base::print_prompt(void)
{
  if (flags & (CONS_FROZEN | CONS_INACTIVE))
    return;

  if (!(flags & CONS_INTERACTIVE))
    return;
  
  if (null_prompt_option->get_value(bool(0)))
    {
      class cl_f *fo= get_fout(), *fi= get_fin();
      char c= 0;
      if (fi &&
	  fi->eof() &&
	  (fi->id() == fo->id()))
	return;
      fo->write(&c, 1);
    }
  else
    {
      dd_printf("%d%s", id, (prompt && prompt[0]) ? prompt : "> ");
    }
}

int
cl_console_base::dd_printf(const char *format, ...)
{
  va_list ap;
  int ret= 0;

  va_start(ap, format);
  ret= cmd_do_print(format, ap);
  va_end(ap);

  return(ret);
}

int
cl_console_base::debug(const char *format, ...)
{
  if ((flags & CONS_DEBUG) == 0)
    return(0);

  va_list ap;
  int ret= 0;

  va_start(ap, format);
  ret= cmd_do_print(format, ap);
  va_end(ap);

  return(ret);
}

/*
 * Printing out an integer in binary format
 */

void
cl_console_base::print_bin(long data, int bits)
{
  long mask= 1;

  mask= mask << ((bits >= 1)?(bits-1):0);
  while (bits--)
    {
      dd_printf("%c", (data&mask)?'1':'0');
      mask>>= 1;
    }
}

void
cl_console_base::print_char_octal(char c)
{
  if (strchr("\a\b\f\n\r\t\v\"", c))
    switch (c)
      {
      case '\a': dd_printf("\a"); break;
      case '\b': dd_printf("\b"); break;
      case '\f': dd_printf("\f"); break;
      case '\n': dd_printf("\n"); break;
      case '\r': dd_printf("\r"); break;
      case '\t': dd_printf("\t"); break;
      case '\v': dd_printf("\v"); break;
      case '\"': dd_printf("\""); break;
      }
  else if (isprint(c))
    dd_printf("%c", c);
  else
    dd_printf("\\%03hho", c);
}

int
cl_console_base::cmd_do_print(const char *format, va_list ap)
{
  int ret;
  class cl_f *fo= get_fout(), *fi= get_fin();
  
  if (fo)
    {
      if (fi &&
	  fi->eof() &&
	  (fi->id() == fo->id()))
	{
	  deb("do not attempt to write on console, where input is at file_end\n");
	  return 0;
	}
      ret= fo->vprintf((char*)format, ap);
      //fo->flush();
      return ret;
    }
  else
    return 0;
}

bool
cl_console_base::interpret(char *cmd)
{
  dd_printf("Unknown command\n");
  return(0);
}

void
cl_console_base::set_id(int new_id)
{
  char *s;

  id= new_id;
  set_name(s= format_string("console%d", id));
  free(s);
}

void
cl_console_base::set_prompt(char *p)
{
  if (prompt)
    free(prompt);
  if (p && *p)
    prompt= strdup(p);
  else
    prompt= 0;
}

bool
cl_console_base::input_active(void) const
{
  if ((
       (flags & CONS_FROZEN) == 0 ||
       (flags & CONS_INTERACTIVE) != 0
       )
      &&
      (flags & CONS_INACTIVE) == 0
      )
    {
      return true;
    }
  else
    return false;
}

int
cl_console_base::proc_input(class cl_cmdset *cmdset)
{
  int retval= 0, i, do_print_prompt= 1;

  un_redirect();
  char *cmdstr;
  i= read_line();
  if (i < 0)
    {
      deb("colsing, bacause read_line on con=%d returned %d\n", id, i);
      return 1;
    }
  if (i == 0)
    return 0;
  cmdstr= lbuf;
  if (cmdstr==NULL)
    cmdstr= (char*)"";
  if (is_frozen())
    {
      app->get_sim()->stop(resUSER);
      set_flag(CONS_FROZEN, false);
      retval = 0;
      do_print_prompt= 0;
    }
  else
    {
      if (cmdstr && *cmdstr == '\004')
        retval = 1;
      else
        {
          class cl_cmdline *cmdline= 0;
          class cl_cmd *cm = 0;
          if (get_flag(CONS_ECHO))
            dd_printf("%s\n", cmdstr);
          cmdline= new cl_cmdline(app, cmdstr, this);
          cmdline->init();
          if (cmdline->repeat() &&
              is_interactive() &&
              last_command)
            {
              cm = last_command;
              delete cmdline;
              cmdline = last_cmdline;
            }
	  else
            {
              cm= cmdset->get_cmd(cmdline, is_interactive());
              if (last_cmdline)
                {
                  delete last_cmdline;
                  last_cmdline = 0;
                }
	      last_command = 0;
            }
          if (cm)
            {
              retval= cm->work(app, cmdline, this);
              if (cm->can_repeat)
                {
                  last_command = cm;
                  last_cmdline = cmdline;
                }
              else
                delete cmdline;
            }
          else if (cmdline->get_name() != 0)
            {
	      if (strlen(cmdstr) > 0)
		{
		  uc_yy_set_string_to_parse(cmdstr);
		  yyparse();
		  uc_yy_free_string_to_parse();
		}
              delete cmdline;
            }
        }
    }
  //un_redirect();
  if (!retval &&
      cmdstr &&
      do_print_prompt &&
      !get_flag(CONS_REDIRECTED))
    {
      print_prompt();
    }
  lbuf= 0;
  return(retval);
}

int
cl_console_base::set_flag(int flag, bool value)
{
  if (value)
    flags|= flag;
  else
    flags&= ~flag;
  return flags;
}

void
cl_console_base::set_interactive(bool new_value)
{
  set_flag(CONS_INTERACTIVE, new_value);
}

bool
cl_console_base::get_flag(int flag)
{
  return flags & flag;
}

bool
cl_console_base::set_cooked(bool new_val)
{
  return false;
}


/*
 * Command interpreter
 *____________________________________________________________________________
 */

cl_commander_base::cl_commander_base(class cl_app *the_app, class cl_cmdset *acmdset):
  cl_base()
{
  app= the_app;
  cons= new cl_list(1, 1, "consoles");
  actual_console= frozen_console= config_console= 0;
  cmdset= acmdset;
}

cl_commander_base::~cl_commander_base(void)
{
  cons->free_all();
  delete cons;
  delete cmdset;
}

void
cl_commander_base::add_console(class cl_console_base *console)
{
  if (!console)
    return;
  int i=cons->add(console);
  console->set_id(i);
  console->init();
  update_active();
}

void
cl_commander_base::del_console(class cl_console_base *console)
{
  cons->disconn(console);
  update_active();
  delete console;
}

void
cl_commander_base::activate_console(class cl_console_base *console)
{
  console->set_flag(CONS_INACTIVE, false);
  console->print_prompt();
  update_active();
}

void
cl_commander_base::deactivate_console(class cl_console_base *console)
{
  console->set_flag(CONS_INACTIVE, true);
  update_active();
}

int
cl_commander_base::consoles_prevent_quit(void)
{
  int i, r= 0;

  for (i= 0; i < cons->count; i++)
    {
      class cl_console_base *c= (class cl_console_base*)(cons->at(i));
      if (c->prevent_quit())
	r++;
    }
  return r;
}


/*
 * Printing to all consoles
 */

int
cl_commander_base::all_printf(const char *format, ...)
{
  va_list ap;
  int i, ret= 0;

  for (i= 0; i < cons->count; i++)
    {
      class cl_console_base *c= (class cl_console_base*)(cons->at(i));

      va_start(ap, format);
      ret= c->cmd_do_print(format, ap);
      va_end(ap);
    }
  return(ret);
}


/*
 * Printing to actual_console
 */

int
cl_commander_base::dd_printf(const char *format, va_list ap)
{
  int ret= 0;
  class cl_console_base *con;

  if (actual_console)
    {
      con= actual_console;
    }
  else if (frozen_console)
    {
      con= frozen_console;
    }
  else
    {
      con= 0;
    }
  if (con)
    {
      ret= con->cmd_do_print(format, ap);
    }
  return(ret);
}

int
cl_commander_base::dd_printf(const char *format, ...)
{
  va_list ap;
  int ret= 0;

  va_start(ap, format);
  ret= dd_printf(format, ap);
  va_end(ap);

  return(ret);
}

/*
 * Printing to consoles which have CONS_DEBUG flag set
 */

int
cl_commander_base::debug(const char *format, ...)
{
  va_list ap;
  int i, ret= 0;

  for (i= 0; i < cons->count; i++)
    {
      class cl_console_base *c= (class cl_console_base*)(cons->at(i));
      if (c->get_flag(CONS_DEBUG))
        {
          va_start(ap, format);
          ret= c->cmd_do_print(format, ap);
          va_end(ap);
        }
    }
  return(ret);
}

int
cl_commander_base::debug(const char *format, va_list ap)
{
  int i, ret= 0;

  for (i= 0; i < cons->count; i++)
    {
      class cl_console_base *c= (class cl_console_base*)(cons->at(i));
      if (c->get_flag(CONS_DEBUG))
        {
          ret= c->cmd_do_print(format, ap);
        }
    }
  return(ret);
}

int
cl_commander_base::flag_printf(int iflags, const char *format, ...)
{
  va_list ap;
  int i, ret= 0;

  for (i= 0; i < cons->count; i++)
    {
      class cl_console_base *c= (class cl_console_base*)(cons->at(i));
      if ((c->get_flag(iflags)) == iflags)
        {
          va_start(ap, format);
          ret= c->cmd_do_print(format, ap);
          va_end(ap);
        }
    }
  return(ret);
}

int
cl_commander_base::input_avail_on_frozen(void)
{
  if (!frozen_console || frozen_console->is_tty())
    return(0);
  return(frozen_console->input_avail());
}

class cl_console_base *
cl_commander_base::exec_on(class cl_console_base *cons, char *file_name)
{
  if (!cons || !file_name || !fopen(file_name, "r"))
    return 0;

  class cl_console_base *subcon = cons->clone_for_exec(file_name);
  subcon->set_flag(CONS_NOWELCOME, true);
  subcon->set_flag(CONS_INTERACTIVE, false);
  add_console(subcon);
  return subcon;
}


/* End of cmd.src/newcmd.cc */
