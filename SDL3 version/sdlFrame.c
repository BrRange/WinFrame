#include "sdlFrame.h"

void KeyboardHandler_pressKey(KeyboardHandler *kbH, SDL_Keycode key){
  [[unlikely]] if(kbH->used >= 6) return;
  for(Uint32 i = 0; i < kbH->used; ++i)
  [[unlikely]] if(kbH->keys[i] == key) return;
  kbH->keys[kbH->used] = key;
}
void KeyboardHandler_releaseKey(KeyboardHandler *kbH, SDL_Keycode key){
  [[unlikely]] if(!key) return;
  for(Uint32 i = 0; i < kbH->used; ++i)
  if(kbH->keys[i] == key){
    kbH->keys[i] = 0;
    --kbH->used;
    return;
  };
}
void KeyboardHandler_clear(KeyboardHandler *kbH){
  *kbH = (KeyboardHandler){0};
}
bool KeyboardHandler_hasKey(KeyboardHandler *kbH, SDL_Keycode key){
  for(Uint32 i = 0; i < kbH->used; ++i)
  if(kbH->keys[i] == key) return true;
  return false;
}

void MouseHandler_move(MouseHandler *moH, float x, float y){
  moH->pos = (SDL_FPoint){.x = x, .y = y};
}
void MouseHandler_pressButton(MouseHandler *moH, Uint8 button, Uint8 clicks){
  moH->button |= button, moH->clickNum = clicks;
}
void MouseHandler_releaseButton(MouseHandler *moH, Uint8 button){
  moH->button &= ~button;
}
bool MouseHandler_hasButton(MouseHandler *moH, Uint8 button){
  return moH->button & button;
}
void MouseHandler_scroll(MouseHandler *moH, Sint16 scroll){
  moH->scroll = scroll;
}
void MouseHandler_clear(MouseHandler *moH){
  *moH = (MouseHandler){.pos = moH->pos};
}

MenuState MenuState_new(MenuFunc fnTick, MenuFunc fnRender, KeyboardHandler *kbHandler, MouseHandler *moHandler, Uint32 auxBytes){
  MenuState menu = {
    .tick = fnTick,
    .render = fnRender,
    .kbHandler = kbHandler,
    .moHandler = moHandler,
    .memory = Arena_new(auxBytes)
  };
  return menu;
}
void MenuState_destroy(MenuState *menu){
  Arena_destroy(&menu->memory);
  *menu = (MenuState){0};
}