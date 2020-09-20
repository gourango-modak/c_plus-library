#ifndef BIGINT
#define BIGINT


class BigInteger {
	
	// Properties

	const char *number;
	int length = 100000;

public:

	// Methods

	// Constructors

	BigInteger();
	BigInteger(const char *num);
	BigInteger(const long long num);

	// Copy constructor

	BigInteger(const BigInteger &num);

	// Operator overloading

	BigInteger operator=(const BigInteger &num);

	BigInteger operator=(const char *num);

	friend ostream& operator<<(ostream &os, BigInteger &num);

	// Addition

	char* add(const BigInteger &num);

	bool isSmaller(const char *n1, const char *n2);

	char* operation(char ops, const char *n1, const char *n2);

	// subtract

	const char* sub(const BigInteger &num);
	
	// Multiplication
	
	const char* multipliar(const char* n1, const char* n2);
	const char* mul(const BigInteger &num);
};


#endif