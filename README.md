# Console client-server application

The project is developed in C++ programming language using QT library for implementation of the client-server interaction.


## Modules

- Logic module that is executed on the server side.
> Server can process clients messages either by deleting duplicative symbols or counting number of palindromes.
- Servers 
> That use Tcp or Udp sockets for interaction with the client.
- Clients
> As well, sending Tcp or Udp sockets to the server.

## How to use it?

1. Compile server application and execute it using flag -p (port number that will be assigned to the server), otherwise server port will be by 9999 by default.
2. Compile client application and execute it with command line arguments: IP and port of the server that you need to connect to. Or use existing utilities such as nc or telnet from the client side.
3. Write a message in terminal that will be processed by the server and get an answer!
