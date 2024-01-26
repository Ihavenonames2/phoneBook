#include <iostream>
#include "Abonent.h"

void Abonent::setName(const std::string& name)
{
    this->name = name;
}

void Abonent::setNumber(const std::string& number)
{
    this->number = number;
}

void Abonent::setService(const std::string& service)
{
    this->service = service;
}

std::string Abonent::getNumber() const
{
    return number;
}

std::string Abonent::getName() const
{
    return name;
}

std::string Abonent::getService() const
{
    return service;
}

void Abonent::call() const
{
    std::cout << "called Abonent from " << service << std::endl;
}

void Abonent::ShowInfo() const
{
    std::cout << name << "  ";
    std::cout << number << "  ";
    std::cout << service << std::endl;
}

bool Abonent::operator < (const Abonent& str) const
{
    return (number < str.number);
}

void Abonent::CallAbonent(std::string number) const
{
 
}


void TelegramAbonent::CallAbonent(std::string number) const
{
    std::cout << "Called abonent "<< number <<" with telegram" << std::endl;
}

void ViberAbonent::CallAbonent(std::string number) const
{
    std::cout << "Called abonent " << number << " with viber" << std::endl;
}

void PhoneAbonent::CallAbonent(std::string number) const
{
    std::cout << "Called abonent " << number << " with phone" << std::endl;
}

BridgeAbonent::BridgeAbonent(const std::string& service, const std::string& phone, const std::string& name) :
    serviceName_(service),
    phoneNumber_(phone),
    name_(name)//TODO BRIDGE
{
}
