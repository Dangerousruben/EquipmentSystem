#include "stdafx.h"
#include "Player.h"
#include "Item.h"
#include "Gun.h"
#include "Rock.h"
#include "AmmoClip.h"
#include "Hat.h"
#include "FlashLight.h"

namespace TextAdventure
{
	void PrintHelp()
	{
		std::cout << "Welcome to this demonstration of the equipment system\nThe Player has 3 available item slots (Leftarm, RightArm and Head)\n";
		std::cout << "Items can be equipped to slots and Leftarm and RightArm can use the items\n";
		std::cout << "The available items are: Gun, AmmoClip FlashLight, Rock, and Hat\n";
		std::cout << "Available commands:\nQuit - Quits the game\nHelp - Displays this message\n[ItemSlot] Equip [Item] - equips the item\n";
		std::cout << "[ItemSlot] Unequip - Unequips the item held\n[ItemSlot] Get Name - Gets name of held item\n[ItemSlot] Interact - Uses the held item\n";
		std::cout << "[ItemSlot] Shoot - Shoots gun if you are holding one\n[ItemSlot] ToggleGunMode - If you are holding a gun toggle the firing mode\n";
		std::cout << "[ItemSlot] Reload - If you are holding a gun in one arm and an ammoclip in the other, it will reload the weapon\n";
		std::cout << "[ItemSlot] get ammo - If you are holding a gun displays the ammo left\n[ItemSlot] Throw - Throw held item\n";
		std::cout << "[ItemSlot] TurnOnOff - Turns switch on item on/off\n[ItemSlot] swap [ItemSlot] - swaps held items\n";
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

		if (a_Word2 == "EQUIP")
		{
			if (a_Word3 == "GUN")
			{
				if (a_Player->EquipItem(std::shared_ptr<Item>(std::make_shared<Gun>()), selectedSlot))
				{
					std::cout << "Player has equipped the Gun\n";
					return true;
				}
			}
			else if ("ROCK" == a_Word3)
			{
				if (a_Player->EquipItem(std::shared_ptr<Item>(std::make_shared<Rock>()), selectedSlot))
				{
					std::cout << "Player has equipped the Rock\n";
					return true;
				}
			}
			else if ("AMMOCLIP" == a_Word3)
			{
				if (a_Player->EquipItem(std::shared_ptr<Item>(std::make_shared<AmmoClip>()), selectedSlot))
				{
					std::cout << "Player has equipped the AmmoClip\n";
					return true;
				}
			}
			else if ("HAT" == a_Word3)
			{
				if (a_Player->EquipItem(std::shared_ptr<Item>(std::make_shared<Hat>()), selectedSlot))
				{
					std::cout << "Player has equipped the Hat\n";
					return true;
				}
			}
			else if ("FLASHLIGHT" == a_Word3)
			{
				if (a_Player->EquipItem(std::shared_ptr<Item>(std::make_shared<FlashLight>()), selectedSlot))
				{
					std::cout << "Player has equipped the FlashLight\n";
					return true;
				}
			}
		}
		else if (a_Word2 == "RELOAD")
		{
			InteractResult result;
			a_Player->Reload(selectedSlot, result);
			std::cout << result.Message;
			return result.Success;
		}
		else if (a_Word2 == "SHOOT")
		{
			InteractResult result;
			a_Player->Shoot(selectedSlot, result);
			std::cout << result.Message;
			return result.Success;
		}
		else if (a_Word2 == "THROW")
		{
			InteractResult result;
			a_Player->Throw(selectedSlot, result);
			std::cout << result.Message;
			return result.Success;
		}
		else if (a_Word2 == "TURNONOFF")
		{
			InteractResult result;
			a_Player->TurnOnOff(selectedSlot, result);
			std::cout << result.Message;
			return result.Success;
		}
		else if (a_Word2 == "TOGGLEGUNMODE")
		{
			InteractResult result;
			a_Player->ToggleGunMode(selectedSlot, result);
			std::cout << result.Message;
			return result.Success;
		}
		else if (a_Word2 == "USE")
		{
			InteractResult result;
			a_Player->Use(selectedSlot, result);
			std::cout << result.Message;
			return result.Success;
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
			if (a_Player->UnEquipItem(selectedSlot))
			{
				std::cout << "The selected item slot has been unequipped its item\n";
				return true;
			}

		}
		else if (a_Word2 == "SWAP")
		{
			if (a_Word3 == "LEFTARM")
			{
				a_Player->SwapItems(selectedSlot, LeftArmSlot);
				return true;
			}
			else if (a_Word3 == "RIGHTARM")
			{
				a_Player->SwapItems(selectedSlot, RightArmSlot);
				return true;
			}
			else if (a_Word3 == "HEAD")
			{
				a_Player->SwapItems(selectedSlot, HeadSlot);
				return true;
			}
		}
		return false;
	}
}

int main()
{
	std::vector<std::string> AvailableItems = { "Gun", "Rock" };
	std::shared_ptr<Player> player(new Player());
	std::string command;
	std::string word1;
	std::string word2;
	std::string word3;
	TextAdventure::PrintHelp();
	while (word1 != "QUIT")
	{
		try
		{
			command.clear();
			word1.clear();
			word2.clear();
			word3.clear();
			getline(std::cin, command);
			if (command != "")
			{
				TextAdventure::SectionCommand(command, word1, word2, word3);

				if (word1 != "QUIT")
				{
					if (!TextAdventure::Parser(word1, word2, word3, player))
					{
						std::cout << "No valid command entered.\n";
					}
				}
			}
		}
		catch (const std::exception& e) {
			std::cout << e.what();
		}
	}
	return 0;
}