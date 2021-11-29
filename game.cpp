#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <dirent.h>
#include </home/guest/Documents/C/CandyCrush/CandyCrush/draw.cpp>

using namespace std;

/*--------------------------------------------------
 
Interface: Create Interface
 
--------------------------------------------------*/

class Interface
 {
   static unique_ptr<Interface> singleton;
   Interface() {};

   public:

   static Interface &create(){
       if (!singleton)
       singleton=unique_ptr<Interface>(new Interface());
       return *singleton;}

   void getWindow(int argc, char *argv[]);
   vector <char*> receivePNGFromSpriteDir();
    
 };



unique_ptr<Interface> Interface::singleton;


void Interface::getWindow(int argc, char *argv[]) {     
     auto candySpritesVector=receivePNGFromSpriteDir();

     srand(time(0));
     MainWindow window(candySpritesVector);
     window.show(argc, argv);
     Fl::run();
}


vector <char*> Interface::receivePNGFromSpriteDir(){
  vector <char*> v;

  struct dirent *entry=nullptr;
  DIR *dp = nullptr;
  dp = opendir("Sprites");
  while((entry = readdir(dp))){

  string candySprite=entry->d_name;
  char* candySprite_2=entry->d_name;

  if(candySprite.find(".png") != string::npos){
  v.push_back(candySprite_2);
  }
  }
  return v;
}

/*****
*****/

int main(int argc, char *argv[])
{
    Interface::create().getWindow(argc, argv);
    return 0;
}
