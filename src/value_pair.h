#pragma once

#include <string>
#include <vector>
#include <memory>

class value_pair
{
public:
	value_pair(std::string Tag, std::string Value);
	~value_pair(void);
	std::string GetValuePairString();

	std::string	Tag;
	std::string Value;
};

void PrintValuePairs (std::vector<std::shared_ptr<value_pair>>);
