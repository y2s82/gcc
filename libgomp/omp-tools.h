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
   in the OMPD standard */

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

typedef ompd_rc_t (*ompd_callback_memory_alloc_fn_t) (ompd_size_t nbytes,
                                                     void **ptr) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_memory_free_fn_t) (void *ptr) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_get_thread_context_for_thread_id_fn_t)
    (ompd_address_space_context_t *address_space_context, ompd_thread_id_t kind,
    ompd_size_t sizeof_thread_id, const void *thread_id,
    ompd_thread_context_t **thread_context) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_sizeof_fn_t)
    (ompd_address_space_context_t *address_space_context,
    ompd_device_type_sizes_t *sizes) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_symbol_addr_fn_t)
    (ompd_address_space_context_t *address_space_context,
    ompd_thread_context_t *thread_context, const char *symbol_name,
    ompd_address_t *symbol_addr, const char *file_name) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_memory_read_fn_t)
    (ompd_address_space_context_t *address_space_context,
    ompd_thread_context_t *thread_context, const ompd_address_t *addr,
    ompd_size_t nbytes, void *buffer) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_memory_write_fn_t) 
    (ompd_address_space_context_t *address_space_context,
    ompd_thread_context_t *thread_context, const ompd_address_t *addr,
    ompd_size_t nbytes, const void *buffer) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_device_host_fn_t) 
    (ompd_address_space_context_t *address_space_context, const void *input,
    ompd_size_t unit_size, ompd_size_t count, void *output) __GOMPD_NOTHROW;

typedef ompd_rc_t (*ompd_callback_print_string_fn_t) (const char *string,
                                                     int category) __GOMPD_NOTHROW;

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

ompd_rc_t ompd_initialize (ompd_word_t api_version,
                          const ompd_callbacks_t *callbacks) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_api_version (ompd_word_t *version) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_version_string (const char **string) __GOMPD_NOTHROW;

ompd_rc_t ompd_finalize (void) __GOMPD_NOTHROW;

ompd_rc_t ompd_process_initialize (ompd_address_space_context_t *context,
                                  ompd_address_space_handle_t **handle) __GOMPD_NOTHROW;

ompd_rc_t ompd_device_initialize (ompd_address_space_handle_t *process_handle,
                                 ompd_address_space_context_t *device_context,
                                 ompd_device_t kind, ompd_size_t sizeof_id,
                                 void *id,
                                 ompd_address_space_handle_t **device_handle) __GOMPD_NOTHROW;

ompd_rc_t ompd_rel_address_space_handle (ompd_address_space_handle_t *handle) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_omp_version (ompd_address_space_handle_t *address_space,
                               ompd_word_t *omp_version) __GOMPD_NOTHROW;

ompd_rc_t
ompd_get_omp_version_string (ompd_address_space_handle_t *address_space,
                            const char **string) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_thread_in_parallel (ompd_parallel_handle_t *parallel_handle,
                                      int thread_num,
                                      ompd_thread_handle_t **thread_handle) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_thread_handle (ompd_address_space_handle_t *handle,
                                 ompd_thread_id_t kind,
                                 ompd_size_t sizeof_thread_id,
                                 const void *thread_id,
                                 ompd_thread_handle_t **thread_handle) __GOMPD_NOTHROW;

ompd_rc_t ompd_rel_thread_handle (ompd_thread_handle_t *thread_handle) __GOMPD_NOTHROW;

ompd_rc_t ompd_thread_handle_compare (ompd_thread_handle_t *thread_handle_1,
                                     ompd_thread_handle_t *thread_handle_2,
                                     int *cmp_value) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_thread_id (ompd_thread_handle_t *thread_handle,
                             ompd_thread_id_t kind,
                             ompd_size_t sizeof_thread_id, void *thread_id) __GOMPD_NOTHROW;

ompd_rc_t
ompd_get_curr_parallel_handle (ompd_thread_handle_t *thread_handle,
                              ompd_parallel_handle_t **parallel_handle) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_enclosing_parallel_handle 
    (ompd_parallel_handle_t *parallel_handle,
    ompd_parallel_handle_t **enclosing_parallel_handle) __GOMPD_NOTHROW;

ompd_rc_t
ompd_get_task_parallel_handle (ompd_task_handle_t *task_handle,
                              ompd_parallel_handle_t **task_parallel_handle) __GOMPD_NOTHROW;

ompd_rc_t ompd_rel_parallel_handle (ompd_parallel_handle_t *parallel_handle) __GOMPD_NOTHROW;

ompd_rc_t
ompd_parallel_handle_compare (ompd_parallel_handle_t *parallel_handle_1,
                             ompd_parallel_handle_t *parallel_handle_2,
                             int *cmp_value) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_curr_task_handle (ompd_thread_handle_t *thread_handle,
                                    ompd_task_handle_t **task_handle) __GOMPD_NOTHROW;

ompd_rc_t
ompd_get_generating_task_handle (ompd_task_handle_t *task_handle,
                                ompd_task_handle_t **generating_task_handle) __GOMPD_NOTHROW;

ompd_rc_t
ompd_get_scheduling_task_handle (ompd_task_handle_t *task_handle,
                                ompd_task_handle_t **scheduling_task_handle) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_task_in_parallel (ompd_parallel_handle_t *parallel_handle,
                                    int thread_num,
                                    ompd_task_handle_t **task_handle) __GOMPD_NOTHROW;

ompd_rc_t ompd_rel_task_handle (ompd_task_handle_t *task_handle) __GOMPD_NOTHROW;

ompd_rc_t ompd_task_handle_compare (ompd_task_handle_t *task_handle_1,
                                   ompd_task_handle_t *task_handle_2,
                                   int *cmp_value) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_task_function (ompd_task_handle_t *task_handle,
                                 ompd_address_t *entry_point) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_task_frame (ompd_task_handle_t *task_handle,
                              ompd_frame_info_t *exit_frame,
                              ompd_frame_info_t *enter_frame) __GOMPD_NOTHROW;

ompd_rc_t
ompd_enumerate_states (ompd_address_space_handle_t *address_space_handle,
                      ompd_word_t current_state, ompd_word_t *next_state,
                      const char **next_state_name, ompd_word_t *more_enums) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_state (ompd_thread_handle_t *thread_handle,
                         ompd_word_t *state, ompd_wait_id_t *wait_id) __GOMPD_NOTHROW;

ompd_rc_t
ompd_get_display_control_vars (ompd_address_space_handle_t *address_space_handle,
                              const char *const **control_vars) __GOMPD_NOTHROW;

ompd_rc_t ompd_rel_display_control_vars (const char *const **control_vars) __GOMPD_NOTHROW;

ompd_rc_t ompd_enumerate_icvs (ompd_address_space_handle_t *handle,
                              ompd_icv_id_t current, ompd_icv_id_t *next_id,
                              const char **next_icv_name,
                              ompd_scope_t *next_scope, int *more) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_icv_from_scope (void *handle, ompd_scope_t scope,
                                  ompd_icv_id_t icv_id, ompd_word_t *icv_value) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_icv_string_from_scope (void *handle, ompd_scope_t scope,
                                         ompd_icv_id_t icv_id,
                                         const char **icv_string) __GOMPD_NOTHROW;

ompd_rc_t ompd_get_tool_data (void *handle, ompd_scope_t scope,
                             ompd_word_t *value, ompd_address_t *ptr) __GOMPD_NOTHROW;


#define ompd_segment_none 0

#ifdef __cplusplus
} // extern "C"
#endif

#endif
