// InformalCodeReview.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <sstream>
#include "InformalCodeReview.h"


bool InformalCodeReview::characteristic(const char numString[], int& c)
{
    int placeCounter = 0;
    bool foundDecimal = false;
    for (int decFinder = 0; decFinder < sizeof(numString); decFinder++)
    {
        if (numString[decFinder] == '.')
        {
            placeCounter = decFinder;
            foundDecimal = true;
            break;
        }
    }
    if (foundDecimal == false)
    {
        placeCounter = sizeof(numString - 1);
    }
        vector<char> slicedCopy;
        string assembledCopy = "";
        int characteristic = 0;
        for (int intTransposer = 0; intTransposer < placeCounter; intTransposer++)
        {
            assembledCopy = assembledCopy + numString[intTransposer];
        }
        stringstream stringToIntConverter(assembledCopy);
        stringToIntConverter >> characteristic;
        c = characteristic;
        return true;
}
bool InformalCodeReview::mantissa(const char numString[], int& numerator, int& denominator)
{
    int placeCounter = 0;
    bool foundDecimal = false;
    int numStringLength = strlen(numString);
    for (int decFinder = 0; decFinder < numStringLength; decFinder++)
    {
        if (numString[decFinder] == '.')
        {
            placeCounter = decFinder;
            foundDecimal = true;
            break;
        }
    }
    placeCounter++;
    if (foundDecimal == false)
    {
        placeCounter = numStringLength - 1;
    }
    vector<char> slicedCopy;
    string assembledCopy = "";
    int mantissa = 0;
    int denomSize = 0;
    denominator = 1;
    for (int intTransposer = placeCounter; intTransposer < numStringLength; intTransposer++)
    {
        assembledCopy = assembledCopy + numString[intTransposer];
        denomSize++;
    }
    stringstream stringToIntConverter(assembledCopy);
    stringToIntConverter >> mantissa;
    for (int denomIterator = 0; denomIterator < denomSize; denomIterator++)
    {
        denominator *= 10;
    }
    numerator = mantissa;
    return true;
}
int main()
{
    InformalCodeReview review;
    const char numString[] = "123.456";  

    int characteristicValue = 0;
    int numerator = 0;
    int denominator = 0;

    review.characteristic(numString, characteristicValue);
    cout << "Characteristic: " << characteristicValue << endl;
    review.mantissa(numString, numerator, denominator);
    cout << "Mantissa: " << numerator << "/" << denominator << endl;

    return 0;
}