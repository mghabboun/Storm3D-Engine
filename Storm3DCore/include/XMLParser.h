#ifndef XML_PARSER
#define XML_PARSER

#include <tinyxml2/tinyxml2.h>
#include <string> 
#include <vector>

class XMLParser
{
public:
    
			XMLParser(){}
			~XMLParser(){}

    bool	LoadFile( const char* filename );
    void	ReadAttribute();
	
	void	ReadRootTag(const char* tag, const char* attrib, std::string &value, std::string &attribute);

    void	ReadTag(const char* tag, const char* attrib, std::string &value, std::string &attribute);
	void	ReadTag(const char* tag, const char* attrib, std::string &value, std::vector< std::string > &attribute);

	void	ReadTagText(const char* tag, std::string &text);

  
private:

    tinyxml2::XMLDocument m_doc;
    
    //std::vector <std::string> 
};

#endif