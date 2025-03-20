
#include <iostream>
using namespace std;

//required function prototypes
bool characteristic(const char numString[], int& c);
bool mantissa(const char numString[], int& numerator, int& denominator);

bool add(int characteristic1, int numerator1, int denominator1, int characteristic2, int numerator2, int denominator2, char result[], int len);
bool subtract(int characteristic1, int numerator1, int denominator1, int characteristic2, int numerator2, int denominator2, char result[], int len); 

bool multiply(int characteristic1, int numerator1, int denominator1, int characteristic2, int numerator2, int denominator2, char result[], int len);
bool divide(int characteristic1, int numerator1, int denominator1, int characteristic2, int numerator2, int denominator2, char result[], int len);

int LCM(int a, int b);
int countDigit(int num);
int pow(int base, int power);

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
    int characteristic1, numerator1, denominator1;
    int characteristic2, numerator2, denominator2;

    //initialize the values
    characteristic1 = 10;
    numerator1 = 1;
    denominator1 = 2;

    characteristic2 = 2;
    numerator2 = 2;
    denominator2 = 3; 

    //if the c-string can hold at least the characteristic
    if(add(characteristic1, numerator1, denominator1, characteristic2, numerator2, denominator2, answer, 10))
    {
        //display string with answer 4.1666666 (cout stops printing at the null terminating character)
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on add"<<endl;
    }

    if(divide(characteristic1, numerator1, denominator1, characteristic2, numerator2, denominator2, answer, 10))
    {
        //display string with answer
        cout<<"Answer: "<<answer<<endl;
    }
    else
    {
        //display error message
        cout<<"Error on divide"<<endl;
    }

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
bool add(int characteristic1, int numerator1, int denominator1, int characteristic2, int numerator2, int denominator2, char result[], int len)
{
    //variables to keep an ongoing calculation to eventually convert to a string
    int resultCharacteristic = 0; 
    int resultNumerator = 0; 
    int resultDenominator = 0; 
    //will be used throuought the function index through the array
    int resultIndex = 0; 
    //if denominators are different, we must cross multiply the fractions
    if (denominator1 != denominator2) {
        int lcm = LCM(denominator1, denominator2);
        numerator1 *= denominator2;
        numerator2 *= denominator1; 
        resultDenominator = lcm; 
    }
    //otherwise the denominator is arbitrarily assigned of the inputted denominators
    else {
        resultDenominator = denominator1; 
    }
    resultNumerator = numerator1 + numerator2; 

    //convert the improper fraction if necessary
    if (resultNumerator > resultDenominator) {
        resultCharacteristic += resultNumerator / resultDenominator; 
        resultNumerator = resultNumerator % resultDenominator;
    }
    resultCharacteristic += characteristic1 + characteristic2; 

    int characteristicLength = countDigit(resultCharacteristic);
    //if the restult is too large, return false 
    if (characteristicLength > len) {
        cout << "Error: the characteristic is too large for the array" << endl; 
        return false; 
    //else convert the characteristics into chars, digit by digit
    } else {
        for (int i = characteristicLength; i > 0; i--) {
            //gets the first digit
            int digit = resultCharacteristic / pow(10, i-1); 
            cout << digit << endl; 
            //this effectively converts the digit into a char
            char cDigit = '0' + digit; 
            result[resultIndex] = cDigit; 
            //takes the remainder of the digits to be used in the next iteration of the loop
            resultCharacteristic = resultCharacteristic % resultCharacteristic / pow(10, i-1);
            resultIndex++; 
        }
    }

    result[resultIndex] = '.';
    resultIndex++;
    result[resultIndex] = '\0';
    // result[1] = '.';
    // result[2] = '1';
    // result[3] = '6';
    // result[4] = '6';
    // result[5] = '6';
    // result[6] = '6';
    // result[7] = '6';
    // result[8] = '6';
    // result[9] = '\0';

    return true;
}
//--
bool subtract(int characteristic1, int numerator1, int denominator1, int characteristic2, int numerator2, int denominator2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to subtract the two numbers
    return true;
}
//--
bool multiply(int characteristic1, int numerator1, int denominator1, int characteristic2, int numerator2, int denominator2, char result[], int len)
{
    //hard coded return value to make the code compile
    //you will have to come up with an algorithm to multiply the two numbers
    return true;
}
//--
bool divide(int characteristic1, int numerator1, int denominator1, int characteristic2, int numerator2, int denominator2, char result[], int len)
{
    //you will have to come up with an algorithm to divide the two numbers
    //hard coded return value to make the main() work
    result[0] = '0';
    result[1] = '.';
    result[2] = '5';
    result[3] = '6';
    result[4] = '2';
    result[5] = '5';
    result[6] = '\0';
    
    return true;
}

//takes two ints and returns their least common multiple 
int LCM(int a, int b)
{
    int greater = max(a, b);
    int smallest = min(a, b);
    //loop finds the first multiple of the greater number that is divisible by the smaller number
    for (int i = greater; ; i += greater) {
        if (i % smallest  == 0)
            return i;
    }
}

//takes in a number, returns number of digits
int countDigit(int num) {
    // Base case
    if (num == 0) {
        return 1;
    }
    int count = 0;
    // Iterate until num has digits remaining
    while (num != 0) {
        // Remove rightmost digit
        num = num / 10;
        // Increment digit count by 1
        count++;
  }
  return count;
}

int pow(int base, int power) {
    int product = 1; 
    for (int i = 0; i < power; i++) {
        product *= base; 
    }
    return product; 
}