#include <iostream>
#include <string>
#include <climits>
#include <cmath> //needed for GCC but unnecesary with MSVC
class BigInteger {
protected:
    short intz[500] = {0};
    int digitCount = 0;
    int getDigCount(long long val) {
        int digCount = 1;
        while (true) {
            val /= 10;
            if (val > 0) {
                digCount++;
            }
            else { break; }
        }
        if (digCount > 500) {
            digCount = 500;
        }
        return digCount;
    }
public:

    BigInteger() {
        digitCount = 1;
    }

    BigInteger(long val) {
        digitCount = getDigCount(val);
        val = std::abs(val);
        //std::cout << digitCount << "\n";
        for (int i = 0; i < digitCount; i++) {
            short* thisDigit = &intz[499 - (digitCount - i) + 1];

            *thisDigit = (val / (int)std::pow(10, digitCount - 1 - i)) % 10;
            //std::cout << *thisDigit << "\n";
        }
    }
    

    BigInteger add(BigInteger bigInt2) {
        BigInteger bigInt1 = *this;
        int c_out = 0;
        int maxDigCount = std::max(bigInt1.digitCount, bigInt2.digitCount);
        bigInt1.digitCount = maxDigCount;
        for (int i = 0; i < maxDigCount; i++) {
            short* bigInt1Digit = &bigInt1.intz[499 - i];
            short* bigInt2Digit = &bigInt2.intz[499 - i];



            short sum = c_out + *bigInt1Digit + *bigInt2Digit;

            c_out = sum / 10;
            *bigInt1Digit = sum % 10;


            if ((i == (maxDigCount - 1)) && (c_out > 0)) {
                maxDigCount++;
                bigInt1.digitCount++;
            }

        }

        return bigInt1;
    }

    std::string toString() {
        std::string stringVal = "";
        for (int i = 0; i < digitCount; i++) {
            short *thisDigit = &intz[499 - (digitCount - i) + 1];
            
            stringVal += std::to_string(*thisDigit);
        }
        return stringVal;
    }

    int getDigitCount() {
        return digitCount;
    }
};

long long fib(int n) {
    const double PHI = (1 + std::sqrt(5)) / 2;
    return (long long)(std::pow(PHI, n) / std::sqrt(5) + 0.5);
     
}

int main() {
    BigInteger num1, num2, num3;
    num1 = BigInteger();
    num2 = BigInteger(1);
    int n = 800;
    std::cout << num1.toString() << std::endl;
    std::cout << num2.toString() << std::endl;
    for (int i = 2; i < n; i++) {
        num3 = num1.add(num2);
        std::cout << num3.toString() << std::endl;
        num1 = num2;
        num2 = num3;
        num3 = num1.add(num2);
    }
    std::cout << num3.toString() << std::endl;
    //std::cout << fib(n);

    return 0;
}
