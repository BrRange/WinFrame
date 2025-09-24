#include "sdlFrame.h"

#define loop(_type, _n) for(_type _i = 0; _i < _n; ++_i)

#define shapeW 30
#define shapeH 20

#define stretch 4

#define Y ~0
#define N 0

void tick(SDL_Window *win, Uint8 color[4], Sint32 speed[2]){
  Sint32 x, y, w = shapeW * stretch, h = shapeH * stretch;
  SDL_GetWindowPosition(win, &x, &y);
  SDL_DisplayID display = SDL_GetDisplayForWindow(win);
  SDL_Rect rect;
  SDL_GetDisplayBounds(display, &rect);

  x += speed[0];
  y += speed[1];

  if(x < rect.x)
    speed[0] *= -1, x = rect.x + 1, color[0] += 32, color[1] -= 32, color[2] += 32;
  if(x + w > rect.x + rect.w)
    speed[0] *= -1, x = rect.x + rect.w - w - 1, color[0] += color[2], color[1] -= color[0], color[2] += color[2];
  if(y < rect.y)
    speed[1] *= -1, y = rect.y + 1, color[0] -= color[2], color[1] += color[1], color[2] -= color[0];
  if(y + h > rect.y + rect.h)
    speed[1] *= -1, y = rect.y + rect.h - h - 1, color[0] -= color[1], color[1] += 32, color[2] -= color[1];

  SDL_SetWindowPosition(win, x, y);
}

void render(SDL_Renderer *rend, Uint8 color[4]){
  SDL_SetRenderDrawColor(rend, color[0], color[1], color[2], color[3]);
  SDL_RenderClear(rend);
}

void handleEvents(SDL_Event *eve){
  while(SDL_PollEvent(eve))
  switch(eve->type){
  case SDL_EVENT_QUIT:
  return;
  }
}

int main(){
  Uint8 isIt = SDL_Init(~0);

  if(!isIt){
    SDL_Quit();
    return 1;
  }

  SDL_Window *win;
  SDL_Renderer *rend;
  SDL_CreateWindowAndRenderer("Screen Saver", shapeW * stretch, shapeH * stretch, SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_BORDERLESS | SDL_WINDOW_TRANSPARENT, &win, &rend);
  SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_NONE);

  Uint32 shapeMask[shapeW * shapeH] = {
    #include "DVD.h"
  };
  SDL_Surface *shape = SDL_CreateSurfaceFrom(shapeW, shapeH, SDL_PIXELFORMAT_ARGB32, shapeMask, sizeof(*shapeMask) * shapeW);
  SDL_SetWindowShape(win, shape);
  SDL_DestroySurface(shape);

  SDL_Event eve = {0};

  SDL_Time start, end = 0;
  SDL_GetCurrentTime(&start);
  
  SDL_srand(start);

  Sint32 speed[2] = {(SDL_rand(5) + 5) * (shapeW / (float)shapeH) * (SDL_rand(2) ? 1 : -1), (SDL_rand(5) + 5) * (shapeH / (float)shapeW) * (SDL_rand(2) ? 1 : -1)};
  Uint8 color[4] = {255, 255, 255, 255};

  while(eve.type != SDL_EVENT_QUIT){
    SDL_GetCurrentTime(&end);
    if(end - start > 16666666){
      start = end;
      handleEvents(&eve);

      tick(win, color, speed);
      render(rend, color);
      SDL_RenderPresent(rend);
    }
    SDL_Delay(1);
  }

  SDL_DestroyRenderer(rend);
  SDL_DestroyWindow(win);
  SDL_Quit();
}