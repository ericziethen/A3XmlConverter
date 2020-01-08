#pragma once

#include "enum_value.h"
#include "misc_lib.h"

#include <sstream>
#include <vector>
#include <iterator>

#define WARNING_CODE_BOOST_BIMAP 4512

// disable bitmap warning
#pragma warning(disable:WARNING_CODE_BOOST_BIMAP)
#include "boost/bimap.hpp"
#include "boost/bimap/unordered_set_of.hpp"


typedef boost::bimap<boost::bimaps::unordered_set_of<int>,boost::bimaps::unordered_set_of<std::string>> INT_STRING_HASHBIMAP_TYPE;
typedef boost::bimap<boost::bimaps::unordered_set_of<int>,boost::bimaps::unordered_set_of<int>> INT_HASHBIMAP_TYPE;


//typedef boost::bimap<int,int> INT_BIMAP_TYPE;
//typedef boost::bimap<int,std::string> INT_STRING_BIMAP_TYPE;

typedef std::function<int(int, ENUM_VALUE_SIDE_TYPE, int)> ENUM_MAP_LOOKUP_FUNC;

template <typename LEFT_TYPE, typename RIGHT_TYPE> void T_InserBimapValue (
	const LEFT_TYPE& LeftValue, const RIGHT_TYPE& RightValue, 
	boost::bimap<boost::bimaps::unordered_set_of<LEFT_TYPE>, boost::bimaps::unordered_set_of<RIGHT_TYPE>>& Bimap)
{
	Bimap.insert (boost::bimap<LEFT_TYPE, RIGHT_TYPE>::value_type(LeftValue, RightValue));
} // T_InserBimapValue

template <typename LEFT_TYPE, typename RIGHT_TYPE> LEFT_TYPE T_GetLeftBimapValue (const RIGHT_TYPE& LookupIndex, 
	const boost::bimap<boost::bimaps::unordered_set_of<LEFT_TYPE>, boost::bimaps::unordered_set_of<RIGHT_TYPE>>& Bimap)
{
	LEFT_TYPE LeftVal;

	try
	{
		LeftVal = Bimap.right.find(LookupIndex)->second;
	}
	catch( std::out_of_range & e ) 
	{
		std::stringstream ErrorText;
		ErrorText << "No Value found for index \"" << LookupIndex << "\" (" << e.what() << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

	return (LeftVal);
} // T_GetLeftBimapValue

template <typename LEFT_TYPE, typename RIGHT_TYPE> RIGHT_TYPE T_GetRightBimapValue (const LEFT_TYPE& LookupIndex, 
			const boost::bimap<boost::bimaps::unordered_set_of<LEFT_TYPE>, boost::bimaps::unordered_set_of<RIGHT_TYPE>>& Bimap)
{
	RIGHT_TYPE RightVal;

	try
	{
		RightVal = Bimap.left.find(LookupIndex)->second;
	}
	catch( std::out_of_range & e ) 
	{
		std::stringstream ErrorText;
		ErrorText << "No Value found for index \"" << LookupIndex << "\" (" << e.what() << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

	return (RightVal);
} // T_GetRightBimapValue

template <typename BIMAP_TYPE> BIMAP_TYPE T_GetBimapValue (
	const ENUM_VALUE_SIDE_TYPE& LookupSide, const BIMAP_TYPE& LookupIndex, 
	const boost::bimap<boost::bimaps::unordered_set_of<BIMAP_TYPE>, boost::bimaps::unordered_set_of<BIMAP_TYPE>>& Bimap)
{
	BIMAP_TYPE Type = -1;

	try
	{
		switch (LookupSide)
		{
		case ENUM_VALUE_SIDE_LEFT:
			Type = Bimap.left.find(LookupIndex)->second;
			break;

		case ENUM_VALUE_SIDE_RIGHT:
			Type = Bimap.right.find(LookupIndex)->second;
			break;

		default:
			std::stringstream ErrorText;
			ErrorText << "Unexpected Side Type Value \"" << LookupSide << "\" -> " <<__FUNCTION__;
			programError (ErrorText.str());
			break;
		} // switch return side type
	}
	catch( std::out_of_range & e ) 
	{
		std::stringstream ErrorText;
		ErrorText << "No Value found for index \"" << LookupIndex << "\" (" << e.what() << ") -> " <<__FUNCTION__;
		programError (ErrorText.str());
	}

	return (Type);
} // T_GetBimapValue

template <typename BIMAP_TYPE> void T_GetAllBimapValues (
	const boost::bimap<boost::bimaps::unordered_set_of<BIMAP_TYPE>, boost::bimaps::unordered_set_of<BIMAP_TYPE>>& Bimap, ENUM_VALUE_LIST& ValueList)
{
	boost::bimap<boost::bimaps::unordered_set_of<BIMAP_TYPE>, boost::bimaps::unordered_set_of<BIMAP_TYPE>>::const_iterator BimapIterator;
	for (BimapIterator = Bimap.begin(); BimapIterator != Bimap.end(); ++BimapIterator)
	{
		ValueList.push_back(std::shared_ptr<enum_value> (new enum_value(BimapIterator->left, BimapIterator->right)));
	} // for each item in the bimap
} // T_GetAllBimapValues
