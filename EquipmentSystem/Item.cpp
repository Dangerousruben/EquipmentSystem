#include "stdafx.h"
#include "Item.h"
#include "ItemSlot.h"


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