#include "stdafx.h"
#include "ParseURLUnit.h"
#include <algorithm>
#include <sstream>
#include <vector>
#include <set>
#include <iostream>
#include <malloc.h>

using namespace std;

set<char> g_invalidSymbols = { '!', '"', '#', '%', '&', '|', ' ', '{', '}', '^', '[', ']', '?', '>', '=', '<', ';', ':', ',', '*',
							 '(', ')', '\'', '/' };

bool CheckProtocolOnCorrect(const string &url, Protocol &resultProtocol, size_t &stringIndex, int &port)
{
	string protocol = url.substr(0, 5);
	
	std::transform(protocol.begin(), protocol.end(), protocol.begin(), tolower);

	if (protocol == "https")
	{
		stringIndex = 5;
		port = 443;
		resultProtocol = Protocol::HTTPS;
		return true;
	}

	protocol.erase(protocol.end() - 1, protocol.end());
	if (protocol == "http")
	{
		stringIndex = 4;
		port = 80;
		resultProtocol = Protocol::HTTP;
		return true;
	}

	protocol.erase(protocol.end() - 1, protocol.end());
	if (protocol == "ftp")
	{
		stringIndex = 3;
		port = 21;
		resultProtocol = Protocol::FTP;
		return true;
	}
	
	return false;
}

bool IsDividerFind(string const &url, size_t &stringIndex)
{
	string divider;
	for (size_t i = stringIndex; i < stringIndex + 3; ++i)
	{
		divider.push_back(url[i]);
	}

	if (divider == "://")
	{
		stringIndex += 3;
		return true;
	}

	return false;
}

bool CheckHostOnCorrect(const string &host)
{
	istringstream is(host);
	string s;
	vector<string> arrayStrings;
	while (getline(is, s, '.'))
	{
		arrayStrings.push_back(s);
	}

	for (size_t i = 0; i < arrayStrings.size(); ++i)
	{
		if (arrayStrings[i].size() != 0)
		{
			for (size_t j = 0; j < arrayStrings[i].size(); ++j)
			{
				if (find(g_invalidSymbols.begin(), g_invalidSymbols.end(), arrayStrings[i][j]) == g_invalidSymbols.end())
				{
					continue;
				}
				return false;
			}
		}

		if (arrayStrings[i].size() == 0)
		{
			return false;
		}
	}
	
	if (arrayStrings.size() == 0)
	{
		return false;
	}
	return true;
}

bool CheckPortOnCorrect(const string &url, int &port, size_t &index)
{
	string subPort;
	for (int j = 1; j < 7; ++j)
	{
		if (isdigit(url[index + j]))
		{
			subPort.push_back(url[index + j]);
			continue;
		}

		if (subPort.size() == 0)
		{
			return false;
		}
		else
		{
			char *temp = new char[subPort.length()];
			for (unsigned int k = 0; k < subPort.length(); ++k)
			{
				temp[k] = subPort[k];
			}

			port = atoi(temp);

			if ((port > 65535) | (port < 1))
			{
				delete[] temp;
				return false;
			}

			delete[] temp;
			index += j + 1;
			return true;
		}
	}
}

bool IsHostFounded(const string &url, string &host, size_t &stringIndex, int &port)
{
	for (size_t i = stringIndex; i < url.size(); ++i)
	{
		if (url[i] == '/')
		{
			if (!CheckHostOnCorrect(host))
			{
				break;
			}
			stringIndex = i + 1;
			return true;
		}
		if (url[i] == ':')
		{
			if (!CheckHostOnCorrect(host))
			{
				break;
			}

			if (!CheckPortOnCorrect(url, port, i))
			{
				break;
			}
			stringIndex = i;
			return true;
		}
		host.push_back(url[i]);
	}
	return false;
}

bool ParseURL(string const &url, Protocol &protocol, int &port, string &host, string &document)
{
	if (url.size() == 0)
	{
		return false;
	}

	size_t stringIndex = 0;

	if (!CheckProtocolOnCorrect(url, protocol, stringIndex, port))
	{
		return false;
	}

	if (!IsDividerFind(url, stringIndex))
	{
		return false;
	}

	if (!IsHostFounded(url, host, stringIndex, port))
	{
		return false;
	}

	document = url.substr(stringIndex, url.size());

	return true;
}