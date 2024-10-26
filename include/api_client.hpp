#ifndef API_CLIENT_HPP
#define API_CLIENT_HPP

#include <string>

class APIClient {
public:
    APIClient(const std::string& client_id, const std::string& client_secret);

    void authenticate();
    std::string makeRequest(const std::string& url, const std::string& payload);
    void place_buy_Order(const std::string& instrument_name, double amount,double price);
    void place_sell_Order(const std::string& instrument_name, double amount,double price,double trigger_price);
    void edit_Order(const std::string& order_id, double amount,double price);
    void cancel_Order(const std::string& order_id);
    void get_order_book(const std::string& instrument_name);

private:
    std::string client_id_;
    std::string client_secret_;
    std::string access_token_;
    
};

#endif // API_CLIENT_HPP
