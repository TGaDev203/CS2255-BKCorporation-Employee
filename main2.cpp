// #include <bits/stdc++.h>
#include "src/include/UserLib/Corporation.h"
#include "src/include/UserLib/ValidateRegex.h"
#include "src/include/DSA/HashMap.h"
#include "src/include/UserInteractions/MakeCorporation.h"

using namespace std;
void processing_information(string line);
void processing_the_department(string line);
HashMap<std::string, Corporation> list_of_corporation = HashMap<std::string, Corporation>();
int main()
{

    // Corporation corporation = makeCorporationFromFile("employees.txt");
    // cout << "Company size: " << corporation.getCompanyList().getAmountValueOccupy() << endl;
    // HashMap<std::string, Company> companies = corporation.getCompanyList();
    // Company company = companies.retrieve("BKEntertainment");
    // cout << "After retrieve: " << company.getDepartmentList() << endl;

    // HashMap<std::string, int> hashMap = HashMap<std::string, int>();
    // hashMap.assign("Alex", 100);
    // decltype(hashMap) hashMap2 = hashMap;
    // std::cout << hashMap2.retrieve("Alex") << std::endl;
    int num1 = 10;
    int num2 = 20;
    Queue<int*> nums = {&num1, &num2};
    std::cout << nums << std::endl;
}

// void processing_information(string line)
// {
//     regex pattern("(.[^;]+);\\s(.[^;]+);\\s(.[^;]+);\\s(.[^;]+);\\s(.[^;]+);\\s(.[^;]+);\\s(.[^;]+);\\s(.[^;]+);\\s(.[^;]+){0,1};\\s");
//     smatch list_of_data;
//     if (regex_search(line, list_of_data, pattern))
//     {
//         processing_the_department(list_of_data[3]);
//         std::cout << endl;
//     }
// }
// void processing_the_department(string line)
// {
//     if (validateCorporationNameFromFile(line))
//     {
//         regex pattern("([A-Z]{3}[a-z]+)");
//         smatch list_of_data;
//         if (regex_search(line, list_of_data, pattern))
//         {
//             // std::cout << "Corporation: " << list_of_data[1] << endl;

//             // CREATE CORPORATION
//             Corporation corporation = Corporation();
//             corporation.setName(list_of_data[1]);
//             list_of_corporation.assign(corporation.getName(), corporation);
//         }
//     }
//     else if (validateCompanyNameFromFile(line))
//     {
//         regex pattern("([A-Z]{3}[a-z]+)->([A-Z]{3}[a-z]+)");
//         smatch list_of_data;
//         if (regex_search(line, list_of_data, pattern))
//         {
//             // CREATE CORPORATION
//             // std::cout << "Corporation: " << list_of_data[1] << endl;

//             // CREATE COMPANY
//             // std::cout << "Company: " << list_of_data[2] << endl;
//             Company company = Company(list_of_data[2]);
//             list_of_corporation[list_of_data[1]].addCompany(company);
//         }
//     }
//     else if (validateDepartmentNameFromFile(line))
//     {
//         regex pattern("([A-Z]{3}[a-z]+)->([A-Z]{3}[a-z]+)->([A-Z]{3}[a-z]+)");
//         smatch list_of_data;
//         if (regex_search(line, list_of_data, pattern))
//         {
//             // std::cout << "Corporation: " << list_of_data[1] << endl;
//             // std::cout << "Company: " << list_of_data[2] << endl;
//             // std::cout << "Department: " << list_of_data[3] << endl;

//             // CREATE CORPORATION
//             Company company = Company();
//             company.setName(list_of_data[2]);

//             Department department = Department();
//             department.setName(list_of_data[3]);

//             company.addDepartment(department);
//             list_of_corporation[list_of_data[1]].addCompany(company);
//         }
//     }
// }