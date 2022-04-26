#pragma once

namespace cryptonote {
    class Diardi {
        public:
            Diardi();

            std::string get_checkpoints_location(network_type nettype);
            std::string fetch_dns_txt_ipfs_path(network_type nettype);
            bool get_checkpoints(network_type nettype);
    };
}