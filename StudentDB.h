/*
 * StudentDB.h
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */
#include<map>
#include<memory>
#ifndef STUDENTDB_H_
#define STUDENTDB_H_

#include "Course.h"
#include "Student.h"

/**
 * @brief The StudentDB class represents a database of students and courses.
 */
class StudentDB
{
public:
    /**
     * @brief Default constructor: Initializes a StudentDB object.
     */
	StudentDB();
    /**
     * @brief Destructor: Cleans up resources associated with
     *  the StudentDB object.
     */
	virtual ~StudentDB();
    /**
     * @brief Getter for the map of courses in the database.
     * @return Reference to the map of courses.
     */
	std::map<int, std::unique_ptr<const Course> >& getCourses() ;

    /**
     * @brief Getter for the map of students in the database.
     * @return Reference to the map of students.
     */
	std::map<int, Student>& getStudents() ;

    /**
     * @brief Variable representing the next available matrikel
     *  number in the database.
     */
	unsigned int nextMatrikelNumber;
    /**
     * @brief Method to write the database to an output stream.
     * @param out Reference to the output stream.
     */
    void write(std::ostream& out) const;
    /**
     * @brief Method to read the database from an input stream.
     * @param in Reference to the input stream.
     */
    void read(std::istream& in);
    /**
     * @brief Method to generate student data from a server.
     * @param numStudents Number of students to generate.
     * communicates with http server using socket receives
     * data of students
     *
     */
    void generateFromServer(int numStudents);

private:
    /**
     * @brief Map of students in the database, where the key
     *  is the matrikel number.
     */
	std::map<int, Student> students;
    /**
     * @brief Map of courses in the database, where the
     *  key is the course key.
     */
	std::map<int, std::unique_ptr<const Course>> courses;
    /**
     * @brief Method to send a command to the server.
     * @param command The command to be sent.
     *  starts and closes connections with commands(generate and quit)
     */

	void sendCommand(const std::string& command);
};

#endif /* STUDENTDB_H_ */
