#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <map>
#include "Human.h"
#include "../DSA/HashMap.h"
class Department
{
private:
    std::string name = "";
    // Manager: Human
    Manager *manager = nullptr;
    // Employee: Human
    std::map<unsigned short, Employee *> employee_list;
    std::map<unsigned short, DeputyManager *> deputy_manager_list;

public:
    Department()
    {
        this->employee_list = std::map<unsigned short, Employee *>();
        this->deputy_manager_list = std::map<unsigned short, DeputyManager *>();
    }
    ~Department()
    {
        delete this->manager;
        cout << "deleted manager" << endl;
        for (auto iter = this->employee_list.begin(); iter != this->employee_list.end(); ++iter)
        {
            delete iter->second;
        }
        cout << "deleted employee" << endl;
        for (auto iter = this->deputy_manager_list.begin(); iter != this->deputy_manager_list.end(); iter++)
        {
            delete iter->second;
        }
        cout << "delete deputy manager list" << endl;
    };
    Department(std::string name, Manager *manager, std::map<unsigned short, DeputyManager *> deputy_manager_list, std::map<unsigned short, Employee *> employee_list);

    // PROPERTIES
    unsigned short getMemberNums() const
    {
        return 1 + this->deputy_manager_list.size() + this->employee_list.size();
    };
    std::map<unsigned short, DeputyManager *> *getDeputyManagerList() { return &(this->deputy_manager_list); };
    std::map<unsigned short, Employee *> *getEmployeeList()
    {
        return &(this->employee_list);
    };
    Manager *getManager()
    {
        return this->manager;
    };
    std::string getName() const { return this->name; };

    // SETTERS
    void setName(std::string name) { this->name = name; };
    void setDeputyManagerList(std::map<unsigned short, DeputyManager *> deputy_manager_list)
    {
        this->deputy_manager_list = deputy_manager_list;
    };
    void setManager(Manager *manager)
    {
        this->manager = manager;
    };
    void setEmployeeList(std::map<unsigned short, Employee *> employee_list)
    {
        this->employee_list = employee_list;
    };

    // For stream....
    friend std::ostream &operator<<(std::ostream &os, const Department &department)
    {
        os << "-----------------------------------------------------------" << std::endl;
        os << "Department: " + department.name << std::endl;
        if (department.manager != nullptr) {
            os << "Manager: " << department.manager->getFullName() << std::endl;
        }
        os << "Deputy Managers: ";
        for (auto current = department.deputy_manager_list.begin(); current != department.deputy_manager_list.end(); ++current)
        {
            os << current->second->getFullName() << ", ";
        }
        os << std::endl;

        os << "Employees: " << department.employee_list.size() << std::endl;
        for (auto current = department.employee_list.begin(); current != department.employee_list.end(); ++current)
        {
            if (current->second != nullptr)
            {
                os << current->second->getFullName() << std::endl;
            }
        }
        os << std::endl;
        os << "-----------------------------------------------------------" << std::endl;

        return os;
    };

    friend std::ostream &operator<<(std::ostream &os, Department *department)
    {
        os << "-----------------------------------------------------------" << std::endl;
        os << "Department: " + department->name << std::endl;
        if (department->manager != nullptr)
        {
            os << "Manager: " + department->manager->getFullName() << std::endl;
        }
        else
            os << "Manager: 0" << std::endl;

        os << "Deputy Managers: " <<  department->deputy_manager_list.size() << std::endl;
        for (auto current = department->deputy_manager_list.begin(); current != department->deputy_manager_list.end(); ++current)
        {
            if (current->second != nullptr)
            {
                os << current->second->getFullName() << std::endl;
            }
        }       
        return os;
    };

    bool operator==(const Department &otherDepartment)
    {
        return this->name == otherDepartment.name;
    }
    bool operator!=(const Department &otherDepartment)
    {
        return this->name != otherDepartment.name;
    }
    // Add some stuffs
    void addEmployee(Employee *employee)
    {
        this->employee_list.insert({employee->getID(), employee});
    };
    // DeputyManager: Human
    void addDeputyManager(DeputyManager *deputy_manager)
    {
        this->deputy_manager_list.insert({deputy_manager->getID(), deputy_manager});
    };
};

Department::Department(std::string name, Manager *manager, std::map<unsigned short, DeputyManager *> deputy_manager_list, std::map<unsigned short, Employee *> employee_list)
{
    this->name = name;

    this->manager = manager;

    this->deputy_manager_list = deputy_manager_list;

    this->employee_list = employee_list;
};


#endif