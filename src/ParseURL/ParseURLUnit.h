#pragma once

#include "stdafx.h"

enum Protocol
{
	HTTP,
	HTTPS,
	FTP
};

bool ParseURL(std::string const &url, Protocol &protocol, int &port, std::string &host, std::string &document);
bool CheckProtocolOnCorrect(const std::string &url, Protocol &protocol, size_t &stringIndex);
bool IsHostFounded(const std::string &url, std::string &host, size_t &stringIndex, int &port);
bool CheckPortOnCorrect(const std::string &url, int &port, size_t &index);
bool CheckHostOnCorrect(const std::string &host);
bool IsDividerFind(std::string const &url, size_t &stringIndex);