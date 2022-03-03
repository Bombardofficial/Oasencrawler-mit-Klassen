#include "game.h"
#include "player.h"
#include "world.h"
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;

game::game() { //connection between classes
    w = new world();
    p = new player(5);
    w->setPlayer(p);
    p->setWorld(w);
}

void game::start_game()
{
    system("Color E4");
    //LADEBILDSCHIRM
    cout << "                                                     ";
    cout << "O"; this_thread::sleep_for(chrono::milliseconds(50)); cout << "A"; this_thread::sleep_for(chrono::milliseconds(50));
    cout << "S"; this_thread::sleep_for(chrono::milliseconds(50)); cout << "E"; this_thread::sleep_for(chrono::milliseconds(50));
    cout << "N"; this_thread::sleep_for(chrono::milliseconds(50)); cout << "C"; this_thread::sleep_for(chrono::milliseconds(50));
    cout << "R"; this_thread::sleep_for(chrono::milliseconds(50)); cout << "A"; this_thread::sleep_for(chrono::milliseconds(50));
    cout << "W"; this_thread::sleep_for(chrono::milliseconds(50)); cout << "L"; this_thread::sleep_for(chrono::milliseconds(50));
    cout << "E"; this_thread::sleep_for(chrono::milliseconds(50)); cout << "R"; this_thread::sleep_for(chrono::milliseconds(250));
    cout << endl << endl << "                                                     ";
    cout << "Loading "; this_thread::sleep_for(chrono::milliseconds(500)); cout << "."; this_thread::sleep_for(chrono::milliseconds(300));
    cout << "."; this_thread::sleep_for(chrono::milliseconds(200)); cout << "."; this_thread::sleep_for(chrono::milliseconds(1000));
    system("cls");

    cout << "Your name: " << endl;
    cin >> name;
    system("cls");

    cout << "Welcome " << name << "!" << endl;

    cout << "You ended up in an abandoned cave where, according to legends, many natives live, protecting hundreds of years old relics. " << endl
        << "Your mission is to collect the stolen relics without losing all of your lives." << endl
        << "You have five lives, however, you can relax in various hiding places in the cave where you can earn bonus lives." << endl << "Good luck!" << endl << endl << endl;

    system("pause");
    system("cls");
    w->generate_world();
    w->generate_elements();

    thegame();
}


void game::thegame()
{
    srand(time(NULL)); //enabling the randomization function
    cout << "                              Controls:              W  -> up" << endl;
    cout << "                                          left <- A  S  D -> right" << endl;
    cout << "                                                     |" << endl;
    cout << "                                                    down" << endl;
    do {
        
        w->printWorld();
        p->richtung();
        system("cls");
        w->elementcheck();
        
        if (p->won()) {
            level++;
            if (level < 4) {
                cout << endl << "YOU FOUND ALL THE RELICS IN THIS PART OF THE CAVE!" << endl
                    << "MOVE ON AND FIND MORE RELICS, BUT WATCH OUT! THERE ARE MORE NATIVES THAN YOU THINK!" << endl;

                system("pause");
                system("cls");

                p->relicscounter = 0;
                p->life = 5;
                w->max_relics;
                p->pos_X = 0;
                p->pos_Y = 0;
                w->level_rand = w->level_rand + 2;

                w->generate_world();
                w->generate_elements();
            }
            else {
                cout << "CONGRATULATION! YOU COLLECTED ALL OF THE RELICS ON EVERY LEVEL! YOU WON!" << endl;
                exit(0);
            }
        }
        


    } while (p->life >= 0 && level != 4);
    cout << "\nUnfortunately the natives got you and you could not escape in time!" << endl;
    cout << "Game over!" << endl;
}
