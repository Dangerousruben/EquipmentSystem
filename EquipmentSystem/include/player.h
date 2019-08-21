#pragma once

namespace EquipmentSystem
{
	class InteractibleItemSlot;
	class ItemSlot;
	class Item;
	class EquipableItem;

	struct InteractResult;

	enum PlayerItemSlots
	{
		LeftArmSlot,
		RightArmSlot,
		HeadSlot
	};

	static std::string ToString(const PlayerItemSlots a_ItemSlot)
	{
		switch (a_ItemSlot)
		{
		case LeftArmSlot:
			return "LeftArmSlot";
		case RightArmSlot:
			return "RightArmSlot";
		case HeadSlot:
			return "HeadSlot";
		default:
			return "";
		}
	}

	//The player, can interact with items
	class Player
	{
	public:
		Player();
		virtual ~Player() {};

		//Equip an item to the given item slot
		void EquipItem(const std::shared_ptr<EquipableItem> a_Item, PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

		//Unequips item on the given slot
		void UnEquipItem(PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

		//Gets name of item
		std::string GetItemNameOnSlot(PlayerItemSlots a_ItemSlot) const;

		//If holding a gun in one hand and a AmmoClip in the other, reload
		void Reload(PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

		//Gets ammo in the gun
		int GetAmmo(PlayerItemSlots a_ItemSlot);

		//Shoots the item if it has shootable interface
		void Shoot(PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

		//Throws the item away
		void Throw(PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

		//Toggles the items state if it has toggle interface
		void ToggleState(PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

		//Uses items default action
		void Use(PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

		//Swap items
		void SwapItems(PlayerItemSlots a_ItemSlot1, PlayerItemSlots a_ItemSlot2, InteractResult& a_Result);

		//Gets the items on the item slots
		std::string GetStatus() const;

	private:
		//Used to quickly search the correct ItemSlot with the enum
		std::map<PlayerItemSlots, std::shared_ptr<ItemSlot>> item_slot_map;

		//Whether the itemslot is an interactibleitemslot
		bool CanInteract(PlayerItemSlots a_ItemSlot);
	};
}
