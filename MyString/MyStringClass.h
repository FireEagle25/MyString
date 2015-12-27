#pragma once

#include <list>
#include <iterator>
#include <iostream>

using namespace std;

class MyString {
private:
	list<char*> fullStr;
	unsigned int blockSize;
	void Add(const char* inputStr);
public:
	MyString(char* inputString, unsigned int blockSize);
	MyString(const MyString & obj);
	~MyString();
	void Print();
	unsigned int Size();
	MyString SubStr(unsigned int startPos, unsigned int cCount);
	int Search(MyString inpStr);
	MyString operator+(const MyString & right);
	MyString operator=(const MyString & right);
	friend int Compare(MyString str1, MyString str2);
};