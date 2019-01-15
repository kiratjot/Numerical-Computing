/********************************************************************************************************************
File Name:			     ass2.cpp
Versions:				 1.0
Author:				     Gurkirat Singh
Student Number:			 040 876 315
Course Name/Number :     Numerical Computing 18F_CST8233_300
Lab sect:				 302
Assignment Name:		 Linear Regression Fit to Data
Assignment #:			 2
Due Date of assignment:  Nov 11, 2018
Submission Date:		 Nov 11, 2018
Professor:			     Andrew Tyler
Purpose:				 Fit data using linear regression least squares method for both a Linear function
and a Power Law function.
********************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include<iostream>
#include <iomanip>
#include <fstream>

#include <string>
#include <math.h>
#include <vector>

using namespace std;

//Function Prototypes
void calculateLinear(int);

/********************************************************************************************************************
Function name:  calculateLinear
Purpose:		This function does the main calculation based on the user's input. Both the calculations for the
Linear function and a Power Law function is done here. Also, the nterpolated/extrapolated levels are
calculated in this function. The function then output the result to the user.
In parameter:   option
Out parameters: NONE
Version:		1.0
Author:			Gurkirat Singh
********************************************************************************************************************/
void calculateLinear(int option)
{
	//declaring a variable to read the file
	ifstream dataIn;

	//variable to store the fileName for input
	char fileName[256];

	//declaring vector of type float to store the values
	vector<float> X, Y;

	//float variable to get the input from the file
	float x, y;

	//declaring variables to count the line and for use in for loop
	int lines = 0 ;

	int S; //declaring variable to store the value of number of lines
	float Sx = 0; // variable to store the value of summation of value of x
	float Sy = 0; // variable to store the value of summation of value of y
	float Sxx = 0; // variable to store the value of summation of value of x^2
	float Sxy = 0; // variable to store the value of summation of value of x*y
	float delta, m, c; // variable to store the value of delta, m, c

	int menu; //variable to store the user input
	float input; //variable to store the year where user wants to Interpolate/Extrapolate

				 //getting the file name from the user
	cout << "Please enter the name of the file to open: ";
	cin >> fileName;

	//opening the file
	dataIn.open(fileName);

	//checking if the file exists
	if (dataIn.good())
	{
		//storing the values of file till the it reaches the end of file
		while ((dataIn >> x) && (dataIn >> y))
		{
			//checking if user wants to calcluate Power Law function
			if (option == 2)
			{
				X.push_back(log(x));
				Y.push_back(log(y));
			}
			else
			{
				X.push_back(x);
				Y.push_back(y);
			}

			//incrementing the line count
			lines++;
		}
	}
	else
	{ //Prompting the user if cannot open the file
		cout << "Error: Cannot open the file" << endl;
		return;
	}

	//closing the file
	dataIn.close();

	//printing the total number of lines
	cout << "There are " << lines << " records" << endl;

	//storing the number of lines
	S = lines;

	//calculating the value of summation of all the values of x
	for (unsigned i = 0; i < X.size(); i++)
	{
		Sx += X.at(i);
	}

	//calculating the value of summation of all the values of y
	for (unsigned i = 0; i < Y.size(); i++)
	{
		Sy += Y.at(i);
	}

	//calculating the value of summation of all the values of x^2
	for (unsigned i = 0; i < X.size(); i++)
	{
		Sxx += pow(X.at(i), 2);
	}

	//calculating the value of summation of all the values of x*y
	for (unsigned i = 0; i < X.size(); i++)
	{
		Sxy += (X.at(i))*(Y.at(i));
	}

	//calculatind the delta value
	delta = (S *Sxx) - (Sx*Sx);

	//calcluating the m value
	m = ((S*Sxy) - (Sx*Sy)) / delta;

	//calculating the c value
	c = ((Sxx*Sy) - (Sx*Sxy)) / delta;

	// priniting the equation based on the users choice of function
	if (option == 2)
		cout << "y = " << setprecision(2) << exp(c) << "x^" << m << endl;
	else
		cout << "y = " << setprecision(3) << m << "*x + " << c << endl;

	//while loop to display the menu again until the user wishes to go to the Main menu
	while (true)
	{

		//getting the input from the user
		cout << "MENU\n 1. Interpolate/Extrapolate\n 2. Main Menu\n ";
		cin >> menu;

		//If user wishes to return to the main menu
		if (menu == 2)
			break;

		//getting the year value to interpolate / extrapolate.
		cout << "Please enter the year to interpolate / extrapolate to : ";
		cin >> input;

		//calculating the final value based on the user choice of the function
		if (option == 1)
		     //if the function was linear
			cout << "The linear interpolated/extrapolated CO2 level in the year " << fixed << setprecision(1) << input << " is " << setprecision(2) << ((m*(input - 1960)) + c) + 316.5 << endl;
		else //if power la function is used
			cout << "The power law interpolated/extrapolated CO2 level in the year " << fixed << setprecision(1) << input << " is " << setprecision(2) << (exp(c)*(pow((input - 1960), m))) + 316.5 << endl;
	}
}

/********************************************************************************************************************
Function name:	main
Purpose:	    main function executes the program and display the menu to the user and asks for input. It then checks
the user input and call appropriate function.
In parameters:  none
Out parameters: 0 for successful execution
Version:        1.0
Author:         Gurkirat Singh
********************************************************************************************************************/
int main()
{
	// int variable to get the user input
	int option;

	cout << "			LEAST_SQUARES LINEAR REGRESSION" << endl;

	//while loop to display the menu again intil the user wishes to quit
	while (true)
	{
		cout << "MENU\n 1. Linear Fit\n 2. Power Law Fit\n 3. Quit" << endl;

		//getting the user input
		cin >> option;

		if (option == 1 || option == 2)
		{
			//calling the function to proceed and calculate the result
			calculateLinear(option);
		}

		else if (option == 3)
		{
			//breaking the loop if user wishes to quit
			break;
		}
		else
		{
			//Telling the user if invalid input has been enterred
			cout << "Invalid input. Please enter a valid number." << endl << endl;
		}
	}

	return 0;
}


