/*
 * Student.h
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include "Poco/Data/Date.h"
#include "Poco/Data/Time.h"

#include <boost/asio.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include<vector>
#include<string>
#include "Enrollment.h"
#include "Adress.h"
#include <cstdlib>
#include <fstream>

using boost::asio::ip::tcp;

/**
 * @brief The Student class represents a student with personal
 * and enrollment details.
 */
class Student
{
public:
    /**
     * @brief Parameterized constructor: Initializes a Student
     * object with personal details and address.
     * @param firstName ,@param lastName ,@param dateOfBirth
     * @param Adress Reference to the Address object representing
     * the student's address.
     */
	Student(const std::string& firstName, const std::string& lastName,
			const Poco::Data::Date& dateOfBirth,  Adress& Adress);
	Student();
	virtual ~Student();

	/*
	 * getters and setters of all the data members of the student
	 */
	const Poco::Data::Date& getDateofBirth() const;
	void setDateofBirth(const Poco::Data::Date &dateofBirth);
	const std::string& getFirstName() const;
	void setFirstName(const std::string &firstName);
	const std::string& getLastName() const;
	void setLastName(const std::string &lastName);
	unsigned int getMatrikelNumber() const;
	void setMatrikelNumber(unsigned int matrikelNumber);
	 Adress& getAdress() ;
	    /**
	     * @brief Getter for the enrollments of the student.
	     * @return Vector of Enrollment objects representing
	     *  the student's enrollments.
	     */
	const std::vector<Enrollment>& getEnrollments() const;

    /**
     * @brief Method to add an enrollment to the student's record.
     * @param enrollment The Enrollment object to be added.
     */
	void addEnrollments(const Enrollment& enrollment);
    /**
     * @brief Method to update the address of the student.
     * @param newStreet The new street information.
     * @param newPostalCode The new postal code.
     * @param newCityName The new city name.
     * @param newAdditionalInfo The new additional information.
     */
	void updateAddress(const std::string& newStreet,
			unsigned short newPostalCode, const std::string& newCityName,
			const std::string& newAdditionalInfo);
    /**
     * @brief Method to update the grade of a specific enrollment.
     * @param enrollmentIndex The index of the enrollment to be updated.
     * @param newGrade The new grade to be set.
     */
	void updateEnrollments(int enrollmentIndex , float newGrade);
    /**
     * @brief Method to remove a specific enrollment.
     * @param enrollmentIndex The index of the enrollment to be removed.
     */
	void removeEnrollments(int enrollmentIndex);
    /**
     * @brief Method to write student details to an output stream.
     * @param out Reference to the output stream.
     */
    void write(std::ostream& out) const;
    /**
     * @brief Method to read student details from an input stream.
     * @param in Reference to the input stream.
     */
    void read(std::istream& in);
    /**
     * @brief Getter for the next available matrikel number.
     * @return The next available matrikel number.
     */
	unsigned int getNextMatrikelNumber() ;
    /**
     * @brief Setter for the next available matrikel number.
     * @param nextMatrikelNumber The next available matrikel number
     *  to be set.
     */
	void setNextMatrikelNumber( unsigned int nextMatrikelNumber);


private:
    /**
     * @brief Static variable representing the next available
     *  matrikel number.
     * it is incremented every time new student is added
     */
	static unsigned int nextMatrikelNumber;
    /**
     * @brief The matrikel number of the student.
     */
	unsigned int matrikelNumber;
	   /**
	     * @brief The first name of the student.
	     */
	std::string firstName;
    /**
     * @brief The last name of the student.
     */
	std::string lastName;
    /**
     * @brief The date of birth of the student.
     */
	Poco::Data::Date dateofBirth;
    /**
     * @brief Vector of Enrollment objects
     *  representing the student's enrollments.
     */
	std::vector<Enrollment> enrollments;
    /**
     * @brief Address object representing the student's address.
     */
	Adress adress;

};

#endif /* STUDENT_H_ */
