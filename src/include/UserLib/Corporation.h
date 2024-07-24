#ifndef CORPORATION_H
#define CORPORATION_H
#include <string>
#include <iostream>
#include "Human.h"
#include "../DSA/Queue.h"
#include "../DSA/HashMap.h"
#include "Company.h"
#include "../UserLib/Record.h"
class Corporation
{
private:
    std::string name;
    President *president = nullptr;
    std::map<unsigned short, VicePresident *> vice_president;
    std::map<std::string, Company *> company_list;

public:
    // CONSTRUCTORS
    Corporation()
    {
        this->vice_president = std::map<unsigned short, VicePresident *>();
        this->company_list = std::map<std::string, Company *>();
    };
    Corporation(std::string name, President *president, std::map<unsigned short, VicePresident *> vice_president, std::map<std::string, Company *> company);
    ~Corporation()
    {
        delete this->president;
        cout << "deleted president" << endl;
        for (auto iter = this->vice_president.begin(); iter != this->vice_president.end(); ++iter)
        {
            delete iter->second;
        }
        cout << "deleted vice president" << endl;
        for (auto iter = this->company_list.begin(); iter != this->company_list.end(); ++iter)
        {
            delete iter->second;
        }
        cout << "delete company list" << endl;
    };

    // OPERATORS
    friend ostream &operator<<(ostream &os, const Corporation *corporation)
    {
        os << "-----------------------------------------------------------" << std::endl;
        os << "Corporation: " + corporation->name << std::endl;
        if (corporation->president != nullptr)
        {
            os << "President: " + corporation->president->getFirstName() + " " + corporation->president->getLastMidName() << std::endl;
        }
        else
            os << "President: 0" << std::endl;
        os << "Vice Presidents: " << corporation->vice_president.size() << std::endl;
        for (auto current = corporation->vice_president.begin(); current != corporation->vice_president.end(); ++current)
        {
            if (current->second != nullptr)
            {
                os << current->second->getFullName() << std::endl;
            }
        }
        os << "----------------------------------------------------------- \n" << "Companies: ";
        for (auto current = corporation->company_list.begin(); current != corporation->company_list.end(); ++current)
        {
            if (current->second != nullptr)
            {
                os << current->second << std::endl;
            }
        }
        os << "-----------------------------------------------------------" << std::endl;

        return os;
    }
    bool operator==(const Corporation &otherCorporation)
    {
        return this->name == otherCorporation.name;
    }
    bool operator!=(const Corporation &otherCorporation)
    {
        return this->name != otherCorporation.name;
    }

    void displayUnit(Corporation *corporation)
    {
        string company;
        cout << "Enter company name:";
        cin >> company;
        for (auto current = corporation->company_list.begin(); current != corporation->company_list.end(); ++current)
        {
            if (current->second != nullptr) {
                if (company == current->second->getName()) {
                   cout << *current->second;
                }
            }
        }
    }

    // PROPERTIES
    std::string getName() const { return this->name; };
    President *getPresident()
    {
        return this->president;
    };
    std::map<unsigned short, VicePresident *> *getVicePresidentList() { return &(this->vice_president); };
    std::map<std::string, Company *> *getCompanyList()
    {
        return &(this->company_list);
    };
    std::map<unsigned short, VicePresident *> *getPointerofVicePresidentList()
    {
        return &(this->vice_president);
    };
    std::map<std::string, Company *> *getPointerofCompanyList()
    {
        return &(this->company_list);
    };
    void setName(std::string name) { this->name = name; };
    void setPresident(President *president)
    {
        this->president = president;
    };
    void setVicePresidentList(std::map<unsigned short, VicePresident *> vice_president_list)
    {
        this->vice_president = vice_president_list;
    };
    void setCompanyList(std::map<std::string, Company *> company_list)
    {
        this->company_list = company_list;
    };

    // METHODS
    void addVicePresident(VicePresident *vice_president) { this->vice_president.insert({vice_president->getID(), vice_president}); };
    void addCompany(Company *company)
    {
        this->company_list.insert({company->getName(), company});
    };
};

Corporation::Corporation(std::string name, President *president, std::map<unsigned short, VicePresident *> vice_president, std::map<std::string, Company *> company)
{
    this->name = name;

    // delete this->president; //! PREVENT MEMORY LEAK
    this->president = president;

    //! PREVENT MEMORY LEAK
    // delete this->vice_president;
    this->vice_president = vice_president;

    //! PREVENT MEMORY LEAK
    // delete this->company_list;
    this->company_list = company_list;
}

#endif
