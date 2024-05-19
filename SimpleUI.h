/*
 * SimpleUI.h
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

#ifndef SIMPLEUI_H_
#define SIMPLEUI_H_

#include "StudentDB.h"

/**
 * @brief The SimpleUI class represents a simple user interface for
 * interacting with a Student Database.
 */
class SimpleUI
{
public:
    /**
     * @brief Parameterized constructor: Initializes a SimpleUI object
     *  with a reference to a StudentDB.
     * @param StudentDB Reference to the StudentDB to interact with.
     */
	SimpleUI(StudentDB& StudentDB );
    /**
     * @brief Method to run the SimpleUI and display the main menu.
     */
	void run();
	virtual ~SimpleUI();
    /**
     * @brief Method to display the main menu options.
     */
    void displayMenu() const;
    /**
     * @brief Method to process user input.
     */
    void processUserInput();
    /**
     * @brief Method to execute a command based on user input.
     * @param choice The user's choice.
     */
    void executeCommand(int choice);
    /**
     * @brief Method to execute read and write commands on file.
     */
    void execute_RW_Commands();
    /**
     * @brief Method to check if a string contains a substring.
     * @param str The main string.
     * @param substr The substring to check for.
     * @return True if str contains substr, false otherwise.
     */
    bool containsSubstring(const std::string& str,
    		const std::string& substr) const;
    /**
     * @brief Method to generate students from a server.
     * call appropriate method on studentDB to connect and read from server
     */
    void generateStudentsFromServer();

private:
    /**
     * @brief Reference to the StudentDB to interact with.
     */
    StudentDB& database;
    /**
     * @brief Helper method to add a new course to the student
     *  database by asking inputs from user.
     */
    void addNewCourse();
    /**
     * @brief Helper method to list all courses in the student database.
     */
    void listCourses();
    /**
     * @brief Helper method to add a new student to the
     * database by asking inputs from user.
     */
    void addNewStudent();
    /**
     * @brief Helper method to add an enrollment to a student.
     * checks for matrikulation number and coursekey
     * and queries for its members
     */
    void addEnrollment();
    /**
     * @brief Helper method to print student details.
     * prints with the address and course enrolled
     */
    void printStudent();
    /**
     * @brief Helper method to search for a student in the database
     * queries search string from user and searches in database .
     */
    void searchStudent();
    /**
     * @brief Helper method to update student information.
     *  Queries the user for a matrikel number
     *  Lists the properties to modify
     *  including changing of grade or deleting enrollments
     */
    void updateStudent();

    /**
     * @brief  method to write data to a file.
     * @param fileName The name of the file.
     * @param database Reference to the StudentDB.
     */

    void writeToFile(const std::string& fileName, StudentDB& database);

    /**
     * @brief method to read data from a file.
     * @param fileName The name of the file.
     * @param database Reference to the StudentDB.
     */
    void readFromFile(const std::string& fileName, StudentDB& database);

};

#endif /* SIMPLEUI_H_ */
