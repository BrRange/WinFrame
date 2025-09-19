void handleEvents(SDL_Event *eve, MenuState *menu){
  while(SDL_PollEvent(eve))
  switch(eve->type & 0xFFF0){
  case SDL_EVENT_QUIT:
  return;

  case SDL_EVENT_WINDOW_DESTROYED:
    SDL_Quit();
  break;

  case SDL_EVENT_MOUSE_MOTION:
    MouseHandler_move(menu->moHandler, eve->motion.x, eve->motion.y);
  break;
  }
}