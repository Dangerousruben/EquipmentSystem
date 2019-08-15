#include "stdafx.h"
#include "Item.h"
#include "ItemSlot.h"


Item::Item()
{
	
}

Item::~Item()
{

}

void Item::Throw(InteractResult& a_Result)
{
	a_Result.Success = true;
	a_Result.Unequip = true;
	a_Result.Message = GetName() + " has been thrown with speed " + std::to_string(ThrowSpeed) + "\n";
	a_Result.ThrowSpeed = ThrowSpeed;
}

ConsumableItem::ConsumableItem()
{
}

ConsumableItem::~ConsumableItem()
{
}

ItemConsumer::ItemConsumer()
{
}

ItemConsumer::~ItemConsumer()
{
}