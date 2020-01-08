#include "enum_value.h"

enum_value::enum_value(int EnumPos, int EnumVal)
{
	this->construct();
	this->EnumPos = EnumPos;
	this->EnumVal = EnumVal;
}

enum_value::~enum_value(void)
{
}

void enum_value::construct ()
{
	this->ValueSet = false;
} // construct


bool operator< (const std::shared_ptr<enum_value> EnumVal1, const std::shared_ptr<enum_value> EnumVal2)
{
	return (EnumVal1->EnumVal < EnumVal2->EnumVal);
}