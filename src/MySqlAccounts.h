//
// Created by mwo on 16/12/16.
//

#ifndef RESTBED_SUP_MYSQLACCOUNTS_H
#define RESTBED_SUP_MYSQLACCOUNTS_H

#include "tools.h"
#include "MySqlConnector.h"



#include <iostream>
#include <memory>



namespace supeg
{

using namespace mysqlpp;
using namespace std;
using namespace nlohmann;


class SupTransactionWithOutsAndIns;
class SupInput;
class SupOutput;
class SupTransaction;
class SupPayment;
class SupAccount;
class TxSearch;



class MysqlInputs
{

    shared_ptr<MySqlConnector> conn;

public:

    MysqlInputs(shared_ptr<MySqlConnector> _conn);

    bool
    select(const uint64_t& address_id, vector<SupInput>& ins);

    bool
    select_for_tx(const uint64_t& address_id, vector<SupInput>& ins);

    bool
    select_for_out(const uint64_t& output_id, vector<SupInput>& ins);

    uint64_t
    insert(const SupInput& in_data);

};



class MysqlOutpus
{

    shared_ptr<MySqlConnector> conn;

public:

    MysqlOutpus(shared_ptr<MySqlConnector> _conn);

    bool
    select(const uint64_t& address_id, vector<SupOutput>& outs);

    bool
    select_for_tx(const uint64_t& tx_id, vector<SupOutput>& outs);

    bool
    select(const uint64_t& out_id, SupOutput& out);

    bool
    exist(const string& output_public_key_str, SupOutput& out);



    uint64_t
    insert(const SupOutput& out_data);

};



class MysqlTransactions
{

    shared_ptr<MySqlConnector> conn;

public:

    MysqlTransactions(shared_ptr<MySqlConnector> _conn);

    bool
    select(const uint64_t& address_id, vector<SupTransaction>& txs);


    uint64_t
    insert(const SupTransaction& tx_data);

    uint64_t
    mark_spendable(const uint64_t& tx_id_no);

    uint64_t
    delete_tx(const uint64_t& tx_id_no);


    bool
    exist(const uint64_t& account_id, const string& tx_hash_str, SupTransaction& tx);


    uint64_t
    get_total_recieved(const uint64_t& account_id);


};

class MysqlPayments
{

    shared_ptr<MySqlConnector> conn;

public:

    MysqlPayments(shared_ptr<MySqlConnector> _conn);

    bool
    select(const string& address, vector<SupPayment>& payments);

    bool
    select_by_payment_id(const string& payment_id, vector<SupPayment>& payments);


    uint64_t
    insert(const SupPayment& payment_data);


    bool
    update(SupPayment& payment_orginal, SupPayment& payment_new);


};

class TxSearch;

class MySqlAccounts
{

    shared_ptr<MySqlConnector> conn;

    shared_ptr<MysqlTransactions> mysql_tx;

    shared_ptr<MysqlOutpus> mysql_out;

    shared_ptr<MysqlInputs> mysql_in;

    shared_ptr<MysqlPayments> mysql_payment;


public:

    MySqlAccounts();


    bool
    select(const string& address, SupAccount& account);

    bool
    select(const int64_t& acc_id, SupAccount& account);

    uint64_t
    insert(const string& address,
           const string& viewkey_hash,
           DateTime const& current_blkchain_timestamp,
           uint64_t const& current_blkchain_height = 0);

    uint64_t
    insert_tx(const SupTransaction& tx_data);

    uint64_t
    insert_output(const SupOutput& tx_out);

    uint64_t
    insert_input(const SupInput& tx_in);

    bool
    select_txs(const string& sup_address, vector<SupTransaction>& txs);

    bool
    select_txs(const uint64_t& account_id, vector<SupTransaction>& txs);

    bool
    select_txs_for_account_spendability_check(const uint64_t& account_id,
                                              vector<SupTransaction>& txs);

    bool
    select_output_with_id(const uint64_t& out_id, SupOutput& out);

    bool
    select_outputs(const uint64_t& account_id, vector<SupOutput>& outs);

    bool
    select_outputs_for_tx(const uint64_t& tx_id, vector<SupOutput>& outs);

    bool
    select_inputs(const uint64_t& account_id, vector<SupInput>& ins);

    bool
    select_inputs_for_tx(const uint64_t& tx_id, vector<SupInput>& ins);

    bool
    select_inputs_for_out(const uint64_t& output_id, vector<SupInput>& ins);

    bool
    output_exists(const string& output_public_key_str, SupOutput& out);

    bool
    tx_exists(const uint64_t& account_id, const string& tx_hash_str, SupTransaction& tx);

    uint64_t
    mark_tx_spendable(const uint64_t& tx_id_no);

    uint64_t
    delete_tx(const uint64_t& tx_id_no);

    uint64_t
    insert_payment(const SupPayment& payment);

    bool
    select_payment_by_id(const string& payment_id, vector<SupPayment>& payments);

    bool
    select_payment_by_address(const string& address, vector<SupPayment>& payments);

    bool
    select_payment_by_address(const string& address, SupPayment& payment);

    bool
    update_payment(SupPayment& payment_orginal, SupPayment& payment_new);

    uint64_t
    get_total_recieved(const uint64_t& account_id);

    bool
    update(SupAccount& acc_orginal, SupAccount& acc_new);

    void
    launch_mysql_pinging_thread();

    shared_ptr<MySqlConnector>
    get_connection();
};


}


#endif //RESTBED_SUP_MYSQLACCOUNTS_H
