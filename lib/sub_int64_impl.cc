/* -*- c++ -*- */
/*
 * Copyright 2018 Antonio Miraglia - ISISpace.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "sub_int64_impl.h"

namespace gr {
  namespace flaress {

    sub_int64::sptr
    sub_int64::make(size_t vlen)
    {
      return gnuradio::get_initial_sptr
        (new sub_int64_impl(vlen));
    }

    /*
     * The private constructor
     */
    sub_int64_impl::sub_int64_impl(size_t vlen)
        : gr::sync_block("sub_int64",
                         io_signature::make(2, 2, sizeof(int64_t) * vlen),
                         io_signature::make(1, 1, sizeof(int64_t) * vlen)),
          d_vlen(vlen)
    {}

    /*
     * Our virtual destructor.
     */
    sub_int64_impl::~sub_int64_impl()
    {
    }

    int
    sub_int64_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
      int64_t *out = (int64_t *)output_items[0];
      const int64_t *in1 = (const int64_t *)input_items[0];
      const int64_t *in2 = (const int64_t *)input_items[1];

      for (int j = 0; j < (noutput_items * d_vlen); j++)
      {
        out[j] = in1[j] - in2[j];
      }

      return noutput_items;
    }

  } /* namespace flaress */
} /* namespace gr */

