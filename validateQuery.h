#pragma once
#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<cctype>
class validateQuery
{
public:
	bool validate(std::vector<std::string> v1);
	std::pair<std::string, std::vector<std::pair<std::string, std::string>>> query;
	std::pair<std::string, std::vector<std::pair<std::string, std::string>>> insertQuery;
};

