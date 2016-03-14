#pragma once
#include <Windows.h>
#include <winsock2.h>
#include <iostream>
#include <string>
// Don't forget to add ws2_32.lib to linker's configure!

class WinLocalAddressGrabber {
private:
	char name[256];
	WSADATA wsad;
	struct hostent *hs;
	struct in_addr addr;

public:
	WinLocalAddressGrabber() {
		int err;

		err = WSAStartup(MAKEWORD(2, 0), &wsad);
		if (err != 0) {
			switch (err) {
			case WSASYSNOTREADY:
				std::cout << "WSASYSNOTREADY\n";
				break;
			case WSAVERNOTSUPPORTED:
				std::cout << "WSAVERNOTSUPPORTED\n";
				break;
			case WSAEINPROGRESS:
				std::cout << "WSAEINPROGRESS\n";
				break;
			case WSAEPROCLIM:
				std::cout << "WSAEPROCLIM\n";
				break;
			case WSAEFAULT:
				std::cout << "WSAEFAULT\n";
				break;
			}
		}
	}

	string getIpAddress() {	
		gethostname(name, sizeof(name));
		hs = gethostbyname(name);
		addr.S_un.S_addr = *(u_long*)hs->h_addr_list[0];
		return inet_ntoa(addr);
	}
};