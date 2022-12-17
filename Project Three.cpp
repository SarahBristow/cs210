// Sarah Bristow
// CS 210: Programming Languages
// Southern New Hampshire University
// December 11, 2022


#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonFile");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonFile");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonFile");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main()
{
	while (true) {   // Starting while loop for menu
		// Declaring variables
		int userInput;
		int number;
		int x;
		string groceryItem;
		string findItem;
		// Menu for user to choose a number from
		cout << "*********************************************************" << endl;   // Star menu boarder
		cout << "*\t\t\tGrocery Menu\t\t\t*" << endl;    // Menu title
		cout << "*********************************************************" << endl;   // Star menu boarder
		cout << "*\t1: Read number of grocery items from list\t*" << endl;   // Display to user option 1 is for grocery items list
		cout << "*\t2: Search for an item\t\t\t\t*" << endl;  // Display to the user option 2 is to search for an item
		cout << "*\t3: Text-Style Histogram\t\t\t\t*" << endl;  // Display to user option 3 is for the text style histogram
		cout << "*\t4: Exit the program\t\t\t\t*" << endl;  // Display to the user option 4 is to exit the program
		cout << "*********************************************************" << endl << endl;   // Star menu boarder
		cout << "Enter your menu selection: ";   // Telling user to enter the menu number
		cin >> userInput;      // Taking input from user as userInput
		cout << endl << endl;  // Displaying seperation between choice and option they chose
		switch (userInput) {      // Starting swith with userInput
		case 1: {      // Option 1 to read number of items from list
			cout << "Here is the amount of each item from the grocery list:" << endl << endl;  // Telling user this is the grocery list
			CallProcedure("CountNumbers");    // Calling CountNumbers from python file
			cout << endl;   // Adding an extra space between list and menu
			break;   // Break and go back to menu selection
		}
		case 2: {  // Option 2 to find the specific item
			cout << "Enter the item you would like to look for: ";  // Telling the user to enter item name
			cin >> findItem;   // Taking in user input as itemName
			x = callIntFunc("SpecificWord", findItem);   // Calling items from python file
			cout << "The number of " << findItem << " on the list is " << x <<  "." << endl;  // Displaying the item and number of times on list
			cout << endl;   // Display space between output and menu
			break;   // Break and go back to menu selection
		}
		case 3: {  // Option 3 to display histogram
			cout << "*\tHistogram:\t*" << endl << endl;   // Displaying histogram title
			CallProcedure("TextBasedHistogram");    // Calling Python TextBasedHistogram
			ifstream file;  // using ifstream to open file 
			file.open("frequency.dat");   // Opening the frequency.dat written by the Python code
			file >> groceryItem;  // Finding the groceryItem name from file list
			file >> number;   // Finding the number from the file list

			while (!file.eof()) {   // Starting while loop for histogram
				cout << groceryItem << "  ";   // Displaying the grocery item name 

			for (int i = 0; i < number; ++i) {	// Displaying the number provided form the list as a "=" for the histogram
				cout << "\033[36m" << "=";   // Setting the color of the = to blue
			}
			cout << "\033[37m";   // Returning the color back to default white
			cout << endl;  // Displaying a space
			file >> groceryItem;   // Finding the next groceryItem from the file list
			file >> number;   // Finding the next number from the file list
			}
			cout << endl;   // Display space between output and menu
			break;    // break and go back to menu selection
		}
		case 4: {   // Option 4 to exit the program
			cout << "Thank you for using the Grocery Tracking Program! Goodbye." << endl;   // Tell user thanks for using the program
			exit(1);   // End program
		}
		default: {      // Anything else the user inputs
			cout << "Invalid input. Please choose 1, 2, 3, or 4.";      // Display to user input is invalid and to choose 1,2,3, or 4
			cout << endl << endl;     // Adding extra space between output and menu
			break;  // Break and go back to menu selection
			}
		}

	}
}