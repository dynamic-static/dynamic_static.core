
/*
==========================================
  Copyright (c) 2011-2020 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#pragma once

#include "dynamic_static/core/defines.hpp"

#include <chrono>
#include <ratio>

namespace dst {

/**
TODO : Documentation
*/
using SystemClock = std::chrono::system_clock;

/**
TODO : Documentation
*/
using SteadyClock = std::chrono::steady_clock;

/**
TODO : Documentation
*/
using HighResolutionClock = std::chrono::high_resolution_clock;

/**
TODO : Documentation
*/
template <typename Rep = double>
using Hours = std::chrono::duration<Rep, std::ratio<3600>>;

/**
TODO : Documentation
*/
template <typename Rep = double>
using Minutes = std::chrono::duration<Rep, std::ratio<60>>;

/**
TODO : Documentation
*/
template <typename Rep = double>
using Seconds = std::chrono::duration<Rep, std::ratio<1>>;

/**
TODO : Documentation
*/
template <typename Rep = double>
using Milliseconds = std::chrono::duration<Rep, std::milli>;

/**
TODO : Documentation
*/
template <typename Rep = double>
using microseconds = std::chrono::duration<Rep, std::micro>;

/**
TODO : Documentation
*/
template <typename Rep = double>
using nanoseconds = std::chrono::duration<Rep, std::nano>;

/**
TODO : Documentation
*/
template <typename ClockType = HighResolutionClock, typename DurationType = nanoseconds<>>
using TimePoint = std::chrono::time_point<ClockType, DurationType>;

/**
TODO : Documentation
*/
template <typename ToDurationType, typename FromDurationType>
inline constexpr ToDurationType duration_cast(const FromDurationType& duration)
{
    return std::chrono::duration_cast<ToDurationType>(duration);
}

/**
TODO : Documentation
*/
class Timer final
{
public:
    /**
    TODO : Documentation
    */
    template <typename DurationType = Milliseconds<>>
    inline auto total() const
    {
        return duration_cast<DurationType>(HighResolutionClock::now() - mBegin).count();
    }

    /**
    TODO : Documentation
    */
    inline void reset()
    {
        mBegin = HighResolutionClock::now();
    }

private:
    TimePoint<> mBegin { HighResolutionClock::now() };
};

/**
TODO : Documentation
*/
class Clock final
{
public:
    /**
    TODO : Documentation
    */
    inline const TimePoint<>& current() const
    {
        return mCurrent;
    }

    /**
    TODO : Documentation
    */
    template <typename DurationType>
    inline auto elapsed() const
    {
        return duration_cast<DurationType>(mCurrent - mPrevious).count();
    }

    /**
    TODO : Documentation
    */
    template <typename DurationType>
    inline auto total() const
    {
        return duration_cast<DurationType>(mCurrent - mBegin).count();
    }

    /**
    TODO : Documentation
    */
    inline void update()
    {
        mPrevious = mCurrent;
        mCurrent = HighResolutionClock::now();
    }

    /**
    TODO : Documentation
    */
    inline void reset()
    {
        mBegin = HighResolutionClock::now();
        mCurrent = mBegin;
        mPrevious = mBegin;
    }

private:
    TimePoint<> mBegin { HighResolutionClock::now() };
    TimePoint<> mPrevious { mBegin };
    TimePoint<> mCurrent { mBegin };
};

} // namespace dst
