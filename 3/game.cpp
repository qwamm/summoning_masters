#include "src/include/classes.hpp"
#include "raylib/src/raylib.h"
#include <iostream>
#include <typeinfo>
#include <future>
#include <vector>
#include <atomic>

static std::mutex mut;

std::ostream &operator << (std::ostream& strm, COLOR c)
{
        const std::string nameCOLOR[] = {"blue", "red"};
        return strm << nameCOLOR[c];
}

Game::Game(std::pair <int,int> map_size)
{
	game_field = new Landscape(map_size);
	g_interface = new Graphics_UI();
	art_intel = new AI(game_field);
	move_number = 0;
}

bool Game::checking(Squad *sq, std::pair<int,int>& res_coordinats, std::pair<int,int> old_coordinats, char ch)
{
	matr<bool> *m1 = game_field->get_matrix();
	if (ch == 'u')
				{

					res_coordinats = std::make_pair(old_coordinats.first-1, old_coordinats.second);
					if (game_field->is_squad_in_cell(res_coordinats) || (*m1)[res_coordinats.first][res_coordinats.second] == 1)
					{
						return false;
					}
					game_field->move_to_cell(sq,res_coordinats);
				}
				else if (ch == 'd')
				{
					res_coordinats = std::make_pair(old_coordinats.first+1, old_coordinats.second);
					if (game_field->is_squad_in_cell(res_coordinats) || (*m1)[res_coordinats.first][res_coordinats.second] == 1)
					{
						return false;
					}
					game_field->move_to_cell(sq,res_coordinats);
				}
				else if (ch== 'l')
				{
					res_coordinats = std::make_pair(old_coordinats.first, old_coordinats.second-1);
					if (game_field->is_squad_in_cell(res_coordinats) || (*m1)[res_coordinats.first][res_coordinats.second] == 1)
					{
						return false;
					}
					game_field->move_to_cell(sq,res_coordinats);
				}
				else if (ch== 'r')
				{
					res_coordinats = std::make_pair(old_coordinats.first, old_coordinats.second+1);
					if (game_field->is_squad_in_cell(res_coordinats) || (*m1)[res_coordinats.first][res_coordinats.second] == 1)
					{
						return false;
					}
					game_field->move_to_cell(sq,res_coordinats);
				}
				else
				{
					res_coordinats = old_coordinats;
				}
}

bool Game::commit_one_iteration(const int screenWidth, const int screenHeight, COLOR player_color)
{
		bool red_summoner_move = false, blue_summoner_move = false;
		game_field->sort_list_of_squads();
		int sz = game_field->get_size_of_list();

		Summoner *ai = player_color == COLOR::red ? game_field->get_second_summoner() : game_field->get_first_summoner();

		std::atomic <bool> cond{false};
                std::promise<Squad*> res_promise;
                auto res = res_promise.get_future();

                std::thread th_summoner(&AI::summoner_move, art_intel, ai, &cond, std::move(res_promise)); //ИИ призывателя

		std::vector<std::thread> v_threads; //ИИ отрядов
		std::pair<int,int> res_coordinats;
		std::atomic<bool> squad_cond[sz];
		char actions[sz];
		for (int j = 0; j < sz; j++)
			std::atomic_init(&squad_cond[j], false);
		for (auto t = 0, ts = 0; t < sz ; t++)
		{
			if (game_field->get_squad_with_given_index(t)->get_color() != player_color)
			{
				v_threads.push_back(std::thread (&AI::squad_move, art_intel, game_field->get_squad_with_given_index(t),
				std::ref(res_coordinats), &(squad_cond[ts]), &actions[ts]));
				ts++;
			}
		}

		for (int j = 0, t = 0; j < sz || !red_summoner_move || !blue_summoner_move;)
		{
		int in_val = -1;
		Squad *sq;
		if (j < game_field->get_size_of_list())
			sq = game_field->get_squad_with_given_index(j);
		else
			sq = NULL;
		Summoner *red = game_field->get_first_summoner(), *blue = game_field->get_second_summoner();
		ll sq_init;
		if (sq == nullptr)
			sq_init = 0;
		else
			sq_init = sq->get_initiative();
		std::cout << game_field->get_size_of_list() << "\n";
		for (int k=0; k < game_field->get_size_of_list(); k++)
		{
			Squad *cur_sq = game_field->get_squad_with_given_index(k);
			std::cout << cur_sq->get_name() << " " << cur_sq->get_color() << "\n";
		}
		if ((red->get_initiation() > sq_init && !red_summoner_move) || (blue->get_initiation() > sq_init && !blue_summoner_move))
		{
			Summoner *cur;
			if (red->get_initiation() > blue->get_initiation() && !red_summoner_move)
			{
				cur = red;
			}
			else if (!blue_summoner_move)
			{
				cur = blue;
			}
			else
			{
				cur = red;
			}

			if (cur->get_color() == COLOR::red)
			{
				red_summoner_move = true;
			}
			else
			{
				blue_summoner_move = true;
			}
			if (cur->get_color() == player_color)
			{
				bool success = false;
				while (!success)
				{
					success = this->summoner_move(screenWidth, screenHeight, cur);
				}
			}
			else
			{
				cond.store(true);
				Squad *sq = res.get();
				th_summoner.join();
				if (sq != NULL && sq->get_coordinats() != std::make_pair(0,0))
				{
									//std::cout << "MARKERNNNNNN\n";
                                	g_interface->DrawSquad(screenWidth, screenHeight, sq->get_color(),
                                	sq->get_coordinats(), sq->get_name());
				}
			}
		}
		else
		{
			if (sq == NULL)
				break;
			j++;
			if (sq->get_color() == player_color)
			{
				bool success = false;
				while (!success)
				{
					success = this->squad_move(sq, screenWidth, screenHeight);
				}
			}
			else
			{
				std::pair<int,int> old_coordinats = sq->get_coordinats();
				squad_cond[t].store(true);
				if (t < v_threads.size())
				{
					v_threads[t].join();
				}
				if  (!this->checking(sq, res_coordinats, old_coordinats, actions[t]))
				{
					art_intel->squad_move(sq, res_coordinats, &squad_cond[t], &actions[t]);
				}

				if (sq->get_coordinats() == std::make_pair(0,0) || res_coordinats == std::make_pair(0,0))
				{
						sq->set_coordinats(old_coordinats);
						res_coordinats = old_coordinats;
				}
				if (res_coordinats != old_coordinats)
				{
						g_interface->remove_squad(old_coordinats);
						g_interface->DrawSquad (screenWidth, screenHeight, sq->get_color(), res_coordinats, sq->get_name());
				}

				//std::cout << "NEW COORDINATS: " << res_coordinats.first << " " << res_coordinats.second << "\n";
				t++;
			}
		}
		}
		for (int i=0; i < v_threads.size(); i++)
			{
				if (squad_cond[i].load() == false)
				{
					v_threads[i].join();
				}
			}
		move_number++;
		return false;
}

bool Game::squad_move(Squad *sq, int screenWidth, int screenHeight)
{
			bool success = false;
			int in_val = g_interface->Squad_move(sq->get_name(), sq->get_color(), sq->get_coordinats());
			switch(in_val)
			{
				case(49):
				{
					std::pair <int,int> p = g_interface->spawn_coordinats(screenWidth, screenHeight), old = sq->get_coordinats();
					if (game_field->move_to_cell(sq,p))
					{
						g_interface->remove_squad(old);
						g_interface->DrawSquad (screenWidth, screenHeight, sq->get_color(), p, sq->get_name());
						success = true;
					}
					break;
				}
				case(50):
				{

					COLOR enemy_color;
					if (sq->get_color() == COLOR::red)
						enemy_color = COLOR::blue;
					else
						enemy_color = COLOR::red;

					std::pair<int,int> c_enemy, prev;
					c_enemy = g_interface->spawn_coordinats(screenWidth, screenHeight);
					if (game_field->valid_enemy_coordinats(enemy_color, c_enemy, sq->get_coordinats(), sq->get_speed(), prev))
					{
						bool is_dead = false;
						if (prev != sq->get_coordinats())
						{
							g_interface->remove_squad(sq->get_coordinats());
							g_interface->DrawSquad(screenWidth, screenHeight, sq->get_color(), prev, sq->get_name());
							sq->set_coordinats(prev);
						}

						ll after, before;

						if (c_enemy == std::make_pair(0,0) || c_enemy == std::make_pair(5,5))
						{
								COLOR s = c_enemy == std::make_pair(0,0) ? COLOR::red : COLOR::blue;
								game_field->summoner_attack(screenWidth, screenHeight, s,sq,is_dead, before, after);
								if (is_dead)
								{
									g_interface->game_over(screenWidth, screenHeight, sq->get_color());
									return true;
								}
						}
						else
						{
							game_field->squad_attack(c_enemy,sq,is_dead, before, after);
							if (is_dead)
							{

								g_interface->remove_squad(c_enemy);
							}
						}

						g_interface->display_health(before, after);

						success = true;
					}
					break;
				}
				case(51):
				{
					game_field->resurrect_squad(sq);
				}
				default:
				{
					break;
				}
			}
			return success;
}

bool Game::summoner_move(const int screenWidth, const int screenHeight, Summoner *cur)
{
				bool success = false;
                                int in_val = g_interface->summoner_move(cur);
                                switch(in_val)
                                {
                                        case(49):
                                        {
                                                std::string school_name = g_interface->ChooseSchool(), skill_name = g_interface->ChooseSkill(school_name);
                                                try
                                                {
                                                                std::pair<int,int> sq_coordinats = g_interface->spawn_coordinats(screenWidth,
                                                                screenHeight);
                                                                success = game_field->summon_squad(cur, sq_coordinats, skill_name, school_name);
                                                                if (success)
                                                                {
                                                                        g_interface->DrawSquad(screenWidth, screenHeight, cur->get_color(),
                                                                         sq_coordinats, skill_name);
                                                                }
                                                                //std::cout << "Distance between squad and summoner: " << game_field->distance_between_units(cur->get_coordinats(), sq_coordinats) << "\n";
                                                }
                                                catch(...)
                                                {
                                                        throw;
                                                }
                                                break;
                                        }
                                        case(50):
                                        {
                                                cur->accumulate_energy();
                                                success = true;
                                                break;
                                        }
                                        case(51):
                                        {
                                                std::string school_name = g_interface->improve_school();
                                                success = cur->improve_school(school_name);
                                                break;
                                        }
                                        default:
                                        {
                                                break;
                                        }
                                }
				return success;
}
