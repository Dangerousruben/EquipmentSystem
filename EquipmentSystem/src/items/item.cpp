#include "stdafx.h"
#include "items/item.h"
#include "items/itemSlot.h"

namespace EquipmentSystem
{
	Item::Item()
	{

	}

	Item::~Item()
	{

	}

	EquipableItem::EquipableItem()
	{
	}

	EquipableItem::~EquipableItem()
	{
	}

	void EquipableItem::Throw(InteractResult& a_Result)
	{
		a_Result.success = true;
		a_Result.unequip = true;
		a_Result.message = GetName() + " has been thrown far far away\n";
	}
}
