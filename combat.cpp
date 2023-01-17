#include <iostream>
#include <random>
#include <array>
#include "personne.h"
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include "color.hpp"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// Class methods

Character::Character(std::string name = "Unnamed Character", int hp = 100, int dmg = 0, std::vector<std::string> List = {{}})
    : name(name), health(hp), dmg(dmg), voice_lines(List){};
Character::~Character() {}

void Character::receiveDamage(int dmg)
{
    if (dmg > this->health)
    {
        this->health = 0;
    }
    else
    {
        this->health -= dmg;
    }
}

void Character::punch(Character &pl1) { pl1.receiveDamage(this->dmg); }

void Character::yell()
{
    srand(time(0));
    int rng = rand() % this->voice_lines.size();
    std::cout << "YELLS: " << dye::on_red(this->voice_lines.at(rng)) << "\n";
}

// List of fighters

std::vector<Character> Fighters{{"Johny Cage", 110, 10, {{"Those were $500 sunglasses, asshole."}, {"I'm so pretty!"}, {"No one can be as strong or as fast as a Cage"}}}, {"Jade", 100, 15, {{"This will be easy"}, {"You make it too easy."}, {"Pitiful effort."}}}, {"Raiden", 120, 10, {{"Let's see if you have what it takes."}, {"You talk too much."}, {"You fought well."}}}, {"Kitana", 100, 15, {{"It was necessary, I assure you"}, {"The mere sight of you makes me ill."}, {"Your death is the only cure"}}}, {"Scorpion", 90, 20, {{"GET OVER HERE!", {"Vengeance will be mine"}, {"To HELL with you!"}}}}, {"Sub-Zero", 105, 15, {{"This fight will be your last!"}, {"Talking. Always his first choice."}, {"I am Sub-Zero."}}}};

void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(h, c);
}

void border()
{
    system("cls");

    for (int i = 25, j = 6; i <= 100; i++)
    {
        gotoxy(i, j);
        std::cout << "=";
    }

    for (int j = 7, i = 25; j <= 26; j++)
    {
        gotoxy(i, j);
        std::cout << "||";
    }

    for (int i = 25, j = 26; i <= 100; i++)
    {
        gotoxy(i, j);
        std::cout << "=";
    }

    for (int j = 7, i = 100; j <= 25; j++)
    {
        gotoxy(i, j);
        std::cout << "||";
    }
}

void Display_Fighters()
{

    gotoxy(40, 10);
    std::cout << "Name";
    gotoxy(60, 10);
    std::cout << "Health";
    gotoxy(80, 10);
    std::cout << "Damage";
    for (int x = 40, y = 13, i = 0; i < Fighters.size(); i++, x = 40)
    {
        gotoxy(x, y + (i * 2));
        std::cout << Fighters.at(i).name;
        x += 20;
        gotoxy(x, y + (i * 2));
        std::cout << Fighters.at(i).health;
        x += 20;
        gotoxy(x, y + (i * 2));
        std::cout << Fighters.at(i).dmg;
    }
}

void color_fighter(int choice)
{

    for (int x = 40, y = 13, i = choice; i <= choice; i++, x = 40)
    {
        gotoxy(x, y + (i * 2));
        std::cout << dye::on_red(Fighters.at(i).name);
        x += 20;
        gotoxy(x, y + (i * 2));
        std::cout << dye::on_red(Fighters.at(i).health);
        x += 20;
        gotoxy(x, y + (i * 2));
        std::cout << dye::on_red(Fighters.at(i).dmg);
    }
}

int select_fighter()
{
    int choice = 0;
    while (true)
    {
        Display_Fighters();
        color_fighter(choice);
        gotoxy(40, 13);
        int ch = _getch();
        if (ch == 224)
        {
            switch (ch = _getch())
            {
            case KEY_DOWN:

                choice++;
                break;
            case KEY_UP:
                choice--;
                break;
            }
        }

        else if (ch == 13)
        {
            std::cout << "Character Chosen\n";
            break;
        }

        else
        {
            std::cout << "Use On Of The Arrow Keys";
        }
    }
    return choice;
}

void display_name(int id, int x)
{
    gotoxy(x, 11);
    std::cout << Fighters.at(id).name;
}

void health_bars(int player_id1, int player_id2)
{
    border();
    int health_pl1 = Fighters.at(player_id1).health;
    display_name(player_id1, 30);

    for (int i = 30; i <= health_pl1 / 5 + 30; i++)
    {
        gotoxy(i, 9);
        std::cout << dye::on_red(" ");
    }
    int health_pl2 = Fighters.at(player_id2).health;
    {
        display_name(player_id2, 70);
        for (int i = 70; i <= health_pl1 / 5 + 70; i++)
        {
            gotoxy(i, 9);
            std::cout << dye::on_red(" ");
        }
    }
}

void Display_Options(int turn)
{
    if (turn % 2 == 0)
    {
        gotoxy(40, 14);
        std::cout << "Attack";
        gotoxy(40, 16);
        std::cout << "Taunt";
        turn = 1;
    }

    else
    {
        gotoxy(70, 14);
        std::cout << "Attack";
        gotoxy(70, 16);
        std::cout << "Taunt";
        turn = 0;
    }
}

void Color_Display_Options(int turn, int choice)
{
    if (turn % 2 == 0)
    {
        if (choice == 0)
        {
            gotoxy(40, 14);
            std::cout << dye::on_red("Attack");
        }
        else
        {
            gotoxy(40, 16);
            std::cout << dye::on_red("Taunt");
        }
    }

    else
    {
        if (choice == 0)
        {
            gotoxy(70, 14);
            std::cout << dye::on_red("Attack");
        }
        else
        {
            gotoxy(70, 16);
            std::cout << dye::on_red("Taunt");
        }
    }
}

int Options()
{
    int choice = 0;
    static int turn = 0;

    while (true)
    {
        Display_Options(turn);
        Color_Display_Options(turn, choice);
        int ch = _getch();
        if (ch == 224)
        {
            switch (ch = _getch())
            {
            case KEY_DOWN:
                choice++;
                break;
            case KEY_UP:
                choice--;
                break;
            }
        }
        else if (ch == 13)
        {
            turn++;
            break;
        }
    }

    return choice;
}

void game_system(int player_1, int player_2)
{
    int current_player = player_1;
    int next_player = player_2;
    health_bars(player_1, player_2);
    do
    {
        switch (Options())
        {
        case 0:
            Fighters.at(current_player).punch(Fighters.at(next_player));
            break;
        case 1:
            gotoxy(40, 16);
            Fighters.at(current_player).yell();
            Sleep(3000);
            break;
        }
        health_bars(player_1, player_2);
        std::swap(current_player, next_player);
        

    } while (Fighters.at(player_1).health > 0 && Fighters.at(player_2).health > 0);
}

void starting_menu()
{
    border();
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); // Gets the consol handle in plain english the resources needed to modify stuff on consol
    SetConsoleTextAttribute(console, 4);              // This function sets the text on consol to a specific color in this case red
    gotoxy(55, 14);
    std::cout << "Mortal Kombat";
    SetConsoleTextAttribute(console, 15);
    gotoxy(55, 17);
    std::cout << "Press Any Key";
    gotoxy(55, 14);
    std::cout << "              ";
    gotoxy(55, 17);
    std::cout << "              ";
    Display_Fighters();
    int player1 = select_fighter();
    fflush(stdin);
    int player2 = select_fighter();
    system("cls");
    health_bars(player1, player2);
    game_system(player1, player2);
}



int main(int argc, char const *argv[])
{

    starting_menu();
}
