// MyString.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "MyStringClass.h"

MyString Replace(MyString sourse, MyString fText, MyString rText) {
	if ( Compare(fText, MyString("", 2)) == 0) {
		cout << "Error. Searching the empty string" << endl;
		return sourse;
	}

	int place = sourse.Search(fText);
	MyString res = sourse;
	if (place != -1) {
		MyString end = res.SubStr(place + fText.Size(), res.Size() - place - fText.Size());
		res = res.SubStr(0, place == 0 ? 0 : place) + rText + Replace(end, fText, rText);;
	}
	return res;
}

int _tmain(int argc, _TCHAR* argv[])
{
	MyString a("aa", 10);
	MyString aa("bbaabbaabbaabbaa", 3);
	a.Print();
	
	(a + aa).Print();
	//a = a + a;
	a.Print();
	a = Replace(aa, a, MyString("c", 5));
	a.Print();
	Replace(a, MyString("aaaaaa", 5), MyString("1", 5)).Print();
	a.Print();

	MyString lol("Paxa ololo", 5);
	MyString peka("Pxaa olloo", 5);

	cout << "STUPID TEST!11 " << Compare(lol, peka);

	system("pause");
	return 0;
}