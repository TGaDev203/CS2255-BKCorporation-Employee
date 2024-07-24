#ifndef ADDANDHUMAN_H
#define ADDANDHUMAN_H

#include <string>
#include "../UserLib/Corporation.h"
#include "../UserLib/Human.h"
#include "../UserLib/ValidateRegex.h"
#include "SearchByID.h"
#include "ValidateNumAndName.h"
#include "DeleteHuman.h"

std::string askUpdateOrStop(std::string userInput)
{
    std::cout << "THERE IS CURRENTLY THERE IS 1 PERSON with the SAME ID in the CORPORATION" << std::endl;
    std::cout << "Do you want to UPDATE to new one or STOP: " << std::endl;
    std::cout << "UPDATE or STOP: ";

    std::getline(std::cin, userInput);
    while (true)
    {
        if (userInput == "STOP")
        {
            return "STOP";
        }
        else if (userInput == "UPDATE")
        {
            return "UPDATE";
        }
        else
        {
            std::cout << "Invalid Input!!!" << std::endl;
            std::cout << "Please enter STOP or UPDATE: ";
            std::getline(std::cin, userInput);
        }
    }
    return "UPDATE"; // DEFAULT VALUE
}

// ADD HUMAN will get Input from TERMINAL to MAKE HUMAN
void addAndUpdateHuman(Corporation *corporation)
{
    //* HUMAN ATTRIBUTES
    unsigned short ID = 0;
    std::string string_ID = "";
    std::string name = "";
    std::string first_name = "";
    std::string last_mid_name = "";
    std::string work_place = "";
    std::string position = "";
    std::string date_of_birth = "";
    std::string birth_place = "";
    std::string email = "";
    std::string phone_num = "";
    std::string first_day_at_work = "";

    // WELCOME
    std::cout << "-----------------------TIME TO MAKE SOME EMPLOYEE-----------------------" << std::endl;

    //* GET INPUT
    //? ID
    std::cout << "Enter ID: ";
    std::cin >> string_ID;

    // IGNORE THE NEW LINE CHARACTER
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    //! DO SOME INTEGER VALIDATIONS
    string_ID = getValueAfterValidate(string_ID, validateNum);
    std::stringstream ss(string_ID);
    ss >> ID;

    //!! VALIDATE ID ??
    Human *human_same_ID = searchByID(corporation, ID);
    if (human_same_ID != nullptr)
    {
        if (human_same_ID->getID() == ID)
        {
            // THEY BOTH HAVE THE SAME ID ->
            // CASE 1: Stop Add
            // Case 2: UPDATE TO THE NEW ONE
            std::string userInput = "";
            userInput = askUpdateOrStop(userInput);

            if (userInput == "STOP")
            {
                return; // STOP THE PROGRAM
            }
            else if (userInput == "UPDATE")
            {
                deleteHuman(corporation, human_same_ID);
            }
        }
    }

    //! UPDATE TO NEW ONE

    //? Name
    std::cout << "Enter NAME: ";
    std::getline(std::cin, name);

    // IGNORE THE NEW LINE CHARACTER
    // std::cin.ignore();

    //! DO SOME STRING VALIDATIONS and DO SOME STRING EXTRACT
    name = getValueAfterValidate(name, validateName);
    std::tuple<std::string, std::string> name_extracted = extractName(name);

    first_name = std::get<0>(name_extracted);
    last_mid_name = std::get<1>(name_extracted);

    // IGNORE THE NEW LINE CHARACTER
    // std::cin.ignore();

    //? DATE OF BIRTH
    std::cout << "Enter DATE OF BIRTH follow the format dd/mm/yyyy:: ";
    std::getline(std::cin, date_of_birth);

    // IGNORE THE NEW LINE CHARATER
    // std::cin.ignore();
    //! VALIDATE DATE OF BIRTH
    date_of_birth = getValueAfterValidate(date_of_birth, validateDate);

    while (!isSmallerOrEqualThanToday(date_of_birth))
    {
        //? GET DATE OF BIRTH AGAIN
        std::cout << "Enter DATE OF BIRTH follow the format dd/mm/yyyy:: ";
        std::getline(std::cin, date_of_birth);

        //! VALIDATE DATE OF BIRTH
        date_of_birth = getValueAfterValidate(date_of_birth, validateDate);
    }

    //? BIRTH PLACE
    std::cout << "Enter BIRTH PLACE: ";
    std::getline(std::cin, birth_place);

    // IGNORE THE NEW LINE CHARACTER
    // std::cin.ignore();

    birth_place = getValueAfterValidate(birth_place, validatePlace);

    //? EMAIL
    std::cout << "Enter EMAIL: ";
    std::getline(std::cin, email);

    // IGNORE THE NEW LINE CHARACTER
    // std::cin.ignore();

    email = getValueAfterValidate(email, validateEmail);

    //? PHONE NUM
    std::cout << "Enter PHONE NUMBER: ";
    std::getline(std::cin, phone_num);

    // IGNORE THE NEW LINE CHARACTER
    // std::cin.ignore();

    phone_num = getValueAfterValidate(phone_num, validatePhoneNum);

    //? FIRST DAY AT WORK
    std::cout << "Enter FIRST DAY AT WORK follow the format dd/mm/yyyy: ";
    std::getline(std::cin, first_day_at_work);

    //! VALIDATE DATE OF WORK
    first_day_at_work = getValueAfterValidate(first_day_at_work, validateDate);

    while (!(isBiggerThanDateOfBirth(first_day_at_work, date_of_birth) && isSmallerOrEqualThanToday(first_day_at_work)))
    {
        std::cout << "Type the date again: " << std::endl;
        std::cout << "Enter the Day you have work as format dd/mm/yyyy: ";

        // GET THE USER INPUT
        std::getline(std::cin, first_day_at_work);

        //! EVALUATE VALUE
        first_day_at_work = getValueAfterValidate(first_day_at_work, validateDate);
    }

    //? WORK PLACE
    //? WORK PLACE + POSITION -> ASSIGN TO THE EQUIVALENT CORPORATION position
    std::cout << "Enter WORK PLACE" << std::endl;
    std::cout << "Corporation or Company or Department: ";
    std::getline(std::cin, work_place);

    //! DO SOME STRING VALIDATIONS
    // IF THE USER TYPE UNVAILABLE
    while (work_place != "Corporation" || work_place != "Company" || work_place != "Department")
    {
        if (work_place == "Corporation" || work_place == "Company" || work_place == "Department")
        {
            break;
        }
        std::cout << "Enter WORK PLACE again" << std::endl;
        std::cout << "Corporation or Company or Department: ";
        std::getline(std::cin, work_place);

        // IGNORE THE NEW LINE CHARACTER
        // std::cin.ignore();
    }

    //? EVALUATE POSITION BASED ON WORK PLACE
    //? POSITION
    if (work_place == "Corporation")
    {
        std::cout << "Enter POSITION: " << std::endl;
        std::cout << "President or Vice President: ";
        std::getline(std::cin, position);
        position = getValueAfterValidate(position, validateCorporationPosition);

        if (position == "President")
        {
            President *new_president = new President(ID, last_mid_name, first_name, work_place, position, date_of_birth, birth_place, email, phone_num, first_day_at_work);
            corporation->setPresident(new_president);
        }
        else if (position == "Vice President")
        {
            VicePresident *new_vice_president = new VicePresident(ID, last_mid_name, first_name, work_place, position, date_of_birth, birth_place, email, phone_num, first_day_at_work);
            corporation->addVicePresident(new_vice_president);
        }
    }
    else if (work_place == "Company")
    {
        std::cout << "Enter POSITION: " << std::endl;
        std::cout << "Director or Vice Director: ";
        std::getline(std::cin, position);
        position = getValueAfterValidate(position, validateCompanyPosition);

        // DISPLAY ALL THE AVAILABLE COMPANY
        std::cout << "Available Company in " + corporation->getName() + ": ";
        std::map<std::string, Company *> *company_list = corporation->getCompanyList();
        for (auto current = company_list->begin(); current != company_list->end(); ++current)
        {
            std::cout << current->first << " | ";
        }
        std::cout << std::endl;

        // ASK THE USER TO INPUT THE RIGHT COMPANY NAME
        std::string input_company_name = "";
        std::cout << "Enter the COMPANY NAME: ";
        std::getline(std::cin, input_company_name);

        // IGNORE THE NEW LINE CHARACTER
        // std::cin.ignore();

        // IF DON'T EXIST -> LOOP
        while (!company_list->count(input_company_name))
        {
            std::cout << "Enter the Company Name again: ";
            std::getline(std::cin, input_company_name);

            // std::cin.ignore();
        }

        if (position == "Director")
        {
            // ADD NEW DIRECTOR
            Director *new_director = new Director(ID, last_mid_name, first_name, work_place, position, date_of_birth, birth_place, email, phone_num, first_day_at_work);
            company_list->at(input_company_name)->setDirector(new_director);
        }
        else if (position == "Vice Director")
        {
            ViceDirector *new_vice_director = new ViceDirector(ID, last_mid_name, first_name, work_place, position, date_of_birth, birth_place, email, phone_num, first_day_at_work);
            company_list->at(input_company_name)->addViceDirector(new_vice_director);
        }
    }
    else if (work_place == "Department")
    {
        std::cout << "Enter POSITION: " << std::endl;
        std::cout << "Manager or Deputy Manager or Employee: ";
        std::getline(std::cin, position);
        position = getValueAfterValidate(position, validateDepartmentPosition);

        // DISPLAY ALL THE AVAILABLE COMPANY
        std::cout << "Available Company in " + corporation->getName() + ": ";
        std::map<std::string, Company *> *company_list = corporation->getCompanyList();
        for (auto current = company_list->begin(); current != company_list->end(); ++current)
        {
            std::cout << current->first << " | ";
        }
        std::cout << std::endl;

        // ASK THE USER TO INPUT THE RIGHT COMPANY NAME
        std::string input_company_name = "";
        std::cout << "Enter the COMPANY NAME: ";
        std::getline(std::cin, input_company_name);

        // IGNORE THE NEW LINE CHARACTER
        // std::cin.ignore();

        // IF DON'T EXIST -> LOOP
        while (!company_list->count(input_company_name))
        {
            std::cout << "Enter the Company Name again: ";
            std::getline(std::cin, input_company_name);

            // std::cin.ignore();
        }

        Company *company_to_add = company_list->at(input_company_name);
        std::map<std::string, Department *> *department_list = company_to_add->getDepartmentList();
        // DISPLAY ALL AVAILABLE DEPARTMENT NAME
        std::cout << "Available Departments in " + company_to_add->getName() + ": ";
        for (auto current = department_list->begin(); current != department_list->end(); ++current)
        {
            std::cout << current->first << " | ";
        }
        std::cout << std::endl;

        std::string input_department_name = "";
        std::cout << "Enter the Department Name: ";
        std::getline(std::cin, input_department_name);

        // LOOP UNTIL GET THE RIGHT INPUT
        while (!department_list->count(input_department_name))
        {
            std::cout << "Enter the Department Name again: ";
            std::getline(std::cin, input_department_name);
        }

        if (position == "Manager")
        {
            Manager *new_manager = new Manager(ID, last_mid_name, first_name, work_place, position, date_of_birth, birth_place, email, phone_num, first_day_at_work);
            department_list->at(input_department_name)->setManager(new_manager);
        }
        else if (position == "Deputy Manager")
        {
            DeputyManager *new_deputy_manager = new DeputyManager(ID, last_mid_name, first_name, work_place, position, date_of_birth, birth_place, email, phone_num, first_day_at_work);
            department_list->at(input_department_name)->addDeputyManager(new_deputy_manager);
        }
        else if (position == "Employee")
        {
            Employee *new_employee = new Employee(ID, last_mid_name, first_name, work_place, position, date_of_birth, birth_place, email, phone_num, first_day_at_work);
            department_list->at(input_department_name)->addEmployee(new_employee);
        }
    }
    // IGNORE THE NEW LINE CHARACTER
    std::fflush(stdin);
}
#endif