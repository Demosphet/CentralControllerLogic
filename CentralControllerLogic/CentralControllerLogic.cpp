// CentralControllerLogic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"

using namespace std;

//Initialsing debugging variables for user input
int upBit;
int downBit;
int leftBit;
int rightBit;
int kickBit;

//Intialsing the dimensions of the soccer pitch
int xStart = 0;
int yStart = 0;
int xEnd = 1000;
int yEnd = 1000;

//Class to create player objects
class Players {
public:
	//Intialising the x & y dimensions for the players to determine their direction of travel
	int xPrevious = 0;
	int yPrevious = 0;
	int xNow = 0;
	int yNow = 0;
	bool ballHold = false;

	//Function to move the players on the soccer pitch
	void move(int up, int down, int left, int right, int kick) {
		//Gyroscope and movement logic
		//Triggered by gyroscope

		//Updating player co-ordinates
		if (up) {
			yNow = yNow + up;
		} if (down) {
			yNow = yNow - down;
		} if (left) {
			xNow = xNow - left;
		} if (right) {
			xNow = xNow + right;
		}

		//Debugging purposes
		cout << xNow << " & " << yNow << endl;

		//Checking for a kick
		if (kick) {
			cout << "Kick Registered" << endl;
		}

		//Updating previous x & y values
		xPrevious = xNow;
		yPrevious = yNow;
	}

	//Function to kick the ball
	void kick(int kick) {
		//Button and kick logic
		//Triggered by button
	}
};

//Class to create ball object
class Ball {
public:
	//Intialising the x & y dimensions for the ball
	int x = 500;
	int y = 500;

	//Function to move the ball on the soccer pitch
	void move() {
		//Ball movement logic
	}
};

int main() {
	//Creating the player objects
	Players p1;
	Players p2;
	Players p3;
	Players p4;
	Players p5;
	Players p6;
	Players p7;
	Players p8;
	Players p9;
	Players p10;
	Players p11;
	Players p12;
	Players p13;
	Players p14;
	//Creating the ball object
	Ball b;

	//Infinite while loop to represent the loop for Arduinos
	while (1) {
		cout << "_________________________________" << endl;
		cout << "Update Player Location" << endl;
		cout << "Up: ";
		cin >> upBit;
		if (upBit != 1) {
			downBit = 1;
		}
		cout << "Left: ";
		cin >> leftBit;
		if (leftBit != 1) {
			rightBit = 1;
		}
		cout << "Kick: ";
		cin >> kickBit;
		cout << "Up: " << upBit << " Down: " << downBit << " Left: " << leftBit << " Right: " << rightBit << " Kick: " << kickBit << endl;

		//Updating player position
		p1.move(upBit, downBit, leftBit, rightBit, kickBit);

		//for (int i = 1; i < 15; i++) {
		//	//get gyroscope values
		//		//include nrf code here
		//	//get button value
		//		//inclyde nrf code here
		//	//update player location
		//		//p1.move(up,down,left,right)
		//		//...
		//		//p14.move(up,down,left,right)
		//}
	}

    return 0;
}

