#include "game.h"
#include "player.h"
#include "world.h"
#include <chrono>
#include <thread>
#include <cassert>
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
    cout << "                                                     ";
    cout << "Welcome " << name << "!" << endl;

    cout << "\nYou ended up in an abandoned cave where, according to legends, many natives live, protecting hundreds of years old relics. " << endl
        << "Your mission is to collect the stolen relics without losing all of your lives." << endl
        << "You have five lives, however, you can relax in various hiding places in the cave where you can earn bonus lives." << endl << "Good luck!" << endl << endl << endl;

    system("pause");
    system("cls");
    cout << "You can choose between two different characters to play with.\n\nAdventurer: easier to evade enemies, but takes more damage if you make the wrong choice.\nExplorer: harder to evade enemies, but takes less damage if you make the wrong choice." << endl;
        
    cout << "\nWhich character do you choose? Adventurer(1) or Researcher(2)?" << endl;

    int castchoose;
    do {
        cin >> castchoose;
        if (castchoose != 1 && castchoose != 2) {
            cout << "Not possible." << endl;
            if (cin.fail()) { // if the answer is not proper for the integer variable
                cin.clear();
                string s;
                cin >> s;
            }
        }
    } while (castchoose != 1 && castchoose != 2);
    if (castchoose == 1) {
        p->adventurer = true;
        p->researcher = false;
    }
    else if (castchoose == 2) {
        p->adventurer = false;
        p->researcher = true;
    }
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
            assert(p->won() == true);
            level++;
            if (level < 4) {
                assert(level < 4);
                cout << endl << "YOU FOUND ALL THE RELICS IN THIS PART OF THE CAVE!" << endl
                    << "MOVE ON AND FIND MORE RELICS, BUT WATCH OUT! THERE ARE MORE NATIVES THAN YOU THINK!\n" << endl;

                system("pause");
                system("cls");

                p->relicscounter = 0;
                p->life = 5;
                w->max_relics = 0;
                p->pos_X = 0;
                p->pos_Y = 0;
                w->level_rand = w->level_rand + 2;

                w->generate_world();
                w->generate_elements();
            }
            else {
                system("cls");
                cout << "\nCONGRATULATION! YOU COLLECTED ALL OF THE RELICS ON EVERY LEVEL! YOU WON!" << endl;
                exit(0);
            }
        }
        


    } while (p->life >= 0 && level != 4);
    cout << "\nUnfortunately the natives got you and you could not escape in time!" << endl;
    cout << "Game over!" << endl;
}
