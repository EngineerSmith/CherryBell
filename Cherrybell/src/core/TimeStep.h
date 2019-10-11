#pragma once

#define DELTATIME 0.01
#define MS_PER_UPDATE DELTATIME

namespace CherryBell {
	class Timestep
	{
	public:
		Timestep(double time)
			: _time(time)
		{}

		operator double() { return _time; }

		double GetSeconds() const { return _time; }
		float GetSecondsFloat() const { return (float)_time; }
		double GetMilliseconds() const { return _time * 1000.0f; }
		float GetMillisecondsFloat() const { return(float)_time; }
	private:
		double _time;
	};
}