#include "Ingredients.h"

IngredientAttributes* GetIngredientAttributes(u8 ingredientID) {
	return &IngredientAttributesTable+ingredientID;
}

u8 GetIngredientQuantity(u8 ingredientID) {
	return IngredientQuantityTable[ingredientID].quantity;
}

void AddIngredientQuantity(u8 ingredientID, u8 val) {
	int i = IngredientQuantityTable[ingredientID].quantity;
	i += val;
	if (i > 255) i = 255;
	IngredientQuantityTable[ingredientID].quantity = i;
}


void SubIngredientQuantity(u8 ingredientID, u8 val) {
	IngredientQuantityTable[ingredientID].quantity -= val;
}

