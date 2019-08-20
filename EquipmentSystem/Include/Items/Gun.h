#pragma once
#include "Items/Item.h"
#include "Items/GunInterface.h"
#include "Items/ToggleInterface.h"


namespace EquipmentSystem
{
	class AmmoClip;

	class Gun : public EquipableItem, public GunInterface, public ToggleInterface
	{
	public:
		Gun();
		virtual ~Gun();

		void ToggleState(InteractResult& a_Result) override;

		void Reload(std::shared_ptr<AmmoClip> a_AmmoClip);

		int GetAmmo() const;

		void Shoot(InteractResult& a_Result) override;


	private:
		std::shared_ptr<AmmoClip> ammo_clip;

		GunMode gun_mode = GunMode::Single;

		const int numof_burst_shot = 3;

		const int fire_rate = 100;

		void SwitchMode(InteractResult& a_Result, GunMode a_NewGunMode);

		void SingleShot(InteractResult& a_Result);

		void AutomaticShot(InteractResult& a_Result);

		void BurstShot(InteractResult& a_Result);

		void FireShot();
	};
}
