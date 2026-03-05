#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>

struct SplitDetail {
    long long exec_qty = 0;
    long long exec_amount = 0;
    long long exec_price = 0;
    std::string exec_time;
    std::string market;
};

struct ExecutionRecord {
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

#endif
