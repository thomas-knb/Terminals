#include "screen.h"
#include <cassert>
#include <cmath>   


/* Positions origin are upper left corner */

Screen::Screen(uint16_t h,uint16_t w):_w(w),_h(h)
{
  _win = new sf::RenderWindow(sf::VideoMode(_w , _h), "Terminals");
}


void Screen::render()
{
  _win->display();
  //_win->clear();
}

void Screen::rect(float x, float y, float w, float h, uint32_t color)
{
  sf::RectangleShape rectangle(sf::Vector2f(w, h));
  rectangle.setFillColor(sf::Color(color));
  rectangle.setPosition(x, y);
  _win->draw(rectangle);
}

void Screen::line(int x0, int y0, int x1, int y1, uint32_t color)
{
  sf::Vertex line[] =
  {
    sf::Vertex(sf::Vector2f(x0, y0), sf::Color(color)),
    sf::Vertex(sf::Vector2f(x1, y1), sf::Color(color))
  };
  _win->draw(line, 2, sf::Lines);
}


void Screen::disc(float x_center, float y_center, float radius, uint32_t color)
{
  sf::CircleShape shape(radius);
  shape.setFillColor(sf::Color(color));
  shape.setPosition(x_center-radius, y_center-radius);
  _win->draw(shape);
}

void Screen::light(float x, float y, float h, float w, uint32_t color)
{
  sf::ConvexShape convex;
  convex.setPointCount(6);
  convex.setPoint(0, sf::Vector2f(0.f, 0.f));
  convex.setPoint(1, sf::Vector2f((3.f/5.f) * w ,-(4.f/7.f) * h ));
  convex.setPoint(2, sf::Vector2f((3.f/5.f) * w, -(1.f/7.f) * h ));
  convex.setPoint(3, sf::Vector2f( w, -(1.f/7.f) * h ));
  convex.setPoint(4, sf::Vector2f((2.f/5.f) * w, (3.f/7.f) * h ));
  convex.setPoint(5, sf::Vector2f((2.f/5.f) * w ,0.f));
  convex.setFillColor(sf::Color(color));
  convex.setPosition(x, y);
  _win->draw(convex);
}


void Screen::diamond(float x, float y, float h, float w, uint32_t color)
{
  sf::ConvexShape convex;
  convex.setPointCount(4);
  convex.setPoint(0, sf::Vector2f(0.f, 0.f));
  convex.setPoint(1, sf::Vector2f(w/2.f ,-h/2.f));
  convex.setPoint(2, sf::Vector2f(w, 0.f));
  convex.setPoint(3, sf::Vector2f( w/2, h/2 ));
  convex.setFillColor(sf::Color(color));
  convex.setPosition(x, y);
  _win->draw(convex);
}

void Screen::star(float x, float y, float size, uint32_t color)
{
  float h,w;
  h = w = size;
  sf::ConvexShape convex;
  convex.setPointCount(10);
  convex.setPoint(0, sf::Vector2f(0.f, 0.f));
  convex.setPoint(1, sf::Vector2f((3.f/8.f)*w,0.f));
  convex.setPoint(2, sf::Vector2f(w/2.f, -(3.f/8.f)*h));
  convex.setPoint(3, sf::Vector2f((5.f/8.f)*w, 0.f ));
  convex.setPoint(4, sf::Vector2f(w, 0.f ));
  convex.setPoint(5, sf::Vector2f((6.f/8.f)*w, (1.f/4.f)*h ));
  convex.setPoint(6, sf::Vector2f((7.f/8.f)*w, (5.5/8.f)*h ));
  convex.setPoint(7, sf::Vector2f(w/2.f, (1.f/2.f)*h ));
  convex.setPoint(8, sf::Vector2f((1.f/8.f)*w,(5.5/8.f)*h ));
  convex.setPoint(9, sf::Vector2f((1.f/4.f)*w, h/4.f ));
  convex.setFillColor(sf::Color(color));
  convex.setPosition(x, y);
  _win->draw(convex);
}

void Screen::text(float x ,float y,std::string str_txt,uint32_t color, std::string font_file)
{
  sf::Font font;
  if (!font.loadFromFile(font_file))
    std::cerr << "no font found" << std::endl;
  sf::Text text;

  text.setFont(font);

  text.setString(str_txt);
  text.setFillColor(sf::Color(color));
  text.setCharacterSize(15);
  text.setPosition(x,y);
  _win->draw(text);
}

