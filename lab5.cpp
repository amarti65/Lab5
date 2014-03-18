//-------------------------------------------------------------------------------------------------
//Author:	   Jason McMullen and Anthony Martini
//Due Date:    3/6/14
//Program:	   Lab5
//Description: Enhanced lab4 in order to print to file.
//-------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include<cstdlib>
#include <iomanip>

using namespace std;
//Constant to control the maximum number of courses in the array.
const int MAX_ENTRY = 10;

//Constants that will consist of the preapproved course name list. Each course will be later
// We are allowed to use global variables?
const string course1 = "CSC101";
const string course2 = "MTH223";
const string course3 = "ENG105";

//-------------------------------------------------------------------------------------------------
//Function getData: The function will first start out by calling another function to determine,
//					after being prompted, if the amount of courses the user wishes to enter is
//				    possible with the limit imposed on the array before compile. The function will
//				    then prompt the user to enter the course information. The input for the courses
//					has to follow a specific format:
//					YEAR  COURSE  # of STUDENTS   (course will be converted to an int by another
//					function)
//					If there is more room in the array the user will be prompted if they wish to
//					enter more data. If so, then the function will repeat itself. If not, then the
//					function will end.
//
//Precondition:		This function requires the actual array to be sent over so we can modify the
//					contents placed inside. It also will need the variable controlling the amount
//					of courses in the array and the variable that is holding the current index
//					of the array.
//Postcondition:	This function will not be returning anything.
//-------------------------------------------------------------------------------------------------

void getData(ifstream &fin, ofstream &fout, int list [][3], int& numCourses, int index);

//-------------------------------------------------------------------------------------------------
//Function graph: graph will print out the results of each class in a graphical format. The format
//				  will be a bar graph with the y axis as the year and the x axis as the number of
//				  students. The symbol "*" will be used to create the bars on the graph. Each set
//				  of 3 "*" will be a unit of 5 students.
//
//Precondition:   graph requires the ability to read the values store in the array and the length
//				  of the array sent to it to work properly.
//Postcondition:  This function will not return anything.
//-------------------------------------------------------------------------------------------------
void graph(ifstream &fin, ofstream &fout, const int list[][3],int numOfCourses, int numOfClass, string className);

//-------------------------------------------------------------------------------------------------
//Function rangeOfYears: This function will compute and output the range of years that each class
//						 was offered.
//
//Precondition:			 The function requires access to read the values in the array and the
//						 length of the array as well as the amount of courses in the array sent to
//						 it.
//Postcondition:		 This function will not output anything.
//-------------------------------------------------------------------------------------------------
void rangeOfYears(ifstream &fin, ofstream &fout, const int list [][3], int numCourses, int& low, int& high);


//-------------------------------------------------------------------------------------------------
//Function minNumberOfStudents: This function will compute and output the class, out of all that
//								were entered, that had the lowest amount of students in. It will
//								do this by going through each entry in the array and compare all
//								the classes to find the one with the least amount of students in
//								enrolled in it.
//
//Precondition:					This function requires array to be passed so it may read the
//								values stored within. It also will need the length of the array.
//Postcondition:			    This function will not ouput anything.
//-------------------------------------------------------------------------------------------------
void minNumberOfStudents(ifstream &fin, ofstream &fout, const int list[][3], int numCourses);

//-------------------------------------------------------------------------------------------------
//Function maxPerYear: This function will compute and output the class that had the max amount of
//					   students per year. The function will use a for loop to go through every
//					   course looking at only the third position in the second column. The years
//					   will then be examined to determine which course had the most amount of
//					   students enrolled in. The function will the ouput the year, course name,
//					   and the amount of students for that course.
//
//Precondition:		   This function will need the array passed to it so it may read the values
//					   stored within. It will also need the length of the array passed as well.
//Postcondition:       This function will not return anything.
//-------------------------------------------------------------------------------------------------
void maxPerYear(ifstream &fin, ofstream &fout, const int list [][3], int numCourses);

//-------------------------------------------------------------------------------------------------
//Function addMore: This function will prompt the user and inquire if they wish to add more data
//					into the array. This prompt will only occur after it has been verified that
//					theres is sufficient room in the array for more entries. If the user wishes to
//					enter more data then the function will call getData.
//
//Precondition:		This function will require the array, the variable controlling the amount of
//					courses in the array, and the index all to be passed to it.
//Postcondition:    This function will not return anything.
//-------------------------------------------------------------------------------------------------
void addMore(ifstream &fin, ofstream &fout, int list[][3], int numCourses, int index);

//-------------------------------------------------------------------------------------------------
//Function convertCourse: This function will compare an entered string and return an int value
//						  assigned with it. The values have been predetermined wiht each course
//						  title. There will be no error checking in this function. If the user did
//						  not type the course name from the preapproved list then the function
//						  will return a -1 and insert that into the array.
//
//Precondition:			  This function needs the entered string passed for it to compare that
//						  string with a predetermined int value for each one.
//Postcondition:		  This function will return the int value of the course name entered in
//						  order for it to be added to an int array. The values are: CSC101 = 1,
//						  MTH223 = 2, ENG1-5 = 3.
//-------------------------------------------------------------------------------------------------
int convertCourse(string course);

//-------------------------------------------------------------------------------------------------
//Function courseName: This function will convert an integer back into the course title.
//
//Precondition:		   The function requires the indetifing integer sent to it so it can compare it
//					   to the predifined list of courses and turn it back into a string.
//Postcondition:	   This function will return the string containing the course title.
//-------------------------------------------------------------------------------------------------
string courseName(int num);

//-------------------------------------------------------------------------------------------------
//Function printMaxYear:
//
//Precondition:
//Postcondition:
//-------------------------------------------------------------------------------------------------
void printMaxYear(int list[][3], int answerIndex);

void printAsterisks(ifstream &fin, ofstream &fout, int n);
//-------------------------------------------------------------------------------------------------
//Function totalPerCourse: The function will comput and output the total number of students per
//						   course.
//
//Precondition:			   totalPerCourse requires the array (so it may read the values stored
//						   within) and the length of the array.
//Postcondition:		   This function will not return anything.
//-------------------------------------------------------------------------------------------------

void totalPerCourse(ifstream &fin, ofstream &fout, const int list[][3], int numCourses,int numOfClass);

//-------------------------------------------------------------------------------------------------
//Function main: The main function. It will be responsible for running the program and making the
//				 necessary calls to following functions.
//-------------------------------------------------------------------------------------------------
int main()
{
	cout << "Main function has begun."<< endl;

	ifstream fin;
	ofstream fout;
	  fin.open("/Users/copiouscannon/Documents/workspace/Cpp/CSFromFile/infile.txt");
	    if (fin.fail( ))
	    {
	        fout << "Input file opening failed.\n";
	        exit(1);
	    }

	    cout << "[CHECK]The file infile.txt is open."<< endl;

	fout.open("/Users/copiouscannon/Documents/workspace/Cpp/CSFromFile/outfile.txt");
	   if (fout.fail( ))
	   {
		   fout << "Output file opening failed.\n";
		   exit(1);
	   }
		cout << "[CHECK]The output file is open."<< endl;

	//create a new array. Will have to change code to adjust size of array
	int list[MAX_ENTRY][3];

	//initializing both variables to 0 since no courses have been added to the array yet
	//low and high years. i.e. the range of years entered in the array
	int numCourses = 9;
	int index = 0;
	int low, high;

	getData(fin, fout, list, numCourses, index);
	cout << "[CHECK]The Data has been received and input into the two dimentional array."<< endl;

	rangeOfYears(fin, fout, list, numCourses, low, high);
	cout << "[CHECK]The rangeOfYears is calculated."<< endl;

	minNumberOfStudents(fin,fout, list, numCourses);
	cout << "[CHECK]The minNumOfStudents has been found."<< endl;

	graph(fin, fout, list, numCourses,convertCourse(course1), courseName(1));
	graph(fin, fout, list, numCourses,convertCourse(course2), courseName(2));
	graph(fin, fout, list, numCourses,convertCourse(course3), courseName(3));
	cout << "[ ]The graphical representation is completed "<< endl;

	totalPerCourse(fin, fout, list, numCourses, convertCourse(course1));
	totalPerCourse(fin, fout, list, numCourses, convertCourse(course2));
	totalPerCourse(fin, fout, list, numCourses, convertCourse(course3));
	cout << "[CHECK]The totalPerCourse has been found"<< endl;

	maxPerYear(fin, fout, list, numCourses);
	cout << "[CHECK]The maxPerYear has been calculated."<< endl;

	int in;
	fin >> in;

	return 0;

}//end main function

//-------------------------------------------------------------------------------------------------
//Function getData: The function will first start out by calling another function to determine,
//					after being prompted, if the amount of courses the user wishes to enter is
//				    possible with the limit imposed on the array before compile. The function will
//				    then prompt the user to enter the course information. The input for the courses
//					has to follow a specific format:
//					YEAR  COURSE  # of STUDENTS   (course will be converted to an int by another
//					function)
//					If there is more room in the array the user will be prompted if they wish to
//					enter more data. If so, then the function will repeat itself. If not, then the
//					function will end.
//
//Precondition:		This function requires the actual array to be sent over so we can modify the
//					contents placed inside. It also will need the variable controlling the amount
//					of courses in the array and the variable that is holding the current index
//					of the array.
//Postcondition:	This function will not be returning anything.
//-------------------------------------------------------------------------------------------------
void getData(ifstream  &fin, ofstream &fout, int list [][3], int& numCourses, int index)
{
	//loop controlling the enter of data in the 2D array. Index will be updated so if more courses
	//wish to be entered the function will not over-write previously entered data
	double next;
	int i = index;

		//fout << "test inner loop";

		while(! fin.eof())
		{
			for (int j = 0; j < 3; j++)

			{
				if (j != 1)
				{
					fin >> list[i][j];
					//fout << list[i][j];
				}//end if statement
				else
				{
					string course;

					fin >> course;

					int courseID = convertCourse(course);

					list[i][j] = courseID;

				}//end else statement

			}//end nested for loop
			i++;
		}// end while loop
	//ask if user would like to add more entries if there is more room
	addMore(fin,fout,list, numCourses, index);
}//end getData function

//-------------------------------------------------------------------------------------------------
//Function checkRequest: This function will determine if there is enough space left in the array to
//						 allow the user to enter more courses.
//
//Precondition:			 The function requires the entered number of courses to be passed to it. So
//						 it may change its value without having to return anything.
//Postcondition:		 The function will not return anything
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//Function addMore: This function will prompt the user and inquire if they wish to add more data
//					into the array. This prompt will only occur after it has been verified that
//					theres is sufficient room in the array for more entries. If the user wishes to
//					enter more data then the function will call getData.
//
//Precondition:		This function will require the array, the variable controlling the amount of
//					courses in the array, and the index all to be passed to it.
//Postcondition:    This function will not return anything.
//-------------------------------------------------------------------------------------------------
void addMore(ifstream &fin, ofstream &fout, int list[][3], int numCourses, int index)
{

	//variable to determine if the user wants to add more course information
	int answer;

	//check to see if there is room in the array for more courses. If so, then will prompt user
	//asking if they would like to enter more
	if (numCourses < MAX_ENTRY)
	{

		fin >> answer;

		//check to see what they entered
		if (answer == 1)
		{

			getData(fin,fout,list, numCourses, index);

		}//end nested if statement

	}//end if statement

}//end addMore function

//-------------------------------------------------------------------------------------------------
//Function convertCourse: This function will compare an entered string and return an int value
//						  assigned with it. The values have been predetermined wiht each course
//						  title. There will be no error checking in this function. If the user did
//						  not type the course name from the preapproved list then the function
//						  will return a -1 and insert that into the array.
//
//Precondition:			  This function needs the entered string passed for it to compare that
//						  string with a predetermined int value for each one.
//Postcondition:		  This function will return the int value of the course name entered in
//						  order for it to be added to an int array. The values are: CSC101 = 1,
//						  MTH223 = 2, ENG1-5 = 3. The function will return a -1 if the course
//						  entered does not match what it on the predetermined list of courses.
//-------------------------------------------------------------------------------------------------
int convertCourse(string course)
{
	ifstream fin;
	ofstream fout;
	int answer = -1;

	//CSC101
	if (course == course1)
	{

		answer = 1;

	}//end if statement
	//MTH223
	else if (course == course2)
	{

		answer = 2;

	}//end first else
	//ENG105
	else if (course == course3)
	{

		answer = 3;

	}//end last else

	return answer;

}//end convertCourse function

//-------------------------------------------------------------------------------------------------
//Function courseName: This function will convert an integer back into the course title.
//
//Precondition:		   The function requires the indetifing integer sent to it so it can compare it
//					   to the predifined list of courses and turn it back into a string.
//Postcondition:	   This function will return the string containing the course title.
//-------------------------------------------------------------------------------------------------
string courseName(int num)
{
	string answer = " ";

	if (num == 1)
	{

		answer = course1;

	}//end if statement
	else if (num == 2)
	{

		answer = course2;

	}//end else if statment
	else if (num == 3)
	{

		answer = course3;

	}//end else if statement

	return answer;

}//end courseName function

//-------------------------------------------------------------------------------------------------
//Function maxPerYear: This function will compute and output the class that had the max amount of
//					   students per year. The function will use a for loop to go through every
//					   course looking at only the third position in the second column. The years
//					   will then be examined to determine which course had the most amount of
//					   students enrolled in. The function will the ouput the year, course name,
//					   and the amount of students for that course.
//
//Precondition:		   This function will need the array passed to it so it may read the values
//					   stored within. It will also need the length of the array passed as well.
//Postcondition:       This function will not return anything.
//-------------------------------------------------------------------------------------------------
void maxPerYear(ifstream &fin, ofstream &fout, const int list [][3], int numCourses)
{
	int max2012 = list[0][2];
	int index2012 = 0;
	int max2013 = list[0][2];
	int index2013 = 0;
	//for (int i = 0; i < numCourses;i++)
	int i = 0;
	while(! fin.eof())
	{
		if (list[i][2] > max2012 && list[i][0] == 2012)
		{
			max2012 = list[i][2];
			index2012 = i;
		}
		if (list[i][2] > max2013 && list[i][0] == 2013)
		{
			max2013 = list[i][2];
			index2013 = i;
		}
		i++;
	}
	fout << "The courses that had the MAXIMUM number of students for"
			<< courseName(list[index2012][1])
			<< "\n"<< "Max value for 2012 "<< max2012;
		//while(max[i][0]==2013)
			//if (list[i][2] > max)
				//max2013 = list[i][2];
	//The max number of students in 2013 in ENG 105 with 40 students
	fout << "\nThe courses that had the MAXIMUM number of students for"
			<< courseName(list[index2013][1])
			<< "\n" << "Max value for 2012"<< max2013
			<< endl;

	//fout << max;
}//end maxPerYear function

//-------------------------------------------------------------------------------------------------
//Function printMaxYear:
//
//Precondition:
//Postcondition:
//-------------------------------------------------------------------------------------------------
void printMaxYear(int list[][3], int answerIndex)
{
// reverse logic of the minimum.
	//int answer = list[][2]
	//int answerIndex =0
	ifstream fin;
	ofstream fout;

	fout << "In "
		<< list[answerIndex][0]
		 << " the max number of students is in "
		 << courseName(list[answerIndex][1])
		 << " with "
		 << list[answerIndex][2]
		 << " students"
		 << endl;

}//end printMaxYear function

//-------------------------------------------------------------------------------------------------
//Function minNumberOfStudents: This function will compute and output the class, out of all that
//								were entered, that had the lowest amount of students in. It will
//								do this by going through each entry in the array and compare all
//								the classes to find the one with the least amount of students in
//								enrolled in it.
//
//Precondition:					This function requires array to be passed so it may read the
//								values stored within. It also will need the length of the array.
//Postcondition:			    This function will not ouput anything.
//-------------------------------------------------------------------------------------------------
void minNumberOfStudents(ifstream &fin, ofstream &fout, const int list [][3], int numCourses)
{
	int answer = list[0][2];
	int answerIndex = 0;

	for (int i = 0; i < numCourses; i++)
	{

		int numStudents = list[i][2];

		if (numStudents <= answer)
		{

			answer = numStudents;
			answerIndex = i;

		}//end if statements

	}//end for loop

	fout << "The course with the MINIMUM number of students was in "
		 << list[answerIndex][0]
		 << " "
		 << courseName(list[answerIndex][1])
		 << " with "
		 << list[answerIndex][2]
		 << " students"
		 << endl;

}//end minNumberOfStudents function

//-------------------------------------------------------------------------------------------------
//Function rangeOfYears: This function will compute and output the range of years that each class
//						 was offered.
//
//Precondition:			 The function requires access to read the values in the array and the
//						 length of the array as well as the amount of courses in the array sent to
//						 it.
//Postcondition:		 This function will not output anything.
//-------------------------------------------------------------------------------------------------
void rangeOfYears(ifstream &fin ,ofstream &fout, const int list [][3], int numCourses, int& low, int& high)
{

	low = list[0][0];
	high = list[0][0];

	for (int i = 0; i < numCourses; i++)
	{

		int year = list[i][0];

		if (low >= year)
		{

			low = list[i][0];

		}//end if statement

		if (high <= year)
		{
			high = list[i][0];

		}//end if statment

	}//end for loop
}//end rangeOfYears function

void graph(ifstream &fin, ofstream &fout, const int list[][3],int numOfCourses, int numOfClass,string className)
{
	int j = 0;
	fout <<  className <<"\n\t |" << "\n\t |" << "\n2012  \t |";
	//int i = 0;
//	while(!fin.eof())
	for (int i = 0;i < 9; i++)
	{

		if ((list[i][1] == numOfClass))
		{
			if(j==0)
			{
				printAsterisks(fin, fout, list[i][2]);
				fout << "\n\t | ";
			}
			if(j==1)
			{
				fout << "\n2013  \t |";
				printAsterisks(fin, fout, list[i][2]);
			}
			if (j==2)
			{
				fout << "\n2014  \t |";
				printAsterisks(fin, fout, list[i][2]);
				fout <<"\n\t |__________________________________________________" << endl;

				if (i = numOfCourses)
				{
					fout << "\n\t  ____5___10___15___20___25___30___35___40___45___50\n";
				}
			}
			j++;
			fout << "";
		}

	}
}//end graph
//Prints n asterisks to the screen .

void printAsterisks(ifstream &fin, ofstream &fout,int n)
 {
	int count = 1;
	for ( int count = 1; count <= n; count++)
	{
		fout << "*";
	}

 }
void totalPerCourse(ifstream &fin, ofstream &fout, const int list[][3], int numCourses,int numOfClass)
{
	switch (numOfClass)
		{
		case 1 : fout << "\nCSC101 had ";
					break;
		case 2 : fout <<  "\nMTH223 had ";
					break;
		case 3 : fout <<  "\nENG105 had ";
					break;
		default:    break;
		}
	int j = 0;
	int total = 0;
	int newTotal = 0;
		for (int i = 0;i <= numCourses; i++)
		{
			if (list[i][1] == numOfClass)
			{
					total =(list[i][2]);
					newTotal+= total;
			}
		}
	fout << newTotal << " students\n";
}
