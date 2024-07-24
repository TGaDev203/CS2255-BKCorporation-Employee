#ifndef ADDDAYSWORKED_H
#define ADDDAYSWORKED_H

#include "../UserLib/Human.h"
#include "../UserLib/ValidateRegex.h"
#include "ValidateNumAndName.h"

void addDaysWorked(Human *human)
{
    //! ATTRIBUTE TO MAKE RECORD
    Record *record_to_add = new Record();
    std::string day_work = "";
    std::string time_start_work = "";
    std::string time_go_home = "";

    //? ASK HOW MANY DAY YOU HAVE WORK
    unsigned short int_days_have_work = 0;
    std::string days_have_work = "";

    //? GET USER INPUT
    std::cout << "Number days you have work: ";
    std::cin >> days_have_work;

    // IGNORE THE WHITE SPACE and the newline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //! EVALUATE VALUE
    days_have_work = getValueAfterValidate(days_have_work, validateNum);
    int_days_have_work = stoi(days_have_work);

    //! ENTER THE DAYS HAVE WORKED
    for (int day_have_work = 1; day_have_work <= int_days_have_work; day_have_work++)
    {
    std:
        cout << "Enter day number " << days_have_work << ":" << std::endl;

        //! GET DAY WORK
        //? ASK USER INPUT THE DAY WORKED
        std::cout << "Enter the Day you have work as format dd/mm/yyyy: ";
        std::getline(std::cin, day_work);

        //! EVALUATE VALUE
        day_work = getValueAfterValidate(day_work, validateDate);
        Date *date_day_work = new Date(day_work);

        while (!(isBiggerThanDateOfBirth(date_day_work, human) && isSmallerOrEqualThanToday(date_day_work)))
        {
            std::cout << "Type the date again: " << std::endl;
            std::cout << "Enter the Day you have work as format dd/mm/yyyy: ";
            delete date_day_work; // PREVENT MEMORY LEAK

            // GET THE USER INPUT
            std::getline(std::cin, day_work);

            //! EVALUATE VALUE
            day_work = getValueAfterValidate(day_work, validateDate);
            date_day_work = new Date(day_work);
        }
        //? ASSIGN TO RECORD
        record_to_add->setDayWorked(date_day_work);

        //----------------------------------------------------------------------------------

        //! GET TIME START WORK
        //? ASK USER INPUT THE TIME START WORK
        std::cout << "Enter the Time you start work as format HH:MM with 24-hour format: ";
        std::getline(std::cin, time_start_work);

        //! EVALUATE VALUE
        time_start_work = getValueAfterValidate(time_start_work, validateTime);
        Time *obj_time_start_work = new Time(time_start_work);

        //? ASSIGN TO RECORD
        record_to_add->setTimeStartWork(obj_time_start_work);

        //----------------------------------------------------------------------------------

        //! GET TIME GO HOME
        //? ASK USER INPUT THE TIME GO HOME
        std::cout << "Enter the Time you go work as format HH:MM with 24-hour format: ";
        std::getline(std::cin, time_go_home);

        //! EVALUATE VALUE
        time_go_home = getValueAfterValidate(time_go_home, validateTime);
        Time *obj_time_go_home = new Time(time_go_home);

        while (!isTimeGoHomeBiggerThanTimeStartWork(obj_time_go_home, obj_time_start_work))
        {
            std::cout << "Impossible!!!" << std::endl;
            std::cout << "Time Go Home is larger than Time Start Work!!!" << std::endl;
            delete obj_time_go_home; // Prevent Memory Leak

            //? ASK USER INPUT THE TIME GO HOME
            std::cout << "Enter the Time you go work as format HH:MM with 24-hour format: ";
            std::getline(std::cin, time_go_home);

            //! EVALUATE VALUE
            time_go_home = getValueAfterValidate(time_go_home, validateTime);
            obj_time_go_home = new Time(time_go_home);
        }

        //? ASSIGN TO RECORD
        record_to_add->setTimeGoHome(obj_time_go_home);

        //! ASSIGN TO THAT HUMAN'S RECORD
        human->addRecord(record_to_add);
    }
}

#endif