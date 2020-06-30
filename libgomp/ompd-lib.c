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

/* This file contains function definitions for OMPD's per-library functions
   defined in the OpenMP 5.0 API Documentation, 5.5.1.  */

#include "omp-tools.h"
#include "libgompd.h"
#include <stdlib.h>

ompd_rc_t
ompd_get_api_version (ompd_word_t *version)
{
  *version = OMPD_VERSION;
  return ompd_rc_ok;
}

ompd_rc_t
ompd_get_version_string (const char **string)
{
  *string = "GNU OpenMP Runtime implementing OpenMP 5.0 "
	    ompd_stringify (OMPD_VERSION);
  return ompd_rc_ok;
}

ompd_rc_t
ompd_initialize (ompd_word_t api_version, const ompd_callbacks_t *callbacks)
{
  static int ompd_initialized = 0;

  if (!callbacks)
    return ompd_rc_bad_input;

  if (ompd_initialized)
    return ompd_rc_error;

  gompd_callbacks = malloc(sizeof(ompd_callbacks_t));
  *gompd_callbacks  = *callbacks;

  (void) api_version;

  ompd_initialized = 1;

  return ompd_rc_ok;
}

ompd_rc_t
ompd_finalize(void)
{
  free (gompd_callbacks);
  return ompd_rc_ok;
}
