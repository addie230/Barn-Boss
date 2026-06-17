#pragma once
#include "Product.h"
#include <map>

class Market
{
private:
    std::map<ProductType, Product> products{};

    Product* findProduct(ProductType product);
    const Product* findProduct(ProductType product) const;

public:
    Market();

    void initDefaults();
    void print() const;

    bool buy(ProductType product, int quantity, int& balance);
    bool sell(ProductType product, int quantity, int& balance);
    bool restock(ProductType product, int quantity);
    bool changePrice(ProductType product, int newPrice);

    void set(ProductType product, int quantity, int price);
    const std::map<ProductType, Product>& getProducts() const;
};
