#ifndef WINFRAMEGUIH
#define WINFRAMEGUIH

#include "winframe.h"

struct GUIRect{
  int x, y, w, h;
  UINT penStyle, penWidth, penColor;
  UINT brushColor;
};
typedef struct GUIRect GUIRect;

void setRectPos(GUIRect *rect, int x, int y){
  rect->x = x;
  rect->y = y;
}

void setRectDim(GUIRect *rect, int w, int h){
  rect->w = w;
  rect->h = h;
}

void setRectPen(GUIRect *rect, UINT style, UINT width, UINT color){
  rect->penStyle = style;
  rect->penWidth = width;
  rect->penColor = color;
}

void setRectBrush(GUIRect *rect, UINT color){
  rect->brushColor = color;
}

void drawRect(GUIRect *rect, struct paintHandler *paintH, HDC hdc){
  setPaintPen(paintH, rect->penStyle, rect->penWidth, rect->penColor);
  setPaintBrush(paintH, rect->brushColor);

  SelectObject(hdc, paintH->pen);
  SelectObject(hdc, paintH->brush);

  Rectangle(hdc, rect->x, rect->y, rect->x + rect->w, rect->y + rect->h);
}

void convertToWinRect(GUIRect *rect, RECT *winRect){
  *winRect = (RECT){rect->x - rect->penWidth, rect->y - rect->penWidth, rect->x + rect->w + rect->penWidth, rect->y + rect->h + rect->penWidth};
}

void getCenterRect(GUIRect *rect, int *x, int *y){
  *x = rect->x + rect->w / 2;
  *y = rect->y + rect->h / 2;
}

#endif