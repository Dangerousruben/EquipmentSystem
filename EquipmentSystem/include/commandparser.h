#pragma once
#include "player.h"

namespace EquipmentSystem
{
	//The parser used for the console
	class CommandParser
	{
	public:
		CommandParser() {};
		~CommandParser() {};

		//Prints the help message
		void PrintHelp();

		//Separates the single command into 3 words
		void SectionCommand(std::string a_Cmd, std::string& a_Word1, std::string& a_Word2, std::string& a_Word3);

		//Parse and execute the correct command
		void Parse(std::string a_Word1, std::string a_Word2, std::string a_Word3, std::shared_ptr<Player> a_Player);

	private:
		//Gets the correct itemslot from word 1 
		PlayerItemSlots ParseItemSlots(std::string a_Word1);

		//Equips the item
		void ParseEquip(std::string a_Word3, PlayerItemSlots a_SelectedSlot, std::shared_ptr<Player> a_Player, InteractResult& a_Result);

		//Parse actions that can be done on an item
		void ParseActions(std::string a_Word2, PlayerItemSlots a_SelectedSlot, std::shared_ptr<Player> a_Player, InteractResult& a_Result);

		//Parse the get command
		void ParseGet(std::string a_Word3, PlayerItemSlots a_SelectedSlot, std::shared_ptr<Player> a_Player, InteractResult& a_Result);

		//Parse the swap command
		void ParseSwap(std::string a_Word1, std::string a_Word3, PlayerItemSlots a_SelectedSlot, std::shared_ptr<Player> a_Player, InteractResult& a_Result);

	};
}