// //Includes
// #include <SDL2/SDL.h>
// #include <iostream>

// //Defines
// #define WIDTH 1920
// #define HEIGHT 1080

// //Create variables
// bool running, fullscreen,showCursor;
// int frameCount, timerFPS, lastFrame, fps, fpsMax;

// //For creating windows
// SDL_Renderer* renderer;
// SDL_Window* window;

// void update(){
//     //Toggle fullscreen updating
//     if(fullscreen){
//         SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
//     } else {
//         SDL_SetWindowFullscreen(window, 0);
//     }
    
// }

// void input() {
//     SDL_Event e;
//     while(SDL_PollEvent(&e)){
//         if(e.type == SDL_QUIT){
//             running = false;
//         }
//     }
//     const Uint8 *keystates = SDL_GetKeyboardState(NULL);
//     //Input control for escape key
//     if(keystates[SDL_SCANCODE_ESCAPE]){
//         running = false;
//     }
//     //Input control for F11 key
//     if(keystates[SDL_SCANCODE_F11]){
//         fullscreen =! fullscreen;
//     }
// }

// void draw() {

//     //Setting up a background
//     SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//     SDL_Rect background;
//     //Position
//     background.x = 0;
//     background.y = 0;
//     //Size
//     background.w = WIDTH;
//     background.h = HEIGHT;
//     //add to renderer buffer
//     SDL_RenderFillRect(renderer, &background);

//     //Setting code to FPS limit
//     frameCount++;
//     int timerFPS = SDL_GetTicks()-lastFrame;
//     if(timerFPS<(1000/fpsMax)) {
//         SDL_Delay((1000/fpsMax)-timerFPS);
//     }

//     //Sends buffer in the renderer to the screen to draw it
//     SDL_RenderPresent(renderer);
// }

// int main(){
//     //Flags
//     running = true;
//     fullscreen = false;
//     showCursor = true;
//     static int lastTime = 0;
//     fpsMax = 60;
//     //Sanity checks
//     if(SDL_Init(SDL_INIT_EVERYTHING) < 0) std::cout <<"SDL initialization failed" <<std::endl;
//     if(SDL_CreateWindowAndRenderer(WIDTH,HEIGHT,fullscreen, &window, &renderer)<0) std::cout << "Failed to create window" <<std::endl;
//     //Set window title
//     SDL_SetWindowTitle(window, "SDL2_Game");
//     //Enable/disable cursor from flag
//     SDL_ShowCursor(showCursor);
//     //Renders pixels better
//     SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
    
//     //Program loop
//     while(running){

//         //Uses SDL to see the time
//         lastFrame = SDL_GetTicks();
//         if(lastFrame>=(lastTime+1000)){
//             lastTime=lastFrame;
//             fps=frameCount;
//             frameCount=0;
//         }

//         //Debugging
//         std::cout << fps << std::endl;


//         update();
//         input();
//         draw();
//     }

//     //Clean up
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
// }