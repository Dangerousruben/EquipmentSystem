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
	m_ItemSlotMap.insert(std::make_pair(HeadSlot, std::shared_ptr<ItemSlot>(std::make_shared<ItemSlot>(Head))));
	m_ItemSlotMap.insert(std::make_pair(PlayerItemSlots::LeftArmSlot, std::shared_ptr<ItemSlot>(std::make_shared<InteractibleItemSlot>(Arm))));
	m_ItemSlotMap.insert(std::make_pair(PlayerItemSlots::RightArmSlot, std::shared_ptr<ItemSlot>(std::make_shared<InteractibleItemSlot>(Arm))));
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
	if (m_ItemSlotMap.at(a_ItemSlot)->HasItemEquipped())
	{
		m_ItemSlotMap.at(a_ItemSlot)->UnEquipItem();
	}

	return m_ItemSlotMap.at(a_ItemSlot)->EquipItem(a_Item);
}

bool Player::UnEquipItem(const PlayerItemSlots a_ItemSlot)
{
	return m_ItemSlotMap.at(a_ItemSlot)->UnEquipItem();
}

std::string Player::GetItemNameOnSlot(PlayerItemSlots a_ItemSlot)
{
	return m_ItemSlotMap.at(a_ItemSlot)->GetItemName();
}

void Player::Reload(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	if (CanInteract(a_ItemSlot))
	{
		PlayerItemSlots otherArm = (a_ItemSlot == RightArmSlot) ? LeftArmSlot : RightArmSlot;
		auto tempGunptr = std::dynamic_pointer_cast<Gun>((m_ItemSlotMap.at(a_ItemSlot)->m_Item));
		if (!tempGunptr)
		{
			tempGunptr = std::dynamic_pointer_cast<Gun>((m_ItemSlotMap.at(otherArm)->m_Item));
			if (!tempGunptr)
			{
				throw NoGunEquipped();
			}
		}


		auto tempAmmoClipptr = std::dynamic_pointer_cast<AmmoClip>(m_ItemSlotMap.at(otherArm)->m_Item);
		if (!tempAmmoClipptr)
		{
			tempAmmoClipptr = std::dynamic_pointer_cast<AmmoClip>((m_ItemSlotMap.at(a_ItemSlot)->m_Item));
			if (!tempAmmoClipptr)
			{
				throw NoAmmoClipEquipped();
			}
		}

		tempGunptr->Reload(tempAmmoClipptr);
		UnEquipItem(otherArm);
		a_Result.Message = "I reloaded my gun\n";
		a_Result.Success = true;
	}
}

int Player::GetAmmo(const PlayerItemSlots a_ItemSlot)
{
	std::weak_ptr<Gun> tempptr = std::dynamic_pointer_cast<Gun>(m_ItemSlotMap.at(a_ItemSlot).get()->m_Item);
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
	auto tempptr = dynamic_cast<InteractibleItemSlot*>(m_ItemSlotMap.at(a_ItemSlot).get());
	if (!tempptr)
	{
		throw CannotInteractWithSlot();
	}
	auto tempShootPtr = std::dynamic_pointer_cast<IGunInterface>(tempptr->m_Item);
	if (tempShootPtr)
	{
		tempShootPtr->Shoot(a_Result);
	}
}

void Player::Throw(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	if (CanInteract(a_ItemSlot))
	{
		std::weak_ptr<Item> tempItemPtr = m_ItemSlotMap.at(a_ItemSlot).get()->m_Item;
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
		std::weak_ptr<IButtonInterface> tempButtonPtr = std::dynamic_pointer_cast<IButtonInterface>(m_ItemSlotMap.at(a_ItemSlot).get()->m_Item);
		if (!tempButtonPtr.expired())
		{
			tempButtonPtr.lock()->PressButton(a_Result);
		}
	}
}

void Player::Use(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	auto tempShootPtr = std::dynamic_pointer_cast<IGunInterface>(m_ItemSlotMap.at(a_ItemSlot).get()->m_Item);
	if (tempShootPtr)
	{
		Shoot(a_ItemSlot, a_Result);
	}
	auto tempAmmoPtr = std::dynamic_pointer_cast<AmmoClip>(m_ItemSlotMap.at(a_ItemSlot).get()->m_Item);
	if (tempAmmoPtr)
	{
		Reload(a_ItemSlot, a_Result);
	}
	auto tempRockPtr = std::dynamic_pointer_cast<Rock>(m_ItemSlotMap.at(a_ItemSlot).get()->m_Item);
	if (tempRockPtr)
	{
		Throw(a_ItemSlot, a_Result);
	}
	auto tempFlashLightPtr = std::dynamic_pointer_cast<FlashLight>(m_ItemSlotMap.at(a_ItemSlot).get()->m_Item);
	if (tempFlashLightPtr)
	{
		TurnOnOff(a_ItemSlot, a_Result);
	}
}

void Player::ToggleGunMode(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result)
{
	if (CanInteract(a_ItemSlot))
	{
		std::weak_ptr<IGunInterface> tempGunPtr = std::dynamic_pointer_cast<IGunInterface>(m_ItemSlotMap.at(a_ItemSlot).get()->m_Item);
		if (!tempGunPtr.expired())
		{
			tempGunPtr.lock()->ToggleMode(a_Result);
		}
	}
}

void Player::SwapItems(const PlayerItemSlots a_ItemSlot1, const PlayerItemSlots a_ItemSlot2)
{
	auto tempItem1 = m_ItemSlotMap.at(a_ItemSlot1)->m_Item;
	auto tempItem2 = m_ItemSlotMap.at(a_ItemSlot2)->m_Item;
	try
	{
		try
		{
			EquipItem(tempItem2, a_ItemSlot1);
		}
		catch (EquipItemEmpty) {}
		catch(ItemSlotEmpty) {}
		try
		{
			EquipItem(tempItem1, a_ItemSlot2);
		}
		catch (EquipItemEmpty) {}
		catch (ItemSlotEmpty) {}
	}
	catch (IncompatibleItem)
	{
		if (tempItem1)
		EquipItem(tempItem1, a_ItemSlot1);
		if (tempItem2)
		EquipItem(tempItem2, a_ItemSlot2);
		throw IncompatibleItem();
	}	
}

bool Player::CanInteract(const PlayerItemSlots a_ItemSlot)
{
	std::weak_ptr<InteractibleItemSlot> tempptr = std::dynamic_pointer_cast<InteractibleItemSlot>(m_ItemSlotMap.at(a_ItemSlot));
	if (tempptr.expired())
	{
		throw CannotInteractWithSlot();
	}
	return true;
}