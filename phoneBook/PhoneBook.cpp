#include <algorithm> 
#include <vector> 
#include "Abonent.h" 
#include "PhoneBook.h" 
#include <iostream> 
#include <libpq-fe.h> 

void PhoneBook::AddToPhoneBook(Abonent&& abonent)
{
     // call AbonentFactory auto temp = AbonentFactory::getAbonent(ser);
    AbonentArr.push_back(std::move(abonent));
}

void PhoneBook::showPhoneBook()
{
    if (AbonentArr.empty())
        std::cout << " Phone book is empty" << std::endl;
    int iter = 1;
    for (Abonent& i : AbonentArr)
    {
        std::cout << iter << ". ";
        i.ShowInfo();
        ++iter;
    }
    std::cout << std::endl;
}

void PhoneBook::RemoveFromPhoneBook(const std::string& number)
{
    for (auto i = AbonentArr.begin(); i != AbonentArr.end();)
    {
        if (i->getNumber() == number)
        {
            i = AbonentArr.erase(i);
        }
        else
        {
            i++;
        }
    }
}

void PhoneBook::sortByASC()
{
    std::sort(AbonentArr.begin(), AbonentArr.end());
}

void PhoneBook::sortByDESC()
{
    std::sort(AbonentArr.rbegin(), AbonentArr.rend());
}

void PhoneBook::parseToBD(PGconn* conn)
{
    std::string query = "TRUNCATE TABLE phoneBook RESTART IDENTITY;";
    PQexec(conn, query.c_str());
    std::string drop_query = "DELETE FROM phoneBook;";
    PGresult* res = PQexec(conn, drop_query.c_str());
    PQclear(res);
    for (Abonent& i : AbonentArr)
    {
        std::string insert_query = "INSERT INTO phoneBook (name, phone_number, service) VALUES ('" + i.getName() + "', '" + i.getNumber() + "', '" + i.getService() + "');";
        PGresult* res = PQexec(conn, insert_query.c_str());
    }
}

void PhoneBook::parseFromBD(PhoneBook& phoneBook, PGconn* conn)
{
    Abonent abonent;

    const char* select_query = "SELECT id, name, phone_number, service FROM phoneBook;";
    PGresult* res = PQexec(conn, select_query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Failed to fetch data from PhoneBook: %s", PQresultErrorMessage(res));
        PQclear(res);
    }

    int rows = PQntuples(res);
    int cols = PQnfields(res);

    for (int i = 0; i < rows; i++) {
        abonent.setName(PQgetvalue(res, i, 1));
        abonent.setNumber(PQgetvalue(res, i, 2));
        abonent.setService(PQgetvalue(res, i, 3));
        phoneBook.AddToPhoneBook(std::move(abonent));
    }
    PQclear(res);

}
