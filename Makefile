all: TcpServers

TcpDuplicationsServer:
	make -C QTcpServer/DuplicationsServer all

TcpPalindromesServer:
	make -C QTcpServer/PalindromesServer all

TcpServers: TcpDuplicationsServer TcpPalindromesServer

uninstall:
	make -C QTcpServer/DuplicationsServer uninstall
	make -C QTcpServer/PalindromesServer uninstall
	