#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <dirent.h>
/*#include </home/guest/Documents/C/CandyCrush/CandyCrush/gamemechanic.cpp>*/
#include </home/guest/Documents/C/CandyCrush/CandyCrush/draw.cpp>
 
using namespace std;
 
/*--------------------------------------------------
 
Interface: Create Interface
 
--------------------------------------------------*/
 
 
 
class Interface{
  MainWindow window;
  public:
  Interface(int argc, char* argv[], Game newGame);
 
};
 
Interface::Interface(int argc, char* argv[], Game newGame) : window(newGame) {
  window.show(argc, argv);
  Fl::run();
}
 
int main(int argc, char *argv[])
{
    Game newGame;
    Interface interface(argc, argv, newGame);
    return 0;
}
