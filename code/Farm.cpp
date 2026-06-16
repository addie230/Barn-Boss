#include "Farm.h"
#include "Animal.h"
#include "Plant.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <stdexcept>

namespace
{
    int harvestReadyEntities(std::vector<std::unique_ptr<FarmEntity>>& entities, Barn& barn)
    {
        int collectedProducts = 0;
        for (std::size_t index = 0; index < entities.size();)
        {
            if (entities[index]->isReady())
            {
                barn.add(entities[index]->getProducedProduct(), 1);
                entities.erase(std::next(entities.begin(), static_cast<std::ptrdiff_t>(index)));
                ++collectedProducts;
            }
            else
            {
                ++index;
            }
        }
        return collectedProducts;
    }

    ProductType seedProductType(int seedId)
    {
        switch (seedId)
        {
            case 1: 
                return ProductType::WheatSeed;
            case 2: 
                return ProductType::CornSeed;
            default: 
                throw std::runtime_error("Invalid seed id.");
        }
    }

    ProductType animalProductType(int animalId)
    {
        switch (animalId)
        {
            case 3: 
                return ProductType::Chicken;
            case 4: 
                return ProductType::Cow;
            default: 
                throw std::runtime_error("Invalid animal id.");
        }
    }
}

int Farm::freeCropland() const
{
    return croplandCapacity - static_cast<int>(cropland.size());
}

int Farm::freeFarmland() const
{
    return farmlandCapacity - static_cast<int>(farmland.size());
}

int Farm::getCroplandCapacity() const
{
    return croplandCapacity;
}

int Farm::getFarmlandCapacity() const
{
    return farmlandCapacity;
}

void Farm::setCapacities(int newCroplandCapacity, int newFarmlandCapacity)
{
    croplandCapacity = std::max(3, newCroplandCapacity);
    farmlandCapacity = std::max(3, newFarmlandCapacity);
}

bool Farm::sowPlant(int seedId, Barn& barn)
{
    ProductType seed = seedProductType(seedId);
    if (freeCropland() <= 0)
    {
        std::cout << "Cannot plant: Cropland is full.\n";
        return false;
    }
    if (!barn.remove(seed, 1))
    {
        std::cout << "Cannot plant: missing seed.\n";
        return false;
    }
    cropland.push_back(std::make_unique<Plant>(seedId));
    std::cout << "Plants planted successfully!\n";
    return true;
}

bool Farm::addAnimal(int animalId, Barn& barn)
{
    ProductType animal = animalProductType(animalId);
    if (freeFarmland() <= 0)
    {
        std::cout << "Cannot add animal: Farmland is full.\n";
        return false;
    }
    if (!barn.remove(animal, 1))
    {
        std::cout << "Cannot add animal: missing animal.\n";
        return false;
    }
    farmland.push_back(std::make_unique<Animal>(animalId));
    std::cout << "Animals added successfully!\n";
    return true;
}

int Farm::harvest(Barn& barn)
{
    int collectedProducts = 0;
    collectedProducts += harvestReadyEntities(cropland, barn);
    collectedProducts += harvestReadyEntities(farmland, barn);
    if (collectedProducts == 0)
    {
        std::cout << "Nothing to harvest yet.\n";
    }
    else
    {
        std::cout << "Harvest completed!\n";
    }
    return collectedProducts;
}

void Farm::progress()
{
    for (auto& entity : cropland)
    {
        entity->progress();
    }
    for (auto& entity : farmland)
    {
        entity->progress();
    }
}

void Farm::print() const
{
    std::cout << "=== FARM ===\n"
        << "Cropland: " << cropland.size() << '/' << croplandCapacity
        << ", free: " << freeCropland() << '\n'
        << "Farmland: " << farmland.size() << '/' << farmlandCapacity
        << ", free: " << freeFarmland() << '\n';
}

bool Farm::expandCropland()
{
    ++croplandCapacity;
    return true;
}

bool Farm::expandFarmland()
{
    ++farmlandCapacity;
    return true;
}

const std::vector<std::unique_ptr<FarmEntity>>& Farm::getCropland() const
{
    return cropland;
}

const std::vector<std::unique_ptr<FarmEntity>>& Farm::getFarmland() const
{
    return farmland;
}

void Farm::addLoadedEntity(char category, int id, int currentCycle)
{
    if (currentCycle < 0)
    {
        currentCycle = 0;
    }
    if (category == 'P')
    {
        if (static_cast<int>(cropland.size()) >= croplandCapacity)
        {
            throw std::runtime_error("Cropland capacity exceeded.");
        }
        cropland.push_back(std::make_unique<Plant>(id, currentCycle));
    }
    else if (category == 'A')
    {
        if (static_cast<int>(farmland.size()) >= farmlandCapacity)
        {
            throw std::runtime_error("Farmland capacity exceeded.");
        }
        farmland.push_back(std::make_unique<Animal>(id, currentCycle));
    }
}