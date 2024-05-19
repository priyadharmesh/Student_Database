/*
 * Student.cpp
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

#include "Student.h"


inline std::ostream& operator<<(std::ostream& out,
		const Poco::Data::Date& date) {
    out << date.year() << '-' << date.month() << '-' << date.day();
    return out;
}

inline std::istream& operator>>(std::istream& in, Poco::Data::Date& date) {
    int year, month, day;
    char dash1, dash2;

    if (in >> year >> dash1 >> month >> dash2 >> day) {
        if (dash1 == '-' && dash2 == '-') {
            date = Poco::Data::Date(year, month, day);
        } else {
            // Handle incorrect format
            in.setstate(std::ios_base::failbit);
        }
    }

    return in;
}



// Definition and initialization of the static member variable
unsigned int Student::nextMatrikelNumber = 100000;

Student::Student(const std::string& firstName, const std::string& lastName,
		const Poco::Data::Date& dateOfBirth,
		 Adress& Adress): matrikelNumber(nextMatrikelNumber),
		firstName(firstName), lastName(lastName), dateofBirth(dateOfBirth)
        ,adress(Adress)
{
	nextMatrikelNumber++;
}

Student::~Student()
{

}


const Poco::Data::Date& Student::getDateofBirth() const
{
	return dateofBirth;
}

void Student::setDateofBirth(const Poco::Data::Date &dateofBirth)
{
	this->dateofBirth = dateofBirth;
}

const std::string& Student::getFirstName() const
{
	return firstName;
}

void Student::setFirstName(const std::string &firstName)
{
	this->firstName = firstName;
}

const std::string& Student::getLastName() const
{
	return lastName;
}

void Student::setLastName(const std::string &lastName)
{
	this->lastName = lastName;
}

unsigned int Student::getMatrikelNumber() const
{
	return matrikelNumber;
}

void Student::setMatrikelNumber(unsigned int matrikelNumber)
{
	this->matrikelNumber = matrikelNumber;
}

 Adress& Student::getAdress()
{
	return adress;
}

const std::vector<Enrollment>& Student::getEnrollments() const
{
	return enrollments;
}

void Student::addEnrollments(const Enrollment& enrollment) {

	 enrollments.push_back(enrollment);
}

void Student::updateAddress(const std::string& newStreet,
		unsigned short newPostalCode, const std::string& newCityName,
		const std::string& newAdditionalInfo) {
    adress = Adress(newStreet, newPostalCode, newCityName, newAdditionalInfo);
}

// Implement the member function
void Student::updateEnrollments(int enrollmentIndex , float newGrade) {

                enrollments[enrollmentIndex].setGrade(newGrade);
}
 void Student::removeEnrollments(int enrollmentIndex)
 {

    enrollments.erase(enrollments.begin() + enrollmentIndex);
 }

void Student::write(std::ostream &out) const
{

	out << matrikelNumber << ";" << firstName << ";" <<
			lastName << ";" << dateofBirth << ";";
	adress.write(out);

    out << "\n"<< enrollments.size() << "\n";
    for (const Enrollment& enrollment : enrollments) {
        enrollment.write(out);
    }
}



Student::Student()
{

}


void Student::read(std::istream& in)
{

	    in >> matrikelNumber ;

	    in.ignore();
	    std::getline(in, firstName, ';');
	    std::getline(in, lastName, ';');
	    in >> dateofBirth;
	    in.ignore();
	    adress.read(in);
        in.ignore();
	    int numEnrollments;
	    in >> numEnrollments;
	    in.ignore();
	    enrollments.resize(numEnrollments);
	    for (Enrollment& enrollment : enrollments) {
	        enrollment.read(in);
	    }
}

 unsigned int Student::getNextMatrikelNumber()
{
	return nextMatrikelNumber;
}

void Student::setNextMatrikelNumber( unsigned int nextMatrikelNumber)
{
	this->nextMatrikelNumber = nextMatrikelNumber;
}
