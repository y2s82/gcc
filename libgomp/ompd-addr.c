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

/* This file contains function definitions for OMPD's Address Space Information
   functions defined in the OpenMP 5.0 API Documentation, 5.5.4.  */

#include <stdlib.h>
#include <string.h>
#include "omp-tools.h"
#include "libgompd.h"

ompd_rc_t
ompd_get_omp_version (ompd_address_space_handle_t *address_space,
		      ompd_word_t *omp_version)
{
  if (omp_version == NULL)
    return ompd_rc_bad_input;
  if (address_space == NULL)
    return ompd_rc_stale_handle;

  /* _OPENMP macro is defined to have yyyymm integer.  */
  ompd_size_t macro_length = sizeof (int);

  ompd_rc_t ret = ompd_rc_ok;

  struct ompd_address_t addr;
  ret = gompd_callbacks.symbol_addr_lookup (address_space->context, NULL,
					    "openmp_version", &addr, NULL);
  if (ret != ompd_rc_ok)
    return ret;

  ret = gompd_callbacks.read_memory (address_space->context, NULL, &addr,
				     macro_length, (void *) omp_version);
  return ompd_rc_ok;
}

ompd_rc_t
ompd_get_omp_version_string (ompd_address_space_handle_t *address_space,
			     const char **string)
{
  if (string == NULL)
    return ompd_rc_bad_input;

  if (address_space == NULL)
    return ompd_rc_stale_handle;

  ompd_word_t omp_version;
  ompd_rc_t ret = ompd_get_omp_version (address_space, &omp_version);
  if (ret != ompd_rc_ok)
    return ret;

  char *tmp = "GNU OpenMP Runtime implementing OpenMP 5.0 "
	    ompd_stringify (omp_version);
  size_t s = strlen(tmp) + 1;

  char *t = NULL;
  ret = gompd_callbacks.alloc_memory (s, (void *) t);
  if (ret != ompd_rc_ok)
    return ret;

  strcpy (t, tmp);

  *string = t;

  return ret;
}
