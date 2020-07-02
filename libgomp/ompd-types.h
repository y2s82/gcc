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

/* This file contains various library-defined data types for OMPD library.  */

#ifndef OMPD_TYPES_H
#define OMPD_TYPES_H 1

#include "omp-tools.h"

#define OMPD_TYPES_VERSION   20180906 /* YYYYMMDD Format */

/* Kinds of device threads  */
#define OMPD_THREAD_ID_PTHREAD      ((ompd_thread_id_t) 0)
#define OMPD_THREAD_ID_LWP	    ((ompd_thread_id_t) 1)
#define OMPD_THREAD_ID_WINTHREAD    ((ompd_thread_id_t) 2)
#define OMPD_THREAD_ID_CUDALOGICAL  ((ompd_thread_id_t) 3)
/* The range of non-standard implementation defined values */
#define OMPD_THREAD_ID_LO       ((ompd_thread_id_t) 1000000)
#define OMPD_THREAD_ID_HI       ((ompd_thread_id_t) 1100000)

/* Target Cuda device-specific thread identification */
typedef struct ompd_dim3_t {
  ompd_addr_t x;
  ompd_addr_t y;
  ompd_addr_t z;
} ompd_dim3_t;

typedef struct ompd_cudathread_coord_t {
  ompd_addr_t cudaDevId;
  ompd_addr_t cudaContext;
  ompd_addr_t warpSize;
  ompd_addr_t gridId;
  ompd_dim3_t  gridDim;
  ompd_dim3_t  blockDim;
  ompd_dim3_t  blockIdx;
  ompd_dim3_t  threadIdx;
} ompd_cudathread_coord_t;

/* Memory Access Segment definitions for Host and Target Devices */
#define OMPD_SEGMENT_UNSPECIFIED	     ((ompd_seg_t) 0)

/* Cuda-specific values consistent with those defined in cudadebugger.h */
#define OMPD_SEGMENT_CUDA_PTX_UNSPECIFIED    ((ompd_seg_t) 0)
#define OMPD_SEGMENT_CUDA_PTX_CODE	     ((ompd_seg_t) 1)
#define OMPD_SEGMENT_CUDA_PTX_REG	     ((ompd_seg_t) 2)
#define OMPD_SEGMENT_CUDA_PTX_SREG	     ((ompd_seg_t) 3)
#define OMPD_SEGMENT_CUDA_PTX_CONST	     ((ompd_seg_t) 4)
#define OMPD_SEGMENT_CUDA_PTX_GLOBAL	     ((ompd_seg_t) 5)
#define OMPD_SEGMENT_CUDA_PTX_LOCAL	     ((ompd_seg_t) 6)
#define OMPD_SEGMENT_CUDA_PTX_PARAM	     ((ompd_seg_t) 7)
#define OMPD_SEGMENT_CUDA_PTX_SHARED	     ((ompd_seg_t) 8)
#define OMPD_SEGMENT_CUDA_PTX_SURF	     ((ompd_seg_t) 9)
#define OMPD_SEGMENT_CUDA_PTX_TEX	     ((ompd_seg_t) 10)
#define OMPD_SEGMENT_CUDA_PTX_TEXSAMPLER     ((ompd_seg_t) 11)
#define OMPD_SEGMENT_CUDA_PTX_GENERIC	     ((ompd_seg_t) 12)
#define OMPD_SEGMENT_CUDA_PTX_IPARAM	     ((ompd_seg_t) 13)
#define OMPD_SEGMENT_CUDA_PTX_OPARAM	     ((ompd_seg_t) 14)
#define OMPD_SEGMENT_CUDA_PTX_FRAME	     ((ompd_seg_t) 15)

/* Kinds of device device address spaces */
#define OMPD_DEVICE_KIND_HOST     ((ompd_device_t) 1)
#define OMPD_DEVICE_KIND_CUDA     ((ompd_device_t) 2)
/* The range of non-standard implementation defined values */
#define OMPD_DEVICE_IMPL_LO       ((ompd_device_t) 1000000)
#define OMPD_DEVICE_IMPL_HI       ((ompd_device_t) 1100000)

#endif /* OMPD_TYPES_H */
