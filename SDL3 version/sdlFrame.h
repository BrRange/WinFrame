#ifndef SDL_FRAME_H_
#define SDL_FRAME_H_

#include <SDL3/SDL.h>
#include "arena.h"

struct KeyboardHandler{
  SDL_Keycode keys[6];
  Uint16 used;
};
typedef struct KeyboardHandler KeyboardHandler;

void KeyboardHandler_pressKey(KeyboardHandler*, SDL_Keycode);
void KeyboardHandler_releaseKey(KeyboardHandler*, SDL_Keycode);
bool KeyboardHandler_hasKey(KeyboardHandler*, SDL_Keycode);
void KeyboardHandler_clear(KeyboardHandler*);

#define MOUSEB_LEFT (1 << 0)
#define MOUSEB_MID (1 << 1)
#define MOUSEB_RIGHT (1 << 2)
#define MOUSEB_EXTRA(x) (1 << (3 + (x)))

struct MouseHandler{
  SDL_FPoint pos;
  Uint8 button;
  Uint8 clickNum;
  Sint16 scroll;
};
typedef struct MouseHandler MouseHandler;

void MouseHandler_move(MouseHandler *moH, float x, float y);
SDL_FPoint MouseHandler_getPos(MouseHandler *moH);
void MouseHandler_pressButton(MouseHandler *moH, Uint8 button, Uint8 clicks);
void MouseHandler_releaseButton(MouseHandler *moH, Uint8 button);
bool MouseHandler_hasButton(MouseHandler *moH, Uint8 button);
void MouseHandler_scroll(MouseHandler *moH, Sint16 scroll);
void MouseHandler_clear(MouseHandler *moH);

struct MenuState;
typedef void (*MenuFunc)(SDL_Window*, SDL_Renderer*, struct MenuState*);

struct MenuState{
  MenuFunc tick, render;
  KeyboardHandler *kbHandler;
  MouseHandler *moHandler;
  Arena memory;
};
typedef struct MenuState MenuState;


MenuState MenuState_new(MenuFunc fnTick, MenuFunc fnRender, KeyboardHandler*, MouseHandler*, Uint32 auxBytes);
void MenuState_destroy(MenuState *menu);

#endif