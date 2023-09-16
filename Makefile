all: main

main: main.cpp Context.hpp CPU.hpp File.hpp OperatingSystem.hpp Process.hpp ProcessParams.hpp Scheduler.hpp TimeTracker.hpp
	g++ -o main main.cpp -std=c++11 -Wall -Wextra 
