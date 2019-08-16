#pragma once
#include "Item.h"
#include "GunInterface.h"



class AmmoClip;

class Gun : public ItemConsumer, public IGunInterface
{
public:
	Gun();
	virtual ~Gun();

	virtual void Interact(InteractResult& a_Result) override;

	virtual std::string GetName() override { return "Gun"; };

	void ToggleMode(InteractResult& a_Result) override;
	
	virtual void Reload(std::shared_ptr<AmmoClip> a_AmmoClip);

	virtual bool CanConsume(std::weak_ptr<Item> a_Item) override;

	virtual bool ConsumeItem(Item* a_Item) override;

	int GetAmmo();

	virtual void Shoot(InteractResult& a_Result) override;


protected:
	//TODO Make struct rather than class
	std::shared_ptr<AmmoClip> m_AmmoClip;

	GunMode m_GunMode = GunMode::Single;

	int NumOfBurstShot = 3;

	void SwitchMode(InteractResult& a_Result, GunMode a_NewGunMode) override;

private:
	virtual void SingleShot(InteractResult& a_Result);

	virtual void AutomaticShot(InteractResult& a_Result);

	virtual void BurstShot(InteractResult& a_Result);

	virtual void FireShot();
};

