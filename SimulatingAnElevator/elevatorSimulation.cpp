/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Kamen Ivanov
* @idnumber 61894
* @task 2
* @compiler VC
*
*/

#include "stdafx.h"
#include<iostream>
#include<fstream>	//ifstream
#include<exception>	
#include<cmath>		//abs()
#include "stack.h"
#include "linkedList.h"

using namespace std;
using namespace::fmi::sdp;


typedef int floor_t;
typedef double seconds_t;
typedef double floorsPerSecond_t;

#define INTERNAL true
#define EXTERNAL false

#define UP true
#define DOWN false

struct ElevatorRequest
{
	seconds_t callTime;
	floor_t floor;
	bool type;
	bool direction;
};

const floorsPerSecond_t elevatorSpeed = 0.2;

const seconds_t requiredTimeForStoppingOnAFloor = 0.0;

//calculates at which time the elevator will arrive from the
//initial floor to the final floor
seconds_t getExpectedTimeOfArrival(const seconds_t timeOfSimulation, floor_t initialFloor, floor_t finalFloor)
{
	seconds_t travelTime = abs(finalFloor - initialFloor) / elevatorSpeed;
	return timeOfSimulation + travelTime;
}

//checks if two times are equal
static bool areEqual(const seconds_t time1, const seconds_t time2)
{
	const seconds_t tolerance = 1e-6;
	return abs(time1 - time2) < tolerance;
}

//this function pops the first request in the stack and executes
//it, by updating the values of
//elevatorLocationFloor, timeOfSimulation and elevatorDirection
//we assume that the stack isn't empty!!!
static void executeRequest(Stack<ElevatorRequest>& elevatorRequestsStack
	, floor_t &elevatorLocationFloor
	, seconds_t &timeOfSimulation
	, bool &elevatorDirection)
		{
			ElevatorRequest requestWhichIsExecuted = elevatorRequestsStack.pop();

			//we update the value of timeOfSimulation
			timeOfSimulation =
				getExpectedTimeOfArrival(timeOfSimulation, elevatorLocationFloor, requestWhichIsExecuted.floor);

			if (elevatorLocationFloor < requestWhichIsExecuted.floor)
				elevatorDirection = UP;
			else
			{
				if (elevatorLocationFloor > requestWhichIsExecuted.floor)
					elevatorDirection = DOWN;
			}

			//we update the value of the elevator location floor
			elevatorLocationFloor = requestWhichIsExecuted.floor;

			cout << timeOfSimulation << ' ' << elevatorLocationFloor << ' ';
			if (elevatorDirection == UP)
				cout << "up";
			else
				cout << "down";

			cout << endl;

			timeOfSimulation += requiredTimeForStoppingOnAFloor;
		}


//If there is a more important request in the list than the
//last request in the stack, we pop it from the list
//and push in on the stack.
//We assume that the stack isn't empty!!!
static void findMoreImportantRequestsAndPushThemInStack
	(
	LinkedList<ElevatorRequest>& elevatorRequestsList
	, Stack<ElevatorRequest>& elevatorRequestsStack
	, const floor_t elevatorLocationFloor
	, const seconds_t timeOfSimulation
	)
{
	ElevatorRequest lastRequestPushedInTheStack = elevatorRequestsStack.peek();

	seconds_t expectedTimeOfArrivalToTheLastRequestInStack = getExpectedTimeOfArrival
		(timeOfSimulation, elevatorLocationFloor, lastRequestPushedInTheStack.floor);

	seconds_t expectedTimeOfArrivalToTheCurrentRequest;

	//this iterator will be used to scan the requests in the list one by one
	LinkedList<ElevatorRequest>::Iterator it = elevatorRequestsList.beginIterator();

	//we scan the list to find a more important request than the last one in the stack
	while (it != elevatorRequestsList.endIterator())
	{
		if (it->callTime >= expectedTimeOfArrivalToTheLastRequestInStack)
			break;

		expectedTimeOfArrivalToTheCurrentRequest = getExpectedTimeOfArrival
			(timeOfSimulation, elevatorLocationFloor, it->floor);

		//if the current request is more important
		//than the last one pushed in the stack
		if (
			(it->floor < lastRequestPushedInTheStack.floor
			&&
			elevatorLocationFloor <= it->floor
			||
			it->floor > lastRequestPushedInTheStack.floor
			&&
			elevatorLocationFloor >= it->floor)
			&&
			(it->callTime < expectedTimeOfArrivalToTheCurrentRequest
			||
			areEqual(it->callTime, expectedTimeOfArrivalToTheCurrentRequest))
			)

		{
			elevatorRequestsStack.push(*it);
			lastRequestPushedInTheStack = *it;

			expectedTimeOfArrivalToTheLastRequestInStack
				= expectedTimeOfArrivalToTheCurrentRequest;

			it.remove();

			//we'll continue the process of searching for
			//more important requests in the list
			//until there are no more such requests
			it = elevatorRequestsList.beginIterator();
			continue;
		}
		++it;
	}
}

//this function executes all elevator requests in the list
static void executeElevatorRequests(LinkedList<ElevatorRequest>& elevatorRequestsList)
{
	//In the beginning the elevator is on the first floor
	floor_t elevatorLocationFloor = 1;

	//In the beginning the elevator is on the first floor,
	//so it's final action must have been "going down"
	bool elevatorDirection = DOWN;

	//this is the actual time of the simulation 
	//that starts "ticking" with the beginning of the simulation
	seconds_t timeOfSimulation = 0.0;

	//this stack is an essential part of the algorithm we will use
	//The request on the top of the stack will be the most important
	//among the other requests in the stack (i.e. it is the earliest one to be executed)
	Stack<ElevatorRequest> elevatorRequestsStack;

	/*
		Here's the algorithm we will use:

		1) If the list is empty
		then END PROCEDURE

		else go to step 2

		2)Pop the first element in the elevator requests list and
		push it in the stack. 
		go to step 3

		3)Traverse through all the other requests in the list,
		starting from the first one
		If a more important request than the last one in the stack is found
		then:
		pop in from the list and push it onto the stack. 
		repeat step 3

		else go to step 4

		4)If the stack is empty
		then go to step 1

		else:
		pop the last request in the stack and execute it.
		go to step 3

	*/

	ElevatorRequest lastRequestPushedInTheStack;

	//this iterator will be used to scan the requests in the list one by one
	LinkedList<ElevatorRequest>::Iterator it = elevatorRequestsList.beginIterator();

	while (!elevatorRequestsList.isEmpty())
	{
		//at this point the stack is empty

		lastRequestPushedInTheStack = elevatorRequestsList.pop_front();

		//we have to add the time in which the elevator isn't moving
		//anywhere to the total time of the simulation
		if (timeOfSimulation < lastRequestPushedInTheStack.callTime)
			timeOfSimulation = lastRequestPushedInTheStack.callTime;

		//we take the first request from the list and 
		//push it in the stack
		elevatorRequestsStack.push(lastRequestPushedInTheStack);

		//we'll scan the list for more important requests
		findMoreImportantRequestsAndPushThemInStack
			(elevatorRequestsList
			, elevatorRequestsStack
			, elevatorLocationFloor
			, timeOfSimulation);


		while (!elevatorRequestsStack.isEmpty())
		{
			executeRequest(elevatorRequestsStack, elevatorLocationFloor, timeOfSimulation, elevatorDirection);

			//we are looking for requests to the same floor,
			//on which the elevator is, which must have been executed
			//along with the last executed request
			//Example:
			//the elevator is on the 1-st floor and is called from 
			//the 10-th floor. It starts going up and before it reaches
			//the 10-th floor it is called again from the 10-th
			//floor. In this case the two requests are executed 
			//simultaneously with the arrival of the elevator
			it = elevatorRequestsList.beginIterator();
			while (it != elevatorRequestsList.endIterator())
			{
				//if the call is made after the elevator arrives
				//on the last request floor
				if (it->callTime > timeOfSimulation
					&&
					areEqual(it->callTime, timeOfSimulation) == false)
					break;

				//if the request was given from the same floor
				if (it->floor == elevatorLocationFloor)
				{
					if (timeOfSimulation < it->callTime + requiredTimeForStoppingOnAFloor)
					{
						timeOfSimulation = it->callTime + requiredTimeForStoppingOnAFloor;
					}

					it.remove();
					it = elevatorRequestsList.beginIterator();
					continue;
				}

				++it;
			}

			if (!elevatorRequestsStack.isEmpty())
			{
				findMoreImportantRequestsAndPushThemInStack
					(elevatorRequestsList
					, elevatorRequestsStack
					, elevatorLocationFloor
					, timeOfSimulation);
			}
		}
	}
}


static void skipWhiteCharacters(istream& in)
{
	while (isspace(in.get()))
		;
	in.unget();
}

istream& operator>>(istream& in, ElevatorRequest& elevatorRequest)
		{
			static const char* externalRequestString = "call";
			static const char* internalRequestString = "go";

			static const char* upDirectionString = "up";
			static const char* downDirectionString = "down";

			skipWhiteCharacters(in);

			//this must be a relatively large number,
			//larger than the length of the four strings above
			const int sizeOfBuffer = 20;

			//this buffer will hold the type of the request and 
			//may also hold the direction of the request
			char stringBuffer[sizeOfBuffer]{};

			//firstly, we'll read the type of request
			in.getline(stringBuffer, sizeOfBuffer, ' ');

			if (strcmp(stringBuffer, externalRequestString) == 0)
				elevatorRequest.type = EXTERNAL;
			else
			{
				if (strcmp(stringBuffer, internalRequestString) == 0)
					elevatorRequest.type = INTERNAL;
				else
				{
					cerr<<"invalid type of elevator request\n";
					in.clear(ios::failbit);
					return in;
				}
			}

			if (elevatorRequest.type == EXTERNAL)
			{
				skipWhiteCharacters(in);

				//now, we'll read the direction of the request
				in.getline(stringBuffer, sizeOfBuffer, ' ');

				if (strcmp(stringBuffer, upDirectionString) == 0)
					elevatorRequest.direction = UP;
				else
				{
					if (strcmp(stringBuffer, downDirectionString) == 0)
						elevatorRequest.direction = DOWN;
					else
					{
						cerr << "invalid direction of elevator request\n";
						in.clear(ios::failbit);
						return in;
					}
				}
			}

			in >> elevatorRequest.floor;

			in >> elevatorRequest.callTime;

			return in;
		}

ostream& operator<<(ostream& out, const ElevatorRequest& elevatorRequest)
		{
			if (elevatorRequest.type == INTERNAL)
				cout << "internal ";
			else
				cout << "external ";

			if (elevatorRequest.type == EXTERNAL)
			{
				if (elevatorRequest.direction == UP)
					cout << "up ";
				else
					cout << "down ";
			}

			cout << elevatorRequest.floor
				<< ' '
				<< elevatorRequest.callTime;

			return out;
		}

//getst the information about the elevator requests in the file
//called elevatorRequestsFileName
//and puts it in the elevator requests list
static bool fillElevatorRequestsList
	(const char* elevatorRequestsFileName, LinkedList<ElevatorRequest>& elevatorRequestsList)
		{
			//file containing all the requests of the elevator
			ifstream elevatorRequestsFile(elevatorRequestsFileName, ios::in);
			if (!elevatorRequestsFile)
			{
				cerr << "could no open " << elevatorRequestsFileName
					<< " for reading\n";
				return false;
			}

			int numberOfFloors;

			int numberOfElevatorRequests;

			elevatorRequestsFile >> numberOfFloors;

			elevatorRequestsFile >> numberOfElevatorRequests;

			if (!elevatorRequestsFile)
			{
				cerr << "Some error occured while reading the number of floors"
						" and the number of requests\n";
				elevatorRequestsFile.close();
				return false;
			}

			//validating the two numbers
			if (numberOfFloors <= 0)
			{
				elevatorRequestsFile.close();
				cerr << "The number of floors must be a positive number\n";
				return false;
			}

			if (numberOfElevatorRequests < 0)
			{
				elevatorRequestsFile.close();
				cerr << "The number of elevator requests must be a non-negative number\n";
				return false;
			}


			//this buffer will hold information about the
			//different requests in the file,
			//by extracting them one by one
			ElevatorRequest elevatorRequestBuffer;

			for (int i = 0; i < numberOfElevatorRequests; ++i)
			{
				elevatorRequestsFile >> elevatorRequestBuffer;

				if (!elevatorRequestsFile)
				{
					cerr << "request number " << (i + 1) << " is incorrect\n";
					elevatorRequestsFile.close();
					return false;
				}

				elevatorRequestsList.push_back(elevatorRequestBuffer);
			}

			return true;
		}


bool elevatorSimulation(const char* elevatorRequestsFileName)
{
	//this list will hold all elevator requests in the file
	LinkedList<ElevatorRequest> elevatorRequestsList;

	bool functionResult;

	try
	{
		functionResult = fillElevatorRequestsList(elevatorRequestsFileName, elevatorRequestsList);
	}
	catch (const exception& except)
	{
		cerr << except.what() << '\n';
		return false;
	}

	if (functionResult == false)
		return false;

	//we accept that the function fillElevatorRequestsList
	//has checked all elevator requests and that they are all correct

	executeElevatorRequests(elevatorRequestsList);

	return true;
}

