.PHONY: main debug

main:
	g++ -O3 -o main main.cpp
#	g++ -O3 -flto -mavx2 -march=znver3 -mtune=znver3 -o main main.cpp

debug:
	g++ -o main main.cpp
