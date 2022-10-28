#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Object {

private:
    SDL_Rect destination;
    SDL_Rect source;
    SDL_Texture* texture;
    bool solid;
    int id;

public:
    Object() {solid=true;}
    SDL_Rect getDestination() const {return destination;}
    SDL_Rect getSource() const {return source;}
    void setDestination(int x, int y, int w, int h);
    void setDestination(int x, int y);
    void setSource(int x, int y, int w, int h);
    void setImage(string filename, SDL_Renderer* renderer);
    SDL_Texture* getTexture() const {return texture;}
    void setSolid(bool s){solid = s;}
    bool getSolid() const {return solid;}
    int getDX() const {return destination.x;}
    int getDY() const {return destination.y;}
    int getDW() const {return destination.w;}
    int getDH() const {return destination.h;}
    void setID(int i) {id = i;}
    int getId() const {return id;}

};


#endif //#OBJECT_H