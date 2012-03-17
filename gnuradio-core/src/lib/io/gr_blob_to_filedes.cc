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

#include <gr_blob_to_filedes.h>
#include <gr_io_signature.h>
#include <iostream>

#ifdef HAVE_IO_H
#include <io.h>
#endif
#include <unistd.h>

class gr_blob_to_filedes_impl : public gr_blob_to_filedes{
public:
    gr_blob_to_filedes_impl(const int fd, const bool close):
        gr_sync_block(
            "blob_to_filedes",
            gr_make_io_signature(0, 0, 0),
            gr_make_io_signature(0, 0, 0)
        ),
        _fd(fd),
        _close(close)
    {
        //NOP
    }

    ~gr_blob_to_filedes_impl(void){
        if (_close) close(_fd);
    }

    int work(
        int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items
    ){
        //loop for blobs until this thread is interrupted
        while (true){
            gr_tag_t msg = this->pop_msg_queue();
            if (!pmt::pmt_is_blob(msg.value)) continue;
            if (pmt::pmt_blob_length(msg.value) == 0) break; //empty blob, we are done here
            const int result = write(
                _fd,
                pmt::pmt_blob_ro_data(msg.value),
                pmt::pmt_blob_length(msg.value)
            );
            //std::cout << "wrote " << result << std::endl;
            if (result <= 0) std::cerr << "gr_tuntap_sink -> write error " << result << std::endl;
        }

        //when handle msgs finished, work is marked done
        return -1;
    }

private:
    const int _fd;
    const bool _close;
};

boost::shared_ptr<gr_blob_to_filedes> gr_make_blob_to_filedes(
    const int fd, const bool close_fd
){
    return boost::shared_ptr<gr_blob_to_filedes>(new gr_blob_to_filedes_impl(fd, close_fd));
}
