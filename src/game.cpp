#include "game.h"

//Constructor
Game::Game(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_CreateWindowAndRenderer(WIDTH,HEIGHT,0, &window, &renderer);
    SDL_SetWindowTitle(window, "capstoneGame");
    TTF_Init();
    running = true;
    fullscreen = false;
    showCursor = true;
    fpsMax = 60;
    mapX = 0;
    mapY = 0;
    speed = 4;
    loadMap("res/1.level");
    font = TTF_OpenFont("res/font.ttf", 24);
    effect.load("res/footsteps.wav");
    player.setImage("res/player.png", renderer);
    player.setDestination(100, 100, 47*3 ,45*3);
    player.setDestination(WIDTH/2, HEIGHT/2, 24, 32);
    player.setSource(0,0,24,32);
    idleLeft = player.createAnimCycle(2,24,32,2,20);
    idleRight = player.createAnimCycle(1,24,32,2,20);
    runLeft = player.createAnimCycle(4,24,32,4,4);
    runRight = player.createAnimCycle(3,24,32,4,4);
    player.setCurrentAnimation(idleRight);
    loop();
}

//Destructor
Game::~Game(){
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Game::loop() {
    static int lastTime = 0;
    while(running){
        lastFrame = SDL_GetTicks();
        
        if(lastFrame>=(lastTime+1000)){
            lastTime=lastFrame;
            fps = frameCount;
            frameCount = 0;
        }

        //Debugging
        //std::cout << fps << std::endl;
        //cout << mouseX << ", " << mouseY << endl;

        render();
        input();
        update();

    }
}

void Game::render(){
    //Setting up a background
    SDL_SetRenderDrawColor(renderer, 254, 102, 7, 255);
    SDL_Rect background;
    //Position
    background.x = 0;
    background.y = 0;
    //Size
    background.w = WIDTH;
    background.h = HEIGHT;
    //add to renderer buffer
    SDL_RenderFillRect(renderer, &background);

    
  
    drawMap();
    draw(player);

    //Setting code to FPS limit
    frameCount++;
    int timerFPS = SDL_GetTicks()-lastFrame;
    if(timerFPS<(1000/fpsMax)) {
        SDL_Delay((1000/fpsMax)-timerFPS);
    }

   //Sends buffer in the renderer to the screen to draw it
    SDL_RenderPresent(renderer);
}

void Game::update(){
    //Toggle fullscreen updating
    if(fullscreen){
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    } else {
        SDL_SetWindowFullscreen(window, 0);
    }
 if(left) {if(player.getCurrrentAnimation()!=runLeft) {player.setCurrentAnimation(runLeft);} player.setDestination(player.getDX()-speed, player.getDY());}
  if(right) {if(player.getCurrrentAnimation()!=runRight) {player.setCurrentAnimation(runRight);} player.setDestination(player.getDX()+speed, player.getDY());}
  player.updateAnimation();
  fall=true;
  for(int i=0; i<map.size(); i++) {
    if(collision(player, map[i])) {
      if(map[i].getSolid()) fall=false;
       if(map[i].getId() == 35) {
        if(up) {player.setDestination(player.getDX(), player.getDY()-(10*TILESIZE));up=down=0;}
        if(down) {player.setDestination(player.getDX(), player.getDY()+(10*TILESIZE));up=down=0;}
      }
    }
  }

  if(fall) player.setDestination(player.getDX(), player.getDY()+GRAVITY);

  if(player.getDX() < 100) {player.setDestination(100, player.getDY()); scroll(speed, 0);}
  if(player.getDX() > WIDTH-100) {player.setDestination(WIDTH-100, player.getDY()); scroll(-speed, 0);}
  if(player.getDY() < 100) {player.setDestination(player.getDX(), 100); scroll(0, speed);}
  if(player.getDY() > HEIGHT-100) {player.setDestination(player.getDX(), HEIGHT-100); scroll(0, -speed);}

}

void Game::input(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            running = false;
            cout << "Exiting Game" << endl;
        }
        if(event.type == SDL_KEYDOWN){
            if(event.key.keysym.sym == SDLK_ESCAPE){
                running = false;
            }
            if(event.key.keysym.sym == SDLK_w){
                up = true;
            }
            if(event.key.keysym.sym == SDLK_a){
                left = true;
                right = false;
            }
            if(event.key.keysym.sym == SDLK_s){
                down = true;
            }
            if(event.key.keysym.sym == SDLK_d){
                right = true;
                left = false;
            }

        }
        if(event.type == SDL_KEYUP){
            if(event.key.keysym.sym == SDLK_w){
                up = false;
            }
            if(event.key.keysym.sym == SDLK_a){
                left = false;
                player.setCurrentAnimation(idleLeft);
            }
            if(event.key.keysym.sym == SDLK_s){
                down = false;
            }
            if(event.key.keysym.sym == SDLK_d){
                right = false;
                player.setCurrentAnimation(idleRight);
            }
        }
        SDL_GetMouseState(&mouseX, &mouseY);
    }
   
}

void Game::draw(Object o){
    SDL_Rect destination = o.getDestination();
    SDL_Rect source = o.getSource();
    SDL_RenderCopyEx(renderer, o.getTexture(), &source, &destination, 0, NULL, SDL_FLIP_NONE);
}


void Game::draw(const char* message, int x, int y, int r, int g, int b){
    SDL_Surface* surface;
    SDL_Texture* texture;
    SDL_Color colour;
    colour.r=r;
    colour.g=g;
    colour.b=b;
    colour.a=255;
    SDL_Rect rect;
    surface = TTF_RenderText_Solid(font, message, colour);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.x=x;
    rect.y=y;
    rect.w=surface->w;
    rect.h=surface->h;
    //Free memory
    SDL_FreeSurface(surface);
    //Draw
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    //Destroy
    SDL_DestroyTexture(texture);
}

void Game::loadMap(const char* filename){
    Object temp;
    temp.setImage("res/tileset.png", renderer);
    int current, mx, my, mw, mh;
    ifstream in(filename);
    if(!in.is_open()){
        cout << "Error opening" << endl;
        return;
    }
    in >> mw;
    in >> mh;
    in >> mx;
    in >> my;
    for(int i = 0; i<mh; i++){
        for(int j = 0; j<mw; j++){
            if(in.eof()){
                cout << "end of map file error" << endl;
                return;
            }
            in >> current;
            if(current != 0){
                temp.setSolid(true);
                temp.setSource((current - 1)*32, 0, 32, 32);
                temp.setDestination((j*TILESIZE)+mx, (i*TILESIZE)+my, TILESIZE, TILESIZE);
                temp.setID(current);
                if(current == 12 || current == 30 || current == 35 || current == 22) temp.setSolid(false);
                map.push_back(temp);
            }
        }
    }
    in.close();
}

void Game::drawMap(){
    for(int i = 0; i<map.size(); i++){
        if(map[i].getDX() >= mapX-TILESIZE & map[i].getDY() >= mapY-TILESIZE & map[i].getDX() <= mapX+WIDTH+TILESIZE & map[i].getDY() <= mapY+HEIGHT+TILESIZE){
            draw(map[i]);
        }     
    }
}

void Game::scroll(int x, int y){
   for(int i = 0; i<map.size(); i++){
        map[i].setDestination(map[i].getDX()+x, map[i].getDY()+y);            
    }
}


bool Game::collision(Object a, Object b){
    if((a.getDX() < (b.getDX()+b.getDW())) && ((a.getDX() + a.getDW()) > b.getDX()) && (a.getDY() < (b.getDY() + b.getDH())) && ((a.getDY() + a.getDH()) > b.getDY())){
        return true;
    } else {
        return false;
    }
}