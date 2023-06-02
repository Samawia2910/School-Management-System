#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <string.h>
#include <fstream>
#include<conio.h>
#include <sstream>


using namespace std;

void initializeStudents(string codeList[], string nameList[], string RollNoList[], string CourseList[], string ClassList[], string ContactList[], int MAX_STUDENTS);
void initializeUsers(string usernames[], string passwords[], int  MAX_STUDENTS);

//function for data persistent

bool saveStudent(string codeList[], string nameList[], string RollNoList[], string CourseList[], string ClassList[], string ContactList[], int  MAX_STUDENTS );
bool loadStudents(string codeList[], string nameList[],  string RollNoList[], string CourseList[], string ClassList[], string ContactList[], int  MAX_STUDENTS);
bool loadUser(string usersList[], string passwordList[], int  MAX_STUDENTS);


//STUDENT MANAGEMENT

int searchstudentCode(string codeList[], int size, string studentcode);
bool addStudents(string codeList[], string nameList[], string RollNoList[], string CourseList[], string ClassList[], string ContactList[], int MAX_STUDENTS, string studentcode, string studentName, string RollNo, string Course, string Class,string Contact);
void viewStudents(string codeList[], string nameList[], string RollNoList[], string CourseList[], string ClassList[], string ContactList[], int  MAX_STUDENTS);
bool updateStudent(string codeList[], string nameList[], string RollNoList[], string CourseList[], string ClassList[], string ContactList[], int  MAX_STUDENTS, string oldStudentcode, string studentcode, string studentName, string RollNo, string Course, string Class, string Contact);
bool deleteStudent(string codeList[], string nameList[], string RollNoList[], string CourseList[], string ClassList[], string ContactList[], int  MAX_STUDENTS, string studentcode);


//VALIDATION FUNCTIONS

bool isValidStudentCode(string studentcode);
bool isValidRollNo(string RollNo);
bool isValidStudentName(string studentName);
bool isValidCourse(string Course);
bool isValidClass(string Class);
bool isValidContact(string Contact);
bool validateAllData(string studentcode, string studentName,  string RollNo,string Course, string Class, string Contact);

//USER MANAGEMENT

bool userExist(string user[], string pass[], string users, string passs, int  MAX_STUDENTS);
void login(string &userName, string &password);

int main()
{

    //Maximum Size of All arrays
    
    const int MAX_STUDENTS = 10;
    string oldStudentcode;
    bool flag = false;
    string userName;
    string password;
    string studentcode;
    string studentName;
    string RollNo;
    string Course;
	string Class;
	string Contact;
	
    char input;
    
    //Declare All Arrays
    
    string usersList[MAX_STUDENTS], passwordList[MAX_STUDENTS];
    string codeList[MAX_STUDENTS], nameList[MAX_STUDENTS], RollNoList[MAX_STUDENTS], CourseList[MAX_STUDENTS], ClassList[MAX_STUDENTS], ContactList[MAX_STUDENTS];
    
    //Initialize all arrays
    
    initializeStudents(codeList, nameList, RollNoList, CourseList, ClassList, ContactList, MAX_STUDENTS);
    initializeUsers(usersList, passwordList, MAX_STUDENTS);
    
    //This function will load the students in arrays
    
    loadStudents(codeList, nameList,RollNoList, CourseList, ClassList, ContactList, MAX_STUDENTS);

    //This function will load the users in array
    
    loadUser(usersList, passwordList, MAX_STUDENTS);

    //For starting code
    
    login(userName, password);
    
    
    do
    {

        while (userExist(usersList, passwordList, userName, password, MAX_STUDENTS) != true || (userName == "" && password == ""))
        {
            cout << "Incorrect info please reenter username and password" << endl;
            cout << "Enter User name: ";
            cin >> userName;
            cout << "Enter Password: ";
            cin >> password;
            cout << endl;
        }


        if (userExist(usersList, passwordList, userName, password, MAX_STUDENTS))
        {
        
		    cout << "Choose the following option" << endl;
            cout << "1   Add Students" << endl;
            cout << "2   Update Students" << endl;
            cout << "3   Delete Students" << endl;
            cout << "4   View All Students" << endl;
            cout << "5   Logout of the system" << endl;
            cout << "6   Exit Program" << endl;
            cout << "Enter the option: ";
            cin >> input;
            int size;
            switch (input)
            
            {
            	
            	// This case for adding the student details
            	
            case '1':

                cout << "Enter the details of the student (Format: Course Code, Course Name, Roll No, Courses, Class, Contact): ";
                cin >> studentcode;
                cin >> studentName;
                cin >> RollNo;
                cin >> Course;
                cin >> Class;
                cin >> Contact;

                //Check validity of all inputs
                
                if (validateAllData(studentcode, studentName, RollNo, Course, Class, Contact))
                {
                    //Call addStudent function
                    
                    if (addStudents(codeList, nameList, RollNoList, CourseList, ClassList, ContactList, MAX_STUDENTS, studentcode, studentName, RollNo, Course, Class, Contact)==true)
                    {
                        cout << "Student Successfully added" << endl;
                    } 
                    else
                    {
                        cout << "Sorry No space to add new student" << endl;
                    }
            }
            
                else
                {
                    //If any validity is false it will not add the student
                    
                    cout << "Invalid details" << endl;
                }
            

                break;
                
               // This case for Updating the student details
               
            case '2':

                cout << "Enter the student code" << endl;
                cin >> oldStudentcode;

                //check validity of studentCode
                
                if (isValidStudentCode(oldStudentcode))
                
                {
                
                    //Find the index of studentCode which  entered to update the  student details

                cout << "Enter the details of the student (Format: Course Code, Course Name, Roll No, Courses, Class, Contact): ";
                cin >> studentcode;
                cin >> studentName;
                cin >> RollNo;
                cin >> Course;
                cin >> Class;
                cin >> Contact;
                
                // cin.ignore();
                
                // getline(cin, studentName);
                    
                    //Check validity of all details 
                    
                                    
				if (validateAllData(studentcode, studentName, RollNo, Course, Class, Contact))
                     {


                        if (updateStudent(codeList, nameList, RollNoList, CourseList, ClassList, ContactList, MAX_STUDENTS, oldStudentcode ,studentcode, studentName, RollNo,Course, Class, Contact))
                        {
                            cout << "Student successfully updated" << endl;
                        }
                        else
                        {
                            cout << "No student found" << endl;
                        }
                    }
                    else
                    {
                        cout << "Invalid student" << endl;
                }
					}
                    
                    else
                {
                    //here we will show message of not valid student
                    
                    cout << "Invalid student" << endl;
                }

                break;
                
                
                //This case for deleting the student details
                
                case '3':
                	
                cout << "Enter Student code" << endl;
                cin >> studentcode;
                
                //Validate the student code
                
                if (isValidStudentCode(studentcode)==true)
                {
                	
                    //call function to delete the student detail which has same student code as enter
                    
                    if (deleteStudent(codeList, nameList, RollNoList, CourseList, ClassList,ContactList, MAX_STUDENTS, studentcode))
                    
                    {
                        cout << "Student Successfully deleted" << endl;
                    }
                    else
                    {
                        cout << "Sorry No Sudent found " << endl;
                    }
                }
                else
                {
                    //if student code is invalid then this message will show
                    
                    cout << "Invalid Student code" << endl;
                }

                break;
                
				
				 case '4':
				 	
                //View All details of All students
                
                viewStudents(codeList, nameList, RollNoList, CourseList, ClassList, ContactList, MAX_STUDENTS);
                break;
                
                
                // For Closing the Program
                
            case '5':
            	
                if (saveStudent(codeList, nameList, RollNoList, CourseList, ClassList, ContactList, MAX_STUDENTS))
                {
                    cout << "All Students Data Saved successfully" << endl;
                }
                else
                {
                    cout << "All data you entered is lost due to some error" << endl;
                }
                userName = "";
                password = "";
                login(userName, password);
                break;
                //Programed closed
                
                case '6':
                	
                if (saveStudent(codeList, nameList, RollNoList, CourseList, ClassList, ContactList, MAX_STUDENTS))
                {
                    cout << "All Students Data Saved successfully" << endl;
                }
                else
                {
                    cout << "All student you entered is lost due to some error" << endl;
                }
                cout << "Program closed ";
                break;
                
                
            default:
                cout << "Invalid choice";
            }
        }
    
	}
	
	 while (input != '6');

    return 0;
}


void initializeStudents(string codeList[], string nameList[], string RollNoList[], string CourseList[], string ClassList[], string ContactList[], int  MAX_STUDENTS)

{
    for (int s = 0; s < MAX_STUDENTS; s++)
    {
    	codeList[s] = " ";
        nameList[s] = " ";
        RollNoList[s] = " ";
        CourseList[s] = " ";
        ClassList[s] = " ";
        ContactList[s] = " ";
        
        
    }
}

//Function to initilize student in arrays

void initializeUsers(string usernames[], string passwords[], int  MAX_STUDENTS)
{
    for (int s = 0; s < MAX_STUDENTS; s++)
    {
        usernames[s] = " ";
        passwords[s] = " ";
    }
}

//Function to save student in arrays

bool saveStudent( string codeList[], string nameList[], string RollNoList[], string CourseList[], string ClassList[], string ContactList[], int  MAX_STUDENTS)
{
    // This variable for read data from file
    
    ofstream myfile;
    
    /*Open the file if exist if not exist then make new file of this name ios::app means that the new data will append in file and 
	not remove previous content of file */
	
    myfile.open("Students.txt");
    
    //This function will check if the file open then write data from file
    
    if (!myfile.eof())
    {
        for (int i = 0; i < MAX_STUDENTS; i++)
        {
            if (codeList[i] !=" " && nameList[i] != " " && RollNoList[i] != " " && CourseList[i] != " " && ClassList[i] != " " && ContactList[i] !=" ")
            {
                //These lines will write all array data to the file and make a comma separated file
                
                myfile << codeList[i] << ",";
                myfile << nameList[i] << ",";
                myfile << RollNoList[i] << ",";
                myfile << CourseList[i] << ",";
                myfile << ClassList[i] << ",";
				myfile << ContactList[i]<<endl;
            }
        }

        myfile.close();
        return true;
        
    }
    else
    {
        //If there is error while opening file this function will return false
        
        return false;
    }
}


//Function to load student in arrays

bool loadStudents(string codeList[], string nameList[], string RollNoList[], string CourseList[], string ClassList[], string ContactList[], int  MAX_STUDENTS)
{
    int i = 0;
    ifstream getStudent;
    getStudent.open("Students.txt");
        for(int i=0;i<MAX_STUDENTS;i++)
        {
            if(!getStudent.eof())
            {
                getline(getStudent,codeList[i],',');
                getline(getStudent,nameList[i],',');
                getline(getStudent,RollNoList[i],',');
                getline(getStudent,CourseList[i],',');
                getline(getStudent,ClassList[i],',');
                getline(getStudent,ContactList[i],'\n');
            }
        }
        

        getStudent.close();
        return true;
    
}


//Fuunction to read users from file and load then onto the arrays

bool loadUser(string usersList[], string passwordList[], int  MAX_STUDENTS)
{
    int i = 0;
    ifstream getUsers("Users.txt");
    if (!getUsers.is_open())
    {
        cout << "File failed to open" << endl;
        return false;
    }
    else
    {
        string username, password;
        string line;
        while (!getUsers.eof() && i <  MAX_STUDENTS)
        {
            getline(getUsers, line);
            stringstream ss(line);
            getline(ss, username, ',');
            usersList[i] = username;
            getline(ss, password, ',');
            passwordList[i] = password;
            i++;
        }

        getUsers.close();
        return true;
    }
}


//Function to search student in arrays

int searchstudentcode(string codeList[], int  MAX_STUDENTS, string studentcode)
{
    int index = -1;
    for (int i = 0; i <  MAX_STUDENTS; i++)
    {
      
        if (codeList[i] == studentcode)
        {
            index = i;
            break;
        }
    }
    return index;
}

    //This Function Will add the function
    
bool addStudents(string codeList[], string nameList[], string RollNoList[], string CourseList[], string ClassList[], string ContactList[] , int  MAX_STUDENTS, string studentcode, string studentName, string RollNo, string Course, string Class, string Contact )
{
    bool flag = false;
    int i = searchstudentcode(codeList, MAX_STUDENTS, " ");
    if (i != -1)
    {

        codeList[i] = studentcode;
        nameList[i] = studentName;
        RollNoList[i] = RollNo;
        CourseList[i] = Course;
        ClassList[i] = Class;
        ContactList[i] = Contact;
        flag = true;
    }
    return flag;
}


// This Function will display (view) all student details

void viewStudents(string codeList[], string nameList[], string RollNoList[], string CourseList[], string ClassList[], string ContactList[], int  MAX_STUDENTS)
{

    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
    cout << left;
    cout << setw(10) << "Student"
         << setw(50) << "Student"
         << setw(10) << "RollNo"
         << setw(10) << "Course"
		 << setw(10) << "Class"
		 << setw(10) << "Contact" << endl;
    cout << setw(10) << "Code"
         << setw(50) << "Name"
         << setw(10) << "" << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
    for (int i = 0; i <  MAX_STUDENTS; i++)
    {
        if (codeList[i] != " ")
        {

            cout << setw(10) << codeList[i]
                 << setw(50) << nameList[i]
                 << setw(10) << RollNoList[i]
                 << setw(10) << CourseList[i]
				 << setw(10) << ClassList[i]
                 << setw(10) << ContactList[i] << endl;
        }
    }
    cout << endl;
    for (int u = 0; u < 80; u++)
        cout << "-";
    cout << endl;
}


// This function will update the course by using studentCode index which we define as globel varaible

bool updateStudent(string codeList[], string nameList[], string RollNoList[], string CourseList[], string ClassList[], string ContactList[], int  MAX_STUDENTS,string oldStudentcode, string studentcode, string studentName, string RollNo, string Course, string Class, string Contact)
{

    bool flag = false;
    int updateIndex = searchstudentcode(codeList, MAX_STUDENTS, oldStudentcode);
    cout<<"Upate Index "<<updateIndex<<endl;
    if (updateIndex != -1)
     {

        codeList[updateIndex] = studentcode;
        nameList[updateIndex] = studentName;
        RollNoList[updateIndex] = RollNo;
        CourseList[updateIndex] = Course;
        ClassList[updateIndex] = Class;
        ContactList[updateIndex] = Contact;
        flag = true;
    }
    return flag;
}


//This function will delete the course by using studentCode

bool deleteStudent(string codeList[], string nameList[], string RollNoList[], string CourseList[], string ClassList[], string ContactList[], int  MAX_STUDENTS, string studentcode)
{
    bool flag = false;
    int i = searchstudentcode(codeList, MAX_STUDENTS, studentcode);
    if (i != -1)
    {
        codeList[i] = " ";
        nameList[i] = " ";
        RollNoList[i] = " ";
        CourseList[i] = " ";
        ClassList[i] = " ";
        ContactList[i] =" ";
        flag = true;
    }

    return flag;
}


//checking validity of studentcode

bool isValidStudentCode(string studentcode)
{
    int x = studentcode.length();
    bool flag = true;
    if (x == 5)
    {

        for (int i = 0; i < 2; i++)
        {
            if (!((studentcode[i] >= 'a' && studentcode[i] <= 'z') || (studentcode[i] >= 'A' && studentcode[i] <= 'Z')))
            {
                flag = false;
                break;
            }
        }

        for (int i = 2; i < 5 && flag; i++)
        {
            if (!(studentcode[i] >= '0' && studentcode[i] <= '9'))
            {
                flag = false;
                break;
            }
        }
    }

    return flag;
}


//checking studentname

bool isValidStudentName(string studentName)
{
    bool flag = true;
    if (studentName.length() <= 50)
    {
        for (int i = 0; i < studentName.length(); i++)
        {
            if (!((studentName[i] >= 'a' && studentName[i] <= 'z') || (studentName[i] >= 'A' && studentName[i] <= 'Z') || (studentName[i] == ' ')))
                flag = false;
        }
    }
    else
        flag = false;

    return flag;
}


// checking the Roll No

bool isValidRollNo(string RollNo)
{
    bool flag = true;
    int y=RollNo.length();
     for (int i = 0; i < y; i++)
        {
            if (!(RollNo[i] >= '0' && RollNo[i] <= '9'))
            {
                flag = false;
                break;
            }
        }
    return flag;
}


//checking coursename

bool isValidCourse(string Course)
{
    bool flag = true;
    if (Course.length() <= 50)
    {
        for (int i = 0; i < Course.length(); i++)
        {
            if (!((Course[i] >= 'a' && Course[i] <= 'z') || (Course[i] >= 'A' && Course[i] <= 'Z') || (Course[i] == ' ')))
                flag = false;
        }
    }
    else
        flag = false;

    return flag;
}


// Validity for class

bool isValidClass(string Class)
{
     bool flag = true;
     int z=Class.length();
     for (int i = 0; i < z; i++)
        {
            if (!(Class[i] >= '0' && Class[i] <= '9'))
            {
                flag = false;
                break;
            }
        }

    return flag;
}


//Validity for contact

bool isValidContact(string Contact)
{
     bool flag = true;
     int w=Contact.length();
     {
     for (int i = 0; i < w; i++)
        {
            if (!(Contact[i] >= '0' && Contact[i] <= '9'))
            {
                flag = false;
                break;
            }
        }
    }
    return flag;
}


//validate all data

bool validateAllData(string studentcode, string studentName, string RollNo, string Course, string Class, string Contact)
{
    if (!(isValidStudentCode(studentcode) && isValidRollNo(RollNo) && isValidCourse(Course)&& isValidClass(Class) && isValidContact(Contact) && isValidStudentName(studentName)))
    {
        return false;
    }
    return true;
}


//user exist

bool userExist(string user[], string pass[], string users, string passs, int MAX_STUDENTS)
{
    bool flag = false;
    int i;
    for (i = 0; i < MAX_STUDENTS; i++)
    {
        if (user[i] == users && pass[i] == passs)
        {
            flag = true;
            break;
        }
    }

    return flag;
}

//for login

void login(string &userName, string &password)
{

    system("cls");
    cout << endl;
    cout <<"__________________*******************_____________________"<<endl;
	cout <<         "|Welcome to the School Management System| "       <<endl;
	cout <<"__________________*******************_____________________"<<endl;
    cout << "Dear users current software is intended for authorized users only." << endl;
    cout << "Login to the system to get access" << endl;
    cout << "Enter User name: ";
    cin >> userName;
    cout << "Enter Password: ";
    cin >> password;
    cout << endl;
    cout <<"*********************************"<<endl;
	cout <<"Enter in main menu " <<endl;
	cout <<"*********************************"<<endl;
	cout <<endl;
	
}

