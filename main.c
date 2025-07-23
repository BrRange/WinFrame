#include <stdio.h>
#include "winframeGUI.h"

void mainRender(WindowFrame *frame, Window window, void **GUI){
  RECT rectBuf;
  GetClientRect(window, &rectBuf);
  int clientW = rectBuf.right - rectBuf.left;
  int clientH = rectBuf.bottom - rectBuf.top;

  if(clientW <= 0 || clientH <= 0) return;
  if(!frame->bitmap){
    setBitmap(frame, window);
    return;
  }

  struct paintHandler *paintH = &frame->paintH;
  HDC hdc = BeginPaint(window, &paintH->painter);

  HDC contx = CreateCompatibleDC(hdc);
  HBITMAP refBitmap = (HBITMAP)SelectObject(contx, frame->bitmap);

  SetBkMode(contx, TRANSPARENT);
  setPaintPen(paintH, PS_SOLID, 1, 0x20a5da);
  setPaintBrush(paintH, RGB(0, 0, 20));
  SelectObject(contx, paintH->pen);
  SelectObject(contx, paintH->brush);

  Rectangle(contx, 0, 0, clientW, clientH);

  drawTextBox(GUI[0], paintH, contx);
  
  BitBlt(
    hdc,
    paintH->painter.rcPaint.left,
    paintH->painter.rcPaint.top,
    paintH->painter.rcPaint.right - paintH->painter.rcPaint.left,
    paintH->painter.rcPaint.bottom - paintH->painter.rcPaint.top,
    contx,
    paintH->painter.rcPaint.left,
    paintH->painter.rcPaint.top,
    SRCCOPY
  );

  SelectObject(contx, refBitmap);
  DeleteDC(contx);
  EndPaint(window, &paintH->painter);
}

void mainTick(WindowFrame *frame, Window window){
  RECT rectBuf;
  GetClientRect(window, &rectBuf);

  GUITextBox *txtbox = frame->GUI[0];
  int wincx = (rectBuf.left + rectBuf.right) >> 1;
  int wincy = (rectBuf.top + rectBuf.bottom) >> 1;
  
  convertRectToWinRect(&txtbox->rect, &rectBuf);
  InvalidateRect(window, &rectBuf, 0);

  setTextRectToFit(frame->GUI[0], window);
  setTextRectPos(txtbox, wincx - txtbox->rect.w / 2, wincy - txtbox->rect.h / 2);
  
  convertRectToWinRect(&txtbox->rect, &rectBuf);
  InvalidateRect(window, &rectBuf, 0);
}

int main() {
  WindowFrame frame = newWindowFrame();
  frame.paintProc = mainRender;
  
  GUITextBox txtbox = {};
  setTextText(&txtbox, "Hello, my name is name");
  setTextFontColor(&txtbox, 0x0000ff);
  setTextPadding(&txtbox, 20);
  setRectPen(&txtbox.rect, PS_SOLID, 1, 0x0000ff);
  setRectBrush(&txtbox.rect, 0xdddddd);
  
  void *GUIElements[] = {&txtbox};
  frame.GUI = GUIElements;
  
  Window window = newWindow(&frame, "AI manager", 0x80000000, 0x80000000, 0x80000000, 0x80000000);
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