#include "stdafx.h"
#include "items/gun.h"
#include "items/ammoClip.h"

namespace EquipmentSystem
{
	Gun::Gun()
	{
		compatible_equip_types = { ItemEquipType::Arm };
		name = "Gun";
		ammo_clip = std::make_shared<AmmoClip>();
	}

	void Gun::SwitchMode(InteractResult& a_Result, GunMode a_NewGunMode)
	{
		gun_mode = a_NewGunMode;
		a_Result.success = true;
		a_Result.message = "Switched mode to " + ToString(a_NewGunMode) + "\n";
	}

	void Gun::ToggleState(InteractResult& a_Result)
	{
		switch (gun_mode)
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
		}
	}


	void Gun::Reload(std::shared_ptr<AmmoClip> a_AmmoClip)
	{
		if (!a_AmmoClip)
		{
			throw NoAmmoClipEquipped();
		}
		ammo_clip.swap(a_AmmoClip);
	}

	int Gun::GetAmmo() const
	{
		return ammo_clip->GetCurrentAmmo();
	}

	void Gun::Shoot(InteractResult& a_Result)
	{
		switch (gun_mode)
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
		}

		a_Result.message += std::to_string(a_Result.numof_shots_fired) + " shots were successfully fired\n";

		a_Result.success = true;
	}

	void Gun::SingleShot(InteractResult& a_Result)
	{
		a_Result.message += "Fire shot in single mode\n";
		try
		{
			FireShot();
		}
		catch (OutOfAmmo)
		{
			a_Result.message += "Out of ammo\n";
		}
		a_Result.numof_shots_fired++;
		a_Result.message += "Shot fired\n";
	}


	void Gun::AutomaticShot(InteractResult& a_Result)
	{
		std::cout << "Fire shots in automatic mode\n";
		try
		{
			while (true)
			{
				FireShot();
				a_Result.numof_shots_fired++;
				// Temporary: just print to stdout to animate the output in a fun way. Should be improved in realistic implementation.
				std::cout << "Shot fired\n";
				std::this_thread::sleep_for(std::chrono::milliseconds(kfire_rate));
			}
		}
		catch (OutOfAmmo)
		{
			a_Result.message += "Out of ammo\n";
		}
	}

	void Gun::BurstShot(InteractResult& a_Result)
	{
		a_Result.message += "Fire " + std::to_string(knumof_burst_shot) + " shots in burst mode\n";
		try
		{
			for (int i = 0; i < knumof_burst_shot; i++)
			{
				FireShot();
				a_Result.numof_shots_fired++;
				// Temporary: just print to stdout to animate the output in a fun way. Should be improved in realistic implementation.
				std::this_thread::sleep_for(std::chrono::milliseconds(kfire_rate));
				std::cout << "Shot fired\n";

			}
		}
		catch (OutOfAmmo)
		{
			a_Result.message += "Out of ammo\n";
		}
	}

	void Gun::FireShot()
	{
		ammo_clip->DispenseBullet();
	}
}
