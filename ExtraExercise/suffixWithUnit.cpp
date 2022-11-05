#include <iostream>

int NumberOfDigit(int number) {
    int count = 0;
    while (number) {
        number /= 10;
        count++;
    }
    return count;
}

int pow(int x, int n) {
    int returnValue = 1;
    for (int i = 0; i < n; i++) {
        returnValue *= x;
    }
    return returnValue;
}

std::string suffixWithUnit(double number) {
    std::string numberValue = "";
    std::string suffixValue = "";
    if (NumberOfDigit(number) > 24) {
        numberValue = std::to_string(number / pow(10, 24));
        suffixValue = " Yotta";
    } else if (NumberOfDigit(number) > 21) {
        numberValue = std::to_string(number / pow(10, 21));
        suffixValue = " Zetta";
    } else if (NumberOfDigit(number) > 18) {
        numberValue = std::to_string(number / pow(10, 18));
        suffixValue = " Exa";
    } else if (NumberOfDigit(number) > 15) {
        numberValue = std::to_string(number / pow(10, 15));
        suffixValue = " Peta";
    } else if (NumberOfDigit(number) > 12) {
        numberValue = std::to_string(number / pow(10, 12));
        suffixValue = " Tera";
    } else if (NumberOfDigit(number) > 9) {
        numberValue = std::to_string(number / pow(10, 9));
        suffixValue = " Giga";
    } else if (NumberOfDigit(number) > 6) {
        numberValue = std::to_string(number / pow(10, 6));
        suffixValue = " Mega";
    } else if (NumberOfDigit(number) > 3) {
        numberValue = std::to_string(number / pow(10, 3));
        suffixValue = " Kilo";
    } else {
        numberValue = std::to_string(number);
    }
    while (numberValue[numberValue.length() - 1] == '0') {
        numberValue.pop_back();
    }
    if (numberValue[numberValue.length() - 1] == '.') {
        numberValue.pop_back();
    }
    return numberValue + suffixValue;
}

int main() {
    double testNumber = 0.2;
    std::cout << suffixWithUnit(testNumber);
    return 0;
}