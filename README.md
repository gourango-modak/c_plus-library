# Big Integer Library

A C++17 big-integer library and optimized.

## Why would I use it?

If you need to work with large integers that maybe overflow in build-in data type size and performance is important to you - then you may find this library very useful for your work.

## Details About this library

when we deal with large number which can't fit in build-In data type size, then this libray is useful because it is easy to use just like build-in data type. In this library, I use character arrays to store the number or String(taking input number as a string). Do all operation using character arrays. we know character array takes less memory than integer array. That's why I choose character array for memory efficency also I didn't use much other libraries. I used queue, cstring, iostream. String library is uses very less time in this library.


## This project contain two version of library


* First Library split into two parts, .h (header file) and .cpp (c++ file). In header file all function prototype is declared and all function defination is provided in .cpp file.

* Second is One Single BigInteger.cpp file. This file can be useful in programming contest when we need to work with large number. To use this file, we need to copy the whole BigInteger Class code from this file (Single File/BigIntegerSingle.cpp) and paste in our code.


## Operations

	1. Addition
	2. Subtraction
	3. Multiplication
	4. Division
	5. Increment
	6. Decrement
	7. Modulo


## Some examples

```

// No of way we can intialize variable and declare

// declaration
BigInteger num, num00, num11;

// intialize with integer value
BigInteger num1 = 123456;

// intialize with string value
BigInteger num2 = "123456";

// intialize with string value into BigInteger Object
string num3 = "1234";
BigInteger num5 = num4;

// intialize with character array value into BigInteger Object
char num6[] = "1234";
BigInteger num7 = num4;

// We can take an input also

cin >> num;
cin >> num00 >> num11;


// Addition

BigInteger add1 = num1.add(num2)
BigInteger add2 = num1+num2;
char *add3 = num1+num2;


// Subtraction

BigInteger sub1 = num1.sub(num2)
BigInteger sub2 = num1-num2;
char *sub3 = num1-num2;


// Multiplication

BigInteger mul1 = num1.mul(num2)
char *mul3 = num1.mul(num2);


// Division

BigInteger div1 = num1.div(num2)
BigInteger div2 = num1/num2;
char *div3 = num1/num2;


// Modulo

BigInteger mod1 = num1.mod(num2)
BigInteger mod2 = num1%num2;
char *mod3 = num1%num2;


// Increment && Decrement

BigInteger inc1 = num1++;
BigInteger inc1 = ++num1;
num1++;
++num1;

BigInteger inc1 = num1--;
BigInteger inc1 = --num1;
num1--;
--num1;



```