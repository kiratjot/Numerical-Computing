/********************************************************************************************************************
File Name:			     ass3.cpp
Versions:				 1.0
Author:				     Gurkirat Singh
Student Number:			 040 876 315
Course Name/Number :     Numerical Computing 18F_CST8233_300
Lab sect:				 302
Assignment Name:		 Martian Lander
Assignment #:			 3
Due Date of assignment:  Dec 2, 2018
Submission Date:		 Dec 2, 2018
Professor:			     Andrew Tyler
Purpose:				 Solve Ordinary differential Equations (ODEs) in real-time for a planetary lander flight
						 simulator
********************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include<iostream>
#include <conio.h>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

// int variable to track the total numbers fo players
int totalPlayers = 0;

//struct to hold the record of individual player
struct MyStruct
{
	string name;	//string to hold the player name
	int bounce;		//int to store the total bounce
	int min;		//to store the minutes
	int sec;		// to store the secinds
	int milli_S;	//to store the milli secinds
};

// declaring a vector of type MyStruct to hold the players records
vector<MyStruct> scores;

/********************************************************************************************************************
Function name:  compare
Purpose:		This function is used to sort the players based on their number of bounces and time taken for landing
In parameter:   lhs, rhs
Out parameters: True / False
Version:		1.0
Author:			Gurkirat Singh
********************************************************************************************************************/
bool compare(MyStruct lhs, MyStruct rhs)
{
	//if the bounce are not same, return true for lower bounces
	if (lhs.bounce != rhs.bounce)
		return lhs.bounce < rhs.bounce;

	//if the minutes are not same, return true for lower minutes
	if (lhs.min != rhs.min)
		return lhs.min < rhs.min;

	//if the seconds are not same, return true for lower seconds
	if (lhs.sec != rhs.sec)
		return lhs.sec < rhs.sec;

	//return true for lower milli seconds
	return lhs.milli_S < rhs.milli_S;
}

/********************************************************************************************************************
Function name:  score
Purpose:		This function is responsible for printing the scoreboard and writing the results into the file
In parameter:   bounce, min, sec, milli_s
Out parameters: NONE
Version:		1.0
Author:			Gurkirat Singh
********************************************************************************************************************/
void score(int bounce, int min, int sec, int milli_S)
{
	MyStruct result; 	//declaring an object of MyStruct
	string fileName; 	//string to hold the file name
	string  name;       //string to hold the player name
	ofstream myfile; 	//ofstram object for file input/output

	//asking the player name
	cout << "Enter your name: ";
	cin >> name;

	//asking user the filename
	cout << "Enter the file name to store the results in (make sure the file exists, eg file.txt): ";
	cin >> fileName;

	//opening the file
	myfile.open(fileName);

	result.name = name; 		//assinging the name of the player
	result.bounce = bounce;		//assinging the bounces of the player
	result.min = min; 		    //assinging the min duration of the player
	result.sec = sec;	        //assinging the seconds duration of the player
	result.milli_S = milli_S; 	//assinging the milli seconds duration of the player

	scores.push_back(result);	//adding the struct object to the vector list

	totalPlayers++;				//incrementing the total number of players

	//calling the sort function to sort out the players based on the bounces and time
	sort(scores.begin(), scores.end(), compare);

	//printing and writing thescores on the file
	cout << "\n*************SCORE CARD*************"<< endl;
	myfile<< "\n*************SCORE CARD*************" << endl;

	for (int i = 0; i < scores.size(); i++)
	{
		cout <<i+1<<". Name: "<< scores[i].name << "\n		Bounce: " << scores[i].bounce << "			Time: " << setprecision(0) << scores[i].min << ":" << scores[i].sec << ":" << scores[i].milli_S << endl;
		myfile << i + 1 << ". Name: " << scores[i].name << "\n		Bounce: " << scores[i].bounce << "			Time: " << setprecision(0) << scores[i].min << ":" << scores[i].sec << ":" << scores[i].milli_S << endl;
	}
	myfile.close(); //closing the file
}

/********************************************************************************************************************
Function name:  simulation
Purpose:		This function performs all the neccessary calculations for the lander. The velocity is calculated
				using Heun's method. Calculating the velocity v and position x of the module as time t (seconds) passes
				after it starts its descent from an initial location 1000 meters above the Martian surface at the
				instant of being released from the mother ship
In parameter:   NONE
Out parameters: NONE
Version:		1.0
Author:			Gurkirat Singh
********************************************************************************************************************/
void simulation()
{
	double dvt = 0;						//variable to store the value at the step start
	double c = 0.13;					//assigning the constant value
	double a = 8.3;						//assigning the constant value
	double g = 3.7;						//assigning the constant value
	double vmax = 46;					//assigning the constant value
	double v = 0;						//variable to store the corrected velocity
	double prev_v = 0;					//variable to store the previous velocity
	double height = 1000;				//variable to store the height
	double vdash = 0;					//variable to store the predicted value
	double gdash = 0;					//variable to store the derivative at the step end
	double deltaSpeed = 0;				//variable to store the change in velocity in every loop
	int bounce = 0;						//variable to store the total number of bounces
	int time_e = 0;						//variable to store the millisecinds
	char ch ='p';						//variable to store the key pressed
	int min, sec;						//variable to store the minutes and seconds
	double burnReserve = 100;			//variable to store the total reserve
	double burn = 0;					//variable to store the burn value
	double burnReserveDisp = 0;			//variable to store the value of remaning burn
	double deltaTime = 0;				//variable to store the differnece of milliseconds from the previous to current loop
	clock_t curr_time, prev_time = 0;	//variables of type clock_t to calculate the time
	clock_t base_time = clock();		//variables of type clock_t to calculate the time
	while (1)
	{
		curr_time = clock() - base_time;								//calculating the total milli secinds
		deltaTime = (curr_time - prev_time);							//calculting the differnece of milliseconds from the previous to current loop
		prev_time = curr_time;
		min = (int) (curr_time*0.001) / 60;								//calculting minutes
		sec = (int) curr_time*0.001 - (min * 60);						//calculating the seconds
		time_e = (int) (curr_time - ((int) (curr_time*0.001) * 1000));	//calculating the millisecinds

		//checking if the user pressed nay keyboard key
		if (_kbhit())
		{
			ch = _getch();

			//if user pressed w
			if (ch == 'w')
			{
				burn++;
			}

			//if user pressed e
			else if (ch == 'e')
			{
				if (burn > 0)
				{
					burn--;
				}
			}
		}
		if (ch == 'w')	//if user pressed w
		{
			system("cls");
			cout << "W was pressed - increase burn";
		}
		else if (ch == 'e') //if user pressed e
		{
			system("cls");
			cout << "E was pressed - decrease burn";
		}
		else

			cout << "*************************STARTING DESCENT*************************\n";

		if (burnReserve > 0) //calcuting the burn left
			burnReserve = burnReserve - (burn*(deltaTime / 1000));
		else
		{ //if no more burn is possible
			burn = 0;
		}
		if (burnReserve < 0) //checking if burn is empty
			burnReserve = 0;
		if (burn < 0) //checking if user dont click E if burn is 0
			burn = 0;

		//using heun's method
		dvt = g - (c *(v + a*pow((v / vmax), 3))) - burn;
		vdash = v + ((dvt)*(deltaTime / 1000)); //predicted velocity
		gdash = g - (c *(vdash + a*pow((vdash / vmax), 3))) - burn;
		v = v + ((dvt + gdash) / 2)*(deltaTime / 1000); //corrected velocity

		height = height - ((v + prev_v) / 2) * (deltaTime / 1000); //remaining height

		if (height <= 0) //checking the bounce
		{
			if (v > 1)
			{
				bounce++;
				v *= -1;
			}
		}

		//checking if its the time to land
		if (v < 1 && v > -1 && height <= 1)
		{
			system("cls");
			cout << "LANDING SUCCESFUL !!!!" << endl;
			score(bounce, min, sec, time_e); //calling the score function to print the results
			break;
		}
		prev_v = v;

		//printing the values of the variables including time, burn, speed,height
		cout << ": BURN = " << setprecision(3) << fixed << burn << " ; BURN RESERVE = " << burnReserve << "\n";
		cout << "MINUTE = " << min << "; SECOND = " << sec << "; MILLISECOND = " << time_e << "\n";
		cout << "SPEED OF DESCENT = " << v << "m/s\n";
		cout << "HEIGHT ABOVE MARTIAN SURFACE = " << height << "metres\n";
		cout << "NUMBER OF BOUNCES = " << bounce << "\n";
		system("cls");//clearing the screen
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

	cout << "*************** Martian Lander ***************" << endl;

	//while loop to display the menu again intil the user wishes to quit
	while (true)
	{
		cout << "\nMENU\n 1. Run the simulation\n 2. Quit" << endl;

		//getting the user input
		cin >> option;

		if (option == 1)
		{
			//calling the function to proceed and calculate the result
			simulation();
		}

		else if (option == 2)
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
