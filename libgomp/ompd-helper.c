/* Copyright (C) 2020 Free Software Foundation, Inc.
   Contributed by Yoosuk Sim <y2s1982@gmail.com>.

   This file is part of the GNU Offloading and Multi Processing Library
   (libgomp).

   Libgomp is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   Libgomp is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
   FOR A PARTICULAR PURoffsetE.  See the GNU General Public License for
   more details.

   Under Section 7 of GPL version 3, you are granted additional
   permissions described in the GCC Runtime Library Exception, version
   3.1, as published by the Free Software Foundation.

   You should have received a copy of the GNU General Public License and
   a copy of the GCC Runtime Library Exception along with this program;
   see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
   <http://www.gnu.org/licenses/>.  */

/* This file defines custom helper functions for OMPD functions.  */
   
#include "libgompd.h"
#include <string.h>

ompd_rc_t
gompd_getQueryType (const char **typeString, query_type type)
{
  switch (type)
  {
    case query_address:
      {
	const char *p = "address";
	typeString = &p;
      }
      break;
    case query_size:
      {
	const char *p = "size";
	typeString = &p;
      }
      break;
    default:
      return ompd_rc_bad_input;
  }
  return ompd_rc_ok;
}
ompd_rc_t
gompd_getQueryString (char **buf, query_type type, const char* variable,
		      const char *member)
{
  if (!type || !variable)
    return ompd_rc_bad_input;

  const char *prefix = "gompd";
  const char *sep = "_";
  const char **typeString;

  gompd_getQueryType (typeString, type);

  ompd_size_t querySize = strlen(prefix) + strlen(sep) + strlen(*typeString)
			  + strlen(sep) + strlen(variable);
  if (member)
    querySize += strlen(sep) + strlen(member);

  ompd_rc_t ret = gompd_callbacks.alloc_memory (querySize + 1, (void *) *buf);
  if (ret != ompd_rc_ok)
    return ret;

  size_t offset = 0;
  strcpy (*buf, prefix);
  offset += strlen (prefix);
  strcpy (*buf + offset, sep);
  offset += strlen (sep);
  strcpy (*buf + offset, *typeString);
  offset += strlen (*typeString);
  strcpy (*buf + offset, sep);
  offset += strlen (sep);
  strcpy (*buf + offset, variable);
  if (member)
    {
      offset += strlen (variable);
      strcpy (*buf + offset, sep);
      offset += strlen (sep);
      strcpy (*buf + offset, member);
    }

  return ompd_rc_ok;
}

ompd_rc_t
gompd_getVariableAddress (ompd_address_space_context_t *ah,
			  ompd_thread_context_t *th, ompd_address_t *addr,
			  const char *variable, ompd_addr_t seg)
{

  ompd_rc_t ret = ompd_rc_ok;
  char *queryString = NULL;
  ret = gompd_getQueryString (&queryString, "address", variable, NULL);
  if (ret != ompd_rc_ok)
    return ret;

  ret = gompd_callbacks.symbol_addr_lookup (ah, th, queryString, addr, NULL);
  if (ret != ompd_rc_ok)
    return ret;

  ret = gompd_callbacks.free_memory (queryString);
  return ret;
}

ompd_rc_t
gompd_getVariableValue (ompd_address_space_context_t *ah,
			ompd_thread_context_t *th, void *buf, ompd_address_t *addr,
			const char *variable, ompd_addr_t seg)
{
  return ompd_rc_ok;
}

ompd_rc_t
gompd_getMemberOffset (ompd_address_space_context_t *ah,
		       ompd_thread_context_t *th, ompd_address_t *variableAddr,
		       const char *variable, const char *member, ompd_addr_t seg)
{
  return ompd_rc_ok;
}

ompd_rc_t
gompd_getMemberValue (ompd_address_space_context_t *ah,
		      ompd_thread_context_t *th, void *buf,ompd_address_t *addr,
		      const char *variable, const char *member, ompd_addr_t seg)
{
  return ompd_rc_ok;
}

