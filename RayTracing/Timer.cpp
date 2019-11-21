#include "Timer.h"

Timer::Timer()
{
	Start();
}

Timer::~Timer()
{
}

void Timer::Start(void)
{
	_counter.first = std::chrono::system_clock::now();
}

void Timer::Stop(void)
{
	_counter.second = std::chrono::system_clock::now();
}

long long Timer::GetTime(void)
{
	Stop();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(_counter.second - _counter.first).count();
	return duration;
}
