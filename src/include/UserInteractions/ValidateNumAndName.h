#ifndef VALIDATENUMANDNAME_H
#define VALIDATENUMANDNAME_H

#include <ctime>
#include <iostream>
#include <tuple>
#include "../UserLib/ValidateRegex.h"
#include "../UserLib/Time.h"

// DO SOME INT VALIDATION FUNCTION
std::string getNumAfterValidate(std::string num)
{
    while (true)
    {
        if (validateNum(num))
        {
            return num;
        }
        std::cout << "Wrong Format!!!" << std::endl;
        std::cout << "Enter Num Again: ";
        std::cin >> num;

        // IGNORE THE WHITE SPACE and the newline
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// DO SOME STRING VALIDATION FUNCTION
std::string getNameAfterValidate(std::string place, std::string name)
{
    while (true)
    {
        if (validateNameFromTerminal(name))
        {
            return name;
        }
        std::cout << "Wrong Format!!!" << std::endl;
        std::cout << "Enter " << place << " Name Again: ";
        std::getline(std::cin, name);

        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

//! FOR VALIDATE DAY DATE UPPER BOUND PURPOSE
bool isSmallerOrEqualThanToday(Date *date_to_evaluate)
{
    // Get the current time
    std::time_t currentTime = std::time(nullptr);

    // Convert the current time to a tm struct
    std::tm *now = std::localtime(&currentTime);

    // Get today year, month, day
    int today_day = now->tm_mday;
    int today_month = (now->tm_mon + 1); // Month is 0-based
    int today_year = (now->tm_year + 1900);

    if (date_to_evaluate->getYear() < today_year) //? If large than today -> IMPOSSIBLE
    {
        return true;
    }
    else if (date_to_evaluate->getYear() == today_year && date_to_evaluate->getMonth() < today_month)
    {
        return true;
    }
    else if (date_to_evaluate->getYear() == today_year && date_to_evaluate->getMonth() == today_month && date_to_evaluate->getDay() <= today_day)
    {
        return true;
    }
    std::cout << "Impossible!!" << std::endl;
    std::cout << "Today is just only: ";
    // Print the current date in the desired format
    std::cout << std::setfill('0') << std::setw(2) << now->tm_mday << '/'
              << std::setw(2) << (now->tm_mon + 1) << '/' // Month is 0-based
              << (now->tm_year + 1900) << std::endl;

    return false;
}

//! FOR VALIDATE DAY DATE LOWER BOUND PURPOSE
bool isBiggerThanDateOfBirth(Date *date_to_evaluate, Human *human)
{
    if (human->getDateOfBirth() != nullptr)
    {
        //! HUMAN DATE OF BIRTH
        unsigned short day_birth = human->getDateOfBirth()->getDay();
        unsigned short month_birth = human->getDateOfBirth()->getMonth();
        unsigned short year_birth = human->getDateOfBirth()->getYear();

        if (date_to_evaluate->getYear() > year_birth)
        {
            return true;
        }
        else if (date_to_evaluate->getYear() == year_birth && date_to_evaluate->getMonth() > month_birth)
        {
            return true;
        }
        else if (date_to_evaluate->getYear() == year_birth && date_to_evaluate->getMonth() == month_birth && date_to_evaluate->getDay() > day_birth)
        {
            return true;
        }
        std::cout << "Impossible!!" << std::endl;
        std::cout << "He/She is only birth in " << human->getDateOfBirth() << std::endl;
        return false;
    }
    return true;
}

//! FOR VALIDATE DAY STRING UPPER BOUND PURPOSE
bool isSmallerOrEqualThanToday(std::string string_date_to_evaluate)
{
    //! DATE TO EVALUATE
    Date date_to_evaluate(string_date_to_evaluate);

    // Get the current time
    std::time_t currentTime = std::time(nullptr);

    // Convert the current time to a tm struct
    std::tm *now = std::localtime(&currentTime);

    // Get today year, month, day
    int today_day = now->tm_mday;
    int today_month = (now->tm_mon + 1); // Month is 0-based
    int today_year = (now->tm_year + 1900);

    if (date_to_evaluate.getYear() < today_year) //? If large than today -> IMPOSSIBLE
    {
        return true;
    }
    else if (date_to_evaluate.getYear() == today_year && date_to_evaluate.getMonth() < today_month)
    {
        return true;
    }
    else if (date_to_evaluate.getYear() == today_year && date_to_evaluate.getMonth() == today_month && date_to_evaluate.getDay() <= today_day)
    {
        return true;
    }
    std::cout << "Impossible!!" << std::endl;
    std::cout << "Today is just only: ";
    // Print the current date in the desired format
    std::cout << std::setfill('0') << std::setw(2) << now->tm_mday << '/'
              << std::setw(2) << (now->tm_mon + 1) << '/' // Month is 0-based
              << (now->tm_year + 1900) << std::endl;

    return false;
}

//! FOR VALIDATE DAY STRING PURPOSE
bool isBiggerThanDateOfBirth(std::string string_date_to_evaluate, std::string birth_day)
{
    //! VALUATE TO VALIDATE
    Date date_to_evaluate(string_date_to_evaluate);
    Date date_birth_day(birth_day);

    //! HUMAN DATE OF BIRTH
    unsigned short day_birth = date_birth_day.getDay();
    unsigned short month_birth = date_birth_day.getMonth();
    unsigned short year_birth = date_birth_day.getYear();

    if (date_to_evaluate.getYear() > year_birth)
    {
        return true;
    }
    else if (date_to_evaluate.getYear() == year_birth && date_to_evaluate.getMonth() > month_birth)
    {
        return true;
    }
    else if (date_to_evaluate.getYear() == year_birth && date_to_evaluate.getMonth() == month_birth && date_to_evaluate.getDay() > day_birth)
    {
        return true;
    }
    std::cout << "Impossible!!" << std::endl;
    std::cout << "He/She is only birth in " << birth_day << std::endl;
    return false;
}

//! FOR VALIDATE TIME TIME
bool isTimeGoHomeBiggerThanTimeStartWork(Time *time_go_home, Time *time_start_work)
{
    if (time_go_home->getHours() == time_start_work->getHours())
    {
        return time_go_home->getMinutes() >= time_go_home->getMinutes();
    }
    return time_go_home->getHours() >= time_start_work->getHours();
}

// DO THE VALUE VALIDATION FUNCTION
std::string getValueAfterValidate(std::string value, std::function<bool(std::string)> validateFunc)
{
    while (true)
    {
        if (validateFunc(value))
        {
            return value;
        }
        std::cout << "Wrong Format!!!" << std::endl;
        std::cout << "Enter Again: ";
        std::getline(std::cin, value);
    }
}

#endif