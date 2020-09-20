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
		length = strlen(num);
		this->number = new char[length];
		this->number = num;
	}
	BigInteger(const long long num) {
		const string str = to_string(num);
		length = str.length();
		char *n = new char[length];
		strcpy(n, str.c_str());
		this->number = n;
	}

	// Copy constructor

	BigInteger(const BigInteger &num) {
		this->number = new char[strlen(num.number)];
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
				delete result;
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
				delete result;
				return finalResult;
			}
		}

		char *result = operation('+', num.number+1, this->number+1);
		char *finalResult = new char[length];
		finalResult[0] = '-';
		strcat(finalResult+1, result);
		delete result;
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
				delete result;
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
			delete result;
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
		delete result;
		return finalResult;
	}

	// Multiplication

	const char* multipliar(const char* n1, const char* n2) {
		int n1_len = strlen(n1), n2_len = strlen(n2);
		char* res = new char[n1_len+n2_len];
		for (int i = 0; i < n1_len+n2_len; ++i) res[i] = '0';
		int j_n2 = 0, carry = 0, res_len = 0;
		for (int i = 0; i < n1_len; ++i)
		{
			j_n2 = 0, carry = 0;
			for (int j = 0; j < n2_len; ++j)
			{
				int m = (n1[n1_len - i - 1] - '0') * (n2[n2_len - j - 1] - '0') + (res[i+j_n2]-'0') + carry;
				res[i+j_n2] = m%10 + '0';
				carry = m/10;
				j_n2++;
			}
			if(carry) res[i+j_n2] = carry+'0';

		}
		int i = n1_len+n2_len-1;
		for (; i>=0; --i)
			if(res[i] != '0') break;
		if(i == -1) return "0";
		reverse(res, res+i+1);
		res[i+1] = '\0';
		return res;
	}

	const char* mul(const BigInteger &num) {

		bool negSign = 0;
		if((this->number[0] == '-' || num.number[0] == '-') && (this->number[0] != '-' || num.number[0] != '-')) negSign = 1;
		
		int len1 = strlen(this->number), len2 = strlen(num.number);
		
		if(this->number[0] == '-') len1--;
		if(num.number[0] == '-') len2--;
		
		const char *res;
		if(len1 > len2) {
			if(this->number[0] == '-' && num.number[0] != '-')
				res = multipliar(num.number, this->number+1);
			else if(this->number[0] != '-' && num.number[0] == '-')
				res = multipliar(num.number+1, this->number);
			else if(this->number[0] == '-' && num.number[0] == '-')
				res = multipliar(num.number+1, this->number+1);
			else res = multipliar(num.number, this->number);
		}
		else {
			if(this->number[0] == '-' && num.number[0] != '-')
				res = multipliar(this->number+1, num.number);
			else if(this->number[0] != '-' && num.number[0] == '-')
				res = multipliar(this->number, num.number+1);
			else if(this->number[0] == '-' && num.number[0] == '-')
				res = multipliar(this->number+1, num.number+1);
			else res = multipliar(this->number, num.number);
		}
		if(negSign) {
			char *finalResult = new char[strlen(res)];
			finalResult[0] = '-';
			strcat(finalResult+1, res);
			delete res;
			return finalResult;
		}
		return res;
	}

	
};


int main()
{
	BigInteger x = "99", y = "-999";

	cout << y.mul(x) << "\n";
}