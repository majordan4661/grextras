// Copyright (C) by Josh Blum. See LICENSE.txt for licensing information.

#include <grextras/socket_message.hpp>
#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>
#include <boost/asio.hpp>
#include <gras/block.hpp>
#include <stdexcept>
#include <iostream>

namespace asio = boost::asio;
using namespace grextras;

static const PMCC DATAGRAM_KEY = PMC::make(std::string("datagram"));

static const long timeout_us = 100*1000; //100ms

#include "udp_socket_message.hpp"
#include "tcp_socket_message.hpp"

SocketMessage::sptr SocketMessage::make(
    const std::string &type,
    const std::string &addr,
    const std::string &port,
    const size_t mtu
)
{
    if (type == "UDP_SERVER" or type == "UDP_CLIENT")
    {
        return boost::make_shared<UDPSocketMessage>(type, addr, port, mtu);
    }
    if (type == "TCP_SERVER" or type == "TCP_CLIENT")
    {
        return boost::make_shared<TCPSocketMessage>(type, addr, port, mtu);
    }
    throw std::runtime_error("SocketMessage::make fail - unknown type " + type);
}