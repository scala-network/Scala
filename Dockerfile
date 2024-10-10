FROM ubuntu:20.04

RUN set -ex && \
    apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get --no-install-recommends --yes install ca-certificates wget unzip && \
    apt-get clean && \
    rm -rf /var/lib/apt

WORKDIR /usr/local/bin

RUN wget https://github.com/scala-network/Scala/releases/download/v8.0.3/scala-v8.0.3-x86_64-unknown-linux-gnu.zip -O scala.zip && \
    unzip scala.zip

COPY entrypoint.sh /entrypoint.sh

RUN adduser --system --group --disabled-password scala && \
	chmod 755 /entrypoint.sh && \
    chown scala:scala /entrypoint.sh && \
    mkdir -p /home/scala/.scala && \
    mkdir -p /home/scala/wallet && \
    chown -Rfv scala:scala /home/scala 

# Contains the blockchain
VOLUME /home/scala/.scala

# Put in wallet file in wallet directory and set wallet file name into environment
ENV SCALA_WALLET_DISABLED=false

ENV SCALA_WALLET_DIRECTORY=/home/scala/wallet

ENV SCALA_WALLET_JSON=''

ENV SCALA_WALLET_RPC_LOGIN=''

ENV SCALA_DAEMON_ADDRESS=''

VOLUME "$SCALA_WALLET_DIRECTORY"

EXPOSE 11811
EXPOSE 11812
EXPOSE 11813

# switch to user scala
USER scala

ENTRYPOINT ["/entrypoint.sh"]
