#pragma once
#include "Product.h"
struct Task 
{ 
	int id{}; 
	ProductType requiredProduct{}; 
	int requiredQuantity{}; 
	int rewardBalance{}; 
	int rewardScore{}; 
};
