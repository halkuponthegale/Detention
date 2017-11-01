#pragma once
class Actor{
public:
  Actor(double x, double y, double w, double h){
    this->x = x;
    this->y=y;
    this->w=w;
    this->h=h;
  }
  double getX(){
    return x;
  }
  double getY(){
    return y;
  }
  void setLocation(double x, double y){
    this->x=x;
    this->y=y;
  }
  void move(double dx, double dy){
    x+=dx;
    y+=dy;
  }
  int getW(){
    return w;
  }
  int getH(){
    return h;
  }
private:
  double x,y;
  int w,h;
};
