# Multistage docker build, requires docker 17.05

# builder stage
FROM ubuntu:20.04 AS builder

RUN set -ex && \
    apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get --no-install-recommends --yes install \
        automake \
        autotools-dev \
        bsdmainutils \
        build-essential \
        ca-certificates \
        ccache \
        cmake \
        curl \
        git \
        libtool \
        pkg-config \
        gperf \
        libboost-all-dev \
        miniupnpc \
        libunbound-dev \
        graphviz \
        doxygen \
        libunwind8-dev \
        libssl-dev \
        libzmq3-dev \
        libsodium-dev \
        libhidapi-dev \
        libnorm-dev \
        libusb-1.0-0-dev \
        libpgm-dev \
        libprotobuf-dev \
        protobuf-compiler

WORKDIR /src
COPY . .


ARG NPROC
RUN set -ex && \
    git submodule init && git submodule update && \
    rm -rf build

RUN if [ -z "$NPROC" ] ; \
    then cmake -S . -B build -D ARCH="default" -D BUILD_TESTS=ON -D CMAKE_BUILD_TYPE=Release && cmake --build build -j$(nproc); \
    else cmake -S . -B build -D ARCH="default" -D BUILD_TESTS=ON -D CMAKE_BUILD_TYPE=Release && cmake --build build -j$NPROC; \
    fi


# runtime stage
FROM ubuntu:20.04

RUN set -ex && \
    apt-get update && \
    apt-get --no-install-recommends --yes install ca-certificates && \
    apt-get clean && \
    rm -rf /var/lib/apt

COPY --from=builder /src/build/bin/ /usr/local/bin/

# Create scala user
COPY entrypoint.sh /entrypoint.sh

RUN adduser --system --group --disabled-password scala && \
	chmod 755 /entrypoint.sh && \
    chown scala:scala /entrypoint.sh

# Contains the blockchain
VOLUME /home/scala/.scala

# Put in wallet file in wallet directory and set wallet file name into environment
ENV SCALA_WALLET_DISABLED=false

ENV SCALA_WALLET_DIRECTORY=/home/scala/wallet

ENV SCALA_WALLET_JSON=''

ENV SCALA_WALLET_RPC_LOGIN=''

ENV SCALA_DAEMON_ADDRESS= ""

VOLUME "$SCALA_WALLET_RPC_LOGIN"

EXPOSE 11811
EXPOSE 11812
EXPOSE 11813

# switch to user scala
USER scala

ENTRYPOINT ["/entrypoint.sh"]

