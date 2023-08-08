// Copyright (c) 2014-2023, The Monero Project
// Copyright (c) 2021-2023, Haku Labs MTÜ
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
// this list of
//    conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
// this list
//    of conditions and the following disclaimer in the documentation and/or
//    other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors
// may be
//    used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include "hardforks.h"

#undef scala_DEFAULT_LOG_CATEGORY
#define scala_DEFAULT_LOG_CATEGORY "blockchain.hardforks"

const hardfork_t mainnet_hard_forks[] = {
    {1, 1, 0, 1341378000},
    {12, 2, 0, 1582125473},

    // Approximately on 14th of September 2023 (V8)
    {16, 820102, 0, 1692005445},
};

const size_t num_mainnet_hard_forks =
    sizeof(mainnet_hard_forks) / sizeof(mainnet_hard_forks[0]);
const uint64_t mainnet_hard_fork_version_1_till = 1;

const hardfork_t testnet_hard_forks[] = {
    {1, 1, 0, 1341378000},
    {12, 2, 0, 1582125473},

    // Approximately on 14th of August 2023 (V8)
    {16, 4700, 0, 1692005445},
};
const size_t num_testnet_hard_forks =
    sizeof(testnet_hard_forks) / sizeof(testnet_hard_forks[0]);
const uint64_t testnet_hard_fork_version_1_till = 624633;

const hardfork_t stagenet_hard_forks[] = {
    {1, 1, 0, 1341378000},
    {12, 2, 0, 1582125473},
    {16, 150, 0, 1691411928},
};
const size_t num_stagenet_hard_forks =
    sizeof(stagenet_hard_forks) / sizeof(stagenet_hard_forks[0]);
