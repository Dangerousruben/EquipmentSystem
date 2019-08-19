#include "stdafx.h"
#include "Player.h"
#include "Item.h"
#include "ItemSlot.h"
#include "Gun.h"
#include "AmmoClip.h"
#include "Rock.h"
#include "FlashLight.h"

Player::Player()
{	
	item_slot_map.insert(std::make_pair(HeadSlot, std::shared_ptr<ItemSlot>(std::make_shared<ItemSlot>(Head))));
	item_slot_map.insert(std::make_pair(PlayerItemSlots::LeftArmSlot, std::shared_ptr<ItemSlot>(std::make_shared<InteractibleItemSlot>(Arm))));
	item_slot_map.insert(std::make_pair(PlayerItemSlots::RightArmSlot, std::shared_ptr<ItemSlot>(std::make_shared<InteractibleItemSlot>(Arm))));
}

Player::~Player()
{

}


void Player::EquipItem(const std::shared_ptr<EquipableItem> a_Item, PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	if (item_slot_map.at(a_ItemSlot)->HasItemEquipped())
	{
		item_slot_map.at(a_ItemSlot)->UnEquipItem(a_Result);
	}
	if (!a_Item)
	{
		throw EquipItemEmpty();
	}
	item_slot_map.at(a_ItemSlot)->EquipItem(a_Item, a_Result);
}

void Player::UnEquipItem(PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	item_slot_map.at(a_ItemSlot)->UnEquipItem(a_Result);
}

std::string Player::GetItemNameOnSlot(PlayerItemSlots a_ItemSlot) const
{
	return item_slot_map.at(a_ItemSlot)->GetItemName();
}

void Player::Reload(PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	if (CanInteract(a_ItemSlot))
	{
		PlayerItemSlots otherArm = (a_ItemSlot == RightArmSlot) ? LeftArmSlot : RightArmSlot;
		auto tempGunptr = std::dynamic_pointer_cast<Gun>((item_slot_map.at(a_ItemSlot)->GetItem()));
		if (!tempGunptr)
		{
			tempGunptr = std::dynamic_pointer_cast<Gun>((item_slot_map.at(otherArm)->GetItem()));
			if (!tempGunptr)
			{
				throw NoGunEquipped();
			}
		}


		auto tempAmmoClipptr = std::dynamic_pointer_cast<AmmoClip>(item_slot_map.at(otherArm)->GetItem());
		if (!tempAmmoClipptr)
		{
			tempAmmoClipptr = std::dynamic_pointer_cast<AmmoClip>((item_slot_map.at(a_ItemSlot)->GetItem()));
			if (!tempAmmoClipptr)
			{
				throw NoAmmoClipEquipped();
			}
		}

		tempGunptr->Reload(tempAmmoClipptr);
		UnEquipItem(otherArm, a_Result);
		a_Result.message += "I reloaded my gun\n";
		a_Result.success = true;
	}
}

int Player::GetAmmo(PlayerItemSlots a_ItemSlot)
{
	auto temp_gun_ptr = std::dynamic_pointer_cast<Gun>(item_slot_map.at(a_ItemSlot).get()->GetItem());
	if (temp_gun_ptr)
	{
		return temp_gun_ptr->GetAmmo();
	}
//	else if ()
	//{

	//}
	else
	{
		throw NoGunEquipped();
	}
}

void Player::Shoot(PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	if (CanInteract(a_ItemSlot))
	{
		auto tempShootPtr = std::dynamic_pointer_cast<GunInterface>(item_slot_map.at(a_ItemSlot).get()->GetItem());
		if (tempShootPtr)
		{
			tempShootPtr->Shoot(a_Result);
		}
	}
}

void Player::Throw(PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	if (CanInteract(a_ItemSlot))
	{
		std::weak_ptr<EquipableItem> tempItemPtr = item_slot_map.at(a_ItemSlot).get()->GetItem();
		if (!tempItemPtr.expired())
		{
			tempItemPtr.lock()->Throw(a_Result);
			if (a_Result.success)
			{
				UnEquipItem(a_ItemSlot, a_Result);
				a_Result.unequip = true;
			}
		}
	}
}

void Player::Toggle(PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	if (CanInteract(a_ItemSlot))
	{
		std::weak_ptr<ToggleInterface> tempButtonPtr = std::dynamic_pointer_cast<ToggleInterface>(item_slot_map.at(a_ItemSlot).get()->GetItem());
		if (!tempButtonPtr.expired())
		{
			tempButtonPtr.lock()->ToggleState(a_Result);
		}
	}
}

void Player::Use(PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	auto item = item_slot_map.at(a_ItemSlot).get()->GetItem();
	auto tempShootPtr = std::dynamic_pointer_cast<GunInterface>(item);
	if (tempShootPtr)
	{
		Shoot(a_ItemSlot, a_Result);
		return;
	}
	auto tempAmmoPtr = std::dynamic_pointer_cast<AmmoClip>(item);
	if (tempAmmoPtr)
	{
		Reload(a_ItemSlot, a_Result);
		return;
	}
	auto tempRockPtr = std::dynamic_pointer_cast<Rock>(item);
	if (tempRockPtr)
	{
		Throw(a_ItemSlot, a_Result);
	}
	auto tempFlashLightPtr = std::dynamic_pointer_cast<FlashLight>(item);
	if (tempFlashLightPtr)
	{
		Toggle(a_ItemSlot, a_Result);
	}
}

void Player::SwapItems(PlayerItemSlots a_ItemSlot1, PlayerItemSlots a_ItemSlot2, InteractResult& a_Result)
{
	auto tempItem1 = item_slot_map.at(a_ItemSlot1)->GetItem();
	auto tempItem2 = item_slot_map.at(a_ItemSlot2)->GetItem();
	try
	{
		try
		{
			EquipItem(tempItem2, a_ItemSlot1, a_Result);
		}
		catch (EquipItemEmpty) {}
		catch(ItemSlotEmpty) {}
		try
		{
			EquipItem(tempItem1, a_ItemSlot2, a_Result);
		}
		catch (EquipItemEmpty) {}
		catch (ItemSlotEmpty) {}
	}
	catch (IncompatibleItem)
	{
		if (tempItem1)
		EquipItem(tempItem1, a_ItemSlot1, a_Result);
		if (tempItem2)
		EquipItem(tempItem2, a_ItemSlot2, a_Result);
		a_Result.message = "Swap failed\n";
		a_Result.success = false;
		throw IncompatibleItem();
	}	
}

std::string Player::GetStatus() const
{
	std::string status = "Player status:\n";
	for (auto iter : item_slot_map)
	{
		try
		{
			status += (ToString(iter.first) + ": " + iter.second->GetItemName() + "\n");
		}
		catch (ItemSlotEmpty)
		{
			status += (ToString(iter.first) + ": Empty\n");
		}
	}
	return status;
}

bool Player::CanInteract(PlayerItemSlots a_ItemSlot)
{
	auto tempptr = std::dynamic_pointer_cast<InteractibleItemSlot>(item_slot_map.at(a_ItemSlot));
	if (!tempptr)
	{
		throw CannotInteractWithSlot();
	}
	return true;
}