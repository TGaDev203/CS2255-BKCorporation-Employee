#ifndef DELETEHUMAN_H
#define DELETEHUMAN_H

#include "../UserLib/Corporation.h"
#include "../UserLib/ValidateRegex.h"

//! SET STOP FLAG
std::atomic<bool> isContinueDeleting = true;

void deleteHumanInDepartment(Department *department_to_search, Human *human_to_delete)
{
    //? CHECK MANAGER
    Manager *manager = department_to_search->getManager();
    if (manager != nullptr)
    {
        if (isIDMatch(manager->getID(), human_to_delete->getID()))
        {
            isContinueDeleting = false;
            
            //! PREVENT MEMORY LEAK
            delete manager;
            department_to_search->setManager(nullptr);
            return;
        }
    }

    //? CHECK DEPUTY MANAGER
    std::map<unsigned short, DeputyManager *> *deputy_manager_list = department_to_search->getDeputyManagerList();
    if (deputy_manager_list->count(human_to_delete->getID()))
    {
        isContinueDeleting = false;
        //! PREVENT MEMORY LEAK
        deputy_manager_list->erase(human_to_delete->getID());
        delete human_to_delete;
        
        return;
    }

    //? CHECK EMPLOYEE
    std::map<unsigned short, Employee *> *employees_list = department_to_search->getEmployeeList();
    employees_list->erase(human_to_delete->getID());
    delete human_to_delete;
    return;
}

void deleteHumanInCompany(Company *company_to_search, Human *human_to_delete)
{
    //? CHECK DIRECTOR
    Director *director = company_to_search->getDirector();
    if (director != nullptr)
    {
        if (isIDMatch(director->getID(), human_to_delete->getID()))
        {
            isContinueDeleting = false;
            
            //! PREVENT MEMORY LEAK
            delete director;
            company_to_search->setDirector(nullptr);
            return;
        }
    }

    //? CHECK VICE DIRECTOR
    std::map<unsigned short, ViceDirector *> *vice_director_list = company_to_search->getViceDirectorList();
    if (vice_director_list->count(human_to_delete->getID()))
    {
        isContinueDeleting = false;
        vice_director_list->erase(human_to_delete->getID());

        //! PREVENT MEMORY LEAK
        delete human_to_delete;
        return;
    }

    //! DIVIDE THREAD BASED ON THE LENGTH OF THE MAP<DEPARTMENT>
    // TO GROUP ALL THE COMPANY THREAD
    std::queue<std::thread> all_department_thread;

    std::map<std::string, Department *> *department_list = company_to_search->getDepartmentList();

    for (auto iter = department_list->begin(); iter != department_list->end(); ++iter)
    {
        //? RUN MULTITHREADING IN EACH DEPARTMENT
        if (isContinueDeleting) //? IF STILL DIDN'T FIND THAT VALUE -> CONTINUE SEARCHING
        {
            all_department_thread.push(std::thread(deleteHumanInDepartment, iter->second, human_to_delete));
        }
    }

    //! JOIN ALL THE THREAD BEFORE RETURN
    while (!all_department_thread.empty())
    {
        all_department_thread.front().join();
        all_department_thread.pop();
    }
}

void deleteHuman(Corporation *corporation, Human *human_to_delete)
{
    //? CHECK PRESIDENT
    President *president = corporation->getPresident();
    if (president != nullptr)
    {
        // IF ID MATCH
        if (isIDMatch(president->getID(), human_to_delete->getID()))
        {
            isContinueDeleting = false;

            //! PREVENT MEMORY LEAK
            delete president;
            corporation->setPresident(nullptr);
            return;
        }
    }

    //? CHECK VICE PRESIDENT
    std::map<unsigned short, VicePresident *> *vice_president_list = corporation->getPointerofVicePresidentList();
    if (vice_president_list->count(human_to_delete->getID()))
    {
        isContinueDeleting = false;
        vice_president_list->erase(human_to_delete->getID());

        //! PREVENT MEMORY LEAK
        delete human_to_delete;
        return;
    }

    delete human_to_delete;

    //! DIVIDE THREAD BASED ON THE LENGTH OF THE MAP<COMPANY>
    std::queue<std::thread> all_company_thread;

    std::map<std::string, Company *> *company_list = corporation->getPointerofCompanyList();

    for (auto iter = company_list->begin(); iter != company_list->end(); ++iter)
    {
        if (isContinueDeleting) //? IF STILL DIDN'T FIND THAT VALUE -> CONTINUE SEARCHING
        {
            //? RUN MULTITHREADING IN EACH COMPANY
            all_company_thread.push(std::thread(deleteHumanInCompany, iter->second, human_to_delete));
        }
    }

    //! JOIN ALL THE THREAD BEFORE RETURN
    while (!all_company_thread.empty())
    {
        all_company_thread.front().join();
        all_company_thread.pop();
    }
}

#endif