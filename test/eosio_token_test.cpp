//
// Created by Vince on 26/2/20.
//
#include "eosio_token_tester.hpp"


TEST_F(eosio_token_tester, basic){
    vm eosevm(token_wasm, "eosio.token"_n);
//    std::ifstream input("/Users/vince/CLionProjects/vm-test/lib/contract/eosio.token/eosio.token.wasm", std::ios::binary | std::ios::ate);
//    std::ifstream::pos_type pos = input.tellg();
//    std::vector<char> tmp(pos);
//    input.seekg(0, std::ios::beg);
//    input.read(&tmp[0], pos);
//
//
//    ofstream myfile;
//    myfile.open ("example.txt");
//
//    for(int i=0; i<tmp.size(); ++i)
//        myfile <<  "0x" << setfill('0') << setw(2) <<  std::hex << (0xff & (unsigned int)tmp[i]) << ", ";
  EXPECT_TRUE(1==1);
}