#include "stdafx.h"
#include "Player.h"
#include "Items/Item.h"
#include "Items/Gun.h"
#include "Items/Rock.h"
#include "Items/AmmoClip.h"
#include "Items/Hat.h"
#include "Items/FlashLight.h"

namespace EquipmentSystem
{
	void PrintHelp()
	{
		std::cout << "The Player has 3 available item slots (Leftarm, RightArm and Head)\nItems can be equipped to slots and Leftarm and RightArm can use the items\n";
		std::cout << "The available items are: Gun, AmmoClip FlashLight, Rock, and Hat\n\n";
		std::cout << "Available commands:\n";
		std::cout << "status - Displays the players itemslots\n";
		std::cout << "quit - Quits the game\n";
		std::cout << "help - Displays the insructions\n";
		std::cout << "[ItemSlot] equip [Item] - equips the item\n";
		std::cout << "[ItemSlot] unequip - Unequips the item held\n";
		std::cout << "[ItemSlot] get name - Gets name of held item\n";
		std::cout << "[ItemSlot] get ammo - If you are holding a gun displays the ammo left\n";
		std::cout << "[ItemSlot] reload - If you are holding a gun in one arm and an ammoclip in the other, it will reload the weapon\n";
		std::cout << "[ItemSlot] shoot - Shoots gun if you are holding one\n";
		std::cout << "[ItemSlot] swap [ItemSlot] - swaps held items\n";
		std::cout << "[ItemSlot] throw - Throw held item\n";
		std::cout << "[ItemSlot] toggle - Toggle item mode, usable on flashlight and gun\n";
		std::cout << "[ItemSlot] use - Uses the held items default action\n";
	}

	void SectionCommand(std::string a_Cmd, std::string& a_Word1, std::string& a_Word2, std::string& a_Word3)
	{
		std::string sub_str;
		std::vector<std::string> words;
		char search = ' ';
		size_t i, j;
		for (i = 0; i < a_Cmd.size(); i++)
		{
			if (a_Cmd.at(i) != search)
			{
				sub_str.insert(sub_str.end(), a_Cmd.at(i));
			}
			if (i == a_Cmd.size() - 1)
			{
				words.push_back(sub_str);
				sub_str.clear();
			}
			if (a_Cmd.at(i) == search)
			{
				words.push_back(sub_str);
				sub_str.clear();
			}
		}

		for (i = words.size() - 1; i > 0; i--)
		{
			if (words.at(i) == "")
			{
				words.erase(words.begin() + i);
			}
		}

		for (i = 0; i < words.size(); i++)
		{
			for (j = 0; j < words.at(i).size(); j++)
			{
				if (islower(words.at(i).at(j)))
				{
					words.at(i).at(j) = toupper(words.at(i).at(j));
				}
			}
		}
		if (words.size() == 1)
		{
			a_Word1 = words.at(0);
		}
		else if (words.size() == 2)
		{
			a_Word1 = words.at(0);
			a_Word2 = words.at(1);
		}
		else if (words.size() == 3)
		{
			a_Word1 = words.at(0);
			a_Word2 = words.at(1);
			a_Word3 = words.at(2);
		}
		else if (words.size() > 3)
		{
			std::cout << "Command too long. Only type a maximum of 3 words\n";
		}
	}

	bool Parser(std::string a_Word1, std::string a_Word2, std::string a_Word3, std::shared_ptr<Player> a_Player)
	{
		if (a_Word1 == "HELP")
		{
			PrintHelp();
			return true;
		}

		if (a_Word1 == "STATUS")
		{
			std::cout << "\n" << a_Player->GetStatus();
			return true;
		}

		//TODO map
		PlayerItemSlots selectedSlot;
		if (a_Word1 == "LEFTARM")
		{
			selectedSlot = PlayerItemSlots::LeftArmSlot;
		}
		else if (a_Word1 == "RIGHTARM")
		{
			selectedSlot = PlayerItemSlots::RightArmSlot;
		}
		else if (a_Word1 == "HEAD")
		{
			selectedSlot = PlayerItemSlots::HeadSlot;
		}
		else
		{
			throw InvalidItemSlot();
		}
		//TODO functie
		if (a_Word2 == "EQUIP")
		{
			if (a_Word3 == "GUN")
			{
				InteractResult result;
				a_Player->EquipItem(std::shared_ptr<EquipableItem>(std::make_shared<Gun>()), selectedSlot, result);
				std::cout << result.message;
				return result.success;
			}
			else if ("ROCK" == a_Word3)
			{
				InteractResult result;
				a_Player->EquipItem(std::shared_ptr<EquipableItem>(std::make_shared<Rock>()), selectedSlot, result);
				std::cout << result.message;
				return result.success;
			}
			else if ("AMMOCLIP" == a_Word3)
			{
				InteractResult result;
				a_Player->EquipItem(std::shared_ptr<EquipableItem>(std::make_shared<AmmoClip>()), selectedSlot, result);
				std::cout << result.message;
				return result.success;
			}
			else if ("HAT" == a_Word3)
			{
				InteractResult result;
				a_Player->EquipItem(std::shared_ptr<EquipableItem>(std::make_shared<Hat>()), selectedSlot, result);
				std::cout << result.message;
				return result.success;
			}
			else if ("FLASHLIGHT" == a_Word3)
			{
				InteractResult result;
				a_Player->EquipItem(std::shared_ptr<EquipableItem>(std::make_shared<FlashLight>()), selectedSlot, result);
				std::cout << result.message;
				return result.success;
			}
		}
		else if (a_Word2 == "RELOAD")
		{
			InteractResult result;
			a_Player->Reload(selectedSlot, result);
			std::cout << result.message;
			return result.success;
		}
		else if (a_Word2 == "SHOOT")
		{
			InteractResult result;
			a_Player->Shoot(selectedSlot, result);
			std::cout << result.message;
			return result.success;
		}
		else if (a_Word2 == "THROW")
		{
			InteractResult result;
			a_Player->Throw(selectedSlot, result);
			std::cout << result.message;
			return result.success;
		}
		else if (a_Word2 == "TOGGLE")
		{
			InteractResult result;
			a_Player->Toggle(selectedSlot, result);
			std::cout << result.message;
			return result.success;
		}
		else if (a_Word2 == "USE")
		{
			InteractResult result;
			a_Player->Use(selectedSlot, result);
			std::cout << result.message;
			return result.success;
		}
		else if (a_Word2 == "GET")
		{
			if (a_Word3 == "NAME")
			{
				std::cout << "The player has " << a_Player->GetItemNameOnSlot(selectedSlot) << " equipped\n";
				return true;
			}
			else if (a_Word3 == "AMMO")
			{
				std::cout << "The gun has " << a_Player->GetAmmo(selectedSlot) << " bullets left\n";
				return true;
			}
		}
		else if (a_Word2 == "UNEQUIP")
		{
			InteractResult result;
			a_Player->EquipItem(std::shared_ptr<EquipableItem>(std::make_shared<Gun>()), selectedSlot, result);
			std::cout << result.message;
			return result.success;

		}
		else if (a_Word2 == "SWAP")
		{
			if (a_Word3 == a_Word1)
			{
				"Cannot swap using the same itemslot\n";
				return false;
			}
			else if (a_Word3 == "LEFTARM")
			{
				InteractResult result;
				a_Player->SwapItems(selectedSlot, LeftArmSlot, result);
				std::cout << result.message;
				return result.success;
			}
			else if (a_Word3 == "RIGHTARM")
			{
				InteractResult result;
				a_Player->SwapItems(selectedSlot, RightArmSlot, result);
				std::cout << result.message;
				return result.success;
			}
			else if (a_Word3 == "HEAD")
			{
				InteractResult result;
				a_Player->SwapItems(selectedSlot, HeadSlot, result);
				std::cout << result.message;
				return result.success;
			}
		}
		return false;
	}
}

int main()
{
	std::shared_ptr<EquipmentSystem::Player> player(new EquipmentSystem::Player());
	std::string command;
	std::string word1;
	std::string word2;
	std::string word3;
	std::cout << "Welcome to this demonstration of the equipment system\n";
	EquipmentSystem::PrintHelp();
	while (true)
	{
		try
		{
			command.clear();
			word1.clear();
			word2.clear();
			word3.clear();
			std::cout << ">>> ";
			getline(std::cin, command);
			if (command == "")
			{
				continue;
			}
				EquipmentSystem::SectionCommand(command, word1, word2, word3);

			if (word1 == "QUIT")
			{
				break;
			}
			if (!EquipmentSystem::Parser(word1, word2, word3, player))
			{
				std::cout << "No valid command entered.\n";
			}
		}
		catch (const std::exception& e) {
			std::cout << e.what();
		}
	}
	return 0;
}