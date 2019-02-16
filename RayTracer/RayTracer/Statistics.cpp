#include "Statistics.h"
#include <iostream>

Statistics::Statistics()
{
	Reset();
}

Statistics::~Statistics()
{
	Reset();
}

void Statistics::SnapShot()
{
	sTime = timer.getElapsedTime();
	sMainTraces = mainTraces;
	sTraces = traces;
	sHits = hits;
	sTraceColorCalculations = traceColorCalculations;
}

void Statistics::PrintSnapShot()
{
	std::cout << "[Statistics - SnapShot]" <<
		"\n Time: \t\t" << sTime.asSeconds() << "s" <<
		"\n MainTraces: \t" << sMainTraces <<
		"\n Traces: \t" << sTraces <<
		"\n Hits: \t\t" << sHits <<
		"\n Misses: \t" << sTraces - sHits <<
		"\n Ratio: \t" << static_cast<float>(sHits) / static_cast<float>(sTraces - sHits) * 100.0f << "%" << 
		"\n ColorCalculations: " << sTraceColorCalculations <<
		std::endl;
}

void Statistics::ResetTimer()
{
	timer.restart();
}

void Statistics::Reset()
{
	mainTraces = 0;
	traces = 0;
	hits = 0;
	traceColorCalculations = 0;
	ResetTimer();
}

void Statistics::PrintStats()
{
	time = timer.getElapsedTime();

	std::cout << "[Statistics]" <<
		"\n Time: \t\t" << time.asSeconds() << "s" <<
		"\n MainTraces: \t" << mainTraces <<
		"\n Traces: \t" << traces <<
		"\n Hits: \t\t" << hits <<
		"\n Misses: \t" << traces - hits << 
		"\n Ratio: \t" << static_cast<float>(hits) / static_cast<float>(traces - hits) * 100.0f << "%" << 
		"\n ColorCalculations: " << traceColorCalculations <<
		std::endl;
}

unsigned int Statistics::mainTraces = 0;
void Statistics::increaseMainTraces()
{
	mainTraces++;
}

unsigned int Statistics::traces = 0;
void Statistics::increaseTraces()
{
	traces++;
}

unsigned int Statistics::hits = 0;
void Statistics::increaseHits()
{
	hits++;
}

unsigned int Statistics::traceColorCalculations = 0;
void Statistics::increaseColorCalculations()
{
	traceColorCalculations++;
}
