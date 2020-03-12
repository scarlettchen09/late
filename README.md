# late
CIS 29 Group Project - Late! Game

Linux compile/link instructions:
---
1) Turn Score.cpp into an object file:

g++ src/Score.cpp -c -Iinclude -L/usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -o src/Score.o

2) Make static library from Score:

ar rcs lib/Score.a src/Score.o

3) Compile command that links the static library Score.a:

g++ src/*.cpp -Iinclude -Llib -L/usr/local/lib -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system ./lib/Score.a -o late-game 

4) Run the game! :)
./late-game
---
