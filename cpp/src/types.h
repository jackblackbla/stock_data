#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>

#include "qv_auth.h"

struct SplitDetail {
    long long exec_qty = 0;
    long long exec_amount = 0;
    long long exec_price = 0;
    std::string exec_time;
    std::string market;
};

struct ExecutionRecord {
    std::string account_no;
    std::string order_no;
    std::string orig_order_no;
    std::string order_type;
    std::string stock_code;
    std::string stock_name;
    long long order_qty = 0;
    long long exec_qty = 0;
    long long order_price = 0;
    long long exec_avg_price = 0;
    std::string exec_time;
    std::string market_code;
    std::string sor_split;
    std::vector<SplitDetail> split_details;
};

struct BalanceSummary {
    std::string account_no;
    long long deposit_amount = 0;
    long long withdrawable_amount = 0;
    long long orderable_amount = 0;
    long long cash_margin = 0;
    long long substitute_margin = 0;
    long long d1_deposit = 0;
    long long d2_deposit = 0;
    long long purchase_amount_total = 0;
    long long valuation_amount_total = 0;
    long long net_asset_amount = 0;
    long long total_profit_loss = 0;
    double profit_rate = 0.0;
    long long net_total_asset_amount = 0;
    std::string activity_type;
};

struct BalancePosition {
    std::string account_no;
    std::string stock_code;
    std::string stock_name;
    std::string balance_type;
    std::string loan_date;
    long long quantity = 0;
    long long unsettled_quantity = 0;
    long long avg_buy_price = 0;
    long long current_price = 0;
    long long profit_loss = 0;
    double profit_rate = 0.0;
    std::string credit_type;
    long long remaining_quantity = 0;
    std::string expiry_date;
    long long valuation_amount = 0;
    std::string issue_margin_rate;
    long long avg_sell_price = 0;
    long long sell_profit_loss = 0;
};

struct BalanceAccountResult {
    QVAccount selected_account;
    BalanceSummary summary;
    std::vector<BalancePosition> positions;
    std::vector<std::string> warnings;
};

#endif
