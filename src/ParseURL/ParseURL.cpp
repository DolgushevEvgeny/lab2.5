// ParseURL.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include "ParseURLUnit.h"

using namespace std;

int main(int argc, char* argv[])
{
	string curUrl;
	while (getline(cin, curUrl))
	{
		string protocol;
		int port;
		string host;
		string document;

		if (ParseURL(curUrl, protocol, port, host, document))
		{
			cout << curUrl << endl;
			cout << "HOST: " << host << endl;
			cout << "PORT: " << port << endl;
			cout << "DOC: " << document << endl;
		}
	}

	return 0;
}

