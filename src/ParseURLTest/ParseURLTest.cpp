// ParseURLTest.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../ParseURL/ParseURLUnit.h"

bool InvalidURL(const std::string &url)
{
	std::string host, doc, protocol;
	int port;
	return (ParseURL(url, protocol, port, host, doc));
}


BOOST_AUTO_TEST_CASE(EmptyURL)
{
	BOOST_CHECK(!InvalidURL(""));
}