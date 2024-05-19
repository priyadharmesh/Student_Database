/*
 * Course.cpp
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

#include "Course.h"
#include <string>
#include <cstring>


Course::Course(const int& courseKey, const std::string& title,
		const float &creditPoints, std::string Major, char
		coursetype) :courseKey(courseKey),
title(title), creditPoints(creditPoints), Coursetype(coursetype)
{
	char charArray[Major.size() + 1];
	strcpy(charArray, Major.substr(0,1).c_str());
	major = charArray[0];
	majorById[major]=Major;

}

std::string Course::getMajor() const
{
	auto it = majorById.find(major);
	if (it != majorById.end())
	{
		return it->second;
	}
	return 0;
}

Course::~Course()
{
	// TODO Auto-generated destructor stub
}

float Course::getCreditPoints() const
{
	return creditPoints;
}

void Course::setCreditPoints(float creditPoints)
{
	this->creditPoints = creditPoints;
}

unsigned int Course::getCourseKey() const
{
	return courseKey;
}

const std::string& Course::getTitle() const
{
	return title;
}

void Course::write(std::ostream &out) const
{
	    out <<getCoursetype() << ";" << courseKey << ";" << title
	    		<< ";" << creditPoints << ";" << getMajor() <<";";

}

void Course::read(std::istream &in)
{

	 in.ignore();
	 in >> courseKey; in.ignore();
    std::getline(in, title, ';');
    in >> creditPoints; in.ignore();
    std::string Major;
    std::getline(in, Major, ';');
	char charArray[Major.size() + 1];
	strcpy(charArray, Major.substr(0,1).c_str());
	major = charArray[0];
	majorById[major]=Major;
}

char Course::getCoursetype() const
{
	return Coursetype;
}

Course::Course()
{
}

void Course::setCoursetype(char coursetype)
{
	Coursetype = coursetype;
}
