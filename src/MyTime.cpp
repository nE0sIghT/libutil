// Copyright (c) 2005 - 2015 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.

///////////////////////////////////////////////////////////////////////////////
// Header
#include "libUtilDefines.h"
#include "MyTime.h"
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/times.h>
#endif // _WIN32

// Include last!
#include "DebugNew.h"

///////////////////////////////////////////////////////////////////////////////
/**
 *  Konstruktor von @p Time.
 *
 *  @author FloSoft
 */
Time::Time(void)
{
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  Destruktor von @p Time.
 *
 *  @author FloSoft
 */
Time::~Time(void)
{
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  liefert die aktuelle Zeit.
 *
 *  @return Zeit als Timestamp
 *
 *  @author FloSoft
 */
unser_time_t Time::CurrentTime(void)
{
    return (unser_time_t)time(NULL);
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  liefert die aktuellen Ticks.
 *
 *  @return Zeit als Ticks
 *
 *  @author FloSoft
 */
unser_time_t Time::CurrentTick(void)
{
    unser_time_t ticks;
#ifdef _WIN32
    ticks = GetTickCount();
#else
    tms tm;
    ticks = times(&tm);
#endif // !_WIN32
    return ticks;
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  formatiert einen Zeitstring.
 *
 *  @param[in] format Formatstring (%Y=4 stelliges Jahr, %m 2 stelliges Monat, %D tag, %H Stunde, %i Minute, %s Sekunden)
 *  @param[in] time   zu benutzender Timestamp.
 *
 *  @return Formatted string
 *
 *  @author FloSoft
 */
std::string Time::FormatTime(const std::string& format, unser_time_t* time)
{
    time_t inTime;
    if(time)
        inTime = *time;
    else
        inTime = CurrentTime();

    tm* time_data = localtime(&inTime);
    if(!time_data)
        return "";

    using std::setw;
    std::stringstream res;
    res << std::setfill('0');

    bool isInFormat = false;
    for(std::string::const_iterator c = format.begin(); c != format.end(); ++c)
    {
        if(isInFormat)
        {
            isInFormat = false;
            switch(*c)
            {
                case 'Y':
                    res << setw(4) << (1900 + time_data->tm_year);
                    break;
                case 'm':
                    res << setw(2) << (time_data->tm_mon+1);
                    break;
                case 'd':
                    res << setw(2) << time_data->tm_mday;
                    break;
                case 'H':
                    res << setw(2) << time_data->tm_hour;
                    break;
                case 'i':
                    res << setw(2) << time_data->tm_min;
                    break;
                case 's':
                    res << setw(2) << time_data->tm_sec;
                    break;
                case '%':
                    res << '%';
                    break;
                default:
                    std::cerr << "Invalid format string: " << format << std::endl;
                    res << *c;
                    break;
            }
        }else if(*c == '%')
            isInFormat = true;
        else
            res << *c;
    }

    if(isInFormat)
        std::cerr << "Invalid format string: " << format << std::endl;

    return res.str();
}
