/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#pragma once

#include <eosio/chain/block_header_state.hpp>
#include <eosio/chain/block.hpp>
#include <eosio/chain/transaction_metadata.hpp>
#include <eosio/chain/action_receipt.hpp>

namespace eosio { namespace chain {

   struct block_state : public block_header_state {
      block_state( const block_header_state& cur ):block_header_state(cur){}
      block_state( const block_header_state& prev, signed_block_ptr b, bool trust = false );
      block_state( const block_header_state& prev, block_timestamp_type when );
      block_state() = default;

      /// weak_ptr prev_block_state....
      signed_block_ptr                                    block;
      bool                                                validated = false;
      bool                                                in_current_chain = false;
      bool                                                pbft_supported = false;

      /// this data is redundant with the data stored in block, but facilitates
      /// recapturing transactions when we pop a block
      vector<transaction_metadata_ptr>                    trxs;
   };

   using block_state_ptr = std::shared_ptr<block_state>;

} } /// namespace eosio::chain

FC_REFLECT_DERIVED( eosio::chain::block_state, (eosio::chain::block_header_state), (block)(validated)(in_current_chain)(pbft_supported) )
