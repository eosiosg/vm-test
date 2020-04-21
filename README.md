# EOS_EVM Test Tool
## Description
This project provides a light, standalone eos-vm testing environment, which can be used for contracts testing without deploying on a testnet.
For now this tool is designated for the [challenge](https://github.com/eosiosg/eos-challenge), to execute evm transactions. See [1](https://eosio.devpost.com/) for more deails.

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


3. Include the library in other evmc compatible test schemes:
#### Linux:  
```
lib/libeosevm.so  
```
#### Mac OS:`
```
lib/libeosevm.dylib
```
example: 
using `testeth` from [aleth](https://github.com/ethereum/aleth):
`testeth -t VMTests -- --all --vm /path_to_build/lib/libeosevm.dylib`

4. Run supplementary tests:
```
test/EOSEVMTest  

```
supplementary tests cover cases that require states check, which are likely to fail on some eth tests. Therefore, these cases were integrated explicitly in this project.  
5.  Run custom eos contract tests:
refer to `test/eosio_token_test.cpp` to write custom tests.