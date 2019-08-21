#pragma once
#include "items/item.h"

namespace EquipmentSystem
{
	//Items can be equipped to slots in here
	class ItemSlot
	{
	public:

		ItemSlot(ItemEquipType a_ItemSlotType) : slot_type(a_ItemSlotType) {};
		virtual ~ItemSlot() {};

		//Unequips current item and equips new
		void EquipItem(std::shared_ptr<EquipableItem> a_NewItem, InteractResult& a_Result);

		//Unequips current item
		void UnEquipItem(InteractResult& a_Result);

		//Checks whether the item can be equipped or not
		bool CanEquip(std::shared_ptr<EquipableItem> a_NewItem) const;

		//Checks if an item is equpped
		bool HasItemEquipped() const;

		//Returns the item name
		std::string GetItemName() const;

		//Returns a pointer to the item
		std::shared_ptr<EquipableItem> GetItem() const { return item; };

	private:
		//Held item
		std::shared_ptr<EquipableItem> item;

		//The compatible equip type
		const ItemEquipType slot_type;
	};

	//Interactible slot, only this slot can be used to Interact with items
	class InteractibleItemSlot : public ItemSlot
	{
	public:
		InteractibleItemSlot(ItemEquipType a_ItemSlotType) : ItemSlot(a_ItemSlotType) {};
		virtual ~InteractibleItemSlot() {};
	};
}
