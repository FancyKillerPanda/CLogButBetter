//  ===== Date Created: 24 July, 2020 ===== 

#include <assert.h>
#include "item.hpp"

std::string getStringFromItemType(ItemType itemType)
{
	switch (itemType)
	{
	case ItemType::SD_LongSleeve:	return "LSSD Shirt";
	case ItemType::SD_ShortSleeve:	return "SSSD Shirt";
	case ItemType::SD_Trousers:		return "SD Trousers";
	case ItemType::SD_Jumper:		return "SD Jumper";
	case ItemType::SD_Belt:			return "SD Belt";
	case ItemType::SD_Shoes:		return "SD Shoes";

	case ItemType::DPU_Shirt:		return "DPU Shirt";
	case ItemType::DPU_Pants:		return "DPU Pants";
	case ItemType::DPU_Jumper:		return "DPU Jumper";
	case ItemType::DPU_Boots:		return "DPU Boots";

	case ItemType::Hat_HFFK:		return "HFFK";
	case ItemType::Hat_Badge:		return "Hat Badge";
	case ItemType::Hat_Puggaree:	return "Puggaree";
	case ItemType::Hat_Bush:		return "Bush Hat";

	case ItemType::RankSlide:		return "Rank Slides";
	case ItemType::Webbing:			return "Webbing";
	case ItemType::Japara:			return "Japara";
	}

	assert(false);
	return "";
}
	
ItemType getItemTypeFromString(const std::string& itemString)
{
	if (itemString == "LSSD Shirt")		return ItemType::SD_LongSleeve;
	else if (itemString == "SSSD Shirt")	return ItemType::SD_ShortSleeve;
	else if (itemString == "SD Trousers")	return ItemType::SD_Trousers;
	else if (itemString == "SD Jumper")	return ItemType::SD_Jumper;
	else if (itemString == "SD Belt")	return ItemType::SD_Belt;
	else if (itemString == "SD Shoes")	return ItemType::SD_Shoes;

	else if (itemString == "DPU Shirt")	return ItemType::DPU_Shirt;
	else if (itemString == "DPU Pants")	return ItemType::DPU_Pants;
	else if (itemString == "DPU Jumper")	return ItemType::DPU_Jumper;
	else if (itemString == "DPU Boots")	return ItemType::DPU_Boots;

	else if (itemString == "HFFK")	return ItemType::Hat_HFFK;
	else if (itemString == "Hat Badge")	return ItemType::Hat_Badge;
	else if (itemString == "Puggaree")	return ItemType::Hat_Puggaree;
	else if (itemString == "Bush Hat")	return ItemType::Hat_Bush;

	else if (itemString == "Rank Slides")	return ItemType::RankSlide;
	else if (itemString == "Webbing")	return ItemType::Webbing;
	else if (itemString == "Japara")	return ItemType::Japara;

	assert(false);
	return ItemType::Webbing;
}
