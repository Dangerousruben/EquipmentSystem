#pragma once
#include "Item.h"

class Gun;

struct Ammo
{
	const int AmmoCapacity;
	int CurrentAmmo;

	Ammo(int a_AmmoCapacity)
		: AmmoCapacity(a_AmmoCapacity), CurrentAmmo(AmmoCapacity)
	{

	}
};

class AmmoClip : public ConsumableItem
{
	friend Gun;
public:
	AmmoClip();
	virtual ~AmmoClip();

	void Interact(InteractResult& a_Result) override;

	bool CanBeConsumedBy(std::weak_ptr<Item> a_Item) override;

	bool ConsumeItem(std::weak_ptr<Item> a_Item) override;

private:
	Ammo m_Ammo;
};
