//
// Created by Vince on 26/2/20.
//
#include "eosio_token_tester.hpp"

TEST_F(eosio_token_tester, create){
    create params = {alice, {10000000000000, 1397703940}};
    eosevm.exec("create", params);
    EXPECT_EQ(1, 1);
}

TEST_F(eosio_token_tester, issue){
    create create_params = {alice, {10000000000000, 1397703940}};
    eosevm.exec("create", create_params);
    asset issue_amount = {10000000, 1397703940};
    issue issue_params = {alice, issue_amount, "issue 1000 EOS"};
    eosevm.exec("issue", issue_params);
    EXPECT_EQ(issue_amount, get_balance(alice).amount);
}

TEST_F(eosio_token_tester, transfer){
    create create_params = {alice, {10000000000000, 1397703940}};
    eosevm.exec("create", create_params);

    asset issue_amount = {10000000, 1397703940};
    issue issue_params = {alice, issue_amount, "issue 1000 EOS"};
    eosevm.exec("issue", issue_params);
    EXPECT_EQ(issue_amount, get_balance(alice).amount);

    asset transfer_amount = {5000000, 1397703940};
    transfer transfer_params = {alice, bob, transfer_amount, "transfer 50 EOS to bob"};
    eosevm.exec("transfer", transfer_params);
    EXPECT_EQ(transfer_amount, get_balance(bob).amount);
    EXPECT_EQ(issue_amount-transfer_amount, get_balance(alice).amount);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}