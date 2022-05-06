#include <iostream>
#include <string>

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

#include "misc_log_ex.h"
#include "common/util.h"
#include "common/dns_utils.h"
#include "common/download.h"
#include "diardi.h"

#undef SCALA_DEFAULT_LOG_CATEGORY
#define SCALA_DEFAULT_LOG_CATEGORY "diardi"

namespace cryptonote {

    Diardi::Diardi() {}

    std::string Diardi::get_checkpoints_location(network_type nettype) {
        std::string path;
        std::string default_directory = tools::get_default_data_dir();

        if(nettype == MAINNET) {
            path = default_directory + "/" + "checkpoints.json";
        } else if(nettype == TESTNET) {
            path = default_directory + "/testnet/" + "checkpoints.json";
        } else if(nettype == STAGENET) {
            path = default_directory + "/stagenet/" + "checkpoints.json";
        } else {
            throw std::runtime_error("Invalid network type");
        }

        return path;
    }

    bool Diardi::get_checkpoints(network_type nettype) {
        std::string checkpoint_location = get_checkpoints_location(nettype);
        if (boost::filesystem::exists(checkpoint_location)) {
            boost::filesystem::remove_all(checkpoint_location);
        }

        std::string ipfs_path = fetch_dns_txt_ipfs_path(nettype);
        std::string url = "https://scala.infura-ipfs.io/ipfs/" + ipfs_path;

        if (!tools::download(checkpoint_location, url)) {
            LOG_PRINT_L1("Error loading checkpoints from IPFS");
            return false;
        }

        return true;
    }

    std::string Diardi::fetch_dns_txt_ipfs_path(network_type nettype) {
        bool available;
        bool valid;
        static const char* dns_name;
        
        if(nettype == MAINNET) {
            dns_name = "_dnslink.dynamic-checkpoints-mainnet.scalaproject.io";
        } else if(nettype == TESTNET) {
            dns_name = "_dnslink.dynamic-checkpoints-testnet.scalaproject.io";
        } else if(nettype == STAGENET) {
            dns_name = "_dnslink.dynamic-checkpoints-stagenet.scalaproject.io";
        } else {
            throw std::runtime_error("Invalid network type");
        }

        std::vector<std::string> records = tools::DNSResolver::instance().get_txt_record(dns_name, available, valid);
        std::string ipfs_path = records[0];
        boost::replace_all(ipfs_path, "dnslink=\"/ipfs/", "");
        boost::replace_all(ipfs_path, "\"", "");

        return ipfs_path;
    }
}