// Copyright (c) 2014-2023, The Monero Project
// Copyright (c) 2021-2023, Haku Labs MTÜ
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// Parts of this file are originally copyright (c) 2012-2013 The Cryptonote developers

#include <unordered_set>
#include <random>
#include "include_base_utils.h"
#include "string_tools.h"
using namespace epee;

#include "common/apply_permutation.h"
#include "cryptonote_tx_utils.h"
#include "cryptonote_config.h"
#include "blockchain.h"
#include "cryptonote_basic/miner.h"
#include "cryptonote_basic/tx_extra.h"
#include "crypto/crypto.h"
#include "crypto/hash.h"
#include "ringct/rctSigs.h"

using namespace crypto;

namespace cryptonote
{
  //---------------------------------------------------------------
  void classify_addresses(const std::vector<tx_destination_entry> &destinations, const boost::optional<cryptonote::account_public_address>& change_addr, size_t &num_stdaddresses, size_t &num_subaddresses, account_public_address &single_dest_subaddress)
  {
    num_stdaddresses = 0;
    num_subaddresses = 0;
    std::unordered_set<cryptonote::account_public_address> unique_dst_addresses;
    for(const tx_destination_entry& dst_entr: destinations)
    {
      if (change_addr && dst_entr.addr == change_addr)
        continue;
      if (unique_dst_addresses.count(dst_entr.addr) == 0)
      {
        unique_dst_addresses.insert(dst_entr.addr);
        if (dst_entr.is_subaddress)
        {
          ++num_subaddresses;
          single_dest_subaddress = dst_entr.addr;
        }
        else
        {
          ++num_stdaddresses;
        }
      }
    }
    LOG_PRINT_L2("destinations include " << num_stdaddresses << " standard addresses and " << num_subaddresses << " subaddresses");
  }
  //---------------------------------------------------------------
  keypair get_deterministic_keypair_from_height(uint64_t height)
  {
    keypair k;

    ec_scalar& sec = k.sec;

    for (int i=0; i < 8; i++)
    {
      uint64_t height_byte = height & ((uint64_t)0xFF << (i*8));
      uint8_t byte = height_byte >> i*8;
      sec.data[i] = byte;
    }
    for (int i=8; i < 32; i++)
    {
      sec.data[i] = 0x00;
    }

    generate_keys(k.pub, k.sec, k.sec, true);

    return k;
  }
  //---------------------------------------------------------------
  uint64_t get_diardi_reward(uint64_t height, uint64_t base_reward)
  {
    return base_reward / 4;
  }
  //---------------------------------------------------------------

  bool get_deterministic_output_key(const account_public_address& address, const keypair& tx_key, size_t output_index, crypto::public_key& output_key)
  {

    crypto::key_derivation derivation = AUTO_VAL_INIT(derivation);
    bool r = crypto::generate_key_derivation(address.m_view_public_key, tx_key.sec, derivation);
    CHECK_AND_ASSERT_MES(r, false, "failed to generate_key_derivation(" << address.m_view_public_key << ", " << tx_key.sec << ")");

    r = crypto::derive_public_key(derivation, output_index, address.m_spend_public_key, output_key);
    CHECK_AND_ASSERT_MES(r, false, "failed to derive_public_key(" << derivation << ", "<< address.m_spend_public_key << ")");

    return true;
  }
  //---------------------------------------------------------------
  std::string diardi_index_to_reward_v1(uint64_t height)
  {
    std::list<std::string> listOfAddresses = {
      "SvjVucMW4PA968WJP7rXRr1fkRVch5q6rLnh86LkZCWFPJiDEB2vizX6VjMezJaKiCN2K1kVvAHDbUmiB1tPjZJP2hety4dnf",
      "SvjVucMW4PA968WJP7rXRr1fkRVch5q6rLnh86LkZCWFPJiDEB2vizX6VjMezJaKiCN2K1kVvAHDbUmiB1tPjZJP2hety4dnf",
      "Svkw5aecRCmgru6t4Jigi9KN3HrENz3VmFVtBmaGJhNVWmUGc6hv5P9Qhi6Uivns49BG1H6WBVWoY85Si8PdYcfN2umFos7KU",
      "Svkw5aecRCmgru6t4Jigi9KN3HrENz3VmFVtBmaGJhNVWmUGc6hv5P9Qhi6Uivns49BG1H6WBVWoY85Si8PdYcfN2umFos7KU",
      "SvkdzwcuUzy1p25pvipH5QB4usEGJ9aBB7ucPrg2fvoKQh8jW6wQnYYTdFsQ6Gg2uVPPLgWt1pzaKVa6zeTmfv3j2XLefxByh",
      "SvkdzwcuUzy1p25pvipH5QB4usEGJ9aBB7ucPrg2fvoKQh8jW6wQnYYTdFsQ6Gg2uVPPLgWt1pzaKVa6zeTmfv3j2XLefxByh",
      "SvjayKidE9SGRX2E5dJWdQbhVfq4nf4tQJkUQ5bBUdgALqiUewJfWQwbmptDEmKqeqc4tRb26duxe3483w2RZRXQ2MPKDzw3a",
      "SvkKGjieJuuMgxyCC3nXJUJDj2CuibeFRL6qan46zw8NCRMPyRtwehjjYG2qqekuUnCW5zmeu27fBLqn1xkQFRkc1wzscXzvo",
      "Svk7VUPASsbZhFErf8rEfuEEX94GWsSWKVS8GNAUDfH363EsSLZ58wd3rph8okcaFALthwMkQ4fWJBzYYjqA3Lk61McroQbno",
      "Svk7VUPASsbZhFErf8rEfuEEX94GWsSWKVS8GNAUDfH363EsSLZ58wd3rph8okcaFALthwMkQ4fWJBzYYjqA3Lk61McroQbno",
      "Svk7Uv5WsovHiooYMa9jtcSdgKJcBztLE5n8A8HSp7s8UXnMdVoNLBf2tKchEqW4Ma6wW27Rb2ntPQqrFZT26hhE25fenVvyp",
      "SvmCQeq1VL2GxLpQznvwF7eHCYd77j9V32fmVVzcfDUSJ4VU3sb5riBdCVYZmk3oVF4b6wqRhPbAbf5oWTC9EFUY16XcZ75cL",
      "SvkKRajEKEnhEUWFXMrHFdRxE7vmYJaifTRoGrNyDPksZqxWGm8NeJi6UaFXDbXVaGEVAiVYPHmsyaFNAcq5qGLR1BzriKyiM",
      "SvkL8FpayF6R4RucZC4L1wcuVFZwPAf52dECSrr2LiViGVGv3YVKnjz9rsfcxkVLJaTaB24JUico23bEjXtpkEMo1eyhRtk6Z",
      "SvjssTR8XNsRxGZeyFnXj9LvHD5c3EZM8XdquLZoBNjrKHcFN3KCzTR5L3yjTvoFCv9usqd9vFbkaiyqyJFFQw9g2KLoCyL6B",
      "SvkWYULscDkRuWZwuVAywHjpFMqVA3beZQPPVDBUiE6YUFwVL4LqTY348Yazdwwa6VbhhBLKTW295T5bPbizzF9837VDwp4bU"
    };

    if((height % 16) == 0){
      std::list<std::string>::iterator it = listOfAddresses.begin();
      std::advance(it, 15);
      return *it;
    }else{
      std::list<std::string>::iterator it = listOfAddresses.begin();
      uint64_t y = (height % 16) - 1;
      std::advance(it, y);
      return *it;
    }
  }
  //---------------------------------------------------------------
  bool validate_diardi_reward_key(uint64_t height, const std::string& diardi_wallet_address_str, size_t output_index, const crypto::public_key& output_key, network_type nettype)
  {
    keypair diardi_key = get_deterministic_keypair_from_height(height);

    cryptonote::address_parse_info diardi_wallet_address;
    
    switch(nettype) {
      case STAGENET:
        cryptonote::get_account_address_from_str(diardi_wallet_address, cryptonote::STAGENET, diardi_wallet_address_str);
        break;
      case TESTNET:
        cryptonote::get_account_address_from_str(diardi_wallet_address, cryptonote::TESTNET, diardi_wallet_address_str);
        break;
      case MAINNET:
        cryptonote::get_account_address_from_str(diardi_wallet_address, cryptonote::MAINNET, diardi_wallet_address_str);
        break;
      default:
        cryptonote::get_account_address_from_str(diardi_wallet_address, cryptonote::MAINNET, diardi_wallet_address_str);
        break;
    }

    crypto::public_key correct_key;

    if (!get_deterministic_output_key(diardi_wallet_address.address, diardi_key, output_index, correct_key))
    {
      MERROR("Failed to generate deterministic output key for diardi wallet output validation");
      return false;
    }

    return correct_key == output_key;
  }
  //---------------------------------------------------------------

  std::list<std::string> diardi_addresses_v2(network_type nettype) {
    std::list<std::string> mainnet_addresses = {};
    std::list<std::string> testnet_addresses = {
      "Tsz4ksnHAQxP7pjCxyZ2fmh4yc7QFSS5zftXAWqXpEhtGTtQt3qvLMdE1Db1nvvLVN2d5npSMxWd3Poom1G6VDey7QGUeGnde5:09473dc481843b92a1b757dc8cef8de0f93ef97acde87f70fa0a0ccf0f5c7359",
      "Tsz54FHBmwwdoiVuAcigRbELu6W3paXxWU9g8hccp9zDZLfBFRVLnhqDComgXoHGtui88qMCWtAsgRRTsnGwzEYW5TfpgJ9GAL:a33e8145b2dc0b9bbc5063d2464fc5e4674e8cc6e3a2510f1b9563a7fec15784",
      "Tsz52AyB4AmhzN6x8hjM6bSGiSbVUjXCL9eA9gJ62ppf7aNnLKw7UuK4CEzintMuge8ZVMaREXSCxjNt9dqjUDkN3yCXQ8LPaA:90dbb9d292f50eb259c5c91fc49715c79d4786638933a8b93b3af2f240274fde",
      "Tsz4xjr6EA78LMR3qzweAEgwW7Yw4xUjvQU533Ps4jUnGXQLzqqMvi68BzvZ9z3kKa2iRUxP81E3M3sR8F8pPzbt9LAbiG7RYy:726db0083c2bd855a9b0a2a9cbeec8a6f1d20717cd8c4c5f88a904450b5cd021",
      "Tsz4k8ofKTpWhz8pUhBTxUWS8YpxzM2eWeEvbDMR7yYfEiVvwZ3vz8K939vZLG1DhnWJ8LXqFs3qkbsP5vyQJD2f7Ae6TZnEXQ:02b5ee660bb19ab9763dc90669aff856cbac643ef3dea4d17c2fe9d8fc51ffe5",
      "Tsz4yAo5vynhHE44YSMLrHX3kTjzvYuHcCNNwbhc3CmGYgiWN76vXLibxy62sTJfaUH3ZmchtcpAQLb9VzB5YWo84jnYDyasWx:763db55bf1f0d11cb31234d426b3a4452b5a188d5b43f7e6e3e5a4e793bd6e46",
      "Tsz4omXdhN8fjoSmMSoSBPLzTW5CduzX3X7LomQPuM9CbxNeZ4YsufLHbm4e4wBtHoPwjDLysm8p9AKMqT7FJ7tv7aQjuU4V6Q:22e9d7f369e7995a6d26d1d89e778426210c9a0192b4030fb38e8bc68bd0fb06",
      "Tsz53NS37gf1ZwGy1B3F1WKwezQbZBGwuExhRaBxs4z2KYk5fK1dr8LbN3QwZEAWeLHv9B6ivZfGh6FEdx2UMsmRASKjG7e4LX:9b7941e45403651ee84b310085713fafd60215479c53769003e067f3176ee312",
      "Tsz53E4u7HeKwVTTEYRuJihgDtNzGp8YSNBvFY5NUTj8eDMQ6iNdktzBTo1p8qDSWhcUt9WSZgAgTbLNLyDZZTPt4WngGmesby:9a32062e8d713b596b9f4ee4a3f32ff7d4b2f441c37ead1d6c387d4bfbde7b54",
      "Tsz4tDBp2MtBGhAQW4KXvYHYPwD2PskRp3cjN9ch723NSAoqRjQ2PskUsKeoKY3RMcMkr94qQYcf9JbESVULNKSy1WUrVyvgRq:4a49ed38973d675679c25e6bb962e4db75796dc97b0fa3ea2dee1ad87d9679e7",
      "Tsz514QzPKsj96oseEgVbNZfXWz1yuBtq2vko45X5xM8Ygb9wJNEM4KHq4uBEcZGRMYRaRufNu4LdXnQtcqoxxfA2XoswQHVVD:86fe370496fbefc1db38b51641c34968cea52889860b85080368eee50bbd6aed",
      "Tsz54UiDc48CN9KNz8ULQYN36GXT8pQ7nFME3MeHha5e1MwrQ3DBSi2APXv7gQgZzS58aNTv5mKwjQQTJiDFvgag5czEGnXSg9:a54bf957b143f1b402f5bd43897dc42d63c7be50cd55c90936826559110228b9",
      "Tsz5C1N2dwNF8vS6wzEWM2jktkwN2C5KPVu3j4xTyNcxYoZzz2DTcTz1nRLASsSEZ3eeme1USFarMTpzynzsgr4q8Pee9cYk82:e806a1b59954845d634a2516b5ffa041462b2939a2acc41b17fa2c5399be231f",
      "Tsz5ASRjtcf3551DxC77RGKgbHT4xyMPBBrqnmZESVac7agZ169WSndX5zPZsbNTrSBMv4etujgsn1jEvZUnwmuw5UH5ys2KFK:da210a7e300c606c4aa8bfa5576fb22cece0269e6640ec776ec879e0c52757f4",
      "Tsz59wAhTbXVV46A7yeXkr8pLcQRfUT17BpY15iWJVKPdMHi86qRXBhQFeUYd8YSMybcBmjSJmmHJ8goXcumZQMM9yGhck1pta:d5a85c0a0aaa4af373ff72b0ef2ebad7a5df1b038640af98d1799c2832d9523b",
      "Tsz4uCSMeLyTXdsRtwyFGq6oEuAEpQr4VGVzNZYbmsKUcXUTyhSshRpVYiDukfJRKvDQJ43foLEShfjTwYNJVKxw56yAsvVQgu:5309afc3ca9e9a0c8299a41f8e22a8cec16814c4965caad60d6018a017d4647c",
      "Tsz4rgd26kBLZdx2C4qcnb88TJGhSVJMJD7EHQC1TJh4Tdjp1c6eA7hfCS8EDQdGT4HNsHSJdXqmmjBCMmWDA24W4ToG1fB4hT:3cc1146e0474f5318e95b3ea902a9e59e4479a442d4862a94cd16e6f279f3b14",
      "Tsz4pv3mna6AF3e4gYAumvjhpKbqXWRMYJyTvjfwnU7vS9VncxKuSpoP2JQrB4aAtEgSpRifXhzLAVJ5ck9UVz3A2pi3d6Gb6D:2d1438243337415a7eca9f6a75ff4f124134f684ef6b74e7f3fbac558596574d",
      "Tsz4u4W5mwqb4AtQ7r7Dy945BinjHm5iSdCqGpsMoMQ8YobGKhRH1pAdiiULqVAmEZQry2orioA1jLtsb4hqs5pg7dbsP2KskY:51d3398c6ccb997a9aa8232f68125e00bd90dbffd3d873193862d97efdbe23b2",
      "Tsz4kVWhmyKL3zd5Xou2j3Skyb23gh7VAQRgaTqijEXpUebMTtbYNx95SGApCS5Zs1hKiyyrdKZx5WQpx7yDE6eH4ME6HPZWDt:05e00d9ec271e6f2f4ccdad46a99ff8b4696cfb9698c0d60eda8fb11efa54c25",
      "Tsz4t1gJLpvKXMKCZvK8Cc2neKb7tniubV4Ytnv6WT6VJtWCtucicBbQjus7JURViyfNCgUhXUnnEE6H4eZrugs8A8Kk99KFVd:4887adf1df6ebe53134bec877d0aaefab18b654826a7c458ee4000b69e6af200",
      "Tsz4vpMv4TuSW3whtfHo9HdHMAxTAv7quhp8qqzcGKXuNXAZiNThephWsL14ce8Q9RMJA8FZg2xCq8pskRPz6gWrAgYvCF9EAq:73e5d5da42b291421622e52d2c79573bc401d635022ec9026678b99bd7ff7d46",
      "Tsz4xFWGV8DGBXahWmnuGnPccAuz13oTdLtjxSxZ9s1oYEhHi6iumiDVvg3E3GvHjE6ipFJFbQuwXVxTrfAgPGWf5YbKYnmePx:6e18e72fba5ac3a82b9ac1ac4b87331f2eb3bdd3f076ed4e28e7eecb96babf9f",
      "Tsz4x4Vd1hSLGk7aqywaZaazyvsRDiQUCMj14WAbDmEZ3NZLTQpTiHK75YQkETtGkYRg2ZxfvEBfMRsLasCf4cmd1HhQYtm6Qd:6c6a2051a9733765853d8eb135cb45541dff69b38d7be6d164212f06a20e2dea",
      "Tsz4tNtPoER4VrbcJd14GcQcfuoBdRwovL9xgM1J7CpZhiuyPjoE35eDN2TEGpLS5VURhrtVrmuraC4m11by6F5V5sqyTJKXsk:4bc565b28214e902bf802205958d2f58dbf56883f97284651195b87fd2f376fb",
      "Tsz554Psk2aVwrXtUgRFDxJpPZi2EBukBgzfiDJPShNq2vdhWnGjotmeH948Fd9YL1hYtLEHD1JMu9xexicRqJ695rhiVAUigQ:aa71bf2977ad0e2db0bbd74ab76a856d166a800a58ef1c2f0d9d1414fa0b81cd",
      "Tsz55cLju1Z9o1JuB1urUZ5k3cVcvhkHK1sJkRazKpTcdiAazjsNJiRZiSuyJ4Jo8UUjgi5WAc4eY265TmJ1bdms5ewq6fzU68:af53887b103492323e26ff96021c59fbb223f546ae052f7e0d0f153723db7925",
      "Tsz4nucXCkaL5DW7GY8ersPxNQWvxtqYjWzPNsWVUuTPfxm12ip4sFAL3cf6ctNvSa1gRaBoUVaWjHcMoK9HiStZ76N8coeHeG:1b490b868b7207328547deb7e8893ca034c0b8c638b34b833695531d62e8ef4a",
      "Tsz58e325DVNsY2vZ3X7y7asxeBXeuSE9112fsfBMdHCNEEPYPuZVAPbWAAMGatRuhCqsrrgJwwRGX6uFHM3fiz61RZRpNtgGD:ca2d09568c82c28a58b7ea171eca8c0638173019ae0000c2894de988bb7eea24",
      "Tsz4qauJvUDLNFUXLpXcAcYiqgsqkaVyQNfCMZTthN26DhREJq7Cgo4URteCZ1oLBGEFSKVFrrAEjdUhaVT4uRqs5kKvANSAoY:330443eca673c8b25c1d9a5299bda65149daa2e38f817ced5275d3abe34be8d8",
      "Tsz4oBSMpmiZ5wZ3VQfpyuU2CMCidkNcG9YE9KnL4X6HWMz6x2RkajcKTTEu6JaZ4kdDZ4Xnbz4pdKzjKBAnKvWF8PtS8tkNqr:1db42431adbfd324229e06fce0a18bb3105a79b549330c35ea0f2dd6b2af8af1",
      "Tsz4uyPv4MA6uLVekkBXWTQjZjgAQRauG6qmsTz76m34iGbrtjv3D5u8V7cJDjXL713BLCwd2maL3X2bcaXRmiRR3e24ko44Ni:65ab7540ec2cbf8c61006ba7980d05ab697ce65064b385db3e809ef32c459e75",
      "Tsz5AJhtGhdPMasefYx6LHRTgZWCPzSz6a3fUDkCHb9T3HX9AkNcZPZcshHEtLVA3fWjgYFc44hb9eJqyC2bY6P19B4hkLwW8Y:d8f2f495a885a6b4cbf924249a923cabfa5f4b25dbc5919232935799420da8f9",
      "Tsz5AYGtLpHL9UfaeJ9H6Gb4ETbRDJi2GADSqsDrv5jBJFo8ET2WkcXVLvh9jamcTTZJQaeHhPfRk7vCjkKtVdVK7Fjx1qFRRW:db05ccd3ea7277a64c1b371721cb9b1aaeb077a3f53717223c58895176672954",
      "Tsz5DrBvZa8SATZzTnZRDdMsnX7PUBEQmXwZCvfjkFckfx1iSF7iGo7cd4y51UDBdCBwYcAFAYq7NK8SJLHyrYcs2MYp9aXD7Z:f859dc46899670aee0f329dd8c7cce9b6c872f23b6b8fb57dce7ff71e9e8db98"
    };

    std::list <std::string> stagenet_addresses = {
      "StS1Bvcb33MQ9EpqUVzBwEfsU3523GfZr8Rwm2tA1KjbCs9p4L8xK3h5eJ3HEx3b9HEqYTceqB3r1Tw2u6EqmYSZ46kd5arWS4:046d45a0f08a5b72d754100ab9e863a130fe5647e12c6be6f20a6d10de46ef30",
      "StS1ef6jTsWDDZ7CDpAYVEFhEQNANgSX26bfscJUuUNSci4R9tchPwQeDTvXf1yY9ARddZiNXnXo2eck5XpxY3Hx7PkEfn8qnb:f15f3854f949098e48719fde5957d8f7ba398d2a1921778276b51fddd7d57bd1",
      "StS1X45Z1QEQGvY2EYz3BHHWkFyWiEKTu2ExjtdGe9CqFeRmMPDk2uhYukGUmYbHJeKzqEhD5msQqcxidHakujUc3EvPuZhrvq:adf9a925e38b263be592dd805462b953c46adf3f58076aeeaee06846c6578ef8"
    };

    switch (nettype)
    {
      case MAINNET:
        return mainnet_addresses;
      case TESTNET:
        return testnet_addresses;
      case STAGENET:
        return stagenet_addresses;
      case FAKECHAIN:
        return mainnet_addresses;
      default: 
        return mainnet_addresses;
      throw std::runtime_error("Invalid network type passed for getting Diardi v2 addresses");
    }
  }
  //---------------------------------------------------------------
  bool construct_miner_tx(size_t height, size_t median_weight, uint64_t already_generated_coins, size_t current_block_weight, uint64_t fee, const account_public_address &miner_address, transaction& tx, const blobdata& extra_nonce, size_t max_outs, uint8_t hard_fork_version) {
    tx.vin.clear();
    tx.vout.clear();
    tx.extra.clear();

    keypair txkey = keypair::generate(hw::get_device("default"));
    add_tx_pub_key_to_extra(tx, txkey.pub);
    if(!extra_nonce.empty())
      if(!add_extra_nonce_to_tx_extra(tx.extra, extra_nonce))
        return false;
    if (!sort_tx_extra(tx.extra, tx.extra))
      return false;

    txin_gen in;
    in.height = height;

    uint64_t block_reward = size_t(0);
    uint64_t diardi_reward = size_t(0);

    if(!get_block_reward(median_weight, current_block_weight, already_generated_coins, block_reward, hard_fork_version, height))
    {
      LOG_PRINT_L0("Block is too big");
      return false;
    }

    #if defined(DEBUG_CREATE_BLOCK_TEMPLATE)
      LOG_PRINT_L1("Creating block template: reward " << block_reward << ", fee " << fee);
    #endif

    if (height > 15 && hard_fork_version <= 12) {
      diardi_reward = get_diardi_reward(height, block_reward);
      block_reward -= diardi_reward;
    }

    block_reward += fee;

    // from hard fork 2, we cut out the low significant digits. This makes the tx smaller, and
    // keeps the paid amount almost the same. The unpaid remainder gets pushed back to the
    // emission schedule
    // from hard fork 4, we use a single "dusty" output. This makes the tx even smaller,
    // and avoids the quantization. These outputs will be added as rct outputs with identity
    // masks, to they can be used as rct inputs.
    if (hard_fork_version >= 2 && hard_fork_version < 4) {
      block_reward = block_reward - block_reward % ::config::BASE_REWARD_CLAMP_THRESHOLD;
    }

    std::vector<uint64_t> out_amounts;
    decompose_amount_into_digits(block_reward, hard_fork_version >= 2 ? 0 : ::config::DEFAULT_DUST_THRESHOLD,
      [&out_amounts](uint64_t a_chunk) { out_amounts.push_back(a_chunk); },
      [&out_amounts](uint64_t a_dust) { out_amounts.push_back(a_dust); });

    CHECK_AND_ASSERT_MES(1 <= max_outs, false, "max_out must be non-zero");
    if (height == 0 || hard_fork_version >= 4)
    {
      // the genesis block was not decomposed, for unknown reasons
      while (max_outs < out_amounts.size())
      {
        //out_amounts[out_amounts.size() - 2] += out_amounts.back();
        //out_amounts.resize(out_amounts.size() - 1);
        out_amounts[1] += out_amounts[0];
        for (size_t n = 1; n < out_amounts.size(); ++n)
          out_amounts[n - 1] = out_amounts[n];
        out_amounts.pop_back();
      }
    }
    else
    {
      CHECK_AND_ASSERT_MES(max_outs >= out_amounts.size(), false, "max_out exceeded");
    }

    uint64_t summary_amounts = 0;
    for (size_t no = 0; no < out_amounts.size(); no++)
    {
      crypto::key_derivation derivation = AUTO_VAL_INIT(derivation);
      crypto::public_key out_eph_public_key = AUTO_VAL_INIT(out_eph_public_key);
      bool r = crypto::generate_key_derivation(miner_address.m_view_public_key, txkey.sec, derivation);
      CHECK_AND_ASSERT_MES(r, false, "while creating outs: failed to generate_key_derivation(" << miner_address.m_view_public_key << ", " << txkey.sec << ")");

      r = crypto::derive_public_key(derivation, no, miner_address.m_spend_public_key, out_eph_public_key);
      CHECK_AND_ASSERT_MES(r, false, "while creating outs: failed to derive_public_key(" << derivation << ", " << no << ", "<< miner_address.m_spend_public_key << ")");

      uint64_t amount = out_amounts[no];
      summary_amounts += amount;

      bool use_view_tags = hard_fork_version >= HF_VERSION_VIEW_TAGS;
      crypto::view_tag view_tag;
      if (use_view_tags)
        crypto::derive_view_tag(derivation, no, view_tag);

      tx_out out;
      cryptonote::set_tx_out(amount, out_eph_public_key, use_view_tags, view_tag, out);

      tx.vout.push_back(out);


      if (hard_fork_version >= 2 && hard_fork_version <= 12 && (height >= 16)) {
        if (already_generated_coins != 0) {
          keypair diardi_key = get_deterministic_keypair_from_height(height);
          add_tx_pub_key_to_extra(tx, diardi_key.pub);

          cryptonote::address_parse_info diardi_wallet_address;
          std::string diardi_maintainer_address;
          diardi_maintainer_address = diardi_index_to_reward_v1(height);

          cryptonote::get_account_address_from_str(diardi_wallet_address, cryptonote::MAINNET, diardi_maintainer_address);
          crypto::public_key out_eph_public_key = AUTO_VAL_INIT(out_eph_public_key);

          if(!get_deterministic_output_key(diardi_wallet_address.address, diardi_key, 1, out_eph_public_key))
          {
            MERROR("Failed to generate deterministic output key for Diardi V1 wallet output creation");
            return false;
          }

          txout_to_key tk;
          tk.key = out_eph_public_key;

          tx_out out;
          summary_amounts += out.amount = diardi_reward;
          out.target = tk;
          tx.vout.push_back(out);

          CHECK_AND_ASSERT_MES(summary_amounts == (block_reward + diardi_reward), false, "Failed to construct miner tx, summary_amounts = " << summary_amounts << " not equal total block_reward = " << (block_reward + diardi_reward));
        }
      }
    }

    CHECK_AND_ASSERT_MES(summary_amounts == block_reward, false, "Failed to construct miner tx, summary_amounts = " << summary_amounts << " not equal block_reward = " << block_reward);

    if (hard_fork_version >= 4) {
      tx.version = 2;
    }
    else {
      tx.version = 1;
    }

    //lock
    tx.unlock_time = height + CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW;
    tx.vin.push_back(in);

    tx.invalidate_hashes();

    //LOG_PRINT("MINER_TX generated ok, block_reward=" << print_money(block_reward) << "("  << print_money(block_reward - fee) << "+" << print_money(fee)
    //  << "), current_block_size=" << current_block_size << ", already_generated_coins=" << already_generated_coins << ", tx_id=" << get_transaction_hash(tx), LOG_LEVEL_2);
    return true;
  }
  //---------------------------------------------------------------
  crypto::public_key get_destination_view_key_pub(const std::vector<tx_destination_entry> &destinations, const boost::optional<cryptonote::account_public_address>& change_addr)
  {
    account_public_address addr = {null_pkey, null_pkey};
    size_t count = 0;
    for (const auto &i : destinations)
    {
      if (i.amount == 0)
        continue;
      if (change_addr && i.addr == *change_addr)
        continue;
      if (i.addr == addr)
        continue;
      if (count > 0)
        return null_pkey;
      addr = i.addr;
      ++count;
    }
    if (count == 0 && change_addr)
      return change_addr->m_view_public_key;
    return addr.m_view_public_key;
  }
  //---------------------------------------------------------------
  bool construct_tx_with_tx_key(const account_keys& sender_account_keys, const std::unordered_map<crypto::public_key, subaddress_index>& subaddresses, std::vector<tx_source_entry>& sources, std::vector<tx_destination_entry>& destinations, const boost::optional<cryptonote::account_public_address>& change_addr, const std::vector<uint8_t> &extra, transaction& tx, uint64_t unlock_time, const crypto::secret_key &tx_key, const std::vector<crypto::secret_key> &additional_tx_keys, bool rct, const rct::RCTConfig &rct_config, bool shuffle_outs, bool use_view_tags)
  {
    hw::device &hwdev = sender_account_keys.get_device();

    if (sources.empty())
    {
      LOG_ERROR("Empty sources");
      return false;
    }

    std::vector<rct::key> amount_keys;
    tx.set_null();
    amount_keys.clear();

    tx.version = rct ? 2 : 1;
    tx.unlock_time = unlock_time;

    tx.extra = extra;
    crypto::public_key txkey_pub;

    // if we have a stealth payment id, find it and encrypt it with the tx key now
    std::vector<tx_extra_field> tx_extra_fields;
    if (parse_tx_extra(tx.extra, tx_extra_fields))
    {
      bool add_dummy_payment_id = true;
      tx_extra_nonce extra_nonce;
      if (find_tx_extra_field_by_type(tx_extra_fields, extra_nonce))
      {
        crypto::hash payment_id = null_hash;
        crypto::hash8 payment_id8 = null_hash8;
        if (get_encrypted_payment_id_from_tx_extra_nonce(extra_nonce.nonce, payment_id8))
        {
          LOG_PRINT_L2("Encrypting payment id " << payment_id8);
          crypto::public_key view_key_pub = get_destination_view_key_pub(destinations, change_addr);
          if (view_key_pub == null_pkey)
          {
            LOG_ERROR("Destinations have to have exactly one output to support encrypted payment ids");
            return false;
          }

          if (!hwdev.encrypt_payment_id(payment_id8, view_key_pub, tx_key))
          {
            LOG_ERROR("Failed to encrypt payment id");
            return false;
          }

          std::string extra_nonce;
          set_encrypted_payment_id_to_tx_extra_nonce(extra_nonce, payment_id8);
          remove_field_from_tx_extra(tx.extra, typeid(tx_extra_nonce));
          if (!add_extra_nonce_to_tx_extra(tx.extra, extra_nonce))
          {
            LOG_ERROR("Failed to add encrypted payment id to tx extra");
            return false;
          }
          LOG_PRINT_L1("Encrypted payment ID: " << payment_id8);
          add_dummy_payment_id = false;
        }
        else if (get_payment_id_from_tx_extra_nonce(extra_nonce.nonce, payment_id))
        {
          add_dummy_payment_id = false;
        }
      }

      // we don't add one if we've got more than the usual 1 destination plus change
      if (destinations.size() > 2)
        add_dummy_payment_id = false;

      if (add_dummy_payment_id)
      {
        // if we have neither long nor short payment id, add a dummy short one,
        // this should end up being the vast majority of txes as time goes on
        std::string extra_nonce;
        crypto::hash8 payment_id8 = null_hash8;
        crypto::public_key view_key_pub = get_destination_view_key_pub(destinations, change_addr);
        if (view_key_pub == null_pkey)
        {
          LOG_ERROR("Failed to get key to encrypt dummy payment id with");
        }
        else
        {
          hwdev.encrypt_payment_id(payment_id8, view_key_pub, tx_key);
          set_encrypted_payment_id_to_tx_extra_nonce(extra_nonce, payment_id8);
          if (!add_extra_nonce_to_tx_extra(tx.extra, extra_nonce))
          {
            LOG_ERROR("Failed to add dummy encrypted payment id to tx extra");
            // continue anyway
          }
        }
      }
    }
    else
    {
      MWARNING("Failed to parse tx extra");
      tx_extra_fields.clear();
    }

    struct input_generation_context_data
    {
      keypair in_ephemeral;
    };
    std::vector<input_generation_context_data> in_contexts;

    uint64_t summary_inputs_money = 0;
    //fill inputs
    int idx = -1;
    for(const tx_source_entry& src_entr:  sources)
    {
      ++idx;
      if(src_entr.real_output >= src_entr.outputs.size())
      {
        LOG_ERROR("real_output index (" << src_entr.real_output << ")bigger than output_keys.size()=" << src_entr.outputs.size());
        return false;
      }
      summary_inputs_money += src_entr.amount;

      //key_derivation recv_derivation;
      in_contexts.push_back(input_generation_context_data());
      keypair& in_ephemeral = in_contexts.back().in_ephemeral;
      crypto::key_image img;
      const auto& out_key = reinterpret_cast<const crypto::public_key&>(src_entr.outputs[src_entr.real_output].second.dest);
      if(!generate_key_image_helper(sender_account_keys, subaddresses, out_key, src_entr.real_out_tx_key, src_entr.real_out_additional_tx_keys, src_entr.real_output_in_tx_index, in_ephemeral,img, hwdev))
      {
        LOG_ERROR("Key image generation failed!");
        return false;
      }

      //check that derivated key is equal with real output key
      if(!(in_ephemeral.pub == src_entr.outputs[src_entr.real_output].second.dest) )
      {
        LOG_ERROR("derived public key mismatch with output public key at index " << idx << ", real out " << src_entr.real_output << "! "<< ENDL << "derived_key:"
          << string_tools::pod_to_hex(in_ephemeral.pub) << ENDL << "real output_public_key:"
          << string_tools::pod_to_hex(src_entr.outputs[src_entr.real_output].second.dest) );
        LOG_ERROR("amount " << src_entr.amount << ", rct " << src_entr.rct);
        LOG_ERROR("tx pubkey " << src_entr.real_out_tx_key << ", real_output_in_tx_index " << src_entr.real_output_in_tx_index);
        return false;
      }

      //put key image into tx input
      txin_to_key input_to_key;
      input_to_key.amount = src_entr.amount;
      input_to_key.k_image = img;

      //fill outputs array and use relative offsets
      for(const tx_source_entry::output_entry& out_entry: src_entr.outputs)
        input_to_key.key_offsets.push_back(out_entry.first);

      input_to_key.key_offsets = absolute_output_offsets_to_relative(input_to_key.key_offsets);
      tx.vin.push_back(input_to_key);
    }

    if (shuffle_outs)
    {
      std::shuffle(destinations.begin(), destinations.end(), crypto::random_device{});
    }

    // sort ins by their key image
    std::vector<size_t> ins_order(sources.size());
    for (size_t n = 0; n < sources.size(); ++n)
      ins_order[n] = n;
    std::sort(ins_order.begin(), ins_order.end(), [&](const size_t i0, const size_t i1) {
      const txin_to_key &tk0 = boost::get<txin_to_key>(tx.vin[i0]);
      const txin_to_key &tk1 = boost::get<txin_to_key>(tx.vin[i1]);
      return memcmp(&tk0.k_image, &tk1.k_image, sizeof(tk0.k_image)) > 0;
    });
    tools::apply_permutation(ins_order, [&] (size_t i0, size_t i1) {
      std::swap(tx.vin[i0], tx.vin[i1]);
      std::swap(in_contexts[i0], in_contexts[i1]);
      std::swap(sources[i0], sources[i1]);
    });

    // figure out if we need to make additional tx pubkeys
    size_t num_stdaddresses = 0;
    size_t num_subaddresses = 0;
    account_public_address single_dest_subaddress;
    classify_addresses(destinations, change_addr, num_stdaddresses, num_subaddresses, single_dest_subaddress);

    // if this is a single-destination transfer to a subaddress, we set the tx pubkey to R=s*D
    if (num_stdaddresses == 0 && num_subaddresses == 1)
    {
      txkey_pub = rct::rct2pk(hwdev.scalarmultKey(rct::pk2rct(single_dest_subaddress.m_spend_public_key), rct::sk2rct(tx_key)));
    }
    else
    {
      txkey_pub = rct::rct2pk(hwdev.scalarmultBase(rct::sk2rct(tx_key)));
    }
    remove_field_from_tx_extra(tx.extra, typeid(tx_extra_pub_key));
    add_tx_pub_key_to_extra(tx, txkey_pub);

    std::vector<crypto::public_key> additional_tx_public_keys;

    // we don't need to include additional tx keys if:
    //   - all the destinations are standard addresses
    //   - there's only one destination which is a subaddress
    bool need_additional_txkeys = num_subaddresses > 0 && (num_stdaddresses > 0 || num_subaddresses > 1);
    if (need_additional_txkeys)
      CHECK_AND_ASSERT_MES(destinations.size() == additional_tx_keys.size(), false, "Wrong amount of additional tx keys");

    uint64_t summary_outs_money = 0;
    //fill outputs
    size_t output_index = 0;
    for(const tx_destination_entry& dst_entr: destinations)
    {
      CHECK_AND_ASSERT_MES(dst_entr.amount > 0 || tx.version > 1, false, "Destination with wrong amount: " << dst_entr.amount);
      crypto::public_key out_eph_public_key;
      crypto::view_tag view_tag;

      hwdev.generate_output_ephemeral_keys(tx.version,sender_account_keys, txkey_pub, tx_key,
                                           dst_entr, change_addr, output_index,
                                           need_additional_txkeys, additional_tx_keys,
                                           additional_tx_public_keys, amount_keys, out_eph_public_key,
                                           use_view_tags, view_tag);

      tx_out out;
      cryptonote::set_tx_out(dst_entr.amount, out_eph_public_key, use_view_tags, view_tag, out);
      tx.vout.push_back(out);
      output_index++;
      summary_outs_money += dst_entr.amount;
    }
    CHECK_AND_ASSERT_MES(additional_tx_public_keys.size() == additional_tx_keys.size(), false, "Internal error creating additional public keys");

    remove_field_from_tx_extra(tx.extra, typeid(tx_extra_additional_pub_keys));

    LOG_PRINT_L2("tx pubkey: " << txkey_pub);
    if (need_additional_txkeys)
    {
      LOG_PRINT_L2("additional tx pubkeys: ");
      for (size_t i = 0; i < additional_tx_public_keys.size(); ++i)
        LOG_PRINT_L2(additional_tx_public_keys[i]);
      add_additional_tx_pub_keys_to_extra(tx.extra, additional_tx_public_keys);
    }

    if (!sort_tx_extra(tx.extra, tx.extra))
      return false;

    CHECK_AND_ASSERT_MES(tx.extra.size() <= MAX_TX_EXTRA_SIZE, false, "TX extra size (" << tx.extra.size() << ") is greater than max allowed (" << MAX_TX_EXTRA_SIZE << ")");

    //check money
    if(summary_outs_money > summary_inputs_money )
    {
      LOG_ERROR("Transaction inputs money ("<< summary_inputs_money << ") less than outputs money (" << summary_outs_money << ")");
      return false;
    }

    // check for watch only wallet
    bool zero_secret_key = true;
    for (size_t i = 0; i < sizeof(sender_account_keys.m_spend_secret_key); ++i)
      zero_secret_key &= (sender_account_keys.m_spend_secret_key.data[i] == 0);
    if (zero_secret_key)
    {
      MDEBUG("Null secret key, skipping signatures");
    }

    if (tx.version == 1)
    {
      //generate ring signatures
      crypto::hash tx_prefix_hash;
      get_transaction_prefix_hash(tx, tx_prefix_hash);

      std::stringstream ss_ring_s;
      size_t i = 0;
      for(const tx_source_entry& src_entr:  sources)
      {
        ss_ring_s << "pub_keys:" << ENDL;
        std::vector<const crypto::public_key*> keys_ptrs;
        std::vector<crypto::public_key> keys(src_entr.outputs.size());
        size_t ii = 0;
        for(const tx_source_entry::output_entry& o: src_entr.outputs)
        {
          keys[ii] = rct2pk(o.second.dest);
          keys_ptrs.push_back(&keys[ii]);
          ss_ring_s << o.second.dest << ENDL;
          ++ii;
        }

        tx.signatures.push_back(std::vector<crypto::signature>());
        std::vector<crypto::signature>& sigs = tx.signatures.back();
        sigs.resize(src_entr.outputs.size());
        if (!zero_secret_key)
          crypto::generate_ring_signature(tx_prefix_hash, boost::get<txin_to_key>(tx.vin[i]).k_image, keys_ptrs, in_contexts[i].in_ephemeral.sec, src_entr.real_output, sigs.data());
        ss_ring_s << "signatures:" << ENDL;
        std::for_each(sigs.begin(), sigs.end(), [&](const crypto::signature& s){ss_ring_s << s << ENDL;});
        ss_ring_s << "prefix_hash:" << tx_prefix_hash << ENDL << "in_ephemeral_key: " << in_contexts[i].in_ephemeral.sec << ENDL << "real_output: " << src_entr.real_output << ENDL;
        i++;
      }

      MCINFO("construct_tx", "transaction_created: " << get_transaction_hash(tx) << ENDL << obj_to_json_str(tx) << ENDL << ss_ring_s.str());
    }
    else
    {
      size_t n_total_outs = sources[0].outputs.size(); // only for non-simple rct

      // the non-simple version is slightly smaller, but assumes all real inputs
      // are on the same index, so can only be used if there just one ring.
      bool use_simple_rct = sources.size() > 1 || rct_config.range_proof_type != rct::RangeProofBorromean;

      if (!use_simple_rct)
      {
        // non simple ringct requires all real inputs to be at the same index for all inputs
        for(const tx_source_entry& src_entr:  sources)
        {
          if(src_entr.real_output != sources.begin()->real_output)
          {
            LOG_ERROR("All inputs must have the same index for non-simple ringct");
            return false;
          }
        }

        // enforce same mixin for all outputs
        for (size_t i = 1; i < sources.size(); ++i) {
          if (n_total_outs != sources[i].outputs.size()) {
            LOG_ERROR("Non-simple ringct transaction has varying ring size");
            return false;
          }
        }
      }

      uint64_t amount_in = 0, amount_out = 0;
      rct::ctkeyV inSk;
      inSk.reserve(sources.size());
      // mixRing indexing is done the other way round for simple
      rct::ctkeyM mixRing(use_simple_rct ? sources.size() : n_total_outs);
      rct::keyV destinations;
      std::vector<uint64_t> inamounts, outamounts;
      std::vector<unsigned int> index;
      for (size_t i = 0; i < sources.size(); ++i)
      {
        rct::ctkey ctkey;
        amount_in += sources[i].amount;
        inamounts.push_back(sources[i].amount);
        index.push_back(sources[i].real_output);
        // inSk: (secret key, mask)
        ctkey.dest = rct::sk2rct(in_contexts[i].in_ephemeral.sec);
        ctkey.mask = sources[i].mask;
        inSk.push_back(ctkey);
        memwipe(&ctkey, sizeof(rct::ctkey));
        // inPk: (public key, commitment)
        // will be done when filling in mixRing
      }
      for (size_t i = 0; i < tx.vout.size(); ++i)
      {
        crypto::public_key output_public_key;
        get_output_public_key(tx.vout[i], output_public_key);
        destinations.push_back(rct::pk2rct(output_public_key));
        outamounts.push_back(tx.vout[i].amount);
        amount_out += tx.vout[i].amount;
      }

      if (use_simple_rct)
      {
        // mixRing indexing is done the other way round for simple
        for (size_t i = 0; i < sources.size(); ++i)
        {
          mixRing[i].resize(sources[i].outputs.size());
          for (size_t n = 0; n < sources[i].outputs.size(); ++n)
          {
            mixRing[i][n] = sources[i].outputs[n].second;
          }
        }
      }
      else
      {
        for (size_t i = 0; i < n_total_outs; ++i) // same index assumption
        {
          mixRing[i].resize(sources.size());
          for (size_t n = 0; n < sources.size(); ++n)
          {
            mixRing[i][n] = sources[n].outputs[i].second;
          }
        }
      }

      // fee
      if (!use_simple_rct && amount_in > amount_out)
        outamounts.push_back(amount_in - amount_out);

      // zero out all amounts to mask rct outputs, real amounts are now encrypted
      for (size_t i = 0; i < tx.vin.size(); ++i)
      {
        if (sources[i].rct)
          boost::get<txin_to_key>(tx.vin[i]).amount = 0;
      }
      for (size_t i = 0; i < tx.vout.size(); ++i)
        tx.vout[i].amount = 0;

      crypto::hash tx_prefix_hash;
      get_transaction_prefix_hash(tx, tx_prefix_hash, hwdev);
      rct::ctkeyV outSk;
      if (use_simple_rct)
        tx.rct_signatures = rct::genRctSimple(rct::hash2rct(tx_prefix_hash), inSk, destinations, inamounts, outamounts, amount_in - amount_out, mixRing, amount_keys, index, outSk, rct_config, hwdev);
      else
        tx.rct_signatures = rct::genRct(rct::hash2rct(tx_prefix_hash), inSk, destinations, outamounts, mixRing, amount_keys, sources[0].real_output, outSk, rct_config, hwdev); // same index assumption
      memwipe(inSk.data(), inSk.size() * sizeof(rct::ctkey));

      CHECK_AND_ASSERT_MES(tx.vout.size() == outSk.size(), false, "outSk size does not match vout");

      MCINFO("construct_tx", "transaction_created: " << get_transaction_hash(tx) << ENDL << obj_to_json_str(tx) << ENDL);
    }

    tx.invalidate_hashes();

    return true;
  }
  //---------------------------------------------------------------
  bool construct_tx_and_get_tx_key(const account_keys& sender_account_keys, const std::unordered_map<crypto::public_key, subaddress_index>& subaddresses, std::vector<tx_source_entry>& sources, std::vector<tx_destination_entry>& destinations, const boost::optional<cryptonote::account_public_address>& change_addr, const std::vector<uint8_t> &extra, transaction& tx, uint64_t unlock_time, crypto::secret_key &tx_key, std::vector<crypto::secret_key> &additional_tx_keys, bool rct, const rct::RCTConfig &rct_config, bool use_view_tags)
  {
    hw::device &hwdev = sender_account_keys.get_device();
    hwdev.open_tx(tx_key);
    try {
      // figure out if we need to make additional tx pubkeys
      size_t num_stdaddresses = 0;
      size_t num_subaddresses = 0;
      account_public_address single_dest_subaddress;
      classify_addresses(destinations, change_addr, num_stdaddresses, num_subaddresses, single_dest_subaddress);
      bool need_additional_txkeys = num_subaddresses > 0 && (num_stdaddresses > 0 || num_subaddresses > 1);
      if (need_additional_txkeys)
      {
        additional_tx_keys.clear();
        for (size_t i = 0; i < destinations.size(); ++i)
        {
          additional_tx_keys.push_back(keypair::generate(sender_account_keys.get_device()).sec);
        }
      }

      bool shuffle_outs = true;
      bool r = construct_tx_with_tx_key(sender_account_keys, subaddresses, sources, destinations, change_addr, extra, tx, unlock_time, tx_key, additional_tx_keys, rct, rct_config, shuffle_outs, use_view_tags);
      hwdev.close_tx();
      return r;
    } catch(...) {
      hwdev.close_tx();
      throw;
    }
  }
  //---------------------------------------------------------------
  bool construct_tx(const account_keys& sender_account_keys, std::vector<tx_source_entry>& sources, const std::vector<tx_destination_entry>& destinations, const boost::optional<cryptonote::account_public_address>& change_addr, const std::vector<uint8_t> &extra, transaction& tx, uint64_t unlock_time)
  {
     std::unordered_map<crypto::public_key, cryptonote::subaddress_index> subaddresses;
     subaddresses[sender_account_keys.m_account_address.m_spend_public_key] = {0,0};
     crypto::secret_key tx_key;
     std::vector<crypto::secret_key> additional_tx_keys;
     std::vector<tx_destination_entry> destinations_copy = destinations;
     return construct_tx_and_get_tx_key(sender_account_keys, subaddresses, sources, destinations_copy, change_addr, extra, tx, unlock_time, tx_key, additional_tx_keys, false, { rct::RangeProofBorromean, 0});
  }
  //---------------------------------------------------------------
  bool generate_genesis_block(
      block& bl
    , std::string const & genesis_tx
    , uint32_t nonce
    )
  {
    //genesis block
    bl = {};

    blobdata tx_bl;
    bool r = string_tools::parse_hexstr_to_binbuff(genesis_tx, tx_bl);
    CHECK_AND_ASSERT_MES(r, false, "failed to parse coinbase tx from hard coded blob");
    r = parse_and_validate_tx_from_blob(tx_bl, bl.miner_tx);
    CHECK_AND_ASSERT_MES(r, false, "failed to parse coinbase tx from hard coded blob");
    bl.major_version = CURRENT_BLOCK_MAJOR_VERSION;
    bl.minor_version = CURRENT_BLOCK_MINOR_VERSION;
    bl.timestamp = 0;
    bl.nonce = nonce;
    miner::find_nonce_for_given_block([](const cryptonote::block &b, uint64_t height, const crypto::hash *seed_hash, unsigned int threads, crypto::hash &hash){
      return cryptonote::get_block_longhash(NULL, b, hash, height, seed_hash, threads);
    }, bl, 1, 0, NULL);
    bl.invalidate_hashes();
    return true;
  }
  //---------------------------------------------------------------
  void get_altblock_longhash(const block& b, crypto::hash& res, const crypto::hash& seed_hash)
  {
    blobdata bd = get_block_hashing_blob(b);
    rx_slow_hash(seed_hash.data, bd.data(), bd.size(), res.data);
  }

  bool get_block_longhash(const Blockchain *pbc, const blobdata& bd, crypto::hash& res, const uint64_t height, const int major_version, const crypto::hash *seed_hash, const int miners)
  {
    if (major_version >= RX_BLOCK_VERSION)
    {
      crypto::hash hash;
      if (pbc != NULL)
      {
        const uint64_t seed_height = rx_seedheight(height);
        hash = seed_hash ? *seed_hash : pbc->get_pending_block_id_by_height(seed_height);
      } else
      {
        memset(&hash, 0, sizeof(hash));  // only happens when generating genesis block
      }
      rx_slow_hash(hash.data, bd.data(), bd.size(), res.data);
    } else {
      const int pow_variant = major_version >= 7 ? major_version - 6 : 0;
      crypto::cn_slow_hash(bd.data(), bd.size(), res, pow_variant, height);
    }
    return true;
  }

  bool get_block_longhash(const Blockchain *pbc, const block& b, crypto::hash& res, const uint64_t height, const crypto::hash *seed_hash, const int miners)
  {
    blobdata bd = get_block_hashing_blob(b);
	return get_block_longhash(pbc, bd, res, height, b.major_version, seed_hash, miners);
  }

  crypto::hash get_block_longhash(const Blockchain *pbc, const block& b, const uint64_t height, const crypto::hash *seed_hash, const int miners)
  {
    crypto::hash p = crypto::null_hash;
    get_block_longhash(pbc, b, p, height, seed_hash, miners);
    return p;
  }
}
