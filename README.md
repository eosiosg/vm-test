# EOS_EVM Test Tool
This a standalone evm test project, leveraging eos-vm to execute evm transactions. See [1](https://github.com/eosiosg/eos-challenge).

## Dependency
### 1. [jsconcpp](https://github.com/open-source-parsers/jsoncpp)  
#### Linux:  
`sudo apt-get install libjsoncpp-dev`
#### Mac OS:
`brew install jsoncpp`
### 2. OpenSSL  
#### Linux:  
`sudo apt-get install libssl-dev`
#### Mac OS:
`brew install openssl`

### 3. [eos-vm](https://github.com/EOSIO/eos-vm)
### 4. [evmc](https://github.com/ethereum/evmc)  
### 5. [secp256k1](https://github.com/cryptonomex/secp256k1-zkp.git)
## Usage

### Building from source
1. Clone the repo and create a ```build``` directory:
```
git clone --recursive https://github.com/eosiosg/vm-test
cd vm-test
mkdir build
cd build
```

2. Build the source:
```
cmake ..
cmake --build . -- -j
```

3. Run the test
```
test/EOSEVMTest  
```

4. Include the library in other evmc compatible test schemes
```
lib/libeosevm.dylib
```
