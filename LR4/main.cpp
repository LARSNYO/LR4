#include "include.h"
int FractionNumber::operationsCount = 0;

int main() {

    FractionNumber fraction1(3, 4);
    CalculatedFraction calcFraction(3, 4);
    MixedFraction mixedFraction(1, 3, 4);

    std::cout << "Fraction: ";
    fraction1.display();

    std::cout << "Calculated Fraction: ";
    calcFraction.display();

    std::cout << "Mixed Fraction: ";
    mixedFraction.display();

    // Копирование объектов
    FractionNumber copiedFraction = fraction1;
    CalculatedFraction copiedCalcFraction = calcFraction;
    MixedFraction copiedMixedFraction = mixedFraction;

    std::cout << "\nCopied Fraction: ";
    copiedFraction.display();

    std::cout << "Copied Calculated Fraction: ";
    copiedCalcFraction.display();

    std::cout << "Copied Mixed Fraction: ";
    copiedMixedFraction.display();

    return 0;
}