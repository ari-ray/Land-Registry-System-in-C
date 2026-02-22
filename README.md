# Land-Registry-System-in-C
A simple yet practical C program to manage land records. This project demonstrates structured data handling, file I/O and clean coding practices in a real world scenario.

## Features 
- Add New Records: Input new land records with details like khatian number (Bangladesh system), owner, plot number, area, land type and last tax payment year.
- Search Records: Look up records by khatian number.
- Display All Records: View all stored land records.
- Defaulter Report: Generate a list of landowners who haven't paid taxes  for the current year.
- Save & Load: Persist records in a text file for future use.

## How it Works
- Structured Data: Uses a "struct" to represent a land record
- Safe Input: Strings are read safely to prevent buffer overflows
- File I/O: Saves and loads records to/from a file, including total record count
- Dynamic Queries: Supports searching by khatian number and generating defaulter lists.

## How to Run
- Open a terminal in the folder where landregistry.c is located
- Compile the program:
  ```bash
  gcc landregistry.c -o LandRecordSystem
- Run the executable:
  ```bash
  ./LandRecordSystem
- Follow the interactive menu to add, search, display or save records.

## Skills Demonstrated
- Structured programming with "struct"s
- Safe user input handling
- File input/ouput in C
- Array manipulation and search algorithms
- Practical problem-solving in C

