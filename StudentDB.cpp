/*
 * StudentDB.cpp
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

#include "StudentDB.h"
#include "BlockCourse.h"
#include "WeeklyCourse.h"

#include <boost/json.hpp>
#include <iostream>
#include <boost/asio.hpp>
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>

#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>
#include <Poco/Dynamic/Var.h>


//using boost::asio::ip::tcp;
namespace asio = boost::asio;
using asio::ip::tcp;

StudentDB::StudentDB()
{
	// TODO Auto-generated constructor stub

}

StudentDB::~StudentDB()
{
	// TODO Auto-generated destructor stub
}

std::map<int, std::unique_ptr<const Course>>& StudentDB::getCourses()
{
	return courses;
}

std::map<int, Student>& StudentDB::getStudents()
{
	return students;
}


void StudentDB::write(std::ostream &out) const
{

    out << courses.size() << "\n";


    for (const auto& course : courses) {
        course.second->write(out);
    }

    out <<"\n"<< students.size() << "\n";

    for (const auto& student : students) {
        student.second.write(out);
    }
}

void StudentDB::read(std::istream &in) {
    // Read the number of courses
	courses.clear();
	std::unique_ptr<Course> course;
    int numCourses;
    in >> numCourses;

    for (int i = 0; i < numCourses; ++i) {
        // Read the course type from the input stream
        char courseTypeChar;
        in >> courseTypeChar;
        if (courseTypeChar == 'B') {

            course = std::make_unique<BlockCourse>();
        } else if (courseTypeChar == 'W') {

            course = std::make_unique<WeeklyCourse>();
        }

        // Read course data
        course->setCoursetype(courseTypeChar);
        course->read(in);

        // Assuming CourseKey is a data member of the Course class
        unsigned int courseKey = course->getCourseKey();

        // Move the unique_ptr to the courses map
        courses[courseKey] = std::move(course);
    }

    // Clear the current database
    students.clear();

    // Read the number of students
    int numStudents;
    in >> numStudents;

    for (int i = 0; i < numStudents; ++i) {
        Student newStudent;
        newStudent.read(in);
        students[newStudent.getMatrikelNumber()] = newStudent;
        newStudent.setNextMatrikelNumber(newStudent.getMatrikelNumber()+1);

    }

}


void StudentDB::generateFromServer(int numStudents) {
    for (int i = 1; i <= numStudents; i++) {

        sendCommand("generate");
    }
    sendCommand("quit");
}


void StudentDB::sendCommand(const std::string& command) {
    try {
        asio::io_context io_context;
        tcp::resolver resolver(io_context);
        tcp::resolver::results_type endpoints =
        		resolver.resolve("www.hhs.users.h-da.cloud", "4242");

        tcp::socket socket(io_context);
        asio::connect(socket, endpoints);

        asio::write(socket, asio::buffer(command + "\n"));

        // Read the response
        boost::asio::streambuf responseBuffer;
        boost::system::error_code error;
        do {
            asio::read(socket, responseBuffer, asio::transfer_all(), error);

            if (error && error != asio::error::eof) {
                throw boost::system::system_error(error);
            }
        } while (!error);

        std::istream pocoStream(&responseBuffer);

        // Read the response content into a string
        std::string responseData;
        Poco::StreamCopier::copyToString(pocoStream, responseData);

 //       to omit the unwanted data from picture field


        size_t picturePos = responseData.find("\"picture\"");
        size_t registrationPos = responseData.find("\"registrationDate\"");

        if (picturePos != std::string::npos &&
        		registrationPos != std::string::npos) {

            responseData.replace(picturePos,
            		registrationPos - picturePos, "\"picture\":\"...\",");
        }
        size_t jsonDataPos = responseData.find("{");
        if (jsonDataPos != std::string::npos) {
            responseData = responseData.substr(jsonDataPos);
        }
        size_t dataGeneratedPos = responseData.find("200 Data generated");
        if (dataGeneratedPos != std::string::npos) {
            responseData.erase(dataGeneratedPos);
        }

        // Remove additional lines and whitespaces after the JSON data
        size_t jsonDataEndPos = responseData.find_last_of("}");
        if (jsonDataEndPos != std::string::npos) {
            responseData = responseData.substr(0, jsonDataEndPos + 1);
        }

        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(responseData);
        Poco::JSON::Object::Ptr jsonObject =
        		result.extract<Poco::JSON::Object::Ptr>();

        std::ostringstream oss;
        jsonObject->stringify(oss);
        // Extract information

        Poco::JSON::Object::Ptr nameObject = jsonObject->getObject("name");
        std::string firstName = nameObject->
        		getValue<std::string>("firstName");
        std::string lastName = nameObject->getValue<std::string>("lastName");


        // Extract date of birth
        Poco::JSON::Object::Ptr dobObject =
        		jsonObject->getObject("dateOfBirth");
        Poco::Data::Date dateOfBirth(
            dobObject->getValue<int>("year"),
            dobObject->getValue<int>("month"),
            dobObject->getValue<int>("date")
        );

        // Extract address
        unsigned short postalCode=0;
        Poco::JSON::Object::Ptr locationObject =
        		jsonObject->getObject("location");
        std::string city = locationObject->getValue<std::string>("city");

        int postCode = std::stoi
        		(locationObject->getValue<std::string>("postCode"));
        if (postCode >= std::numeric_limits<unsigned short>::min() &&
            postCode <= std::numeric_limits<unsigned short>::max()) {
            postalCode = static_cast<unsigned short>(postCode);
        }
        else
        {
        	std::cerr << "Postal Code is out of range for "
        			"unsigned short." << std::endl;
        }
        std::string state = locationObject->getValue<std::string>("state");
        std::string street = locationObject->getValue<std::string>("street");

        //to create new student
    	Adress Adress1(street, postalCode, city, state);

    	Student Student1(firstName, lastName, dateOfBirth, Adress1);
    	std::map<int, Student>& students=getStudents();
    	students.insert(std::make_pair(Student1.getMatrikelNumber()
    			,Student1));


    }

    catch (std::exception& e) {
      //  std::cerr << "Exception: " << e.what() << std::endl;
    }
}
