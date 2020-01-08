#include "value_pair.h"
#include "a3_ui_text.h"
#include <sstream>

value_pair::value_pair(std::string Tag, std::string Value)
{
	this->Tag = Tag;
	this->Value = Value;
}

value_pair::~value_pair(void)
{
}

std::string value_pair::GetValuePairString()
{
	std::stringstream Text;
	Text << "(" << this->Tag << ", " << this->Value << ")";
	return (Text.str());
} // PrintValuePair

void PrintValuePairs (std::vector<std::shared_ptr<value_pair>> ObjectValuePairs)
{
	std::vector<std::shared_ptr<value_pair>>::iterator ValuePairIterator;
	std::stringstream Text;
	for(ValuePairIterator = ObjectValuePairs.begin(); ValuePairIterator != ObjectValuePairs.end(); ++ValuePairIterator)
	{
		Text << (*ValuePairIterator)->GetValuePairString() << ", ";
	}
	showTextMsg(Text.str());
} // PrintValuePairs
