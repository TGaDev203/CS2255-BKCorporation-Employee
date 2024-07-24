#ifndef SEARCHBYNAME_H
#define SEARCHBYNAME_H

#include <queue>
#include <thread>
#include "../DSA/Stack.h"
#include "../UserLib/Corporation.h"
#include "../UserLib/Human.h"

bool isNameMatch(std::string name, std::string search_string)
{
    size_t found = name.find(search_string);
    return found != std::string::npos;
}

void searchNameInDepartment(Department *department_to_search, Stack<Human *> *search_basket, std::string search_string)
{
    // CHECK MANAGER
    Manager *manager = department_to_search->getManager();
    if (manager != nullptr)
    {
        if (isNameMatch(manager->getFullName(), search_string))
        {
            search_basket->Push(manager);
        }
    }

    // CHECK DEPUTY MANAGER
    std::map<unsigned short, DeputyManager *>* deputy_manager_list = department_to_search->getDeputyManagerList();
    for (auto iter = deputy_manager_list->begin(); iter != deputy_manager_list->end(); ++iter)
    {
        if (iter->second != nullptr)
        {
            if (isNameMatch(iter->second->getFullName(), search_string))
            {
                search_basket->Push(iter->second);
            }
        }
    }

    // CHECK EMPLOYEE
    std::map<unsigned short, Employee *>* employees_list = department_to_search->getEmployeeList();
    std::map<unsigned short, Employee *>::iterator iter;

    for (iter = employees_list->begin(); iter != employees_list->end(); ++iter)
    {
        Employee *employee_to_search = iter->second;
        if (employee_to_search != nullptr)
        {
            // CHECKING EACH EMPLOYEE
            if (isNameMatch(employee_to_search->getFullName(), search_string))
            {
                search_basket->Push(employee_to_search);
            }
        }
    }
}

void searchNameInCompany(Company *company_to_search, Stack<Human *> *search_basket, std::string search_string)
{
    //? CHECK DIRECTOR
    Director *director = company_to_search->getDirector();
    if (director != nullptr)
    {
        if (isNameMatch(director->getFullName(), search_string))
        {
            search_basket->Push(director);
        }
    }

    //? CHECK VICE DIRECTOR
    std::map<unsigned short, ViceDirector *>* vice_director_list = company_to_search->getViceDirectorList();
    for (auto iter = vice_director_list->begin(); iter != vice_director_list->end(); ++iter)
    {
        if (iter->second != nullptr)
        {
            if (isNameMatch(iter->second->getFullName(), search_string))
            {
                search_basket->Push(iter->second);
            }
        }
    }

    //! DIVIDE THREAD BASED ON THE LENGTH OF THE MAP<DEPARTMENT>
    // TO GROUP ALL THE COMPANY THREAD
    std::queue<std::thread> all_department_thread;

    std::map<std::string, Department *>* department_list = company_to_search->getDepartmentList();
    std::map<std::string, Department *>::iterator iter;

    for (iter = department_list->begin(); iter != department_list->end(); ++iter)
    {
        //? RUN MULTITHREADING IN EACH DEPARTMENT
        all_department_thread.push(std::thread(searchNameInDepartment, iter->second, search_basket, search_string));
    }

    //! JOIN ALL THE THREAD BEFORE RETURN
    while (!all_department_thread.empty())
    {
        all_department_thread.front().join();
        all_department_thread.pop();
    }
}

Stack<Human *> *searchByName(Corporation *corporation, const std::string search_string)
{
    //! INSTANTIATE MAIN THREAD as the FUNCTION to search CORPORATION
    Stack<Human *> *search_basket = new Stack<Human *>();

    //? CHECK PRESIDENT
    President *president = corporation->getPresident();
    if (president != nullptr)
    {
        if (isNameMatch(president->getFullName(), search_string))
        {
            search_basket->Push(president);
        }
    }

    //? CHECK VICE PRESIDENT
    std::map<unsigned short, VicePresident *>* vice_president_list = corporation->getVicePresidentList();
    for (auto current = vice_president_list->begin(); current != vice_president_list->end(); ++current)
    {
        if (current->second != nullptr)
        {
            if (isNameMatch(current->second->getFullName(), search_string))
            {
                search_basket->Push(current->second);
            }
        }
    }

    //! DIVIDE THREAD BASED ON THE LENGTH OF THE MAP<COMPANY>
    std::queue<std::thread> all_company_thread;

    std::map<std::string, Company *>* company_list = corporation->getCompanyList();
    std::map<std::string, Company *>::iterator iter;

    for (iter = company_list->begin(); iter != company_list->end(); ++iter)
    {
        //? RUN MULTITHREADING IN EACH COMPANY
        all_company_thread.push(std::thread(searchNameInCompany, iter->second, search_basket, search_string));
    }

    //! JOIN ALL THE THREAD BEFORE RETURN
    while (!all_company_thread.empty())
    {
        all_company_thread.front().join();
        all_company_thread.pop();
    }

    //! RETURN THE SEARCH BASKET
    return search_basket;
}

#endif