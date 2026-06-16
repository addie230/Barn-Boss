#include "Animal.h"
#include <stdexcept>

namespace
{
    int getAnimalRequiredCycles(int id)
    {
        switch (id)
        {
        case 3:
            return 3;
        case 4:
            return 5;
        default:
            throw std::runtime_error("Invalid animal id.");
        }
    }
    ProductType getAnimalProducedProduct(int id)
    {
        switch (id)
        {
        case 3:
            return ProductType::Egg;
        case 4:
            return ProductType::Milk;
        default:
            throw std::runtime_error("Invalid animal id.");
        }
    }
}

Animal::Animal(int id, int currentCycle)
    : FarmEntity(getAnimalRequiredCycles(id),
        getAnimalProducedProduct(id),
        currentCycle),
    animalId(id)
{
}

std::string Animal::getName() const
{
    return animalId == 3 ? "Chicken" : "Cow";
}