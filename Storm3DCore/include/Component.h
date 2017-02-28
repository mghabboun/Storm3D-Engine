#ifndef STORM_3D_ENTITY_H
#define STORM_3D_ENTITY_H

#include "RefCounter.h"

#include <string>

class Component : public RefCounter 
{
    Component(){}


    std::string m_name; 
};


#endif
