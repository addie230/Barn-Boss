#pragma once
#include <string>

enum class ProductType 
{ 
    WheatSeed = 1, 
    CornSeed = 2, 
    Chicken = 3, 
    Cow = 4, 
    Wheat = 5, 
    Corn = 6, 
    Egg = 7, 
    Milk = 8 
};

struct Product {
    ProductType type{};
    int quantity{};
    int price{};
};

std::string toString(ProductType type);
ProductType productFromId(int id);
ProductType productFromString(const std::string& name);
int productId(ProductType type);
bool isSeed(ProductType type);
bool isAnimalProduct(ProductType type);

