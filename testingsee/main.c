//
//  main.c
//  testingsee
//
//  Created by Jonatas Pereira on 23/10/19.
//  Copyright © 2019 Jonatas Pereira. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
    int x, y;
    short life;
    char *name;
} Man;


bool eventLoop(SDL_Window *window, Man *man)
{
    SDL_Event event;
    bool done = false;
    
        // Check for events
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_WINDOWEVENT_CLOSE:
                    if(window){
                        SDL_DestroyWindow(window);
                        window = NULL;
                        printf("Window closed.");
                        done = true;
                    }
                    break;
                
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            printf("Esc hit. closing...\n");
                            done = true;
                            break;
     
                        default:
                            break;
                    }
                    break;
                    case SDL_QUIT:
                    done = true;
                    break;
                    
                default:
                    break;
            }
        }
    
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_LEFT])
    {
        man->x -=10;
    };
    if (state[SDL_SCANCODE_RIGHT]) {
        man->x +=10;
    }
    if(state[SDL_SCANCODE_UP]){
        man->y -=10;
    }
    if(state[SDL_SCANCODE_DOWN]){
        man->y +=10;
    }
    return done;
}
void doRender(SDL_Renderer *renderer, Man *man)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    SDL_Rect rect = {man->x, man->y, 200, 200};
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);
}


int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    
    window = SDL_CreateWindow("Tuto", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Man man;
    man.x = 220;
    man.y =  140;
    
    
    
    bool done = false;
    while (!done)
    {
        done = (eventLoop(window, &man));
        
        doRender(renderer, &man);
        
        SDL_Delay(10);
    }
    
    return 0;
}
