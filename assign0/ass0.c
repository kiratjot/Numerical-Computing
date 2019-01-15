/********************************************************************************************************************
 File Name:			     ass0.c
 Versions:				 1.0
 Author:				 Gurkirat Singh
 Student Number:		 040 876 315
 Course Name/Number :    Numerical Computing 18F_CST8233_300
 Lab sect:				 302
 Assignment Name:		 Raster GraphicProject in C
 Assignment #:			 0
 Due Date of assignment: Sept 24, 2018
 Submission Date:		 22 September 2018
 Professor:			     Andrew Tyler
 Purpose:				 The purpose of the assignment is to hold the data of a raster graphic application using
						 a forward list (aka singly-linked list) in dynamic memory for its data. The code is written
						 using C language. The user is prompted with options, to insert, delete and display the
						 the GraphicElements list. When the user quits, the program close leaving behind no memory
						 leaks. Invalid inputs have been handled properly.
********************************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC	// need this to get the line identification
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF); // in main, after local declarations
//NB must be in debug build

#include <crtdbg.h>
#include <stdio.h>
#include <time.h>

typedef enum { FALSE = 0, TRUE } BOOL;

// struct GraphicElement containing the File name, pointer to the next GraphicElement in the list
struct GraphicElement {
	//fileName is a pointer to char
	char* fileName;
	//pNext is a pointer to struct GraphicElement
	struct GraphicElement* pNext;
};

//struct containing the pointer to the struct GraphicElement
struct RasterGraphic {
	struct GraphicElement* GraphicElements;
};

//Function Prototypes
void InitRasterGraphic(struct RasterGraphic*);
void InsertGraphicElement(struct RasterGraphic*);
void DeleteGraphicElement(struct RasterGraphic*);
void ReportRasterGraphic(struct RasterGraphic*);
void CleanUp(struct RasterGraphic*);

/********************************************************************************************************************
Function name:	main
Purpose:	    main function executes the program and display the menu to the user and asks for input. It then checks the
				user input and call appropriate function.
In parameters:  none
Out parameters: 0 for successful execution
Version:        1.0
Author:         Andrew Tyler
********************************************************************************************************************/
int main(void)
{
	char response;
	BOOL RUNNING = TRUE;
	struct RasterGraphic RG;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	InitRasterGraphic(&RG);

	while (RUNNING)
	{
		printf("MENU\n 1. Insert a GraphicElement\n 2. Delete the first GraphicElement\n 3. Report the RasterGraphic\n 4. Quit\n");
		scanf("%c", &response);
		switch (response)
		{
		case '1':InsertGraphicElement(&RG); break;
		case '2':DeleteGraphicElement(&RG); break;
		case '3':ReportRasterGraphic(&RG); break;
		case '4':RUNNING = FALSE; CleanUp(&RG); break;
		default:printf("Please enter a valid option\n");
		}
		printf("\n");
		while ((response = getchar()) != '\n' && response != EOF);// clear input buffer
	}
	return 0;
}

/********************************************************************************************************************
Function name:  InitRasterGraphic
Purpose:		Inititalises the pointer GraphicElements with Null
In parameter:   Address of Struct RasterGraphic
Out parameters: NONE
Version:		1.0
Author:			Gurkirat Singh
********************************************************************************************************************/
void InitRasterGraphic(struct RasterGraphic *ptr) {

	//Inititalising the pointer GraphicElements with Null
	ptr->GraphicElements = NULL;

}

/********************************************************************************************************************
Function name:	InsertGraphicElement
Purpose:		Adding a new GraphicElement to the RasterGraphic at a position selected by the user
In parameter:	Address of Struct RasterGraphic
Out parameters: NONE
Version:		1.0
Author:			Gurkirat Singh
********************************************************************************************************************/
void InsertGraphicElement(struct RasterGraphic* ptr) {

	//counting the number of GraphicElements added
	int count = 1;

	printf("Insert a GraphicElement in the RasterGraphic\n");

	//declaring a pointer to Struct GraphicElement and allocating memory to it
	struct GraphicElement *newElement = malloc(sizeof(*newElement));

	// char array to store the file name
	char Name[256];
	printf("Please enter the GraphicElement filename: ");
	scanf("%s", Name);

	//allocating the memory to store the file name
	newElement->fileName = malloc(sizeof(Name));

	//copying the string pointed to, by Name to fileName
	strcpy(newElement->fileName, Name);

	//checking if the list is empty
	if (ptr->GraphicElements == NULL)
	{
		//pointing the GraphicElements to the new struct
		ptr->GraphicElements = newElement;
		newElement->pNext = NULL;
		printf("This is the first GraphicElement in the list\n");
	}
	else {

		// declaring and initialising Pointer pointing to the first element in the list
		struct GraphicElement * iterator = ptr->GraphicElements;

		//declaring a pointer to keep track of the next element in the list
		struct GraphicElement * nextElement;

		//counting the number of GraphicElements in the list
		while (iterator->pNext != NULL) {
			count++;
			iterator = iterator->pNext;
		}

		printf("There are %d GraphicElement(s) in the list. Please specify the position (<= %d) to insert at : ", count, count);

		//num to store the index where user wants to add the element to the list
		int num = 0;
		scanf("%d", &num);


		//if user wants to add at the beginning
		if (num == 0) {
			newElement->pNext = ptr->GraphicElements;
			ptr->GraphicElements = newElement;
		}

		//checking if the user wants to add at the end of the list
		else if (num == count) {
			newElement->pNext = NULL;
			iterator->pNext = newElement;
		}

		//checking if the user wants to add within the list
		else if (num > 0 && num < count) {
			iterator = ptr->GraphicElements;
			nextElement = iterator->pNext;

			for (int i = 1; i < num; i++) {
				iterator = iterator->pNext;
				nextElement = iterator->pNext;
			}
			iterator->pNext = newElement;
			newElement->pNext = nextElement;
		}

		//printing the error if user put invalid invalid index number
		else {
			printf("Invalid Input. Please try again\n");
			free(newElement->fileName);
			free(newElement);
		}
	}
}

/********************************************************************************************************************
Function name:	DeleteGraphicElement
Purpose:		Delete the first GraphicElement from the RasterGraphic and free the memory allocated to the fileName and
				GraphicElement
In parameter:	Address of Struct RasterGraphic
Out parameters: NONE
Version:		1.0
Author:			Gurkirat Singh
********************************************************************************************************************/
void DeleteGraphicElement(struct RasterGraphic * ptr)
{
	// declaring and initialising the pointer temp to point to the first element in the list
	struct GraphicElement * temp = ptr->GraphicElements;

	//checking if the list is not empty
	if (ptr->GraphicElements != NULL) {
		ptr->GraphicElements = ptr->GraphicElements->pNext;

		//freeing the memory allocated to the pointer fileName
		free(temp->fileName);

		//freeing the memory allocated to the pointer temp
		free(temp);
	}
	//printing the error if the list is empty and user tries to delete
	else printf("There are no elements in the list. Please add and then delete\n");
}

/********************************************************************************************************************
Function name:	ReportRasterGraphic
Purpose:		Display the GraphicElements details one after another at 1 second interval
In parameter:	Address of Struct RasterGraphic
Out parameters: NONE
Version			1.0
Author:			Gurkirat Singh
********************************************************************************************************************/
void ReportRasterGraphic(struct RasterGraphic* pA)
{
	int counter = 0;
	time_t startsec, oldsec, newsec;
	struct GraphicElement* iterator = pA->GraphicElements;

	if (pA->GraphicElements == 0)
	{
		printf("No GraphicElements in the RasterGraphic\n");
		return;
	}
	printf("Report the RasterGraphic\n");
	startsec = oldsec = time(NULL);
	while (iterator)
	{
		newsec = time(NULL);
		if (newsec > oldsec)
		{
			printf("GraphicElement #%d, time = %I64d sec\n", counter++, newsec - startsec);
			printf("Image file name = %s\n", iterator->fileName);
			iterator = iterator->pNext;
			oldsec = newsec;
		}
	}
}

/********************************************************************************************************************
Function name:	ReportRasterGraphic
Purpose:		Free the memory allocated by FileName and GraphicElements
In parameter:	Address of Struct RasterGraphic
Out parameters: NONE
Version:		1.0
Author:			Gurkirat Singh
********************************************************************************************************************/
void CleanUp(struct RasterGraphic * ptr)
{
	//declaring and initialising a pointer to the first GraphicElement in the list
	struct  GraphicElement * temp = ptr->GraphicElements;

	//freeing the memeory allocated if the GraphicElement exists
	while (ptr->GraphicElements != NULL) {
		ptr->GraphicElements = ptr->GraphicElements->pNext;

		//freeing the memory allocated to the pointer fileName
		free(temp->fileName);

		//freeing the memory allocated to the pointer temp
		free(temp);
		temp = ptr->GraphicElements;
	}
}
