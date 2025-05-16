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
	os << "t0=" << timer.t0 << "\n";
	os << "t =" << timer.t  << "\n";
	return os;
}

std::istream& operator>>(std::istream& is, Timer& timer) {
	std::string line;
	std::getline(is, line);
	if (line.find("t0") != std::string::npos)
		timer.t0 = std::stol(line.substr(line.find("=") + 1));
	std::getline(is, line);
	if (line.find("t") != std::string::npos)
		timer.t = std::stol(line.substr(line.find("=") + 1));
	timer.CalibrateTime();
	return is;
}