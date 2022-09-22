#pragma once
#include <iostream>
#include <string>
#include <chrono>


using namespace std;


class SimpleTimer {
public:
	SimpleTimer(const char * _name) : name(_name) {
		start = std::chrono::high_resolution_clock::now();
	};
	~SimpleTimer() {
		stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> duration = stop - start;
		cout << name << " " << duration.count() << "s" << endl;
	};
private:
	std::chrono::time_point<std::chrono::steady_clock> start, stop;
	string name;
};
