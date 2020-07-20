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

/* This file defines custom helper functions for OMPD functions.  */
   
#include "libgompd.h"

ompd_rc_t
gompd_getQuery (const char* type, const char* variable, const char *member)
{
  return ompd_rc_ok;
}

ompd_rc_t
gompd_getVariableAddress (ompd_address_space_context_t *ah,
                          ompd_thread_context_t *th, ompd_address_t *addr,
                          const char *variable, ompd_addr_t seg)
{
  return ompd_rc_ok;
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

