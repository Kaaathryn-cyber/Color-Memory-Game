//Kathryn Kaelin
//Lab2Out
//Memory game
#include <iostream>
#include <ctime>
#include "graph1.h"

using namespace std;

//Structure Array
struct ColorInfo
{
	int objNum;
	int r, g, b;
};

//Function Prototypes
void GetNoColor(int* noColors);
void SetColors(int* colorNums, int noColors);
void SetColorInfo(ColorInfo* colorData, int noColors);
void GetDelay(int* delay);
void DisplayColors(int* colorNums, ColorInfo* colorData, int noColors, int delay);
void game(int* colorNums, ColorInfo* colorData, int noColors, int delay);

int main()
{
	//Variables
	int noColors = 0, delay = 0;
	const int MAX_ELE = 5;
	int colorNums[MAX_ELE];
	ColorInfo colorData[MAX_ELE];
	char repeat = 'y';

	do
	{
		//Initialize RNG
		srand(time(0));

		//Display graphics
		displayGraphics();

		//Function Declaration
		GetNoColor(&noColors);
		SetColors(colorNums, noColors);
		SetColorInfo(colorData, noColors);
		GetDelay(&delay);
		DisplayColors(colorNums, colorData, noColors, delay);
		game(colorNums, colorData, noColors, delay);

		//Repeats the program is the user so chooses
		cout << "Would you like to play again? <y for yes/ n for no> ";
		cin >> repeat;

		if (repeat == 'y' || repeat == 'Y')
		{
			clearGraphics();
			system("cls");
		}

	} while (repeat == 'y' || repeat == 'Y');


}

//Function Definitions

//Gets the number of colors that will be displayed
void GetNoColor(int* noColors)
{
	
	do
	{
		cout << "Enter number of colors to display <between 2 and 5 inclusive>: ";
		cin >> *noColors;
		if (*noColors < 2 || *noColors > 5)
			cout << "***INVALID*** Please enter a number between 2 and 5.\n\n";
	} while (*noColors < 2 || *noColors > 5);
}

//Sets the colors to a random number between 0 - 5
void SetColors(int* colorNums, int noColors)
{
	int i = 0;
	for (i = 0; i < noColors; i++)
	{
		colorNums[i] = rand() % 5;
	}
}

//Sets the RGB values to the array
void SetColorInfo(ColorInfo* colorData, int noColors)
{
	int i = 0;
	for (i = 0; i < noColors; i++)
	{
		colorData[i].objNum = 0;
	}
	colorData[0].r = 255;
	colorData[0].g = 0;
	colorData[0].b = 0;
	colorData[1].r = 0;
	colorData[1].g = 255;
	colorData[1].b = 0;
	colorData[2].r = 0;
	colorData[2].g = 0;
	colorData[2].b = 255;
	colorData[3].r = 255;
	colorData[3].g = 255;
	colorData[3].b = 0;
	colorData[4].r = 255;
	colorData[4].g = 0;
	colorData[4].b = 255;
}

//Gets the number of seconds for the delay
void GetDelay(int* delay)
{
	do
	{
		cout << "Enter delay <between 1 and 3 inclusive> ";
		cin >> *delay;
		if (*delay < 1 || *delay > 3)
			cout << "***INVALID*** Please enter a number that is between 1 and 3.\n\n";
	} while (*delay < 1 || *delay > 3);

}

//Displays the colors for and then clears the colors after the set amount of seconds
void DisplayColors(int* colorNums, ColorInfo* colorData, int noColors, int delay)
{
	int i = 0, x = 50, y = 100;
	
	for (i = 0; i < noColors; i++)
	{
		colorData[i].objNum = drawRect(x, y, 75, 75);
		setColor(colorData[i].objNum, colorData[colorNums[i]].r, colorData[colorNums[i]].g, colorData[colorNums[i]].b);
		gout << setPos(x, y + 95) << setColor(0, 255, 0) << "Color # " << i + 1 << endg;
		x += 100;
	}

	Sleep(1000 * delay); //Sleep function uses miliseconds --> 1000 miliseconds = 1 second

	clearGraphics();
	system("cls");
}

//Displays a list of colors for the user to choose from, keeps score for ever answer the user gets right or wrong, and counts the number
//of plays that the user goes through. The results are then presented when the game is over
void game(int* colorNums, ColorInfo* colorData, int noColors, int delay)
{
	int i;
	int score = 0, plays = 0, x = 50, y = 100, answer;

	//Game
	for (i = 0; i < noColors; i++)
	{
		do
		{
			//Color list
			cout << "Select Color #" << i + 1 << endl;
			cout << "1. Red\n" << "2. Green\n" << "3. Blue\n" << "4. Yellow\n" << "5. Purple" << endl;
			cout << "Enter Choice: ";
			cin >> answer;

			if (!(answer == colorNums[i] + 1))
			{
				//Display incoorect and subtract 2 from the score
				score -= 2;
				gout << setPos(310, 70) << setColor(0, 255, 0) << "INCORRECT!" << endg;
				gout << setPos(310, 85) << setColor(0, 255, 0) << "Score: " << score << endg;
				plays += 1;
			}

		} while (!(answer == colorNums[i] + 1));

		//Display correct and add 2 to the score
		score += 2;
		plays += 1;
		gout << setPos(310, 70) << setColor(0, 255, 0) << "CORRECT!!!" << endg;
		gout << setPos(310, 85) << setColor(0, 255, 0) << "Score: " << score << endg;

		//Display rectangles when correct answer is given
		colorData[i].objNum = drawRect(x, y, 75, 75);
		setColor(colorData[i].objNum, colorData[colorNums[i]].r, colorData[colorNums[i]].g, colorData[colorNums[i]].b);
		x += 100;
	}
	//Game Over
	gout << setPos(310, 300) << setColor(0, 255, 0) << "Game Over!!!" << endg;
	gout << setPos(310, 315) << setColor(0, 255, 0) << "Score: " << score << endg;
	gout << setPos(310, 330) << setColor(0, 255, 0) << "Plays: " << plays << endg;

}