#include "Barn.h"
#include <algorithm>
#include <iostream>

Barn::Barn()
{
    for (int id = 1; id <= 8; ++id)
    {
        items[productFromId(id)] = 0;
    }
}

int Barn::get(ProductType product) const
{
    const auto found = items.find(product);
    return found == items.end() ? 0 : found->second;
}

void Barn::add(ProductType product, int quantity)
{
    if (quantity > 0)
    {
        items[product] += quantity;
    }
}

bool Barn::remove(ProductType product, int quantity)
{
    if (quantity <= 0 || get(product) < quantity)
    {
        return false;
    }

    items[product] -= quantity;
    return true;
}

bool Barn::has(ProductType product, int quantity) const
{
    return quantity > 0 && get(product) >= quantity;
}

void Barn::print() const
{
    std::cout << "=== BARN ===\n";
    for (const auto& item : items)
    {
        std::cout << toString(item.first) << ": " << item.second << '\n';
    }
}

const std::map<ProductType, int>& Barn::getItems() const
{
    return items;
}

void Barn::set(ProductType product, int quantity)
{
    items[product] = std::max(0, quantity);
}
