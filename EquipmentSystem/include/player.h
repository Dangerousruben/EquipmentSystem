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

	class Player
	{
	public:
		Player();
		virtual ~Player() {};

		void EquipItem(const std::shared_ptr<EquipableItem> a_Item, PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

		void UnEquipItem(PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

		std::string GetItemNameOnSlot(PlayerItemSlots a_ItemSlot) const;

		void Reload(PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

		int GetAmmo(PlayerItemSlots a_ItemSlot);

		void Shoot(PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

		void Throw(PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

		void Toggle(PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

		void Use(PlayerItemSlots a_ItemSlot, InteractResult& a_Result);

		void SwapItems(PlayerItemSlots a_ItemSlot1, PlayerItemSlots a_ItemSlot2, InteractResult& a_Result);

		InteractResult* Test();

		std::string GetStatus() const;

	private:
		std::map<PlayerItemSlots, std::shared_ptr<ItemSlot>> item_slot_map;

		bool CanInteract(PlayerItemSlots a_ItemSlot);
	};
}
