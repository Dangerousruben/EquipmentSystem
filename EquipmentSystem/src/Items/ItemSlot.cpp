#include "stdafx.h"
#include "Items/ItemSlot.h"
#include "Player.h"


namespace EquipmentSystem
{
	ItemSlot::ItemSlot(ItemEquipType a_ItemSlotType) : slot_type(a_ItemSlotType)
	{
	}

	ItemSlot::~ItemSlot()
	{
	}

	void ItemSlot::EquipItem(const std::shared_ptr<EquipableItem> a_NewItem, InteractResult& a_Result)
	{
		if (CanEquip(a_NewItem))
		{
			a_Result.message += a_NewItem->GetName() + " has been equipped\n";
			a_Result.success = true;
			item = a_NewItem;
		}
	}

	void ItemSlot::UnEquipItem(InteractResult& a_Result)
	{
		if (!item)
		{
			throw ItemSlotEmpty();
		}
		a_Result.message += item->GetName() + " has been unequipped\n";
		a_Result.success = true;
		item.reset();
	}

	bool ItemSlot::CanEquip(std::shared_ptr<EquipableItem> a_NewItem) const
	{
		if (!a_NewItem)
		{
			throw EquipItemEmpty();
		}

		//Will find either ItemEquipType Any or slot_type in the items compatible_equip_types vector
		auto foundItem = std::find_if(a_NewItem->compatible_equip_types.begin(), a_NewItem->compatible_equip_types.end(),
			[=](ItemEquipType a_ItemType) { return a_ItemType == ItemEquipType::Any || a_ItemType == slot_type; });

		if (foundItem == a_NewItem->compatible_equip_types.end())
		{
			throw IncompatibleItem();
		}
		return true;
	}

	bool ItemSlot::HasItemEquipped() const
	{
		return item != nullptr;
	}

	std::string ItemSlot::GetItemName() const
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
}
