#include "Product.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>

std::string toString(ProductType type)
{
    switch (type)
    {
    case ProductType::WheatSeed:
        return "Wheat Seed";
    case ProductType::CornSeed:
        return "Corn Seed";
    case ProductType::Chicken:
        return "Chicken";
    case ProductType::Cow:
        return "Cow";
    case ProductType::Wheat:
        return "Wheat";
    case ProductType::Corn:
        return "Corn";
    case ProductType::Egg:
        return "Egg";
    case ProductType::Milk:
        return "Milk";
    }
    return "Unknown";
}

ProductType productFromId(int id)
{
    if (id < 1 || id > 8)
    {
        throw std::runtime_error("Invalid product id.");
    }
    return static_cast<ProductType>(id);
}

ProductType productFromString(const std::string& name)
{
    std::string normalized = name;

    std::transform(normalized.begin(), normalized.end(), normalized.begin(),
        [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

    normalized.erase(std::remove(normalized.begin(), normalized.end(), '_'), normalized.end());
    normalized.erase(std::remove(normalized.begin(), normalized.end(), '-'), normalized.end());
    normalized.erase(std::remove(normalized.begin(), normalized.end(), ' '), normalized.end());

    if (normalized == "wheat")
    {
        return ProductType::Wheat;
    }
    if (normalized == "corn")
    {
        return ProductType::Corn;
    }
    if (normalized == "egg")
    {
        return ProductType::Egg;
    }
    if (normalized == "milk")
    {
        return ProductType::Milk;
    }
    if (normalized == "wheatseed")
    {
        return ProductType::WheatSeed;
    }
    if (normalized == "cornseed")
    {
        return ProductType::CornSeed;
    }
    if (normalized == "chicken")
    {
        return ProductType::Chicken;
    }
    if (normalized == "cow")
    {
        return ProductType::Cow;
    }
    throw std::runtime_error("Invalid product name.");
}

int productId(ProductType type)
{
    return static_cast<int>(type);
}

bool isSeed(ProductType type)
{
    return type == ProductType::WheatSeed || type == ProductType::CornSeed;
}

bool isAnimalProduct(ProductType type)
{
    return type == ProductType::Chicken || type == ProductType::Cow;
}
