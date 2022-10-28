#include "object.h"

void Object::setDestination(int x, int y, int w, int h){
    destination.x = x;
    destination.y = y;
    destination.w = w;
    destination.h = h;
}

void Object::setDestination(int x, int y){
    destination.x = x;
    destination.y = y;
}
void Object::setSource(int x, int y, int w, int h){
    source.x = x;
    source.y = y;
    source.w = w;
    source.h = h;
}

void Object::setImage(string filename, SDL_Renderer* renderer) {

  SDL_Surface* surface = IMG_Load(filename.c_str());
  texture = IMG_LoadTexture(renderer, filename.c_str());

}

