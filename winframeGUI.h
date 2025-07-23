#ifndef WINFRAMEGUIH
#define WINFRAMEGUIH

#include "winframe.h"

Register strLen(const char *str){
  register const char *end = str;
  while(*end) ++end;
  return (Register)(end - str);
}

struct GUIRect{
  int x, y, w, h;
  unsigned penStyle, penWidth, penColor;
  unsigned brushColor;
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

void setRectPen(GUIRect *rect, unsigned style, unsigned width, unsigned color){
  rect->penStyle = style;
  rect->penWidth = width;
  rect->penColor = color;
}

void setRectBrush(GUIRect *rect, unsigned color){
  rect->brushColor = color;
}

void drawRect(GUIRect *rect, struct paintHandler *paintH, HDC hdc){
  setPaintPen(paintH, rect->penStyle, rect->penWidth, rect->penColor);
  setPaintBrush(paintH, rect->brushColor);

  SelectObject(hdc, paintH->pen);
  SelectObject(hdc, paintH->brush);

  Rectangle(hdc, rect->x, rect->y, rect->x + rect->w, rect->y + rect->h);
}

void convertRectToWinRect(GUIRect *rect, RECT *winRect){
  *winRect = (RECT){rect->x - rect->penWidth, rect->y - rect->penWidth, rect->x + rect->w + rect->penWidth, rect->y + rect->h + rect->penWidth};
}

void getRectCenter(GUIRect *rect, int *x, int *y){
  *x = rect->x + rect->w / 2;
  *y = rect->y + rect->h / 2;
}

struct GUITextBox{
  const char *text;
  Register textLen;
  unsigned fontColor;
  int padding;
  GUIRect rect;
};
typedef struct GUITextBox GUITextBox;

void setTextText(GUITextBox *txtbox, const char *text){
  txtbox->text = text;
  txtbox->textLen = strLen(text);
}

void setTextFontColor(GUITextBox *txtbox, unsigned color){
  txtbox->fontColor = color;
}

void setTextPadding(GUITextBox *txtbox, int padding){
  txtbox->padding = padding;
}

void setTextRectPos(GUITextBox *txtbox, int x, int y){
  setRectPos(&txtbox->rect, x, y);
}

void setTextRectDim(GUITextBox *txtbox, int w, int h){
  setRectDim(&txtbox->rect, w, h);
}

void setTextRectToFit(GUITextBox *txtbox, Window window){
  SIZE txtdim;
  HDC context = GetDC(window);
  GetTextExtentPoint32(context, txtbox->text, txtbox->textLen, &txtdim);
  setTextRectDim(txtbox, txtdim.cx + 2 * txtbox->padding, txtdim.cy + 2 * txtbox->padding);
  ReleaseDC(window, context);
}

void drawTextBox(GUITextBox *txtbox, struct paintHandler *paintH, HDC hdc){
  drawRect(&txtbox->rect, paintH, hdc);
  SetTextColor(hdc, txtbox->fontColor);
  TextOut(hdc, txtbox->rect.x + txtbox->padding, txtbox->rect.y + txtbox->padding, txtbox->text, txtbox->textLen);
}

struct ClickBox{
  GUIRect *rect;
};
typedef struct ClickBox ClickBox;

#endif