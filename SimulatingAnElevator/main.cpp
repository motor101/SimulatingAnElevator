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

bool elevatorSimulation(const char *elevatorRequestsFileName);

int main(int argc, char *argv[])
{
	
	if (argc < 2)
	{
		std::cerr << "The name of the file with the elevator requests must "
			"be a command line argument\n";
		return 1;
	}

	elevatorSimulation(argv[1]);	

	return 0;
}

