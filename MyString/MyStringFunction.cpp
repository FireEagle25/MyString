#include "MyStringClass.h"

#pragma once

int* incArrSize(int* inpArr, int & size) {
	int* res = new int[size + 1];
	for(int i = 0; i < size; i++)
		res[i] = inpArr[i];
	size++;
	return res;
}

void MyString::Add(const char* inputString) {
	list<char *>::iterator lastIt = fullStr.end();
	int i = 0;
	if (fullStr.size() > 0) {	
		lastIt--;
		char* last = fullStr.size() > 0 ? *lastIt : "";
		for(;strlen(last) < blockSize && strlen(inputString) > i; i++)
			last[strlen(last)] = inputString[i];
	}
	for (int j = i; j < strlen(inputString); j += blockSize) {
		char *substr = (char*)malloc(blockSize + 1); 
		strncpy(substr, inputString + j, blockSize);
		substr[blockSize] = '\0';
		fullStr.push_back(substr);
	}
}

MyString::MyString(char* inputString, unsigned int inpBlockSize) {

	if(inpBlockSize == 0)
		cout << "Incorrect size..." << endl;
	else {
		blockSize = inpBlockSize;

		for (int i = 0; i < strlen(inputString); i += blockSize) {
			char *substr = (char*)malloc(blockSize + 1); 
			strncpy(substr, inputString + i, blockSize);
			substr[blockSize] = '\0';
			fullStr.push_back(substr);
		}
	}

}

MyString::MyString(const MyString & obj) {
	fullStr = obj.fullStr;
	blockSize = obj.blockSize;
}

MyString::~MyString() {
	fullStr.clear();
}

void MyString::Print() {
	cout << "Print..." << endl;
	copy(fullStr.begin(), fullStr.end(), ostream_iterator<char *>(cout,"|"));
	cout << endl;
	return;
}

unsigned int MyString::Size() {
	if (fullStr.size() == 0)
		return 0;
	unsigned int result = (fullStr.size() - 1) * blockSize;
	list<char *>::iterator lastIt = fullStr.end();
	lastIt--;
	char* last = *lastIt;
	result += strlen(last);
	return result;
}

MyString MyString::operator+(const MyString & right) {
	MyString rightCopy(right);

	//—транный кусман, но в этот раз работает. „то-то странное происходило при конструкторе копировани€ от this
	MyString result("", blockSize);

	for (list<char *>::iterator it = this->fullStr.begin(); it != this->fullStr.end(); it++)
		result.Add(*it);

	for (list<char *>::iterator it = rightCopy.fullStr.begin(); it != rightCopy.fullStr.end(); it++)
		result.Add(*it);

	return result;
}

MyString MyString::operator=(const MyString & right) {
	this->fullStr.clear();
	MyString rightCopy(right);
	for (list<char *>::iterator it = rightCopy.fullStr.begin(); it != rightCopy.fullStr.end(); it++)
		this->Add(*it);
	return *this;
}

int Compare(MyString str1, MyString str2) {
	int result = 0;
	for (list<char *>::iterator it = str1.fullStr.begin(); it != str1.fullStr.end(); it++)
		result += strlen(*it);
	for (list<char *>::iterator it = str2.fullStr.begin(); it != str2.fullStr.end(); it++)
		result -= strlen(*it);

	if (result > 0) return 1;
	if (result < 0) return -1;

	for (list<char *>::iterator it = str1.fullStr.begin(); it != str1.fullStr.end(); it++) {
		char * part = *it;
		for (int i = 0; part[i] != '\0'; i++) {
			result += (int) part[i];
		}
	}

	for (list<char *>::iterator it = str2.fullStr.begin(); it != str2.fullStr.end(); it++) {
		char * part = *it;
		for (int i = 0; part[i] != '\0'; i++) {
			result -= (int) part[i];
		}
	}

	if (result > 0) return 1;
	if (result < 0) return -1;
	return 0;
}

MyString MyString::SubStr(unsigned int startPos, unsigned int cCount) {
	MyString result("", blockSize);

	int block = 0;
	list<char *>::iterator it = fullStr.begin();

	for (block = 0; (block + 1) * blockSize <= startPos && it != fullStr.end(); block++, it++);

	while( cCount > 0 && it != fullStr.end()) {
		char* buf = *it;
		unsigned int currSize = (blockSize -(startPos % blockSize)) > cCount ? cCount : (blockSize -(startPos % blockSize));
		char *substr = (char*)malloc(currSize + 1);
		memcpy(substr, &buf[startPos % blockSize], currSize);
		substr[currSize] = '\0';
		result.Add(substr);
		startPos += strlen(substr);
		cCount -= strlen(substr);
		it++;
	}
	return result;
}

int MyString::Search(MyString inpStr) {
	if (!inpStr.Size() == 0 && !Size() == 0) {
		int currSize = Size() - inpStr.Size() + 1;
		for (int i = 0; i < currSize; i++)
			if (Compare(SubStr(i, inpStr.Size()), inpStr) == 0)
				return i;
	}
	return -1;
}