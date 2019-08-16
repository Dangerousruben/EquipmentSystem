#pragma once
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>

enum ItemEquipType
{
	Any,
	Head,
	Torso,
	Arm,
	Leg,
	None
};


struct InteractResult 
{
	bool Success = false;
	bool Unequip = false;
	std::string Message = "";

	bool Consume = false;

	int ThrowSpeed = 0;

	int NumOfShotsFired = 0;
};


class Item
{
public:
	Item();
	virtual ~Item();

	virtual std::string GetName() { return Name; };

	std::vector<ItemEquipType> CompatibleEquipTypes;

	virtual void Throw(InteractResult& a_Result);

protected:
	std::string Name = "Item";

	int ThrowSpeed = 10;
};