/*
 * WeeklyCourse.cpp
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

#include "WeeklyCourse.h"


WeeklyCourse::WeeklyCourse(const int& courseKey, const std::string& title,
		const float &creditPoints, std:: string Major ,
		Poco::DateTime::DaysOfWeek dayOfWeek,
        Poco::Data::Time startTime,
        Poco::Data::Time endTime , char coursetype):
		Course(courseKey, title, creditPoints, Major, coursetype),
		dayOfWeek(dayOfWeek), startTime(startTime), endTime(endTime)
{
}

WeeklyCourse::~WeeklyCourse()
{
	// TODO Auto-generated destructor stub
}

const Poco::DateTime::DaysOfWeek WeeklyCourse::getDayOfWeek() const
{
	return dayOfWeek;
}

 const Poco::Data::Time& WeeklyCourse::getEndTime() const
{
	return endTime;
}

 const Poco::Data::Time& WeeklyCourse::getStartTime() const
{
	return startTime;
}


void WeeklyCourse::write(std::ostream& out) const {

    Course::write(out);
    out << dayOfWeek << ";" << startTime << ";" << endTime << ";";
}


void WeeklyCourse::read(std::istream& in)  {

    Course::read(in);

    in >> dayOfWeek;
    in.ignore();
    in >> startTime;
    in.ignore();
    in >> endTime;
    in.ignore();
}


