// CentralControllerLogic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"	//Needed for rand() function
#include "iostream"
#include "string"

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

//Initialising variable to determine if players from either team is within the range of the ball
bool team1 = false;
bool team2 = false;
bool contention = team1 & team2;

//Initialising the number of players
const int numberOfPlayersPlusOne = 5;

//Initialising the player's within range of the ball variables
string withinRange[numberOfPlayersPlusOne] = { "0" };
int numberOfPlayersWithinRange = 0;

//Initialising team counter
int teamNumber = 1;

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

	//Initialising team numbers
	int team = 0;

	//Intialising the range within the ball
	int rangeMaxX;
	int rangeMinX;
	int rangeMaxY;
	int rangeMinY;

	//Initialising the probability the player will obtain the ball
	int obtainProbability;

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
		cout << "Min Range Y: " << rangeMinY << endl;
		cout << endl;

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
		for (int i = 1; i < numberOfPlayersPlusOne; i++) {
			if (teamNumber == 3) {
				teamNumber = 1;
			}

			//Setting team numbers for each player
			p[i].team = teamNumber;
			teamNumber++;
		}

		for (int i = 1; i < numberOfPlayersPlusOne; i++) {
			cout << "_______________________ " << i <<  " _________________________ " << endl;
			cout << "Team: " << p[i].team << endl;
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

			//Checking if the player is within range of the ball
			if (p[i].xNow <= p[i].rangeMaxX && p[i].xNow >= p[i].rangeMinX && p[i].yNow <= p[i].rangeMaxY && p[i].yNow >= p[i].rangeMinY) {
				withinRange[i] = "1";

				//Determining which player is within range of the ball
				cout << "withinRange Variable" << endl;

				for (int j = 1; j < numberOfPlayersPlusOne; j++) {
					if (withinRange[j] == "1") {
						if(j % 2 == 1) {
							team1 = true;
						} else if (j % 2 == 0) {
							team2 = true;
						}
						cout << j << " has a value of: " << withinRange[j] << endl;
						numberOfPlayersWithinRange++;
					} else {
						cout << j << " has a value of: " << withinRange[j] << endl;
					}
				}
				cout << endl;

				int maxValue = 0;
				int maxPlayer = 0;

				//Taking appropriate action depending on how many players are within range of the ball
				if (numberOfPlayersWithinRange > 1) {
					if(contention) {
						for (int j = 1; j < numberOfPlayersPlusOne; j++) {
							if (withinRange[j] == "1") {
								p[j].obtainProbability = rand() % 100;
								cout << "Value of the Generated Random Number for Player " << j << " : " << p[j].obtainProbability << endl;
								cout << endl;

								//Setting the player index if plauers contesting for the ball are not on the same team
								if (p[j].obtainProbability > maxValue) {
									maxValue = p[j].obtainProbability;
									maxPlayer = j;
								}
							} else {
								//Error case
								cout << "Caught in an unexpected else 1" << endl;
							}
						}
					} else if (!contention) {
						//Setting the player index if plauers contesting for the ball are on the same team
						maxPlayer = i;

						//Debugging purposes
						cout << "Contention: Same Team" << endl;
						cout << endl;
					}

					//Debugging purposes
					cout << "maxPlayer: " << maxPlayer << endl;
					cout << "maxValue: " << maxValue << endl;
					cout << "xNow: " << p[maxPlayer].xNow << endl;
					cout << "yNow: " << p[maxPlayer].yNow << endl;

					//Updating the ball location
					b.ballX = p[maxPlayer].xNow;
					b.ballY = p[maxPlayer].yNow;

					//Updating the possession status of the ball
					kickBall = false;
					p[maxPlayer].ballHold = true;

					// numberOfPlayersWithinRange = 1;

					/*if (p[1].obtainProbability > 50) {
						b.ballX = p[1].xNow;
						b.ballY = p[1].yNow;

						kickBall = false;
						p[1].ballHold = true;

						numberOfPlayersWithinRange = 1;
					} else if (p[2].obtainProbability > 50) {
						b.ballX = p[2].xNow;
						b.ballY = p[2].yNow;

						kickBall = false;
						p[2].ballHold = true;

						numberOfPlayersWithinRange = 1;
					} else {
						//Error case
						cout << "Caught in an unexpected else 2" << endl;
					}*/
				} else if (numberOfPlayersWithinRange == 1) {
					b.ballX = p[i].xNow;
					b.ballY = p[i].yNow;

					kickBall = false;
					p[i].ballHold = true;

					// numberOfPlayersWithinRange = 1;
				} else {
					//Error case
					cout << "Caught in an unexpected else 3" << endl;
				}

				//Debugging purposes
				cout << "Ball's New Location: " << endl;
				cout << "Ball X: " << b.ballX << endl;
				cout << "Ball Y: " << b.ballY << endl;
				cout << "Ball Hold: " << p[i].ballHold << endl;

				//Debugging purposes
				cout << "Within Range of the ball" << endl;
				cout << endl;

				numberOfPlayersWithinRange = 0;
			} else {
				//If no player is within range of the ball
				withinRange[i] = "0";
			}

			/*
			//Checking if anyplayer is holding the ball
			if (p[1].ballHold == true || p[2].ballHold == true) {
				cout << "Ball is being HELD" << endl;
				cout << endl;
			} else {
				cout << "Ball is NOT being HELD" << endl;
				cout << endl;
			}*/

			//Checking if anyplayer is holding the ball
			int ballHoldCounter = 0;
			for (int j = 1; j < numberOfPlayersPlusOne; j++) {
				if (p[j].ballHold == true) {
					ballHoldCounter++;
				} if (j == ((numberOfPlayersPlusOne)-1)) {
					if (ballHoldCounter > 0) {
						cout << "Ball is being HELD" << endl;
						cout << endl;
					} else {
						cout << "Ball is NOT being HELD" << endl;
						cout << endl;
					}
					ballHoldCounter = 0;
				}
			}

			//Checking whether the player has kicked the ball
			if (kickBit) {
				cout << "Kicked" << endl;
				cout << endl;
				p[i].kick(&b, kickBit);
			}
		}

		//Updating the ball's location
		b.move();

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

