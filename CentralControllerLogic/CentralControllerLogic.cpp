// CentralControllerLogic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"	//Needed for rand() function
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

//Initialising the trajectory of the ball
int kickTrajectoryX;
int kickTrajectoryY;

//Initialising the kick of the ball
bool kickBall = false;

//Initialising the number of players within the range of the ball
int playersWithinRange = 0;

//Class to create ball object
class Ball {
public:
	//Intialising the x & y dimensions for the ball
	int ballX = 988;
	int ballY = 988;
	bool wallHit = false;

	//Function to move the ball on the soccer pitch
	void move() {
		//Checking if the ball was kicked
		if (kickBall) {
			//Determining the trajectory of the ball
			if (kickTrajectoryX < 0) {
				ballX = ballX - 3;

				//Debugging purposes
				cout << "Kick Trajectory";
				cout << "X<0 ";
				cout << "BallX: " << ballX << endl;
			} if (kickTrajectoryY < 0) {
				ballY = ballY - 3;

				//Debugging purposes
				cout << "Kick Trajectory";
				cout << "Y<0 ";
				cout << "BallY: " << ballY << endl;
			} if (kickTrajectoryX > 0) {
				ballX = ballX + 3;

				//Debugging purposes
				cout << "Kick Trajectory";
				cout << "X>0 ";
				cout << "BallX: " << ballX << endl;
			} if (kickTrajectoryX > 0) {
				ballY = ballY + 3;

				//Debugging purposes
				cout << "Kick Trajectory";
				cout << "Y>0 ";
				cout << "BallY: " << ballY << endl;
			}
		}
		
		//Checking if the ball has reached the edges of the soccer pitch
		if (ballX < xStart) {
			ballX = 0;
			wallHit = true;
		} if (ballX > xEnd) {
			ballX = 1000;
			wallHit = true;
		} if (ballY < yStart) {
			ballY = 0;
			wallHit = true;
		} if (ballY > yEnd) {
			ballY = 1000;
			wallHit = true;
		} else {
			wallHit = false;
		}

		//Ball location
		cout << "Ball's Location: ";
		cout << ballX << " & " << ballY << endl;
		cout << endl;
	}
};

//Class to create player objects
class Players {
public:
	//Intialising the x & y dimensions for the players to determine their direction of travel
	int xPrevious = 985;
	int yPrevious = 985;
	int xNow = 985;
	int yNow = 985;
	int trajectoryX;
	int trajectoryY;
	bool ballHold = false;		//Yet to have used this variable

	//Intialising the range within the ball
	int rangeMaxX;
	int rangeMinX;
	int rangeMaxY;
	int rangeMinY;

	//Function to move the players on the soccer pitch
	void move(Ball *b, int up, int down, int left, int right) {
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

		//Checking if the player has reached the edges of the soccer pitch
		if (xNow < xStart) {
			xNow = 0;
		} if (xNow > xEnd) {
			xNow = 1000;
		} if (yNow < yStart) {
			yNow = 0;
		} if (yNow > yEnd) {
			yNow = 1000;
		}

		//Debugging purposes
		cout << "Player's New Location: " << xNow << " & " << yNow << endl;
		cout << endl;

		//Calculating trajectory for a possible kick
		trajectoryX = xNow - xPrevious;
		trajectoryY = yNow - yPrevious;


		//Determining the ball's range
		rangeMaxX = b->ballX + 1;
		rangeMinX = b->ballX - 1;
		rangeMaxY = b->ballY + 1;
		rangeMinY = b->ballY - 1;

		//Debugging purposes
		cout << "X Vector: " << trajectoryX << endl;
		cout << "Y Vector: " << trajectoryY << endl;
		cout << endl;

		//Debugging purposes
		cout << "Max Range X: " << rangeMaxX << endl;
		cout << "Min Range X: " << rangeMinX << endl;
		cout << "Max Range Y: " << rangeMaxY << endl;
		cout << "Max Range Y: " << rangeMaxY << endl;
		cout << endl;

		//Checking if the player is within range of the ball
		if (xNow <= rangeMaxX && xNow >= rangeMinX && yNow <= rangeMaxY && yNow >= rangeMinY) {
			//Proof of concept-------------------------------------------------------
			if (playersWithinRange > 0) {
				int random = rand() % 100;
				cout << "Value of the Generated Random Number: " << random << endl;
				cout << endl;
			}
			//-----------------------------------------------------------------------

			b->ballX = xNow;
			b->ballY = yNow;

			kickBall = false;
			ballHold = true;
			playersWithinRange++;

			//if (p[1]->ballHold == true) {
			//	cout << "Showing P1 Ball Hold" << endl;
			//} if (p[2]->ballHold == true) {
			//	cout << "Showing P2 Ball Hold" << endl;
			//}

			//Debugging purposes
			cout << "Ball's New Location: ";
			cout << "Ball X: " << b->ballX << endl;
			cout << "Ball Y: " << b->ballY << endl;
			cout << "Ball Hold: " << ballHold << endl;

			//Debugging purposes
			cout << "Within Range of the ball" << endl;
			cout << "Player's Within Range of the Ball: " << playersWithinRange << endl;
			cout << endl;
		}

		//Updating previous x & y values
		xPrevious = xNow;
		yPrevious = yNow;
	}

	//Function to kick the ball
	void kick(Ball *b, int kick) {
		//Button and kick logic
		//Triggered by button

		kickBall = true;
		ballHold = false;
		playersWithinRange--;

		//Determining the trajectory of the ball
		if (trajectoryX < 0) {
			b->ballX = b->ballX - 3;
			kickTrajectoryX = trajectoryX;

			//Debugging purposes
			cout << "X<0 ";
			cout << "BallX: " << b->ballX << endl;
		} if (trajectoryY < 0) {
			b->ballY = b->ballY - 3;
			kickTrajectoryY = trajectoryY;

			//Debugging purposes
			cout << "Y<0 ";
			cout << "BallY: " << b->ballY << endl;
		} if (trajectoryX > 0) {
			b->ballX = b->ballX + 3;
			kickTrajectoryX = trajectoryX;

			//Debugging purposes
			cout << "X>0 ";
			cout << "BallX: " << b->ballX << endl;
		} if (trajectoryX > 0) {
			b->ballY = b->ballY + 3;
			kickTrajectoryY = trajectoryY;

			//Debugging purposes
			cout << "Y>0 ";
			cout << "BallY: " << b->ballY << endl;
		}

		//Debugging purposes
		cout << "Ball Hold: " << ballHold << endl;
	}
};

int main() {
	//Creating the player objects
	Players p[14];

	//Creating the ball object
	Ball b;

	//Infinite while loop to represent the loop for Arduinos
	while (1) {
		for (int i = 1; i < 3; i++) {
			cout << "_______________________ " << i <<  " _________________________ " << endl;
			cout << "Player " << i << "'s Current Location: " << p[i].xNow << " & " << p[i].yNow << endl;
			cout << endl;
			cout << "Update Player Location" << endl;

			cout << "Up: ";
			cin >> upBit;
			if (upBit == 0) {
				downBit = 1;
			} else {
				downBit = 0;
			}
			cout << "Left: ";
			cin >> leftBit;
			if (leftBit == 0) {
				rightBit = 1;
			} else {
				rightBit = 0;
			}

			cout << "Kick: ";
			cin >> kickBit;
			cout << "Up: " << upBit << " Down: " << downBit << " Left: " << leftBit << " Right: " << rightBit << " Kick: " << kickBit << endl;
			cout << endl;

			//Updating player's position
			p[i].move(&b, upBit, downBit, leftBit, rightBit);

			//Checking if anyplayer is holding the ball
			if (p[1].ballHold == true || p[2].ballHold == true) {
				cout << "Ball is being HELD" << endl;
				cout << endl;
			} else {
				cout << "Ball is NOT being HELD" << endl;
				cout << endl;
			}

			//Updating the ball's location
			b.move();

			//Checking whether the player has kicked the ball
			if (kickBit) {
				cout << "Kicked" << endl;
				cout << endl;
				p[i].kick(&b, kickBit);
			}
			
			//Restarting the for loop
			if (i == 2) {
				i = 0;
			}
		}

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

