// **********************************************************************
// * FILE  : Timer.h
// * GROUP : TecLibs/System
// *---------------------------------------------------------------------
// * PURPOSE : Handles accurate time mesurement in your code.
// * COMMENT : - How to time your code well ?
// *             There are two ways of doing time measurement:
// *               -> use pentium RDTSC : retruns number of clock time in your code.
// *               -> use win32 QueryPerformanceCounter : give directly the time spent.
// *           - The accurancy of the first method is far better than the
// *             second. In fact you directly have access to the number
// *             of processor cycles between start and end.
// *           - The win32 QueryPerfomanceCounter is a win32 behavior
// *             which allows to time some code with an accurancy of about
// *             1µs, versus 10 ns for the first. So when the first is
// *             avaiable, you should use it.
// *---------------------------------------------------------------------
// * DATES     : 14/09/1999
// * AUTHORS   : Alexandre Jenny (ajenny@fr.infogrames.com)
// *             Loic Le Chevalier (llechevalier@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/TecLab 2000
// **********************************************************************
#ifndef _Timer_h_
#define _Timer_h_



// ----------------------------------------------------------------------
// +---------
// | Includes files
// +---------
#include "../TecLibs.h"    // To be Tec


// +---------
// | Platform test
// +---------
#ifndef _WIN32
    #error Win32 environment needed! (Cf. Timer.html)
#endif



// ----------------------------------------------------------------------

// **************************************************
// * SYSTEMTIMER class
// *-------------------------------------------------
// * - Handles accurate time mesurement in your code.
// * - Ex.: Timer timer();
// *        ...
// *        timer.Start();
// *        ...
// **************************************************

class Timer
{
public:
    // +---------
    // | Life-cycle
    // +---------
    Timer();
    ~Timer();

    
    // +---------
    // | Time units
    // +---------
    enum TimeUnits {
        unitCpuClock,      // result unit is in cpu clocks
        unitNanoS,         // result unit is in ns
        unitMicroS,        // result unit is in µs
        unitMilliS,        // result unit is in ms
        unitS              // result unit is in s
    };


    // +---------
    // | Manage chrono
    // +---------
    void   Start();
    Float64 Stop(TimeUnits Unit = unitCpuClock);
    void   Reset();


    // +---------
    // | Get misc values
    // +---------
    Float64 GetAverage(TimeUnits Unit = unitCpuClock) {
        return UnitConv(Unit, AverageTime);
    };

    IntS64 GetNbCalls() {
        return NbCalls;
    };

    IntS64 GetCPUFrequency() {
        return cpufreq;
    };

    IntS64 GetSelfCycle() {
        return selfcycle;
    };
    
private:
    // +---------
    // | Misc datas
    // +---------
    IntS64 NbCalls;        //!< number of times called
    IntS64 AverageTime;    //!< average of time in function : UNIT(CPU CLOCKS)

    IntS64 StartTime;      //!< time of start : UNIT(CPU CLOCKS)
    IntS64 EndTime;        //!< time of end   : UNIT(CPU CLOCKS)
    IntS64 ElapsedTime;    //!< elasped time  : UNIT(CPU CLOCKS)
    
    Bool    Running;        //!< is running or not ?


    // +---------
    // | Conversion
    // +---------
    Float64 UnitConv(TimeUnits Unit, __int64 Value);


    // +---------
    // | Calibration
    // +---------
    static IntS64 cpufreq;     //!< cpu periode : UNIT(Hz)
    static IntS64 selfcycle;   //!< store the number of cycles spent in the chronometer
    static Bool Calibrated;     //!< only calibrate the chonometer once
};

#endif//_Timer_h_
