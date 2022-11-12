all: TcpServers clients

TcpDuplicationsServer:
	make -C QTcpServer/DuplicationsServer all

TcpPalindromesServer:
	make -C QTcpServer/PalindromesServer all

TcpServers: TcpDuplicationsServer TcpPalindromesServer

clients:
	make -C QTcpClient all

uninstall:
	make -C QTcpServer/DuplicationsServer uninstall
	make -C QTcpServer/PalindromesServer uninstall
	make -C QTcpClient uninstall
	