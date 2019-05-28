# Birzeit University
## Department of Computer Science
## COMP2321
## First Semester – Fall 2016/2017

This project is based on what you have learnt in the lecture room
about Linked List. In this project, you will implement a system to
accept new students at a university based on an **admission mark**
that is computed based on the Tawjihi, High-School, and Placement
Test grades.

Your program should assign new registered students to their majors
based on their **admission marks**. Each input student should be
assigned to one major only. The student may not be assigned to any
major if (s)he didn’t pass achieve the required **admission marks** of
majors for all faculties. Each major has a unique non-overlapping
range of averages. For example, Medicine [97-99], Engineering [90-
96], Science [85-89], and so on.

Your program should read two input files. The containing the Name
of students, Tawjihi, High-school, and Placement test grade.

The second file should contain the acceptance criteria by the
university that is:

- the Tawjihi grade’s rate in the **admission mark**
- school grade’s rate in the **admission mark**
- Placement test grade’s in the **admission mark**
- Number of faculties
- A list of faculties and the range of their averages

Your application should have the options of: 
1. Read the files
2. Accept new students
3. Print (on the screen) all accepted students based on their faculties
4. Print (on the screen) rejected students;
5. Write accepted and not accepted students to files
6. Quit


Your test files should contain at least 5 faculties and at least 30
students.
