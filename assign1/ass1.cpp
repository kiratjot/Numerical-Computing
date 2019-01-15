/********************************************************************************************************************
File Name:			     ass1.cpp
Versions:				 1.0
Author:				     Gurkirat Singh
Student Number:			 040 876 315
Course Name/Number :     Numerical Computing 18F_CST8233_300
Lab sect:				 302
Assignment Name:		 Catenary Function
Assignment #:			 1
Due Date of assignment:  Oct 14, 2018
Submission Date:		 Oct 12, 2018
Professor:			     Andrew Tyler
Purpose:				 Investigate a Maclaurin series approximation to the Catenary function.
********************************************************************************************************************/

#include<iostream>
#include <iomanip>
using namespace std;

/********************************************************************************************************************
Function name:  print
Purpose:		This function asks the user for the highest power, range and scale factor for the series and then
				calculates the x value, series, exact value, exact % error and trunc % error. After calculation is
				done, the values are diplayed on the screen. The function also checks if the user puts invalid input.
In parameter:   NONE
Out parameters: NONE
Version:		1.0
Author:			Gurkirat Singh
********************************************************************************************************************/
void print()
{
	// int to store the highest power
	int power;

	// double variable to store the range of value of x, scale factor and value of x itself
	double lowX, highX, scaleF, x;

	//variable to store the  value of x after increment
	double valueX;

	//variable to store the value of series after calculations
	double seriesV;

	cout << "        EVALUATING THE CATENARY SERIES APPROXIMATION\n\n";

	//asking the user to provide the highest power of x. If user enters invalid input, the user gets the prompt again.
	do {
	cout << "Please enter the highest power of x in the catenary series (0, 2, 4, 6, 8, or 10): ";
	cin >> power; 	//getting the value of highest power
   }while ((power%2 != 0) || power < 0 || power > 10);

   cout << "\n        CHOOSE THE RANGE OF EVALUATION - low x to high x";

   //asking the user to provide the minimum value of x. If user enters invalid input, the user gets the prompt again.
   do
   {
	   cout << "\nPlease enter low x - in the range -10.0 to 0.0: ";
	   cin >> lowX; //getting the value of min value of x
   } while (lowX<-10.0 || lowX>0.0);

   //asking the user to provide the max value of x. If user enters invalid input, the user gets the prompt again.
   do
   {
	   cout << "Please enter high x - in the range 0.0 to +10.0: ";
	   cin >> highX; //getting the value of max value of x
   } while (highX<0.0 || highX > 10.0);

   //asking the user to provide the scale factor. If user enters invalid input, the user gets the prompt again.
   do
   {
	   cout << "\nPlease enter the scale factor the range 0.0 to +10.0: ";
	   cin >> scaleF; //getting the value of scale factor
   } while (scaleF <0.0 || scaleF >10.0);

	cout << "\nCATENARY SERIES TO x^" << power << " from x = " << fixed << setprecision(6) << lowX << " to x = " << highX << "\n";
	cout << setprecision(5);

	// variable to store the increment value
	double diff = (highX - lowX) / 10;

	/**variables to store the Exact value of the series, tempSeries to store the value temporarily, truncTerm to store
	the value of truncated series */
	double ExactV = 0, tempSeries = 0, truncTerm = 0;

	cout << "  x          Series           Exact         Exact % Error            Trunc. % Error\n";

	//for loop to print the series 11 times
	for (int x = 0; x <= 10; x++)
	{

		//Calculating the new value of x everytime and incrementing it.
		valueX = lowX + (x*diff);

		 seriesV = 0;

		//value to be used as x in the series
		double realX = valueX / scaleF;

		//calculating the exact value of the series by using the the library function exp()
		ExactV = ((scaleF / 2) * (exp(valueX / scaleF) + exp(-valueX / scaleF)));

		//calculating the series and adding up the value until we reach the highest power enterred by the user
		for (int sPower = 0; sPower <= power; sPower = sPower + 2)
		{
			//calculting the value of the series and truncated term if power is 0
			if (sPower == 0)
			{
				tempSeries = 1;
				truncTerm = (realX * realX) / 2;
			}

			//calculting the value of the series and truncated term if power is 2
			else if (sPower == 2)
			{
					tempSeries = (realX * realX) / 2;
					truncTerm = (realX * realX *realX * realX) / 24;
			}

			//calculting the value of the series and truncated term if power is 4
			else if (sPower == 4)
			{
				tempSeries = (realX * realX *realX * realX) / 24;
				truncTerm = (realX * realX * realX * realX * realX * realX) / 720;
			}

			//calculting the value of the series and truncated term if power is 6
			else if (sPower == 6)
			{
				tempSeries = (realX * realX * realX * realX * realX * realX) / 720;
				truncTerm = (realX * realX * realX * realX * realX * realX * realX * realX) / 40320;
			}

			//calculting the value of the series and truncated term if power is 8
			else if (sPower == 8)
			{
				tempSeries = (realX * realX * realX * realX * realX * realX * realX * realX) / 40320;
				truncTerm = (realX * realX * realX * realX * realX * realX * realX * realX * realX * realX) / 3628800;
			}

			//calculting the value of the series and truncated term if power is 10
			else if (sPower == 10)
			{
				tempSeries = (realX * realX * realX * realX * realX * realX * realX * realX * realX * realX) / 3628800;
				truncTerm = (realX * realX * realX * realX * realX * realX * realX * realX * realX * realX * realX * realX) / 479001600;
			}

			//Calculating the series value by adding up the value obtained from each power of the x
			seriesV = seriesV + tempSeries;
		}

		//printing the value of the x by setting up the precision and in scientific notation
		cout << showpos << scientific<< setprecision(3) << valueX;

		//calculating and printing the value of the series by setting up the precision and multiplying with the scale factor
		cout << "   " << noshowpos << setprecision(5) << seriesV*scaleF;

		//printing the exact value of the series by setting up the precision
		cout << "      " << ExactV;

		//calculating and printing the value of the Exact % Error by setting up the precision
		cout << "         " << 100 * (ExactV - (seriesV*scaleF)) / ExactV;

		//calculating and printing the value of the Trunc % Error by setting up the precision
		cout << "            " << 100 * truncTerm / seriesV << endl;
	}
}


/********************************************************************************************************************
Function name:	main
Purpose:	    main function executes the program and display the menu to the user and asks for input. It then checks the
				user input and call appropriate function.
In parameters:  none
Out parameters: 0 for successful execution
Version:        1.0
Author:         Gurkirat Singh
********************************************************************************************************************/
int main()
{
	// int variable to get the user input
	int input;

	//while loop to display the menu again intil the user wishes to quit
	while (true)
	{
		cout <<endl<< "**********************************"<<endl<<"        Catenary Series" << endl << "1. Evaluate the function" << endl << "2. Quit\n**********************************"<<endl;

		//getting the user input
		cin >> input;

		if (input == 1)
		{
			//calling the print function if user wishes to calculate the series
			print();
		}
		else if (input == 2) {

			//breaking the loop if user wishes to quit
			break;
		}
		else
		{
			//Telling the user if invalid input has been enterred
			cout << "Invalid input. Please enter a valid number." << endl<<endl;
		}
	}
	return 0;
}