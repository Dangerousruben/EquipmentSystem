#include "stdafx.h"
#include "Gun.h"
#include "AmmoClip.h"

Gun::Gun()
{
	CompatibleEquipTypes = { ItemEquipType::Arm };
	Name = "Gun";
	m_AmmoClip = std::make_shared<AmmoClip>();
}

Gun::~Gun() 
{
}

void Gun::Interact(InteractResult& a_Result)
{
	if (m_AmmoClip->m_Ammo.CurrentAmmo > 0)
	{
		m_AmmoClip->m_Ammo.CurrentAmmo--;
		a_Result.Success = true;
		a_Result.Unequip = false;
		a_Result.Message = "Pew, pew, pew\n";
	}
	else
	{
		throw OutOfAmmo();
	}
}

void Gun::Reload(std::shared_ptr<AmmoClip> a_AmmoClip)
{
	if (a_AmmoClip)
	{
		m_AmmoClip.swap(a_AmmoClip);
	}
}

bool Gun::CanConsume(std::weak_ptr<Item> a_Item)
{
	return false;
}

bool Gun::ConsumeItem(Item* a_Item)
{
	//auto tempptr = dynamic_cast<AmmoClip*>(a_Item);
	//if (tempptr)
	{
		//Reload(tempptr);
	}
	return false;
}

int Gun::GetAmmo()
{
	return m_AmmoClip->m_Ammo.CurrentAmmo;
}

void Gun::Shoot(InteractResult& a_Result)
{
	if (m_AmmoClip->m_Ammo.CurrentAmmo > 0)
	{
		m_AmmoClip->m_Ammo.CurrentAmmo--;
		a_Result.Success = true;
		a_Result.Message = "You have fired 1 shot\n";
	}
	else
	{
		throw OutOfAmmo();
	}
}
