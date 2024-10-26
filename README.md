# Deribit Trading API Client

This project implements a C++ client for interacting with the Deribit trading platform's API. It enables users to authenticate with the API, retrieve the order book, and place buy/sell orders on the Deribit test network using JSON-RPC over HTTP.


## Features

- **Authentication**: OAuth 2.0 authentication to obtain an access token using `client_id` and `client_secret`.
- **Public API**: Fetches order book details for a specified instrument.
- **Private API**: Places buy and sell orders.

## Dependencies

This project uses the following libraries:

- `libcurl`: For handling HTTP requests.
- `nlohmann/json`: For JSON parsing.

**Note**: You can install these dependencies via `vcpkg` (a C++ package manager) or your preferred method.

### Installing Dependencies with vcpkg

1. Install `vcpkg` following the instructions on [vcpkg GitHub](https://github.com/microsoft/vcpkg).
2. Install dependencies:

   ```bash
   vcpkg install curl
   vcpkg install nlohmann-json


