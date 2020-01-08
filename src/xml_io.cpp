#include "xml_io.h"

#include <sstream>
#include <iostream>
#include "section.h"

// ----------------------------------------------------------------------
// STDOUT dump and indenting utility functions
// ----------------------------------------------------------------------
const unsigned int NUM_INDENTS_PER_SPACE=2;

xml_io::xml_io(void)
{
}


xml_io::~xml_io(void)
{
}


std::string GetA3StorageFileName (std::string BaseFileName)
{
	return (BaseFileName + std::string(".xml"));
} // GetA3StorageFileName

void WriteA3XmlData(TiXmlElement* root, const std::string& ElementName, const std::vector<std::shared_ptr<value_pair>>& ObjectValuePairs)
{
	TiXmlElement* msg;
	msg = new TiXmlElement( ElementName.c_str() ); 
	root->LinkEndChild( msg );
	for(std::vector<std::shared_ptr<value_pair>>::const_iterator Iterator = ObjectValuePairs.begin();
		Iterator != ObjectValuePairs.end(); ++Iterator)
	{
//std::cout << "  @@ TAG: " << (*Iterator)->Tag << ", VAL: " << (*Iterator)->Value << std::endl;

		msg->SetAttribute(((*Iterator)->Tag).c_str(), ((*Iterator)->Value).c_str());
	}

} // WriteA3XmlData

void ReadA3XmlData(TiXmlElement* root, std::vector<std::shared_ptr<value_pair>>& ObjectValuePairs)
{
	TiXmlAttribute* pAttrib=root->FirstAttribute();
	while (pAttrib)
	{
		ObjectValuePairs.push_back(std::shared_ptr<value_pair> (new value_pair(pAttrib->Name(), pAttrib->Value())));
		pAttrib=pAttrib->Next();
	}
} // ReadA3XmlData
