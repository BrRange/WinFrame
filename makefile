test:
	gcc main.c -o main.exe -lgdi32
build:
	gcc main.c -o WinFrame.exe -lgdi32 -O3 -mwindows && WinFrame.exe