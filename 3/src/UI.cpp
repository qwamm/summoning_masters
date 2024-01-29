#include "include/classes.hpp"
#include <iostream>

void UI::squad_not_reachable()
{
	std::cout << "The selected summoner cannot be reached\n";
}

int UI::squad_num(int mx_ind)
{
					int squad_num = -1;
					do
                                        {
                                                std::cin >> squad_num;
                                                if (squad_num >= mx_ind + 1 && squad_num <1)
                                                        std::cout <<"Wrong squad number. Try again";
                                        } while (squad_num > mx_ind && squad_num <1);
		return squad_num;
}

void UI::squad_attack(COLOR enemy_color, Summoner *red, Summoner *blue)
{
	std::cout << "Which enemy do you want to attack?\n";
	std::cout << "ENEMY COLOR: " << enemy_color << "\n";
	std::pair<int,int> enemy_summoner_coordinats = enemy_color == COLOR::red ? red->get_coordinats()
                                         : blue->get_coordinats();
	/*std::cout << mx_ind + 1 << ". " <<"Enemy summoner in coordinats " << "(" << enemy_summoner_coordinats.first
                                         << "," << enemy_summoner_coordinats.second << ")\n";*/
}

std::pair<int,int> UI::cell_coordinats()
{
	std::cout << "Enter coordinats of cell you want to move:\n";
	std::pair <int,int> p;
	std::cin >> p.first >> p.second;
	return p;
}

int UI::squad_move(Squad *sq)
{
			int in_val;
			std::cout << "NAME: " << sq->get_name() << "\n";
                        std::cout << "COORDINATS: " << "(" << sq->get_coordinats().first << "," << sq->get_coordinats().second << ")" << "\n";
                        std::cout << "1. Move to cell" << std::endl;
                        std::cout << "2. Approach the enemy and attack" << std::endl;
			if (sq->get_name() == "Heal" || sq->get_name() == "Resurrect")
                        {
                                std::cout << "3. Resurrect dead squad members" << std::endl;
                        }
			std::cin >> in_val;
			return in_val;
}

void UI::wrong_number()
{
	std::cout << "Error: you entered wrong number. Try again.\n";
}

std::string UI::improve_school()
{
	std::string school;
	std::cout << "Choose school knowledge of which you want to improve\n" << std::endl;
	std::cin>>school;
	return school;
}

std::pair<int,int> UI::spawn_coordinats()
{
	std::cout << "Enter coordinats in which you want to spawn squad:\n";
        std::pair <int, int> sq_coordinats;
        std::cin >> sq_coordinats.first >> sq_coordinats.second;
	return sq_coordinats;
}

void UI::summon_squad(std::string &skill_name, std::string &school_name)
{
	std::cout << "Choose a school\n";
        std::cin >> school_name;
	std::cout << "Choose a skill:\n";
	std::scanf("\n");
	std::getline(std::cin, skill_name);
}

int UI::summoner_move(Summoner *cur)
{
	int in_val;
	std::cout << "What do you want to do during current iteration?\n" << std::endl;
	std::cout << "COLOR OF SUMMONER: " << cur->get_color() << "\n";
        std::cout << "COORDINATS: " << "(" << cur->get_coordinats().first << "," << cur->get_coordinats().second << ")" << "\n";
        std::cout << "1. Summon a squad of available creatures" << std::endl;
       	std::cout << "2. Accumulate energy" << std::endl;
       	std::cout << "3. Improve knowledge of one of the schools for experience" << std::endl;
       	std::cin >> in_val;
	return in_val;
}
