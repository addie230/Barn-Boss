#pragma once
#include "Market.h"
#include "User.h"

class MarketManager : public User
{
public:
    MarketManager(int id, const std::string& username, const std::string& password);

    std::string getType() const override;

    void openMarketCatalog(const Market& market) const;
    bool restock(Market& market, ProductType product, int quantity);
    bool changePrice(Market& market, ProductType product, int newPrice);
};
