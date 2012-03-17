/*
 * Copyright 2011 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_GR_BLOB_TO_STREAM_H
#define INCLUDED_GR_BLOB_TO_STREAM_H

#include <gr_core_api.h>
#include <gr_sync_block.h>

class gr_blob_to_stream;

/*!
 * \brief Make a blob to stream block
 *
 * This block reads incoming messages from the queue,
 * and copies the blob contents into the outgoing stream.
 * Non-blob message values will be ignored by the block.
 * An empty blob (length 0 bytes) tells the work to exit.
 *
 * \param item_size the size of the output stream in bytes
 * \return a new blob to stream block
 */
GR_CORE_API boost::shared_ptr<gr_blob_to_stream> gr_make_blob_to_stream(const size_t item_size);

class GR_CORE_API gr_blob_to_stream : virtual public gr_sync_block{
};

#endif /* INCLUDED_GR_BLOB_TO_STREAM_H */
