//  ===== Date Created: 24 July, 2020 ===== 

#if !defined(ITEM_HPP)
#define ITEM_HPP

#include <string>

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

struct ItemGroup
{
	ItemType type;
	
	int size;
	int subsize = -1;

	unsigned int quantity = 0;
	unsigned int quantityOnOrder = 0;

	std::string notes;
};

std::string getStringFromItemType(ItemType itemType);
ItemType getItemTypeFromString(const std::string& itemString);

#endif
