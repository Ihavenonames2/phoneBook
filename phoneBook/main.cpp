#include "PhoneBook.h" 
#include "Abonent.h" 
#include "AbonentFactory.h" 

#include <iostream> 
#include <vector> 
#include <algorithm>   
#include <fstream> 
#include <libpq-fe.h>

//Abonent сделать абстратным + bridge
//сделать что то типа entityAbonent для работы с ними


PGconn* connection()
{
    PGconn* conn = PQconnectdb("host=localhost port=5432 dbname=postgres user=postgres password=admin");
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
        PQfinish(conn);
    }
    return conn;
}

int main()
{
    PGconn* conn = connection();
    PhoneBook phoneBook;
    phoneBook.parseFromBD(phoneBook, conn);
    Abonent abonent;
    int statement = -1;

    while (statement != 4)
    {
        std::string name = " ";
        std::string service = " ";
        std::string number = " ";
        int temp = -1;
        std::cout << "1. Add to phone book" << std::endl;
        std::cout << "2. Remove from phone book" << std::endl;
        std::cout << "3. Show phone book" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cin >> statement;
        switch (statement)
        {
        case 1:
            std::cout << "Enter name" << std::endl;
            std::cin >> name;
            abonent.setName(name);
            std::cout << "Enter number" << std::endl;
            std::cin >> number;
            abonent.setNumber(number);
            std::cout << "Enter service" << std::endl;
            std::cin >> service;
            abonent.setService(service);
            phoneBook.AddToPhoneBook(std::move(abonent));
            system("cls");
            break;
        case 2:
            std::cout << "Enter number of abonent to remove" << std::endl;
            std::cin >> number;
            phoneBook.RemoveFromPhoneBook(number);
            break;
        case 3:
            system("cls");
            while (temp != 0)
            {
                phoneBook.showPhoneBook();
                std::cout << "1. to sort numbers by asc" << std::endl;
                std::cout << "2. to sort number by desc" << std::endl;
                std::cout << "3. to call a number" << std::endl;
                std::cout << "0. to main menu" << std::endl;
                std::cin >> temp;
                if (temp == 1)
                {
                    phoneBook.sortByASC();
                    system("cls");
                }
                else if (temp == 2)
                {
                    phoneBook.sortByDESC();
                    system("cls");
                }
                else if (temp == 3)
                {
                    std::string number;
                    std::cout << "Enter a number to call" << std::endl;
                    std::cin >> number;
                    std::string ser;
                    std::cout << "Enter a service to call with" << std::endl;
                    std::cin >> ser;
                    auto temp = AbonentFactory::getAbonent(ser);
                    system("cls");
                    temp->CallAbonent(number);
                }
            }
            break;
        case 4:
            phoneBook.parseToBD(conn);
            break;
        }


    }
}
