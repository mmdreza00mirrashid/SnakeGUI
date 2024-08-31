/*
 * Class to define the in game foods
*/ 

#ifndef FOOD_H_
#define FOOD_H_

#include <SFML/Graphics.hpp>

#include "parts.h"
enum class FoodType { SIZE, SPEED };
class Food {
	public:

		/////////////////
		//   Getters   //
		/////////////////

		FoodPart getPart() const {
			return _part;
		}
		
		FoodType getFoodType() const {
       	 return _foodType;
    		}
		
		//////////////
		// Settters //
		//////////////
		
		void setFoodType(const FoodType foodType) {
			_foodType = foodType;
		}

		/////////////////
		// Constructor //
		/////////////////

		Food(FoodPart part) : _part(part) {}

	private:
		FoodPart _part;
		FoodType _foodType;
};

#endif
