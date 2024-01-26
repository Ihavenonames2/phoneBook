#pragma once 

#include <vector> 
#include <string> 
#include "Abonent.h" 
#include <libpq-fe.h> 

class PhoneBook
{
private:
    std::vector<Abonent> AbonentArr;

public:
    void AddToPhoneBook(Abonent&& abonent);
    void showPhoneBook();
    void RemoveFromPhoneBook(const std::string& number);
    void sortByASC();
    void sortByDESC();
    void parseToBD(PGconn* conn);
    void parseFromBD(PhoneBook& phoneBook, PGconn* conn);
};
