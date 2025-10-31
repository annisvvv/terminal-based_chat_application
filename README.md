## Building the Project

You will need a C compiler (like `gcc`) to build the executables.

1.  **Compile the standalone server:**
    ```bash
    gcc server.c -o server
    ```

2.  **Compile the standalone client:**
    ```bash
    gcc client.c -o client
    ```

3.  **Compile the combined client/server role application:**
    ```bash
    gcc client-server_role.c -o chat_role
    ```

## Running the Applications

### Running the Standalone Server

On the machine designated as the server:

1.  Execute the compiled server program:
    ```bash
    ./server
    ```
    The server will start listening on port `8080` and wait for a client to connect.

2.  **To find the server's IP address** (needed for the client to connect), open a new terminal on the server machine and run:
    ```bash
    hostname -I
    ```
    Note down the appropriate IP address (e.g., `192.168.x.x` or your public IP if connecting over the internet).

### Running the Standalone Client

On the machine designated as the client:

1.  Execute the compiled client program, providing the server's IP address as an argument:
    ```bash
    ./client <SERVER_IP_ADDRESS>
    ```
    Replace `<SERVER_IP_ADDRESS>` with the actual IP address of the server (e.g., `./client 192.168.1.10`).
    If no IP address is provided, it defaults to `127.0.0.1` (localhost).

### Running the Combined Client/Server Role

On either machine:

1.  Execute the compiled program:
    ```bash
    ./chat_role
    ```

2.  The program will prompt you: `do you want to listen oor connect (1/2) :`
    *   **To act as a server:** Enter `1`. The application will then listen for incoming connections.
    *   **To act as a client:** Enter `2`. The application will then prompt you to `Enter the server IP address:`. Provide the IP address of the machine running the server role.

Once connected, you can type messages in your terminal, and they will be sent to the other party. Type `exit` to end the conversation.
