/*
 * Course.h
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

#ifndef COURSE_H_
#define COURSE_H_

#include<map>
#include<iostream>
class Course
{
public:

    /**
     * @brief Parameterized constructor:
     * Initializes a Course object with provided values.
     * @param courseKey
     * @param title
     * @param creditPoints .
     * @param Major
     * @param coursetype
     */
	Course(const int& courseKey, const std::string& title,
			const float &creditPoints, const std::string Major ,
			char coursetype );
    /**
     * @brief Destructor: Cleans up resources associated with
     * the Course object.
     */
	virtual ~Course();
	/*
	 * default constructor
	 */
	Course();
	/*
	 * getters and setters of all data members
	 */
	/*
	 * @ returns : checks the majorbyId map and
	 *  returns the corresponding string value for major
	 *
	 */
	std::string getMajor() const;
	void setMajor(unsigned char major);
	float getCreditPoints() const;
	void setCreditPoints(float creditPoints);
	unsigned int getCourseKey() const;
	const std::string& getTitle() const;
	char getCoursetype() const;
	void setCoursetype(char coursetype);

	   /**
	     * @brief Virtual function to write data to the output stream.
	     * @param out The output stream.
	     */
    virtual void write(std::ostream& out) const;
    /**
     * @brief Virtual function to read data from the input stream.
     * @param in The input stream.
     */
    virtual void read(std::istream& in) ;


private:
    /**
     * @brief Data member: Map to store major information.
     * key:major with character value:string data
     */
	std::map<unsigned char ,std::string> majorById;
    /**
     * @brief Data member: The key identifying the course.
     */
	unsigned int courseKey;
    /**
     * @brief Data member: The title of the course.
     */
	std::string title;
    /**
     * @brief Data member: The major associated with the course.
     */
	unsigned char major;
    /**
     * @brief Data member: The credit points associated with the course.
     */

	float creditPoints;
    /**
     * @brief Data member: The type of the course.
     * B-Blocked Course
     * W-Weekly Course
     */
	
	unsigned int Coursetype;

};

#endif /* COURSE_H_ */
