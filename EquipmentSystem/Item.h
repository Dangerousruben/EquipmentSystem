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

	virtual void Interact(InteractResult& a_Result) = 0;

	virtual std::string GetName() { return Name; };

	std::vector<ItemEquipType> CompatibleEquipTypes;

	virtual void Throw(InteractResult& a_Result);

protected:
	std::string Name = "Item";

	int ThrowSpeed = 10;
};

class ConsumableItem : public Item
{
public:
	ConsumableItem();
	virtual ~ConsumableItem();

	virtual bool CanBeConsumedBy(std::weak_ptr<Item> a_Item) = 0;

	virtual bool ConsumeItem(std::weak_ptr<Item> a_Item) = 0;

private:

};

class ItemConsumer : public Item
{
public:
	ItemConsumer();
	virtual ~ItemConsumer();

	virtual bool CanConsume(std::weak_ptr<Item> a_Item) = 0;

	virtual bool ConsumeItem(Item* a_Item) = 0;

private:

};