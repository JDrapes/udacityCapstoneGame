#ifndef GAME_H
#define GAME_H
#define WIDTH 1280
#define HEIGHT 720
#define TILESIZE 16
#define GRAVITY 10

#include <iostream>
using namespace std;
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <vector>
#include "audio.h"
#include "object.h"
#include "entity.h"

class Game {
public:
    Game();
    ~Game();
    void loop();
    void update();
    void input();  
    void render();
    void draw(Object o);
    void draw(const char* message, int x, int y, int r, int g, int b);
    void loadMap(const char* filename);
    void drawMap();
    void scroll(int x, int y);
    bool collision(Object a, Object b);
private:
    SDL_Renderer* renderer;
    SDL_Window* window;
    bool running, fullscreen, showCursor;
    int frameCount, timerFPS, lastFrame, fps, fpsMax, mouseX, mouseY;
    TTF_Font *font;
    Audio effect;
    Entity player;
    vector<Object> map;
    int mapX, mapY;
    int speed;
    bool left,right,up,down, fall;
    int idleLeft, idleRight, runLeft, runRight;

};

#endif //GAME_H