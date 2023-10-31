#include "gbafe.h"

// structs

struct AlchemyIngredient {
  u16 ingredientID; //elementID | 0x100
  u8 quantity; //if elementID instead of ingredientID, # of points needed 
} typedef AlchemyIngredient;

struct AlchemyRecipe {
  AlchemyIngredient* ingredients;
  bool outputsIngredient;  
  u8 outputItem;
} typedef AlchemyRecipe;

// EA literals
extern AlchemyRecipe* RecipesTable;

// function prototypes


