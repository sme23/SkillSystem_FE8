#include "Ingredients.h"

IngredientAttributes* GetIngredientAttributes(u8 ingredientID) {
	return &IngredientAttributesTable+ingredientID;
}

u8 GetIngredientQuantity(u8 ingredientID) {
	return IngredientQuantityTable[ingredientID].quantity;
}

void AddIngredientQuantity(u8 ingredientID, u8 val) {
	IngredientQuantityTable[ingredientID].quantity += val;
}


void SubIngredientQuantity(u8 ingredientID, u8 val) {
	IngredientQuantityTable[ingredientID].quantity -= val;
}

