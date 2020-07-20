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
   FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
   more details.

   Under Section 7 of GPL version 3, you are granted additional
   permissions described in the GCC Runtime Library Exception, version
   3.1, as published by the Free Software Foundation.

   You should have received a copy of the GNU General Public License and
   a copy of the GCC Runtime Library Exception along with this program;
   see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
   <http://www.gnu.org/licenses/>.  */

/* This file contains various macros and auxiliary function declarations
   for OMPD library.  */

#ifndef LIBGOMPD_H
#define LIBGOMPD_H 1

#include "omp-tools.h"
#include <string.h>

#define ompd_stringify(x) ompd_str2(x)
#define ompd_str2(x) #x

#define OMPD_VERSION 201811

#define FOREACH_QUERYTYPE(TYPE)\
	TYPE (gompd_query_address)\
	TYPE (gompd_query_size)\


extern ompd_callbacks_t gompd_callbacks;

typedef struct _ompd_aspace_handle {
  ompd_address_space_context_t *context;
  ompd_device_t kind;
  ompd_size_t sizeof_id;
  void *id;
  ompd_address_space_handle_t *process_reference;
  ompd_size_t ref_count;
} ompd_address_space_handle_t;

typedef enum gompd_query_type {
#define GENERATE_ENUM(ENUM) ENUM,
  FOREACH_QUERYTYPE (GENERATE_ENUM)
#undef GENERATE_ENUM
} query_type;

ompd_rc_t gompd_getQueryStringSize (size_t *, query_type, const char*, const char *);

ompd_rc_t gompd_getQueryString (char **, query_type, const char*, const char *);

ompd_rc_t gompd_getAddress (ompd_address_space_context_t *, ompd_thread_context_t *,
			    ompd_address_t *, const char *, const char *, ompd_addr_t);

ompd_rc_t gompd_getSize (ompd_address_space_context_t *, ompd_thread_context_t *,
			 ompd_size_t *, const char *, const char *);

ompd_rc_t gompd_getValue (ompd_address_space_context_t *, ompd_thread_context_t *,
			  void *, ompd_address_t *, const char *, const char *);

ompd_rc_t gompd_getVariableAddress (ompd_address_space_context_t *,
				    ompd_thread_context_t *, ompd_address_t *,
				    const char *, ompd_addr_t);

ompd_rc_t gompd_getVariableSize (ompd_address_space_context_t *,
				 ompd_thread_context_t *, ompd_size_t *, const char *);

ompd_rc_t gompd_getVariableValue (ompd_address_space_context_t *, ompd_thread_context_t *,
                                  void *, ompd_address_t *, const char *);

ompd_rc_t gompd_getMemberAddress (ompd_address_space_context_t *,
				  ompd_thread_context_t *, ompd_address_t *,
				  const char *, const char *, ompd_addr_t);

ompd_rc_t gompd_getMemberSize (ompd_address_space_context_t *, ompd_thread_context_t *,
			       ompd_size_t *, const char *, const char *);

ompd_rc_t gompd_getMemberValue (ompd_address_space_context_t *, ompd_thread_context_t *,
				void *, ompd_address_t *, const char *, const char *);

#endif /* LIBGOMPD_H */
