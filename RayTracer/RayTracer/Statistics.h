#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class Statistics
{
public:
	Statistics();
	~Statistics();

	void SnapShot();
	void PrintSnapShot();

	void ResetTimer();
	void Reset();
	void PrintStats();
	
	static void increaseMainTraces();
	static void increaseTraces();
	static void increaseHits();
	static void increaseColorCalculations();
private:
	sf::Clock timer;
	sf::Time time;
	sf::Time sTime;

	static unsigned int mainTraces;
	unsigned int sMainTraces = 0;
	static unsigned int traces;
	unsigned int sTraces = 0;
	static unsigned int hits;
	unsigned int sHits = 0;
	static unsigned int traceColorCalculations;
	unsigned int sTraceColorCalculations = 0;
};