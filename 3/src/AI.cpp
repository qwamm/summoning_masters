#include "include/classes.hpp"
#include "include/matrix.hpp"
#include "../raylib/src/raylib.h"
#include <atomic>

static std::mutex mut;

void AI::squad_move(Squad *sq, std::pair<int,int> &res, std::atomic <bool> *cond, char *x)
{
	matr<bool> *m = game_field->get_matrix();
	std::pair<int,int> cur_coordinats = sq->get_coordinats();
	(*x) = 's';
	if (cur_coordinats.first + 1 < m->getM() &&
	 (*m)[cur_coordinats.first + 1][cur_coordinats.second] != 1)
	{
		std::pair <int, int> c = std::make_pair(cur_coordinats.first + 1, cur_coordinats.second);
		if (!game_field->is_squad_in_cell(c))
		{
				(*x) = 'd';
		}
	}
	else if (cur_coordinats.second + 1 < m->getN() && (*m)[cur_coordinats.first][cur_coordinats.second + 1] != 1)
	{
		std::pair <int, int> c = std::make_pair(cur_coordinats.first, cur_coordinats.second + 1);
		if (!game_field->is_squad_in_cell(c))
		{
				(*x) = 'r';
		}
	}
	else if (cur_coordinats.second - 1 >= 0 && (*m)[cur_coordinats.first][cur_coordinats.second - 1] != 1)
	{
		std::pair <int, int> c = std::make_pair(cur_coordinats.first, cur_coordinats.second + 1);
		if (!game_field->is_squad_in_cell(c))
		{
				(*x) = 'l';
		}
	}
	else if (cur_coordinats.first - 1 >= 0 && (*m)[cur_coordinats.first - 1][cur_coordinats.second] != 1)
	{
		std::pair <int, int> c = std::make_pair(cur_coordinats.first, cur_coordinats.second + 1);
		if (!game_field->is_squad_in_cell(c))
		{
				(*x) = 'u';
		}
	}
	res = sq->get_coordinats();
}

Squad* AI::summoner_move(Summoner *cur, std::atomic<bool> *cond, std::promise<Squad*> res)
{
	//std::cout << "MARKERNNN\n";
	std::pair <int,int> p = std::make_pair(2,5);
	Squad *sq;
	while (!(*cond)) {}

	int q = 0;
	for (int i = 0; i < game_field->get_size_of_list(); i++)
	{
		Squad *sq_1 = game_field->get_squad_with_given_index(i);
		if (sq_1->get_color() == cur->get_color())
			q++;
	}

	if (game_field->is_squad_in_cell(std::make_pair(1,2)) == NULL && q < 3)
	{
		p = std::make_pair(1,2);
		game_field->summon_squad(cur, p, "Earth elementals", "Terra");
	}
	else if (game_field->is_squad_in_cell(std::make_pair(4,3)) == NULL && q < 3)
	{
		p = std::make_pair(4,3);
		game_field->summon_squad(cur, p, "Air elementals", "Air");
	}
	else if (game_field->is_squad_in_cell(std::make_pair(5,2)) == NULL && q < 3)
	{
		p = std::make_pair(5,2);
		game_field->summon_squad(cur, p, "Curses", "Fire");
	}
	else if (q >=3)
	{
		        cur->accumulate_energy();
	}

	sq = game_field->is_squad_in_cell(p);
	res.set_value(sq);
	return sq;
}
