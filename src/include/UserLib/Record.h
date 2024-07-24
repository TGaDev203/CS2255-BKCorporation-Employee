#ifndef RECORD_H
#define RECORD_H

#include "Time.h"
#include "Date.h"
#include <sstream>
using namespace std;
class Record
{
private:
    Date *day_worked = nullptr;
    Time *time_start_work = nullptr;
    Time *time_go_home = nullptr;

public:
    // CONSTRUCTORS
    Record(){};
    Record(Date *day_worked, Time *time_start_work, Time *time_go_home)
    {
        delete this->day_worked;
        this->day_worked = day_worked;

        delete this->time_start_work;
        this->time_start_work = time_start_work;

        delete this->time_go_home;
        this->time_go_home = time_go_home;
    };

    Record(string record)
    {
        for (char &x : record)
        {
            if (x == ',')
            {
                x = ' ';
            }
        }
        stringstream ss(record);
        string day_worked, time_start_work, time_go_home;
        ss >> day_worked >> time_start_work >> time_go_home;

        delete this->day_worked;
        this->day_worked = new Date(day_worked);

        delete this->time_start_work;
        this->time_start_work = new Time(time_start_work);

        delete this->time_go_home;
        this->time_go_home = new Time(time_go_home);
    }

    // COPY CONSTRUCTOR
    Record(const Record *otherRecord)
    {
        if (this != otherRecord)
        {
            delete this->day_worked;
            this->day_worked = otherRecord->day_worked;

            delete this->time_start_work;
            this->time_start_work = otherRecord->time_start_work;

            delete this->time_go_home;
            this->time_go_home = otherRecord->time_go_home;
        }
    }

    ~Record()
    {
        delete this->day_worked;
        delete this->time_start_work;
        delete this->time_go_home;
    }

    // OPERATORS
    friend std::ostream &operator<<(std::ostream &os, const Record &record)
    {
        os << record.day_worked << ", " << record.time_start_work << "," << record.time_go_home;
        return os;
    }

    friend std::ostream &operator<<(std::ostream &os, const Record *record)
    {
        if (record->day_worked != nullptr)
        {
            os << record->day_worked << ", ";
        }

        if (record->time_start_work != nullptr)
        {
            os << record->time_start_work << "; ";
        }

        if (record->time_go_home != nullptr)
        {
            os << record->time_go_home;
        }

        if (record->getTimeShortage() != nullptr)
        {
            os << "| Time Shortage: " << record->getTimeShortage();
        }

        return os;
    }
    Record operator=(const Record *otherRecord)
    {
        if (this != otherRecord)
        {
            this->day_worked = otherRecord->day_worked;
            this->time_start_work = otherRecord->time_start_work;
            this->time_go_home = otherRecord->time_go_home;
        }
        return *this;
    }

    // METHODS
    Time *getTimeShortage()
    {
        // Calculating the number of hours short of employees
        // arrive late or leave early. Round up to 1 hour
        unsigned short minutesShortage = this->time_go_home->getMinutes() - this->time_start_work->getMinutes();
        unsigned short hoursShortage = this->time_go_home->getHours() - this->time_start_work->getHours();

        if (minutesShortage != 0)
        {
            if (hoursShortage < 1)
            {
                // To Prevent the Hour is 0
                hoursShortage = 1;
            }

            return new Time(hoursShortage, 0);
        }

        return new Time(hoursShortage, minutesShortage);
    }

    // PROPERTIES
    Date *getDayWorked() const { return this->day_worked; };
    Time *getTimeStartWork() const { return this->time_start_work; };
    Time *getTimeGoHome() const { return this->time_go_home; };
    Time *getTimeShortage() const { return this->getTimeShortage(); };

    void setDayWorked(Date *day_worked)
    {
        delete this->day_worked; //! PREVENT MEMORY LEAK
        this->day_worked = day_worked;
    };
    void setTimeStartWork(Time *time_started)
    {
        //! PREVENT MEMORY LEAK
        delete this->time_start_work;
        this->time_start_work = time_started;
    };
    void setTimeGoHome(Time *time_go_home)
    {
        //! PREVENT MEMORY LEAK
        delete this->time_go_home;
        this->time_go_home = time_go_home;
    };

    // OPERATORS
    bool operator==(const Record &otherRecord)
    {
        return this->day_worked == otherRecord.day_worked && this->time_start_work == otherRecord.time_start_work && this->time_go_home == otherRecord.time_go_home;
    }
    bool operator!=(const Record &otherRecord)
    {
        return this->day_worked != otherRecord.day_worked || this->time_start_work != otherRecord.time_start_work || this->time_go_home != otherRecord.time_go_home;
    }
};

#endif