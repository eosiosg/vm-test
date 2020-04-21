//
// Created by Vince on 2/3/20.
//
#include "challenge_tester.hpp"


TEST_F(challenge_tester, basic){

    eosevm.create(accountb, "aaaaaa");
    eosevm.create(accountb, "d81f4358cb8cab53d005e7f47c7ba3f5116000a6");
    eosevm.create(accountb, "cd1722f2947def4cf144679da39c4c32bdc35681");
    eosevm.create(accountb, "0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6");

    eosevm.create(accountc, "aaaaaa");
    eosevm.create(accountc, "39944247c2edf660d86d57764b58d83b8eee9014");

    eosevm.create(accountd, "aaaaaa");
    eosevm.create(accountd, "e327e755438fbdf9e60891d9b752da10a38514d1");

    // ERC20----------------------------------with nonce -------------------------------------
    // create contract Serialized TX
    eosevm.raw("f90f1f8080830f42408080b90ed16060604052341561000f57600080fd5b604051610dd1380380610dd18339810160405280805190602001909190805182019190602001805190602001909190805182019190505083600160003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020819055508360008190555082600390805190602001906100a79291906100e3565b5081600460006101000a81548160ff021916908360ff16021790555080600590805190602001906100d99291906100e3565b5050505050610188565b828054600181600116156101000203166002900490600052602060002090601f016020900481019282601f1061012457805160ff1916838001178555610152565b82800160010185558215610152579182015b82811115610151578251825591602001919060010190610136565b5b50905061015f9190610163565b5090565b61018591905b80821115610181576000816000905550600101610169565b5090565b90565b610c3a806101976000396000f3006060604052600436106100af576000357c0100000000000000000000000000000000000000000000000000000000900463ffffffff16806306fdde03146100b4578063095ea7b31461014257806318160ddd1461019c57806323b872dd146101c557806327e235e31461023e578063313ce5671461028b5780635c658165146102ba57806370a082311461032657806395d89b4114610373578063a9059cbb14610401578063dd62ed3e1461045b575b600080fd5b34156100bf57600080fd5b6100c76104c7565b6040518080602001828103825283818151815260200191508051906020019080838360005b838110156101075780820151818401526020810190506100ec565b50505050905090810190601f1680156101345780820380516001836020036101000a031916815260200191505b509250505060405180910390f35b341561014d57600080fd5b610182600480803573ffffffffffffffffffffffffffffffffffffffff16906020019091908035906020019091905050610565565b604051808215151515815260200191505060405180910390f35b34156101a757600080fd5b6101af610657565b6040518082815260200191505060405180910390f35b34156101d057600080fd5b610224600480803573ffffffffffffffffffffffffffffffffffffffff1690602001909190803573ffffffffffffffffffffffffffffffffffffffff1690602001909190803590602001909190505061065d565b604051808215151515815260200191505060405180910390f35b341561024957600080fd5b610275600480803573ffffffffffffffffffffffffffffffffffffffff169060200190919050506108f7565b6040518082815260200191505060405180910390f35b341561029657600080fd5b61029e61090f565b604051808260ff1660ff16815260200191505060405180910390f35b34156102c557600080fd5b610310600480803573ffffffffffffffffffffffffffffffffffffffff1690602001909190803573ffffffffffffffffffffffffffffffffffffffff16906020019091905050610922565b6040518082815260200191505060405180910390f35b341561033157600080fd5b61035d600480803573ffffffffffffffffffffffffffffffffffffffff16906020019091905050610947565b6040518082815260200191505060405180910390f35b341561037e57600080fd5b610386610990565b6040518080602001828103825283818151815260200191508051906020019080838360005b838110156103c65780820151818401526020810190506103ab565b50505050905090810190601f1680156103f35780820380516001836020036101000a031916815260200191505b509250505060405180910390f35b341561040c57600080fd5b610441600480803573ffffffffffffffffffffffffffffffffffffffff16906020019091908035906020019091905050610a2e565b604051808215151515815260200191505060405180910390f35b341561046657600080fd5b6104b1600480803573ffffffffffffffffffffffffffffffffffffffff1690602001909190803573ffffffffffffffffffffffffffffffffffffffff16906020019091905050610b87565b6040518082815260200191505060405180910390f35b60038054600181600116156101000203166002900480601f01602080910402602001604051908101604052809291908181526020018280546001816001161561010002031660029004801561055d5780601f106105325761010080835404028352916020019161055d565b820191906000526020600020905b81548152906001019060200180831161054057829003601f168201915b505050505081565b600081600260003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020819055508273ffffffffffffffffffffffffffffffffffffffff163373ffffffffffffffffffffffffffffffffffffffff167f8c5be1e5ebec7d5bd14f71427d1e84f3dd0314c0f7b2291e5b200ac8c7c3b925846040518082815260200191505060405180910390a36001905092915050565b60005481565b600080600260008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002054905082600160008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020541015801561072e5750828110155b151561073957600080fd5b82600160008673ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000206000828254019250508190555082600160008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020600082825403925050819055507fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff8110156108865782600260008773ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020600082825403925050819055505b8373ffffffffffffffffffffffffffffffffffffffff168573ffffffffffffffffffffffffffffffffffffffff167fddf252ad1be2c89b69c2b068fc378daa952ba7f163c4a11628f55a4df523b3ef856040518082815260200191505060405180910390a360019150509392505050565b60016020528060005260406000206000915090505481565b600460009054906101000a900460ff1681565b6002602052816000526040600020602052806000526040600020600091509150505481565b6000600160008373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020549050919050565b60058054600181600116156101000203166002900480601f016020809104026020016040519081016040528092919081815260200182805460018160011615610100020316600290048015610a265780601f106109fb57610100808354040283529160200191610a26565b820191906000526020600020905b815481529060010190602001808311610a0957829003601f168201915b505050505081565b600081600160003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000205410151515610a7e57600080fd5b81600160003373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff1681526020019081526020016000206000828254039250508190555081600160008573ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020600082825401925050819055508273ffffffffffffffffffffffffffffffffffffffff163373ffffffffffffffffffffffffffffffffffffffff167fddf252ad1be2c89b69c2b068fc378daa952ba7f163c4a11628f55a4df523b3ef846040518082815260200191505060405180910390a36001905092915050565b6000600260008473ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff16815260200190815260200160002060008373ffffffffffffffffffffffffffffffffffffffff1673ffffffffffffffffffffffffffffffffffffffff168152602001908152602001600020549050929150505600a165627a7a72305820c4fde1a7c25d01c2c831892bb28af4a76928a6ac10d854b6e98b38d49891c19c002900000000000000000000000000000000000000000000000000000000000027100000000000000000000000000000000000000000000000000000000000000080000000000000000000000000000000000000000000000000000000000000000400000000000000000000000000000000000000000000000000000000000000c0000000000000000000000000000000000000000000000000000000000000000566697273740000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000005457468657200000000000000000000000000000000000000000000000000000025a0a0056e8e578615efc90cb2455170293cd4dcfe3c8b3de6e0e236d83a8565ea13a007b9fab8e218311e6f46da91f24044e1277107d056799dd2e98a7e69930499fa");

    // transfer 39944247c2edf660d86d57764b58d83b8eee9014 100 Serialized TX
    eosevm.raw("f8ab018609184e72a00083271000944a40687878845ef7cfe60b5a6f2cb47627469b7780b844a9059cbb00000000000000000000000039944247c2edf660d86d57764b58d83b8eee9014000000000000000000000000000000000000000000000000000000000000006426a0d0b77737974af56f86db5f49b1aac8703798fd8b9cf97e03c5a4dc1966fa6025a0149779f6c95edda1ff1e4b91105f581a1da759dcebc8ec9fff69afc8356fa16d");

    // transfer e327e755438fbdf9e60891d9b752da10a38514d1 500 Serialized TX
    eosevm.raw("f8ab028609184e72a00083027100944a40687878845ef7cfe60b5a6f2cb47627469b7780b844a9059cbb000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d100000000000000000000000000000000000000000000000000000000000001f425a0d744b0fd51c02ca4ca893c0e938553fc9e2a3dc83673f9e64d8dddecc5d6ef13a015d3d8404b9fcb89063d6adabeea625a19dc537ffd47547d09652f5c8a300908");

    // balance of ${accountc} 39944247c2edf660d86d57764b58d83b8eee9014 Serialized TX
    eosevm.raw("f88a038609184e72a00083027100944a40687878845ef7cfe60b5a6f2cb47627469b7780a470a0823100000000000000000000000039944247c2edf660d86d57764b58d83b8eee901425a085f78f8f3e3b5abc85f933840a0b487d4337834a6da3bf89dd0c0175c4bd0543a06748e82d40d6ebd936f00e31d29ea1be0cef61befc205929a2424867b19b9ca3");

    // balance of ${accountd} e327e755438fbdf9e60891d9b752da10a38514d1 Serialized TX
    eosevm.raw("f88a048609184e72a00083027100944a40687878845ef7cfe60b5a6f2cb47627469b7780a470a08231000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d125a0db8e3abb163f8549baf1c67705f47a821563e2229d1a71b0ed0ff8eb8acaf61ea017391b0e5a67bea5d7de096e844cfcf56062bcbc1f480e29f655da58b0405956");

    // approve  ${accountd} approve ${accountc} 200 Serialized TX
    eosevm.raw("f8ab808609184e72a00083027100944a40687878845ef7cfe60b5a6f2cb47627469b7780b844095ea7b3000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d100000000000000000000000000000000000000000000000000000000000000c825a0ccd3f12a0bfa26089d8e03c8279f7f4ac9ab40e2ab643e849100789ac51a5ea8a07ab4446e0d80d53e786c8ea60f1c15c8e8c847d3138a4bbdb0b7e888df99d633");

    // allowance ${accountd} approve ${accountc} 200 Serialized TX
    eosevm.raw("f8ab018609184e72a00083027100944a40687878845ef7cfe60b5a6f2cb47627469b7780b844dd62ed3e000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d1000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d125a065e3ef8f051860b0c42fd001d5ca1ff6bdd397b0780dadaa6cdd3eecbf7db639a062cf53464901105d5970367b3587902958669be7460e817fb9ffc727ee5746c9");

    // transfer ${accountd} to ${accountc} 20 Serialized TX
    eosevm.raw("f8cb028609184e72a00083027100944a40687878845ef7cfe60b5a6f2cb47627469b7780b86423b872dd000000000000000000000000e327e755438fbdf9e60891d9b752da10a38514d100000000000000000000000039944247c2edf660d86d57764b58d83b8eee9014000000000000000000000000000000000000000000000000000000000000001426a0df880ec31ae3ffbfefd7f3fdfd9db8af64b54171501bfec1714ae50668ca7fc9a055ee4ab38a3263ff9544da6c84d02f73b828c0cee97ba06ec2f74eba0f391fce");

    // balance of ${accountc} 39944247c2edf660d86d57764b58d83b8eee9014 Serialized TX
    eosevm.raw("f88a038609184e72a00083027100944a40687878845ef7cfe60b5a6f2cb47627469b7780a470a0823100000000000000000000000039944247c2edf660d86d57764b58d83b8eee901426a0a2fd83c70eb55afbc1c66b97e3fb4c3ddbf29b4140d1ca6dedff5b1481bce95da03764a5d7abab92f12b7e48a21cff4e016409129423907c7d219a59cb5995fbdf");
    
    EXPECT_TRUE(true);
}

TEST_F(challenge_tester, suicide0){
    // https://github.com/ethereum/tests/blob/7497b116a019beb26215cbea4028df068dea06be/VMTests/vmSystemOperations/suicide0.json

    map<string, account_type> expected_pre_state {
            {"0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6", {"0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6", "0x152d02c7e14af6800000", "0x33ff", "0x00"}},
            {"0xcd1722f3947def4cf144679da39c4c32bdc35681", {"0xcd1722f3947def4cf144679da39c4c32bdc35681", "0x17", "0x6000355415600957005b60203560003555", "0x00"}}
    };

    account_type expected_post_state {
            "0xcd1722f3947def4cf144679da39c4c32bdc35681",
            "0x152d02c7e14af6800017",
            "0x6000355415600957005b60203560003555",
            "0x00"};

    string expected_gas_left = "0x03e6";
    string expected_output = "0x";

    eosevm.create(accountb, "0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6");
    eosevm.create(accountb, "cd1722f3947def4cf144679da39c4c32bdc35681");

    //set pre state for 0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6
    eosevm.set_balance("0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6", "0x152d02c7e14af6800000");
    eosevm.set_code("0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6", "0x33ff" );
    //set pre for state 0xcd1722f3947def4cf144679da39c4c32bdc35681
    eosevm.set_balance("0xcd1722f3947def4cf144679da39c4c32bdc35681", "0x17" );
    eosevm.set_code("0xcd1722f3947def4cf144679da39c4c32bdc35681", "0x6000355415600957005b60203560003555" );

    for (auto& e: expected_pre_state) {
        EXPECT_EQ(e.second, get_account(e.first));
    }

    auto result = eosevm.rawtest(
         "0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6",
         "0xcd1722f3947def4cf144679da39c4c32bdc35681",
         "0x33ff",
         "0x",
         "0x03e8",
         "0x5af3107a4000",
         "0xcd1722f3947def4cf144679da39c4c32bdc35681",
         "0x0186a0",
         {(int)(string_to_i64("0x00")), (uint64_t) string_to_i64("0x01")}
    );

    EXPECT_EQ((int64_t)hex_to_ui64(expected_gas_left), string_to_i64(result.gas_left));
    EXPECT_EQ(expected_output.substr(2), result.output);
    EXPECT_EQ(expected_post_state, get_account("0xcd1722f3947def4cf144679da39c4c32bdc35681"));
}

TEST_F(challenge_tester, suicideNotExistingAccount){
    // https://github.com/ethereum/tests/blob/7497b116a019beb26215cbea4028df068dea06be/VMTests/vmSystemOperations/suicideNotExistingAccount.json

    map<string, account_type> expected_pre_state {
        {"0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6", {"0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6", "0x152d02c7e14af6800000", "0x73aa1722f3947def4cf144679da39c4c32bdc35681ff", "0x00"}},
        {"0xcd1722f3947def4cf144679da39c4c32bdc35681", {"0xcd1722f3947def4cf144679da39c4c32bdc35681", "0x17", "0x6000355415600957005b60203560003555", "0x00"}}
    };

    map<string, account_type> expected_post_state {
        {"0xaa1722f3947def4cf144679da39c4c32bdc35681", {"0xaa1722f3947def4cf144679da39c4c32bdc35681", "0x152d02c7e14af6800000", "0x", "0x00"}},
        {"0xcd1722f3947def4cf144679da39c4c32bdc35681", {"0xcd1722f3947def4cf144679da39c4c32bdc35681", "0x17", "0x6000355415600957005b60203560003555", "0x00"}}
    };

    string expected_gas_left = "0x03e5";
    string expected_output = "0x";

    eosevm.create(accountb, "0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6");
    eosevm.create(accountb, "cd1722f3947def4cf144679da39c4c32bdc35681");

    //set pre state for 0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6
    eosevm.set_balance("0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6", "0x152d02c7e14af6800000");
    eosevm.set_code("0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6", "0x73aa1722f3947def4cf144679da39c4c32bdc35681ff" );
    //set pre for state 0xcd1722f3947def4cf144679da39c4c32bdc35681
    eosevm.set_balance("0xcd1722f3947def4cf144679da39c4c32bdc35681", "0x17");
    eosevm.set_code("0xcd1722f3947def4cf144679da39c4c32bdc35681", "0x6000355415600957005b60203560003555" );

    for (auto& e: expected_pre_state) {
        EXPECT_EQ(e.second, get_account(e.first));
    }

    auto result = eosevm.rawtest(
            "0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6",
            "0xcd1722f3947def4cf144679da39c4c32bdc35681",
            "0x73aa1722f3947def4cf144679da39c4c32bdc35681ff",
            "0x",
            "0x03e8",
            "0x5af3107a4000",
            "0xcd1722f3947def4cf144679da39c4c32bdc35681",
            "0x0186a0",
            {(int)(string_to_i64("0x00")), (uint64_t) string_to_i64("0x01")}
            );

    EXPECT_EQ((int64_t)hex_to_ui64(expected_gas_left), string_to_i64(result.gas_left));
    EXPECT_EQ(expected_output.substr(2), result.output);
    for (auto& e: expected_post_state) {
        EXPECT_EQ(e.second, get_account(e.first));
    }

};

TEST_F(challenge_tester, push32AndSuicide){
    // https://github.com/ethereum/tests/blob/7497b116a019beb26215cbea4028df068dea06be/VMTests/vmPushDupSwapTest/push32AndSuicide.json

    account_type expected_pre_state {
            "0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6",
            "0x152d02c7e14af6800000",
            "0x7fff10112233445566778899aabbccddeeff00112233445566778899aabbccddeeff600355",
            "0x00"};

    account_type expected_post_state {
            "0xbbccddeeff00112233445566778899aabbccddee",
            "0x152d02c7e14af6800000",
            "0x",
            "0x00"};

    string expected_gas_left = "0x01869d";
    string expected_output = "0x";

    eosevm.create(accountb, "0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6");
    eosevm.create(accountb, "cd1722f3947def4cf144679da39c4c32bdc35681");

    //set pre state for 0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6
    eosevm.set_balance("0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6", "0x152d02c7e14af6800000" );
    eosevm.set_code("0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6", "0x7fff10112233445566778899aabbccddeeff00112233445566778899aabbccddeeff600355");

    EXPECT_EQ(expected_pre_state, get_account("0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6"));

    auto result = eosevm.rawtest(
            "0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6",
            "0xcd1722f3947def4cf144679da39c4c32bdc35681",
            "0x7fff10112233445566778899aabbccddeeff00112233445566778899aabbccddeeff600355",
            "0x",
            "0x0186a0",
            "0x5af3107a4000",
            "0xcd1722f3947def4cf144679da39c4c32bdc35681",
            "0x0de0b6b3a7640000",
            {(int)(string_to_i64("0x00")), (uint64_t) string_to_i64("0x01")}
    );

    EXPECT_EQ((int64_t)hex_to_ui64(expected_gas_left), string_to_i64(result.gas_left));
    EXPECT_EQ(expected_output.substr(2), result.output);
    EXPECT_EQ(expected_post_state, get_account("0xbbccddeeff00112233445566778899aabbccddee"));
}

TEST_F(challenge_tester, suicide){
    // https://github.com/ethereum/tests/tree/7497b116a019beb26215cbea4028df068dea06be/VMTests/vmTests

    account_type expected_pre_state {
            "0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6",
            "0x152d02c7e14af6800000",
            "0x33ff",
            "0x00"};

    account_type expected_post_state {
            "0xcd1722f3947def4cf144679da39c4c32bdc35681",
            "0x152d02c7e14af6800000",
            "0x",
            "0x00"};

    string expected_gas_left = "0x01869e";
    string expected_output = "0x";

    eosevm.create(accountb, "0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6");
    eosevm.create(accountb, "cd1722f3947def4cf144679da39c4c32bdc35681");

    //set pre state for 0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6
    eosevm.set_balance("0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6", "0x152d02c7e14af6800000" );
    eosevm.set_code("0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6", "0x33ff");

    EXPECT_EQ(expected_pre_state, get_account("0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6"));
    auto result = eosevm.rawtest(
            "0x0f572e5295c57f15886f9b263e2f6d2d6c7b5ec6",
            "0xcd1722f3947def4cf144679da39c4c32bdc35681",
            "0x33ff",
            "0x",
            "0x0186a0",
            "0x5af3107a4000",
            "0xcd1722f3947def4cf144679da39c4c32bdc35681",
            "0x0de0b6b3a7640000",
            {(int)(string_to_i64("0x00")), (uint64_t) string_to_i64("0x01")}
    );

    EXPECT_EQ((int64_t)hex_to_ui64(expected_gas_left), string_to_i64(result.gas_left));
    EXPECT_EQ(expected_output.substr(2), result.output);
    EXPECT_EQ(expected_post_state, get_account("0xcd1722f3947def4cf144679da39c4c32bdc35681"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}