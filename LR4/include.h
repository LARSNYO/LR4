﻿#include <iostream>
#include <string>
#include <fstream>

class FractionNumber {

private:
	int* numerator;
	int* denominator;
	static int operationsCount;

public:

	//Consturctor with parameters
	FractionNumber(int num, int denom) : numerator(new int(num)), denominator(new int(denom)) {
		if (denom == 0) {
			throw std::invalid_argument("Denominator cannot be zero.");
		}
	}

	//Copy constructor
	FractionNumber(const FractionNumber& otherFraction) : numerator(new int(*otherFraction.numerator)), denominator(new int(*otherFraction.denominator)) {}

	////Default Constructor
	FractionNumber() : FractionNumber(5, 9) {}

	//Destructor
	~FractionNumber() {
		delete numerator;
		delete denominator;
		std::cout << "Fraction object is being destroyed." << std::endl;
	}

	//Method for adding fractions
	FractionNumber add(const FractionNumber& otherFraction) const {
		int resultNum = *numerator * (*otherFraction.denominator) + (*otherFraction.numerator) * *denominator;
		int resultDenom = *denominator * (*otherFraction.denominator);
		FractionNumber::operationsCount++;
		return FractionNumber(resultNum, resultDenom);
	}
	
	//Method for subtracting fractions
	FractionNumber subtract(const FractionNumber& otherFraction) const {
		int resultNum = *numerator * (*otherFraction.denominator) - (*otherFraction.numerator) * *denominator;
		int resultDenom = *denominator * (*otherFraction.denominator);
		FractionNumber::operationsCount++;
		return FractionNumber(resultNum, resultDenom);
	}

	//Method for multiplying fractions
	FractionNumber multiply(const FractionNumber& otherFraction) const {
		int resultNum = *numerator * (*otherFraction.numerator);
		int resultDenom = *denominator * (*otherFraction.denominator);
		FractionNumber::operationsCount++;
		return FractionNumber(resultNum, resultDenom);
	}

	//Method for dividing fractions
	FractionNumber divide(const FractionNumber& otherFraction) const {
		if (*otherFraction.numerator == 0) {
			throw std::invalid_argument("Division by zero.");
		}
		int resultNum = *numerator * (*otherFraction.denominator);
		int resultDenom = *denominator * (*otherFraction.numerator);
		FractionNumber::operationsCount++;
		return FractionNumber(resultNum, resultDenom);
	}
	
	//Method for displaying fractions on the screen
	void display() const {
		std::cout << *numerator << "/" << *denominator << std::endl;
	}

	//Operation counter
	static void displayCount() {
		std::cout << "Number of Fraction objects created: " << operationsCount << std::endl;
	}

	//Overloading the fraction addition operator
	FractionNumber operator+(const FractionNumber& otherFraction) const {
		return add(otherFraction);
	}

	//Overloading the fraction subtraction operator
	FractionNumber operator-(const FractionNumber& otherFraction) const {
		return subtract(otherFraction);
	}

	//Overloading the operator for adding a number with a fraction
	friend FractionNumber operator+(int value, const FractionNumber& otherFraction) {
		int resultNum = value * (*otherFraction.denominator) + *otherFraction.numerator;
		int resultDenom = *otherFraction.denominator;
		FractionNumber::operationsCount++;
		return FractionNumber(resultNum, resultDenom);
	}

	//Overloading the operator to subtract a number with a fraction
	friend FractionNumber operator-(int value, const FractionNumber& otherFraction) {
		int resultNum = value * (*otherFraction.denominator) - *otherFraction.numerator;
		int resultDenom = *otherFraction.denominator;
		FractionNumber::operationsCount++;
		return FractionNumber(resultNum, resultDenom);
	}

	//Overloading the float cast
	operator float() const {
		return static_cast<float>(*numerator) / static_cast<float>(*denominator); //static_cast - преобразователь числового типа
	}

	//Assignment operator overloading
	FractionNumber& operator=(const FractionNumber& otherFraction) {
		if (this != &otherFraction) { //делаем проверку чтобы оператор объект не присваивался сам себе, если этого не происходит, то мы освобождаем память, чтобы не потерять ссылки на уже выделенные участки памяти.
			delete numerator;
			delete denominator;

			numerator = new int(*otherFraction.numerator);
			denominator = new int(*otherFraction.denominator);
		}
		return *this;
	}

	//Output operator overloading
	friend std::ostream& operator<< (std::ostream& os, const FractionNumber& otherFraction) {
		os << *otherFraction.numerator << "/" << *otherFraction.denominator << std::endl;
		return os;
	}
	//Input operator overloading
	friend std::istream& operator>> (std::istream& is, FractionNumber& otherFraction) {
		int num, denom;
		char slash;
		is >> num >> slash >> denom;
		if (denom == 0) {
			throw std::invalid_argument("Denominator cannot be zero.");
		}
		otherFraction = FractionNumber(num, denom);
		FractionNumber::operationsCount++;
		return is;
	}

	//Save to file
	void saveToFile(const std::string& filename) const {
		std::ofstream file(filename);
		if (file.is_open()) {
			file << *numerator << "/" << *denominator << std::endl;
			std::cout << "File saved ! " << std::endl;
			file.close();
		}
		else {
			std::cerr << "Error: file not found." << std::endl;
		}
	}

	//Load from file
	void loadFromFile(const std::string& filename) {
		std::ifstream file(filename);
		if (file.is_open()) {
			int num, denom;
			char slash;
			file >> num >> slash >> denom;
			if (denom == 0) {
				throw std::invalid_argument("Denominator cannot be zero.");
			}
			*numerator = num;
			*denominator = denom;
			file.close();
		}
		else {
			std::cerr << "Error: file not found." << std::endl;
		}
	}

	//Save to binary file
	void saveToBinaryFile(const std::string& filename) const {
		std::ofstream file(filename, std::ios::binary);
		if (file.is_open()) {
			file.write(reinterpret_cast<char*>(numerator), sizeof(int));
			file.write(reinterpret_cast<char*>(denominator), sizeof(int));
			std::cout << "File saved ! " << std::endl;
			file.close();
		}
		else {
			std::cerr << "Error: file not found." << std::endl;
		}
	}

	//Load from binary file
	void loadFromBinaryFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::binary);
		if (file.is_open()) {
			file.read(reinterpret_cast<char*>(numerator), sizeof(int));
			file.read(reinterpret_cast<char*>(denominator), sizeof(int));
			file.close();
		}
		else {
			std::cerr << "Error: file not found." << std::endl;
		}
	}

};

// Derived class CalculatedFraction
class CalculatedFraction : public FractionNumber {
private:
	float result;

public:
	CalculatedFraction(int num, int denom) : FractionNumber(num, denom), result(static_cast<float>(num) / denom) {}

	float getResult() const {
		return result;
	}

	void display() const {
		FractionNumber::display();
		std::cout << "Result: " << result << std::endl;
	}
};

// Derived class MixedFraction
class MixedFraction : public FractionNumber {
private:
	int wholePart;

public:
	MixedFraction(int whole, int num, int denom) : FractionNumber(num, denom), wholePart(whole) {}

	void display() const {
		std::cout << wholePart << " ";
		FractionNumber::display();
	}

	int getWholePart() const {
		return wholePart;
	}
};
