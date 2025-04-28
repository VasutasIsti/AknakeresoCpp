#include "timer.hpp"

void Timer::CalibrateTime() {
	time_t current = time(nullptr);
	t = (t-t0) + current;
	t0 = current;
}

time_t Timer::GetDeltaTime() {
	t = time(nullptr);
	return t - t0;
}

std::ostream& operator<<(std::ostream& os, const Timer& timer) {
	// TODO
	// majd \n a vegere
	return os;
}

std::istream& operator>>(std::istream& is, Timer& timer) {
	// TODO
	return is;
}