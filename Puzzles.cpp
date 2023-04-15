#include "Puzzles.h"

int Puzzle1()
{
    cout << "Question 1 which shall be fun! What is 7 + 2?" << endl;
    int playerGuess;
    cin >> playerGuess;
    if (playerGuess == 9)
    {
        cout << "You are correct but are you prepared for what's next?" << endl;
        return 0;
    }
    else
    {
        cout << "Incorrect you simple fool, now you'll taste the might Gahul!" << endl;
        return -1;
    }
}
