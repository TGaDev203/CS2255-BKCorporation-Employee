#ifndef USERINTERACTIONS_H
#define USERINTERACTIONS_H

#include "../UserLib/Corporation.h"
#include "../UserLib/Company.h"
#include "../UserLib/Department.h"
#include "../UserLib/Human.h"
#include "../DSA/Stack.h"
#include "../DSA/HashMap.h"
#include "../UserLib/ValidateRegex.h"
#include "ValidateNumAndName.h"
#include "MakeCorporation.h"
#include "AddAndUpdateHuman.h"
#include "SearchByName.h"
#include "AddDaysWorked.h"
#include "WriteToTheFile.h"
#include "DeleteHuman.h"

// ALL THE REQUIREMENTS FUNCTION

// MAKE FUNCTIONS
Corporation *makeCorporation(std::string file_path = "");

// DISPLAY FUNCTIONS
void displayCorporationInfo(Corporation *corporation);
void displayHumanInfo(Human *human); //! USE searchByID()
void displayUnitInfo(Company *company);
void displayUnitInfo(Department *department);

// SEARCH FUNCTIONS USE CONCURRENCY - PARRALELISM
Stack<Human *> *searchByName(Corporation *corporation, const std::string name_input);
Human *searchByID(Corporation *corporation, const int ID);

// ADJUST FUNCTIONS USING TERMINAL
void addAndUpdateHuman(Corporation *corporation); //! USE searchByID() -> IF Yes -> Update to new One ? || IF No -> Add new One
void addDaysWorked(Human *human);
void deleteHuman(Corporation* corporation, Human* human);

// WRITE TO FILE
void writeToTheFile(Corporation *corp, std::string file_path);

// EXIT FUNCTION
void exitProgram();

//-----------------------------------------------------------------------------------------------

// DISPLAY PURPOSE ONLY
// Result: images\Output.png
void displayCorporationInfo(Corporation *corporation);
void displayHumanInfo(Human *human);
void displayUnitInfo(const Company *company);
void displayUnitInfo(const Department *department);

// MAKE CORPORATION use file_path to extract data from a FILE
// DEFAULT: it will get Input from TERMINAL to MAKE COPORATION
Corporation *makeCorporation(std::string file_path)
{
    // IF THE FILE PATH IS EMPTY
    // -> DO THE TERMINAL PART
    Corporation *corporation = nullptr;
    if (validateFileTxt(file_path))
    {
        corporation = makeCorporationFromFile(file_path);
    }
    else // DO THE TERMINAL PART
    {
        corporation = makeCorporationFromTerminal();
    }

    return corporation;
}

// DISPLAY FUNCTIONS
void displayCorporationInfo(Corporation *corporation)
{
    cout << "Corporation: " << corporation->getName() << endl;
    cout << "President: " << corporation->getPresident()->getFullName() << endl;
    cout << "Vice Presidents: ";
    for (auto current = corporation->getVicePresidentList()->begin(); current != corporation->getVicePresidentList()->end(); ++current)
    {
        cout << current->second << ", ";
    }
    cout << std::endl;
}

void displayHumanInfo(Human *human) //! USE searchByID()
{
    if (human != nullptr)
    {
        std::cout << "Here is person you find: " << '\n'
                  << human;
    }
}

void displayUnitInfo(Company *company)
{
    cout << "Company: " << company->getName() << endl;
    cout << "Director: " << company->getDirector()->getFullName() << endl;
    cout << "Vice Directors: ";
    for (auto current = company->getViceDirectorList()->begin(); current != company->getViceDirectorList()->end(); ++current)
    {
        cout << current->second << ", ";
    }
    cout << std::endl;
}

// EXIT FUNCTION
void exitProgram()
{
    exit(0);
}

#endif