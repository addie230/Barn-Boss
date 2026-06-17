#include "Market.h"
#include <algorithm>
#include <iostream>

Market::Market()
{
    initDefaults();
}

Product* Market::findProduct(ProductType product)
{
    auto found = products.find(product);
    return found == products.end() ? nullptr : &found->second;
}

const Product* Market::findProduct(ProductType product) const
{
    auto found = products.find(product);
    return found == products.end() ? nullptr : &found->second;
}

void Market::initDefaults()
{
    products.clear();
    set(ProductType::WheatSeed, 20, 10);
    set(ProductType::CornSeed, 20, 15);
    set(ProductType::Chicken, 10, 25);
    set(ProductType::Cow, 5, 50);
    set(ProductType::Wheat, 20, 15);
    set(ProductType::Corn, 20, 20);
    set(ProductType::Egg, 15, 30);
    set(ProductType::Milk, 10, 60);
}

void Market::print() const
{
    std::cout << "=== MARKET CATALOG ===\n";
    for (const auto& item : products)
    {
        const ProductType type = item.first;
        const Product& product = item.second;
        std::cout << productId(type) << ". " << toString(type)
            << " | Qty: " << product.quantity
            << " | Price: " << product.price << '\n';
    }
}

bool Market::buy(ProductType type, int quantity, int& balance)
{
    Product* product = findProduct(type);
    if (!product)
    {
        std::cout << "Purchase failed: product does not exist.\n";
        return false;
    }
    if (quantity <= 0 || product->quantity < quantity)
    {
        std::cout << "Purchase failed: insufficient market quantity.\n";
        return false;
    }
    const int cost = product->price * quantity;
    if (balance < cost)
    {
        std::cout << "Purchase failed: insufficient balance.\n";
        return false;
    }
    product->quantity -= quantity;
    balance -= cost;
    std::cout << "The purchase was successful!\n";
    return true;
}

bool Market::sell(ProductType type, int quantity, int& balance)
{
    Product* product = findProduct(type);
    if (!product)
    {
        std::cout << "Sale failed: product does not exist.\n";
        return false;
    }
    if (quantity <= 0)
    {
        std::cout << "Sale failed: quantity must be positive.\n";
        return false;
    }
    product->quantity += quantity;
    balance += product->price * quantity;
    std::cout << "The sale was successful!\n";
    return true;
}

bool Market::restock(ProductType type, int quantity)
{
    Product* product = findProduct(type);
    if (!product)
    {
        std::cout << "Restock failed: product does not exist.\n";
        return false;
    }
    if (quantity <= 0)
    {
        std::cout << "Restock failed: quantity must be positive.\n";
        return false;
    }
    product->quantity += quantity;
    std::cout << "Product restocked successfully!\n";
    return true;
}

bool Market::changePrice(ProductType type, int newPrice)
{
    Product* product = findProduct(type);
    if (!product)
    {
        std::cout << "Price change failed: product does not exist.\n";
        return false;
    }
    if (newPrice <= 0)
    {
        std::cout << "Price change failed: price must be positive.\n";
        return false;
    }
    product->price = newPrice;
    std::cout << "Price changed successfully!\n";
    return true;
}

void Market::set(ProductType type, int quantity, int price)
{
    products[type] = { type, std::max(0, quantity), std::max(1, price) };
}

const std::map<ProductType, Product>& Market::getProducts() const
{
    return products;
}