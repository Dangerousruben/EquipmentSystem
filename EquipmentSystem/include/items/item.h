#pragma once
#include "player.h"

namespace EquipmentSystem
{
	enum ItemEquipType
	{
		Any,
		Head,
		Torso,
		Arm,
		Leg
	};


	//Whenever an interaction is made an instance of the struct is send as a reference in the function
	struct InteractResult
	{
		bool success = false;
		std::string message = "";
		int numof_shots_fired = 0;
	};

	//Standard item class
	class Item
	{
	public:
		Item() {};
		virtual ~Item() {};

		std::string GetName() { return name; };

	protected:
		std::string name = "Item";

	};

	//Items that can be equipped
	class EquipableItem : public Item
	{
	public:
		EquipableItem() {};
		virtual ~EquipableItem() {};

		//A list of compatible equip types
		std::vector<ItemEquipType> compatible_equip_types;

		//Throws the item away
		virtual void Throw(InteractResult& a_Result);

	};
}
