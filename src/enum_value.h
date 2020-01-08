#pragma once

#include <memory>
#include <functional>

class enum_value
{
public:
	int		EnumPos;
	int		EnumVal;
	bool	ValueSet;

	enum_value::enum_value(int, int);
	~enum_value(void);

	void construct ();
};

typedef enum
{
	ENUM_VALUE_SIDE_UNKNOWN,
	ENUM_VALUE_SIDE_LEFT,
	ENUM_VALUE_SIDE_RIGHT,
	ENUM_VALUE_SIDE_BOTH,
	NO_OF_ENUM_VALUE_SIDE_TYPES
} ENUM_VALUE_SIDE_TYPE;

#define ENUM_VAL_DEFAULT_POS 0
#define ENUM_VAL_DEFAULT_VAL 0

#define ENUM_NULL_VALUE_STRING "0"

// Operator < overload for sorting
bool operator< (const std::shared_ptr<enum_value> EnumVal1, const std::shared_ptr<enum_value> EnumVal2);
