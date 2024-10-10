# Using Scala with Docker

This guide provides instructions on how to set up and run a Scala application using Docker.

## Docker Build

Build the Scala Docker image from the latest release:

```
docker build -t scalad:latest .
```

## Docker Pull Image

You can use the pre-built image from the Docker Hub repository `ahmyi`:

```
docker pull ahmyi/scalad:latest
```

Before using the Scala daemon and wallet containers on the same host, create a network. You can also use the container's name instead. Below is a sample command using a Docker network.

To create a Docker network with a specific subnet, replace `network_name` with your desired name:

```
docker network create --subnet 192.0.2.0/24 network_name
```

## How to Run the Scala Daemon

This command specifies the network, sets a static IP, and defines an environment variable to disable wallet mode and enable daemon mode. This separation follows best practices, ensuring that each service does not interrupt the other.

```
docker run -d --network network_name --restart always --ip=192.0.2.69 -e SCALA_WALLET_DISABLED=true --name scala_daemon ahmyi/scalad:latest
```

You can replace the tag with the actual tag used if you're building the image or using other Docker Hub namespaces.

## How to Run the Scala Wallet

Launch the Scala wallet, binding it to a port and setting it to connect to the daemon. Modify the environment variables as needed. Refer to the "Working with Wallets" section for more details on using RPC via Docker.

```
docker run -d -p 11813:11813 --network network_name --restart always -e SCALA_WALLET_DISABLED=false -e SCALA_DAEMON_ADDRESS=192.0.2.69:11812 --name scala_wallet ahmyi/scalad:latest
```

## Environment Variables

- **SCALA_WALLET_DISABLED** (default: `false`):  
  Set to `true` to run the image as a daemon only (no wallet).

- **SCALA_WALLET_DIRECTORY** (default: `/home/scala/wallet`):  
  Specify a different directory for the wallet.

- **SCALA_WALLET_RPC_LOGIN** (default: `''`):  
  Optional RPC login credentials.

- **SCALA_DAEMON_ADDRESS** (default: `node.scalaproject.io:11812`):  
  The address of the Scala daemon.

- **SCALA_WALLET_JSON_FILE** (default: `''`):  
  Optional method to load the wallet from a JSON file.

## Working with RPC Wallets

### Without JSON

When using the wallet without a JSON file, the `SCALA_WALLET_JSON_FILE` environment variable is not set. You can perform the following operations:

#### Generate a Wallet from Keys

Use this RPC call to generate a wallet from your keys:

```
curl -i -X POST http://localhost:11812/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"generate_from_keys", "params":{"address":"...", "filename":"wallet", "password":"password", "spendkey":"...", "viewkey":"..."}}'
```

#### Open an Existing Wallet

Open an existing wallet with the following command:

```
curl -X POST http://localhost:11812/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"open_wallet","params":{"filename":"wallet","password":"password"}}' -H 'Content-Type: application/json'
```

#### Create a New Wallet

To create a new wallet, use:

```
curl http://localhost:11812/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"create_wallet","params":{"filename":"wallet","password":"password","language":"English"}}' -H 'Content-Type: application/json'
```

#### Restore a Wallet by Deterministic Seed

Restore a wallet using a deterministic seed with this command:

```
curl http://localhost:38083/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"restore_deterministic_wallet","params":{"filename":"wallet","password":"password","seed":"...","restore_height":0,"language":"English","seed_offset":""}}' -H 'Content-Type: application/json'
```

### With JSON

If you have an existing wallet, you can use a JSON configuration like this:

```json
{
	"version": 1,
  	"filename": "wallet",
  	"scan_from_height": 0,
  	"password": "password",
  	"seed": "..."
}
```

To apply this JSON configuration, place it in your wallet directory and run:

```
docker run -d -p 11813:11813 --network network_name --restart always -e SCALA_WALLET_JSON_FILE=wallet.json -e SCALA_WALLET_DISABLED=false -e SCALA_DAEMON_ADDRESS=192.0.2.69:11812 -v $(pwd)/wallet:/home/scala/wallet --name scala_wallet ahmyi/scalad:latest
```
