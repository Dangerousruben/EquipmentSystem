#pragma once
#include "Item.h"

class ItemSlot
{
public:

	ItemSlot(ItemEquipType a_ItemSlotType);
	virtual ~ItemSlot();

	void EquipItem(std::shared_ptr<EquipableItem> a_NewItem, InteractResult& a_Result);

	void UnEquipItem(InteractResult& a_Result);

	bool CanEquip(std::shared_ptr<EquipableItem> a_NewItem) const;

	bool HasItemEquipped() const;

	std::string GetItemName() const;

	std::shared_ptr<EquipableItem> GetItem() const { return item; };

private:
	std::shared_ptr<EquipableItem> item;

	const ItemEquipType slot_type;
};

class InteractibleItemSlot : public ItemSlot
{
public:
	InteractibleItemSlot(ItemEquipType a_ItemSlotType);
	virtual ~InteractibleItemSlot();
};