# BKCorporation Employee Management System

---

## I. Project Overview

The BKCorporation Employee Management System is designed to manage the hierarchical structure of BKCorporation, including its subsidiaries and departments. The system handles employee information and provides various functionalities to manage and view employee details effectively.

---

## II. Structure

The organizational structure of BKCorporation is as follows:
- Chairman: Head of the corporation.
- Vice Chairmen: Under the Chairman.
- Subsidiaries: Including BKEntertainment, BKFood, BKTech, etc.
  - Director: Head of each subsidiary.
  - Deputy Directors: Assist the Director.
- Departments: Within each subsidiary.
  - Head of Department: Manages the department.
  - Deputy Head of Department: Assists the Head.
- Employees: Each department can have an unlimited number of employees.

---

## III. Features

1. Display Basic Information about BKCorporation:
   - View the Chairman's name.
   - List of subsidiaries with their Directors and Deputy Directors.
   - List of departments with their Heads and Deputy Heads.
   - Total number of employees in the corporation.

2. Search Employee Information:
   - Enter a search string to find employees by surname and given name.
   - Display basic information about the employees matching the search criteria.

3. Display Employee Work Status:
   - Input an employee ID to view their work status for the current month.
   - Calculate the number of hours the employee was late or left early (rounded up to the nearest hour).
   - Exclude weekends and public holidays from the calculations.

4. Display Information of a Unit:
   - Enter the name of a unit (subsidiary or department) to list all employees within that unit.

5. Add New Employee:
   - Add a new employee to the system with all required details.

6. Update Employee Information:
   - Update the basic information of an existing employee.

7. Exit Program:
   - Exit the program.

---

## III. File Format

The employee information is stored in a text file with the following format:

Employee ID
Surname Given Name
Unit
Position
Date of Birth
Hometown
Address
Email
Phone Number
Start Date
Work Date, Time In, Time Out

Example:

1
Trần Văn
A
BKCorporation
Chairman
10/01/1980
Hà Nội
Số 1, Tạ Quang Bửu
tranvana@gmail.com
0123456789
22/02/2016
22/02/2016,7:49,18:00
23/02/2016,7:51,18:05
24/02/2016,7:45,12:30
2
Nguyễn Thị
B
BKEntertainment
Employee

---

## IV. How to Use

1. Run the Program
   - Compile the program using a suitable C++ compiler.
   - Execute the compiled program to start the system.

2. Navigate the Menu
   - Follow the prompts to perform various tasks such as searching for employees, displaying work status, or updating information.

3. Provide Input
   - Enter the required data as prompted by the system.

4. Exit the System
   - Choose the option to exit the program when finished.

---

## V. Contributing

This project is a first-time effort to develop a command-line interface (CLI) application for managing employee data within BKCorporation. The main goals were to create a functional CLI tool that handles employee records, including searching, updating, and tracking work status.

**My Contributions**

1. Data Handling: Created methods for reading from and writing to text files to manage employee records.
2. Validation Functions: Implemented functions to validate employee data and ensure data integrity.
3. Main Logic: Developed the main application logic to handle user interactions and execute core functionalities.
4. Testing: Conducted basic testing to ensure the functionality and reliability of the system.
