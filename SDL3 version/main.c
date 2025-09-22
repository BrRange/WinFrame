#include "sdlFrameGUI.h"
#include "eventHandler.h"
#include <SDL3/SDL_ttf.h>
#include <stdio.h>

#include "arena.c"
#include "sdlFrame.c"
#include "sdlFrameGUI.c"

void mainTick(SDL_Window *win, SDL_Renderer *rend, MenuState *menu){
  printf("\rMouse Pos: (%3.f, %3.f)", menu->moHandler->pos.x, menu->moHandler->pos.y);
}
void mainRender(SDL_Window *win, SDL_Renderer *rend, MenuState *menu){
  GUIRect *gRect = Arena_get(&menu->memory, 0);
  TTF_Font *font = *(TTF_Font**)Arena_get(&menu->memory, sizeof(GUIRect));
  SDL_Surface *winSurf = SDL_GetWindowSurface(win);

  SDL_SetRenderDrawColor(rend, Hex_expandRGB(0x000020));
  SDL_RenderClear(rend);

  SDL_Surface *textG = TTF_RenderText_Blended(font, "Hello world!", 0, Color_hex(0x800000ff));
  SDL_Texture *textT = SDL_CreateTextureFromSurface(rend, textG);
  SDL_DestroySurface(textG);
  
  GUIRect_draw(gRect, rend);
  SDL_RenderTexture(rend, textT, NULL, NULL);
  SDL_DestroyTexture(textT);
}

Sint32 main(){
  SDL_Init(-1);
  
  TTF_Init();

  SDL_Window *win;
  SDL_Renderer *rend;
  SDL_CreateWindowAndRenderer("Main", 420, 420, SDL_WINDOW_RESIZABLE, &win, &rend);
  SDL_SetWindowPosition(win, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

  TTF_Font *font = TTF_OpenFont("fonts/font.ttf", 128.f);

  SDL_Event eve = {0};
  SDL_Time start, end = 0;
  SDL_GetCurrentTime(&start);

  SDL_srand(start);

  KeyboardHandler generalKb = {0};
  MouseHandler generalMo = {0};

  MenuState mainMenu = MenuState_new(mainTick, mainRender, &generalKb, &generalMo, 69420);
  *(GUIRect*)Arena_alloc(&mainMenu.memory, sizeof(GUIRect)) = GUIRect_new(10, 10, 300, 200, Color_hex(0xdaa520), Color_hex(0x1a1a1a));
  *(size_t*)Arena_alloc(&mainMenu.memory, sizeof(void*)) = (size_t)font;

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

  TTF_CloseFont(font);
  TTF_Quit();

  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  SDL_Quit();

  SDL_Log("\nNormal Exit");
}