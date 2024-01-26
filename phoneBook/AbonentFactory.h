#pragma once

#include "Abonent.h"
#include <iostream> 


class AbonentFactory
{
public:
    AbonentFactory() = delete;

    static std::shared_ptr<Abonent> getAbonent(const std::string& service);
    
};
