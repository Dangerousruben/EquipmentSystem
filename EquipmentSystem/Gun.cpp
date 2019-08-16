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

void Gun::SwitchMode(InteractResult& a_Result, GunMode a_NewGunMode)
{
	m_GunMode = a_NewGunMode;
	a_Result.Success = true;
	a_Result.Message = "Switched mode to " + ToString(a_NewGunMode) + "\n";
}

void Gun::ToggleMode(InteractResult& a_Result)
{
	switch (m_GunMode)
	{
	case Single:
		SwitchMode(a_Result, Automatic);
		break;
	case Automatic:
		SwitchMode(a_Result, Burst);
		break;
	case Burst:
		SwitchMode(a_Result, Single);
		break;
	default:
		break;
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
	switch (m_GunMode)
	{
	case Single:
		SingleShot(a_Result);
		break;
	case Automatic:
		AutomaticShot(a_Result);
		break;
	case Burst:
		BurstShot(a_Result);
		break;
	default:
		break;
	}
	if (a_Result.NumOfShotsFired == 1)
	{
		a_Result.Message += std::to_string(a_Result.NumOfShotsFired) + " shot was successfully fired\n";
	}
	else
	{
		a_Result.Message += std::to_string(a_Result.NumOfShotsFired) + " shots were successfully fired\n";
	}
	a_Result.Success = true;
}

void Gun::SingleShot(InteractResult& a_Result)
{
	a_Result.Message += "Fire shot in single mode\n";
	try
	{
		FireShot();
	}
	catch (OutOfAmmo)
	{
		a_Result.Message += "Out of ammo\n";
	}
	a_Result.NumOfShotsFired++;
	a_Result.Message += "Shot fired\n";
}


//TODO make better or remove
void Gun::AutomaticShot(InteractResult& a_Result)
{
	std::cout << "Fire shots in automatic mode\n";
	try
	{
		while (true)
		{
			FireShot();
			a_Result.NumOfShotsFired++;
			std::cout << "Shot fired\n";
			Sleep(100);
		}
	}
	catch (OutOfAmmo)
	{
		a_Result.Message += "Out of ammo\n";
	}
}

void Gun::BurstShot(InteractResult& a_Result)
{
	a_Result.Message += "Fire " + std::to_string(NumOfBurstShot) + " shots in burst mode\n";
	for (int i = 0; i < NumOfBurstShot; i++)
	{
		try
		{
			FireShot();
		}
		catch (OutOfAmmo)
		{
			a_Result.Message += "Out of ammo\n";
			continue;
		}
		a_Result.NumOfShotsFired++;
		a_Result.Message += "Shot fired\n";
	}
}

void Gun::FireShot()
{
	if (m_AmmoClip->m_Ammo.CurrentAmmo > 0)
	{
		m_AmmoClip->m_Ammo.CurrentAmmo--;
	}
	else
	{
		throw OutOfAmmo();
	}
}
