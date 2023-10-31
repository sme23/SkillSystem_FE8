#include "gbafe.h"

//structs
struct IngredientAttributes {
  u16 nameID;
  u16 descID;
  u8 category;
  u8 fire;
  u8 water;
  u8 earth;
  u8 thunder;
  u8 ice;
  u8 wind;
  u8 light;
  u8 dark;
  u8 pad[3];
} typedef IngredientAttributes;

struct IngredientQuantity {
  u8 quantity;
} typedef IngredientQuantity;

//EA literals
extern IngredientAttributes IngredientAttributesTable;
extern IngredientQuantity* IngredientQuantityTable;

//function prototypes
IngredientAttributes* GetIngredientAttributes(u8 ingredientID);
u8 GetIngredientQuantity(u8 ingredientID);
void AddIngredientQuantity(u8 ingredientID, u8 val);
void SubIngredientQuantity(u8 ingredientID, u8 val);
