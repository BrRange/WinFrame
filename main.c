#include <stdio.h>
#include "winframe.h"

void mainRender(WindowFrame *frame, Window window){
  struct paintHandler *paintH = &frame->paintH;
  HDC hdc = BeginPaint(window, &paintH->painter);
  SetBkMode(hdc, TRANSPARENT);
  setPaintPen(paintH, PS_SOLID, 0, RGB(0, 0, 0));
  setPaintBrush(paintH, RGB(200, 200, 255));

  SelectObject(hdc, paintH->pen);
  SelectObject(hdc, paintH->brush);

  
  SIZE txtdim;
  GetTextExtentPoint32(hdc, "Sample text", 11, &txtdim);
  Rectangle(hdc, 0, 0, txtdim.cx + 20, txtdim.cy + 20);
  TextOut(hdc, 10, 10, "Sample text", 11);
  EndPaint(window, &paintH->painter);
}

int main() {
  WindowFrame frame = newWindowFrame();
  frame.paintProc = mainRender;

  Window window = newWindow(&frame, "AI manager", -1u/2+1, -1u/2+1, -1u/2+1, -1u/2+1);
  ShowWindow(window, 1);

  MSG event;
  while (GetMessage(&event, NULL, 0, 0)) {

    if (sysTapped(VK_ESCAPE)) {
      DestroyWindow(window);
    }

    TranslateMessage(&event);
    DispatchMessage(&event);
    UpdateWindow(window);

    Sleep(10);
  }

  closeWindowFrame(&frame);

  puts("Program exit");
}