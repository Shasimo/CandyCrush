#include <iostream>
#include <memory>
#include <vector>
#include <fstream>

using namespace std;

class Game{
    /*********
    Singleton code from class INFO-F-202
    **********/
    static unique_ptr<Game> singleton;
    ofstream fileSprite;
    vector<ofstream> candySprite;

    Game(): fileSprite{"Sprites"} {};

    public:

    void drawBoard(const string message)
    {
        cout << message;
    }

    static Game &create(){
        if (!singleton)
            singleton=unique_ptr<Game>(new Game());
            return *singleton;
    }

};

unique_ptr<Game> Game::singleton;

int main()
{
    Game::create().drawBoard("Bonjour");
    return 0;
}
