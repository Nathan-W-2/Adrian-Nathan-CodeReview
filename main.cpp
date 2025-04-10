#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len); 
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len);

int LeastCommonMultiple(int a, int b);
int GreatestCommonDivisor(int a, int b); 
int countDigit(int num);
int pow(int base, int power);
int abs(int num);
bool toString(int characteristic, int numerator, int denominator, char result[], int len);
void fixDenominator(int& n1, int& d1);
bool equalizeDenominators(int& n1, int& d1, int& n2, int& d2, int& resultDenominator);
void reduceFraction(int& numerator, int& denominator);
bool improperToMixed(int& resultNumerator, int resultDenominator, int& resultCharacteristic); 
bool willOverflowMult(int a, int b);
bool willOverflowAdd(int a, int b);
bool willOverflowSub(int a, int b);

int main()
{
    //this c-string, or array of 8 characters, ends with the null terminating character '\0'
    //['1', '2', '3', '.', '4', '5', '6', '\0']
    const char number[] = "123.456"; 
    int c, n, d;

    //if both conversions from c-string to integers can take place
    if(characteristic(number, c) && mantissa(number, n, d))
    {
        //do some math with c, n, and d
        cout<<"c: "<<c<<endl;
        cout<<"n: "<<n<<endl;
        cout<<"d: "<<d<<endl;
    }
    else //at least one of the conversions failed
    {
        //handle the error on input
        cout<<"Error on input"<<endl;
    }

    //room for 9 characters plus the null terminating character
    char answer[10];
    int c1, n1, d1;
    int c2, n2, d2;

    //initialize the values
    c1 = 1;
    n1 = 3902;
    d1 = 30833;

    c2 = 3;
    n2 = 490;
    d2 = 40033; 

    //if the c-string can hold at least the characteristic
    if(add(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on add"<<endl;
    }
    if(subtract(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on subtract"<<endl;
    }
    if(multiply(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on multiply"<<endl;
    }

    if(divide(c1, n1, d1, c2, n2, d2, answer, 10))
    {
        //display string with answer
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }

    // cout << LeastCommonMultiple(8, 1) << endl; 

    return 0;
} 
//--
bool characteristic(const char numString[], int& c)
{
    //hard coded return value to make the main() work
    c = 123;
    return true;
}
//--
bool mantissa(const char numString[], int& numerator, int& denominator)
{
    //hard coded return value to make the main() work
    numerator = 456;
    denominator = 1000;
    return true;
}
//--
bool add(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    if (d1 == 0 or d2 == 0) {
        cout << "Error: Divide by Zero" << endl; 
        return false; 
    }
    //variables to keep an ongoing calculation to eventually convert to a string
    int resultCharacteristic = 0; 
    int resultNumerator = 0; 
    int resultDenominator = 0; 
    //reduce the fractions to prevent some cases of overflow
    reduceFraction(n1, d1); 
    reduceFraction(n2, d2); 
    //make sure only the numerators can be negative and denominators are the same 
    if (!equalizeDenominators(n1, d1, n2, d2, resultDenominator)) {
        return false; 
    }

    if (willOverflowMult(c1, resultDenominator)) {
        cout << "Error: Overflow/Underflow in add()" << endl; 
        return false; 
    }
    if (willOverflowAdd(resultNumerator, c1 * resultDenominator)) {
        cout << "Error: Overflow/Underflow in add()" << endl; 
        return false; 
    }
    resultNumerator += c1 * resultDenominator;
    if (willOverflowMult(c2, resultDenominator)) {
        cout << "Error: Overflow/Underflow in add()" << endl; 
        return false; 
    }
    if (willOverflowAdd(resultNumerator, c2 * resultDenominator)) {
        cout << "Error: Overflow/Underflow in add()" << endl; 
        return false; 
    }
    resultNumerator += c2 * resultDenominator;
    if (willOverflowAdd(n1, n2)) {
        cout << "Error: Overflow/Underflow in add()" << endl; 
        return false; 
    }
    if (willOverflowAdd(resultNumerator, n1 + n2)) {
        cout << "Error: Overflow/Underflow in add()" << endl; 
        return false; 
    }
    resultNumerator += n1 + n2;
    
    //convert the improper fraction if necessary
    if (!improperToMixed(resultNumerator, resultDenominator, resultCharacteristic)) {
        return false; 
    }
    //toString() returns a bool
    return toString(resultCharacteristic, resultNumerator, resultDenominator, result, len);
}
//--
bool subtract(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    if (d1 == 0 or d2 == 0) {
        cout << "Error: Divide by Zero" << endl; 
        return false; 
    }
    //variables to keep an ongoing calculation to eventually convert to a string
    int resultCharacteristic = 0; 
    int resultNumerator = 0; 
    int resultDenominator = 0; 
    //reduce the fractions to prevent some cases of overflow
    reduceFraction(n1, d1); 
    reduceFraction(n2, d2); 
    //make sure only the numerators can be negative
    if (!equalizeDenominators(n1, d1, n2, d2, resultDenominator)) {
        return false; 
    }

    if (willOverflowMult(c1, resultDenominator)) {
        cout << "Error: Overflow/Underflow in subtract()" << endl; 
        return false; 
    }
    if (willOverflowAdd(c1 * resultDenominator, n1)) {
        cout << "Error: Overflow/Underflow in subtract()" << endl; 
        return false; 
    }
    if (willOverflowAdd(resultNumerator, c1 * resultDenominator + n1)) {
        cout << "Error: Overflow/Underflow in subtract()" << endl; 
        return false; 
    }
    resultNumerator += c1 * resultDenominator + n1;
    if (willOverflowMult(c2, resultDenominator)) {
        cout << "Error: Overflow/Underflow in subtract()" << endl; 
        return false; 
    }
    if (willOverflowSub(resultNumerator, c2 * resultDenominator)) {
        cout << "Error: Overflow/Underflow in subtract()" << endl; 
        return false; 
    }
    resultNumerator -= c2 * resultDenominator;
    if (willOverflowSub(resultNumerator, n2)) {
        cout << "Error: Overflow/Underflow in subtract()" << endl; 
        return false; 
    }
    resultNumerator -= n2;
    
    //convert the improper fraction if necessary
    if (!improperToMixed(resultNumerator, resultDenominator, resultCharacteristic)) {
        return false; 
    }
    return toString(resultCharacteristic, resultNumerator, resultDenominator, result, len);
}
//--
bool multiply(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    if (d1 == 0 or d2 == 0) {
        cout << "Error: Divide by Zero" << endl; 
        return false; 
    }
    //variables to keep an ongoing calculation to eventually convert to a string
    int resultCharacteristic = 0; 
    int resultNumerator = 0; 
    int resultDenominator = 0; 
    //make sure only the numerators can be negative
    fixDenominator(n1, d1);
    fixDenominator(n2, d2);
    //reduce the fractions to prevent some cases of overflow
    reduceFraction(n1, d1); 
    reduceFraction(n2, d2); 

    if (willOverflowMult(c1, d1)) {
        cout << "Error: Overflow/Underflow in multiply()" << endl; 
        return false; 
    }
    if (willOverflowAdd(resultNumerator, c1 * d1)) {
        cout << "Error: Overflow/Underflow in multiply()" << endl; 
        return false; 
    }
    resultNumerator += c1 * d1;
    if (willOverflowAdd(resultNumerator, n1)) {
        cout << "Error: Overflow/Underflow in multiply()" << endl; 
        return false; 
    }
    resultNumerator += n1;
    if (willOverflowMult(c2, d2)) {
        cout << "Error: Overflow/Underflow in multiply()" << endl; 
        return false; 
    }
    if (willOverflowAdd(c2 * d2, n2)) {
        cout << "Error: Overflow/Underflow in multiply()" << endl; 
        return false; 
    }
    if (willOverflowMult(resultNumerator, c2 * d2 + n2)) {
        cout << "Error: Overflow/Underflow in multiply()" << endl; 
        return false; 
    }
    resultNumerator *= c2 * d2 + n2;
    if (willOverflowMult(d1, d2)) {
        cout << "Error: Overflow/Underflow in multiply()" << endl; 
        return false; 
    }
    resultDenominator = d1 * d2; 
    
    fixDenominator(resultNumerator, resultDenominator);
    //convert the improper fraction if necessary
    if (!improperToMixed(resultNumerator, resultDenominator, resultCharacteristic)) {
        return false; 
    }
    return toString(resultCharacteristic, resultNumerator, resultDenominator, result, len);
}
//--
bool divide(int c1, int n1, int d1, int c2, int n2, int d2, char result[], int len)
{
    if (d1 == 0 or d2 == 0) {
        cout << "Error: Divide by Zero" << endl; 
        return false; 
    }
    if (c2 == 0 and n2 == 0) {
        cout << "Error: Divide by Zero" << endl; 
        return false; 
    }
    //variables to keep an ongoing calculation to eventually convert to a string
    int resultCharacteristic = 0; 
    int resultNumerator = 0; 
    int resultDenominator = 0; 
     //make sure only the numerators can be negative
     fixDenominator(n1, d1);
     fixDenominator(n2, d2);
     //reduce the fractions to prevent some cases of overflow
     reduceFraction(n1, d1); 
     reduceFraction(n2, d2); 

    if (willOverflowMult(c1, d1)) {
        cout << "Error: Overflow/Underflow in divide()" << endl; 
        return false; 
    }
    if (willOverflowAdd(resultNumerator, c1 * d1)) {
        cout << "Error: Overflow/Underflow in divide()" << endl; 
        return false; 
    }
    resultNumerator += c1 * d1;
    if (willOverflowAdd(resultNumerator, n1)) {
        cout << "Error: Overflow/Underflow in divide()" << endl; 
        return false; 
    }
    resultNumerator += n1;
    if (willOverflowMult(resultNumerator, resultDenominator)) {
        cout << "Error: Overflow/Underflow in divide()" << endl; 
        return false; 
    }
    resultNumerator *= d2; 
    if (willOverflowMult(c2, d2)) {
        cout << "Error: Overflow/Underflow in divide()" << endl; 
        return false; 
    }
    if (willOverflowAdd(c2 * d2, n2)) {
        cout << "Error: Overflow/Underflow in divide()" << endl; 
        return false; 
    }
    if (willOverflowMult(d1, c2 * d2 + n2)) {
        cout << "Error: Overflow/Underflow in divide()" << endl; 
        return false; 
    }
    resultDenominator = d1 * (c2 * d2 + n2); 
    
    fixDenominator(resultNumerator, resultDenominator);
    //convert the improper fraction if necessary
    if (!improperToMixed(resultNumerator, resultDenominator, resultCharacteristic)) {
        return false; 
    }
    return toString(resultCharacteristic, resultNumerator, resultDenominator, result, len);
}

//takes two ints and returns their least common multiple 
int LeastCommonMultiple(int a, int b)
{
    if (a == 0 or b == 0) {
        return 0;
    }
    int greatest = max(a, b);
    int smallest = min(a, b);
    // cout << greatest << endl; 
    // cout << smallest << endl; 
    //loop finds the first multiple of the greatest number that is divisible by the smaller number
    for (int multiple = greatest; ; multiple += greatest) {
        if (multiple % smallest == 0) {
            return i;
        }
        if (willOverflowAdd(i, greatest)) {
            cout << "Error: Least common multiple of fractions is larger than INT_MAX" << endl; 
            return -1; 
        }
        // cout << i % smallest << endl; 
    }
}

int GreatestCommonDivisor(int a, int b) {
    if (a == 0) {
        return b;
    }
    if (b == 0) {
        return a;
    }
    if (willOverflowMult(a, b)) {
        cout << "Error: Overflow/Underflow in GreatestCommonDivisor()" << endl; 
        throw "Error: Overflow/Underflow in GreatestCommonDivisor()"; 
    }
    return (abs(a) * abs(b)) / LeastCommonMultiple(a,b); 
}

//takes in a number, returns number of digits
int countDigit(int num) {
    // base case
    if (num == 0) {
        return 1;
    }
    int count = 0;
    // iterate until num has digits remaining
    while (num != 0) {
        // remove rightmost digit
        num = num / 10;
        // increment digit count by 1
        count++;
  }
  return count;
}

int pow(int base, int power) {
    int product = 1; 
    for (int i = 0; i < power; i++) {
        if (willOverflowMult(product, base)) {
            cout << "Error: Overflow/Underflow in pow()" << endl; 
            throw "Error: Overflow/Underflow in pow()"; 
        }
        product *= base; 
    }
    return product; 
}

int abs(int num) {
    if (num >= 0) {
        return num;
      } else {
        return -num;
      }
}

bool toString(int characteristic, int numerator, int denominator, char result[], int len) {
    //will be used throuought the function index through the array
    int resultIndex = 0; 
    //get the length of the characteristicLength in terms of digits 
    int characteristicLength = countDigit(characteristic);
    //if the number is negative, we must account that the string must have room for a negative sign
    if (characteristic < 0 or numerator < 0 ) {
        result[resultIndex] = '-';
        resultIndex++;
        //the number can be converted to positive now that it has been accounted for
        if (characteristic < 0) {
            characteristic = -characteristic; 
        }
        if (numerator < 0) {
            numerator = -numerator; 
        }
    }
    //if the result is too large, return false 
    if (characteristicLength + resultIndex > len - 1) {
        cout << "Error: the characteristic is too large for the array" << endl; 
        return false; 
    //else convert the characteristics into chars, digit by digit
    } else {
        for (int i = characteristicLength; i > 0; i--) {
            //gets the first digit
            int digit = characteristic / pow(10, i-1); 
            //this effectively converts the digit into a char
            result[resultIndex] = '0' + digit; 
            //takes the remainder of the digits to be used in the next iteration of the loop
            characteristic = characteristic % pow(10, i-1);
            resultIndex++; 
        }
    }

    //if the numerator is zero, that means the calculation has no fraction and only the characteristic, meaning no decimal is added
    //the second condition is to see if there is room left in the array for a decimal
    if (numerator != 0 and resultIndex < len - 2) {
        result[resultIndex] = '.';
        resultIndex++;
    
        while (numerator != 0 and resultIndex < len - 1) {
            if (willOverflowAdd(numerator, 10)) {
                cout << "Error: Overflow/Underflow in toString()" << endl; 
                return false; 
            }
            numerator *= 10;
            int digit = numerator / denominator; 
            result[resultIndex] = '0' + digit; 
            resultIndex++;
            numerator = numerator % denominator;
        }
    } 
    result[resultIndex] = '\0';
    return true; 
}

//change denominators from negaitve to positive
void fixDenominator(int& numerator, int& denominator) {
    if (denominator < 0) {
        numerator = -numerator; 
        denominator = -denominator; 
    }
}

//numerators will most likely be changed, denominators remained mostly untouched and are only converted to positive if necessary
bool equalizeDenominators(int& n1, int& d1, int& n2, int& d2, int& resultDenominator) {
    fixDenominator(n1, d1);
    fixDenominator(n2, d2);
    //if denominators are different, we must cross multiply the fractions
    if (d1 != d2) {
        int lcm = LeastCommonMultiple(d1, d2);
        //if lcm is -1, that means an error occured in LeastCommonMultiple() and we exit the function
        if (lcm == -1) {
            return false; 
        }
        if (willOverflowMult(n1, lcm / d1)) {
            cout << "Error: Overflow/Underflow in equalizeDenominators()" << endl; 
            return false; 
        }
        n1 *= lcm / d1;
        if (willOverflowMult(n2, lcm / d2)) {
            cout << "Error: Overflow/Underflow in equalizeDenominators()" << endl; 
            return false; 
        }
        n2 *= lcm / d2; 
        resultDenominator = lcm; 
    }
    //otherwise the denominator is arbitrarily assigned of the inputted denominators
    else {
        resultDenominator = d1; 
    }
    return true; 
}

void reduceFraction(int& numerator, int& denominator) {
    int gcd = GreatestCommonDivisor(numerator, denominator);
    numerator /= gcd; 
    denominator /= gcd; 
}

bool improperToMixed(int& resultNumerator, int resultDenominator, int& resultCharacteristic) {
    if (abs(resultNumerator) >= resultDenominator) {
        if (willOverflowAdd(resultCharacteristic, resultNumerator / resultDenominator)) {
            cout << "Error: Overflow/Underflow in improperToMixed()" << endl; 
            return false; 
        }
        resultCharacteristic += resultNumerator / resultDenominator; 
        resultNumerator = resultNumerator % resultDenominator;
    }
    return true;
}

bool willOverflowMult(int a, int b) {
    bool retVal = false; 
    // if -1 is multiplied by the intmin, the result will be one more than the INT_MAX, causing overflow
    if ((a == -1 && b == INT_MIN) or (b == -1 && a == INT_MIN)) {
        retVal = true; 
    } 
    // the inequalities of a * b > INT_MAX and a * b < INT_MIN rewritten so it can be calculated without overflowing normally
    if (b != 0 && a > INT_MAX / abs(b)) {
        retVal = true; 
    }
    // if (b != 0 && a < INT_MIN / b) {
    //     retVal = true; 
    // }
    return retVal;
}

bool willOverflowAdd(int a, int b) {
    bool retVal = false; 
    // the inequalities of a + b > INT_MAX and a + b < INT_MIN rewritten so it can be calculated without overflowing normally
    if ((b > 0 && a > INT_MAX - b) or (b < 0 && a < INT_MIN - b)) {
        retVal = true; 
    }
    return retVal;
}

bool willOverflowSub(int a, int b) {
    bool retVal = false; 
    // the inequalities of a - b > INT_MAX and a - b < INT_MIN rewritten so it can be calculated without overflowing normally
    if ((b < 0 && a > INT_MAX + b) or (b > 0 && a < INT_MIN + b)) {
        retVal = true; 
    } 
    return retVal;
}
