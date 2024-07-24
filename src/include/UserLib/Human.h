#ifndef HUMAN_H
#define HUMAN_H

#include <string>
#include "../DSA/Queue.h"

#include "Date.h"
#include "Record.h"

class Human
{
protected:
    unsigned short ID = 0;
    std::string last_mid_name = " ";
    std::string first_name = " ";
    std::string work_place = "";
    std::string position = "";
    Date *date_of_birth = nullptr;
    std::string birth_place = "";
    std::string email = "";
    std::string phone_num = "";
    Queue<Record *> days_work;
    Date *first_day_at_work = nullptr;

public:
    Human()
    {
        this->days_work = Queue<Record *>();
        this->ID = 0;
        this->position = "Human";
    };
    Human(unsigned short ID, std::string last_mid_name, std::string first_name, std::string work_place, std::string position, std::string dob, std::string birth_place, std::string email, std::string phone_num, std::string first_day_at_work);

    ~Human()
    {
        // CLEAN UP MEMORY
        delete this->date_of_birth;

        delete this->first_day_at_work;

        for (auto iter = days_work.begin(); iter != days_work.end(); ++iter)
        {
            Record *record_to_remove = (*iter).getValue();
            delete record_to_remove;
        }
        cout << "delete everything...." << endl;
    };

    friend std::ostream &operator<<(std::ostream &os, const Human &human)
    {
        os << "----------------------------------------------------------" << std::endl;
        os << "ID: " << human.ID << "\n";
        os << "Last-mid name: " << human.last_mid_name << "\n";
        os << "First name: " << human.first_name << "\n";
        os << "Workplace: " << human.work_place << "\n";
        os << "Position: " << human.position << "\n";
        os << "Date of birth: " << human.date_of_birth << "\n";
        os << "Birth place: " << human.birth_place << "\n";
        os << "Email: " << human.email << "\n";
        os << "Phone number: " << human.phone_num << "\n";
        os << "First day at work: " << human.first_day_at_work << "\n";
        for (auto current = human.days_work.begin(); current != human.days_work.end(); ++current)
        {
            Record *record = (*current).getValue();
            os << *record << std::endl;
        }
        os << "----------------------------------------------------------" << std::endl;
        return os;
    };

    friend std::ostream &operator<<(std::ostream &os, const Human *human)
    {
        os << "----------------------------------------------------------" << std::endl;
        if (human != nullptr)
        {
            os << "ID: " << human->ID << "\n";
            os << "Last-mid name: " << human->last_mid_name << "\n";
            os << "First name: " << human->first_name << "\n";
            os << "Workplace: " << human->work_place << "\n";
            os << "Position: " << human->position << "\n";

            if (human->date_of_birth != nullptr)
            {
                os << "Date of birth: " << human->date_of_birth << "\n";
            }
            else
                os << "Date of birth: " << std::endl;

            os << "Birth place: " << human->birth_place << "\n";
            os << "Email: " << human->email << "\n";
            os << "Phone number: " << human->phone_num << "\n";

            if (human->first_day_at_work != nullptr)
            {
                os << "First day at work: " << human->first_day_at_work << "\n";
            }
            else
                os << "First day at work: " << std::endl;

            os << "Days Worked: " << std::endl;
            for (auto current = human->days_work.begin(); current != human->days_work.end(); ++current)
            {
                Record *record = (*current).getValue();
                if (record != nullptr)
                {
                    os << record << std::endl;
                }
            }
        }
        else
            os << "Unknown Person" << std::endl;
        os << "----------------------------------------------------------" << std::endl;
        return os;
    };
    friend std::ostream &operator>>(const Human *human, std::ostream &os)
    {
        os << human->ID << "; ";
        os << human->last_mid_name << "; ";
        os << human->first_name << "; ";
        os << human->work_place << "; ";

        os << human->position << "; ";
        if (human->date_of_birth != nullptr)
        {
            os << human->date_of_birth << "; ";
        }
        else
        {
            os << "; ";
        }
        os << human->birth_place << "; ";
        os << human->email << "; ";
        os << human->phone_num << "; ";
        if (human->first_day_at_work != nullptr)
        {
            os << human->first_day_at_work << "; ";
        }
        else
        {
            os << "; ";
        }

        return os;
    }
    void setRecord(Queue<Record *> record);
    // PROPERTIES
    unsigned short getID() const { return this->ID; };
    std::string getLastMidName() const { return this->last_mid_name; };
    std::string getFirstName() const { return this->first_name; };
    std::string getFullName() const { return this->first_name + " " + this->last_mid_name; };
    std::string getWorkPlace() const { return this->work_place; };
    std::string getPosition() const { return this->position; };
    Date *getDateOfBirth() const { return this->date_of_birth; };
    std::string getBirthPlace() const { return this->birth_place; };
    std::string getEmail() const { return this->email; };
    std::string getPhoneNum() const { return this->phone_num; };
    Date *getFirstDayAtWork() { return this->first_day_at_work; };
    Queue<Record *> *getPointerDaysWork() { return &(this->days_work); };

    void setID(const unsigned short ID) { this->ID = ID; };
    void setLastMidName(const std::string last_mid_name) { this->last_mid_name = last_mid_name; };
    void setFirstName(const std::string first_name) { this->first_name = first_name; };
    void setWorkPlace(const std::string work_place) { this->work_place = work_place; };
    void setPosition(const std::string position) { this->position = position; };
    void setDateOfBirth(Date *date_of_birth)
    {
        delete this->date_of_birth; //! PREVENT MEMORY LEAK
        this->date_of_birth = date_of_birth;
    };
    void setBirthPlace(const std::string birth_place) { this->birth_place = birth_place; };
    void setEmail(const std::string email) { this->email = email; };
    void setPhoneNum(const std::string phone_num) { this->phone_num = phone_num; };
    void setFirstDayAtWork(Date *first_day_at_work)
    {
        delete this->first_day_at_work; //! PREVENT MEMORY LEAK
        this->first_day_at_work = first_day_at_work;
    };
    Queue<Record *> *getDaysWork() { return &(this->days_work); };
    void addRecord(Record *record)
    {
        this->days_work.Enqueue(record);
    };

    // OPERATORS
    bool operator==(const Human &otherHuman)
    {
        bool a1 = this->first_name == otherHuman.first_name;
        bool a2 = this->last_mid_name == otherHuman.last_mid_name;
        bool a3 = this->ID == otherHuman.ID;
        bool a4 = this->birth_place == otherHuman.birth_place;
        bool a5 = this->date_of_birth == otherHuman.date_of_birth;
        bool a6 = this->email == otherHuman.email;
        return a1 && a2 && a3 && a4 && a5 && a6;
    }
    bool operator!=(const Human &otherHuman)
    {
        bool a1 = this->first_name == otherHuman.first_name;
        bool a2 = this->last_mid_name == otherHuman.last_mid_name;
        bool a3 = this->ID == otherHuman.ID;
        bool a4 = this->birth_place == otherHuman.birth_place;
        bool a5 = this->date_of_birth == otherHuman.date_of_birth;
        bool a6 = this->email == otherHuman.email;
        return !a1 || !a2 || !a3 || !a4 || !a5 || !a6;
    };
};

Human::Human(unsigned short ID, std::string last_mid_name, std::string first_name, std::string work_place, std::string position, std::string dob, std::string birth_place, std::string email, std::string phone_num, std::string first_day_at_work)
{
    this->ID = ID;
    this->last_mid_name = last_mid_name;
    this->first_name = first_name;
    this->work_place = work_place;
    this->position = position;

    //! PREVENT MEMORY LEAK
    delete this->date_of_birth;
    this->date_of_birth = new Date(dob);

    this->birth_place = birth_place;
    this->email = email;
    this->phone_num = phone_num;

    //! PREVENT MEMORY LEAK
    delete this->first_day_at_work;
    this->first_day_at_work = new Date(first_day_at_work);
}
void Human::setRecord(Queue<Record *> record)
{
    //! PREVENT MEMORY LEAK
    this->days_work.Clear();

    this->days_work = record;
}

class Employee : public Human
{
public:
    Employee() : Human()
    {
        this->ID = 0;
        this->position = "Employee";
    };
    Employee(unsigned short ID, std::string last_mid_name, std::string first_name, std::string department, std::string position, std::string dob, std::string birth_place, std::string email, std::string phone_num, std::string first_day_at_work) : Human(ID, last_mid_name, first_name, department, "Employee", dob, birth_place, email, phone_num, first_day_at_work){};
};
class DeputyManager : public Human
{
public:
    DeputyManager() : Human()
    {
        this->ID = 0;
        this->position = "Deputy Manager";
    };
    DeputyManager(unsigned short ID, std::string last_mid_name, std::string first_name, std::string department, std::string position, std::string dob, std::string birth_place, std::string email, std::string phone_num, std::string first_day_at_work) : Human(ID, last_mid_name, first_name, department, "Deputy Manager", dob, birth_place, email, phone_num, first_day_at_work){};
};
class Manager : public Human
{
public:
    Manager() : Human()
    {
        this->ID = 0;
        this->position = "Manager";
    };
    Manager(unsigned short ID, std::string last_mid_name, std::string first_name, std::string department, std::string position, std::string dob, std::string birth_place, std::string email, std::string phone_num, std::string first_day_at_work) : Human(ID, last_mid_name, first_name, department, "Manager", dob, birth_place, email, phone_num, first_day_at_work){};
};
class ViceDirector : public Human
{
public:
    ViceDirector() : Human()
    {
        this->ID = 0;
        this->position = "Vice Director";
    };
    ViceDirector(unsigned short ID, std::string last_mid_name, std::string first_name, std::string department, std::string position, std::string dob, std::string birth_place, std::string email, std::string phone_num, std::string first_day_at_work) : Human(ID, last_mid_name, first_name, department, "Vice Director", dob, birth_place, email, phone_num, first_day_at_work){};
};
class Director : public Human
{
public:
    Director() : Human()
    {
        this->ID = 0;
        this->position = "Director";
    };
    Director(unsigned short ID, std::string last_mid_name, std::string first_name, std::string department, std::string position, std::string dob, std::string birth_place, std::string email, std::string phone_num, std::string first_day_at_work) : Human(ID, last_mid_name, first_name, department, "Director", dob, birth_place, email, phone_num, first_day_at_work){};
};
class VicePresident : public Human
{
public:
    VicePresident() : Human()
    {
        this->ID = 0;
        this->position = "Vice President";
    };
    VicePresident(unsigned short ID, std::string last_mid_name, std::string first_name, std::string department, std::string position, std::string dob, std::string birth_place, std::string email, std::string phone_num, std::string first_day_at_work) : Human(ID, last_mid_name, first_name, department, "Vice President", dob, birth_place, email, phone_num, first_day_at_work){};
};
class President : public Human
{
public:
    President() : Human()
    {
        this->ID = 0;
        this->position = "President";
    };
    President(unsigned short ID, std::string last_mid_name, std::string first_name, std::string department, std::string position, std::string dob, std::string birth_place, std::string email, std::string phone_num, std::string first_day_at_work) : Human(ID, last_mid_name, first_name, department, "President", dob, birth_place, email, phone_num, first_day_at_work){};
};

#endif