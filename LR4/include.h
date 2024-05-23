#include <iostream>
#include <string>
#include <fstream>


class FractionNumber {


private:
	int* numerator;
	int* denominator;
	static int operationsCount;


public:

	//Consturctor with parameters
	FractionNumber(int num, int denom) : numerator(new int(num)), denominator(new int(denom)) {}


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


	FractionNumber add(const FractionNumber& otherFraction) {
		int resultNum = *numerator * (*otherFraction.denominator) + (*otherFraction.numerator) * *denominator;
		int resultDenom = *denominator * (*otherFraction.denominator);
		FractionNumber::operationsCount++;
		return FractionNumber(resultNum, resultDenom);
	}


	FractionNumber subtract(const FractionNumber& otherFraction) {
		int resultNum = *numerator * (*otherFraction.denominator) - (*otherFraction.numerator) * *denominator;
		int resultDenom = *denominator * (*otherFraction.denominator);
		FractionNumber::operationsCount++;
		return FractionNumber(resultNum, resultDenom);
	}


	FractionNumber multiply(const FractionNumber& otherFraction) {
		int resultNum = *numerator * (*otherFraction.numerator);
		int resultDenom = *denominator * (*otherFraction.denominator);
		FractionNumber::operationsCount++;
		return FractionNumber(resultNum, resultDenom);
	}


	FractionNumber divide(const FractionNumber& otherFraction) {
		int resultNum = *numerator * (*otherFraction.denominator);
		int resultDenom = *denominator * (*otherFraction.numerator);
		FractionNumber::operationsCount++;
		return FractionNumber(resultNum, resultDenom);
	}


	void display() {
		std::cout << *numerator << "/" << *denominator << std::endl;
	}


	static void displayCount() {
		std::cout << "Number of Fraction objects created: " << operationsCount << std::endl;
	}

	//LR2

	FractionNumber operator+(const FractionNumber& otherFraction) const {
		int resultNum = *numerator * (*otherFraction.denominator) + (*otherFraction.numerator) * *denominator;
		int resultDenom = *denominator * (*otherFraction.denominator);
		FractionNumber::operationsCount++;
		return FractionNumber(resultNum, resultDenom);
	}

	FractionNumber operator-(const FractionNumber& otherFraction) const {
		int resultNum = *numerator * (*otherFraction.denominator) - (*otherFraction.numerator) * *denominator;
		int resultDenom = *denominator * (*otherFraction.denominator);
		FractionNumber::operationsCount++;
		return FractionNumber(resultNum, resultDenom);
	}

	friend FractionNumber operator+(int value, const FractionNumber& otherFraction) {
		int resultNum = value * (*otherFraction.denominator) + *otherFraction.numerator;
		int resultDenom = *otherFraction.denominator;
		FractionNumber::operationsCount++;
		return FractionNumber(resultNum, resultDenom);
	}

	friend FractionNumber operator-(int value, const FractionNumber& otherFraction) {
		int resultNum = value * (*otherFraction.denominator) - *otherFraction.numerator;
		int resultDenom = *otherFraction.denominator;
		FractionNumber::operationsCount++;
		return FractionNumber(resultNum, resultDenom);
	}

	operator float() const {
		return static_cast<float>(*numerator) / static_cast<float>(*denominator); //static_cast - ��������������� ��������� ����
	}

	FractionNumber& operator=(const FractionNumber& otherFraction) {
		if (this != &otherFraction) { //������ �������� ����� �������� ������ �� ������������ ��� ����, ���� ����� �� ����������, �� �� ����������� ������, ����� �� �������� ������ �� ��� ���������� ������� ������.
			delete numerator;
			delete denominator;

			numerator = new int(*otherFraction.numerator);
			denominator = new int(*otherFraction.denominator);
		}
		return *this;
	}

	//LR 3
	// 
	//���������� ��������� ������

	friend std::ostream& operator<< (std::ostream& os, const FractionNumber& otherFraction) {
		os << *otherFraction.numerator << "/" << *otherFraction.denominator << std::endl;
		return os;
	}
	//���������� ��������� �����
	friend std::istream& operator>> (std::istream& is, FractionNumber& otherFraction) {
		int num, denom;
		char slash;
		is >> num >> slash >> denom;
		otherFraction = FractionNumber(num, denom);
		FractionNumber::operationsCount++;
		return is;
	}

	//���������� � ����
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

	//������ �� �����
	void loadFromFile(const std::string& filename) {
		std::ifstream file(filename);
		if (file.is_open()) {
			int num, denom;
			char slash;
			file >> num >> slash >> denom;
			*numerator = num;
			*denominator = denom;
			file.close();
		}
		else {
			std::cerr << "Error: file not found." << std::endl;
		}
	}

	//���������� � �������� ����
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

	//�������� �� ��������� �����
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
int FractionNumber::operationsCount = 0;



// ����������� ����� CalculatedFraction
class CalculatedFraction : public FractionNumber {
private:
	float result;

public:
	CalculatedFraction(int num, int denom) : FractionNumber(num, denom), result(static_cast<float>(num) / denom) {}

	float getResult() const {
		return result;
	}

	void display() {
		FractionNumber::display();
		std::cout << "Result: " << result << std::endl;
	}
};

// ����������� ����� MixedFraction
class MixedFraction : public FractionNumber {
private:
	int wholePart;

public:
	MixedFraction(int whole, int num, int denom) : FractionNumber(num, denom), wholePart(whole) {}

	void display() {
		std::cout << wholePart << " ";
		FractionNumber::display();
	}

	int getWholePart() const {
		return wholePart;
	}
};