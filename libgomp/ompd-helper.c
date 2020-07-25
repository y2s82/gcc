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

static const char *gompd_query_type_string[] = {
#define GENERATE_STRING(STRING) ompd_stringify (STRING),
  FOREACH_QUERYTYPE (GENERATE_STRING)
#undef GENERATE_STRING
};

ompd_rc_t
gompd_getQueryStringSize (size_t *size, query_type type,
			  const char* variableType, const char *memberType)
{
  const char *sep = "_";
  const char **typeString = &gompd_query_type_string[type];

  *size = strlen (*typeString) + strlen (sep) + strlen (variableType);
  if (memberType)
    *size += strlen (sep) + strlen (memberType);

  return ompd_rc_ok;
}
ompd_rc_t
gompd_getQueryString (char **queryString, query_type type,
		      const char* variableType, const char *memberType)
{
  if (!type || !variableType)
    return ompd_rc_bad_input;

  const char *sep = "_";
  const char **typeString = &gompd_query_type_string[type];

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

ompd_rc_t
gompd_getAddress (ompd_address_space_context_t *ac, ompd_thread_context_t *tc,
		  ompd_address_t *addr, const char *variableType,
		  const char *memberType, ompd_addr_t seg)
{
  if (!ac)
    return ompd_rc_stale_handle;
  ompd_rc_t ret = ompd_rc_ok;
  char *queryString = NULL;
  size_t querySize = 0;
  ret = gompd_getQueryStringSize (&querySize, gompd_query_address, variableType,
				  memberType);
  if (ret != ompd_rc_ok)
    return ret;
  ret = gompd_callbacks.alloc_memory (querySize + 1, (void *) queryString);
  if (ret != ompd_rc_ok)
    return ret;
  ret = gompd_getQueryString (&queryString, gompd_query_address, variableType,
			      memberType);
  if (ret != ompd_rc_ok)
    return ret;

  if (!memberType)
    {
      ret = gompd_callbacks.symbol_addr_lookup (ac, tc, queryString, addr,
						NULL);
      if (ret != ompd_rc_ok)
	return ret;
    }
  else if (addr)
    {
      ompd_size_t offset;
      ompd_address_t offsetAddr;
      ret = gompd_callbacks.symbol_addr_lookup (ac, tc, queryString,
						&offsetAddr, NULL);
      if (ret != ompd_rc_ok)
	return ret;
      ret = gompd_callbacks.read_memory (ac, tc, &offsetAddr,
					 sizeof (ompd_size_t),
					 (void *) &offset);
      if (ret != ompd_rc_ok)
	return ret;
      addr->address += offset;
    }
  else
    {
      return ompd_rc_bad_input;
    }

  return gompd_callbacks.free_memory (queryString);
}

ompd_rc_t
gompd_getSize (ompd_address_space_context_t *ac, ompd_thread_context_t *tc,
	       ompd_size_t *size, const char *variableType,
	       const char *memberType)
{
  if (!ac)
    return ompd_rc_stale_handle;
  ompd_rc_t ret;
  ompd_address_t sizeAddr;
  char *queryString = NULL;
  ret = gompd_getQueryString (&queryString, gompd_query_size, variableType,
			      memberType);

  if (ret != ompd_rc_ok)
    return ret;

  ret = gompd_callbacks.symbol_addr_lookup (ac, tc, queryString, &sizeAddr,
					    NULL);
  if (ret != ompd_rc_ok)
    return ret;

  return gompd_callbacks.read_memory (ac, tc, &sizeAddr, sizeof (ompd_size_t),
				     (void *) size);
}

ompd_rc_t gompd_getValue (ompd_address_space_context_t *ac,
			  ompd_thread_context_t *tc, void *value,
			  ompd_address_t *addr,
			  const char *variableType, const char *memberType)
{
  if (!ac)
    return ompd_rc_stale_handle;
  if (!addr)
    return ompd_rc_bad_input;

  ompd_rc_t ret;
  ompd_size_t size;
  ret = gompd_getSize (ac, tc, &size, variableType, memberType);
  if (ret != ompd_rc_ok)
    return ret;
  return gompd_callbacks.read_memory (ac, tc, addr, size, value);
}

ompd_rc_t
gompd_getVariableAddress (ompd_address_space_context_t *ac,
			  ompd_thread_context_t *tc, ompd_address_t *addr,
			  const char *variableType, ompd_addr_t seg)
{
  return gompd_getAddress (ac, tc, addr, variableType, NULL, seg);
}

ompd_rc_t
gompd_getVariableSize (ompd_address_space_context_t *ac,
		       ompd_thread_context_t * tc, ompd_size_t *size,
		       const char *variableType)
{
  return gompd_getSize (ac, tc, size, variableType, NULL);
}

ompd_rc_t
gompd_getVariableValue (ompd_address_space_context_t *ac,
			ompd_thread_context_t *tc, void *value,
			ompd_address_t *variableAddress,
			const char *variableType)
{
  return gompd_getValue (ac, tc, value, variableAddress, variableType, NULL);
}

ompd_rc_t
gompd_getMemberAddress (ompd_address_space_context_t *ac,
			ompd_thread_context_t *tc, ompd_address_t *variableAddr,
			const char *variableType, const char *memberType,
			ompd_addr_t seg)
{
  if (!variableAddr)
    return ompd_rc_bad_input;
  return gompd_getAddress (ac, tc, variableAddr, variableType, memberType, seg);
}

ompd_rc_t
gompd_getMemberSize (ompd_address_space_context_t *ac,
		     ompd_thread_context_t *tc, ompd_size_t *size,
		     const char *variableType, const char *memberType)
{
  return gompd_getSize (ac, tc, size, variableType, memberType);
}

ompd_rc_t
gompd_getMemberValue (ompd_address_space_context_t *ac,
		      ompd_thread_context_t *tc, void *value,
		      ompd_address_t *addr, const char *variableType,
		      const char *memberType)
{
  return gompd_getValue (ac, tc, value, addr, variableType, memberType);
}
