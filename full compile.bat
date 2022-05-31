g++ -shared Server.cpp -o out/Server.dll -Wl,--kill-at
g++ -shared Manager.cpp -o out/Manager.dll -Wl,--kill-at
g++ -shared ServerNew.cpp -o out/ServerNew.dll -Wl,--kill-at
g++ -shared Manager2.cpp -o out/Manager2.dll -Wl,--kill-at
g++ -c Main.cpp -o out/Main.o 
g++ out/Main.o -o run.exe

pause