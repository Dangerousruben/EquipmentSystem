#pragma once
#include "items/item.h"
#include "items/shootable.h"
#include "items/toggle.h"


namespace EquipmentSystem
{
	class AmmoClip;

	//Holds AmmoClip and can shoot in single, automatic and burst mode
	class Gun : public EquipableItem, public Shootable, public Toggle
	{
	public:
		Gun();
		virtual ~Gun() {};

		//Toggles shoot state to single, automatic or burst
		void ToggleState(InteractResult& a_Result) override;

		//Resets ammo_clip pointer
		void Reload(std::shared_ptr<AmmoClip> a_AmmoClip);

		//Gets ammo left in ammo clip
		int GetAmmo() const;

		//Shoot function
		void Shoot(InteractResult& a_Result) override;


	private:
		//AmmoClip held
		std::shared_ptr<AmmoClip> ammo_clip;

		//Curren gun mode
		GunMode gun_mode = GunMode::Single;

		//Number of shots fired when in burst
		const int knumof_burst_shot = 3;

		//Fire rate in miliseconds
		const int kfire_rate = 100;

		//Switches gun mode to the new mode given
		void SwitchMode(InteractResult& a_Result, GunMode a_NewGunMode);

		//Calls FireShot 1 time
		void SingleShot(InteractResult& a_Result);

		//Calls FireShot repeatedly until the ammo clip is empty
		void AutomaticShot(InteractResult& a_Result);

		//Calls FireShot knumof_burst_shot times
		void BurstShot(InteractResult& a_Result);

		//Fires a shot
		void FireShot();
	};
}
