// ParseURLTest.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../ParseURL/ParseURLUnit.h"

Protocol g_protocol = HTTP;
Protocol g_protocol1 = HTTPS;
Protocol g_protocol2 = FTP;

bool TestInvalidURL(const std::string &url)
{
	Protocol protocol;
	std::string host, doc;
	int port;
	return ParseURL(url, protocol, port, host, doc);
}

bool TestValidURL(const std::string &url, Protocol &protocol, const int port, const std::string &host, const std::string &document)
{
	Protocol newProtocol;
	std::string newHost, newDocument;
	int newPort;

	if (!ParseURL(url, newProtocol, newPort, newHost, newDocument))
	{
		return false;
	}
	return ((newProtocol == protocol) && (newHost == host) && (newPort == port) && (newDocument == document));
}

BOOST_AUTO_TEST_CASE(EmptyURL)
{
	BOOST_CHECK(!TestInvalidURL(""));
}

BOOST_AUTO_TEST_CASE(CheckProtocols)
{
	std::string host, doc;
	Protocol protocol;
	int port;
	BOOST_CHECK(!ParseURL("hTtp://www.youtube.com", protocol, port, host, doc));
	BOOST_CHECK_EQUAL(protocol, g_protocol);
	BOOST_CHECK(!ParseURL("HttpS://www.youtube.com", protocol, port, host, doc));
	BOOST_CHECK_EQUAL(protocol, g_protocol1);
	BOOST_CHECK(!ParseURL("FTp://www.youtube.com", protocol, port, host, doc));
	BOOST_CHECK_EQUAL(protocol, g_protocol2);
}

BOOST_AUTO_TEST_CASE(NoDelimiter)
{
	BOOST_CHECK(!TestInvalidURL("http:/:/www.youtube.com"));
}

BOOST_AUTO_TEST_CASE(NoProtocol)
{
	BOOST_CHECK(!TestInvalidURL("://host:1995/doc"));
}

BOOST_AUTO_TEST_CASE(NoAddress)
{
	BOOST_CHECK(!TestInvalidURL("ftp://"));
}

BOOST_AUTO_TEST_CASE(UnknownProtocol)
{
	BOOST_CHECK(!TestInvalidURL("margtu://moodle/volgatech"));
}

BOOST_AUTO_TEST_CASE(HostFormatError)
{
	BOOST_CHECK(!TestInvalidURL("http:///host/doc"));
	BOOST_CHECK(!TestInvalidURL("http://:host/doc"));
} 

BOOST_AUTO_TEST_CASE(NoPortInUrl)
{
	BOOST_CHECK(!TestInvalidURL("http://host:/doc"));
}

BOOST_AUTO_TEST_CASE(InvalidPorts)
{
	BOOST_CHECK(!TestInvalidURL("http://host:-1/doc"));
	BOOST_CHECK(!TestInvalidURL("http://host:port/doc"));
	BOOST_CHECK(!TestInvalidURL("http://host:65536/doc"));
}

BOOST_AUTO_TEST_CASE(TestURL_1)
{
	Protocol protocol = Protocol::HTTPS;
	BOOST_CHECK(TestValidURL("HttPS://www.youtube.com/channel", protocol, 443, "www.youtube.com", "channel"));
}

BOOST_AUTO_TEST_CASE(TestURL_2)
{
	Protocol protocol = Protocol::HTTP;
	BOOST_CHECK(TestValidURL("HttP://mail/doc:1995", protocol, 80, "mail", "doc:1995"));
}

BOOST_AUTO_TEST_CASE(TestURL_3)
{
	Protocol protocol = Protocol::FTP;
	BOOST_CHECK(TestValidURL("ftp://mail:1995/doc1747read_and_translate", protocol, 1995, "mail", "doc1747read_and_translate"));
}

BOOST_AUTO_TEST_CASE(WithoutDocument)
{
	Protocol protocol = Protocol::HTTPS;
	BOOST_CHECK(TestValidURL("https://mail.ru/", protocol, 443, "mail.ru", ""));
}