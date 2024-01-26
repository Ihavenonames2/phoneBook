#pragma once

#include <string>

class Abonent
{
private:
    std::string name;
    std::string number;
    std::string service;

public:
    void setName(const std::string& name);
    void setNumber(const std::string& number);
    void setService(const std::string& service);
    std::string getNumber() const;
    std::string getName() const;
    std::string getService() const;
    void call() const;
    void ShowInfo() const;
    bool operator < (const Abonent& str) const;
    virtual void CallAbonent(std::string number) const;
    
};

class TelegramAbonent : public Abonent
{
public:
    void CallAbonent(std::string number) const override;
};

class ViberAbonent : public Abonent
{
public:
    void CallAbonent(std::string number) const override;
};

class PhoneAbonent : public Abonent
{
public:
    void CallAbonent(std::string number) const override;
};

class BridgeAbonent 
{
public:
    BridgeAbonent() = default;
    BridgeAbonent(const std::string& service, const std::string& phone, const std::string& name);

    // private !!!!TODDO
    std::string serviceName_;
    std::string phoneNumber_;
    std::string name_;
};