#include <iostream>
#include "Utilities.h"
#include <windows.h>
#include <thread>
#include <chrono>
#include <mmsystem.h>
#include "Game.h"
#include "Bot.h"
#include "PlayerManager.h"
#include "PlayWithPlayer.h"
#include "ReplayManager.h"

#pragma comment(lib, "winmm.lib") // Link Windows multimedia library

using namespace std;

// Set cursor position
void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to play background music
void playBackgroundMusic(const std::string& musicFile) {
    // Convert std::string to LPCWSTR for PlaySound
    std::wstring wideString = std::wstring(musicFile.begin(), musicFile.end());
    LPCWSTR wideCharString = wideString.c_str();

    PlaySound(wideCharString, NULL, SND_ASYNC | SND_LOOP);
}

// Function to display Caro animation
void PrintCaro() {
    int x = 25, y = 0;
    Textcolor(rand() % 15 + 1);
    gotoXY(x, y);                cout << "ooooooooooooo";
    gotoXY(x - 3, y + 1);        cout << "oooooooooooooooo";
    gotoXY(x - 5, y + 2);        cout << "oooooooooooooooooo";
    gotoXY(x - 6, y + 3);        cout << "ooooooooooooooooooo";
    Textcolor(rand() % 15 + 1);
    gotoXY(x - 7, y + 4);        cout << "ooooooo";
    gotoXY(x - 8, y + 5);        cout << "ooooooo";
    gotoXY(x - 8, y + 6);        cout << "ooooooo";
    gotoXY(x - 8, y + 7);        cout << "ooooooo";
    gotoXY(x - 8, y + 8);        cout << "ooooooo";
    gotoXY(x - 8, y + 9);        cout << "ooooooo";
    Textcolor(rand() % 15 + 1);
    gotoXY(x - 8, y + 10);       cout << "ooooooo";
    gotoXY(x - 7, y + 11);       cout << "ooooooo";
    gotoXY(x - 6, y + 12);       cout << "ooooooooooooooooooo";
    gotoXY(x - 5, y + 13);       cout << "oooooooooooooooooo";
    Textcolor(rand() % 15 + 1);
    gotoXY(x - 3, y + 14);       cout << "oooooooooooooooo";
    gotoXY(x, y + 15);           cout << "ooooooooooooo";
    Textcolor(rand() % 15 + 1);
    gotoXY(x - 4 + 22, y + 4);				    cout << "ooooooooooo";
    gotoXY(x - 4 + 22 - 2, y + 5);		      cout << "ooooooooooooooo";
    gotoXY(x - 4 + 22 - 3, y + 6);		     cout << "ooooooooooooooooo";
    Textcolor(rand() % 15 + 1);
    gotoXY(x - 4 + 22 - 3, y + 7);			 cout << "ooooooooooooooooo";
    gotoXY(x - 4 + 22 - 3, y + 8);			 cout << "oooooo     oooooo";
    gotoXY(x - 4 + 22 - 3, y + 9);			 cout << "oooooo     oooooo";
    Textcolor(rand() % 15 + 1);
    gotoXY(x - 4 + 22 - 3, y + 10);		 cout << "oooooo     oooooo";
    gotoXY(x - 4 + 22 - 3, y + 11);		 cout << "ooooooooooooooooo";
    gotoXY(x - 4 + 22 - 3, y + 12);		 cout << "oooooo     oooooo";
    Textcolor(rand() % 15 + 1);
    gotoXY(x - 4 + 22 - 3, y + 13);		 cout << "oooooo     oooooo";
    gotoXY(x - 4 + 22 - 3, y + 14);		 cout << "oooooo     oooooo";
    gotoXY(x - 4 + 22 - 3, y + 15);		 cout << "oooooo     oooooo";

    Textcolor(rand() % 15 + 1);

    gotoXY(x + 33, y + 4);			cout << "ooooo   ooooooooo";
    gotoXY(x + 33, y + 5);			cout << "oooooooooooooooooo";
    gotoXY(x + 33, y + 6);			cout << "ooooooooooooooooooo";
    Textcolor(rand() % 15 + 1);
    gotoXY(x + 33, y + 7);			cout << "oooooooooooooooooooo";
    gotoXY(x + 1 + 33, y + 8);			 cout << "ooooooo     ooooooo";
    gotoXY(x + 1 + 33, y + 9);			 cout << "ooooooo     ooooooo";
    Textcolor(rand() % 15 + 1);
    gotoXY(x + 1 + 33, y + 10);		 cout << "ooooooo";
    gotoXY(x + 1 + 33, y + 11);		 cout << "ooooooo";
    gotoXY(x + 1 + 33, y + 12);		 cout << "ooooooo";
    Textcolor(rand() % 15 + 1);
    gotoXY(x + 1 + 33, y + 13);		 cout << "ooooooo";
    gotoXY(x + 1 + 33, y + 14);		 cout << "ooooooo";
    gotoXY(x + 1 + 33, y + 15);		 cout << "ooooooo";
    // Textcolor(Yellow);
    gotoXY(x + 57, y + 4);					cout << "ooooooooooo";
    gotoXY(x + 57 - 2, y + 5);			  cout << "ooooooooooooooo";
    Textcolor(rand() % 15 + 1);
    gotoXY(x + 57 - 3, y + 6);			 cout << "ooooooooooooooooo";
    gotoXY(x + 57 - 3, y + 7);			 cout << "ooooooooooooooooo";
    Textcolor(rand() % 15 + 1);
    gotoXY(x + 57 - 3, y + 8);			 cout << "oooooo     oooooo";
    gotoXY(x + 57 - 3, y + 9);			 cout << "oooooo     oooooo";
    gotoXY(x + 57 - 3, y + 10);		 cout << "oooooo     oooooo";
    gotoXY(x + 57 - 3, y + 11);		 cout << "oooooo     oooooo";
    Textcolor(rand() % 15 + 1);
    gotoXY(x + 57 - 3, y + 12);		 cout << "ooooooooooooooooo";
    gotoXY(x + 57 - 3, y + 13);		 cout << "ooooooooooooooooo";
    Textcolor(rand() % 15 + 1);
    gotoXY(x + 57 - 2, y + 14);		  cout << "ooooooooooooooo";
    gotoXY(x + 57, y + 15);				cout << "ooooooooooo";
    // Adjust menu position below the animation
    gotoXY(0, y + 20); // Move the cursor to a new line for the menu
}

// Display guidelines for the game
void showGuidelines() {
    Textcolor(14); // Yellow
    cout << "\nGUIDELINES\n";
    cout << "1. Tic Tac Toe is played on a 10x10 grid.\n";
    cout << "2. Players take turns placing their symbol (X or O).\n";
    cout << "3. Align 5 of your symbols consecutively to win (horizontally, vertically, or diagonally).\n";
    cout << "4. Modes:\n";
    cout << "   - Easy: Bot makes random moves.\n";
    cout << "   - Normal: Bot uses basic strategy.\n";
    cout << "   - Hard: Bot uses advanced strategies with depth analysis.\n";
    cout << "5. Replay past games using the replay option.\n";
    Textcolor(7); // Reset to default
}

// Display the menu
void showMenu() {
    system("CLS");
    PrintCaro();   // Display animation

    Textcolor(11); // Light Cyan for menu

    // Center menu
    int menuX = 40, menuY = 16; // Adjust X and Y for positioning
    gotoXY(menuX, menuY);
    Textcolor(14);
    cout << "******************************************";
    gotoXY(menuX, menuY + 1); cout << "              MAIN MENU              ";
    gotoXY(menuX, menuY + 2); cout << "******************************************";
    Textcolor(13);
    gotoXY(menuX, menuY + 3); cout << "1. Guidelines";
    gotoXY(menuX, menuY + 4); cout << "2. Play with BOT (Easy)";
    gotoXY(menuX, menuY + 5); cout << "3. Play with BOT (Normal)";
    gotoXY(menuX, menuY + 6); cout << "4. Play with BOT (Hard)";
    gotoXY(menuX, menuY + 7); cout << "5. Play with Another Player";
    gotoXY(menuX, menuY + 8); cout << "6. Search Player";
    gotoXY(menuX, menuY + 9); cout << "7. Rewatch Game Replay";
    gotoXY(menuX, menuY + 10); cout << "8. Exit";
    gotoXY(menuX, menuY + 11);
    Textcolor(14);
    cout << "******************************************";
    Textcolor(7); // Reset to default

    gotoXY(menuX, menuY + 12); // Center the "Choose an option" text
    Textcolor(14);
    cout << "Choose an option: ";
    Textcolor(7);
}

// Main function
int main() {
    srand(time(0)); // Seed random number generator
    ReplayManager replayManager;
    PlayerManager playerManager;
    playerManager.loadPlayersFromFile("player.txt");

    playBackgroundMusic("background.wav");

    int choice;
    string p1;

    cout << "Welcome to Caro Tic Tac Toe!" << endl;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: // Guidelines
            showGuidelines();
            system("pause"); // Pause to allow user to read
            break;
        case 2: { // Easy Bot
            cout << "Enter your name: ";
            cin >> p1;
            Bot bot(Bot::EASY);
            Game game(p1, &bot);
            vector<string> moves = game.startGameWithBot();
            replayManager.saveReplay("Replay_Bot_Easy.txt", moves);
            break;
        }
        case 3: { // Normal Bot
            cout << "Enter your name: ";
            cin >> p1;
            Bot bot(Bot::NORMAL);
            Game game(p1, &bot);
            vector<string> moves = game.startGameWithBot();
            replayManager.saveReplay("Replay_Bot_Normal.txt", moves);
            break;
        }
        case 4: { // Hard Bot
            cout << "Enter your name: ";
            cin >> p1;
            Bot bot(Bot::HARD);
            Game game(p1, &bot);
            vector<string> moves = game.startGameWithBot();
            replayManager.saveReplay("Replay_Bot_Hard.txt", moves);
            break;
        }
        case 5: { // Play with Player
            PlayWithPlayer playWithPlayer;
            vector<string> moves = playWithPlayer.startGame();
            replayManager.saveReplay("Replay_Player_vs_Player.txt", moves);
            break;
        }
        case 6: { // Search Player
            string playerName;
            cout << "Enter player name to search: ";
            cin >> playerName;
            playerManager.searchPlayerByName(playerName);
            break;
        }
        case 7: { // Rewatch Replay
            string replayFile;
            cout << "Enter replay file name to watch: ";
            cin >> replayFile;
            replayManager.rewatchReplay(replayFile);
            break;
        }
        case 8: // Exit
            cout << "Exiting the game. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Try again!" << endl;
        }
    }
}
