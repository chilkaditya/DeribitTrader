#include "api_client.hpp"
#include <iostream>
#include <string>
// #include <bits/stdc++.h>



int main() {
    std::string client_id = "Ye64q9Rj";
    std::string client_secret = "nBzkI65mUuJ7QulxB1JwTEkBXtZQc8dRTUKJK1aUy_g";
    APIClient api_client(client_id, client_secret);
    try {
        APIClient api_client(client_id, client_secret);
        
        // Authenticate to get access token
        api_client.authenticate();
        
        // Specify instrument name
        std::string instrument_name = "BTC-PERPETUAL";
        
        // View current position
        api_client.view_position(instrument_name);

        // Other operations (optional)
        double amount = 10.0;
        double price = 30000.0;
        // api_client.place_buy_order(instrument_name, amount, price);
        // api_client.place_sell_order(instrument_name, amount, price);

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
