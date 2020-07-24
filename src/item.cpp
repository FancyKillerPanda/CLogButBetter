//  ===== Date Created: 24 July, 2020 ===== 

#include <assert.h>
#include "item.hpp"

std::string getStringFromItemType(ItemType itemType)
{
	switch (itemType)
	{
	case ItemType::SD_LongSleeve:	return "lssd";
	case ItemType::SD_ShortSleeve:	return "sssd";
	case ItemType::SD_Trousers:		return "sdt";
	case ItemType::SD_Jumper:		return "sdj";
	case ItemType::SD_Belt:			return "belt";
	case ItemType::SD_Shoes:		return "shoe";

	case ItemType::DPU_Shirt:		return "dps";
	case ItemType::DPU_Pants:		return "dpp";
	case ItemType::DPU_Jumper:		return "dpj";
	case ItemType::DPU_Boots:		return "boot";

	case ItemType::Hat_HFFK:		return "hffk";
	case ItemType::Hat_Badge:		return "badge";
	case ItemType::Hat_Puggaree:	return "pug";
	case ItemType::Hat_Bush:		return "bush";

	case ItemType::RankSlide:		return "rks";
	case ItemType::Webbing:			return "web";
	case ItemType::Japara:			return "jap";
	}

	assert(false);
	return "";
}
	
ItemType getItemTypeFromString(const std::string& itemString)
{
	if (itemString == "lssd")		return ItemType::SD_LongSleeve;
	else if (itemString == "sssd")	return ItemType::SD_ShortSleeve;
	else if (itemString == "sdt")	return ItemType::SD_Trousers;
	else if (itemString == "sdj")	return ItemType::SD_Jumper;
	else if (itemString == "belt")	return ItemType::SD_Belt;
	else if (itemString == "shoe")	return ItemType::SD_Shoes;

	else if (itemString == "dps")	return ItemType::DPU_Shirt;
	else if (itemString == "dpp")	return ItemType::DPU_Pants;
	else if (itemString == "dpj")	return ItemType::DPU_Jumper;
	else if (itemString == "boot")	return ItemType::DPU_Boots;

	else if (itemString == "hffk")	return ItemType::Hat_HFFK;
	else if (itemString == "badge")	return ItemType::Hat_Badge;
	else if (itemString == "pug")	return ItemType::Hat_Puggaree;
	else if (itemString == "bush")	return ItemType::Hat_Bush;

	else if (itemString == "rks")	return ItemType::RankSlide;
	else if (itemString == "web")	return ItemType::Webbing;
	else if (itemString == "jap")	return ItemType::Japara;

	assert(false);
	return ItemType::Webbing;
}
