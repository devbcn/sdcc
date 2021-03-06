/*
 * Simulator of microcontrollers (cmd.src/cmdutil.h)
 *
 * Copyright (C) 1999,99 Drotos Daniel, Talker Bt.
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
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with UCSIM; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA. */
/*@1@*/

#ifndef CMD_CMDUTIL_HEADER
#define CMD_CMDUTIL_HEADER

#ifdef SOCKET_AVAIL
# include HEADER_SOCKET
#endif

#include "ddconfig.h"

#include "uccl.h"


#ifdef SOCKET_AVAIL
extern UCSOCKET_T make_server_socket(unsigned short int port);
#endif
#ifdef _WIN32
enum e_handle_type { CH_UNDEF, CH_FILE, CH_SOCKET, CH_CONSOLE, CH_SERIAL,};
enum e_handle_type get_handle_type(HANDLE handle);
//bool input_avail(HANDLE handle, e_handle_type type = CH_UNDEF);
bool input_avail(UCSOCKET_T handle);
#else
bool input_avail(UCSOCKET_T handle);
#endif
//extern void print_bin(long data, int bits, class cl_console *con);
extern struct name_entry *get_name_entry(struct name_entry tabl[],
					 char *name,
					 class cl_uc *uc);
/*extern bool interpret_bitname(char *name, class cl_uc *uc,
			      uchar **cell, uchar *celladdr,
			      uchar *bitaddr, uchar *bitmask,
			      char **symname);*/
extern char *proc_escape(char *string, int *len);
extern int cmd_vfprintf(FILE *f, char *format, va_list ap);
extern int cmd_fprintf(FILE *f, char *format, ...);

extern int bool_name(char *s, int *val);

  
#endif

/* End of cmd.src/cmdutil.h */
