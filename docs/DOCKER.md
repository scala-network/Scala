# Using Scala with Docker

This guide provides instructions on how to set up and run the Scala application using Docker.

## Step 1: Create a Docker Network

Create a Docker network with a specific subnet. Replace `network_name` with your desired network name.

```bash
docker network create --subnet 192.0.2.0/24 network_name
```

## Step 2: Build the Scala Docker Image

Build the Scala Docker image, specifying the number of processors to use (NPROC). 

```bash
docker build -t scalad:latest --build-arg NPROC=8 .
```

## Step 3: Run the Scala Daemon

Start the Scala daemon in detached mode. This command specifies the network, sets a static IP, and defines an environment variable to disable the wallet.

```bash
docker run -d --network network_name --restart always --ip=192.0.2.69 -e SCALA_WALLET_DISABLED=true --name scala_daemon scalad:latest
```

## Step 4: Run the Scala Wallet

Launch the Scala wallet, binding it to a port and setting it to connect to the daemon. Modify the environment variables as needed.

```bash
docker run -d -p 11813:11813 --network network_name --restart always -e SCALA_WALLET_DISABLED=false -e SCALA_DAEMON_ADDRESS=192.0.2.69:11812 --name scala_wallet scalad:latest
```

## Environment Variables

- **SCALA_WALLET_DISABLED** (default: false)  
  Set to `true` to run the image as a daemon only (no wallet).

- **SCALA_WALLET_DIRECTORY** (default: `/home/scala/wallet`)  
  Specify a different directory for the wallet.

- **SCALA_WALLET_RPC_LOGIN** (default: `''`)  
  Optional RPC login credentials.

- **SCALA_DAEMON_ADDRESS** (default: `node.scalaproject.io:11812`)  
  The address of the Scala daemon.

- **SCALA_WALLET_JSON_FILE** (default: `''`)  
  Optional method to load the wallet from a JSON file. Not set when using the wallet without JSON.

## Working with Wallets

### Without JSON

When using the wallet without a JSON file, the `SCALA_WALLET_JSON_FILE` environment variable is not set. You can perform the following operations:

#### 1. Generate a Wallet from Keys

Use this RPC call to generate a wallet from your keys:

```bash
curl -i -X POST http://localhost:11812/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"generate_from_keys", "params":{"address":"...", "filename":"wallet", "password":"password", "spendkey":"...", "viewkey":"..."}}'
```

#### 2. Open an Existing Wallet

Open an existing wallet with the following command:

```bash
curl -X POST http://localhost:11812/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"open_wallet","params":{"filename":"wallet","password":"password"}}' -H 'Content-Type: application/json'
```

#### 3. Create a New Wallet

To create a new wallet, use:

```bash
curl http://localhost:11812/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"create_wallet","params":{"filename":"wallet","password":"password","language":"English"}}' -H 'Content-Type: application/json'
```

#### 4. Restore a Wallet by Deterministic Seed

Restore a wallet using a deterministic seed with this command:

```bash
curl http://localhost:38083/json_rpc -d '{"jsonrpc":"2.0","id":"0","method":"restore_deterministic_wallet","params":{"filename":"wallet","password":"password","seed":"...","restore_height":0, "language":"English","seed_offset":""}}' -H 'Content-Type: application/json'
```

### With JSON (For Existing Wallet)

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
