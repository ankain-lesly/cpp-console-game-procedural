#include <iostream>
#include "dec.h"
#include "vector"
#include "conio.h"
#include "stdlib.h"

using namespace std;

// Game
bool isPlaying = false;
// int position = 0;

int POSITION_Y = 0;
int POSITION_X = 0;

// GAME PLAY
int CANVAS_SIZE = 12; // L1 = 12 | L2 = 20
int items_total = 12; // L1 = 10 | L2 20
int items_collected = 0;
bool end_game = false;
bool isWin = false;

// Canvas
// string CANVAS = {{}};
vector<vector<string>> CANVAS;

// Game Objects
string OBJECT_WALL = C_Yellow(" # ");
string OBJECT_TRASH = C_Red(" @ ");
// string OBJECT_PLAYER = C_Green(" X ", true);
string OBJECT_PLAYER = C_Green(" O ", true);
string OBJECT_SPACER = " . ";

// Initialize Game states
void start()
{
  // position = 13;
  POSITION_Y = 8;
  POSITION_X = 5;

  intro_headers();
  init_setup_canvas();

  // Start Game
  cout << "\n >>\t Press [Enter] to begin: \n\n";
  getchar();
  draw_canvas();
  isPlaying = true;

  run_game();
}

// Create Game Canvas
void draw_canvas()
{
  // get coordinated from position
  game_headers();

  cout << C_Yellow("*****************************************") << endl;
  cout << C_Yellow("*****************************************") << endl;

  // cout << "*                                       *\n";
  // cout << "*    ...                                *\n";
  // cout << "*\n*   ...\n";
  for (int x = 0; x < CANVAS_SIZE; x++)
  {
    // cout << "*  ";
    cout << "***";
    for (int y = 0; y < CANVAS_SIZE; y++)
    {
      cout << CANVAS[x][y];
    }
    cout << "**\n";
  }
  // cout << "*                                       *\n";
  cout << C_Yellow("*****************************************") << endl;
  cout << C_Yellow("*****************************************") << endl;

  // cout << "...\n";
}

void init_setup_canvas()
{
  for (int x = 0; x < CANVAS_SIZE; x++)
  {
    vector<string> row;
    for (int y = 0; y < CANVAS_SIZE; y++)
    {
      if (x == POSITION_Y && y == POSITION_X)
        row.push_back(OBJECT_PLAYER);
      else if (x == 0 || x == CANVAS_SIZE - 1 || y == 0 || y == CANVAS_SIZE - 1)
        row.push_back(OBJECT_WALL);
      else
        row.push_back(OBJECT_SPACER);
    }
    CANVAS.push_back(row);
  }
  // >>
  setup_walls();
  setup_collectables();
}

// Add Collectable items
void setup_collectables()
{
  int x, y, counter = 0;

  while (counter < items_total)
  {
    x = rand() % CANVAS_SIZE;
    y = rand() % CANVAS_SIZE;

    // cout << endl
    //      << "x: " << x << endl
    //      << "y: " << y << endl
    //      << "@Canvas: " << CANVAS[x][y] << endl
    //      << "counter: " << counter << endl;

    if (CANVAS[x][y] == OBJECT_SPACER)
    {
      CANVAS[x][y] = OBJECT_TRASH;
      counter++;
      continue;
    }
  }
}

// Add Walls
void setup_walls()
{
  // int walls[CANVAS_SIZE][2] = {
  int x, y, WALL_AMOUNT = 20;

  int wall[WALL_AMOUNT][2] = {
      {6, 1},
      {6, 2},
      {6, 3},
      {6, 4},
      {7, 4},
      {8, 4},
      {9, 4},
      {2, 8},
      {4, 9},
      {3, 8},
      {4, 8},
      {4, 7},
      {4, 6},
      {4, 5},
      {4, 8},
      {5, 8},
      {6, 8},
      {7, 8},
  };

  for (int i = 0; i < WALL_AMOUNT; i++)
  {
    x = wall[i][0];
    y = wall[i][1];

    if (!x || !y)
      continue;

    CANVAS[x][y] = OBJECT_WALL;
  }
}

// Run Game
void run_game()
{
  // GAME_STATE Game timeout

  // while in array [key]
  int key = 0;
  while (!end_game && !isWin)
  // if (true)
  {
    // Clear Screen
    system("CLS");
    draw_canvas();
    move_player();
    // GAME_STATE Player Win
  }

  if (isWin)
    win_game_text();
  if (end_game)
    end_game_text();
  // GAME_STATE Player loose
}

bool move_player()
{
  // update position
  char key;
  key = getch();
  int posY = POSITION_Y;
  int posX = POSITION_X;

  // if (key == 75 && POSITION_X > 0 && POSITION_X < CANVAS_SIZE - 1)
  if (key == 75 && POSITION_X > 1)
  {
    // cout << "\nMoving left: " << POSITION_X << endl;
    POSITION_X--;
  }
  else if (key == 77 && POSITION_X < CANVAS_SIZE - 2)
  {
    // cout << "\nMoving right: " << POSITION_X << endl;
    POSITION_X++;
  }
  else if (key == 72 && POSITION_Y > 1)
  {
    // cout << "\nMoving up: " << POSITION_Y << endl;
    POSITION_Y--;
  }
  else if (key == 80 && POSITION_Y < CANVAS_SIZE - 2)
  {
    // cout << "\nMoving down: " << POSITION_Y << endl;
    POSITION_Y++;
  }

  // Add Score
  if (items_collected >= items_total)
    isWin = true;
  //-- TRASH Collision
  if (CANVAS[POSITION_Y][POSITION_X] == OBJECT_TRASH)
    items_collected++;

  // Wall Collision
  if (CANVAS[POSITION_Y][POSITION_X] == OBJECT_WALL)
  {
    POSITION_X = posX;
    POSITION_Y = posY;
    return false;
  }

  // Exit
  if (key == 81 || key == 113)
    end_game = true;
  // return void;
  // break;

  // Update CANVAS
  CANVAS[posY][posX] = OBJECT_SPACER;
  CANVAS[POSITION_Y][POSITION_X] = OBJECT_PLAYER;
  // game_board.get_cell(x, y) = Cell(this->symbol);
  return true;
}

// Game Start Instructions
void intro_headers()
{
  cout << endl
       << endl
       << endl;
  cout << C_Green("---------------------------------- ") << endl;
  cout << C_Green("- <<<<< ROBOT CLEANER GAME >>>>> -", true) << endl;
  cout << C_Green("---------------------------------- ") << "\n*\n";
  cout << C_Yellow("* INSTRUCTIONS [PRESS] >> ") << "\n*\n";
  cout << "* [Q > Exit, ]" << endl;
  cout << "* [USE ARROW KEYS TO PLAY] \n"
       << endl;
  cout << "* --------------------------------- \n";
  cout << "*  " + C_Blue("UP") + " <> " + C_Blue("DOWN") + " <> " + C_Blue("LEFT") + " <> " + C_Blue("RIGHT") + "" << endl;
  cout << "* --------------------------------- \n";
}

// Game Play Header
void game_headers()
{
  cout << "\n       " + C_Green("       LEVEL - ONE ", true) + "        \n";
  cout << "*****************************************" << endl;
  cout << "*        " + C_Green("<< GAME PLAY - PRESS >>", true) + "        *\n";
  cout << "*                                       * \n";

  cout << "* ------------------------------------- *\n";
  cout << "*      " + C_Blue("UP") + " <> " + C_Blue("DOWN") + " <> " + C_Blue("LEFT") + " <> " + C_Blue("RIGHT") + "      *" << endl;
  cout << "* ------------------------------------- *\n";
  cout << "*      " + C_Yellow("Collected") + ": [" << items_collected << "], " + C_Yellow("Left") + ": [" << items_total - items_collected << "]        * \n";
  cout << "*                                       * \n";
  cout << "*     [Q > Exit, P > Pause, S, Save]    * \n";
  cout << "*****************************************" << endl;
}

void end_game_text()
{
  cout
      << endl
      << endl
      << C_Red("   \t | >>\n")
      << C_Red(" >>\t | Exiting Game...\n")
      << C_Red("   \t | >>")
      << endl;
}

void win_game_text()
{
  cout
      << endl
      << endl
      << "   \t " + C_Green("| >>  >>  >>  >> >>") + " \n"
      << " " + C_Green(">>") + "\t | " + C_Green("Woohuu You Won!..") + "\n"
      << "   \t " + C_Green("| >>  >>  >>  >> >>") + " \n"
      << endl
      << endl
      << " >>\t Press T to Play Again!"
      << endl
      << " >>\t ..."
      << endl
      << endl;

  // cout << "\n >>\t Press [Enter] to begin: \n\n";
  // getchar();
}

// Colors >> Red
string C_Red(string text, bool bold)
{
  if (bold)
    return "\033[1m\033[31m" + text + "\033[0m";
  else
    return "\033[31m" + text + "\033[0m";
}
// Colors >> Green
string C_Green(string text, bool bold)
{
  if (bold)
    return "\033[1m\033[32m" + text + "\033[0m";
  else
    return "\033[32m" + text + "\033[0m";
}
// Colors >> Yellow
string C_Yellow(string text, bool bold)
{
  if (bold)
    return "\033[1m\033[33m" + text + "\033[0m";
  else
    return "\033[33m" + text + "\033[0m";
}
// Colors >> Blue
string C_Blue(string text, bool bold)
{
  if (bold)
    return "\033[1m\033[34m" + text + "\033[0m";
  else
    return "\033[34m" + text + "\033[0m";
}
