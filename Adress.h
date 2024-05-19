/*
 * Adress.h
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

#ifndef ADRESS_H_
#define ADRESS_H_

#include<iostream>

class Adress
{
public:
	/*
	 * @brief Constructor: Initializes the Address
	 * object with provided values.
     * @param street The street name of the address.
     * @param postalCode The postal code of the address.
     * @param cityName The name of the city.
     * @param additionalInfo Additional information about the address.
	 */
	Adress(const std::string& street, unsigned short postalCode,
            const std::string& cityName, const std::string& additionalInfo);
	Adress();
	virtual ~Adress();
	/*
	 * setters and getters for all the data members of address
	 *
	 */
	const std::string& getAdditionalInfo() const;
	void setAdditionalInfo(const std::string &additionalInfo);
	const std::string& getCityName() const;
	void setCityName(const std::string &cityName);
	unsigned short getPostalCode() const;
	void setPostalCode(unsigned short postalCode);
	const std::string& getStreet() const;
	void setStreet(const std::string &street);

     /*
     * @brief Write function: Outputs the Address
     * object's data to the provided output stream.
     * @param out The output stream.
     */
    void write(std::ostream& out) const;

    /**
     * @brief Read function: Reads data members of the
     * Address class from the input stream.
     * @param in The input stream.
     */
    void read(std::istream& in);
private:
    /**
     * @brief Data member: Street name of the address.
     */
	std::string street;
    /**
     * @brief Data member: Postal code of the address.
     */
	unsigned short postalCode;
    /**
     * @brief Data member: Name of the city.
     */
	std::string cityName;
    /**
     * @brief Data member: Additional information about the address.
     */
	std::string additionalInfo;
};

#endif /* ADRESS_H_ */
