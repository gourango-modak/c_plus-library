#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#include "biginteger.h"


// Constructors

BigInteger::BigInteger() {
	this->number = new char[length];
}
BigInteger::BigInteger(char *num) {
	length = strlen(num);
	this->number = new char[length];
	strcpy(this->number, num);
}
BigInteger::BigInteger(string num) {
	length = num.length();
	this->number = new char[length];
	strcpy(this->number, num.c_str());
}
BigInteger::BigInteger(const char *num) {
	length = strlen(num);
	this->number = new char[length];
	strcpy(this->number, num);
}
BigInteger::BigInteger(const long long num) {
	string str = to_string(num);
	length = str.length();
	char *n = new char[length];
	strcpy(n, str.c_str());
	this->number = n;
}

// Copy constructor

BigInteger::BigInteger(const BigInteger &num) {
	length = strlen(num.number);
	number = new char[length];
	strcpy(number, num.number);
}

// Property

void BigInteger::setNumber(char* num) {
	strcpy(this->number, num);
}

// Operator overloading

BigInteger BigInteger::operator=(BigInteger &num) {
	delete[] this->number;
	length = strlen(num.number);
	char *temp = new char[length];
	strcpy(temp, num.number);
	this->number = temp;
	return *this;
}

BigInteger BigInteger::operator=(std::string num) {
	delete[] this->number;
	length = num.length();
	char *temp = new char[length];
	strcpy(temp, num.c_str());
	this->number = temp;
	return *this;
}

BigInteger BigInteger::operator=(char *num) {
	delete[] this->number;
	length = strlen(num);
	char *temp = new char[length];
	strcpy(temp, num);
	this->number = temp;
	return *this;
}

BigInteger BigInteger::operator=(const char *num) {
	delete[] this->number;
	length = strlen(num);
	char *temp = new char[length];
	strcpy(temp, num);
	this->number = temp;
	return *this;
}

// Pre Increment Operator

BigInteger BigInteger::operator++() {
	BigInteger one(1);
	char *result = this->add(one);
	delete [] this->number;
	this->number = new char[strlen(result)];
	strcpy(this->number, result);
	return *this;
}

BigInteger BigInteger::operator--() {
	BigInteger one(1);
	char *result = this->sub(one);
	delete [] this->number;
	this->number = new char[strlen(result)];
	strcpy(this->number, result);
	return *this;
}

// Post Increment Operator

BigInteger BigInteger::operator++(int) {
	BigInteger temp = *this;
	BigInteger one(1);
	char *result = this->add(one);
	delete [] this->number;
	this->number = new char[strlen(result)];
	strcpy(this->number, result);
	return temp;
}

BigInteger BigInteger::operator--(int) {
	BigInteger temp = *this;
	BigInteger one(1);
	char *result = this->sub(one);
	delete [] this->number;
	this->number = new char[strlen(result)];
	strcpy(this->number, result);
	return temp;
}


// Modulo Operator
char* BigInteger::operator%(BigInteger &dividend) {
	char *result = dividend.mod(*this);
	return result;
}

// Divide Operator
char* BigInteger::operator/(BigInteger &dividend) {
	char *result = dividend.div(*this);
	return result;
}

std::ostream& operator<<(std::ostream &os, BigInteger &num) {
	os << num.number;
	return os;
}

std::istream& operator>>(std::istream &is, BigInteger &num) {
	char arr[1000];
	is >> arr;
	strcpy(num.number, arr);
	return is;
}

// Addition

char* BigInteger::add(BigInteger &num) {

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

char BigInteger::isSmaller(char *n1, char *n2) {
	// Is First Number Small or Not
	int n1Len = strlen(n1);
	int n2Len = strlen(n2);

	if(n1[0] == '-') n1Len--;
	if(n2[0] == '-') n2Len--;

	if(n1[0] == '0' && n2[0] != '0') return 'l';
	else if(n1[0] != '0' && n2[0] == '0') return 'g';
	else if(n1[0] == '0' && n2[0] == '0') return 'e';

	if(n1Len < n2Len) return 'l';
	else if (n1Len > n2Len) return 'g';

	for(int i = 0; i < n1Len; i++) {
		if(n1[i] - '0' < n2[i] - '0') return 'l';
		else if(n1[i] - '0' > n2[i] - '0') return 'g';
	}
	// if two number are equal
	return 'e';
}

char* BigInteger::operation(char ops, char *n1, char *n2) {

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

char* BigInteger::sub(BigInteger &num) {
	
	char isFirstNumberSmall = isSmaller(this->number, num.number);
	// if first number smaller then second number then return true otherwise false

	// two number are positive
	
	if(this->number[0] != '-' && num.number[0] != '-') {
		
		// 11 - 99
		
		if(isFirstNumberSmall == 'l') {

			char *result = operation('-', num.number, this->number);
			
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
		
		char *result = operation('-', this->number, num.number);
		int nonZeroPos = strlen(result)-1;
		for (int i = 0; i < strlen(result)-1; ++i)
			if(result[i] != '0') {nonZeroPos = i; break;}
		return (result+nonZeroPos);
	}
	
	// -11 - 99
	
	else if(this->number[0] == '-' && num.number[0] != '-') {
		
		char *result = operation('+', this->number+1, num.number);
		
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

	if(isFirstNumberSmall == 'l') {
		
		char *result = operation('-', num.number+1, this->number+1);
	
		int nonZeroPos = strlen(result)-1;
		for (int i = 0; i < strlen(result); ++i)
			if(result[i] != '0') {nonZeroPos = i; break;}
		return result+nonZeroPos;
	}

	// -99 - (-11)

	char *result = operation('-', this->number+1, num.number+1);
	
	int nonZeroPos = strlen(result)-1;
	for (int i = 0; i < strlen(result)-1; ++i)
		if(result[i] != '0') {nonZeroPos = i; break;}
	
	char *zero = new char[2];
	zero[0] = '0';
	zero[1] = '\0';
	
	if(*(result+nonZeroPos) == '0') return zero;
	
	char *finalResult = new char[length];
	finalResult[0] = '-';
	strcat(finalResult+1, result+nonZeroPos);
	delete result;
	return finalResult;
}

// Multiplication

char* BigInteger::multipliar(char* n1, char* n2) {
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

	char *zero = new char[2];
	zero[0] = '0';
	zero[1] = '\0';

	int i = n1_len+n2_len-1;
	for (; i>=0; --i)
		if(res[i] != '0') break;
	if(i == -1) return zero;
	reverse(res, res+i+1);
	res[i+1] = '\0';
	return res;
}

char* BigInteger::mul(BigInteger &num) {

	bool negSign = 0;
	if((this->number[0] == '-' || num.number[0] == '-') && (this->number[0] != '-' || num.number[0] != '-')) negSign = 1;
	
	int len1 = strlen(this->number), len2 = strlen(num.number);
	
	if(this->number[0] == '-') len1--;
	if(num.number[0] == '-') len2--;
	
	char *res;
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

// Division

std::pair<char*, char*> BigInteger::divOps(BigInteger &divisor, BigInteger &dividend) {

	BigInteger dividendCopy = dividend;
	
	int divisorLen = strlen(divisor.number);
	int dividendLen = strlen(dividendCopy.number);
	
	char* reminder = new char[divisorLen];
	char* quotient = new char[dividendLen];
	
	int quotientItr = 0;
	int divisorItr = 0;
	
	char *res = new char[dividendLen]; // temporary store the dividend number portion
	
	BigInteger dividendPortion; // suppose we divide 999/11 then 99 is the dividedPortion for the first time
	BigInteger multi_res; // after multiplication we store in this object such as 9*11 = 99
	
	char multipiarPtr[2]; // to Store digit from 1 - 9 for multiplication
	BigInteger multi; // for convert 1-9 digit to BigInteger Object


	char check; // This is for check condition. Is it Less or Greater or Equal

	queue<char> q;
	for(int i=0; i<dividendLen; i++) {
		q.push(dividendCopy.number[i]);
	}

	int resLen = 0;
	
	while(1) {

		int i = resLen;
		for(; !q.empty(); i++) {    // keep storing number until its greater than divisor in (res variable)
			res[i] = q.front();
			q.pop();
			char check = isSmaller(res, divisor.number);
			if(check == 'l') quotient[quotientItr++] = '0';
			if(check == 'g' || check == 'e') break;
		}
		res[i+1] = '\0';

		if(q.empty() && isSmaller(res,divisor.number) == 'l')  {  // If a number is less than divisor
			strcpy(reminder, res);
			break;
		}

		dividendPortion.setNumber(res); // store the dividend portion for divide

		int multipiar = 1;
		char *mul, *mul2;

		for(; ;multipiar++) {
			multipiarPtr[0] = multipiar+'0';
			multipiarPtr[1] = '\0';

			multi.setNumber(multipiarPtr); // store multipiar value like 1,2,3,4,5,6,7,8,9 into object
			
			mul = divisor.mul(multi); // multiplying
			
			check = isSmaller(res, mul);
			if(check == 'l' || check == 'e') break;

			// Second time checking that if next multiplier greater than the dividend or not 

			multipiarPtr[0] = (multipiar+1)+'0';
			multipiarPtr[1] = '\0';
			multi.setNumber(multipiarPtr);

			mul2 = divisor.mul(multi);
			check = isSmaller(res, mul2);
			if(check == 'l') break;
		}
		
		quotient[quotientItr++] = multipiar+'0';
		multi_res.setNumber(mul); // store multiplier Value
		
		res = dividendPortion.sub(multi_res); // Subtract from dividend to multiplier value
		

		// checking res variable equal zero or not. If zero then resLen = 0
		int rLen = strlen(res);
		for(i=0; i<rLen; i++) if(res[i] != '0') break;
		resLen = rLen - i;
	}

	quotient[quotientItr] = '\0';
	int zeroBreakItr1 = 0, zeroBreakItr2 = 0;
	for(; zeroBreakItr1<quotientItr-1; zeroBreakItr1++) if(quotient[zeroBreakItr1] != '0') break;
	for(; zeroBreakItr2<divisorItr-1; zeroBreakItr2++) if(reminder[zeroBreakItr2] != '0') break;
	return make_pair(zeroBreakItr1+quotient, zeroBreakItr2+reminder);
}

char* BigInteger::div(BigInteger &dividend) {
	
	pair<char*, char*> result;
	int num1Len = strlen(this->number);
	int num2Len = strlen(dividend.number);
	
	char *finalResult = new char[max(num1Len, num2Len)];
	bool isNegSign = 0;

	BigInteger num1, num2;
	if(this->number[0] == '-' && dividend.number[0] == '-') {
		num1.setNumber(this->number+1);
		num2.setNumber(dividend.number+1);
		result = divOps(num1, num2);
	}
	else if(this->number[0] == '-' && dividend.number[0] != '-') {
		num1.setNumber(this->number+1);
		num2.setNumber(dividend.number);
		result = divOps(num1, num2);
		isNegSign = 1;
	}
	else if(this->number[0] != '-' && dividend.number[0] == '-') {
		num1.setNumber(this->number);
		num2.setNumber(dividend.number+1);
		result = divOps(num1, num2);
		isNegSign = 1;
	}
	else {
		result = divOps(*this, dividend);
	}

	if(isNegSign && strcmp(result.first, "0") != 0) {
		finalResult[0] = '-';
		strcpy(finalResult+1, result.first);
	} else {
		strcpy(finalResult, result.first);
	}
		
	return finalResult;
}

char* BigInteger::mod(BigInteger &dividend) {

	pair<char*, char*> result;
	int num1Len = strlen(this->number);
	int num2Len = strlen(dividend.number);
	
	char *finalResult = new char[max(num1Len, num2Len)];
	bool isNegSign = 0;
	
	BigInteger num1, num2;
	if(this->number[0] == '-' && dividend.number[0] == '-') {
		num1.setNumber(this->number+1);
		num2.setNumber(dividend.number+1);
		result = divOps(num1, num2);
		isNegSign = 1;
	}
	else if(this->number[0] == '-' && dividend.number[0] != '-') {
		num1.setNumber(this->number+1);
		num2.setNumber(dividend.number);
		result = divOps(num1, num2);
		isNegSign = 1;
	}
	else if(this->number[0] != '-' && dividend.number[0] == '-') {
		num1.setNumber(this->number);
		num2.setNumber(dividend.number+1);
		result = divOps(num1, num2);
		isNegSign = 1;
	}
	else {
		result = divOps(*this, dividend);
	}
	
	if(isNegSign && strcmp(result.second, "0") != 0) {
		finalResult[0] = '-';
		strcpy(finalResult+1, result.second);
	} else {
		strcpy(finalResult, result.second);
	}
	return finalResult;
}
