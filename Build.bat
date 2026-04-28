g++.exe -std=c++2a  -c "Main.cpp" -o "Main.o"
g++.exe  -o "Main.exe" "Main.o" -lgdi32
del /q "Main.o"