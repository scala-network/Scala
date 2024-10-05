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

RUN ls /usr/local/bin/

# Create scala user
RUN adduser --system --group --disabled-password scala && \
	mkdir -p /wallet /home/scala/.scala && \
	chown -R scala:scala /home/scala/.scala && \
	chown -R scala:scala /wallet

# Contains the blockchain
VOLUME /home/scala/.scala

# Generate your wallet via accessing the container and run:
# cd /wallet
# scala-wallet-cli
VOLUME /wallet

EXPOSE 11811
EXPOSE 11812

# switch to user scala
USER scala

ENTRYPOINT ["scalad"]
CMD ["--p2p-bind-ip=0.0.0.0", "--p2p-bind-port=11811", "--rpc-bind-ip=0.0.0.0", "--rpc-bind-port=11812", "--non-interactive", "--confirm-external-bind"]

