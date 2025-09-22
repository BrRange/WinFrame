#ifndef SDL_FRAME_GUI_H_
#define SDL_FRAME_GUI_H_

#include "sdlFrame.h"
#include "SDL3/SDL_ttf.h"

#define Color_expand(_color) (_color).r, (_color).g, (_color).b, (_color).a
#define Hex_expandRGBA(_hexColor) (Uint8)((_hexColor) >> 24), (Uint8)((_hexColor) >> 16), (Uint8)((_hexColor) >> 8), (Uint8)(_hexColor)
#define Hex_expandRGB(_hexColor) (Uint8)((_hexColor) >> 16), (Uint8)((_hexColor) >> 8), (Uint8)((_hexColor)), (Uint8)(255)

SDL_Color Color_hex(Uint32 hexColor);

struct GUIRect{
  float x, y, w, h;
  SDL_Color borderColor, fillColor;
};
typedef struct GUIRect GUIRect;

GUIRect GUIRect_new(float x, float y, float w, float h, SDL_Color borderColor, SDL_Color fillColor);
void GUIRect_setPos(GUIRect*, float x, float y);
void GUIRect_setDim(GUIRect*, float w, float h);
void GUIRect_setFillColor(GUIRect*, SDL_Color);
void GUIRect_setBorderColor(GUIRect*, SDL_Color);
void GUIRect_draw(GUIRect*, SDL_Renderer*);

struct GUITextBox{
  GUIRect gRect;
  TTF_Font *font;
  SDL_Color textColor;
  bool wrap;
  Uint16 padding;
  char *buffer;
  SDL_Texture *preRender;
};
typedef struct GUITextBox GUITextBox;

GUITextBox GUITextBox_new(GUIRect, TTF_Font*, SDL_Color textColor, bool wrap, char *buffer, Uint16 padding);
void GUITextBox_setFont(GUITextBox*, TTF_Font*);
void GUITextBox_setTextColor(GUITextBox*, SDL_Color);
void GUITextBox_setWrapping(GUITextBox*, bool);
void GUITextBox_draw(GUITextBox*, SDL_Renderer*);

#endif