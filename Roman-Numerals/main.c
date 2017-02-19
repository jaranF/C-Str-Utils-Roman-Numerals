#include <stdio.h>
#include <string.h>
#include <math.h>
//Runtime_Environment
#include <limits.h>		/* PATH_MAX */

#define kMaxToConvert            3999
#define kCardinalOfDigits           4
#define kASCIIOfsetToIntValue      48
#define kRomanNumeralDivisorPoints 13
#define kMaxConsecutiveCharRepeats  3

char* Executables_Path( char* );
char* RomanNumerals( const char* );
char* ConvertToRoman( int, char*, int[kRomanNumeralDivisorPoints][2][3], int );
char* ConvertIntArrayToChar( int*, int, char*, int );

int main(int argc, const char * argv[])
{
    int userArgsOffset = 0;
    char buffToConvertArg[kCardinalOfDigits +1];  //Four chars for the integer positions plus one for NUL terminating char
    char filePath[PATH_MAX + 1];
    
    if (argc > 0) {
        if(strstr(argv[0], filePath) != NULL) {
            userArgsOffset = 1;
        } //end if
        strlcpy(buffToConvertArg, argv[userArgsOffset], kCardinalOfDigits+1); //limit the length of whatever user inputs.
        printf("\n------------------\n%s ---raw input\n-------------------\n", argv[userArgsOffset]);
        RomanNumerals(buffToConvertArg);
    } //end if argc > 0 (args length greater than zero
    
    
    
    return 0;
}

char* RomanNumerals(const char* buffDecimalToConvert) {
    char buff[kCardinalOfDigits +1];  //Four chars for the integer positions plus one for NUL terminating char
    char resultingRomanNumber[14]; //Longest r.numeral < 4000 is 3488 =  MMMCDLXXXVIII (13 chars long + 1 for NUL terminaing char)
    int  decimalToConvert = 0;
    unsigned long i, toConvertLen;
    char* buffPointer;
    char c;
    int romanNumerals[kRomanNumeralDivisorPoints][2][3] = {
        {{'M',  0,  0},  1000},
        {{'C',  'M',  0},  900},
        {{'D',  0,  0}, 500},
        {{'C', 'D', 0}, 400},
        {{'C',  0,  0}, 100},
        {{'X', 'C', 0}, 90},
        {{'L',  0,  0}, 50},
        {{'X', 'L', 0}, 40},
        {{'X',  0,  0}, 10},
        {{'I', 'X', 0}, 9},
        {{'V',  0,  0}, 5},
        {{'I', 'V', 0}, 4},
        {{'I',  0,  0}, 1}
        
    };
    // memset(resultingRomanNumber, '\0', sizeof(resultingRomanNumber));
    //strcat(resultingRomanNumber, "A"); this will be added in at to the left of the first \0 char in string buffer array
    strcpy(buff, buffDecimalToConvert);
    //needs to be 0199
    buffPointer = &buff[0] + strlen(buff);
    toConvertLen = strlen(buff);
    i = toConvertLen < kCardinalOfDigits ? toConvertLen : kCardinalOfDigits;
    while ( i > 0 ) {
        c = *(--buffPointer);
        if ( c == '\0' ) { c = '0'; }
        c -= kASCIIOfsetToIntValue;
        decimalToConvert += (int)pow(10, (double)(toConvertLen - i)) * c;
        i--;
    }
    printf("\n----%d----\n", decimalToConvert);
    ConvertToRoman(decimalToConvert, resultingRomanNumber, romanNumerals, 0);
    printf("\n----%s----\n", resultingRomanNumber);
    buffPointer = resultingRomanNumber;
    //   for (i = 0; i < kCardinalOfDigits; i++) {
    //       toIntExploded[i] = buff[i] - kASCIIOfsetToIntValue;
    //       //printf("- %d -\n", toIntExploded[i]);
    //   }
    //   memset(romanNumeralResult,' ',13);
    //   romanNumeralResult[13] = '\0';
    //   puts(romanNumeralResult);
    return buffPointer;
}

char* ConvertToRoman(int toConvert, char* resultingRomanNumber, int romanNumerals[kRomanNumeralDivisorPoints][2][3], int numeralOrdinal ) {
    char romanBuffer[kMaxConsecutiveCharRepeats + 1];
    int numberTimesNumeralRepeats = 1;
    int digitPositionValue = romanNumerals[numeralOrdinal][1][0];
    if ( toConvert == 0) return resultingRomanNumber;
    int divisorResult = toConvert / romanNumerals[numeralOrdinal][1][0];
    memset(romanBuffer, '\0', kMaxConsecutiveCharRepeats + 1);
    printf("++%d++z\n", divisorResult);
    if (divisorResult > 0) {
        ConvertIntArrayToChar(&(romanNumerals[numeralOrdinal][0][0]), 3, romanBuffer, kMaxConsecutiveCharRepeats + 1);
        if (strlen(romanBuffer) == 1) {
            numberTimesNumeralRepeats = divisorResult;
        }
        memset(romanBuffer, romanBuffer[0], numberTimesNumeralRepeats);
        strcat(resultingRomanNumber, romanBuffer);
        if (digitPositionValue != 1) {
            ConvertToRoman(toConvert - (divisorResult * digitPositionValue), resultingRomanNumber,
                           romanNumerals, ++numeralOrdinal);
        }
    } else {
        ConvertToRoman(toConvert, resultingRomanNumber, romanNumerals, ++numeralOrdinal);
    } //end if
    return resultingRomanNumber;
}



char* ConvertIntArrayToChar(int* pointerToArray, int intArraySize, char* charArrayResult, int charArraySize) {
    int i = 0;
    while (*pointerToArray != '\0' && i < intArraySize) {
        charArrayResult[i] = *pointerToArray;
        i++;
        printf("- %d -\n", *pointerToArray);
        pointerToArray++;
    }
    return charArrayResult;
}
//ret romanStringBuilder, incrementable pointer to char array, incrementalable pointer to int array of Numeral values 1000, 500, 100, incrementalble pointer to cooresponding int value of numerals

