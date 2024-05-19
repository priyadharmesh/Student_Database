/*
 * Enrollment.cpp
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

#include "Enrollment.h"
#include <sstream>
#include <limits>

Enrollment::Enrollment(const float& grade, const std::string semester
		,const Course* course):
grade(grade), semester(semester),course(course)
{

}

Enrollment::~Enrollment()
{
	// TODO Auto-generated destructor stub
}

const Course* Enrollment::getCourse() const
{
    return course;
}


float Enrollment::getGrade() const
{
	return grade;
}

const std::string& Enrollment::getSemester() const
{
	return semester;
}

void Enrollment::setGrade(float grade)
{
	this->grade = grade;
}


void Enrollment::write(std::ostream& out) const {
	out << course->getCourseKey() <<";";
    out << grade << ";" << semester << ";" << "\n";

}

void Enrollment::read(std::istream& in) {

    std::string ignoredPart;
    std::getline(in, ignoredPart, ';');
    in >> grade;
    in.ignore();  // Ignore the delimiter
    std::getline(in, semester, ';');
   Course newCourse;
    course = new Course(newCourse);
}

Enrollment::Enrollment()
{
}
