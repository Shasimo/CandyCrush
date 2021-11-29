#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Shared_Image.H>
#include <string>
#include <math.h>
#include <time.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <random>
#include <array>
#include <memory>

#if __cplusplus >= 202002L
#include <numbers>
using std::numbers::pi;
#else
const double pi=3.141592653589793238462643383279502884L;
#endif
 
using namespace std;
 
const int windowWidth = 550;
const int windowHeight = 2000;
const double refreshPerSecond = 60;
 
 
struct Point {
  int x, y;
};
 
/*--------------------------------------------------
 
Text class.
 
Use to display text on the screen. For example:
 
Text("Hello!", {250, 250}).draw();
 
will create a text temporary instance with the
string "Hello!" centered at 250, 250 and will
call draw on the temporary.
 
It should have all the features you need and you
should not need to edit it.
 
--------------------------------------------------*/
 
class Text {
  Point center;
  string s;
  int fontSize;
  Fl_Color color;
 public:
  //Constructor
  Text(string s, Point center, int fontSize = 10, Fl_Color color = FL_BLACK):
    s{s}, center{center}, fontSize{fontSize}, color{color} {}
 
  //Draw
  void draw();
 
  //Setters and getters
  string getString() {
    return s;
  }
  void setString(const string &newString) {
    s = newString;
  }
  int getFontSize() {
    return fontSize;
  }
  void setFontSize(int newFontSize) {
    fontSize = newFontSize;
  }
  Point getCenter() {
    return center;
  }
  void setCenter(Point newCenter) {
    center = newCenter;
  }
};
 
void Text::draw() {
  fl_color(color);
  fl_font(FL_HELVETICA, fontSize);
  int width, height;
  fl_measure(s.c_str(), width, height, false);
  fl_draw(s.c_str(), center.x-width/2, center.y-fl_descent()+height/2);
}
 
/*--------------------------------------------------
 
Rectangle class.
 
Use to display a fillend-in rectangle on the screen
with different colors for the fill and the border
 
It should have all the features you need and you
should not need to edit it.
 
--------------------------------------------------*/


 
class Rectangle {
  Point center;
  int w, h;
  Fl_Color fillColor, frameColor;
 public:
  Rectangle(Point center, int w, int h,
            Fl_Color frameColor = FL_BLACK,
            Fl_Color fillColor = FL_WHITE);
  void draw();
  void setFillColor(Fl_Color newFillColor);
  Fl_Color getFillColor() {
    return fillColor;
  }
  void setFrameColor(Fl_Color newFrameColor);
  Fl_Color getFrameColor() {
    return frameColor;
  }
  void setWidth(int neww) {
    w = neww;
  }
  void setHeight(int newh) {
    h = newh;
  }
  int getWidth() {
    return w;
  }
  int getHeight() {
    return h;
  }
  bool contains(Point p);
  Point getCenter() {
    return center;
  }
};
 
Rectangle::Rectangle(Point center, int w, int h,
                     Fl_Color frameColor,
                     Fl_Color fillColor):
  center{center}, w{w}, h{h}, fillColor{fillColor}, frameColor{frameColor} {}
 
void Rectangle::draw() {
  fl_draw_box(FL_FLAT_BOX, center.x-w/2, center.y-h/2, w, h, fillColor);
  fl_draw_box(FL_BORDER_FRAME, center.x-w/2, center.y-h/2, w, h, frameColor);
}
 
void Rectangle::setFillColor(Fl_Color newFillColor) {
  fillColor = newFillColor;
}
 
void Rectangle::setFrameColor(Fl_Color newFrameColor) {
  frameColor = newFrameColor;
}
 
bool Rectangle::contains(Point p) {
  return p.x>=center.x-w/2 &&
         p.x<center.x+w/2 &&
         p.y>=center.y-h/2 &&
         p.y<center.y+h/2;
}

/*----------------------
-----------------------*/

class TextRectangle : public Rectangle, public Text
{
  public:
  TextRectangle(Point center, int w, int h, string s) : 
  Rectangle{center, w, h}, Text{s, center} {}
  void draw();

};

void TextRectangle::draw() {
  Rectangle::draw();
  Text::draw();
}

/*----------------------
----------------------*/


class Candy {
  Point center;
  char* candySprite;
  public:
  Candy(Point center, char* candySprite);
  void draw();

};

Candy::Candy(Point center, char* candySprite) : 
center(center), candySprite(candySprite) {};

void Candy::draw() {
  /*fl_draw_box(FL_BORDER_FRAME, center.x-50/2, center.y-50/2, 40, 40, FL_BLUE);*/
  Fl_PNG_Image png("Sprites/tile000.png");
  Fl_Box box(center.x-50/2, center.y-50/2, 40, 40);
  box.image(png);
  box.show();
};




/*--------------------------------------------------
 
Circle class.
 
Use to display a fillend-in rectangle on the screen
with different colors for the fill and the border
 
It should have all the features you need and you
should not need to edit it.
 
--------------------------------------------------*/
 
class Circle {
  Point center;
  int r;
  Fl_Color fillColor, frameColor;
 public:
  Circle(Point center, int r,
            Fl_Color frameColor = FL_BLACK,
            Fl_Color fillColor = FL_WHITE);
  void draw();
  void setFillColor(Fl_Color newFillColor);
  Fl_Color getFillColor() {
    return fillColor;
  }
  void setFrameColor(Fl_Color newFrameColor);
  Fl_Color getFrameColor() {
    return frameColor;
  }
  bool contains(Point p);
  Point getCenter() {
    return center;
  }
};
 
Circle::Circle(Point center, int r,
                     Fl_Color frameColor,
                     Fl_Color fillColor):
  center{center}, r{r}, fillColor{fillColor}, frameColor{frameColor} {}
 
void Circle::draw() {
  array<Point,37> points;
  for (int i=0;i<36;i++)
    points[i]={static_cast<int>(center.x+r*sin(i*10*pi/180)),
      static_cast<int>(center.y+r*cos(i*10*pi/180))};
  points[36]=points[0];
  fl_color(fillColor);
  fl_begin_polygon();
  for (auto& point : points) {
    fl_vertex(point.x, point.y);
  }
  fl_end_polygon();
  fl_color(frameColor);
  fl_begin_line();
  for (auto& point : points) {
    fl_vertex(point.x, point.y);
  }
  fl_end_line();
}
 
void Circle::setFillColor(Fl_Color newFillColor) {
  fillColor = newFillColor;
}
 
void Circle::setFrameColor(Fl_Color newFrameColor) {
  frameColor = newFrameColor;
}
 
bool Circle::contains(Point p) {
  return ( (p.x-center.x)*(p.x-center.x)
          +(p.y-center.y)*(p.y-center.y)<=r*r);
}
 


 
 
/*--------------------------------------------------
 
Cell class.
 
The Canvas class below will have cells as instance
vraiables and call the methods of Cell
--------------------------------------------------*/
 
 
class Cell {
  Rectangle r;
  Circle c;
  Candy o;
  vector<Cell *> neighbors;

  Fl_Color color_candy;
  bool selected;
  Point* center_ptr;
  Point center;

 public:
  // Constructor
  Cell(Point center, int w, int h, int r, Fl_Color color_candy, char* candie);
  Cell &operator=(const Cell &other);
 
  void draw();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);

  void setNeighbors(vector <Cell *> newNeighbors) {neighbors = newNeighbors;}
  vector <Cell*> getNeighbors() {return neighbors;}
  Point getCenter();
  Fl_Color getColor() {return color_candy;}
  bool getSelected();
  void setSelected(bool value);
 
};
 
Cell::Cell(Point center, int w, int h, int r, Fl_Color color_candy, char* candie):
  o(center, candie),
  r(center, w, h, FL_BLACK, FL_WHITE), 
  c(center, r, FL_BLACK, FL_WHITE), 
  selected(false),
  color_candy(color_candy),
  center_ptr(&center),
  center({center_ptr->x, center_ptr->y})
  {}

Cell &Cell::operator =(const Cell &other)
{
  
  center_ptr=other.center_ptr;
  color_candy=other.color_candy;
  return *this;
}
 
void Cell::draw() {
  r.setFillColor(color_candy);
  r.draw();
  o.draw();
}
 
void Cell::mouseMove(Point mouseLoc) {
  if (r.contains(mouseLoc) && !selected) {
    Fl_Color orange = fl_color_average(FL_RED, FL_YELLOW, 0.4);
    r.setFrameColor(orange);
  } 
  else {
    if (!selected)
   { r.setFrameColor(FL_BLACK);}
  }
}
 
 
void Cell::mouseClick(Point mouseLoc) {
   if (r.contains(mouseLoc) && !selected) {
    r.setFrameColor(FL_RED);
    selected=true;
  } 
  else if (r.contains(mouseLoc) && selected) {
    r.setFrameColor(FL_RED);
    selected=false;
  } 
}



bool Cell::getSelected() {
  return selected;
}

void Cell::setSelected(bool value) {
  selected=value;
}

Point Cell::getCenter() {
  return center;
}
 
 
/*--------------------------------------------------
 
Canvas class.
 
One instance of the canvas class is made by the
MainWindow class.
 
The fltk system via MainWindow calls:
 
draw 60 times a second
mouseMove whenever the mouse is moved
mouseClick whenever the mouse is clicked
keyPressed whenever a key is pressed
 
Any drawing code should be called ONLY in draw
or methods called by draw. If you try to draw
elsewhere it will probably crash.
--------------------------------------------------*/
 
 
class Canvas {
  vector< vector<Cell> > cells;
  vector<char*> candySprites;
 public:
  Canvas(vector <char*> candySprites);
  void draw();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);

  void checkIfNeighborsSelected();
  void clearSelected();
  void SwitchTwoCells(Cell c, Cell* n);
};
 
Canvas::Canvas(vector <char*> candySprites) : candySprites(candySprites) {

  cells.clear();
  Fl_Color color_candy;
  int random_number;
  for (int x = 0; x<9; x++) {
    cells.push_back({});
    for (int y = 0; y<9; y++)
    {
      char* candie;
      random_number=rand()%4;
      switch(random_number)
      {
        case 0:
        color_candy=FL_RED;
        candie = candySprites[0];
        break;

        case 1:
        color_candy=FL_BLUE;
        candie = candySprites[1];

        break;
        case 2:
        color_candy=FL_YELLOW;
        candie = candySprites[2];
        break;

        case 3:
        color_candy=FL_GREEN;
        candie = candySprites[3];
        break;
      }
      cells[x].push_back({{45*x+50, 45*y+120}, 40, 40, 15, color_candy, candie});
    }
  }

  for (int x = 0; x<9; x++)
    for (int y = 0; y<9; y++) {
      vector<Cell *> neighbors;

  for (auto &shift: vector<Point>({
    {-1, 0},
    { 0, 1},
    { 1, 0},
    { 0, -1},
    })) 
    
    {
      int neighborx = x+shift.x;
      int neighbory = y+shift.y;
      if (neighborx >= 0 &&
          neighbory >= 0 &&
          neighborx < cells.size() &
          neighbory < cells[neighborx].size())
        neighbors.push_back(&cells[neighborx][neighbory]);
      cells[x][y].setNeighbors(neighbors);
    }
    }
 
}

void Canvas::SwitchTwoCells(Cell c, Cell* n)
{

  vector <Cell *> future_neighbors_n;
  vector <Cell *> future_neighbors_c;
  vector <Cell *> v1 = c.getNeighbors();
  vector <Cell *> v2 = n->getNeighbors();

  for (int i = 0; i < v1.size(); i++) 
    if (!( (v1[i]->getCenter().x == n->getCenter().x) && 
    (v1[i]->getCenter().y == n->getCenter().y)) )
    {
      future_neighbors_n.push_back(v1[i]);
    }
  future_neighbors_n.push_back(&c);

  for (int i = 0; i < v2.size(); i++) 
    if (!( (v2[i]->getCenter().x == c.getCenter().x) && 
    (v2[i]->getCenter().y == c.getCenter().y)) )
    {
      future_neighbors_c.push_back(v2[i]);
    }
  future_neighbors_c.push_back(n);

  swap( 
  cells[(c.getCenter().x-50)/45][(c.getCenter().y - 120)/45],
  cells[(n->getCenter().x-50)/45][(n->getCenter().y - 120)/45]
  );


}

void Canvas::clearSelected() {
  for (auto &v: cells)
    for (auto &c: v)
     if (c.getSelected())
     {
       c.setSelected(false);
     }
}

void Canvas::checkIfNeighborsSelected() {
  int cout_selected=0;
  for (auto &v: cells)
    for (auto &c: v)
    {
      if (c.getSelected())
      {
        cout_selected++;
       for (auto &neighbor: c.getNeighbors())
       {
         if (neighbor->getSelected())
         {
           c.setSelected(false);
           neighbor->setSelected(false);
           SwitchTwoCells(c, neighbor);
         }

       }
      }
    }
  if (cout_selected>=2)
  {
    clearSelected();
  }
     
}
 
 
void Canvas::draw() {
  checkIfNeighborsSelected();
  for (auto &v: cells)
    for (auto &c: v)
      c.draw();
}
 
void Canvas::mouseMove(Point mouseLoc) {
  for (auto &v: cells)
    for (auto &c: v)
      c.mouseMove(mouseLoc);
}
 
void Canvas::mouseClick(Point mouseLoc) {
  for (auto &v: cells)
    for (auto &c: v)
      for (auto &c: v) c.mouseClick(mouseLoc);
}
 
void Canvas::keyPressed(int keyCode) {
  switch (keyCode) {
    case 'q':
      exit(0);
  }
}
 
/*--------------------------------------------------
 
MainWindow class.
 
Do not edit!!!!
 
--------------------------------------------------*/
 
class MainWindow : public Fl_Window {
  Canvas canvas;
  vector <char*> candySprites;
 public:
  MainWindow(vector <char*> candySprites) : Fl_Window(500, 500, windowWidth, windowHeight, "CandyCrush"),
  candySprites(candySprites),
  canvas(candySprites)
  {
    Fl::add_timeout(1.0/refreshPerSecond, Timer_CB, this);
    resizable(this);
  }
  void draw() override {
    Fl_Window::draw();
    TextRectangle display_score({90,60}, 120, 70, "Score:");
    TextRectangle display_objective({230, 60}, 120, 70, "Objective:");
    TextRectangle display_hits({370, 60}, 120, 70, "Hits remaning:");
    display_score.draw();
    display_objective.draw();
    display_hits.draw();
    canvas.draw();
  }
  int handle(int event) override {
    switch (event) {
      case FL_MOVE:
        canvas.mouseMove(Point{Fl::event_x(), Fl::event_y()});
        return 1;
      case FL_PUSH:
        canvas.mouseClick(Point{Fl::event_x(), Fl::event_y()});
        return 1;
      case FL_KEYDOWN:
        canvas.keyPressed(Fl::event_key());
        return 1;
    }
    return 0;
  }
  static void Timer_CB(void *userdata) {
    MainWindow *o = (MainWindow*) userdata;
    o->redraw();
    Fl::repeat_timeout(1.0/refreshPerSecond, Timer_CB, userdata);
  }
};
