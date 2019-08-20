#pragma once
#include "Player.h"

enum ItemEquipType
{
	Any,
	Head,
	Torso,
	Arm,
	Leg
};


struct InteractResult 
{
	bool success = false;
	bool unequip = false;
	std::string message = "";
	bool consume = false;
	int numof_shots_fired = 0;
};

class Item
{
public:
	Item();
	virtual ~Item();

	std::string GetName() { return name; };

protected:
	std::string name = "Item";

};

class EquipableItem : public Item
{
public:
	EquipableItem();
	virtual ~EquipableItem();

	std::vector<ItemEquipType> compatible_equip_types;

	virtual void Throw(InteractResult& a_Result);

};