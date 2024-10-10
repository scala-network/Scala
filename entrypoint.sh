#!/bin/sh

SCALA_HOME="/home/scala/.scala"

if [ "$SCALA_WALLET_DISABLED" = "false" ]; then
	SCALA_ARGUMENTS="--trusted-daemon --non-interactive --confirm-external-bin --log-level=1 --rpc-bind-port 11813 --max-log-files 2 --rpc-bind-ip=0.0.0.0"
	if [ "$SCALA_DAEMON_ADDRESS" = "" ]; then
		SCALA_DAEMON_ADDRESS="scala_daemon:11812";
	fi
	
	SCALA_ARGUMENTS="$SCALA_ARGUMENTS --daemon-address $SCALA_DAEMON_ADDRESS"

	SCALA_WALLET_DIRECTORY="/home/scala/wallet";

	if [ ! -d "$SCALA_WALLET_DIRECTORY" ]; then
	  mkdir -p $SCALA_WALLET_DIRECTORY;
	  chown -R scala:scala $SCALA_WALLET_DIRECTORY
	fi
		
	SCALA_ARGUMENTS="$SCALA_ARGUMENTS --wallet-dir $SCALA_WALLET_DIRECTORY --log-file $SCALA_WALLET_DIRECTORY/logs/scala-wallet-rpc.log "

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
	if [ ! -d "$SCALA_HOME" ]; then
	  	mkdir -p "$SCALA_HOME"
		chown -R scala:scala "$SCALA_HOME"
	fi
	
	/usr/local/bin/scalad --p2p-bind-ip=0.0.0.0 --p2p-bind-port=11811 --rpc-bind-ip=0.0.0.0 --rpc-bind-port=11812 --non-interactive --confirm-external-bind --no-zmq
fi


