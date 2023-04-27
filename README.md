# Scala

Copyright (c) 2014-2023, The Monero Project
Copyright (c) 2021-2023, Haku Labs MTÜ
Portions Copyright (c) 2012-2013 The Cryptonote developers.

[<img src="https://scalaproject.io/img/card.jpg">](https://scalaproject.io)


Scala is a privacy-focused cryptocurrency project linking distributed technologies to build a globally scalable and mobile-friendly ecosystem. We provide an opaque blockchain, untraceable payments, unlinkable transactions, and blockchain-analysis resistance.

Our vision is to distribute wealth for everyone and every device. We want to be the people’s coin. To achieve this goal, we focus on implementing solutions that are mobile-friendly and energy-efficient. There are about 4 billion mobile devices in the world, and we want to make sure that our ecosystem takes that into account. We also take a lot of time to improve the user experience so that our applications can be used easily by anyone.

Obviously, our goal is also to bring useful utilities and to solve real-world problems, in a way that is economically viable for the project and to sustain our growth. We take advantage of next-gen technologies such as IPFS and custom software to provide the utility of data storage and we use the proven CryptoNote protocol for providing the financial aspects.

## Table of Contents

- [Scala](#scala)
  - [Table of Contents](#table-of-contents)
  - [Development resources](#development-resources)
  - [Vulnerability response](#vulnerability-response)
  - [Research](#research)
  - [Announcements](#announcements)
  - [Translations](#translations)
  - [Coverage](#coverage)
  - [Introduction](#introduction)
  - [About this project](#about-this-project)
  - [Supporting the project](#supporting-the-project)
  - [License](#license)
  - [Contributing](#contributing)
  - [Scheduled software/network upgrades](#scheduled-softwarenetwork-upgrades)
  - [Release staging schedule and protocol](#release-staging-schedule-and-protocol)
  - [Compiling scala from source](#compiling-scala-from-source)
    - [Dependencies](#dependencies)
    - [Cloning the repository](#cloning-the-repository)
    - [Build instructions](#build-instructions)
      - [On Linux and macOS](#on-linux-and-macos)
      - [On the Raspberry Pi](#on-the-raspberry-pi)
      - [*Note for Raspbian Jessie users:*](#note-for-raspbian-jessie-users)
      - [On Windows:](#on-windows)
    - [On FreeBSD:](#on-freebsd)
    - [On OpenBSD:](#on-openbsd)
    - [On NetBSD:](#on-netbsd)
    - [On Solaris:](#on-solaris)
    - [Building portable statically linked binaries](#building-portable-statically-linked-binaries)
    - [Cross Compiling](#cross-compiling)
    - [Gitian builds](#gitian-builds)
  - [Installing scala from a package](#installing-scala-from-a-package)
  - [Running scalad](#running-scalad)
  - [Internationalization](#internationalization)
  - [Using Tor](#using-tor)
    - [Using Tor on Tails](#using-tor-on-tails)
  - [Pruning](#pruning)
  - [Debugging](#debugging)
    - [Obtaining stack traces and core dumps on Unix systems](#obtaining-stack-traces-and-core-dumps-on-unix-systems)
      - [To run scala within gdb:](#to-run-scala-within-gdb)
    - [Analysing memory corruption](#analysing-memory-corruption)
      - [ASAN](#asan)
      - [valgrind](#valgrind)
    - [LMDB](#lmdb)
- [Known Issues](#known-issues)
  - [Protocols](#protocols)
    - [Socket-based](#socket-based)
    - [Blockchain-based](#blockchain-based)

## Development resources

- Web: [scalaproject.io](https://scalaproject.io)
- Mail: [dev@getscala.org](mailto:hello@scalaproject.io)
- GitHub: [https://github.com/scala-network/scala](https://github.com/scala-network/scala)

## Vulnerability response

- Our [Vulnerability Response Process](https://github.com/scala-project/meta/blob/master/VULNERABILITY_RESPONSE_PROCESS.md) encourages responsible disclosure
- We are also available via [HackerOne](https://hackerone.com/scala)

## Research

The [scala Research Lab](https://src.getscala.org/resources/research-lab/) is an open forum where the community coordinates research into scala cryptography, protocols, fungibility, analysis, and more. We welcome collaboration and contributions from outside researchers! Because not all Lab work and publications are distributed as traditional preprints or articles, they may be easy to miss if you are conducting literature reviews for your own scala research. You are encouraged to get in touch with the scala research community if you have questions, wish to collaborate, or would like guidance to help avoid unnecessarily duplicating earlier or known work.

The scala research community is available on IRC in [#scala-research-lab on Libera](https://web.libera.chat/#scala-research-lab), which is also accessible via Matrix.

## Announcements

- You can subscribe to an [announcement listserv](https://lists.getscala.org) to get critical announcements from the scala core team. The announcement list can be very helpful for knowing when software updates are needed.

## Translations
The CLI wallet is available in different languages. If you want to help translate it, see our self-hosted localization platform, Weblate, on [translate.getscala.org]( https://translate.getscala.org/projects/scala/cli-wallet/). Every translation *must* be uploaded on the platform, pull requests directly editing the code in this repository will be closed. If you need help with Weblate, you can find a guide with screenshots [here](https://github.com/scala-ecosystem/scala-translations/blob/master/weblate.md).
&nbsp;

If you need help/support/info about translations, contact the localization workgroup. You can find the complete list of contacts on the repository of the workgroup: [scala-translations](https://github.com/scala-ecosystem/scala-translations#contacts).

## Coverage

| Type      | Status |
|-----------|--------|
| Coverity  | [![Coverity Status](https://scan.coverity.com/projects/9657/badge.svg)](https://scan.coverity.com/projects/9657/)
| OSS Fuzz  | [![Fuzzing Status](https://oss-fuzz-build-logs.storage.googleapis.com/badges/scala.svg)](https://bugs.chromium.org/p/oss-fuzz/issues/list?sort=-opened&can=1&q=proj:scala)
| Coveralls | [![Coveralls Status](https://coveralls.io/repos/github/scala-project/scala/badge.svg?branch=master)](https://coveralls.io/github/scala-project/scala?branch=master)
| License   | [![License](https://img.shields.io/badge/license-BSD3-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

## Introduction

scala is a private, secure, untraceable, decentralised digital currency. You are your bank, you control your funds, and nobody can trace your transfers unless you allow them to do so.

**Privacy:** scala uses a cryptographically sound system to allow you to send and receive funds without your transactions being easily revealed on the blockchain (the ledger of transactions that everyone has). This ensures that your purchases, receipts, and all transfers remain private by default.

**Security:** Using the power of a distributed peer-to-peer consensus network, every transaction on the network is cryptographically secured. Individual wallets have a 25-word mnemonic seed that is only displayed once and can be written down to backup the wallet. Wallet files should be encrypted with a strong passphrase to ensure they are useless if ever stolen.

**Untraceability:** By taking advantage of ring signatures, a special property of a certain type of cryptography, scala is able to ensure that transactions are not only untraceable but have an optional measure of ambiguity that ensures that transactions cannot easily be tied back to an individual user or computer.

**Decentralization:** The utility of scala depends on its decentralised peer-to-peer consensus network - anyone should be able to run the scala software, validate the integrity of the blockchain, and participate in all aspects of the scala network using consumer-grade commodity hardware. Decentralization of the scala network is maintained by software development that minimizes the costs of running the scala software and inhibits the proliferation of specialized, non-commodity hardware.

## About this project

This is the core implementation of scala. It is open source and completely free to use without restrictions, except for those specified in the license agreement below. There are no restrictions on anyone creating an alternative implementation of scala that uses the protocol and network in a compatible manner.

As with many development projects, the repository on GitHub is considered to be the "staging" area for the latest changes. Before changes are merged into that branch on the main repository, they are tested by individual developers in their own branches, submitted as a pull request, and then subsequently tested by contributors who focus on testing and code reviews. That having been said, the repository should be carefully considered before using it in a production environment, unless there is a patch in the repository for a particular show-stopping issue you are experiencing. It is generally a better idea to use a tagged release for stability.

**Anyone is welcome to contribute to scala's codebase!** If you have a fix or code change, feel free to submit it as a pull request directly to the "master" branch. In cases where the change is relatively small or does not affect other parts of the codebase, it may be merged in immediately by any one of the collaborators. On the other hand, if the change is particularly large or complex, it is expected that it will be discussed at length either well in advance of the pull request being submitted, or even directly on the pull request.

## Supporting the project

scala is a 100% community-sponsored endeavor. If you want to join our efforts, the easiest thing you can do is support the project financially. Both scala and Bitcoin donations can be made to **donate.getscala.org** if using a client that supports the [OpenAlias](https://openalias.org) standard. Alternatively, you can send XMR to the scala donation address via the `donate` command (type `help` in the command-line wallet for details).

The scala donation address is:  
`888tNkZrPN6JsEgekjMnABU4TBzc2Dt29EPAvkRxbANsAnjyPbb3iQ1YBRk1UXcdRsiKc9dhwMVgN5S9cQUiyoogDavup3H`  
Viewkey:  
`f359631075708155cc3d92a32b75a7d02a5dcf27756707b47a2b31b21c389501`  
Base address for restoring with address and viewkey:
`44AFFq5kSiGBoZ4NMDwYtN18obc8AemS33DBLWs3H7otXft3XjrpDtQGv7SqSsaBYBb98uNbr2VBBEt7f2wfn3RVGQBEP3A`  

The Bitcoin donation address is:  
`1KTexdemPdxSBcG55heUuTjDRYqbC5ZL8H`

Core development funding and/or some supporting services are also graciously provided by [sponsors](https://www.getscala.org/community/sponsorships/):

[<img width="150" src="https://www.getscala.org/img/sponsors/tarilabs.png"/>](https://tarilabs.com/)
[<img width="150" src="https://www.getscala.org/img/sponsors/globee.png"/>](https://globee.com/)
[<img width="150" src="https://www.getscala.org/img/sponsors/symas.png"/>](https://symas.com/)
[<img width="150" src="https://www.getscala.org/img/sponsors/forked_logo.png"/>](http://www.forked.net/)
[<img width="150" src="https://www.getscala.org/img/sponsors/macstadium.png"/>](https://www.macstadium.com/)

There are also several mining pools that kindly donate a portion of their fees, [a list of them can be found on our Bitcointalk post](https://bitcointalk.org/index.php?topic=583449.0).

## License

See [LICENSE](LICENSE).

## Contributing

If you want to help out, see [CONTRIBUTING](docs/CONTRIBUTING.md) for a set of guidelines.

## Scheduled software/network upgrades

scala uses a scheduled software/network upgrade (hard fork) mechanism to implement new features into the scala software and network. This means that users of scala (end users and service providers) should run current versions and upgrade their software when new releases are available. Software upgrades occur when new features are developed and implemented in the codebase. Network upgrades occur in tandem with software upgrades that modify the consensus rules of the scala network. The required software for network upgrades will be available prior to the scheduled network upgrade date. Please check the repository prior to this date for the proper scala software version. Below is the historical schedule and the projected schedule for the next upgrade.

Dates are provided in the format YYYY-MM-DD. The "Minimum" is the software version that follows the new consensus rules. The "Recommended" version may include bug fixes and other new features that do not affect the consensus rules.


| Software upgrade block height  | Date       | Fork version      | Minimum scala version | Recommended scala version | Details                                                                            |
| ------------------------------ | -----------| ----------------- | ---------------------- | -------------------------- | ---------------------------------------------------------------------------------- |
| 1009827                        | 2016-03-22 | v2                | v0.9.4                 | v0.9.4                     | Allow only >= ringsize 3, blocktime = 120 seconds, fee-free blocksize 60 kb       |
| 1141317                        | 2016-09-21 | v3                | v0.9.4                 | v0.10.0                    | Splits coinbase into denominations  |
| 1220516                        | 2017-01-05 | v4                | v0.10.1                | v0.10.2.1                  | Allow normal and RingCT transactions |
| 1288616                        | 2017-04-15 | v5                | v0.10.3.0              | v0.10.3.1                  | Adjusted minimum blocksize and fee algorithm      |
| 1400000                        | 2017-09-16 | v6                | v0.11.0.0              | v0.11.0.0                  | Allow only RingCT transactions, allow only >= ringsize 5      |
| 1546000                        | 2018-04-06 | v7                | v0.12.0.0              | v0.12.3.0                  | Cryptonight variant 1, ringsize >= 7, sorted inputs
| 1685555                        | 2018-10-18 | v8                | v0.13.0.0              | v0.13.0.4                  | max transaction size at half the penalty free block size, bulletproofs enabled, cryptonight variant 2, fixed ringsize [11](https://youtu.be/KOO5S4vxi0o)
| 1686275                        | 2018-10-19 | v9                | v0.13.0.0              | v0.13.0.4                  | bulletproofs required
| 1788000                        | 2019-03-09 | v10               | v0.14.0.0              | v0.14.1.2                  | New PoW based on Cryptonight-R, new block weight algorithm, slightly more efficient RingCT format
| 1788720                        | 2019-03-10 | v11               | v0.14.0.0              | v0.14.1.2                  | forbid old RingCT transaction format
| 1978433                        | 2019-11-30 | v12               | v0.15.0.0              | v0.16.0.0                  | New PoW based on RandomX, only allow >= 2 outputs, change to the block median used to calculate penalty, v1 coinbases are forbidden, rct sigs in coinbase forbidden, 10 block lock time for incoming outputs
| 2210000                        | 2020-10-17 | v13               | v0.17.0.0              | v0.17.3.2                  | New CLSAG transaction format
| 2210720                        | 2020-10-18 | v14               | v0.17.1.1              | v0.17.3.2                  | forbid old MLSAG transaction format
| 2688888                        | 2022-08-13 | v15               | v0.18.0.0              | v0.18.1.2                  | ringsize = 16, bulletproofs+, view tags, adjusted dynamic block weight algorithm
| 2689608                        | 2022-08-14 | v16               | v0.18.0.0              | v0.18.1.2                  | forbid old v14 transaction format
| XXXXXXX                        | XXX-XX-XX | XXX                | vX.XX.X.X              | vX.XX.X.X                  | XXX |

X's indicate that these details have not been determined as of commit date.

\* indicates estimate as of commit date

## Release staging schedule and protocol

Approximately three months prior to a scheduled software upgrade, a branch from master will be created with the new release version tag. Pull requests that address bugs should then be made to both master and the new release branch. Pull requests that require extensive review and testing (generally, optimizations and new features) should *not* be made to the release branch.

## Compiling scala from source

### Dependencies

The following table summarizes the tools and libraries required to build. A
few of the libraries are also included in this repository (marked as
"Vendored"). By default, the build uses the library installed on the system
and ignores the vendored sources. However, if no library is found installed on
the system, then the vendored source will be built and used. The vendored
sources are also used for statically-linked builds because distribution
packages often include only shared library binaries (`.so`) but not static
library archives (`.a`).

| Dep          | Min. version  | Vendored | Debian/Ubuntu pkg    | Arch pkg     | Void pkg           | Fedora pkg          | Optional | Purpose         |
| ------------ | ------------- | -------- | -------------------- | ------------ | ------------------ | ------------------- | -------- | --------------- |
| GCC          | 5             | NO       | `build-essential`    | `base-devel` | `base-devel`       | `gcc`               | NO       |                 |
| CMake        | 3.5           | NO       | `cmake`              | `cmake`      | `cmake`            | `cmake`             | NO       |                 |
| pkg-config   | any           | NO       | `pkg-config`         | `base-devel` | `base-devel`       | `pkgconf`           | NO       |                 |
| Boost        | 1.58          | NO       | `libboost-all-dev`   | `boost`      | `boost-devel`      | `boost-devel`       | NO       | C++ libraries   |
| OpenSSL      | basically any | NO       | `libssl-dev`         | `openssl`    | `openssl-devel`    | `openssl-devel`     | NO       | sha256 sum      |
| libzmq       | 4.2.0         | NO       | `libzmq3-dev`        | `zeromq`     | `zeromq-devel`     | `zeromq-devel`      | NO       | ZeroMQ library  |
| OpenPGM      | ?             | NO       | `libpgm-dev`         | `libpgm`     |                    | `openpgm-devel`     | NO       | For ZeroMQ      |
| libnorm[2]   | ?             | NO       | `libnorm-dev`        |              |                    |                     | YES      | For ZeroMQ      |
| libunbound   | 1.4.16        | NO       | `libunbound-dev`     | `unbound`    | `unbound-devel`    | `unbound-devel`     | NO       | DNS resolver    |
| libsodium    | ?             | NO       | `libsodium-dev`      | `libsodium`  | `libsodium-devel`  | `libsodium-devel`   | NO       | cryptography    |
| libunwind    | any           | NO       | `libunwind8-dev`     | `libunwind`  | `libunwind-devel`  | `libunwind-devel`   | YES      | Stack traces    |
| liblzma      | any           | NO       | `liblzma-dev`        | `xz`         | `liblzma-devel`    | `xz-devel`          | YES      | For libunwind   |
| libreadline  | 6.3.0         | NO       | `libreadline6-dev`   | `readline`   | `readline-devel`   | `readline-devel`    | YES      | Input editing   |
| expat        | 1.1           | NO       | `libexpat1-dev`      | `expat`      | `expat-devel`      | `expat-devel`       | YES      | XML parsing     |
| GTest        | 1.5           | YES      | `libgtest-dev`[1]    | `gtest`      | `gtest-devel`      | `gtest-devel`       | YES      | Test suite      |
| ccache       | any           | NO       | `ccache`             | `ccache`     | `ccache`           | `ccache`            | YES      | Compil. cache   |
| Doxygen      | any           | NO       | `doxygen`            | `doxygen`    | `doxygen`          | `doxygen`           | YES      | Documentation   |
| Graphviz     | any           | NO       | `graphviz`           | `graphviz`   | `graphviz`         | `graphviz`          | YES      | Documentation   |
| lrelease     | ?             | NO       | `qttools5-dev-tools` | `qt5-tools`  | `qt5-tools`        | `qt5-linguist`      | YES      | Translations    |
| libhidapi    | ?             | NO       | `libhidapi-dev`      | `hidapi`     | `hidapi-devel`     | `hidapi-devel`      | YES      | Hardware wallet |
| libusb       | ?             | NO       | `libusb-1.0-0-dev`   | `libusb`     | `libusb-devel`     | `libusbx-devel`     | YES      | Hardware wallet |
| libprotobuf  | ?             | NO       | `libprotobuf-dev`    | `protobuf`   | `protobuf-devel`   | `protobuf-devel`    | YES      | Hardware wallet |
| protoc       | ?             | NO       | `protobuf-compiler`  | `protobuf`   | `protobuf`         | `protobuf-compiler` | YES      | Hardware wallet |
| libudev      | ?             | NO       | `libudev-dev`        | `systemd`    | `eudev-libudev-devel` | `systemd-devel`  | YES      | Hardware wallet |

[1] On Debian/Ubuntu `libgtest-dev` only includes sources and headers. You must
build the library binary manually. This can be done with the following command `sudo apt-get install libgtest-dev && cd /usr/src/gtest && sudo cmake . && sudo make`
then:

* on Debian:
  `sudo mv libg* /usr/lib/`
* on Ubuntu:
  `sudo mv lib/libg* /usr/lib/`

[2] libnorm-dev is needed if your zmq library was built with libnorm, and not needed otherwise

Install all dependencies at once on Debian/Ubuntu:

```
sudo apt update && sudo apt install build-essential cmake pkg-config libssl-dev libzmq3-dev libunbound-dev libsodium-dev libunwind8-dev liblzma-dev libreadline6-dev libexpat1-dev libpgm-dev qttools5-dev-tools libhidapi-dev libusb-1.0-0-dev libprotobuf-dev protobuf-compiler libudev-dev libboost-chrono-dev libboost-date-time-dev libboost-filesystem-dev libboost-locale-dev libboost-program-options-dev libboost-regex-dev libboost-serialization-dev libboost-system-dev libboost-thread-dev python3 ccache doxygen graphviz
```

Install all dependencies at once on Arch:
```
sudo pacman -Syu --needed base-devel cmake boost openssl zeromq libpgm unbound libsodium libunwind xz readline expat gtest python3 ccache doxygen graphviz qt5-tools hidapi libusb protobuf systemd
```

Install all dependencies at once on Fedora:
```
sudo dnf install gcc gcc-c++ cmake pkgconf boost-devel openssl-devel zeromq-devel openpgm-devel unbound-devel libsodium-devel libunwind-devel xz-devel readline-devel expat-devel gtest-devel ccache doxygen graphviz qt5-linguist hidapi-devel libusbx-devel protobuf-devel protobuf-compiler systemd-devel
```

Install all dependencies at once on openSUSE:

```
sudo zypper ref && sudo zypper in cppzmq-devel libboost_chrono-devel libboost_date_time-devel libboost_filesystem-devel libboost_locale-devel libboost_program_options-devel libboost_regex-devel libboost_serialization-devel libboost_system-devel libboost_thread-devel libexpat-devel libminiupnpc-devel libsodium-devel libunwind-devel unbound-devel cmake doxygen ccache fdupes gcc-c++ libevent-devel libopenssl-devel pkgconf-pkg-config readline-devel xz-devel libqt5-qttools-devel patterns-devel-C-C++-devel_C_C++
```

Install all dependencies at once on macOS with the provided Brewfile:

```
brew update && brew bundle --file=contrib/brew/Brewfile
```

FreeBSD 12.1 one-liner required to build dependencies:

```
pkg install git gmake cmake pkgconf boost-libs libzmq4 libsodium unbound
```

### Cloning the repository

Clone recursively to pull-in needed submodule(s):

```
git clone --recursive https://github.com/scala-project/scala
```

If you already have a repo cloned, initialize and update:

```
cd scala && git submodule init && git submodule update
```

*Note*: If there are submodule differences between branches, you may need 
to use `git submodule sync && git submodule update` after changing branches
to build successfully.

### Build instructions

scala uses the CMake build system and a top-level [Makefile](Makefile) that
invokes cmake commands as needed.

#### On Linux and macOS

* Install the dependencies
* Change to the root of the source code directory, change to the most recent release branch, and build:

    ```bash
    cd scala
    git checkout release-v0.18
    make
    ```

    *Optional*: If your machine has several cores and enough memory, enable
    parallel build by running `make -j<number of threads>` instead of `make`. For
    this to be worthwhile, the machine should have one core and about 2GB of RAM
    available per thread.

    *Note*: The instructions above will compile the most stable release of the
    scala software. If you would like to use and test the most recent software,
    use `git checkout master`. The master branch may contain updates that are
    both unstable and incompatible with release software, though testing is always
    encouraged.

* The resulting executables can be found in `build/release/bin`

* Add `PATH="$PATH:$HOME/scala/build/release/bin"` to `.profile`

* Run scala with `scalad --detach`

* **Optional**: build and run the test suite to verify the binaries:

    ```bash
    make release-test
    ```

    *NOTE*: `core_tests` test may take a few hours to complete.

* **Optional**: to build binaries suitable for debugging:

    ```bash
    make debug
    ```

* **Optional**: to build statically-linked binaries:

    ```bash
    make release-static
    ```

Dependencies need to be built with -fPIC. Static libraries usually aren't, so you may have to build them yourself with -fPIC. Refer to their documentation for how to build them.

* **Optional**: build documentation in `doc/html` (omit `HAVE_DOT=YES` if `graphviz` is not installed):

    ```bash
    HAVE_DOT=YES doxygen Doxyfile
    ```

* **Optional**: use ccache not to rebuild translation units, that haven't really changed. scala's CMakeLists.txt file automatically handles it

    ```bash
    sudo apt install ccache
    ```

#### On the Raspberry Pi

Tested on a Raspberry Pi Zero with a clean install of minimal Raspbian Stretch (2017-09-07 or later) from https://www.raspberrypi.org/downloads/raspbian/. If you are using Raspian Jessie, [please see note in the following section](#note-for-raspbian-jessie-users).

* `apt-get update && apt-get upgrade` to install all of the latest software

* Install the dependencies for scala from the 'Debian' column in the table above.

* Increase the system swap size:

    ```bash
    sudo /etc/init.d/dphys-swapfile stop  
    sudo nano /etc/dphys-swapfile  
    CONF_SWAPSIZE=2048
    sudo /etc/init.d/dphys-swapfile start
    ```

* If using an external hard disk without an external power supply, ensure it gets enough power to avoid hardware issues when syncing, by adding the line "max_usb_current=1" to /boot/config.txt

* Clone scala and checkout the most recent release version:

    ```bash
    git clone https://github.com/scala-project/scala.git
    cd scala
    git checkout v0.18.1.2
    ```

* Build:

    ```bash
    USE_SINGLE_BUILDDIR=1 make release
    ```

* Wait 4-6 hours

* The resulting executables can be found in `build/release/bin`

* Add `export PATH="$PATH:$HOME/scala/build/release/bin"` to `$HOME/.profile`

* Run `source $HOME/.profile`

* Run scala with `scalad --detach`

* You may wish to reduce the size of the swap file after the build has finished, and delete the boost directory from your home directory

#### *Note for Raspbian Jessie users:*

If you are using the older Raspbian Jessie image, compiling scala is a bit more complicated. The version of Boost available in the Debian Jessie repositories is too old to use with scala, and thus you must compile a newer version yourself. The following explains the extra steps and has been tested on a Raspberry Pi 2 with a clean install of minimal Raspbian Jessie.

* As before, `apt-get update && apt-get upgrade` to install all of the latest software, and increase the system swap size

    ```bash
    sudo /etc/init.d/dphys-swapfile stop
    sudo nano /etc/dphys-swapfile
    CONF_SWAPSIZE=2048
    sudo /etc/init.d/dphys-swapfile start
    ```


* Then, install the dependencies for scala except for `libunwind` and `libboost-all-dev`

* Install the latest version of boost (this may first require invoking `apt-get remove --purge libboost*-dev` to remove a previous version if you're not using a clean install):

    ```bash
    cd
    wget https://sourceforge.net/projects/boost/files/boost/1.72.0/boost_1_72_0.tar.bz2
    tar xvfo boost_1_72_0.tar.bz2
    cd boost_1_72_0
    ./bootstrap.sh
    sudo ./b2
    ```

* Wait ~8 hours

    ```bash    
    sudo ./bjam cxxflags=-fPIC cflags=-fPIC -a install
    ```

* Wait ~4 hours

* From here, follow the [general Raspberry Pi instructions](#on-the-raspberry-pi) from the "Clone scala and checkout most recent release version" step.

#### On Windows:

Binaries for Windows are built on Windows using the MinGW toolchain within
[MSYS2 environment](https://www.msys2.org). The MSYS2 environment emulates a
POSIX system. The toolchain runs within the environment and *cross-compiles*
binaries that can run outside of the environment as a regular Windows
application.

**Preparing the build environment**

* Download and install the [MSYS2 installer](https://www.msys2.org), either the 64-bit or the 32-bit package, depending on your system.
* Open the MSYS shell via the `MSYS2 Shell` shortcut
* Update packages using pacman:

    ```bash
    pacman -Syu
    ```

* Exit the MSYS shell using Alt+F4
* Edit the properties for the `MSYS2 Shell` shortcut changing "msys2_shell.bat" to "msys2_shell.cmd -mingw64" for 64-bit builds or "msys2_shell.cmd -mingw32" for 32-bit builds
* Restart MSYS shell via modified shortcut and update packages again using pacman:

    ```bash
    pacman -Syu
    ```


* Install dependencies:

    To build for 64-bit Windows:

    ```bash
    pacman -S mingw-w64-x86_64-toolchain make mingw-w64-x86_64-cmake mingw-w64-x86_64-boost mingw-w64-x86_64-openssl mingw-w64-x86_64-zeromq mingw-w64-x86_64-libsodium mingw-w64-x86_64-hidapi mingw-w64-x86_64-unbound
    ```

    To build for 32-bit Windows:

    ```bash
    pacman -S mingw-w64-i686-toolchain make mingw-w64-i686-cmake mingw-w64-i686-boost mingw-w64-i686-openssl mingw-w64-i686-zeromq mingw-w64-i686-libsodium mingw-w64-i686-hidapi mingw-w64-i686-unbound
    ```

* Open the MingW shell via `MinGW-w64-Win64 Shell` shortcut on 64-bit Windows
  or `MinGW-w64-Win64 Shell` shortcut on 32-bit Windows. Note that if you are
  running 64-bit Windows, you will have both 64-bit and 32-bit MinGW shells.

**Cloning**

* To git clone, run:

    ```bash
    git clone --recursive https://github.com/scala-project/scala.git
    ```

**Building**

* Change to the cloned directory, run:

    ```bash
    cd scala
    ```

* If you would like a specific [version/tag](https://github.com/scala-project/scala/tags), do a git checkout for that version. eg. 'v0.18.1.2'. If you don't care about the version and just want binaries from master, skip this step:

    ```bash
    git checkout v0.18.1.2
    ```

* If you are on a 64-bit system, run:

    ```bash
    make release-static-win64
    ```

* If you are on a 32-bit system, run:

    ```bash
    make release-static-win32
    ```

* The resulting executables can be found in `build/release/bin`

* **Optional**: to build Windows binaries suitable for debugging on a 64-bit system, run:

    ```bash
    make debug-static-win64
    ```

* **Optional**: to build Windows binaries suitable for debugging on a 32-bit system, run:

    ```bash
    make debug-static-win32
    ```

* The resulting executables can be found in `build/debug/bin`

### On FreeBSD:

The project can be built from scratch by following instructions for Linux above(but use `gmake` instead of `make`). 
If you are running scala in a jail, you need to add `sysvsem="new"` to your jail configuration, otherwise lmdb will throw the error message: `Failed to open lmdb environment: Function not implemented`.

scala is also available as a port or package as `scala-cli`.

### On OpenBSD:

You will need to add a few packages to your system. `pkg_add cmake gmake zeromq libiconv boost libunbound`.

The `doxygen` and `graphviz` packages are optional and require the xbase set.
Running the test suite also requires `py3-requests` package.

Build scala: `gmake`

Note: you may encounter the following error when compiling the latest version of scala as a normal user:

```
LLVM ERROR: out of memory
c++: error: unable to execute command: Abort trap (core dumped)
```

Then you need to increase the data ulimit size to 2GB and try again: `ulimit -d 2000000`

### On NetBSD:

Check that the dependencies are present: `pkg_info -c libexecinfo boost-headers boost-libs protobuf readline libusb1 zeromq git-base pkgconf gmake cmake | more`, and install any that are reported missing, using `pkg_add` or from your pkgsrc tree.  Readline is optional but worth having.

Third-party dependencies are usually under `/usr/pkg/`, but if you have a custom setup, adjust the "/usr/pkg" (below) accordingly.

Clone the scala repository recursively and checkout the most recent release as described above. Then build scala: `gmake BOOST_ROOT=/usr/pkg LDFLAGS="-Wl,-R/usr/pkg/lib" release`.  The resulting executables can be found in `build/NetBSD/[Release version]/Release/bin/`.

### On Solaris:

The default Solaris linker can't be used, you have to install GNU ld, then run cmake manually with the path to your copy of GNU ld:

```bash
mkdir -p build/release
cd build/release
cmake -DCMAKE_LINKER=/path/to/ld -D CMAKE_BUILD_TYPE=Release ../..
cd ../..
```

Then you can run make as usual.

### Building portable statically linked binaries

By default, in either dynamically or statically linked builds, binaries target the specific host processor on which the build happens and are not portable to other processors. Portable binaries can be built using the following targets:

* ```make release-static-linux-x86_64``` builds binaries on Linux on x86_64 portable across POSIX systems on x86_64 processors
* ```make release-static-linux-i686``` builds binaries on Linux on x86_64 or i686 portable across POSIX systems on i686 processors
* ```make release-static-linux-armv8``` builds binaries on Linux portable across POSIX systems on armv8 processors
* ```make release-static-linux-armv7``` builds binaries on Linux portable across POSIX systems on armv7 processors
* ```make release-static-linux-armv6``` builds binaries on Linux portable across POSIX systems on armv6 processors
* ```make release-static-win64``` builds binaries on 64-bit Windows portable across 64-bit Windows systems
* ```make release-static-win32``` builds binaries on 64-bit or 32-bit Windows portable across 32-bit Windows systems

### Cross Compiling

You can also cross-compile static binaries on Linux for Windows and macOS with the `depends` system.

* ```make depends target=x86_64-linux-gnu``` for 64-bit linux binaries.
* ```make depends target=x86_64-w64-mingw32``` for 64-bit windows binaries.
  * Requires: `python3 g++-mingw-w64-x86-64 wine1.6 bc`
  * You also need to run:  
```update-alternatives --set x86_64-w64-mingw32-g++ x86_64-w64-mingw32-g++-posix && update-alternatives --set x86_64-w64-mingw32-gcc x86_64-w64-mingw32-gcc-posix```
* ```make depends target=x86_64-apple-darwin11``` for macOS binaries.
  * Requires: `cmake imagemagick libcap-dev librsvg2-bin libz-dev libbz2-dev libtiff-tools python-dev`
* ```make depends target=i686-linux-gnu``` for 32-bit linux binaries.
  * Requires: `g++-multilib bc`
* ```make depends target=i686-w64-mingw32``` for 32-bit windows binaries.
  * Requires: `python3 g++-mingw-w64-i686`
* ```make depends target=arm-linux-gnueabihf``` for armv7 binaries.
  * Requires: `g++-arm-linux-gnueabihf`
* ```make depends target=aarch64-linux-gnu``` for armv8 binaries.
  * Requires: `g++-aarch64-linux-gnu`
* ```make depends target=riscv64-linux-gnu``` for RISC V 64 bit binaries.
  * Requires: `g++-riscv64-linux-gnu`
* ```make depends target=x86_64-unknown-freebsd``` for freebsd binaries.
  * Requires: `clang-8`
* ```make depends target=arm-linux-android``` for 32bit android binaries
* ```make depends target=aarch64-linux-android``` for 64bit android binaries


The required packages are the names for each toolchain on apt. Depending on your distro, they may have different names. The `depends` system has been tested on Ubuntu 18.04 and 20.04.

Using `depends` might also be easier to compile scala on Windows than using MSYS. Activate Windows Subsystem for Linux (WSL) with a distro (for example Ubuntu), install the apt build-essentials and follow the `depends` steps as depicted above.

The produced binaries still link libc dynamically. If the binary is compiled on a current distribution, it might not run on an older distribution with an older installation of libc. Passing `-DBACKCOMPAT=ON` to cmake will make sure that the binary will run on systems having at least libc version 2.17.

### Gitian builds

See [contrib/gitian/README.md](contrib/gitian/README.md).

## Installing scala from a package

**DISCLAIMER: These packages are not part of this repository or maintained by this project's contributors, and as such, do not go through the same review process to ensure their trustworthiness and security.**

Packages are available for

* Debian Buster

    See the [instructions in the whonix/scala-gui repository](https://gitlab.com/whonix/scala-gui#how-to-install-scala-using-apt-get)

* Debian Bullseye and Sid

    ```bash
    sudo apt install scala
    ```
More info and versions in the [Debian package tracker](https://tracker.debian.org/pkg/scala).

* Arch Linux [(via Community packages)](https://www.archlinux.org/packages/community/x86_64/scala/):

    ```bash
    sudo pacman -S scala
    ```

* Void Linux:

    ```bash
    xbps-install -S scala
    ```

* GuixSD

    ```bash
    guix package -i scala
    ```

* Gentoo [scala overlay](https://github.com/gentoo-scala/gentoo-scala)

    ```bash
    emerge --noreplace eselect-repository
    eselect repository enable scala
    emaint sync -r scala
    echo '*/*::scala ~amd64' >> /etc/portage/package.accept_keywords
    emerge net-p2p/scala
    ```

* macOS [(homebrew)](https://brew.sh/)
    ```bash
    brew install scala
    ```

* Docker

    ```bash
    # Build using all available cores
    docker build -t scala .

    # or build using a specific number of cores (reduce RAM requirement)
    docker build --build-arg NPROC=1 -t scala .

    # either run in foreground
    docker run -it -v /scala/chain:/home/scala/.bitscala -v /scala/wallet:/wallet -p 18080:18080 scala

    # or in background
    docker run -it -d -v /scala/chain:/home/scala/.bitscala -v /scala/wallet:/wallet -p 18080:18080 scala
    ```

* The build needs 3 GB space.
* Wait one hour or more

Packaging for your favorite distribution would be a welcome contribution!

## Running scalad

The build places the binary in `bin/` sub-directory within the build directory
from which cmake was invoked (repository root by default). To run in the
foreground:

```bash
./bin/scalad
```

To list all available options, run `./bin/scalad --help`.  Options can be
specified either on the command line or in a configuration file passed by the
`--config-file` argument.  To specify an option in the configuration file, add
a line with the syntax `argumentname=value`, where `argumentname` is the name
of the argument without the leading dashes, for example, `log-level=1`.

To run in background:

```bash
./bin/scalad --log-file scalad.log --detach
```

To run as a systemd service, copy
[scalad.service](utils/systemd/scalad.service) to `/etc/systemd/system/` and
[scalad.conf](utils/conf/scalad.conf) to `/etc/`. The [example
service](utils/systemd/scalad.service) assumes that the user `scala` exists
and its home is the data directory specified in the [example
config](utils/conf/scalad.conf).

If you're on Mac, you may need to add the `--max-concurrency 1` option to
scala-wallet-cli, and possibly scalad, if you get crashes refreshing.

## Internationalization

See [README.i18n.md](docs/README.i18n.md).

## Using Tor

> There is a new, still experimental, [integration with Tor](docs/ANONYMITY_NETWORKS.md). The
> feature allows connecting over IPv4 and Tor simultaneously - IPv4 is used for
> relaying blocks and relaying transactions received by peers whereas Tor is
> used solely for relaying transactions received over local RPC. This provides
> privacy and better protection against surrounding node (sybil) attacks.

While scala isn't made to integrate with Tor, it can be used wrapped with torsocks, by
setting the following configuration parameters and environment variables:

* `--p2p-bind-ip 127.0.0.1` on the command line or `p2p-bind-ip=127.0.0.1` in
  scalad.conf to disable listening for connections on external interfaces.
* `--no-igd` on the command line or `no-igd=1` in scalad.conf to disable IGD
  (UPnP port forwarding negotiation), which is pointless with Tor.
* `DNS_PUBLIC=tcp` or `DNS_PUBLIC=tcp://x.x.x.x` where x.x.x.x is the IP of the
  desired DNS server, for DNS requests to go over TCP, so that they are routed
  through Tor. When IP is not specified, scalad uses the default list of
  servers defined in [src/common/dns_utils.cpp](src/common/dns_utils.cpp).
* `TORSOCKS_ALLOW_INBOUND=1` to tell torsocks to allow scalad to bind to interfaces
   to accept connections from the wallet. On some Linux systems, torsocks
   allows binding to localhost by default, so setting this variable is only
   necessary to allow binding to local LAN/VPN interfaces to allow wallets to
   connect from remote hosts. On other systems, it may be needed for local wallets
   as well.
* Do NOT pass `--detach` when running through torsocks with systemd, (see
  [utils/systemd/scalad.service](utils/systemd/scalad.service) for details).
* If you use the wallet with a Tor daemon via the loopback IP (eg, 127.0.0.1:9050),
  then use `--untrusted-daemon` unless it is your own hidden service.

Example command line to start scalad through Tor:

```bash
DNS_PUBLIC=tcp torsocks scalad --p2p-bind-ip 127.0.0.1 --no-igd
```

A helper script is in contrib/tor/scala-over-tor.sh. It assumes Tor is installed
already, and runs Tor and scala with the right configuration.

### Using Tor on Tails

TAILS ships with a very restrictive set of firewall rules. Therefore, you need
to add a rule to allow this connection too, in addition to telling torsocks to
allow inbound connections. Full example:

```bash
sudo iptables -I OUTPUT 2 -p tcp -d 127.0.0.1 -m tcp --dport 18081 -j ACCEPT
DNS_PUBLIC=tcp torsocks ./scalad --p2p-bind-ip 127.0.0.1 --no-igd --rpc-bind-ip 127.0.0.1 \
    --data-dir /home/amnesia/Persistent/your/directory/to/the/blockchain
```

## Pruning

As of April 2022, the full scala blockchain file is about 130 GB. One can store a pruned blockchain, which is about 45 GB.
A pruned blockchain can only serve part of the historical chain data to other peers, but is otherwise identical in
functionality to the full blockchain.
To use a pruned blockchain, it is best to start the initial sync with `--prune-blockchain`. However, it is also possible
to prune an existing blockchain using the `scala-blockchain-prune` tool or using the `--prune-blockchain` `scalad` option
with an existing chain. If an existing chain exists, pruning will temporarily require disk space to store both the full
and pruned blockchains.

For more detailed information see the ['Pruning' entry in the scalapedia](https://www.getscala.org/resources/scalapedia/pruning.html)

## Debugging

This section contains general instructions for debugging failed installs or problems encountered with scala. First, ensure you are running the latest version built from the GitHub repo.

### Obtaining stack traces and core dumps on Unix systems

We generally use the tool `gdb` (GNU debugger) to provide stack trace functionality, and `ulimit` to provide core dumps in builds which crash or segfault.

* To use `gdb` in order to obtain a stack trace for a build that has stalled:

Run the build.

Once it stalls, enter the following command:

```bash
gdb /path/to/scalad `pidof scalad`
```

Type `thread apply all bt` within gdb in order to obtain the stack trace

* If however the core dumps or segfaults:

Enter `ulimit -c unlimited` on the command line to enable unlimited filesizes for core dumps

Enter `echo core | sudo tee /proc/sys/kernel/core_pattern` to stop cores from being hijacked by other tools

Run the build.

When it terminates with an output along the lines of "Segmentation fault (core dumped)", there should be a core dump file in the same directory as scalad. It may be named just `core`, or `core.xxxx` with numbers appended.

You can now analyse this core dump with `gdb` as follows:

```bash
gdb /path/to/scalad /path/to/dumpfile`
```

Print the stack trace with `bt`

 * If a program crashed and cores are managed by systemd, the following can also get a stack trace for that crash:

```bash
coredumpctl -1 gdb
```

#### To run scala within gdb:

Type `gdb /path/to/scalad`

Pass command-line options with `--args` followed by the relevant arguments

Type `run` to run scalad

### Analysing memory corruption

There are two tools available:

#### ASAN

Configure scala with the -D SANITIZE=ON cmake flag, eg:

```bash
cd build/debug && cmake -D SANITIZE=ON -D CMAKE_BUILD_TYPE=Debug ../..
```

You can then run the scala tools normally. Performance will typically halve.

#### valgrind

Install valgrind and run as `valgrind /path/to/scalad`. It will be very slow.

### LMDB

Instructions for debugging suspected blockchain corruption as per @HYC

There is an `mdb_stat` command in the LMDB source that can print statistics about the database but it's not routinely built. This can be built with the following command:

```bash
cd ~/scala/external/db_drivers/liblmdb && make
```

The output of `mdb_stat -ea <path to blockchain dir>` will indicate inconsistencies in the blocks, block_heights and block_info table.

The output of `mdb_dump -s blocks <path to blockchain dir>` and `mdb_dump -s block_info <path to blockchain dir>` is useful for indicating whether blocks and block_info contain the same keys.

These records are dumped as hex data, where the first line is the key and the second line is the data.

# Known Issues

## Protocols

### Socket-based

Because of the nature of the socket-based protocols that drive scala, certain protocol weaknesses are somewhat unavoidable at this time. While these weaknesses can theoretically be fully mitigated, the effort required (the means) may not justify the ends. As such, please consider taking the following precautions if you are a scala node operator:

- Run `scalad` on a "secured" machine. If operational security is not your forte, at a very minimum, have a dedicated a computer running `scalad` and **do not** browse the web, use email clients, or use any other potentially harmful apps on your `scalad` machine. **Do not click links or load URL/MUA content on the same machine**. Doing so may potentially exploit weaknesses in commands which accept "localhost" and "127.0.0.1".
- If you plan on hosting a public "remote" node, start `scalad` with `--restricted-rpc`. This is a must.

### Blockchain-based

Certain blockchain "features" can be considered "bugs" if misused correctly. Consequently, please consider the following:

- When receiving scala, be aware that it may be locked for an arbitrary time if the sender elected to, preventing you from spending that scala until the lock time expires. You may want to hold off acting upon such a transaction until the unlock time lapses. To get a sense of that time, you can consider the remaining blocktime until unlock as seen in the `show_transfers` command.
