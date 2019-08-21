#include "stdafx.h"
#include "items/item.h"
#include "items/itemSlot.h"

namespace EquipmentSystem
{
	void EquipableItem::Throw(InteractResult& a_Result)
	{
		a_Result.success = true;
		a_Result.message = GetName() + " has been thrown far far away\n";
	}
}
