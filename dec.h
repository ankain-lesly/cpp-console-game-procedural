#ifndef GAME_H
#define GAME_H

using namespace std;

// functions
// Game
void start();
void run_game();
void intro_headers();
void game_headers();
void end_game_text();

// Canvas
void draw_canvas();
void init_setup_canvas();
void setup_collectables();
void setup_walls();

// Player
bool move_player();
void win_game_text();

// -- Colors
string C_Red(string text, bool bold = false);
string C_Green(string text, bool bold = false);
string C_Yellow(string text, bool bold = false);
string C_Blue(string text, bool bold = false);

#endif
