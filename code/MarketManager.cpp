#include "MarketManager.h"

MarketManager::MarketManager(int id, const std::string& username, const std::string& password)
    : User(id, username, password)
{
}

std::string MarketManager::getType() const
{
    return "MarketManager";
}

void MarketManager::openMarketCatalog(const Market& market) const
{
    market.print();
}

bool MarketManager::restock(Market& market, ProductType product, int quantity)
{
    return market.restock(product, quantity);
}

bool MarketManager::changePrice(Market& market, ProductType product, int newPrice)
{
    return market.changePrice(product, newPrice);
}
