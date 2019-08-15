#pragma once
#include "Item.h"

class ItemSlot
{
public:
	friend Player;

	ItemSlot(ItemEquipType a_ItemSlotType);
	virtual ~ItemSlot();

	bool EquipItem(std::shared_ptr<Item> a_NewItem);

	bool UnEquipItem();

	bool HasItemEquipped();

	std::string GetItemName();

protected:
	std::shared_ptr<Item> item;

private:

	ItemEquipType SlotType;
};

class InteractibleItemSlot : public ItemSlot
{
public:
	InteractibleItemSlot(ItemEquipType a_ItemSlotType);
	virtual ~InteractibleItemSlot();

	void Interact(InteractResult& a_Result);
};