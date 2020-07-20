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
gompd_getQueryString (char **queryString, query_type type, const char* variableType,
		      const char *memberType)
{
  if (!type || !variableType)
    return ompd_rc_bad_input;

  const char *sep = "_";
  const char **typeString = &gompd_query_type_string [type];

  ompd_size_t querySize = strlen(*typeString) + strlen(sep) + strlen(variableType);
  if (memberType)
    querySize += strlen(sep) + strlen(memberType);

  ompd_rc_t ret = gompd_callbacks.alloc_memory (querySize + 1, (void *) *queryString);
  if (ret != ompd_rc_ok)
    return ret;

  size_t offset = 0;
  strcpy (*queryString, *typeString);
  offset += strlen (*typeString);
  strcpy (*queryString + offset, sep);
  offset += strlen (sep);
  strcpy (*queryString + offset, variableType);
  if (memberType)
    {
      offset += strlen (variableType);
      strcpy (*queryString + offset, sep);
      offset += strlen (sep);
      strcpy (*queryString + offset, memberType);
    }

  return ompd_rc_ok;
}

ompd_rc_t gompd_getAddress (ompd_address_space_context_t *ah, ompd_thread_context_t *th,
                            ompd_address_t *addr, const char *variableType,
			    const char *memberType, ompd_addr_t seg)
{
  ompd_rc_t ret = ompd_rc_ok;
  char *queryString = NULL;
  ret = gompd_getQueryString (&queryString, gompd_query_address, variableType, memberType);
  if (ret != ompd_rc_ok)
    return ret;

  if (!memberType)
    {
      ret = gompd_callbacks.symbol_addr_lookup (ah, th, queryString, addr, NULL);
      if (ret != ompd_rc_ok)
        return ret;
    }
  else if (addr)
    {
      ompd_size_t offset;
      ompd_address_t offsetAddr;
      ret = gompd_callbacks.symbol_addr_lookup (ah, th, queryString, &offsetAddr, NULL);
      if (ret != ompd_rc_ok)
        return ret;
      ret = gompd_callbacks.read_memory (ah, th, &offsetAddr, sizeof (ompd_size_t),
					 (void *) &offset);
      if (ret != ompd_rc_ok)
        return ret;
      addr->address += offset;
    }
  else
    {
      return ompd_rc_bad_input;
    }

  ret = gompd_callbacks.free_memory (queryString);
  return ret;
}

ompd_rc_t
gompd_getSize (ompd_address_space_context_t *ah, ompd_thread_context_t *th,
	       ompd_size_t *size, const char *variableType, const char *memberType)
{
  ompd_rc_t ret;
  ompd_address_t sizeAddr;
  char *queryString = NULL;
  ret = gompd_getQueryString (&queryString, gompd_query_size, variableType, NULL);

  if (ret != ompd_rc_ok)
    return ret;

  ret = gompd_callbacks.symbol_addr_lookup (ah, th, queryString, &sizeAddr, NULL);
  if (ret != ompd_rc_ok)
    return ret;

  ret = gompd_callbacks.read_memory (ah, th, &sizeAddr, sizeof (ompd_size_t),
				     (void *) size);
  return ret;
}

ompd_rc_t gompd_getValue (ompd_address_space_context_t *, ompd_thread_context_t *,
			  void *, ompd_address_t *, const char *, const char *, 
		  	  ompd_addr_t);

ompd_rc_t
gompd_getVariableAddress (ompd_address_space_context_t *ah,
			  ompd_thread_context_t *th, ompd_address_t *addr,
			  const char *variableType, ompd_addr_t seg)
{
  return gompd_getAddress (ah, th, addr, variableType, NULL, seg);
}

ompd_rc_t
gompd_getVariableSize (ompd_address_space_context_t *ah, ompd_thread_context_t * th,
		       ompd_size_t *size, const char *variableType)
{
  ompd_rc_t ret;
  ompd_address_t sizeAddr;
  char *queryString = NULL;
  ret = gompd_getQueryString (&queryString, gompd_query_size, variableType, NULL);
  if (ret != ompd_rc_ok)
    return ret;

  ret = gompd_callbacks.symbol_addr_lookup (ah, th, queryString, &sizeAddr, NULL);
  if (ret != ompd_rc_ok)
    return ret;

  ret = gompd_callbacks.read_memory (ah, th, &sizeAddr, sizeof (ompd_size_t),
				     (void *) size);
  return ret;
}

ompd_rc_t
gompd_getVariableValue (ompd_address_space_context_t *ah,
			ompd_thread_context_t *th, void *value,
			ompd_address_t *variableAddress, const char *variableType,
			ompd_addr_t seg)
{
  ompd_rc_t ret;
  ompd_size_t variableSize;

  ret = gompd_getVariableSize (ah, th, &variableSize, variableType);
  if (ret != ompd_rc_ok)
    return ret;

  ret = gompd_callbacks.read_memory (ah, th, variableAddress, variableSize, value);

  return ompd_rc_ok;
}

ompd_rc_t
gompd_getMemberAddress (ompd_address_space_context_t *ah,
			ompd_thread_context_t *th, ompd_address_t *variableAddr,
			const char *variableType, const char *memberType, ompd_addr_t seg)
{
  if (!variableAddr)
    return ompd_rc_bad_input;
  return gompd_getAddress (ah, th, variableAddr, variableType, memberType, seg);
}

ompd_rc_t
gompd_getMemberSize (ompd_address_space_context_t *ah, ompd_thread_context_t *th,
		     ompd_address_t *addr, const char *variableType,
		     const char *memberType, ompd_addr_t seg)
{
  return ompd_rc_ok;
}

ompd_rc_t
gompd_getMemberValue (ompd_address_space_context_t *ah,
		      ompd_thread_context_t *th, void *queryString,ompd_address_t *addr,
		      const char *variableType, const char *memberType, ompd_addr_t seg)
{
  return ompd_rc_ok;
}

