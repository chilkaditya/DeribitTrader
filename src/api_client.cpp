#include "api_client.hpp"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>

// std::cout << "reached" << std::endl;
APIClient::APIClient(const std::string& client_id, const std::string& client_secret) 
    : client_id_(client_id), client_secret_(client_secret),access_token_("") {
        // std::cout << "reached" << std::endl;
    }

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    s->append((char*)contents, newLength);
    return newLength;
}

std::string APIClient::makeRequest(const std::string& url, const std::string& payload) {
    // std::cout << "reached" << std::endl;
    CURL* curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return response;
}

void APIClient::authenticate() {
    std::string url = "https://test.deribit.com/api/v2/public/auth";
    nlohmann::json payload = {
        {"jsonrpc", "2.0"},
        {"id", 1},
        {"method", "public/auth"},
        {"params", {
            {"grant_type", "client_credentials"},
            {"client_id", client_id_},
            {"client_secret", client_secret_}
        }}
    };

    std::string response = makeRequest(url, payload.dump());
    nlohmann::json json_response = nlohmann::json::parse(response);

    if (json_response.contains("result") && json_response["result"].contains("access_token")) {
        access_token_ = json_response["result"]["access_token"];
        // return access_token_;
    } else {
        throw std::runtime_error("Failed to authenticate");
    }
}

void APIClient::place_buy_Order(const std::string& instrument_name, double amount,double price) {
    std::string url = "https://test.deribit.com/api/v2/private/buy";
    
    // Create JSON payload
    nlohmann::json payload = {
        {"jsonrpc", "2.0"},
        {"id", 3},
        {"method", "private/buy"},
        {"params", {
            {"instrument_name", instrument_name},
            {"amount", amount},
            {"price", price},
            {"type", "limit"}, // You can also use "market"
            {"access_token", access_token_}
        }}
    };

    // Send request and parse response
    std::string response = makeRequest(url, payload.dump());
    nlohmann::json json_response = nlohmann::json::parse(response);

    // Handle the response
    std::cout << "Buy Order Response: " << json_response.dump(4) << std::endl;
}

void APIClient::place_sell_Order(const std::string& instrument_name, double amount,double price,double trigger_price) {
    std::string url = "https://test.deribit.com/api/v2/private/sell";
    
    // Create JSON payload
    nlohmann::json payload = {
        {"jsonrpc", "2.0"},
        {"id", 3},
        {"method", "private/sell"},
        {"params", {
            {"instrument_name", instrument_name},
            {"amount", amount},
            {"price", price},
            {"trigger_price", trigger_price},
            {"type", "stop_limit"}, // You can also use "market"
            {"trigger", "last_price"},
            {"access_token", access_token_}
        }}
    };

    // Send request and parse response
    std::string response = makeRequest(url, payload.dump());
    nlohmann::json json_response = nlohmann::json::parse(response);

    // Handle the response
    std::cout << "Buy Order Response: " << json_response.dump(4) << std::endl;
}

void APIClient::edit_Order(const std::string& order_id, double amount,double price) {
    std::string url = "https://test.deribit.com/api/v2/private/edit";
    
    // Create JSON payload
    nlohmann::json payload = {
        {"jsonrpc", "2.0"},
        {"id", 3},
        {"method", "private/edit"},
        {"params", {
            {"order_id", order_id},
            {"amount", amount},
            {"price", price},
            {"advanced", "implv"},
            {"access_token", access_token_}
        }}
    };

    // Send request and parse response
    std::string response = makeRequest(url, payload.dump());
    nlohmann::json json_response = nlohmann::json::parse(response);

    // Handle the response
    std::cout << "Buy Order Response: " << json_response.dump(4) << std::endl;
}

void APIClient::cancel_Order(const std::string& order_id) {
    std::string url = "https://test.deribit.com/api/v2/private/cancel";
    
    // Create JSON payload
    nlohmann::json payload = {
        {"jsonrpc", "2.0"},
        {"id", 3},
        {"method", "private/cancel"},
        {"params", {
            {"order_id", order_id},
            {"access_token", access_token_}
        }}
    };

    // Send request and parse response
    std::string response = makeRequest(url, payload.dump());
    nlohmann::json json_response = nlohmann::json::parse(response);

    // Handle the response
    std::cout << "Buy Order Response: " << json_response.dump(4) << std::endl;
}

void APIClient::get_order_book(const std::string& instrument_name) {
    std::string url = "https://test.deribit.com/api/v2/public/get_order_book";

    // Create JSON payload
    nlohmann::json payload = {
        {"jsonrpc", "2.0"},
        {"id", 5},
        {"method", "public/get_order_book"},
        {"params", {
            {"instrument_name", instrument_name},
            {"depth", 5}
        }}
    };

    // Send the HTTP POST request
    std::string response = makeRequest(url, payload.dump());
    nlohmann::json json_response = nlohmann::json::parse(response);

    // Check if the response contains the result
    if (json_response.contains("result")) {
        // Print the result in a formatted way
        std::cout << "Order Book for " << instrument_name << ": " << json_response["result"].dump(4) << std::endl;
    } else {
        std::cerr << "Failed to retrieve order book data." << std::endl;
    }
}

void APIClient::view_position(const std::string &instrument_name) {
    std::string url = "https://test.deribit.com/api/v2/private/get_position";
    nlohmann::json payload = {
        {"jsonrpc", "2.0"},
        {"id", 6},
        {"method", "private/get_position"},
        {"params", {
            {"instrument_name", instrument_name},
            {"access_token", access_token_}
        }}
    };

    std::string response = makeRequest(url, payload.dump());
    nlohmann::json json_response = nlohmann::json::parse(response);

    if (json_response.contains("result")) {
        std::cout << "Current Position for " << instrument_name << ": " << json_response["result"].dump(4) << std::endl;
    } else {
        std::cerr << "Failed to retrieve current position data." << std::endl;
    }
}
