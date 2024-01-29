#include "include/classes.hpp"
#include "include/matrix.hpp"
#include "../raylib/src/raylib.h"
#include <string>
#include <iostream>

void Graphics_UI::ToggleFullScreenWindow(int windowWidth, int windowHeight)
{
	        /*ToggleFullscreen();
                SetWindowSize(windowWidth, windowHeight);*/
	if (!IsWindowFullscreen())
	{
		int monitor = GetCurrentMonitor();
		SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
		ToggleFullscreen();
	}
	else
	{
		SetWindowSize(windowWidth, windowHeight);
		ToggleFullscreen();
		//SetWindowSize(windowWidth, windowHeight);
	}
}

void Graphics_UI::StartScreen(const int screenWidth, const int screenHeight)
{
		InitWindow(screenWidth, 450, "Summoning masters");

        	SetTargetFPS(60);

		ClearBackground(RAYWHITE);

                while (!IsKeyPressed(32) && !WindowShouldClose())
                {
                        if (IsKeyPressed(KEY_ENTER) && (IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)))
                        	ToggleFullScreenWindow(screenWidth, screenHeight);
                        BeginDrawing();

                        DrawText("Press Space to start the game", 300, 350, 20, BLACK);

                        DrawTexture(LoadTexture("gigachad.png"), 330, 100, WHITE);

                        EndDrawing();
                }

                //CloseWindow();
}

void Graphics_UI::DrawingMap(Game g, matr<bool> *m, const int screenWidth, const int screenHeight)
{
		BeginDrawing();
		DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
		EndDrawing();

		COLOR player_color = this->choose_color();

                BeginDrawing();
                DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
                EndDrawing();

                while (!WindowShouldClose())
                {

                        BeginDrawing();

                        for (int i = 0; i < screenWidth/160; i++)
                        {
                                for (int j=0; j < screenHeight/76; j++)
                                {
                                        DrawRectangleLines(j*80, i*76, 80, 76, BLACK);
                                        if ((*m)[i][j] == 1)
                                        {
                                                DrawRectangle(j*80, i*76, 80, 76, BLACK);
                                        }
                                }
                        }

                        DrawRectangle(40,38, 15, 15, RED);
                        DrawRectangle(screenWidth - 40 - 480, screenHeight - 38, 15, 15, BLUE);

                        EndDrawing();

                        bool cond = g.commit_one_iteration(screenWidth, screenHeight, player_color);
                        if (cond)
                        {
                                while (!IsKeyPressed(32) && !WindowShouldClose())
                                {
                                        BeginDrawing();
                                        DrawText("Press space to exit", 480, 325, 20, BLACK);
                                        EndDrawing();
                                }
                                break;
                        }
                }
                CloseWindow();
}

COLOR Graphics_UI::choose_color()
{
	int in_val = -1;
	while (in_val < 49 || in_val > 50)
	{
		BeginDrawing();
		DrawText("Choose your side:", 480, 200, 20, BLACK);
		DrawText("1. RED", 500, 240, 20, RED);
		DrawText("2. BLUE", 500, 280, 20, BLUE);
		EndDrawing();
		in_val = GetKeyPressed();
	}
	return in_val == 49 ? COLOR::red : COLOR::blue;
}

std::string Graphics_UI::improve_school()
{
	std::string res;
	int in_val = -1;
	while (in_val < 49 || in_val > 52)
	{
		BeginDrawing();
		DrawText("Choose school:", 600, 100, 20, BLACK);
		DrawText("1. Fire", 600, 170, 20, BLACK);
		DrawText("2. Water", 600, 240, 20, BLACK);
		DrawText("3. Terra", 600, 310, 20, BLACK);
		DrawText("4. Air", 600, 380, 20, BLACK);
		EndDrawing();
		in_val = GetKeyPressed();
	}
	switch(in_val)
	{
		case(49):
		{
			res = "Fire";
			break;
		}
		case(50):
		{
			res = "Water";
			break;
		}
		case(51):
		{
			res = "Terra";
			break;
		}
		case(52):
		{
			res = "Air";
			break;
		}
	}
	this->clear_right_side();
	return res;
}

void Graphics_UI::display_health(ll before, ll after)
{
	while (!IsKeyPressed(32))
	{
		BeginDrawing();
		std::string s1 = "ENEMY HEALTH BEFORE: ", str = s1 + std::to_string(before);
		DrawText(str.c_str(), 500, 170, 25, BLACK);
		std::string s2 = "ENEMY HEALTH AFTER: ", str_2 = s2 + std::to_string(after);
        	DrawText(str_2.c_str(), 500, 240, 25, BLACK);
		EndDrawing();
	}
	this->clear_right_side();
}

int Graphics_UI::summoner_move(Summoner *cur)
{
				int in_val = -1;
				while (in_val < 49 || in_val > 51)
				{
                                        COLOR c = cur->get_color();
                                        BeginDrawing();
                                        if (in_val == 0)
                                        {
                                                if (c == COLOR::red)
                                                {
                                                        DrawText("COLOR: RED", 600, 100, 30, RED);
                                                }
                                                else
                                                {
                                                        DrawText("COLOR: BLUE", 600, 100, 30, BLUE);
                                                }
                                                DrawText("Make your choice:", 600, 170, 20, BLACK);
                                                DrawText("1. Summon a squad", 600, 240, 20, BLACK);
                                                DrawText("2. Accumulate energy", 600, 310, 20, BLACK);
						DrawText("3. Improve knowledge of school", 600, 380, 20, BLACK);
						DrawText("for experience", 600, 410, 20, BLACK);
                                        }
                                        EndDrawing();
                                        in_val = GetKeyPressed();
                                }
                                this->clear_right_side();
				return in_val;
}

void Graphics_UI::game_over(const int screenWidth, const int screenHeight, COLOR s)
{
	Color win = s == COLOR::red ? RED : BLUE;
	BeginDrawing();
	DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
	if (s == COLOR::red)
		DrawText("RED WIN!", 480, 240, 20, win);
	else if (s == COLOR::blue)
		DrawText("BLUE WIN!", 480, 240, 20, win);
	EndDrawing();
}

void Graphics_UI::remove_squad(std::pair<int,int> old)
{
	BeginDrawing();
	DrawRectangle(old.second*80, old.first*76, 80, 76, RAYWHITE);
	DrawRectangleLines(old.second*80, old.first*76, 80, 76, RAYWHITE);
	EndDrawing();
}

int Graphics_UI::Squad_move(std::string skill_name, COLOR clr, std::pair<int,int> c)
{
	int in_val = -1;
	Color clr_2 = clr == COLOR::red ? RED : BLUE;
	while (in_val < 49 || in_val > 50)
	{
	BeginDrawing();
	if (clr == COLOR::red)
	{
        	DrawText("COLOR: RED", 600, 50, 20, clr_2);
	}
	else if (clr == COLOR::blue)
	{
		DrawText("COLOR: BLUE", 600, 50, 20, clr_2);
	}
	std::string s1 = "Coordinats: ", comma = ",";
	std::string str = s1 + std::to_string(c.first) + comma + std::to_string(c.second);
        DrawText(str.c_str(), 600, 110, 20, BLACK);
        DrawText("Make your choice:", 600, 170, 20, BLACK);
	DrawText("1. Move to cell", 600, 230, 20, BLACK);
	DrawText("2. Approach enemy squad", 600, 290, 20, BLACK);
	DrawText("or summoner and attack", 600, 350, 20, BLACK);
	EndDrawing();
	in_val = GetKeyPressed();
	}
      	this->clear_right_side();
	return in_val;
}

void Graphics_UI::DrawSquad(const int screenWidth, const int screenHeight, COLOR clr, std::pair<int,int> c, std::string skill_name)
{
			Color cur;
			if (clr == COLOR::red)
			{
				cur = RED;
			}
			else
			{
				cur = BLUE;
			}
			int i = c.first, j = c.second;
						BeginDrawing();
						if (skill_name == "Curses" || skill_name == "Curse")
						{
                                        		DrawTexture(LoadTexture("Curse.png"), j*80 + 10, i*76 + 10, cur);
						}
						else if (skill_name == "Executioners" || skill_name == "Executioner")
						{
							DrawTexture(LoadTexture("Executioner.png"), j*80 + 10, i*76 + 10, cur);
						}
						else if (skill_name == "Earth elementals" || skill_name == "Earth elemental")
						{
							DrawTexture(LoadTexture("earth_elemental.png"), j*80 + 5, i*76 + 10, cur);
						}
						else if (skill_name == "Air elementals" || skill_name == "Air elemental")
						{
							DrawTexture(LoadTexture("air_elemental.png"), j*80 + 5, i*76, cur);
						}
						else if (skill_name == "Water elementals" || skill_name == "Water elemental")
						{
							DrawTexture(LoadTexture("water_elemental.png"), j*80 + 5, i*76, cur);
						}
						else if (skill_name == "Heal" || skill_name == "Heals")
						{
							DrawTexture(LoadTexture("heal.png"), j*80 + 5, i*76, cur);
						}
						else if (skill_name == "Resurrection" || skill_name == "Resurrections")
						{
							 DrawTexture(LoadTexture("resurrection.png"), j*80 + 5, i*76, cur);
						}
						EndDrawing();
}

std::pair <int,int> Graphics_UI::convert_coordinats_from_pixels(const int screenWidth, const int screenHeight, int x, int y)
{
	for (int i = 0; i < screenWidth/160; i++)
	{
		for (int j = 0; j < screenHeight/76; j++)
		{
			if (x >= j*80 && x <= j*80 + 80 && y >= i*76 && y <= i*76 + 76)
			{
				return std::make_pair(i,j);
			}
		}
	}
}

std::pair <int,int> Graphics_UI::spawn_coordinats(const int screenWidth, const int screenHeight)
{
			while(1)
			{
                       		if( IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                        	{
						Vector2 v = GetMousePosition();
						return this->convert_coordinats_from_pixels(screenWidth, screenHeight, v.x, v.y);
                        	}
				BeginDrawing();
				EndDrawing();
			}
}

std::string Graphics_UI::ChooseSkill(std::string school_name)
{
	std::string res;
	int k = -1;
	if (school_name == "Fire")
	{
		while (k < 49 || k > 50)
		{
			BeginDrawing();
			DrawText("Choose a skill:", 600, 170, 20, BLACK);
                        DrawText("1. Executioners", 600, 230, 20, BLACK);
                        DrawText("2. Curses", 600, 290, 20, BLACK);
			EndDrawing();
			k = GetKeyPressed();
		}
		switch(k)
		{
			case(49):
				res = "Executioners";
				break;
			case(50):
				res = "Curses";
				break;
		}
	}
	else if (school_name == "Terra")
	{
		while (k < 49 || k > 50)
                {
                        BeginDrawing();
                        DrawText("Choose a skill:", 600, 170, 20, BLACK);
                        DrawText("1. Earth elementals", 600, 230, 20, BLACK);
                        DrawText("2. Resurrection", 600, 290, 20, BLACK);
                        EndDrawing();
                        k = GetKeyPressed();
                }
                switch(k)
                {
                        case(49):
                                res = "Earth elementals";
                                break;
                        case(50):
                                res = "Resurrection";
                                break;
                }
	}
	else if (school_name == "Water")
	{
                while (k < 49 || k > 50)
                {
                        BeginDrawing();
                        DrawText("Choose a skill:", 600, 170, 20, BLACK);
                        DrawText("1. Water elementals", 600, 230, 20, BLACK);
                        DrawText("2. Heal", 600, 290, 20, BLACK);
                        EndDrawing();
                        k = GetKeyPressed();
                }
                switch(k)
                {
                        case(49):
                                res = "Water elementals";
                                break;
                        case(50):
                                res = "Heal";
                                break;
                }
	}
	else if (school_name == "Air")
	{
                while (k != 49)
                {
                        BeginDrawing();
                        DrawText("Choose a skill:", 600, 170, 20, BLACK);
                        DrawText("1. Air elementals", 600, 230, 20, BLACK);
                        //DrawText("2. Heal", 600, 290, 20, BLACK);
                        EndDrawing();
                        k = GetKeyPressed();
                }
                switch(k)
                {
                        case(49):
                                res = "Air elementals";
                                break;
                        /*case(50):
                                res = "Heal";
                                break; */
                }
	}
        this->clear_right_side();
	return res;
}

std::string Graphics_UI::ChooseSchool()
{
		std::string res;
		int k = -1;
		while (k < 49 || k > 52)
		{
			BeginDrawing();
                	DrawText("Choose a school:", 600, 170, 20, BLACK);
                	DrawText("1. Fire", 600, 230, 20, BLACK);
                	DrawText("2. Terra", 600, 290, 20, BLACK);
                	DrawText("3. Water", 600, 350, 20, BLACK);
                	DrawText("4. Air", 600, 410, 20, BLACK);
               		EndDrawing();
			k = GetKeyPressed();
		}
		switch(k)
		{
			case(49):
				res = "Fire";
				break;
			case(50):
				res = "Terra";
				break;
			case(51):
				res = "Water";
				break;
			case(52):
				res = "Air";
				break;
		}
		this->clear_right_side();
		return res;
}

void Graphics_UI::clear_right_side()
{
                                BeginDrawing();
                                DrawRectangle(480, 0, 480, 456, RAYWHITE);
                                EndDrawing();
}
