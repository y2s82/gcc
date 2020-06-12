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

/* This file contains prototypes of functions and data types defined 
   in the OMPD standard.  */

#ifndef _OMP_TOOLS_H
#define _OMP_TOOLS_H

#ifdef __cplusplus
extern "C" {
# define __GOMPD_NOTHROW throw ()
#else
# define __GOMPD_NOTHROW __attribute__((__nothrow__))
#endif

typedef __UINT64_TYPE__ ompd_wait_id_t;

typedef struct ompd_address_t {
  ompd_seg_t segment;
  ompd_addr_t address;
} ompd_address_t;

typedef struct ompd_frame_info_t {
  ompd_address_t frame_address;
  ompd_word_t frame_flag;
} ompd_frame_info_t;

typedef struct _ompd_aspace_handle ompd_address_space_handle_t;
typedef struct _ompd_thread_handle ompd_thread_handle_t;
typedef struct _ompd_parallel_handle ompd_parallel_handle_t;
typedef struct _ompd_task_handle ompd_task_handle_t;

typedef struct _ompd_aspace_cont ompd_address_space_context_t;
typedef struct _ompd_thread_cont ompd_thread_context_t;

typedef struct ompd_device_type_sizes_t {
  __UINT8_TYPE__ sizeof_char;
  __UINT8_TYPE__ sizeof_short;
  __UINT8_TYPE__ sizeof_int;
  __UINT8_TYPE__ sizeof_long;
  __UINT8_TYPE__ sizeof_long_long;
  __UINT8_TYPE__ sizeof_pointer;
} ompd_device_type_sizes_t;


const char **ompd_dll_locations;

void ompd_dll_locations_valid (void) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_memory_alloc_fn_t) (ompd_size_t,
                                                     void **) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_memory_free_fn_t) (void *) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_get_thread_context_for_thread_id_fn_t)
    (ompd_address_space_context_t *, ompd_thread_id_t,
    ompd_size_t, const void *,
    ompd_thread_context_t **) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_sizeof_fn_t)
    (ompd_address_space_context_t *,
    ompd_device_type_sizes_t *) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_symbol_addr_fn_t)
    (ompd_address_space_context_t *,
    ompd_thread_context_t *, const char *,
    ompd_address_t *, const char *) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_memory_read_fn_t)
    (ompd_address_space_context_t *,
    ompd_thread_context_t *, const ompd_address_t *,
    ompd_size_t, void *) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_memory_write_fn_t) 
    (ompd_address_space_context_t *,
    ompd_thread_context_t *, const ompd_address_t *,
    ompd_size_t, const void *) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_device_host_fn_t) 
    (ompd_address_space_context_t *, const void *,
    ompd_size_t, ompd_size_t, void *) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_print_string_fn_t) (const char *,
                                                     int ) __GOMPD_NOTHROW;

typedef struct ompd_callbacks_t {
  ompd_callback_memory_alloc_fn_t alloc_memory;
  ompd_callback_memory_free_fn_t free_memory;
  ompd_callback_print_string_fn_t print_string;
  ompd_callback_sizeof_fn_t sizeof_type;
  ompd_callback_symbol_addr_fn_t symbol_addr_lookup;
  ompd_callback_memory_read_fn_t read_memory;
  ompd_callback_memory_write_fn_t write_memory;
  ompd_callback_memory_read_fn_t read_string;
  ompd_callback_device_host_fn_t device_to_host;
  ompd_callback_device_host_fn_t host_to_device;
  ompd_callback_get_thread_context_for_thread_id_fn_t
      get_thread_context_for_thread_id;
} ompd_callbacks_t;

void ompd_bp_parallel_begin (void) __GOMPD_NOTHROW;

void ompd_bp_parallel_end (void) __GOMPD_NOTHROW;

void ompd_bp_task_begin (void) __GOMPD_NOTHROW;

void ompd_bp_task_end (void) __GOMPD_NOTHROW;

void ompd_bp_thread_begin (void) __GOMPD_NOTHROW;

void ompd_bp_thread_end (void) __GOMPD_NOTHROW;

void ompd_bp_device_begin (void) __GOMPD_NOTHROW;

void ompd_bp_device_end (void) __GOMPD_NOTHROW;

ompd_rc_t ompd_initialize (ompd_word_t,
                          const ompd_callbacks_t *) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_api_version (ompd_word_t *) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_version_string (const char **) __GOMPD_NOTHROW;

ompd_rc_t ompd_finalize (void) __GOMPD_NOTHROW;

ompd_rc_t ompd_process_initialize (ompd_address_space_context_t *,
                                  ompd_address_space_handle_t **) __GOMPD_NOTHROW;

ompd_rc_t ompd_device_initialize (ompd_address_space_handle_t *,
                                 ompd_address_space_context_t *,
                                 ompd_device_t, ompd_size_t, void *,
                                 ompd_address_space_handle_t **) __GOMPD_NOTHROW;

ompd_rc_t ompd_rel_address_space_handle (ompd_address_space_handle_t *) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_omp_version (ompd_address_space_handle_t *,
                               ompd_word_t *) __GOMPD_NOTHROW;

ompd_rc_t
ompd_get_omp_version_string (ompd_address_space_handle_t *,
                            const char **) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_thread_in_parallel (ompd_parallel_handle_t *, int,
                                      ompd_thread_handle_t **) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_thread_handle (ompd_address_space_handle_t *,
                                 ompd_thread_id_t,
                                 ompd_size_t, const void *,
                                 ompd_thread_handle_t **) __GOMPD_NOTHROW;

ompd_rc_t ompd_rel_thread_handle (ompd_thread_handle_t *) __GOMPD_NOTHROW;

ompd_rc_t ompd_thread_handle_compare (ompd_thread_handle_t *,
                                     ompd_thread_handle_t *, int *) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_thread_id (ompd_thread_handle_t *,
                             ompd_thread_id_t,
                             ompd_size_t, void *) __GOMPD_NOTHROW;

ompd_rc_t
ompd_get_curr_parallel_handle (ompd_thread_handle_t *,
                              ompd_parallel_handle_t **) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_enclosing_parallel_handle 
    (ompd_parallel_handle_t *,
    ompd_parallel_handle_t **) __GOMPD_NOTHROW;

ompd_rc_t
ompd_get_task_parallel_handle (ompd_task_handle_t *,
                              ompd_parallel_handle_t **) __GOMPD_NOTHROW;

ompd_rc_t ompd_rel_parallel_handle (ompd_parallel_handle_t *) __GOMPD_NOTHROW;

ompd_rc_t
ompd_parallel_handle_compare (ompd_parallel_handle_t *,
                             ompd_parallel_handle_t *, int *) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_curr_task_handle (ompd_thread_handle_t *,
                                    ompd_task_handle_t **) __GOMPD_NOTHROW;

ompd_rc_t
ompd_get_generating_task_handle (ompd_task_handle_t *,
                                ompd_task_handle_t **) __GOMPD_NOTHROW;

ompd_rc_t
ompd_get_scheduling_task_handle (ompd_task_handle_t *,
                                ompd_task_handle_t **) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_task_in_parallel (ompd_parallel_handle_t *, int,
                                    ompd_task_handle_t **) __GOMPD_NOTHROW;

ompd_rc_t ompd_rel_task_handle (ompd_task_handle_t *) __GOMPD_NOTHROW;

ompd_rc_t ompd_task_handle_compare (ompd_task_handle_t *,
                                   ompd_task_handle_t *, int *) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_task_function (ompd_task_handle_t *,
                                 ompd_address_t *) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_task_frame (ompd_task_handle_t *,
                              ompd_frame_info_t *,
                              ompd_frame_info_t *) __GOMPD_NOTHROW;

ompd_rc_t
ompd_enumerate_states (ompd_address_space_handle_t *,
                      ompd_word_t, ompd_word_t *,
                      const char **, ompd_word_t *) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_state (ompd_thread_handle_t *,
                         ompd_word_t *, ompd_wait_id_t *) __GOMPD_NOTHROW;

ompd_rc_t
ompd_get_display_control_vars (ompd_address_space_handle_t *,
                              const char *const **) __GOMPD_NOTHROW;

ompd_rc_t ompd_rel_display_control_vars (const char *const **) __GOMPD_NOTHROW;

ompd_rc_t ompd_enumerate_icvs (ompd_address_space_handle_t *,
                              ompd_icv_id_t, ompd_icv_id_t *, const char **,
                              ompd_scope_t *, int *) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_icv_from_scope (void *, ompd_scope_t,
                                  ompd_icv_id_t, ompd_word_t *) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_icv_string_from_scope (void *, ompd_scope_t,
                                         ompd_icv_id_t, const char **) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_tool_data (void *, ompd_scope_t,
                             ompd_word_t *, ompd_address_t *) __GOMPD_NOTHROW;


#define ompd_segment_none 0

#ifdef __cplusplus
} // extern "C"
#endif

#endif
