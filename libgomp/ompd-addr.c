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

/* This file contains function definition for Address Space Information, defined
   in the section 5.5.4 of OpenMP API Specification 5.0.  */

#include "omp-tools.h"
#include "libgompd.h"

ompd_rc_t
ompd_get_omp_version (ompd_address_space_handle_t *ah,
			       ompd_word_t *omp_version)
{
  ompd_rc_t ret;
  ompd_address_t verAddr;
  ret = gompd_getVariableAddress (ah->context, NULL, &verAddr, "ompd_version", verAddr.segment);

  ret = gompd_getVariableValue (ah->context, NULL, (void *)omp_version, &verAddr, "ompd_version");
  return ret;
}

ompd_rc_t
ompd_get_omp_version_string (ompd_address_space_handle_t *ah,
			    const char **string)
{
  return ompd_rc_ok;
}
