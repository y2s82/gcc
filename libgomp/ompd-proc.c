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

/* This file contains function definitions for OMPD's per-process functions
   defined in the OpenMP 5.0 API Documentation, 5.5.2.  */

#include <stdlib.h>
#include "omp-tools.h"
#include "libgompd.h"
#include "ompd-types.h"

ompd_rc_t
ompd_process_initialize (ompd_address_space_context_t *context,
			 ompd_address_space_handle_t **handle)
{
  ompd_rc_t ret;

  if (handle == NULL)
    return ompd_rc_stale_handle;
  if (context == NULL)
    return ompd_rc_bad_input;

  void *p = NULL;
  ret = gompd_callbacks.alloc_memory (sizeof (ompd_address_space_handle_t), p);
  if (ret != ompd_rc_ok)
    return ret;

  *handle = p;
  (*handle)->context = context;
  (*handle)->kind = OMPD_DEVICE_KIND_HOST;
  (*handle)->id = NULL;
  (*handle)->sizeof_id = 0;
  (*handle)->process_reference = NULL;
  (*handle)->ref_count = 0;

  return ret;
}

ompd_rc_t
ompd_device_initialize (ompd_address_space_handle_t *process_handle,
			ompd_address_space_context_t *device_context,
			ompd_device_t kind, ompd_size_t sizeof_id, void *id,
			ompd_address_space_handle_t **device_handle)
{
  /* FIXME: implementation require more association with gomp-plugin.  */

  ompd_rc_t ret;

  if (process_handle == NULL || device_handle == NULL)
    return ompd_rc_stale_handle;

  if (device_context == NULL || id == NULL)
    return ompd_rc_bad_input;

  void *p = NULL;
  ret = gompd_callbacks.alloc_memory (sizeof (ompd_address_space_handle_t), p);
  if (ret != ompd_rc_ok)
    return ret;

  *device_handle = p;
  p = NULL;

  ret = gompd_callbacks.alloc_memory (sizeof_id, p);
  if (ret != ompd_rc_ok)
    return ret;

  (*device_handle)->id = p;

  /* FIXME: implementation requires decision on id handling.  */

  (*device_handle)->sizeof_id = sizeof_id;
  (*device_handle)->context = device_context;
  (*device_handle)->kind = kind;
  (*device_handle)->ref_count = 0;
  (*device_handle)->process_reference = process_handle;
  process_handle->ref_count++;

  /* FIXME: currently returning error until implementation is fixed.  */
  return ompd_rc_error;
}

ompd_rc_t
ompd_rel_address_space_handle (ompd_address_space_handle_t *handle)
{
  ompd_rc_t ret;
  if (handle == NULL || handle->context == NULL)
    return ompd_rc_stale_handle;

  if (handle->ref_count != 0)
    return ompd_rc_unavailable;

  if (handle->process_reference)
    {
      if (handle->process_reference->ref_count == 0)
	return ompd_rc_error;
      handle->process_reference->ref_count--;
    }

  if (handle->id)
    {
      ret = gompd_callbacks.free_memory (handle->id);
      if (ret != ompd_rc_ok)
	return ret;
    }

  return gompd_callbacks.free_memory (handle);
}
