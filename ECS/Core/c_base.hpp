#pragma once
#include "../ecs_types.hpp"
#include <sstream>
#include <SFML/Graphics.hpp>

class C_Base
{
    public:
        C_Base(const Component& l_type);
        virtual ~C_Base();

        Component GetType(){ return m_type;}

        friend std::stringstream& operator >> (std::stringstream& l_stream,C_Base& b)
        {
            b.ReadIn(l_stream);
            return l_stream;
        }

        virtual void ReadIn(std::stringstream& l_stream) = 0;
    private:
        Component m_type;
};