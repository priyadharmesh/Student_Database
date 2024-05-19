/*
 * BlockCourse.h
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

#ifndef BLOCKCOURSE_H_
#define BLOCKCOURSE_H_

#include "Course.h"
#include "Poco/Data/Date.h"
#include "Poco/Data/Time.h"

class BlockCourse: public Course
{
public:
    /**
     * @brief Default constructor: Initializes a
     * BlockCourse object with default values.
     */
	BlockCourse() = default;
    /**
     * @brief Parameterized constructor:
     * Initializes a BlockCourse object with provided values.
     * @param courseKey ,@param title ,
     * @param creditPoints, @param Major  ,@param startDate,
     *  @param endDate , @param startTime ,@param endTime
     *  ,@param coursetype
     */
	BlockCourse(const int& courseKey, const std::string& title,
			const float &creditPoints,std::string Major,
			Poco::Data::Date startDate ,
			Poco::Data::Date endDate, Poco::Data::Time startTime,
			Poco::Data::Time endTime, char coursetype);
    /**
     * @brief Destructor:
     * Cleans up resources associated with the BlockCourse object.
     */
	virtual ~BlockCourse();
    /**
     * @brief Getter for endDate.
     * @return The end date of the block course.
     */
	const Poco::Data::Date& getEndDate() const;

    /**
     * @brief Getter for endTime.
     * @return The end time of the block course.
     */
	const Poco::Data::Time& getEndTime() const ;
    /**
     * @brief Getter for startDate.
     * @return The start date of the block course.
     */
	const Poco::Data::Date& getStartDate() const;
    /**
     * @brief Getter for startTime.
     * @return The start time of the block course.
     */
	 const Poco::Data::Time& getStartTime() const ;

	  /**
	   * @brief Write function: Outputs the BlockCourse
	   * object's data to the provided output stream.
	   * @param out The output stream.
	   */
    void write(std::ostream& out) const override;

    /**
     * @brief Read function: Reads data members
     * of the BlockCourse class from the input stream.
     * @param in The input stream.
     */
    void read(std::istream& in)  override;

    /**
     * @brief Friend function to overload the
     * << operator for outputting Poco::Data::Date.
     * @param out The output stream.
     * @param date The Poco::Data::Date object.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& out,
    		const Poco::Data::Date& date);

    /**
     * @brief Friend function to overload the >>
     * operator for reading Poco::Data::Date.
     * @param in The input stream.
     * @param date The Poco::Data::Date object.
     * @return The input stream.
     */
    friend std::istream& operator>>(std::istream& in,
    		Poco::Data::Date& date);
private:
    /**
     * @brief Data member: The start date of the block course.
     */
	Poco::Data::Date startDate;
    /**
     * @brief Data member: The end date of the block course.
     */
	Poco::Data::Date endDate;
    /**
     * @brief Data member: The start time of the block course.
     */
	Poco::Data::Time startTime;
    /**
     * @brief Data member: The end time of the block course.
     */
	Poco::Data::Time endTime;

};

#endif /* BLOCKCOURSE_H_ */
