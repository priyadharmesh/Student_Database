/*
 * SimpleUI.cpp
 *
 *  Created on: 27-Jan-2024
 *      Author: dharm
 */

#include <fstream>
#include "SimpleUI.h"
#include "Course.h"
#include "Enrollment.h"
#include "BlockCourse.h"
#include "WeeklyCourse.h"
#include "Poco/Data/Date.h"
#include "Poco/Data/Time.h"

SimpleUI::SimpleUI(StudentDB& StudentDB): database(StudentDB)
{

}


void SimpleUI::run() {
    while (true) {
        displayMenu();
        processUserInput();
    }
}


void SimpleUI::displayMenu() const {
    std::cout << "1. Add new Course\n"
              << "2. List courses\n"
              << "3. Add new student\n"
              << "4. Add enrollment\n"
              << "5. Print student\n"
              << "6. Search student\n"
              << "7. Update student\n"
			  << "8. Read or Write into File \n"
			  << "9. Student from Server \n "
              << "10. Exit\n"
              << "Enter your choice: ";
}

void SimpleUI::processUserInput() {
    int choice;
    std::cin >> choice;

    executeCommand(choice);
}

void SimpleUI::executeCommand(int choice) {
    switch (choice) {
        case 1:
            addNewCourse();
            break;
        case 2:
            listCourses();
            break;
        case 3:
            addNewStudent();
            break;
        case 4:
            addEnrollment();
            break;
        case 5:
            printStudent();
            break;
        case 6:
            searchStudent();
            break;
        case 7:
            updateStudent();
            break;
        case 8:
        	execute_RW_Commands();
        	break;
        case 9:
        	generateStudentsFromServer();
        	break;
        case 10:
            std::cout << "Exiting...\n";
            exit(0);
        default:
            std::cout << "Invalid choice. Please enter a valid option.\n";
    }
}

void SimpleUI::generateStudentsFromServer()
{
    int numStudents;
    std::cout << "Enter the number of students to add: ";
    std::cin >> numStudents;
	database.generateFromServer(numStudents);
}


void SimpleUI::addNewCourse() {

	int courseKey;
	std::string title;
	float creditPoints;
	std::string major;
	std::cout<<"Enter the course details"<<std::endl;
	std::cout<<"Do you need to add a BlockedCourse or a WeeklyCourse..\n "
			"Press B.Blocked Course \n W.WeeklyCourse"<<std::endl;
	char choice;
	std::cin>>choice;
	std::cout<<"Enter the courseKey"<<std::endl;

	std::cin>>courseKey;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout<<"Enter the title"<<std::endl;
	std::getline(std::cin, title);

	std::cout<<"Enter the major"<<std::endl;
	std::cin>>major;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout<<"enter the creditpoints for the course"<<std::endl;
	std::cin>> creditPoints;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	switch (choice)
	{
	case 'B':
	{
		int day,month,year;
		int hour,minute,seconds;
		std::cout<<"Enter the start date for the course"<<std::endl;
		std::cin>>day>>month>>year;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		Poco::Data::Date startDate(year, month, day);
		std::cout<<"Enter the end date for the course"<<std::endl;
		std::cin>>day>>month>>year;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		Poco::Data::Date endDate(year, month, day);
		std::cout<<"Enter the start time for the course"<<std::endl;
		std::cin>>hour>>minute>>seconds;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		Poco::Data::Time startTime(hour, minute, seconds);
		std::cout<<"Enter the end time for the course"<<std::endl;
		std::cin>>hour>>minute>>seconds;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		Poco::Data::Time endTime(hour, minute, seconds);

	    std::unique_ptr<BlockCourse> blockCourse=
	    		std::make_unique<BlockCourse>(courseKey, title, creditPoints,
	    				major,startDate,endDate,startTime,endTime,'B' );
		auto& courses=database.getCourses();
		auto it = courses.find(courseKey);
	    if(it != courses.end())
	    {
	    	std::cout<<"key already exists"<<std::endl;
	    }
	    else
	      courses[courseKey] = std::move(blockCourse);
		break;
	}
	case 'W':
	{
		int hour,minute,seconds;
		std::cout<<"Enter the Day of week for the course"<<std::endl;
		std::string dayString;
		std::cin >> dayString;

		Poco::DateTime::DaysOfWeek days=Poco::DateTime::MONDAY;

		if (dayString == "Monday") {
		    days = Poco::DateTime::MONDAY;
		} else if (dayString == "Tuesday") {
		    days = Poco::DateTime::TUESDAY;
		} else if (dayString == "Wednesday") {
		    days = Poco::DateTime::WEDNESDAY;
		} else if (dayString == "Thursday") {
		    days = Poco::DateTime::THURSDAY;
		} else if (dayString == "Friday") {
		    days = Poco::DateTime::FRIDAY;
		} else if (dayString == "Saturday") {
		    days = Poco::DateTime::SATURDAY;
		} else if (dayString == "Sunday") {
		    days = Poco::DateTime::SUNDAY;
		} else {
		    std::cout << "Invalid day input. "
		    		"Please enter a valid day." << std::endl;
		}

		std::cout<<"Enter the start time for the course"<<std::endl;
		std::cin>>hour>>minute>>seconds;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		Poco::Data::Time startTime(hour, minute, seconds);
		std::cout<<"Enter the end time for the course"<<std::endl;
		std::cin>>hour>>minute>>seconds;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		Poco::Data::Time endTime(hour, minute, seconds);
		std::unique_ptr<Course> weeklyCourse = std::unique_ptr<WeeklyCourse>
		    (new WeeklyCourse(courseKey, title,
		    		creditPoints, major, days, startTime, endTime , 'W'));
		auto& courses=database.getCourses();
		auto it = courses.find(courseKey);
	    if(it != courses.end())
	    {
	    	std::cout<<"key already exists"<<std::endl;
	    }
	    else
	      courses[courseKey] = std::move(weeklyCourse);

		break;
	}
	default:
		std::cout <<"Invalid choice .Please enter a valid option.\n";
	}

}



void SimpleUI::listCourses() {

	 auto& courses=database.getCourses();
	    std::cout << "Current Courses:\n" << courses.size()<< std::endl ;
	    for (const auto& entry : courses) {
	        int key = entry.first;
	        const Course* course = entry.second.get();
	        std::cout << "Course Type is : " << course->getCoursetype()
	        		<< "\n Course Key: " << key << "\n Title: "
					<< course->getTitle() << "\n Major: "
					<< course->getMajor()
					<<"\n CreditPoints: "<< course->getCreditPoints()
					<<std::endl;

	        //down casting reference from a base class type to a
	       // derived class type is known as downcasting to access
	        //member function of derived class
	       if( const BlockCourse* blockedCourse =
	    		   dynamic_cast<const BlockCourse*>(course))
	       {
	        std::cout<<"StartDate is: "<<blockedCourse->getStartDate().day()
	        	<<"/"<<blockedCourse->getStartDate().month()
	        	<<"/"<<blockedCourse->getStartDate().year()
			    <<"\n End date is: "<<blockedCourse->getEndDate().day()
				<<"/"<<blockedCourse->getEndDate().month()
	        	<<"/"<<blockedCourse->getEndDate().year()
				<<"\n Start time is :"<<blockedCourse->getStartTime().hour()
					<<"/"<<blockedCourse->getStartTime().minute()
	        		<<"/"<<blockedCourse->getStartTime().second()
					<<"\n End time is :"<<blockedCourse->getEndTime().hour()
					<<"/"<<blockedCourse->getEndTime().minute()
	        		<<"/"<<blockedCourse->getEndTime().second()<<std::endl;
	       }
	       if(const WeeklyCourse* weeklyCourse =
	    		   dynamic_cast<const WeeklyCourse*>(course))
	       {
	    	   std::cout<<"Start Day :"<<weeklyCourse->getDayOfWeek()
	    			   <<"\n Start time: "<<weeklyCourse->
					   getStartTime().hour()
					   <<"/"<<weeklyCourse->getStartTime().minute()
	    			   << "/"<<weeklyCourse->getStartTime().second()
					   <<"\n End time: "<<weeklyCourse->getEndTime().hour()
					   <<"/"<<weeklyCourse->getEndTime().minute()
	    			   << "/"<<weeklyCourse->getEndTime().second()<<std::endl;
	       }
	    }

}

void SimpleUI::addNewStudent() {

	std::string firstName;
	std::string lastName;
	std::string street;
	unsigned short postalCode;
	std::string cityName;
	std::string additionalInfo;
	int day, month, year;

	std::cout<< "Adding a new student"<<std::endl;
	std::cout<<"Enter the first name"<<std::endl;
	std::cin>>firstName;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout<<"Enter the last name"<<std::endl;
	std::cin>>lastName;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout<<"Enter your date of birth (DD--MM--YYYY): "<<std::endl;
	std::cin>> day >> month >> year;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	Poco::Data::Date dateofBirth(year, month, day);

	std::cout<<"Enter the address"<<std::endl;
	std::cout<<"Enter the Street Name"<<std::endl;
	std::getline(std::cin, street);
	std::cout<<"Enter the postalCode"<<std::endl;
	std::cin>>postalCode;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout<<"Enter the cityName"<<std::endl;
    std::cin>>cityName;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout<<"Enter additional info if any: "<<std::endl;
	std::cin>>additionalInfo;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	Adress Adress1(street, postalCode, cityName, additionalInfo);

	Student Student1(firstName, lastName, dateofBirth, Adress1);
	std::map<int, Student>& students=database.getStudents();
	students.insert(std::make_pair(Student1.getMatrikelNumber(), Student1));

}

void SimpleUI::addEnrollment() {
	int mat_num;
	int course_key;
	std::string semester;
	float grade;
	std::unique_ptr<const Course> course;
	const Course* rawCoursePtr = nullptr;
	std::cout<<"Adding enrollment, "
			"Please enter the matriculation number"<<std::endl;
	 std::cin>>mat_num;
	 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	 std::cout<<"please enter the courseKey"<<std::endl;
	 std::cin>>course_key;
	 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	 auto& student=database.getStudents();
	 auto& courses=database.getCourses();
	 auto it = student.find(mat_num);
	 auto it1 = courses.find(course_key);

	 if(!(it != student.end() && it1 != courses.end()))
	 {
		std::cout<<"no students or course as such, try again"<<std::endl;
	 }
	 else
	 {

		 std::cout<<"enter the semester"<<std::endl;
		 std::cin>>semester;
		 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		 std::cout<<"enter the grade"<<std::endl;
		 std::cin>>grade;
		 std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		 if(it1 != courses.end())
		 {
			 rawCoursePtr = it1->second.get();
		 }
		 Enrollment enrollment1(grade,semester,rawCoursePtr);
		 if(it != student.end())
		 {
			 Student& student1=it->second;
			 student1.addEnrollments(enrollment1);
		 }
	 }
}

void SimpleUI::printStudent() {
	std::vector<Enrollment> enrollments;
	 auto& student=database.getStudents();
	    std::cout << "Current Students:\n"<<student.size()<<std::endl;

	    for (const auto& entry : student) {
	        int key = entry.first;
	        Student student = entry.second;
	        std::cout << "Matriculation Number is :"<<key<<std::endl;
	        std::cout << "FirstName: " <<student.getFirstName()
	        		<< "\n LastName: " << student.getLastName()
					<< "\n DateofBirth: "<<
	        		student.getDateofBirth().day()
					<<"/"<<student.getDateofBirth().month()
					<<"/"<<student.getDateofBirth().year()
					<<	"\n Adress of a student is: "<<std::endl;
	                std::cout<<"\n street: "<<student.getAdress().getStreet()
					<<"\n postalCode: "<< student.getAdress().getPostalCode()
					<<"\n cityName: "<< student.getAdress().getCityName()
					<<", Additional info: "<<student.getAdress().
					getAdditionalInfo()<<std::endl;
	                std::cout<<"\n Enrollment details"<<std::endl;
	        enrollments=student.getEnrollments();
	        if(enrollments.size()==0)
	        {
	        	std::cout<<"No enrollments for the student"<<std::endl;
	        }
	        else
	        {
		        for (const auto& element : enrollments)
		        {
		        	std::cout<<"Grade:" <<element.getGrade()<<
		        			"\n Semester :"<<element.getSemester()<<std::endl;
		        }
	        }

	    }
}

void SimpleUI::searchStudent() {
    std::string searchQuery;
    std::cout << "Enter search query: ";
    std::cin >> searchQuery;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto& students = database.getStudents();
    for (const auto& entry : students) {
        const Student& student = entry.second;
        if (containsSubstring(student.getFirstName(), searchQuery)
        		|| containsSubstring(student.getLastName(), searchQuery)) {
            std::cout << "Matriculation Number: " << entry.first <<
            		"\n First Name: " << student.getFirstName()
                      << "\n Last Name: " << student.getLastName()<<
					  std::endl;
        }
        else
        {
        	std::cout<<"No student found"<<std::endl;
        }
    }
}



bool SimpleUI::containsSubstring(const std::string& str,
		const std::string& substr) const {
    return str.find(substr) != std::string::npos;
}

void SimpleUI::updateStudent() {

	    int matriculationNumber;
	    std::cout << "Enter matriculation number to update student: ";
	    std::cin >> matriculationNumber;
	    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	    auto& students = database.getStudents();
	    auto it = students.find(matriculationNumber);
	    if (it != students.end()) {
	        Student& student = it->second;
	        bool exit = false;
	        while (!exit) {
	        	std::cout << "Select property to update "
	        			"(enter the corresponding number):" << std::endl;
	        	std::cout << "1. First Name\n2. Last Name\n"
	        			"3. Date of Birth\n4. Address\n5."
	        	" Enrollments\n0. Exit update\n";
	        	  int choice;
	        	  std::cin >> choice;
	        	  std::cin.ignore(std::numeric_limits<std::streamsize>
	        	  ::max(), '\n');
	              switch (choice) {
	                  case 1: {
	                      std::string firstName;
	                      std::cout << "Enter new first name: ";
	                      std::cin >> firstName;
	                      std::cin.ignore(std::numeric_limits
	                    		  <std::streamsize>::max(), '\n');
	                      student.setFirstName(firstName);
	                      break;
	                  }
	                  case 2: {
	                      std::string lastName;
	                      std::cout << "Enter new last name: ";
	                      std::cin >> lastName;
	                      std::cin.ignore(std::numeric_limits
	                    		  <std::streamsize>::max(), '\n');
	                      student.setLastName(lastName);
	                      break;
	                  }
	                  case 3: {
	                	    int day, month, year;
	                	    std::cout << "Enter new date of birth"
	                	    		" (DD MM YYYY): ";
	                	    std::cin >> day >> month >> year;
	                	    std::cin.ignore(std::numeric_limits
	                	    		<std::streamsize>::max(), '\n');
	                	    Poco::Data::Date newDateOfBirth(year, month, day);
	                	    student.setDateofBirth(newDateOfBirth);
	                      break;
	                  }
	                  case 4: {
	                	    std::string newStreet, newCityName,
							newAdditionalInfo;
	                	    unsigned short newPostalCode;

	                	    std::cout << "Enter new street: ";
	                	    std::getline(std::cin, newStreet);
	                	    std::cout << "Enter new postal code: ";
	                	    std::cin >> newPostalCode;
	                	    std::cin.ignore(std::numeric_limits
	                	    		<std::streamsize>::max(), '\n');
	                	    std::cout << "Enter new city name: ";
	                	    std::getline(std::cin, newCityName);
	                	    std::cout << "Enter new additional info: ";
	                	    std::getline(std::cin, newAdditionalInfo);

	                	    student.updateAddress(newStreet, newPostalCode,
	                	    		newCityName, newAdditionalInfo);
	                        break;
	                  }
	                  case 5: {

	                //	  student.updateEnrollments();
	                	    if (student.getEnrollments().empty()) {
	                	        std::cout << "No enrollments to update.\n";
	                	        return;
	                	    }

	                	    std::cout << "Enrollments:\n";
	                	    for (size_t i = 0;
	                	    		i < student.getEnrollments().size(); ++i)
	                	    {
	                	        std::cout << i + 1 << ". Grade: "
	                	        		<< student.getEnrollments()[i].
										getGrade() << ", Semester: " <<
										student.getEnrollments()
										[i].getSemester() << "\n";
	                	    }

	                	    std::cout << "Enter the enrollment number"
	                	    		" to update (0 to exit): ";
	                	     int choice;
	                	     std::cin >> choice;

	                	     if (choice > 0 && choice
	                	    		 <= static_cast<int>(student.
	                	    				 getEnrollments().size())) {
	                	         // User chose a valid enrollment
	                	         int enrollmentIndex = choice - 1;

	                	         // Display options for the selected

	                	         std::cout << "1. Update grade\n";
	                	         std::cout << "2. Remove enrollment\n";
	                	         std::cout << "Enter your choice: ";
	                	         int option;
	                	         std::cin >> option;
	                	         switch (option) {
	                	             case 1: {

	                	                 std::cout << "Enter new grade: ";
	                	                 float newGrade;
	                	                 std::cin >> newGrade;
                                         student.updateEnrollments
										 (enrollmentIndex, newGrade);
                                         std::cout << "Grade updated.\n";
                                         break;
	                	             }
	                	             case 2:
	                	             {
	                	            	 student.removeEnrollments
										 (enrollmentIndex);
	                	            	 std::cout << "Enrollment removed.\n";
	                	            	 break;
	                	             }
	                	             default:
	                	                 std::cout << "Invalid option.\n";
	                	                 break;

	                	         }

	                	     }
	                	     break;
	                  }
	                  case 0:
	                      exit = true;
	                      break;
	                  default:
	                      std::cout << "Invalid choice. "
	                    		  "Please try again." << std::endl;
	              }

	          }
	        }

	    else {
	            std::cout << "Student with matriculation number "
	            		<< matriculationNumber << " not found." << std::endl;
	        }
	    }


// Writing database to file part
void SimpleUI::execute_RW_Commands() {
    int choice;
    std::cout << "1. Write to file\n2. Read from file\nEnter your choice: ";
    std::cin >> choice;

    std::string fileName;
    std::cout << "Enter the file name: ";
    std::cin >> fileName;


    switch (choice) {
        case 1:
            writeToFile(fileName, database);
            break;
        case 2:
            readFromFile(fileName, database);
            break;
        default:
            std::cout << "Invalid choice\n";
    }
}


void SimpleUI::writeToFile(const std::string& fileName, StudentDB& database)
{
    std::ofstream outFile(fileName);
    if (!outFile) {
        std::cerr << "Error opening file for writing\n";
        return;
    }
    database.write(outFile);
    std::cout << "Data written to file successfully\n";
}

void SimpleUI::readFromFile(const std::string& fileName, StudentDB& database)
{
    std::ifstream inFile(fileName);
    if (!inFile) {
        std::cerr << "Error opening file for reading\n";
        return;
    }

    database.read(inFile);
    std::cout << "Data read from file successfully\n";
}

SimpleUI::~SimpleUI()
{
}

