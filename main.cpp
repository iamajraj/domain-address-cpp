#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "wsock32.dll")

using namespace std;

int main()
{
  WSADATA wsaData;
  int result_i;
  int dwError;
  in_addr addr;

  result_i = WSAStartup(MAKEWORD(2, 2), &wsaData);

  if (result_i != 0)
  {
    cout << "Failed" << endl;
    return 1;
  }

  char hostname[] = "google.com";
  char **pAlias;
  hostent *host = gethostbyname(hostname);
  if (host == NULL)
  {
    dwError = WSAGetLastError();
    if (dwError != 0)
    {
      if (dwError == WSAHOST_NOT_FOUND)
      {
        printf("Host not found\n");
        return 1;
      }
      else if (dwError == WSANO_DATA)
      {
        printf("No data record found\n");
        return 1;
      }
      else
      {
        printf("Function failed with error: %ld\n", dwError);
        return 1;
      }
    }
  }
  else
  {
    cout << host->h_name << endl;
    for (pAlias = host->h_aliases; *pAlias != 0; pAlias++)
    {
      cout << "Alternate Address: " << *pAlias << endl;
    }

    switch (host->h_addrtype)
    {
    case AF_INET:
      cout << "IPV4 Address" << endl;
      break;
    case AF_NETBIOS:
      printf("AF_NETBIOS\n");
      break;
    default:
      printf(" %d\n", host->h_addrtype);
      break;
    }

    int i = 0;
    if (host->h_addrtype == AF_INET)
    {
      while (host->h_addr_list[i] != 0)
      {
        addr.s_addr = *(u_long *)host->h_addr_list[i++];
        cout << "IP Address: " << inet_ntoa(addr) << endl;
      }
    }
  }

  return 0;
}