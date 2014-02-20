#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <sstream> 
#include <unistd.h>

using namespace std;

long QueryPerformanceFrequency();
long QueryPerformanceCounter();
long GetTickCount(long& startTime);

int main()
{  	   
	long freq = QueryPerformanceFrequency();
	long time = QueryPerformanceCounter();
	// get the number of "ticks" since program start.
	long ticks = GetTickCount(time); // count is 

	cout << "Query Performance Frequency = " << freq << '\n';
	cout << "Query Performance Counter = " << time << '\n';
	cout << "Ticks Since Program start = " << ticks << '\n';

	return 0;
}

// get the CPU freq
long QueryPerformanceFrequency()
{
	FILE * catcmd;
	char output[20];
	int endchar;
	double mhz;

	catcmd = popen("cat /proc/cpuinfo | grep MHz", "r"); // open file
	endchar = fread(output, 1, 20, catcmd);
	output[endchar] = '\0';

	string tmp = output;
	int position = tmp.find (':');
	string x = tmp.substr ((position + 2), 8);
	pclose(catcmd); // close file

	stringstream s(x);
	s >> mhz;

	mhz = mhz * 100;

	return mhz;
}

// get the time
long QueryPerformanceCounter()
{
	struct timeval time;
	gettimeofday(&time, 0);
	return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

// get ticks (since program start)
long GetTickCount(long &startTime)
{
	long start = startTime;

	// some work to do between ticks ....
	for(int i = 0; i <= 2; i++){
		sleep (1);
		cout << "counting ..." << '\n';
	}

	long nowTime = QueryPerformanceCounter(); 
	long ticksElapsed = (nowTime - start);

	return ticksElapsed;
}


