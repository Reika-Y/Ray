#pragma once
#include <chrono>

// 時間計測用
class Timer
{
public:
	Timer();
	~Timer();
	void Start(void);
	void Stop(void);
	long long GetTime(void);
private:
	std::pair<std::chrono::system_clock::time_point, std::chrono::system_clock::time_point> _counter;
};

