#include "api_client.hpp"
#include <iostream>
#include <string>
// #include <bits/stdc++.h>



int main() {
    std::string client_id = "Ye64q9Rj";
    std::string client_secret = "nBzkI65mUuJ7QulxB1JwTEkBXtZQc8dRTUKJK1aUy_g";
    APIClient api_client(client_id, client_secret);
    try {
        api_client.authenticate();
        // std::cout << "Access Token: " << access_token_ << std::endl;
        
        // Make further private API calls
        // get_account_summary(access_token);
        api_client.place_buy_Order("ETH-PERPETUAL",40,10);

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    
    try {
        // Define the instrument name for which to fetch the order book
        std::string instrument_name = "BTC-PERPETUAL"; // Change this as needed

        // Get and display the order book
        api_client.get_order_book(instrument_name);

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}