#ifndef WRITETOTHEFILE
#define WRITETOTHEFILE

#include <bits/stdc++.h>
#include "../UserLib/Corporation.h"
#include "../DSA/Queue.h"

// write the president
// wirte the vice presidents
// for each company:
// write director
// write the vice directors
// for each department
// write the manager
// write the deputy managers
// write the employees.
std::string filling(unsigned short a)
{
    if (a < 10)
    {
        return "0" + to_string(a);
    }
    else
    {
        return to_string(a);
    }
}
void writeToTheFile(Corporation *corp, std::string file_path)
{
    ofstream fs(file_path);
    // write the president
    // wirte the vice presidents
    // for each company:
    // write director
    // write the vice directors
    // for each department
    // write the manager
    // write the deputy managers
    // write the employees.
    President *p = corp->getPresident();
    std::string name_of_corp = corp->getName();
    if (p != nullptr)
    {
        fs << p->getID() << "\t" << p->getLastMidName() + " " + p->getFirstName() << "\t" << name_of_corp << "\t" << p->getPosition() << "\t" << p->getDateOfBirth()->getYear() << "-" << filling(p->getDateOfBirth()->getMonth()) << "-" << filling(p->getDateOfBirth()->getDay()) << "\t" << p->getBirthPlace() << "\t" << p->getEmail() << "\t" << p->getPhoneNum() << "\t" << p->getFirstDayAtWork()->getYear() << "-" << filling(p->getFirstDayAtWork()->getMonth()) << "-" << filling(p->getFirstDayAtWork()->getDay()) << "\t" << endl;
    }
    std::map<unsigned short, VicePresident *> *vp_list_pointer = corp->getPointerofVicePresidentList();

    for (auto cur = vp_list_pointer->begin(); cur != vp_list_pointer->end(); ++cur)
    {
        if (cur->second != nullptr)
        {
            fs << cur->second->getID() << "\t" << cur->second->getLastMidName() + " " + cur->second->getFirstName() << "\t" << name_of_corp << "\t" << cur->second->getPosition() << "\t" << cur->second->getDateOfBirth()->getYear() << "-" << filling(cur->second->getDateOfBirth()->getMonth()) << "-" << filling(cur->second->getDateOfBirth()->getDay()) << "\t" << cur->second->getBirthPlace() << "\t" << cur->second->getEmail() << "\t" << cur->second->getPhoneNum() << "\t" << cur->second->getFirstDayAtWork()->getYear() << "-" << filling(cur->second->getFirstDayAtWork()->getMonth()) << "-" << filling(cur->second->getFirstDayAtWork()->getDay()) << "\t" << endl;
        }
    }
    std::map<std::string, Company *> *pointer_of_company_list = corp->getPointerofCompanyList();

    for (auto cur_company = pointer_of_company_list->begin(); cur_company != pointer_of_company_list->end(); ++cur_company)
    {
        std::string company_name = cur_company->first;
        Company *cp = cur_company->second;
        Director *d = cp->getDirector();
        if (d != nullptr)
        {
            fs << d->getID() << "\t" << d->getLastMidName() + " " + d->getFirstName() << "\t" << name_of_corp + "->" + company_name << "\t" << d->getPosition() << "\t" << d->getDateOfBirth()->getYear() << "-" << filling(d->getDateOfBirth()->getMonth()) << "-" << filling(d->getDateOfBirth()->getDay()) << "\t" << d->getBirthPlace() << "\t" << d->getEmail() << "\t" << d->getPhoneNum() << "\t" << d->getFirstDayAtWork()->getYear() << "-" << filling(d->getFirstDayAtWork()->getMonth()) << "-" << filling(d->getFirstDayAtWork()->getDay()) << "\t" << endl;
        }
        std::map<unsigned short, ViceDirector *> *vice_director_list_pointer = cp->getPointerOfViceDirector();

        for (auto cur_vice_director = vice_director_list_pointer->begin(); cur_vice_director != vice_director_list_pointer->end(); ++cur_vice_director)
        {
            if (cur_vice_director->second != nullptr)
            {
                fs << cur_vice_director->second->getID() << "\t" << cur_vice_director->second->getLastMidName() + " " + cur_vice_director->second->getFirstName() << "\t" << name_of_corp + "->" + company_name << "\t" << cur_vice_director->second->getPosition() << "\t" << cur_vice_director->second->getDateOfBirth()->getYear() << "-" << filling(cur_vice_director->second->getDateOfBirth()->getMonth()) << "-" << filling(cur_vice_director->second->getDateOfBirth()->getDay()) << "\t" << cur_vice_director->second->getBirthPlace() << "\t" << cur_vice_director->second->getEmail() << "\t" << cur_vice_director->second->getPhoneNum() << "\t" << cur_vice_director->second->getFirstDayAtWork()->getYear() << "-" << filling(cur_vice_director->second->getFirstDayAtWork()->getMonth()) << "-" << filling(cur_vice_director->second->getFirstDayAtWork()->getDay()) << "\t" << endl;
            }
        }
        std::map<std::string, Department *> *pointer_of_department_list = cp->getPointerOfDepartmentList();

        for (auto cur_department = pointer_of_department_list->begin(); cur_department != pointer_of_department_list->end(); ++cur_department)
        {
            std::string department_name = cur_department->first;
            Department *dept = cur_department->second;
            Manager *manager = dept->getManager();
            if (manager != nullptr)
            {
                fs << manager->getID() << "\t" << manager->getLastMidName() + " " + manager->getFirstName() << "\t" << name_of_corp + "->" + company_name + "->" + department_name << "\t" << manager->getPosition() << "\t" << manager->getDateOfBirth()->getYear() << "-" << filling(manager->getDateOfBirth()->getMonth()) << "-" << filling(manager->getDateOfBirth()->getDay()) << "\t" << manager->getBirthPlace() << "\t" << manager->getEmail() << "\t" << manager->getPhoneNum() << "\t" << manager->getFirstDayAtWork()->getYear() << "-" << filling(manager->getFirstDayAtWork()->getMonth()) << "-" << filling(manager->getFirstDayAtWork()->getDay()) << "\t" << endl;
            }
            std::map<unsigned short, DeputyManager *> *pointer_of_deputy_manager_list = dept->getDeputyManagerList();
            for (auto cur_deputy_manager = pointer_of_deputy_manager_list->begin(); cur_deputy_manager != pointer_of_deputy_manager_list->end(); ++cur_deputy_manager)
            {
                if (cur_deputy_manager->second != nullptr)
                {
                    fs << cur_deputy_manager->second->getID() << "\t" << cur_deputy_manager->second->getLastMidName() + " " + cur_deputy_manager->second->getFirstName() << "\t" << name_of_corp + "->" + company_name + "->" + department_name << "\t" << cur_deputy_manager->second->getPosition() << "\t" << cur_deputy_manager->second->getDateOfBirth()->getYear() << "-" << filling(cur_deputy_manager->second->getDateOfBirth()->getMonth()) << "-" << filling(cur_deputy_manager->second->getDateOfBirth()->getDay()) << "\t" << cur_deputy_manager->second->getBirthPlace() << "\t" << cur_deputy_manager->second->getEmail() << "\t" << cur_deputy_manager->second->getPhoneNum() << "\t" << cur_deputy_manager->second->getFirstDayAtWork()->getYear() << "-" << filling(cur_deputy_manager->second->getFirstDayAtWork()->getMonth()) << "-" << filling(cur_deputy_manager->second->getFirstDayAtWork()->getDay()) << "\t" << endl;
                }
            }
            std::map<unsigned short, Employee *> *pointer_of_employee_list = dept->getEmployeeList();
            for (auto cur_employee = pointer_of_employee_list->begin(); cur_employee != pointer_of_employee_list->end(); ++cur_employee)
            {
                if (cur_employee->second != nullptr)
                {
                    fs << cur_employee->second->getID() << "\t" << cur_employee->second->getLastMidName() + " " + cur_employee->second->getFirstName() << "\t" << name_of_corp + "->" + company_name + "->" + department_name << "\t" << cur_employee->second->getPosition() << "\t" << cur_employee->second->getDateOfBirth()->getYear() << "-" << filling(cur_employee->second->getDateOfBirth()->getMonth()) << "-" << filling(cur_employee->second->getDateOfBirth()->getDay()) << "\t" << cur_employee->second->getBirthPlace() << "\t" << cur_employee->second->getEmail() << "\t" << cur_employee->second->getPhoneNum() << "\t" << cur_employee->second->getFirstDayAtWork()->getYear() << "-" << filling(cur_employee->second->getFirstDayAtWork()->getMonth()) << "-" << filling(cur_employee->second->getFirstDayAtWork()->getDay()) << "\t" << endl;
                }
            }
        }
    }

    fs.close();
}

#endif