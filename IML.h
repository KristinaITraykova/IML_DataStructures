#pragma once

#include <string>
#include "LList.h"
#include "Stack.h"

class IML {
public:

	Stack<std::string>& interpretator(std::string& text, Stack<std::string>& st, Stack<std::string>& ); // string turns to stack   works!!
	void iml(Stack<std::string>& s, Stack<std::string>& st);
	LList<std::string>& transformList(LList<std::string>& list);

	bool isNumber(char s) const;
	bool isAlpha(char s) ;
	bool isSign(char s) const;
	//bool isDigit(std::string&) const;
	
	void operation1(LList<std::string>& list);    // operations 1 and 2 - +, *    ->works
	void operation2(LList<std::string>& list);    // operation 3 and 4  - ++, **  ->works
	void operation3(LList<std::string>& list);    // operation 5 - A              ->works
	void operation4(LList<std::string>& list);    // operation 6 - F              ->works
	void operation5(LList<std::string>& list);    // operation 7 - last           ->works
	void operation6(LList<std::string>& list);    // operation reverse            ->works
	void operation7(LList<std::string>& list);    // sorting                      ->works
	void operation8(LList<std::string>& list);    // from the proper index        ->works
	//void operation9(LList<std::string>& list);    // remove duplicates

};
