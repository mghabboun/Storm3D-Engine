

#include "Storm3DCore/include/XMLParser.h"

#include <string>

using namespace tinyxml2;
//--------------------------------------
void XMLParser::ReadTag(const char* tag, const char* attrib, std::string &value, std::string &attribute)
{
    int stop =0;
    XMLElement *pRoot = m_doc.RootElement();
   
    XMLElement *element = pRoot->FirstChildElement();
    while( element )
    {
      value = element->Value(); // In your example xml file this gives you ToDo
	  if (value.compare( tag ) == 0 )
      {
        const char* att = element->Attribute( attrib ); //Gets you the attribute variable
        if ( att )
           attribute = att; 

        break;
      } 

      element = element->NextSiblingElement();
    }
}


//--------------------------------------
void XMLParser::ReadTag(const char* tag, const char* attrib, std::string &value, std::vector< std::string > &attribute)
{
    int stop =0;
    XMLElement *pRoot = m_doc.RootElement();
   
    XMLElement *element = pRoot->FirstChildElement();
    while( element )
    {
      value = element->Value(); // In your example xml file this gives you ToDo
	  if (value.compare( tag ) == 0 )
      {
        const char* att = element->Attribute( attrib ); //Gets you the attribute variable
        if ( att )
		{ 
			attribute.push_back(att);
		}
      } 

      element = element->NextSiblingElement();
    }
}

//--------------------------------------
void XMLParser::ReadRootTag(const char* tag, const char* attrib, std::string &value, std::string &attribute)
{
	XMLElement *pRoot = m_doc.RootElement();
	if ( pRoot ) 
	{
		value = pRoot->Value(); // In your example xml file this gives you ToDo
		if (value.compare( tag ) == 0 )
		{
			const char* att = pRoot->Attribute( attrib ); //Gets you the attribute variable
			if ( att )
				attribute = att;
		} 
	}
}


//--------------------------------------
void XMLParser::ReadTagText(const char* tag, std::string &text)
{
    int stop =0;
    XMLElement *pRoot = m_doc.RootElement();
   
    XMLElement *element = pRoot->FirstChildElement();
    while( element )
    {
      const char* value = element->Value(); // In your example xml file this gives you ToDo
      if (strcmp(value, tag) == 0 )
	  {
		  const char* att = element->GetText();
		  text = att;
		  break;
	  } 

      element = element->NextSiblingElement();
    }
}

//--------------------------------------
void XMLParser::ReadAttribute()
{

}


//--------------------------------------
bool XMLParser::LoadFile( const char* filename )
{
   if (m_doc.LoadFile( filename ) == 0)
   {
	   return true;
   }

   return false;
}