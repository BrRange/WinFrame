#include "sdlFrameGUI.h"

SDL_Color Color_hex(Uint32 hexColor){
  union{
    SDL_Color color;
    Uint32 hex;
  } convert = {.hex = hexColor};
  return convert.color;
}

GUIRect GUIRect_new(float x, float y, float w, float h, SDL_Color borderColor, SDL_Color fillColor){
  GUIRect gRect = {
    .x = x, .y = y,
    .w = w, .h = h,
    .borderColor = borderColor,
    .fillColor = fillColor
  };
  return gRect;
}

void GUIRect_setPos(GUIRect *gRect, float x, float y){
  SDL_assert(gRect);
  gRect->x = x, gRect->y = y;
}

void GUIRect_setDim(GUIRect *gRect, float w, float h){
  SDL_assert(gRect);
  gRect->w = w, gRect->h = h;
}

void GUIRect_setFillColor(GUIRect *gRect, SDL_Color fillColor){
  SDL_assert(gRect);
  gRect->fillColor = fillColor;
}

void GUIRect_setBorderColor(GUIRect *gRect, SDL_Color borderColor){
  SDL_assert(gRect);
  gRect->borderColor = borderColor;
}

void GUIRect_draw(GUIRect *gRect, SDL_Renderer *rend){
  SDL_assert(gRect);
  SDL_assert(rend);
  SDL_SetRenderDrawColor(rend, Color_expand(gRect->fillColor));
  SDL_RenderFillRect(rend, (void*)gRect);
  SDL_SetRenderDrawColor(rend, Color_expand(gRect->borderColor));
  SDL_RenderRect(rend, (void*)gRect);
}

static void GUITextBox_preRender(GUITextBox *tBox){
  SDL_Surface *canvas = tBox->wrap ? TTF_RenderText_Blended_Wrapped() : TTF_RenderText_Blended;
}

GUITextBox GUITextBox_new(GUIRect gRect, TTF_Font *font, SDL_Color textColor, bool wrap, char *buffer, Uint16 padding){
  SDL_assert(font);
  GUITextBox tBox = {
    .gRect = gRect,
    .font = font,
    .textColor = textColor,
    .wrap = wrap,
    .buffer = buffer,
    .padding = padding
  };
  return tBox;
}

void GUITextBox_setFont(GUITextBox *tBox, TTF_Font *font){
  SDL_assert(tBox);
  SDL_assert(font);
  tBox->font = font;
}

void GUITextBox_setTextColor(GUITextBox *tBox, SDL_Color textColor){
  SDL_assert(tBox);
  tBox->textColor = textColor;
}

void GUITextBox_setWrapping(GUITextBox *tBox, bool wrap){
  SDL_assert(tBox);
  tBox->wrap = wrap;
}

void GUITextBox_setPadding(GUITextBox *tBox, Uint16 padding){
  SDL_assert(tBox);
  tBox->padding = padding;
}

void GUITextBox_draw(GUITextBox *tBox, SDL_Renderer *rend){
  SDL_assert(tBox);
  SDL_assert(rend);
  GUIRect_draw(&tBox->gRect, rend);
  Uint16 pad = tBox->padding;
  SDL_Rect intRect = {
    .x = tBox->gRect.x + pad,
    .y = tBox->gRect.y + pad,
    .w = tBox->gRect.w - pad / 2,
    .h = tBox->gRect.h - pad / 2
  };

}