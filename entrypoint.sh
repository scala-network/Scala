#!/bin/sh

if [ "$SCALA_WALLET_DISABLED" = "false" ]; then
	SCALA_ARGUMENTS="--trusted-daemon --non-interactive --log-level=1 --rpc-bind-port 11813 --rpc-bind-ip=0.0.0.0"
	if [ "$SCALA_DAEMON_ADDRESS" = "" ]; then
		SCALA_DAEMON_ADDRESS="node.scalaproject.io:11812";
	fi
		chown -R scala:scala /wallet && \
	SCALA_ARGUMENTS="$SCALA_ARGUMENTS --daemon-address $SCALA_DAEMON_ADDRESS"

	if [ "$SCALA_WALLET_DIRECTORY" = "" ]; then
		SCALA_WALLET_DIRECTORY="/home/scala/wallet";
	fi

	if [ ! -d "$SCALA_WALLET_DIRECTORY" ]; then
	  mkdir -p $SCALA_WALLET_DIRECTORY;
	  chown -R scala:scala $SCALA_WALLET_DIRECTORY
	fi
		
	SCALA_ARGUMENTS="$SCALA_ARGUMENTS --wallet-dir $SCALA_WALLET_DIRECTORY"

	if [ "$SCALA_WALLET_RPC_LOGIN" != "" ]; then
		SCALA_ARGUMENTS="$SCALA_ARGUMENTS --rpc-login $SCALA_WALLET_RPC_LOGIN"
	else
		SCALA_ARGUMENTS="$SCALA_ARGUMENTS --disable-rpc-login"
	fi

	if [ "$SCALA_WALLET_JSON_FILE" != "" ]; then
		SCALA_ARGUMENTS="$SCALA_ARGUMENTS --generate-from-json $SCALA_WALLET_DIRECTORY/$SCALA_WALLET_JSON_FILE"
	fi

	/usr/local/bin/scala-wallet-rpc $SCALA_ARGUMENTS
else
	SCALA_HOME="/home/scala/.scala"
	if [ ! -d "$SCALA_HOME" ]; then
	  	mkdir -p "$SCALA_HOME"
		chown -R scala:scala "$SCALA_HOME"
	fi
	
	/usr/local/bin/scalad --p2p-bind-ip=0.0.0.0 --p2p-bind-port=11812 --rpc-bind-ip=0.0.0.0 --rpc-bind-port=11812 --non-interactive --confirm-external-bind
fi

