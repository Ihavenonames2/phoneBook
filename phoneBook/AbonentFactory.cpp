#include "AbonentFactory.h"

std::shared_ptr<Abonent> AbonentFactory::getAbonent(const std::string& service)
{
    if (service == "Telegram")
        return std::make_shared<TelegramAbonent>();
    if (service == "Viber")
        return std::make_shared<ViberAbonent>();
    if (service == "Phone")
        return std::make_shared<PhoneAbonent>();
}