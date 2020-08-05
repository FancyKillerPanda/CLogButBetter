//  ===== Date Created: 24 July, 2020 ===== 

#if !defined(ITEM_HPP)
#define ITEM_HPP

#include <string>

/*
 * Represents the type of the uniform item.
 */
enum class ItemType
{
	SD_LongSleeve,
	SD_ShortSleeve,
	SD_Trousers,
	SD_Jumper,
	SD_Belt,
	SD_Shoes,

	DPU_Shirt,
	DPU_Pants,
	DPU_Jumper,
	DPU_Boots,
	
	Hat_HFFK,
	Hat_Badge,
	Hat_Puggaree,
	Hat_Bush,

	RankSlide,
	Webbing,
	Japara,
};

/*
 * Holds all information about one unique item "type", which is
 * uniquely identified by its actual type and its size (and subsize if it
 * exists).

 * This structure also contains information about the number of items
 * currently in the group, as well as the number of items that have
 * been ordered. There is a field for notes about this item group.
 */
struct ItemGroup { ItemType type;
	
	int size;
	int subsize = -1;

	unsigned int quantity = 0;
	unsigned int quantityOnOrder = 0;

	std::string notes;
};

/*
 * Returns the string representation for each item type.
 *
 * Input: the type of item
 * Output: a string representing the item type
 */
std::string getStringFromItemType(ItemType itemType);

/*
 * Returns the item type that a particular string represents. It is
 * essentially the opposite of the above function.
 *
 * Input: a string representing the item type
 * Output: the type of item
 */
ItemType getItemTypeFromString(const std::string& itemString);

#endif
