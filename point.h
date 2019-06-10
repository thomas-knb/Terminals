#pragma once
#include <string>
#include <iostream>
#include <cmath>


class Point
{
 public:
  Point():_x(0),_y(0){}
  Point(double x, double y):_x(x),_y(y){}
  double getX(){return _x;}
  double getY(){return _y;}
  void setXY(double x, double y){_x = x; _y = y;}
  double dist(Point point){return sqrt(pow(this->_x - point._x, 2) + pow(this->_y - point._y, 2));}
 private:
  double _x;
  double _y;
};

