#include "stdafx.h"
#include "ItemSlot.h"
#include "Player.h"



ItemSlot::ItemSlot(ItemEquipType a_ItemSlotType)
{
	SlotType = a_ItemSlotType;
}

ItemSlot::~ItemSlot()
{
}

bool ItemSlot::EquipItem(const std::shared_ptr<Item> a_NewItem)
{
	if (CanEquip(a_NewItem))
	{
		item = a_NewItem;
		return true;
	}
	return false;
}

bool ItemSlot::UnEquipItem()
{
	if (!item)
	{
		throw ItemSlotEmpty();
	}
	item.reset();
	return true;
}

bool ItemSlot::CanEquip(std::shared_ptr<Item> a_NewItem)
{
	if (!a_NewItem)
	{
		throw EquipItemEmpty();
	}
	auto foundItem = std::find_if(a_NewItem->CompatibleEquipTypes.begin(), a_NewItem->CompatibleEquipTypes.end(),
		[=](ItemEquipType a_ItemType) { return a_ItemType == ItemEquipType::Any || a_ItemType == SlotType; });

	if (foundItem == a_NewItem->CompatibleEquipTypes.end())
	{
		throw IncompatibleItem();
	}
	return true;
}

bool ItemSlot::HasItemEquipped()
{
	if (item)
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::string ItemSlot::GetItemName()
{
	if (!item)
	{
		throw ItemSlotEmpty();
	}
	return item->GetName();
}

InteractibleItemSlot::InteractibleItemSlot(ItemEquipType a_ItemSlotType)
	: ItemSlot(a_ItemSlotType)
{
}

InteractibleItemSlot::~InteractibleItemSlot()
{
}

void InteractibleItemSlot::Interact(InteractResult& a_Result)
{
	if (item)
	{
		return item->Interact(a_Result);
	}
	else
	{
		throw ItemSlotEmpty();
	}
}
