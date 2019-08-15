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

//	virtual void ModeSwitch() override;
	
	virtual void Reload(std::shared_ptr<AmmoClip> a_AmmoClip);

	virtual bool CanConsume(std::weak_ptr<Item> a_Item) override;

	virtual bool ConsumeItem(Item* a_Item) override;

	int GetAmmo();

	virtual void Shoot(InteractResult& a_Result) override;


protected:
	std::shared_ptr<AmmoClip> m_AmmoClip;
};

