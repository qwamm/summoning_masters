#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <cstdlib>
#include "/home/qurst/oop2023/3/src/include/classes.hpp"
#include "/home/qurst/oop2023/3/src/include/matrix.hpp"

TEST_CASE ("Skill")
{
	SECTION("Constructors")
	{
		Skill("demons", "demon", 10, 0, 1.5);
	}
	SECTION("Getters")
	{
		Skill d("demons", "demon", 10, 0, 1.5);
		REQUIRE(d.getName() == "demons");
		REQUIRE(d.getCreatureName() == "demon");
		REQUIRE(d.getMinKnowledge() == 10);
		REQUIRE(d.getEnergyExpended() == 0);
		REQUIRE(d.getHeadcountRatio() == 1.5);
	}
}

TEST_CASE ("School")
{
	SECTION("Weaker schools")
	{
		School s("Robots");
		s.add_weaker_school("Biotechnology");
		s.add_weaker_school("Parallel universes");
		s.add_weaker_school("Goblins");
		REQUIRE(s.get_quantity_of_weaker_schools() == 3);
		REQUIRE(s.get_weaker_school(1) == "Parallel universes");
	}
	SECTION("Creatures")
	{
		School s("Robots");
		Skill r("B-6", "B-6s", 10, 0, 1.2);
		s.add_skill(r);
		REQUIRE(s.find_creature("B-6").getName() == r.getName());
		s.change_creature("B-6", r);
		REQUIRE(s.get_num_of_creatures() == 1);
	}
}

TEST_CASE("Table of schools")
{
	Table_of_schools t;
	REQUIRE(t.get_num_of_schools() == 0);
	School x("knights");
	t.add_school(x);
	REQUIRE (t.get_num_of_schools() == 1);
	REQUIRE_NOTHROW(t.get_school("knights"));
	REQUIRE(t.get_num_of_creatures("knights") == 0);
}

TEST_CASE("initiative creatures")
{
	School x("undead");
	Squad sq("zombies", x, 2, COLOR::blue);
	sq.set_cur_health(100);
	sq.set_max_health(100);
	sq.set_coordinats(std::make_pair(5,2));
	sq.set_color(COLOR::red);
	//sq.set_initiative((ll)532);
	REQUIRE(sq.get_cur_health() == 100);
	REQUIRE(sq.get_max_health() == 100);
	REQUIRE(sq.get_coordinats() == std::make_pair(5,2));
	//REQUIRE(sq.get_initiation() == (ll)532);
	REQUIRE(sq.get_color() == COLOR::red);
}

TEST_CASE("Squad")
{
	 School fire("Fire");
	 Skill curse("Curses", "Curse", 0, 10, 1.5);
	 fire.add_skill(curse);
	 Squad sq("curses", fire, 2, COLOR::blue);
	 Squad sq_2("executioners", fire, 3, COLOR::red);
	 sq.set_coordinats(std::make_pair(0,0));
	 sq_2.set_coordinats(std::make_pair(5,5));
	 sq.set_speed(3);
	 sq.set_damage(10);
	 sq.set_defence(15);
	 sq.set_quantity(54);
	 sq.set_experience_for_destroying(324);
	 REQUIRE(sq.is_reachable(&sq_2) == false);
	 REQUIRE(sq.get_name() == "curses");
	 REQUIRE(sq.get_school().get_name() == fire.get_name());
	 REQUIRE(sq.get_speed() == 3);
	 REQUIRE(sq.get_damage() == 10);
	 REQUIRE(sq.get_defence() == 15);
	 REQUIRE(sq.get_quantity() == 54);
	 REQUIRE(sq.get_experience_for_destroying() == 324);
}

TEST_CASE("Typical squad")
{
        School fire("Fire");
        Skill ex("Executioners", "Executioner", 12, 10, 1.5);
        fire.add_skill(ex);
	Typical_squad s("executioners", fire, 2, COLOR::red, 15);
	REQUIRE(s.get_moral() == 15);
	ll before = s.get_moral();
	s.balance_moral();
	REQUIRE(s.get_moral() < before);
}

TEST_CASE("Resurrecting_squad")
{
	School fire("Fire");
        Skill ex("Executioners", "Executioner", 12, 10, 1.5);
        fire.add_skill(ex);
	Resurrecting_squad s("executioners", fire, 2, COLOR::red);
	s.set_cur_health(50);
	s.set_max_health(100);
	s.set_quantity(20);
	s.try_resurrect();
	REQUIRE(s.get_cur_health() > 50);
	REQUIRE(s.get_quantity() > 20);
}

TEST_CASE("Summoners")
{
	SECTION("Constructor")
	{
		Summoner s1("Red", 100, 100, 0, 1000000, 50, 1.3, rand()%100, COLOR::red);
		s1.set_possession_of_school("Fire",11);
		REQUIRE(s1.get_possession_of_school("Fire") == 11);
		s1.accumulate_energy();
		s1.improve_school("Fire");
		//REQUIRE(s1.get_experience() == 0);
	}
}

TEST_CASE("Landscape")
{
	 School fire("Fire");
         Skill curse("Curses", "Curse", 0, 10, 1.5);
         fire.add_skill(curse);
         Squad sq("curses", fire, 2, COLOR::blue);
	Landscape x(std::make_pair(6,6));
	matr<bool> *ptr = x.get_matrix();
	REQUIRE (ptr != nullptr);
	x.add_squad(&sq);
	std::pair <int,int> prev;
	REQUIRE(x.distance_between_units(std::make_pair(0,0), std::make_pair(1,0), prev) == 1);
	REQUIRE(x.get_size_of_field() == std::make_pair(6,6));
	REQUIRE(x.get_table() != nullptr);
	REQUIRE(x.get_size_of_list() == 1);
	REQUIRE(x.get_first_summoner() != nullptr);
	REQUIRE(x.get_second_summoner() != nullptr);
	REQUIRE(x.get_squad_with_given_index(0) != NULL);
	REQUIRE((*(x.get_matrix()))[1][0] == 0);
	x.sort_list_of_squads();
	x.summon_squad(x.get_first_summoner(), std::make_pair(3,4), "Executioners", "Fire");
	x.move_to_cell(&sq, std::make_pair(0,3));
	REQUIRE(x.is_squad_in_cell(std::make_pair(4,4)) == NULL);
	bool is_dead;
	ll b,a;
	REQUIRE(x.squad_attack(std::make_pair(5,2), &sq, is_dead,b,a) == false);
}
