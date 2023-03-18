// **********************************************************************
// * FILE  : Timer.h
// * GROUP : TecLibs, System section
// *---------------------------------------------------------------------
// * PURPOSE : Handles accurate time mesurement in your code.
// * COMMENT : Cf. Timer.h
// *---------------------------------------------------------------------
// * DATES     : 14/09/1999
// * AUTHORS   : Alexandre Jenny (ajenny@fr.infogrames.com)
// *             Loic Le Chevalier (llechevalier@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/TecLab 2000
// **********************************************************************
#include "Timer.h"



// ----------------------------------------------------------------------
// +---------
// | Includes files
// +---------
#include <windows.h>    // To use ?
#include <winbase.h>    // To use ?

#include <stdio.h>      // To use printf()
#include <stdlib.h>     // To use ?
#include <math.h>       // To use ?

#include <assert.h>     // To use assert()



// ----------------------------------------------------------------------
// +---------
// | Misc datas
// +---------
IntS64 Timer::cpufreq    = 0;
IntS64 Timer::selfcycle  = 0;
Bool   Timer::Calibrated = false;



// +---------
// | Get misc values
// +---------
#pragma optimize("",off)
IntS64 GetPentiumTSC(void)
{
	volatile __int64 retvalue=0;
	__asm
	{
		push	eax
		push	ebx
		push	edx
		_emit	0x0f			; cpuid
		_emit	0xa2
		_emit	0x0F			; rdtsc
		_emit	0x31
		lea		ebx, retvalue
		mov		dword ptr [ebx], eax
		mov		dword ptr [ebx+4], edx
		pop		edx
		pop		ebx
		pop		eax
	}
	return retvalue;
}
#pragma optimize("", on)



// +---------
// | Life-cycle
// +---------
Timer::Timer()
{
	NbCalls = 0;
	AverageTime = 0;
	StartTime = 0;
	EndTime = 0;
	ElapsedTime = 0;
	Running = false;
	if (!Calibrated)
	{
		selfcycle = 0;
		Bool RDTSC;
		// test if RDTSC works
		// just times twice and if duration > 0 then suppose it works
		__int64 ts1, ts2;
		ts1 = GetPentiumTSC();
		ts2 = GetPentiumTSC();
		RDTSC = (ts2>ts1);

#ifdef _DEBUG
		assert(RDTSC);
/*
#define NBMEASURE 1000
		printf("DEBUG\n");
		printf("Timing the NOP => Creating around_nop.txt \n");
		FILE *file;
		if ( (file = fopen("around_nop.txt", "w+" )) != NULL )
		{
			__int64 tb[NBMEASURE], f;
			int i;
			
			for (i=0; i<NBMEASURE; i++)
			{
				Start();
				__asm
				{
					nop
				}
				f = (__int64)Stop();
				tb[i] = f;
			}
			
			for (i=0; i<NBMEASURE; i++)
				fprintf(file, "%I64d\n", tb[i]);
			fclose(file);
		}

		printf("Timing CPU frequency => Creating frequency.txt \n");
		if ( (file = fopen("frequency.txt", "w+" )) != NULL )
		{
			LARGE_INTEGER cps, win1, win2;
			Float64 tmp=0.0;
			__int64 cpu1, cpu2, d2;
			int i, j;

			QueryPerformanceFrequency(&cps);
			
			for (i=0; i<NBMEASURE; i++)
			{
				// time some code
				QueryPerformanceCounter(&win1);
				cpu1 = GetPentiumTSC();
				for (j=0; j<10000; j++)
					tmp += sin(3.1*j*j+j*8.2);
				QueryPerformanceCounter(&win2);
				cpu2 = GetPentiumTSC();
				d2 = cps.QuadPart*(cpu2-cpu1)/(win2.QuadPart-win1.QuadPart);

				fprintf(file, "%d\n", d2);
			}
			fclose(file);
		}*/
#endif
		
		// calibration : find the processor frequency !
		// we use the windows internal high perf counter to
		// calibrate our counter. Thus the accurancy of the
		// frequency measurement is relative to the windows
		// counter.
		// We try to find the good proportion by timing a same
		// portion of code with both methods.
		// then we use stats to say us what is the best value
		// and it accurancy
		
		LARGE_INTEGER cps, win1, win2;
		Float64 tmp=0.0;
		__int64 cpu1, cpu2, d1, d2, tab[100], mean = 0;
		int i, j;

		QueryPerformanceFrequency(&cps);
		for (i=0; i<100; i++)
		{
			// time some code
			QueryPerformanceCounter(&win1);
			cpu1 = GetPentiumTSC();
			for (j=0; j<10000; j++)
				tmp += sin(3.1*j*j+j*8.2);
			QueryPerformanceCounter(&win2);
			cpu2 = GetPentiumTSC();
			
			// retrieve proportions
			d2 = cps.QuadPart*(cpu2-cpu1)/(win2.QuadPart-win1.QuadPart);
			tab[i] = d2;
			mean += d2;
		}
		mean /= 100;

		// statistic :
		d1 = 0; // covariance
		for (i=0; i<100; i++)
			d1 += (tab[i]-mean)*(tab[i]-mean);
		d1 /= 100;
		d1 = (__int64)sqrt((Float64)d1);

		// with corrections this time
		cpufreq = (mean*1000000)/1002284;

#ifdef _DEBUG
		printf("CPU Frequency %I64d Hz, Ecart Type %I64d Hz\n", cpufreq, d1);
#endif

		// try to find the nop length !
		// we times the nop until we 100 times find the same
		// value => we suppose that this is the good value in clock times
		// attention:
		// when you want to know how many cycles the CPU is spending in the
		// timer, you should not consider that selfcycle is null, because the
		// pentium pipeline would optimise it, and step over. So you should init
		// it to something totaly arbitrary. Then you substract the value found to
		// your result, and bravisimo, the timer then says that you spend 0 cpu clock
		// between start() and stop().
		d1 = d2 = 0;
		i = 0;
		selfcycle = 124524475;
		while (i<100)
		{
			Start();
			__asm
			{
				nop
			}
			d2 = (__int64)Stop();

			if (d2==d1)
				i++;
			else
			{
				d1 = d2;
				i = 0;
			}
		}
		selfcycle += d1-1;

#ifdef _DEBUG
		printf("Self cycles %I64d \n", selfcycle);
#endif
		// reset average
		Calibrated = true;
		Reset();
	}
}


// ----------------------------------------------------------------------
// +---------
// | Manage chrono
// +---------

// ******************************
// * RESET()
// *-----------------------------
// * - Reset a timing
// * - 
// ******************************
void Timer::Reset()
{
	NbCalls = 0;
	AverageTime = 0;
	StartTime = 0;
	EndTime = 0;
	Running = false;
}


// ******************************
// * START()
// *-----------------------------
// * - Start a timing
// * - 
// ******************************
void Timer::Start()
{
	StartTime = GetPentiumTSC();
}


// ******************************
// * STOP()
// *-----------------------------
// * - Stop a timeing
// * - 
// ******************************
Float64 Timer::Stop(TimeUnits Unit)
{
	EndTime = GetPentiumTSC();
	ElapsedTime = EndTime-StartTime-selfcycle;
	AverageTime = (NbCalls*AverageTime + ElapsedTime)/(NbCalls+1);
	NbCalls++;
	return UnitConv(Unit, ElapsedTime);
}



// ----------------------------------------------------------------------
// +---------
// | Conversion
// +---------
Float64 Timer::UnitConv(TimeUnits Unit, IntS64 Value)
{
	switch (Unit) {

		case unitNanoS :
			return 1e9 * (Float64)Value / (Float64)cpufreq;

		case unitMicroS :
			return 1e6 * (Float64)Value / (Float64)cpufreq;

		case unitMilliS :
			return 1e3 * (Float64)Value / (Float64)cpufreq;

		case unitS :
			return (Float64)Value / (Float64)cpufreq;

		default :
			return (Float64) Value;
	}
}
