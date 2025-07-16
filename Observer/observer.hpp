#pragma once
#include "message.hpp"
class Observer
{
    public:
        virtual ~Observer();
        virtual void Notify(const Message& l_messge)=0;
};