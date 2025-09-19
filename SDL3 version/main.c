#include "sdlFrame.h"
#include "eventHandler.h"
#include <stdio.h>

void mainTick(SDL_Window *win, SDL_Renderer *rend, MenuState *menu){
  printf("\rMouse Pos: (%3.f, %3.f)", menu->moHandler->pos.x, menu->moHandler->pos.y);
}
void mainRender(SDL_Window *win, SDL_Renderer *rend, MenuState *menu){
  return;
}

Sint32 main(){
  SDL_Init(-1);
  SDL_Window *win;
  SDL_Renderer *rend;
  SDL_CreateWindowAndRenderer("Main", 420, 420, SDL_WINDOW_RESIZABLE, &win, &rend);
  SDL_SetWindowPosition(win, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

  SDL_Event eve = {0};
  SDL_Time start, end = 0;
  SDL_GetCurrentTime(&start);

  SDL_srand(start);

  KeyboardHandler generalKb = {0};
  MouseHandler generalMo = {0};

  MenuState mainMenu = MenuState_new(mainTick, mainRender, &generalKb, &generalMo, 0);

  while(eve.type != SDL_EVENT_QUIT){
    SDL_GetCurrentTime(&end);
    if(end - start > 16666666){
      start = end;
      handleEvents(&eve, &mainMenu);

      mainMenu.tick(win, rend, &mainMenu);
      mainMenu.render(win, rend, &mainMenu);

      SDL_RenderPresent(rend);
    }
    SDL_Delay(1);
  }

  MenuState_destroy(&mainMenu);
  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  SDL_Quit();
  SDL_Log("\nNormal Exit");
}