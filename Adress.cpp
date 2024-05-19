/*
 * Adress.cpp
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

#include "Adress.h"

Adress::Adress(const std::string& street, unsigned short postalCode,
        const std::string& cityName, const std::string& additionalInfo)
        :street(street),postalCode(postalCode), cityName(cityName),
		 additionalInfo(additionalInfo)
{
	// TODO Auto-generated constructor stub

}

Adress::~Adress()
{
	// TODO Auto-generated destructor stub
}

const std::string& Adress::getAdditionalInfo() const
{
	return additionalInfo;
}

void Adress::setAdditionalInfo(const std::string &additionalInfo)
{
	this->additionalInfo = additionalInfo;
}

const std::string& Adress::getCityName() const
{
	return cityName;
}

void Adress::setCityName(const std::string &cityName)
{
	this->cityName = cityName;
}

unsigned short Adress::getPostalCode() const
{
	return postalCode;
}

void Adress::setPostalCode(unsigned short postalCode)
{
	this->postalCode = postalCode;
}

const std::string& Adress::getStreet() const
{
	return street;
}

void Adress::setStreet(const std::string &street)
{
	this->street = street;
}

void Adress::write(std::ostream &out) const
{
	    out << street << ";" << cityName << ";"
	    << postalCode << ";" <<additionalInfo <<";";

}

void Adress::read(std::istream &in)
{
    std::getline(in, street, ';');
    std::getline(in, cityName, ';');
    in >> postalCode;in.ignore();
    std::getline(in, additionalInfo, ';');
}

Adress::Adress()
{
}
