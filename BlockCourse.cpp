/*
 * BlockCourse.cpp
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

#include "BlockCourse.h"
#include <ostream>
#include <istream>
#include <Poco/Data/Date.h>


std::ostream& operator<<(std::ostream& out,
		const Poco::Data::Date& date) {
    out << date.year() << '-' << date.month() << '-' << date.day();
    return out;
}


inline std::istream& operator>>(std::istream& in,
		Poco::Data::Date& date) {
    int year, month, day;
    char dash1, dash2;

    if (in >> year >> dash1 >> month >> dash2 >> day) {

        if (dash1 == '-' && dash2 == '-') {
            date = Poco::Data::Date(year, month, day);
        } else {

            in.setstate(std::ios_base::failbit);
        }
    }

    return in;
}



std::ostream& operator<<(std::ostream& out,
		const  Poco::Data::Time& time) {

    out << time.hour() << ':' << time.minute() << ':' << time.second();
    return out;
}

std::istream& operator>>(std::istream& in, Poco::Data::Time& time) {

    int hours, minutes, seconds;
    char colon1, colon2;

    if (in >> hours >> colon1 >> minutes >> colon2 >> seconds) {

        if (colon1 == ':' && colon2 == ':') {
            time = Poco::Data::Time(hours, minutes, seconds);
        } else {

            in.setstate(std::ios_base::failbit);
        }
    }

    return in;
}


/**
 * @brief The BlockCourse class represents a
 * block-type course, derived from the Course class.
 */
BlockCourse::BlockCourse(const int& courseKey,
		const std::string& title, const float &creditPoints,
		const std::string Major, Poco::Data::Date startDate,
        Poco::Data::Date endDate, Poco::Data::Time startTime,
        Poco::Data::Time endTime, char coursetype) :
		Course(courseKey, title, creditPoints, Major, coursetype) ,
		startDate(startDate), endDate(endDate), startTime(startTime),
		endTime(endTime)
{
}

BlockCourse::~BlockCourse()
{
	// TODO Auto-generated destructor stub
}

 const Poco::Data::Date& BlockCourse::getEndDate() const
{
	return endDate;
}

 const Poco::Data::Time& BlockCourse::getEndTime() const
{
	return endTime;
}

 const Poco::Data::Date& BlockCourse::getStartDate() const
{
	return startDate;
}

 const Poco::Data::Time& BlockCourse::getStartTime() const
{
	return startTime;
}


void BlockCourse::write(std::ostream& out) const {

    Course::write(out);
    out << startDate << ";" << endDate << ";" << startTime
    		<< ";" << endTime << ";" <<"\n";
}

void BlockCourse::read(std::istream& in)  {

	    Course::read(in);
	    in.ignore();

	    if (!(in >> startDate)) {
	        std::cerr << "Error reading startDate" << std::endl;
	    }

	    in.ignore();

	    if (!(in >> endDate)) {
	        std::cerr << "Error reading endDate" << std::endl;
	    }

	    in.ignore();

	    if (!(in >> startTime)) {
	        std::cerr << "Error reading startTime" << std::endl;
	    }

	    in.ignore();

	    if (!(in >> endTime)) {
	        std::cerr << "Error reading endTime" << std::endl;
	    }

	    in.ignore();
}


