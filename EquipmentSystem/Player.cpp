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
	ItemSlotMap.insert(std::make_pair(HeadSlot, std::shared_ptr<ItemSlot>(std::make_shared<ItemSlot>(Head))));
	ItemSlotMap.insert(std::make_pair(PlayerItemSlots::LeftArmSlot, std::shared_ptr<ItemSlot>(std::make_shared<InteractibleItemSlot>(Arm))));
	ItemSlotMap.insert(std::make_pair(PlayerItemSlots::RightArmSlot, std::shared_ptr<ItemSlot>(std::make_shared<InteractibleItemSlot>(Arm))));
}

Player::~Player()
{

}


bool Player::EquipItem(const std::shared_ptr<Item> a_Item, const PlayerItemSlots a_ItemSlot)
{
	if (!a_Item)
	{
		throw EquipItemEmpty();
	}

	return ItemSlotMap.at(a_ItemSlot)->EquipItem(a_Item);
}

bool Player::UnEquipItem(const PlayerItemSlots a_ItemSlot)
{
	return ItemSlotMap.at(a_ItemSlot)->UnEquipItem();
}

std::string Player::GetItemNameOnSlot(PlayerItemSlots a_ItemSlot)
{
	return ItemSlotMap.at(a_ItemSlot)->GetItemName();
}

void Player::Interact(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	auto tempptr = dynamic_cast<InteractibleItemSlot*>(ItemSlotMap.at(a_ItemSlot).get());
	if (!tempptr)
	{
		throw CannotInteractWithSlot();
	}
	else
	{
		tempptr->Interact(a_Result);
		ResolveInteract(a_Result, a_ItemSlot);
	}
}

void Player::Reload(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	auto tempptr = dynamic_cast<InteractibleItemSlot*>(ItemSlotMap.at(a_ItemSlot).get());
	if (!tempptr)
	{
		throw CannotInteractWithSlot();
	}
	auto tempGunptr = std::dynamic_pointer_cast<Gun>((tempptr->item));
	if (!tempGunptr)
	{
		throw NoGunEquipped();
	}

	PlayerItemSlots otherArm;
	switch (a_ItemSlot)
	{
	case LeftArmSlot:
		otherArm = RightArmSlot;
	case RightArmSlot:
		otherArm = LeftArmSlot;
	default:
		break;
	}


	auto tempAmmoClipptr = std::dynamic_pointer_cast<AmmoClip>(ItemSlotMap.at(otherArm).get()->item);
	if (!tempAmmoClipptr)
	{
		throw NoAmmoClipEquipped();
	}

	tempGunptr->Reload(tempAmmoClipptr);
	UnEquipItem(otherArm);
	a_Result.Message = "I reloaded my gun\n";
	a_Result.Success = true;
}

int Player::GetAmmo(const PlayerItemSlots a_ItemSlot)
{
	std::weak_ptr<Gun> tempptr = std::dynamic_pointer_cast<Gun>(ItemSlotMap.at(a_ItemSlot).get()->item);
	if (!tempptr.expired())
	{
		return tempptr.lock()->GetAmmo();
	}
	else
	{
		throw NoGunEquipped();
	}
}

void Player::Shoot(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	auto tempptr = dynamic_cast<InteractibleItemSlot*>(ItemSlotMap.at(a_ItemSlot).get());
	if (!tempptr)
	{
		throw CannotInteractWithSlot();
	}
	auto tempShootPtr = std::dynamic_pointer_cast<IGunInterface>(tempptr->item);
	if (tempShootPtr)
	{
		tempShootPtr->Shoot(a_Result);
	}
}

void Player::Throw(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	if (CanInteract(a_ItemSlot))
	{
		std::weak_ptr<Item> tempItemPtr = ItemSlotMap.at(a_ItemSlot).get()->item;
		if (!tempItemPtr.expired())
		{
			tempItemPtr.lock()->Throw(a_Result);
			if (a_Result.Success)
			{
				a_Result.Unequip = UnEquipItem(a_ItemSlot);
			}
		}
	}
}

void Player::TurnOnOff(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	if (CanInteract(a_ItemSlot))
	{
		std::weak_ptr<IButtonInterface> tempButtonPtr = std::dynamic_pointer_cast<IButtonInterface>(ItemSlotMap.at(a_ItemSlot).get()->item);
		if (!tempButtonPtr.expired())
		{
			tempButtonPtr.lock()->PressButton(a_Result);
		}
	}
}

void Player::Use(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	auto tempShootPtr = std::dynamic_pointer_cast<IGunInterface>(ItemSlotMap.at(a_ItemSlot).get()->item);
	if (tempShootPtr)
	{
		Shoot(a_ItemSlot, a_Result);
	}
	auto tempAmmoPtr = std::dynamic_pointer_cast<AmmoClip>(ItemSlotMap.at(a_ItemSlot).get()->item);
	if (tempAmmoPtr)
	{
		Reload(a_ItemSlot, a_Result);
	}
	auto rockPtr = std::dynamic_pointer_cast<Rock>(ItemSlotMap.at(a_ItemSlot).get()->item);
	if (rockPtr)
	{
		Throw(a_ItemSlot, a_Result);
	}
	auto flashLightPtr = std::dynamic_pointer_cast<FlashLight>(ItemSlotMap.at(a_ItemSlot).get()->item);
	if (flashLightPtr)
	{
		TurnOnOff(a_ItemSlot, a_Result);
	}
}

void Player::ToggleGunMode(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	if (CanInteract(a_ItemSlot))
	{
		std::weak_ptr<IGunInterface> tempGunPtr = std::dynamic_pointer_cast<IGunInterface>(ItemSlotMap.at(a_ItemSlot).get()->item);
		if (!tempGunPtr.expired())
		{
			tempGunPtr.lock()->ToggleMode(a_Result);
		}
	}
}

bool Player::CanInteract(const PlayerItemSlots a_ItemSlot)
{
	std::weak_ptr<InteractibleItemSlot> tempptr = std::dynamic_pointer_cast<InteractibleItemSlot>(ItemSlotMap.at(a_ItemSlot));
	if (tempptr.expired())
	{
		throw CannotInteractWithSlot();
	}
	return true;
}

void Player::ResolveInteract(InteractResult& a_Result, const PlayerItemSlots a_ItemSlot)
{
	if (!a_Result.Success)
	{
		throw InteractionFailed(a_Result.Message);
	}
	else
	{
		if (a_Result.Unequip)
		{
			a_Result.Unequip = UnEquipItem(a_ItemSlot);
		}
		else if (a_Result.Consume)
		{
			std::weak_ptr<ConsumableItem> tempptr = std::dynamic_pointer_cast<ConsumableItem>(ItemSlotMap.at(a_ItemSlot));
			if (tempptr.expired())
			{
				PlayerItemSlots otherArm;
				switch (a_ItemSlot)
				{
				case LeftArmSlot:
					otherArm = RightArmSlot;
				case RightArmSlot:
					otherArm = LeftArmSlot;
				default:
					break;
				}
				tempptr.lock()->ConsumeItem(ItemSlotMap.at(otherArm)->item);
			}
			else
			{
				throw ItemCannotBeConsumed(ItemSlotMap.at(a_ItemSlot)->GetItemName());
			}
		}
	}
}