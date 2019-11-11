#pragma once

#define DELTATIME 0.01
#define DELTATIMEF 0.01f
#define MS_PER_UPDATE DELTATIME

namespace CherryBell {
	class Time
	{
	public:
		Time(double seconds)
			: _time(seconds)
		{}

		operator double() { return _time; }
		operator float() { return (float)_time; }

		double GetMinutes() const { return _time != 0 ? _time / 0.6 : 0; }
		float GetMinutesFloat() const { return _time != 0 ? (float)_time / 0.6f : 0; }
		double GetSeconds() const { return _time; }
		float GetSecondsFloat() const { return (float)_time; }
		double GetMilliseconds() const { return _time * 1000.0; }
		float GetMillisecondsFloat() const { return(float)_time * 1000.0f; }
	private:
		double _time;
	};
}
