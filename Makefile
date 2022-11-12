all: TcpServers clients

TcpServers: TcpDuplicationsServer TcpPalindromesServer

UdpServers: UdpDuplicationsServer UdpPalindromesServer


TcpDuplicationsServer:
	make -C QTcpServer/DuplicationsServer all

TcpPalindromesServer:
	make -C QTcpServer/PalindromesServer all

UdpDuplicationsServer:
	make -C QUdpServer/DuplicationsServer all

UdpPalindromesServer:
	make -C QUdpServer/PalindromesServer all

clients:
	make -C QTcpClient all
	make -C QUdpClient all

uninstall:
	make -C QTcpServer/DuplicationsServer uninstall
	make -C QTcpServer/PalindromesServer uninstall
	make -C QUdpServer/DuplicationsServer uninstall
	make -C QUdpServer/PalindromesServer uninstall
	make -C QTcpClient uninstall
	make -C QUdpClient uninstall
	