#pragma once
#include <iostream>
#include <string>
#include <map>


class InteractibleItemSlot;
class ItemSlot;
class Item;

struct InteractResult;

enum PlayerItemSlots
{
	LeftArmSlot,
	RightArmSlot,
	HeadSlot
};

class Player
{
public:
	Player();
	~Player();

	bool EquipItem(const std::shared_ptr<Item> a_Item, const PlayerItemSlots a_ItemSlot);

	bool UnEquipItem(const PlayerItemSlots a_ItemSlot);

	std::string GetItemNameOnSlot(const PlayerItemSlots a_ItemSlot);

	void Interact(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

	void Reload(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

	int GetAmmo(const PlayerItemSlots a_ItemSlot);

	void Shoot(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

	void Throw(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

	void TurnOnOff(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

	void Use(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

	void ToggleGunMode(const PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

private:
	std::map<PlayerItemSlots, std::shared_ptr<ItemSlot>> ItemSlotMap;

	bool CanInteract(const PlayerItemSlots a_ItemSlot);

	void ResolveInteract(InteractResult& a_Result, const PlayerItemSlots a_ItemSlot);
};