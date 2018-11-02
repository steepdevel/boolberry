// Copyright (c) 2012-2013 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <boost/uuid/uuid.hpp>
#include "net/net_utils_base.h"
#include "p2p_protocol_defs.h"

namespace nodetool
{

  typedef boost::uuids::uuid uuid;
  typedef boost::uuids::uuid net_connection_id;


  typedef std::list<std::pair<net_utils::connection_context_base, peerid_type> > connections_list_type;

  template<class t_connection_context>
  struct i_p2p_endpoint
  {
    virtual bool relay_notify_to_all(int command, const std::string& data_buff, const epee::net_utils::connection_context_base& context)=0;
    virtual bool invoke_command_to_peer(int command, const std::string& req_buff, std::string& resp_buff, const epee::net_utils::connection_context_base& context)=0;
    virtual bool invoke_notify_to_peer(int command, const std::string& req_buff, const epee::net_utils::connection_context_base& context)=0;
    virtual bool drop_connection(const epee::net_utils::connection_context_base& context)=0;
    virtual void request_callback(const epee::net_utils::connection_context_base& context)=0;
    virtual uint64_t get_connections_count()=0;
    virtual void for_each_connection(std::function<bool(t_connection_context&, peerid_type)> f)=0;
    virtual bool block_ip(uint32_t adress)=0;
    virtual bool add_ip_fail(uint32_t adress)=0;
    virtual bool is_stop_signal_sent()=0;
    virtual bool do_idle_sync_with_peers(const connections_list_type& concts) = 0;
  };

  template<class t_connection_context>
  struct p2p_endpoint_stub: public i_p2p_endpoint<t_connection_context>
  {
    virtual bool relay_notify_to_all(int command, const std::string& data_buff, const epee::net_utils::connection_context_base& context)
    {
      return false;
    }
    virtual bool invoke_command_to_peer(int command, const std::string& req_buff, std::string& resp_buff, const epee::net_utils::connection_context_base& context)
    {
      return false;
    }
    virtual bool invoke_notify_to_peer(int command, const std::string& req_buff, const epee::net_utils::connection_context_base& context)
    {
      return true;
    }
    virtual bool drop_connection(const epee::net_utils::connection_context_base& context)
    {
      return false;
    }
    virtual void request_callback(const epee::net_utils::connection_context_base& context)
    {

    }
    virtual void for_each_connection(std::function<bool(t_connection_context&,peerid_type)> f)
    {

    }
    virtual bool is_stop_signal_sent()
    {
      return false;
    }
    virtual uint64_t get_connections_count()    
    {
      return false;
    }
    virtual bool block_ip(uint32_t adress)
    {
      return true;
    }
    virtual bool add_ip_fail(uint32_t adress)
    {
      return true;
    }
    virtual bool do_idle_sync_with_peers(const connections_list_type& concts)
    {
      return true;
    }
  };
}
