#ifndef BIGINT
#define BIGINT


class BigInteger {
	
	// Properties

	char *number;
	int length = 1000;

public:

	// Methods

	// Constructors

	BigInteger();
	BigInteger(char*);
    BigInteger(std::string);
	BigInteger(const char*);
	BigInteger(const long long);

	// Copy constructor

	BigInteger(const BigInteger &num);

	// Property

	void setNumber(char* num);

	// Operator overloading

	BigInteger operator=(BigInteger &num);

    BigInteger operator=(std::string num);

	BigInteger operator=(char *num);

    BigInteger operator=(const char *num);

	// Pre Increment Operator

	BigInteger operator++();

	BigInteger operator--();

	// Post Increment Operator

	BigInteger operator++(int);

	BigInteger operator--(int);


	// Modulo Operator
	char* operator%(BigInteger &dividend);

	// Divide Operator
	char* operator/(BigInteger &dividend);

	friend std::ostream& operator<<(std::ostream &os, BigInteger &num);

    friend std::istream& operator>>(std::istream &is, BigInteger &num);

	// Addition

	char* add(BigInteger &num);

	char isSmaller(char *n1, char *n2);

	char* operation(char ops, char *n1, char *n2);
	
	// subtract

	char* sub(BigInteger &num);
	
	// Multiplication

	char* multipliar(char* n1, char* n2);

	char* mul(BigInteger &num);

	// Division

    std::pair<char*, char*> divOps(BigInteger &divisor, BigInteger &dividend);

	char* div(BigInteger &dividend);

	// Modulo
	
    char* mod(BigInteger &dividend);

};


#endif