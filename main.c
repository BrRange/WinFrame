#include <stdio.h>
#include "winframeGUI.h"

Register strLen(const char *str){
  register const char *end = str;
  while(*end) ++end;
  return (Register)(end - str);
}

void mainRender(WindowFrame *frame, Window window, void **GUI){
  struct paintHandler *paintH = &frame->paintH;
  HDC hdc = BeginPaint(window, &paintH->painter);
  SetBkMode(hdc, TRANSPARENT);

  RECT rectBuf;
  GetClientRect(window, &rectBuf);
  setPaintPen(paintH, PS_SOLID, 1, 0x20a5da);
  setPaintBrush(paintH, RGB(0, 0, 20));
  SelectObject(hdc, paintH->pen);
  SelectObject(hdc, paintH->brush);

  Rectangle(hdc, 0, 0, rectBuf.right - rectBuf.left, rectBuf.bottom - rectBuf.top);

  setPaintBrush(paintH, RGB(255, 255, 255));
  SelectObject(hdc, paintH->brush);

  SIZE txtdim;
  const char *text = "This rectangle stretches to fit the text it contains. Very intriguing indeed.";
  size_t textLen = strLen(text);
  GetTextExtentPoint32(hdc, text, textLen, &txtdim);
  Rectangle(hdc, 0, 0, txtdim.cx + 20, txtdim.cy + 20);
  TextOut(hdc, 10, 10, text, textLen);

  drawRect(GUI[0], &frame->paintH, hdc);
  
  EndPaint(window, &paintH->painter);
}

void mainTick(WindowFrame *frame, Window window){
  RECT rectBuf;
  convertToWinRect(frame->GUI[0], &rectBuf);
  InvalidateRect(window, &rectBuf, 1);
  
  setRectPos(frame->GUI[0], frame->mouseH.x - ((GUIRect*)frame->GUI[0])->w / 2, frame->mouseH.y - ((GUIRect*)frame->GUI[0])->h / 2);

  convertToWinRect(frame->GUI[0], &rectBuf);
  InvalidateRect(window, &rectBuf, 1);
}

int main() {
  WindowFrame frame = newWindowFrame();
  frame.paintProc = mainRender;

  GUIRect box = {};
  setRectPen(&box, PS_SOLID, 1, 0x20a5da);
  setRectBrush(&box, RGB(63, 63, 63));
  setRectDim(&box, 20, 20);
  void *GUIElements[] = {&box};
  frame.GUI = GUIElements;

  Window window = newWindow(&frame, "AI manager", -1u/2+1, -1u/2+1, -1u/2+1, -1u/2+1);
  ShowWindow(window, 1);
  updateCursor(&frame.curH);

  Event event;
  while (IsWindow(window)) {
    
    handleEvents(&event, 0);
    mainTick(&frame, window);
    UpdateWindow(window);

    if (sysTapped(VK_ESCAPE)) {
      DestroyWindow(window);
    }

    Sleep(10);
  }

  closeWindowFrame(&frame);

  puts("Program exit");
}