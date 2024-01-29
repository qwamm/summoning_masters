#ifndef CLASSES_H
#define CLASSES_H
#include <iostream>
#include <cstring>
#include <map>
#include <utility>
#include <unordered_map>
#include <vector>
#include <future>
#include <atomic>
#include "matrix.hpp"
#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include "../../raylib/src/raylib.h"

static std::mutex mut1;

typedef unsigned long int ll;

enum COLOR {blue, red};

class Skill ///умение
{
	std::string name;
	std::string creature_name;
	unsigned int min_knowledge;
	unsigned int energy_expended;
	double headcount_ratio;

	public:
		Skill(std::string _name, std::string _creature_name, unsigned int _min_knowledge, unsigned int _energy_expended, double _headcount_ratio);

		Skill() : Skill("", "", 0, 0, 0) {};
		~Skill() {};

		std::string getName() const ///получение названия умения
		{
			return name;
		}
		std::string getCreatureName() const ///получение имени сущности
		{
			return creature_name;
		}
		unsigned int getMinKnowledge() const ///получение минимального знания
		{
			return min_knowledge;
		}
		unsigned int getEnergyExpended() const ///получение затраченной энергии
		{
			return energy_expended;
		}
		double getHeadcountRatio() const ///получение коэффициента численности
		{
			return headcount_ratio;
		}
};

class School ///школа
{
	private:
		std::string name;
		std::vector<std::string> weaker_schools;
		std::vector<Skill> list_of_skills;
	public:

		School(std::string _name)
		{
			name = _name;
		}

		School() : School("") {};

		~School()
		{
			weaker_schools.clear();
			list_of_skills.clear();
		}

		[[nodiscard]] int get_quantity_of_weaker_schools() const ///получение количества более слабых школ
		{
			return weaker_schools.size();
		}

		void add_weaker_school (std::string school_name) ///добавление более слабой школы
		{
			weaker_schools.push_back(school_name);
		}

		std::string get_weaker_school(int i) ///получение более слабой школы
		{
			return weaker_schools[i];
		}

                void add_skill(Skill &s) ///добавление умения
                {
                        list_of_skills.push_back(s);
                }

		Skill& find_creature(std::string skill_name); ///поиск существа в списке умений школы

		void change_creature (std::string creature_name, Skill &obj); ///изменение существа в списке умений школы

		std::string get_name() const ///получение имени школы
		{
			return name;
		}

		int get_num_of_creatures() const ///получение количества существ
		{
			return list_of_skills.size();
		}

		std::vector<Skill>& get_list_of_skills() ///получение списка умений
		{
			return list_of_skills;
		}

		void set_name(std::string _name) ///установка имени
		{
			name = _name;
		}
};

class Table_of_schools ///таблица школ
{
	protected:
		std::unordered_map<std::string, School> schools;
	public:
		Table_of_schools() = default;

		~Table_of_schools()
		{
			schools.clear();
		}

		void add_school(School &obj); ///добавление школы в таблицу
		void add_skill(std::string school_name, Skill &s); ///добавление умения в список умений школы, содержащейся в таблице

		Skill& get_creature(std::string school_name, std::string skill_name); ///получение существа умения школы, содержащейся в таблице

		void change_creature(std::string school_name, std::string creature_name, Skill &obj); ///изменение существа

		int get_num_of_schools() const ///получение количества школ
		{
			return schools.size();
		}

		[[nodiscard]] School& get_school(std::string school_name) ///получение школы
		{
			if (schools.contains(school_name))
			{
				return schools[school_name];
			}
			else
			{
				throw std::invalid_argument("Table doesn't contain given school name");
			}
		}

		int get_num_of_creatures(std::string school_name); ///получение количества существ
};

class initiative_creatures ///инициативное существо
{
	private:
		COLOR c; ///цвет призывателя (красный/синий)
		ll cur_health; ///текущее здоровье
		ll max_health; ///максимальное здоровье
		ll initiative; ///инициатива
		std::pair<int, int> coordinats; ///координаты
	public:
		void move_to_cell(char d); ///переместиться в клетку

		void set_cur_health( ll _c) ///установить текущее здоровье
		{
			cur_health = _c;
		}

		void set_max_health (ll _m) ///установить максимальное здоровье
		{
			max_health = _m;
		}

		[[nodiscard]] ll get_cur_health() const ///получить текущее здоровье
		{
			return cur_health;
		}

		[[nodiscard]] ll get_max_health() const ///получить максимальное здоровье
		{
			return max_health;
		}

		[[nodiscard]] std::pair<int,int> get_coordinats() const ///получить координаты
		{
			return coordinats;
		}

		void set_coordinats(std::pair<int,int> p) ///установить координаты
		{
			coordinats = p;
		}

		void set_initiative(ll _initiative) ///установить инициативу
		{
			initiative = _initiative;
		}

		[[nodiscard]] ll get_initiation() const ///получить инициативу
		{
			return initiative;
		}

		void set_color(COLOR _c) ///установить цвет существа
		{
			c = _c;
		}

		[[nodiscard]] COLOR get_color() const ///поулчить цвет существа
		{
			return c;
		}
};

class BOOST_SYMBOL_VISIBLE Squad: public initiative_creatures ///аморальный отряд
{
	protected:
		std::string name; //название существ
		School squad_school; //школа отряда
		ll initiative; //инициатива
		ll speed; //скорость
		ll damage; //урон
		ll defence; //защита
		ll quantity; //количество
		ll experience_for_destroying; //опыт за уничтожение отряда
	public:
		Squad () {}
		Squad (std::string _name) : name(_name) {}

		Squad(std::string _name, School &_squad_school, ll _head_count_ratio, COLOR c);

		void make_damage(ll _damage); ///нанести урон

		virtual void attack(Squad *enemy); ///атака

		bool is_reachable(Squad *s); ///достижим ли отряд

		[[nodiscard]] std::string get_name() const ///получить имя
		{
			return name;
		}

		[[nodiscard]] School& get_school() ///получение школы
		{
			return squad_school;
		}
		[[nodiscard]] ll get_damage() const ///получение урона
		{
			return damage;
		}
		[[nodiscard]] ll get_initiative() const ///получение инициативы
		{
			return initiative;
		}
                [[nodiscard]] ll get_speed() const ///получение скорости
                {
                        return speed;
                }
                [[nodiscard]] ll get_defence() const ///получение уровня защиты
                {
                        return defence;
                }
		[[nodiscard]] ll get_quantity() const ///получение количества юнитов
                {
                        return quantity;
                }
                [[nodiscard]] ll get_experience_for_destroying() const ///получение опыта за уничтожение
                {
                        return experience_for_destroying;
                }

                void set_name (std::string _name)
                {
                	name = _name;
                }

		void set_school (School &_school) ///установка школы
		{
			squad_school = _school;
		}

                void set_damage(ll _damage) /// установка урона
                {
                        damage = _damage;
                }
                void set_initiative(ll _initiative) ///установка инициативы
                {
                        initiative = _initiative;
                }
                void set_speed(ll _speed) ///установка скорости
                {
                        speed = _speed;
                }
                void set_defence(ll _defence) ///установка уровня защиты
                {
                        defence = _defence;
                }
                void set_quantity(ll _quantity) ///установка количества юнитов
                {
                        quantity = _quantity;
                }
                void set_experience_for_destroying(ll _experience_for_destroying) ///установка опыта, который враг получит за уничтожение данного отряда
                {
                        experience_for_destroying = _experience_for_destroying;
                }
		virtual void print() const ///распечатать имя отряда
		{
			std::cout << name << std::endl;
		}
};

class Typical_squad : public Squad ///моральный (обычный) отряд
{
	private:
		long int moral; //мораль отряда
	public:
		Typical_squad(std::string _name, School &_squad_school, ll _head_count_ratio, COLOR c, ll _moral) : Squad ( _name,
		 _squad_school, _head_count_ratio, c), moral (_moral) {}

		long int get_moral() const ///получение значения морали
		{
			return moral;
		}

		//void attack(Squad *enemy) override;

		void print() const override ///распечатать имя отряда и его мораль
		{
			Squad::print();
			std::cout << "moral of the squad: " << moral <<"\n";
		}

		virtual void balance_moral() ///сбалансировать мораль
		{
			moral-=5;
		}
};

class Resurrecting ///возрождение
{
	public:
		virtual void try_resurrect() {} ///возродить некоторое количество погибщих членов отряда
};

class Resurrecting_squad : public Typical_squad, public Resurrecting ///возраждающийся отряд
{
	public:
		Resurrecting_squad(std::string _name, School &_squad_school, ll _head_count_ratio, COLOR c) : Typical_squad( _name,
                 _squad_school, _head_count_ratio, c, 0) {}
		void try_resurrect() override ///возродить некоторое количество погибщих членов отряда
		{
			ll prev_cur_health = this->get_cur_health();
			this->set_cur_health ((int) this->get_max_health()*0.75 + this->get_cur_health());
			this->set_quantity(this->get_quantity() + this->get_cur_health() - prev_cur_health);
		}
};

class Resurrecting_squad_without_moral : public Squad, public Resurrecting ///аморальный возраждающийся отряд
{
        public:
		Resurrecting_squad_without_moral(std::string _name, School &_squad_school, ll _head_count_ratio, COLOR c) : Squad ( _name,
                 _squad_school, _head_count_ratio, c) {}
                void try_resurrect() override ///возродить некоторое количество погибщих членов отряда
		{
			 this->set_cur_health ((int) this->get_max_health()*0.75 + this->get_cur_health());
		}
};

class Summoner : public initiative_creatures ///призыватель
{
        private:
                std::string name; //имя призывателя
                ll unspent_experience; //непотраченный опыт
                ll max_energy; //максимальная энергия
                ll cur_energy; //текущая энергия
                ll accumulation_coefficient; //коэффициент аккумуляции
                std::unordered_map<std::string, ll> possession_of_schools; //владение школами
                const static ll num_of_schools = 4;
        public:

                Summoner (std::string _name, ll _max_health, ll _cur_health, ll _unspent_experience, ll _max_energy, ll _cur_energy,
                 ll _accumulation_coefficient, ll _initiative, COLOR c)
                {
                        this->set_max_health(_max_health);
                        this->set_cur_health(_cur_health);
                        unspent_experience = _unspent_experience;
                        max_energy = _max_energy;
                        cur_energy = _cur_energy;
                        accumulation_coefficient = _accumulation_coefficient;
                        this->set_initiative(_initiative);
                        this->set_color(c);
                }

                ~Summoner()
		{
			possession_of_schools.clear();
		}

                void set_possession_of_school(std::string school_name, ll _p) ///установить уровень владения школой
		{
			if (!possession_of_schools.contains(school_name))
                        	possession_of_schools.insert(std::make_pair(school_name, _p));
			else
				throw std::invalid_argument("The possession of given school has already inserted in the table");
                }

                [[nodiscard]] ll get_possession_of_school(std::string school_name) noexcept ///получить уровень владения школой
                {
                        if (possession_of_schools.contains(school_name))
                                return possession_of_schools[school_name];
                        else
                                return 0;
                }
                void reduce_energy (ll _energy) ///уменьшить энергию
                {
                        if (_energy > cur_energy)
                                cur_energy = 0;
                        else
                                cur_energy -= _energy;
                }

                void accumulate_energy() ///аккумулировать энергию
                {
                        cur_energy += 10*accumulation_coefficient;
                }

                bool improve_school (std::string school_name); ///улучшить школу

              	void increase_experience(ll exp) ///увеличить опыт
		{
			unspent_experience += exp;
		}

                ll get_experience(const ll exp) ///получить опыт
                {
                        return unspent_experience;
                }
};

class Landscape ///ландшафт
{
        private:
                matr<bool> *m;
                Table_of_schools *t;
                std::vector<Squad*> list_of_squads;
                std::unordered_map <std::string, Squad*> squad_map;
                std::vector < boost::shared_ptr<Squad>> plugin_vector;
                Summoner *s1, *s2;
        public:
                Landscape(std::pair <int,int> map_size); ///конструктор карты с параметром, задающим её размер
                ~Landscape()
                {
                        /*for (int i = 0; i < list_of_squads.size(); i++)
                        {
                                delete list_of_squads[i];
                        }*/
                        list_of_squads.clear();
                        delete m;
                        delete t;
                        delete s1;
                        delete s2;
                }

		matr<bool>* get_matrix() ///поулчение матрицы
		{
			return m;
		}

		bool valid_enemy_coordinats (COLOR enemy_color, std::pair <int,int> c_enemy, std::pair<int,int> c_squad, ll sq_speed, std::pair<int,int> &prev); ///функция, проверяющая
		///нахождение врага в заданной клетке

		/*std::pair<int,int> return_next_obstacle(std::pair <int, int> c) ///функция, возвращающая следующее препятствие
		{
			matr<bool> *m1 = m;
			std::pair <int,int> c1= m->it->return_next_cell([m1](matr<bool> *mt, std::pair <int,int> c, int r, int k) -> std::pair<int,int>
			 {return m1->next_cell(mt, c, r, k);}, c  ,2);
			return c1;
		}*/

		void add_squad_in_map(Squad *sq);

		std::unordered_map<std::string, Squad*>& create_hash_map(Table_of_schools *t);

		Squad* create_squad(Skill cur_skill, School school, COLOR s_color);

		void resurrect_squad (Squad *sq) ///возродить часть членов отряда
		{
			dynamic_cast<Resurrecting*>(sq)->try_resurrect();
		}

                bool summon_squad(Summoner *cur, std::pair <int,int> sq_coordinats, std::string skill_name, std::string school_name); ///призвать новый отряд

		bool summoner_attack(const int screenWidth, const int screenHeight, COLOR summoner_color, Squad *sq, bool &is_dead, ll &before, ll &after); ///атаковать призывателя

                bool squad_attack(std::pair <int,int> c_enemy, Squad *sq, bool& is_dead, ll &before, ll &after); ///атаковать отряд

                void sort_list_of_squads() noexcept; ///отсортировать список отрядов

                Squad* is_squad_in_cell(std::pair <int,int> c); ///проверка, находится ли отряд в клетке

                bool move_to_cell (Squad *sq, std::pair <int, int> c); ///передвижение отряда в новую клетку

                bool set_squad_in_free_cell(Squad *sq, std::pair<int,int> c); ///установка отряда в свободную клетку

                [[nodiscard]] Squad* get_squad_with_highest_initiation(); ///получение отряда с наибольшей инициативой из списка отрядов

                [[nodiscard]] Squad* get_squad_with_given_index(int ind); ///получение отряда из списка отрядов по заданному индексу

                [[nodiscard]] Summoner* get_first_summoner() ///получение красного призывателя
                {
                        return s1;
                }

                [[nodiscard]] Summoner *get_second_summoner() ///получение синего призывателя
                {
                        return s2;
                }

                void add_squad(Squad *sq) ///добавление нового отряда в список отрядов
                {
                        list_of_squads.push_back(sq);
                }

                int print_squads(COLOR c) noexcept; ///вывод имен отрядов из списка в консоль

		int distance_between_units (std::pair <int,int> s1, std::pair <int,int> s2, std::pair<int,int> &prev) ///расстояние между юнитами на карте
		{
			int dest = 0;
			std::vector<std::pair<int,int>> v;
			for (int c = 0; c < list_of_squads.size(); c++)
			{
				v.push_back(list_of_squads[c]->get_coordinats());
			}
			m->destination(s1,s2, &dest, prev, v);
			return dest;
		}

                [[nodiscard]] std::pair<int,int> get_size_of_field() const; ///получение размеров поля
                [[nodiscard]] CELL_TYPE get_type_of_cell (int i, int j) const; ///получить тип клетки по координатам
                void set_type_of_cell (CELL_TYPE type, int i, int j); ///установить тип клетки (земля/препятствие) по координатам

                [[nodiscard]] Table_of_schools* get_table() ///получение таблицы школ
                {
                        return t;
                }

                [[nodiscard]] int get_size_of_list() const ///получение размера списка отрядов
                {
                		//mut1.lock();
                        return list_of_squads.size();
 						//mut1.unlock();
                }

};

/*class UI
{
	public:
		int summoner_move(Summoner *cur);
		void summon_squad(std::string &skill_name, std::string &school_name);
		std::pair<int,int> spawn_coordinats();
		std::string improve_school();
		void wrong_number();
		int squad_move(Squad *sq);
		std::pair<int,int> cell_coordinats();
		void squad_attack(COLOR enemy_color, Summoner *red, Summoner *blue);
		int squad_num(int mx_ind);
		void squad_not_reachable();
		//void game_over(const int screenWidth, const int screenHeight, COLOR s);
};*/

class Game;

class Graphics_UI
{
	public:
		void StartScreen(const int screenWidth, const int screenHeight); ///начальный экран
		void DrawingMap(Game g, matr<bool> *m, const int screeWidth, const int screenHeight); ///нарисовать карту
		std::pair <int,int> convert_coordinats_from_pixels(const int screenWidth, const int screenHeight, int x, int y); ///преобразовать координаты в пикселях в координаты в матрице
		void DrawSquad (const int screenWidth, const int screenHeight, COLOR clr, std::pair <int, int> c, std::string squad_name); ///нарисовать отряд
		int Squad_move(std::string skill_name, COLOR clr, std::pair<int,int> c); ///ход отряда
		void remove_squad(std::pair<int,int> old); ///удалить отряд с карты
		void game_over(const int screenWidth, const int screenHeight, COLOR s); ///окончание игры
		int summoner_move(Summoner *cur); ///ход призывателя
		void clear_right_side(); ///очистить правую сторону экрана
		void display_health(ll before, ll after); ///отобразить здоровье на экране
		std::string improve_school(); ///улучшить школу
		void ToggleFullScreenWindow(int windowWidth, int windowHeight);
		std::string ChooseSchool(); ///выбрать школу
		std::string ChooseSkill(std::string school_name); ///выбрать умение
		COLOR choose_color(); ///меню выбора стороны
		std::pair <int,int> spawn_coordinats(const int screenWidth, const int screenHeight); ///получить координаты клетки, в которой заспавнится новый отряд
};

class AI
{
        private:
                Landscape *game_field;
                Graphics_UI *g_interface;
        public:
        		std::mutex ai_mutex;
                AI(Landscape *g)
                {
                        game_field = g;
                        g_interface = new Graphics_UI();
                }
                ~AI()
                {
                        game_field = NULL;
                        delete g_interface;
                }
                Squad* summoner_move(Summoner *cur, std::atomic<bool> *cond, std::promise<Squad*> res_promise);
                void squad_move(Squad *sq, std::pair<int,int> &res, std::atomic <bool> *cond, char *x);
};

class Game
{
        private:
                ll move_number;
                Landscape *game_field;
		Graphics_UI *g_interface; //графический интерфейс
		AI *art_intel;
        public:
		Game(std::pair <int,int> map_size); ///конструктор с параметром, задающим размер карты
		~Game()
		{
			delete game_field;
			delete g_interface;
			delete art_intel;
		}

		bool checking(Squad *sq, std::pair<int,int>& res_coordinats, std::pair<int,int> old_coordinats, char ch);

		void StartScreen (const int screenWidth, const int screenHeight) ///начальный экран
		{
			g_interface->StartScreen(screenWidth, screenHeight);
		}
		void DrawingMap(const int screenWidth, const int screenHeight) ///нарисовать карту
		{
			g_interface->DrawingMap(*this, game_field->get_matrix(), screenWidth, screenHeight);
		}

                bool commit_one_iteration(const int screenWidth, const int screenHeight, COLOR player_color); ///совершить ход

		bool summoner_move(const int screenWidth, const int screenHeight, Summoner *cur);

		bool squad_move(Squad *sq, int screenWidth, int screenHeight);
};

#endif
