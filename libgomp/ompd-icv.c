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

/* This file contains function definition related to OMPD's ICV information.
   The specifics are defined in the OpenMP API Specification 5.0, section
   5.5.9.  */

#include "omp-tools.h"
#include "libgompd.h"

ompd_rc_t ompd_enumerate_icvs (ompd_address_space_handle_t *handle,
			       ompd_icv_id_t current, ompd_icv_id_t *next_id,
			       const char **next_icv_name,
			       ompd_scope_t *next_scope, int *more) 
{
  return ompd_rc_ok;
}

ompd_rc_t ompd_get_icv_from_scope (void *handle, ompd_scope_t scope,
				   ompd_icv_id_t icv_id, ompd_word_t *icv_value)
{
  return ompd_rc_ok;
}

ompd_rc_t ompd_get_icv_string_from_scope (void *handle, ompd_scope_t scope,
				          ompd_icv_id_t icv_id,
					  const char **icv_string)
{
  return ompd_rc_ok;
}

ompd_rc_t ompd_get_tool_data (void *handle, ompd_scope_t scope,
			      ompd_word_t *value, ompd_address_t *ptr)
{
  return ompd_rc_ok;
}
