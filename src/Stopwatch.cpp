/*
 * Stopwatch.cpp
 *
 *  Created on: Mar 18, 2010
 *      Author: Sebastian Scherer <sebastian.scherer@uni-tuebingen.de>
 */

#include <utils_general/Stopwatch.h>
#include <utils_general/RamaxxException.h>

#include <cstdio>

Stopwatch::Stopwatch() {
    reset();
}

//Should this method do the same like resume() or should it act like reset()?
void Stopwatch::restart() {
    clock_gettime(CLOCK_REALTIME, &mStart);
    //gettimeofday(&mStart, NULL);
    stopped = false;
}

void Stopwatch::reset() {
    clock_gettime(CLOCK_REALTIME, &mStart);
    //gettimeofday(&mStart, NULL);
    mStop.tv_sec = 0;
    //mStop.tv_usec = 0;
    mStop.tv_nsec = 0;
    stopped = false;
}

void Stopwatch::resetStopped() {
    mStop.tv_sec = 0;
    //mStop.tv_usec = 0;
    mStop.tv_nsec = 0;
    stopped = true;
}

int Stopwatch::sElapsed() const {
    //timeval t;
    timespec t;
    //gettimeofday(&t, NULL);
    clock_gettime(CLOCK_REALTIME, &t);

    return t.tv_sec - mStart.tv_sec;
}

int Stopwatch::msElapsed() const {
    //timeval t;
    timespec t;
    //gettimeofday(&t, NULL);
    clock_gettime(CLOCK_REALTIME, &t);

    int msElapsed = (t.tv_sec - mStart.tv_sec)*1000;
    //msElapsed += (t.tv_usec - mStart.tv_usec)/1000;
    msElapsed += (int)((t.tv_nsec - mStart.tv_nsec)/(long)1000000);
    return msElapsed;
}

int Stopwatch::usElapsed() const {
    //timeval t;
    timespec t;
    //gettimeofday(&t, NULL);
    clock_gettime(CLOCK_REALTIME, &t);

    int seconds = t.tv_sec - mStart.tv_sec;
    //int useconds = t.tv_usec - mStart.tv_usec;
    int useconds = (int)((t.tv_nsec - mStart.tv_nsec)/(long)1000);
    return seconds * 1000000 + useconds;
}

double Stopwatch::sElapsedDouble() const {
    return msElapsed() / 1000.0;
}

double Stopwatch::elapsed() const {
    int seconds = mStop.tv_sec;
    //int useconds = mStop.tv_usec;
    long nseconds = mStop.tv_nsec;
    if (not stopped) {
        //timeval t;
        timespec t;
        //gettimeofday(&t, NULL);
        clock_gettime(CLOCK_REALTIME, &t);
        seconds += t.tv_sec - mStart.tv_sec;
        //useconds += t.tv_usec - mStart.tv_usec;
        nseconds += t.tv_nsec - mStart.tv_nsec;
    }
    //return seconds + useconds / 1000000.0;
    return seconds + nseconds / 1000000000.0;
}

std::ostream& operator<<(std::ostream& stream, const Stopwatch& watch) {
    int timeInUs = watch.usElapsed();
    int us = timeInUs%1000;
    int ms = timeInUs/1000%1000;
    int s  = timeInUs/1000000;
    if (s > 0) stream << s << " s, " << ms << " ms and ";
    else if (ms > 0) stream << ms << " ms and ";
    return stream << us << " us.";
}

void Stopwatch::stop() {
    //timeval t;
    timespec t;
    if (stopped == false)
    {
        //gettimeofday(&t, NULL);
        clock_gettime(CLOCK_REALTIME, &t);
        stopped = true;
        mStop.tv_sec += t.tv_sec - mStart.tv_sec;
        //mStop.tv_usec += t.tv_usec - mStart.tv_usec;
        mStop.tv_nsec += t.tv_nsec - mStart.tv_nsec;
    }
}

void Stopwatch::resume() {
    if (not stopped)
        throw RamaxxException("Stopwatch was not stopped.");
    //gettimeofday(&mStart, NULL);
    clock_gettime(CLOCK_REALTIME, &mStart);
    stopped = false;
}

int Stopwatch::sElapsedStatic() {
    return mStop.tv_sec;
}

int Stopwatch::usElapsedStatic() {
    int seconds = mStop.tv_sec;
    //int useconds = mStop.tv_usec;
    long useconds = mStop.tv_nsec/(long)1000;
    return seconds * 1000000 + (int)useconds;
}

long Stopwatch::nsElapsedStatic() {
    long seconds = mStop.tv_sec;
    long nseconds = mStop.tv_nsec;
    return seconds * 1000000000 + nseconds;
}
