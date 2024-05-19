/*
 * WeeklyCourse.h
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

#ifndef WEEKLYCOURSE_H_
#define WEEKLYCOURSE_H_

#include "Course.h"
#include "Poco/Data/Date.h"
#include "Poco/Data/Time.h"

/**
 * @brief The WeeklyCourse class represents a course that
 *  occurs weekly with specific days and times.
 */

class WeeklyCourse: public Course
{
public:
    /**
     * @brief Default constructor:
     * Initializes a WeeklyCourse object with default values.
     */
	WeeklyCourse() = default;
    /**
     * @brief Parameterized constructor:
     * Initializes a WeeklyCourse object with specified values.
     * @param courseKey ,@param title ,@param creditPoints
     * ,@param Major ,@param dayOfWeek , @param startTime
     * @param endTime .,@param coursetype .
     */
	WeeklyCourse(const int& courseKey, const std::string& title,
			const float &creditPoints ,const std::string Major,
			Poco::DateTime::DaysOfWeek dayOfWeek,
            Poco::Data::Time startTime,
            Poco::Data::Time endTime , char coursetype);
    /**
     * @brief Destructor: Cleans up resources associated
     * with the WeeklyCourse object.
     */
	virtual ~WeeklyCourse();
    /**
     * @brief Getter for the day of the week when the course occurs.
     * @return The day of the week.
     */
	const Poco::DateTime::DaysOfWeek getDayOfWeek() const;
    /**
     * @brief Getter for the end time of the course.
     * @return Reference to the end time.
     */
	const Poco::Data::Time& getEndTime() const ;
    /**
     * @brief Getter for the start time of the course.
     * @return Reference to the start time.
     */
	const Poco::Data::Time& getStartTime() const ;

    /**
     * @brief Method to write the WeeklyCourse object
     *
     * to an output stream.
     * @param out Reference to the output stream.
     */
    void write(std::ostream& out) const override;
    /**
     * @brief Method to read the WeeklyCourse object from an input stream.
     * @param in Reference to the input stream.
     */
    void read(std::istream& in)  override;

    /**
     * @brief Friend function to output Poco::Data::Time
     * to an output stream.
     * @param out Reference to the output stream.
     * @param time The Poco::Data::Time to output.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& out,
    		const Poco::Data::Time& time);
    /**
     * @brief Friend function to input Poco::Data::Time
     *  from an input stream.
     * @param in Reference to the input stream.
     * @param time Reference to the Poco::Data::Time to input.
     * @return Reference to the input stream.
     */
    friend std::istream& operator>>(std::istream& in,
    		Poco::Data::Time& time);
    /**
     * @brief Friend function to output Poco::DateTime::DaysOfWeek
     * to an output stream.
     * @param out Reference to the output stream.
     * @param dayOfWeek The Poco::DateTime::DaysOfWeek to output.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& out,
    		const Poco::DateTime::DaysOfWeek& dayOfWeek);
    /**
      * @brief Friend function to input Poco::DateTime::DaysOfWeek
      * from an input stream.
      * @param in Reference to the input stream.
      * @param dayOfWeek Reference to the
      * Poco::DateTime::DaysOfWeek to input.
      * @return Reference to the input stream.
      */
    friend  std::istream& operator>>(std::istream& in,
    		Poco::DateTime::DaysOfWeek& dayOfWeek);

private:
    /**
     * @brief The day of the week when the course occurs.
     */
	Poco::DateTime::DaysOfWeek dayOfWeek;
    /**
     * @brief The start time of the course.
     */
	Poco::Data::Time startTime;
    /**
     * @brief The end time of the course.
     */
	Poco::Data::Time endTime;
};

inline std::ostream& operator << (std::ostream& out,
		const Poco::Data::Time& time) {
    out << time.hour() << ':' << time.minute() << ':' << time.second();
    return out;
}

inline std::istream& operator >> (std::istream& in,
		Poco::Data::Time& time) {
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

inline std::ostream& operator<<(std::ostream& out,
		const Poco::DateTime::DaysOfWeek& dayOfWeek) {
    switch (dayOfWeek) {
        case Poco::DateTime::SUNDAY:
            out << "Sunday";
            break;
        case Poco::DateTime::MONDAY:
            out << "Monday";
            break;
        case Poco::DateTime::TUESDAY:
            out << "Tuesday";
            break;
        case Poco::DateTime::WEDNESDAY:
            out << "Wednesday";
            break;
        case Poco::DateTime::THURSDAY:
            out << "Thursday";
            break;
        case Poco::DateTime::FRIDAY:
            out << "Friday";
            break;
        case Poco::DateTime::SATURDAY:
            out << "Saturday";
            break;
        default:
            out << "Invalid Day";
            break;
    }

    return out;
}

inline std::istream& operator>>(std::istream& in,
		Poco::DateTime::DaysOfWeek& dayOfWeek) {
    std::string dayStr;
    std::getline(in, dayStr, ';');

    if (dayStr == "Sunday") {
        dayOfWeek = Poco::DateTime::SUNDAY;
    } else if (dayStr == "Monday") {
        dayOfWeek = Poco::DateTime::MONDAY;
    } else if (dayStr == "Tuesday") {
        dayOfWeek = Poco::DateTime::TUESDAY;
    } else if (dayStr == "Wednesday") {
        dayOfWeek = Poco::DateTime::WEDNESDAY;
    } else if (dayStr == "Thursday") {
        dayOfWeek = Poco::DateTime::THURSDAY;
    } else if (dayStr == "Friday") {
        dayOfWeek = Poco::DateTime::FRIDAY;
    } else if (dayStr == "Saturday") {
        dayOfWeek = Poco::DateTime::SATURDAY;
    } else {
        in.setstate(std::ios_base::failbit);
    }

    return in;
}

#endif /* WEEKLYCOURSE_H_ */
