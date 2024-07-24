#ifndef VALIDATEREGEX_H
#define VALIDATEREGEX_H

#include <string>
#include <string>
#include <regex>
#include <tuple>

//* VALIDATE HUMAN ATTRIBUTE FUNCTIONS
bool validateNum(std::string ID);
bool validateName(std::string name);
bool validateCorporationPosition(std::string position_name);
bool validateCompanyPosition(std::string position_name);
bool validateDepartmentPosition(std::string position_name);
bool validateDate(std::string date);
bool validateTime(std::string time);
bool validatePlace(std::string birth_place);
bool validateEmail(std::string email);
bool validatePhoneNum(std::string phone_num);

//* VALIDATE CORPORATION NAME, COMPANY NAME, DEPARTMENT NAME FROM FILE
bool validateCorporationNameFromFile(std::string department_name);
bool validateCompanyNameFromFile(std::string company_name);
bool validateDepartmentNameFromFile(std::string department_name);

//* VALIDATE CORPORATION NAME, COMPANY NAME, DEPARTMENT NAME FROM TERMINAL
bool validateNameFromTerminal(std::string name);

//? VALIDATE OTHER UTILITIES
bool validateFileTxt(std::string filename);

//! EXTRACT DATA
std::tuple<std::string, std::string> extractName(std::string full_name);
std::tuple<std::string> extractCorporationFromFile(std::string corporation_name);
std::tuple<std::string, std::string> extractCompanyFromFile(std::string company_name);
std::tuple<std::string, std::string, std::string> extractDepartmentFromFile(std::string department_name);

//-------------------------------------------------------------------

//* VALIDATE HUMAN ATTRIBUTE FUNCTIONS
bool validateNum(std::string ID)
{
    return std::regex_match(ID, std::regex("([0-9])+"));
}

bool validateName(std::string name)
{
    return (std::regex_match(name, std::regex("(([A-Z]{1}[a-z]+)\\s?){1,}")));
}

bool validatePosition(std::string position_name)
{
    return std::regex_match(position_name, std::regex("(([A-Z]{1}[a-z]+)?){1,}"));
}

bool validateDate(std::string date)
{
    std::regex date_pattern("([0]?[1-9]|[1|2][0-9]|[3][0|1])[./-]([0]?[1-9]|[1][0-2])[./-]([0-9]{4}|[0-9]{2})");
    return std::regex_match(date, date_pattern);
}

bool validateTime(std::string time)
{
    std::regex time_pattern("^([0-9]|0[0-9]|1[0-9]|2[0-3]):[0-5][0-9]$");
    return std::regex_match(time, time_pattern);
}

bool validatePlace(std::string place)
{
    std::regex place_pattern("(([A-Z]{1}[a-z]+)\\s?){1,}");
    return std::regex_match(place, place_pattern);
}

bool validateCorporationPosition(std::string position_name)
{
    bool statement1 = position_name == "President";
    bool statement2 = position_name == "Vice President";
    return statement1 || statement2;
}

bool validateCompanyPosition(std::string position_name)
{
    bool statement1 = position_name == "Director";
    bool statement2 = position_name == "Vice Director";
    return statement1 || statement2;
}

bool validateDepartmentPosition(std::string position_name)
{
    bool statement1 = position_name == "Manager";
    bool statement2 = position_name == "Deputy Manager";
    bool statement3 = position_name == "Employee";
    return statement1 || statement2 || statement3;
}

bool validateEmail(std::string email)
{
    std::regex email_pattern("[a-z0-9._%+-]+@[a-z0-9.-]+\\.[a-z]{2,4}");
    return std::regex_match(email, email_pattern);
}

bool validatePhoneNum(std::string phone_num)
{
    std::regex phone_num_pattern("0[0-9]{9,10}");
    return std::regex_match(phone_num, phone_num_pattern);
}

// * VALIDATE CORPORATION NAME, COMPANY NAME, DEPARTMENT NAME FROM FILE

// EXTRACT CORPORATION, COMPANY AND DEPARTMENT FROM FILE!!!!
bool validateCorporationNameFromFile(std::string corporation_name)
{
    std::regex corporation_pattern("([A-Z]{3}[a-z]+)");
    return std::regex_match(corporation_name, corporation_pattern);
}
std::tuple<std::string> extractCorporationFromFile(std::string corporation_name)
{
    std::tuple<std::string> result;
    std::regex corporation_pattern("([A-Z]{3}[a-z]+)");
    std::smatch list_of_data;
    if (std::regex_search(corporation_name, list_of_data, corporation_pattern))
    {
        // result = make_tuple(list_of_data[1]);
        return std::tuple<std::string>(list_of_data[1]);
    }
    return std::tuple<std::string>("Corporation");
}
bool validateCompanyNameFromFile(std::string company_name)
{
    std::regex company_pattern("([A-Z]{3}[a-z]+)->([A-Z]{3}[a-z]+)");
    return std::regex_match(company_name, company_pattern);
}
std::tuple<std::string, std::string> extractCompanyFromFile(std::string company_name)
{
    std::tuple<std::string, std::string> result;
    std::regex corporation_pattern("([A-Z]{3}[a-z]+)->([A-Z]{3}[a-z]+)");
    std::smatch list_of_data;
    if (std::regex_search(company_name, list_of_data, corporation_pattern))
    {
        // result = make_tuple(list_of_data[1], list_of_data[2]);
        return std::tuple<std::string, std::string>(list_of_data[1], list_of_data[2]);
    }
    return std::tuple<std::string, std::string>("Company", "Company");
}
bool validateDepartmentNameFromFile(std::string department_name)
{
    std::regex department_pattern("([A-Z]{3}[a-z]+)->([A-Z]{3}[a-z]+)->([A-Z]{3}[a-z]+)");
    return std::regex_match(department_name, department_pattern);
}
std::tuple<std::string, std::string, std::string> extractDepartmentFromFile(std::string department_name)
{
    std::tuple<std::string, std::string, std::string> result;
    std::regex department_pattern("([A-Z]{3}[a-z]+)->([A-Z]{3}[a-z]+)->([A-Z]{3}[a-z]+)");
    std::smatch list_of_data;
    if (std::regex_search(department_name, list_of_data, department_pattern))
    {
        return std::tuple<std::string, std::string, std::string>(list_of_data[1], list_of_data[2], list_of_data[3]);
    }
    return std::tuple<std::string, std::string, std::string>("Department", "Department", "Department");
}

std::tuple<std::string, std::string> extractName(std::string full_name)
{    
    // WORK WITH NAME WITH 5 WORDS
    std::regex name_pattern("([A-Z]{1}[a-z]+)\\s(([A-Z]{1}[a-z]*)\\s?)+");
    std::smatch list_of_data;
    if (std::regex_search(full_name,list_of_data, name_pattern))
    {
        return {list_of_data[1], list_of_data[2]}; 
    }
    return {"Unknown", "Unknown"};
}

// * VALIDATE CORPORATION NAME, COMPANY NAME, DEPARTMENT NAME FROM TERMINAL
bool validateNameFromTerminal(std::string name)
{
    std::regex name_pattern("(?:([a-zA-Z0-9]+)\\s?)+");
    return std::regex_match(name, name_pattern);
}

//? VALIDATE OTHER UTILITIES
bool validateFileTxt(std::string filename)
{
    std::regex filename_pattern("^[^\\s](.*).txt$");
    return std::regex_match(filename, filename_pattern);
}

//? VALIDATE ID 
bool isIDMatch(const unsigned short human_ID, const unsigned short ID_to_find)
{
    return human_ID == ID_to_find;
}
#endif