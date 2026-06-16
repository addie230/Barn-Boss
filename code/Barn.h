#pragma once
#include "Product.h"
#include <map>

class Barn
{
private:
    std::map<ProductType, int> items{};

public:
    Barn();
    int get(ProductType product) const;
    void add(ProductType product, int quantity);
    bool remove(ProductType product, int quantity);
    bool has(ProductType product, int quantity) const;
    void print() const;
    const std::map<ProductType, int>& getItems() const;
    void set(ProductType product, int quantity);
};
