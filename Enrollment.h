/*
 * Enrollment.h
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

/**
 * @brief The Enrollment class represents a student's enrollment in a course.
 */
#ifndef ENROLLMENT_H_
#define ENROLLMENT_H_

#include"Course.h"
#include<iostream>
#include<memory>

class Enrollment
{
public:
    /**
     * @brief Parameterized constructor: Initializes an
     * Enrollment object with provided values.
     * @param grade ,@param semester
     * @param course Pointer to the Course object associated
     *  with the enrollment.
     */
	Enrollment(const float& grade, const std::string semester ,
			const Course* course);
	/*
	 * Default Constructor
	 */
	Enrollment();
    /**
     * @brief Destructor: Cleans up resources associated
     *  with the Enrollment object.
     */
	virtual ~Enrollment();

    /**
     * @brief Getter for course.
     * @return Pointer to the Course object associated with the enrollment.
     */
	const Course* getCourse() const;
    /**
     * @brief Getter for grade.
     * @return The grade obtained in the course.
     */
	float getGrade() const;
    /**
     * @brief Getter for semester.
     * @return The semester in which the student is enrolled.
     */
	const std::string& getSemester() const;
    /**
     * @brief Setter for grade.
     * @param grade The grade to set for the enrollment.
     */
	void setGrade(float grade);

    /**
     * @brief Virtual function to write data to the output stream.
     * @param out The output stream.
     */
    void write(std::ostream& out) const;
    /**
     * @brief Virtual function to read data from the input stream.
     * @param in The input stream.
     */
    void read(std::istream& in);

private:
    /**
     * @brief Data member: The grade obtained in the course.
     */
	float grade;
    /**
     * @brief Data member: The semester in which the student is enrolled.
     */
	std::string semester;
    /**
     * @brief Data member: Pointer to the Course
     * object associated with the enrollment.
     */
	const Course* course;
};

#endif /* ENROLLMENT_H_ */
