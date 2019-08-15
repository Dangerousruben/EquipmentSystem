#include "stdafx.h"
#include "AmmoClip.h"
#include "Gun.h"

AmmoClip::AmmoClip() : 
	m_Ammo(10)
{
	CompatibleEquipTypes = { ItemEquipType::Arm };
	Name = "Ammo Clip";
}

AmmoClip::~AmmoClip()
{
}

void AmmoClip::Interact(InteractResult& a_Result)
{
	a_Result.Success = true;
	a_Result.Unequip = false;
	a_Result.Message = "Ammo clip was used";
	a_Result.Consume = true;
}

bool AmmoClip::CanBeConsumedBy(std::weak_ptr<Item> a_Item)
{
	auto tempptr = std::dynamic_pointer_cast<Gun>(a_Item.lock());
	if (tempptr)
	{
		return true;
	}
	else
	{
		throw ItemCannotBeConsumed(GetName());
	}
}

bool AmmoClip::ConsumeItem(std::weak_ptr<Item> a_Item)
{
	if (!a_Item.expired())
	{
		if (CanBeConsumedBy(a_Item))
		{
			auto tempptr = std::dynamic_pointer_cast<Gun>(a_Item.lock());
			//tempptr->Reload(this);
			return true;
		}
	}
	return false;
}
