#pragma once
#include <iostream>
#include <string>
#include <vector>


#include <SFML/Graphics.hpp>

 /**
     Constructor of Screen  open a SFML window
     @param w width of the window (e.g. 500)
     @param h height of the window (e.g. 500)
 **/

class Screen
{
 public:
  Screen(uint16_t h, uint16_t w);
  ~Screen(){delete _win;};
  bool isOpen(){return _win->isOpen();}
  void close(){_win->close();}
  bool pollEvent(sf::Event& event){return _win->pollEvent(event);}
  void render();
  /** draw a filled rectangle
      @param x x-coordinate of the center (in pixels)
      @param y y-coordinate of the center (in pixels)
      @param w width of the rectangle (in pixels)
      @param h height of the rectangle (in pixels)
      @param color 0xRRGGBBAA (default: blue)
  */
  void rect(float x, float y, float w, float h, uint32_t color = 0xFF0000FF);
  
  /** draw a line
      @param x0 starting x-coordinate (in pixels)
      @param y0 starting y-coordinate (in pixels)
      @param x1 ending x-coordinate (in pixels)
      @param y1 ending y-coordinate (in pixels)
      @param color 0xRRGGBBAA (default: red)
  */
  void line(int x0, int y0, int x1, int y1, uint32_t color = 0xFF0000FF);
  /*
    draw a disc
    @param x x-coordinate of the center (in pixels)
    @param y y-coordinate of the center (in pixels)
    @param radius (in pixels)
    @param color 0xRRGGBBAA (default: red)
  */
  void disc(float x, float y, float radius, uint32_t color = 0xFF0000FF);
   /*
    draw a disc
    @param x x-coordinate of the center (in pixels)
    @param y y-coordinate of the center (in pixels)
    @param radius (in pixels)
    @param color 0xRRGGBBAA (default: red)
  */
  void light(float x, float y, float height, float width, uint32_t color = 0xFFFF00FF);
   /*
    draw a lightning
    @param x x-coordinate of the center (in pixels)
    @param y y-coordinate of the center (in pixels)
    @param height(in pixels)
    @param width(in pixels)
    @param color 0xRRGGBBAA (default: yellow
  */
  void diamond(float x, float y, float height, float width, uint32_t color = 0xAEFBFFFF);
   /*
    draw a diamond
    @param x x-coordinate of the center (in pixels)
    @param y y-coordinate of the center (in pixels)
    @param height(in pixels)
    @param width(in pixels)
    @param color 0xRRGGBBAA (default: light blue
  */
  void star(float x, float y, float size, uint32_t color = 0xFFCD00FF);
   /*
    draw a disc
    @param x x-coordinate of the center (in pixels)
    @param y y-coordinate of the center (in pixels)
    @param size  (in pixels)
    @param color 0xRRGGBBAA (default: orange)
  */
  void text(float x ,float y,std::string text,uint32_t color = 0x35EEEEFF,std::string font_file = "font/Montserrat-Bold.ttf");

  
 protected:


 private:
  sf::RenderWindow *  _win;
  uint16_t _w, _h;

};

