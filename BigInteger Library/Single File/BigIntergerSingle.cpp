#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;


class BigInteger {
	
	// Properties

	const char *number;
	int length = 100000;

public:

	// Methods

	// Constructors

	BigInteger() {
		this->number = new char[length];
	}
	BigInteger(const char *num) {
		this->number = new char[length];
		this->number = num;
	}

	// Copy constructor

	BigInteger(const BigInteger &num) {
		this->number = new char[length];
		this->number = num.number;
	}

	// Operator overloading

	BigInteger operator=(const BigInteger &num) {
		this->number = num.number;
		return *this;
	}

	BigInteger operator=(const char *num) {
		this->number = num;
		return *this;
	}

	friend ostream& operator<<(ostream &os, BigInteger &num) {
		os << num.number;
		return os;
	}

	// Addition

	char* add(const BigInteger &num) {

		bool isFirstNumberSmall = 0;

		if(this->number[0] != '-' && num.number[0] != '-')
			return operation('+', this->number, num.number);
		
		else if(this->number[0] == '-' && num.number[0] != '-') {
			
			isFirstNumberSmall = isSmaller(this->number, num.number);
			
			if(isFirstNumberSmall) {
				return operation('-', num.number, this->number+1);
			} else {
				const char *result = operation('-', this->number+1, num.number);
				
				int nonZeroPos = 0;
				for (int i = 0; i < strlen(result); ++i)
					if(result[i] != '0') {nonZeroPos = i; break;}
				
				char *finalResult = new char[length];
				finalResult[0] = '-';
				strcat(finalResult+1, result+nonZeroPos);
				return finalResult;
			}
		}
		else if(this->number[0] != '-' && num.number[0] == '-') {
			
			isFirstNumberSmall = isSmaller(num.number, this->number);
			
			if(isFirstNumberSmall) {
				return operation('-', this->number, num.number+1);
			} else {
				char *result = operation('-', num.number+1, this->number);
				
				int nonZeroPos = 0;
				for (int i = 0; i < strlen(result); ++i)
					if(result[i] != '0') {nonZeroPos = i; break;}
				
				char *finalResult = new char[length];
				finalResult[0] = '-';
				strcat(finalResult+1, result+nonZeroPos);
				return finalResult;
			}
		}

		char *result = operation('+', num.number+1, this->number+1);
		char *finalResult = new char[length];
		finalResult[0] = '-';
		strcat(finalResult+1, result);
		return finalResult;
	}

	bool isSmaller(const char *n1, const char *n2) {
		int n1Len = strlen(n1);
		int n2Len = strlen(n2);

		if(n1[0] == '-') n1Len--;
		if(n2[0] == '-') n2Len--;

		if(n1Len < n2Len) return true;
		else if (n1Len > n2Len) return false;

		for(int i = 0; i < n1Len; i++) {
			if(n1[n1Len - i - 1] - '0' < n2[n2Len - i - 1] - '0') return true;
			else if(n1[n1Len - i - 1] - '0' > n2[n2Len - i - 1] - '0') return false;
		}
		return false;
	}

	char* operation(char ops, const char *n1, const char *n2) {

		int num1Len = strlen(n1);
		int num2Len = strlen(n2);
		int maxLen = max(num1Len, num2Len);
		int minLen = min(num1Len, num2Len);

		char *result = new char[maxLen+1];

		int carry = 0, ptr = 0, val = 0, i = 0, k = 0, q = 0;
		
		for(k = num1Len-1, q = num2Len-1; i < minLen; i++) {
			if(ops == '+') {
				val = (n1[k--] - '0') + (n2[q--] - '0') + carry;
				result[ptr++] = val%10 + '0';
				carry = val/10;
			} else {
				val = (n1[k--] - '0') - (n2[q--] - '0') - carry;
				if(val < 0) val += 10, carry = 1; else carry = 0;
				result[ptr++] = val + '0';
			}
		}

		while(i < num2Len) {
			if(ops == '+') {
				val = (n2[q--] - '0') + carry;
				result[ptr++] = val%10 + '0';
				carry = val/10;
			} else {
				val = (n2[k--] - '0') - carry;
				if(val < 0) val += 10, carry = 1; else carry = 0;
				result[ptr++] = val + '0';
			}
			i++;
		}

		while(i < num1Len) {
			if(ops == '+') {
				val = (n1[k--] - '0') + carry;
				result[ptr++] = val%10 + '0';
				carry = val/10;
			} else {
				val = (n1[k--] - '0') - carry;
				if(val < 0) val += 10, carry = 1; else carry = 0;
				result[ptr++] = val + '0';
			}
			i++;
		}

		if(carry) result[ptr++] = carry + '0';

		reverse(result, result+ptr);
		result[ptr] = '\0';

		return result;
	}

	// subtract

	const char* sub(const BigInteger &num) {

		bool isFirstNumberSmall = 0;
		
		isFirstNumberSmall = isSmaller(this->number, num.number); // if first number smaller then second number then return true otherwise false

		// two number are positive
		
		if(this->number[0] != '-' && num.number[0] != '-') {
			
			// 11 - 99
			
			if(isFirstNumberSmall) {

				const char *result = operation('-', num.number, this->number);
				
				int nonZeroPos = 0;
				for (int i = 0; i < strlen(result); ++i)
					if(result[i] != '0') {nonZeroPos = i; break;}
				
				char *finalResult = new char[length];
				finalResult[0] = '-';
				strcat(finalResult+1, result+nonZeroPos);
				return finalResult;
			}
			
			// 99 - 11
			
			const char *result = operation('-', this->number, num.number);
			int nonZeroPos = strlen(result)-1;
			for (int i = 0; i < strlen(result)-1; ++i)
				if(result[i] != '0') {nonZeroPos = i; break;}
			return (result+nonZeroPos);
		}
		
		// -11 - 99
		
		else if(this->number[0] == '-' && num.number[0] != '-') {
			
			const char *result = operation('+', this->number+1, num.number);
			
			int nonZeroPos = 0;
			for (int i = 0; i < strlen(result); ++i)
				if(result[i] != '0') {nonZeroPos = i; break;}
			
			char *finalResult = new char[length];
			finalResult[0] = '-';
			strcat(finalResult+1, result+nonZeroPos);
			return finalResult;
		}
		
		// 11 - (-99)
		
		else if(this->number[0] != '-' && num.number[0] == '-') {
			return operation('+', num.number+1, this->number);
		}

		// -11 - (-99)

		if(isFirstNumberSmall) {
			
			const char *result = operation('-', num.number+1, this->number+1);
		
			int nonZeroPos = strlen(result)-1;
			for (int i = 0; i < strlen(result); ++i)
				if(result[i] != '0') {nonZeroPos = i; break;}
			return result+nonZeroPos;
		}

		// -99 - (-11)

		const char *result = operation('-', this->number+1, num.number+1);
		
		int nonZeroPos = strlen(result)-1;
		for (int i = 0; i < strlen(result)-1; ++i)
			if(result[i] != '0') {nonZeroPos = i; break;}

		if(*(result+nonZeroPos) == '0') return "0";
		
		char *finalResult = new char[length];
		finalResult[0] = '-';
		strcat(finalResult+1, result+nonZeroPos);
		
		return finalResult;
	}
	
};


// int main()
// {
// 	BigInteger x = "100", y = "89";
// 	cout << x.add(y) << "\n";
// }