
#include <iostream>
#include <fstream>
#include <string>
#include "IML.h"
#include "LList.h"
#include "Stack.h"
#include "Errors.h"

bool IML::isNumber(char s) const
{
	return s == '0' || s == '1' || s == '2' || s == '3' || s == '4' || s == '5' || s == '6' || s == '7' || s == '8' || s == '9';
}

bool IML::isAlpha(char s) 
{
	return s == 'A' || s == 'B' || s == 'C' || s == 'D' || s == 'E' || s == 'F' || s == 'G' ||
		s == 'H' || s == 'I' || s == 'J' || s == 'K' || s == 'L' || s == 'M' || s == 'N' ||
		s == 'O' || s == 'P' || s == 'Q' || s == 'R' || s == 'S' || s == 'T' || s == 'U' ||
		s == 'V' || s == 'W' || s == 'Z' || s == 'X' || s == 'Y';
}

bool IML::isSign(char s) const
{
	if (s == 47)
		return true;

	return false;
}

Stack<std::string>& IML::interpretator(std::string& text, Stack<std::string>& stack1, Stack<std::string>& helper)
{
	std::string temp = "";    // for the operation
	std::string s = "";        // helper string for numbers
	int countOperation = 7;

	size_t size = text.size();
	int j = 1;
	for (size_t i = 0; i < size; i++, j++)
	{
		if (text[i] == '<') 
		{
			if (isSign(text[j])) {
				stack1.push(">");
				while (text[i] != '>') {
					++i;
					j++;
				}
			}
			else if (isAlpha(text[j])) {
				stack1.push("<");
			}
		}
		else if (isAlpha(text[i]))
		{
			countOperation = 7;
			temp = "";
			while (countOperation) {
				temp += text[i];
				countOperation--;
				i++;
				j++;
			}

			if (temp == "MAP-INC")
			{
				i += 2;                            
				j += 2;
				stack1.push("+");

				s = "";
				if (text[i] == '-') {
					s += text[i];
					i++;
					j++;
				}
				while (isNumber(text[i])) {
					s += text[i];
					i++;
					j++;
				}
				stack1.push(s);
				i++;                              // for " and >
				j++;
			}
			else if (temp == "MAP-MLT") {
				i += 2;
				j += 2;
				stack1.push("*");

				s = "";
				if (text[i] == '-') {             // if (text[i] is '-' ->negative number)
					s += text[i];
					i++;
					j++;
				}
				while (isNumber(text[i]))
				{
					s += text[i];
					if (!isNumber(text[j]))
						break;
					i++;
					j++;
				}
				stack1.push(s);						// add number into stack1

				i += 1;
				j += 1;
			}
			else if (temp == "AGG-SUM")             // ++
			{
				stack1.push("++");                  // add ++ to the stack1
			}
			else if (temp == "AGG-PRO")             // **
			{
				stack1.push("**");                  // add ** to the stack1
			}
			else if (temp == "AGG-AVG")             // A
			{
				stack1.push("A");                   // add A to the stack1
			}
			else if (temp == "AGG-FST")             // F   first
			{
				stack1.push("F");                   // add ? to the stack
			}
			else if (temp == "AGG-LST")             // L   last
			{
				stack1.push("L");                   // add ? to the stack1
			}
			else if (temp == "SRT-REV")             // R-everse
			{
				stack1.push("R");                   // add R to the stack1
			}
			else if (temp == "SRT-ORD")             // SORTING    SA or SD
			{
				i += 2;                             // <free space> and "
				j += 2;
				s = "";
				while (isAlpha(text[i]))
				{
					s += text[i];
					i++;
					j++;
				}

				if (s == "ASC") {
					stack1.push("SA");
				}
				else if (s == "DSC") {
					stack1.push("SD");
				}
				i++;                              // for " and >
				j++;
			}
			else if (temp == "SRT-SLC")              // S
			{
				i += 2;                              // read the number..like first if statement and add to the stack1
				j += 2;
				stack1.push("S");

				s = "";
				if (text[i] == '-') {                // if (text[i] is '-' ->negative number)
					s += text[i];
					i++;
					j++;
				}
				while (isNumber(text[i]))
				{
					s += text[i];
					i++;
					j++;
				}
				stack1.push(s);                      // add number to the stack

				i++;
				j++;
			}
			else if (temp == "SRT-DST")              // D
			{
				stack1.push("D");                    // add  to the stack1
			}
		}

		else if (isNumber(text[i]))
		{
			s = "";
			while (isNumber(text[i]))
			{
				s += text[i];
				if (!isNumber(text[j]))
					break;

				i++;
				j++;
			}
			stack1.push(s);                           // add number to the stack1
		}

		else if (text[i] == ' ')
			continue;
	}

	iml(stack1, helper);
	std::cout << "stack: " << stack1.getTopSize() << "   ";
	while (!stack1.isEmpty()) {
		std::cout << stack1.getTop() << " ";
		stack1.pop();
	}
	return stack1;
}

void IML::iml(Stack<std::string>& s, Stack<std::string>& helper)
{
	LList<std::string> list;

	size_t sizeHelper = 0;
	size_t sizeList = 0;
	
	while (!s.isEmpty())
	{
		if (s.getTop() == "<")
		{
			s.pop();                            // pop < 

			while (helper.getTop() != ">")		// !helper.isEmpty()
			{
				list.push_back(helper.getTop());
				helper.pop();
			}
			helper.pop();						// for >

			sizeList = list.getSize();
			for (size_t i = 0; i < sizeList; i++)
			{
				std::cout << list.getAt(i) << " ";
			}
			std::cout << std::endl;

			list = transformList(list);           // call function that "translate" the list

			sizeList = list.getSize();
			for (size_t i = 0; i < sizeList; i++)
			{
				std::cout << list.getAt(i) << " ";
			}
			std::cout << std::endl;

			while (!list.isEmpty()) {
				helper.push(list.getAt(list.getSize()-1));
				list.removeAt(list.getSize() - 1);
			}
		}

		else {
			helper.push(s.getTop());
			s.pop();
		}
	}

	//return helper;
}

LList<std::string>& IML::transformList(LList<std::string>& list)   // transform list  
{
	if (list.getAt(0) == "+" || list.getAt(0) == "*") // call operation for + and *
	{
		operation1(list);    
	}
	else if (list.getAt(0) == "++" || list.getAt(0) == "**")
	{
		operation2(list);
	}
	else if (list.getAt(0) == "A")
	{
		operation3(list);
	}
	else if (list.getAt(0) == "F")
	{
		operation4(list);
	}
	else if (list.getAt(0) == "L")
	{
		operation5(list);
	}
	else if (list.getAt(0) == "R")
	{
		operation6(list);
	}
	else if (list.getAt(0) == "SA" || list.getAt(0) == "SD")
	{
		operation7(list);
	}
	else if (list.getAt(0) == "S")
	{
		operation8(list);
	}
	/*else if (list.getAt(0) == "D")
	{
		operation9(list);
	}*/

	return list;
}

void IML::operation1(LList<std::string>& list)
{
	std::string temp = list.getAt(0);             // MAP-INC -> + or *
	list.removeFirst();
	size_t num = atoi(list.getAt(0).c_str());     // string to double -> this is number which must be added to the other numbers
	list.removeFirst();

	size_t currentNumber = 0;    // double
	size_t size = list.getSize(); 
	for (size_t i = 0; i < size; i++)
	{
		if (temp == "+") {
			currentNumber = atoi(list.getAt(i).c_str());
			currentNumber += num;
			list.changeElementAt(i, std::to_string(currentNumber));
		}
		else if (temp == "*") {
			currentNumber = atoi(list.getAt(i).c_str());
			currentNumber *= num;
			list.changeElementAt(i, std::to_string(currentNumber));
		}
	}
}

void IML::operation2(LList<std::string>& list)
{
	std::string temp = list.getAt(0);
	list.removeFirst();

	size_t currentNumber = 0;
	size_t number = 0;
	size_t size = list.getSize();
	for (size_t i = 0; i < size; i++)
	{
		if (temp == "++") {
			currentNumber = atoi(list.getAt(i).c_str());
			number += currentNumber;
		}
		else if (temp == "**") {
			currentNumber = atoi(list.getAt(i).c_str());
			number *= currentNumber;
		}
	}

	while (!list.isEmpty()) {
		list.removeFirst();
	}
	list.push_back(std::to_string(number));
}

void IML::operation3(LList<std::string>& list)
{
	list.removeFirst();

	size_t currentNumber = 0;
	size_t sumNumber = 0;
	size_t size = list.getSize();
	for (size_t i = 0; i < size; i++)
	{
		currentNumber = atoi(list.getAt(i).c_str());
		sumNumber += currentNumber;
	}

	sumNumber /= size;

	while (!list.isEmpty()) {
		list.removeFirst();
	}
	list.push_back(std::to_string(sumNumber));
}

void IML::operation4(LList<std::string>& list)
{
	list.removeFirst();
	std::string temp = list.getAt(0);

	while(!list.isEmpty())
	{
		list.removeAt(list.getSize()-1);
	}
	list.push_back(temp);
}

void IML::operation5(LList<std::string>& list)
{
	list.removeFirst();

	while (!list.onlyOneData()) {
		list.removeFirst();
	}
}

void IML::operation6(LList<std::string>& list)
{
	list.removeFirst();
	list.reverse();
}

void IML::operation7(LList<std::string>& list)
{
	std::string temp = list.getAt(0);
	list.removeFirst();

	LList<int> lNum;
	int tempNum;
	size_t size = list.getSize();
	for (size_t i = 0; i < size; i++)
	{
		tempNum = atoi(list.getAt(i).c_str());     // cast temp to int
		lNum.push_back(tempNum);
	}

	if (temp == "SA") {
		lNum.sortASC();
	}
	else if (temp == "SD") {
		lNum.sortDSC();
	}

	while (!list.isEmpty()) {
		list.removeFirst();
	}

	for (size_t i = 0; i < size; i++)
	{
		temp = std::to_string(lNum.getAt(i));
		list.push_back(temp);
	}
}

void IML::operation8(LList<std::string>& list)
{
	list.removeFirst();
	size_t number = atoi(list.getAt(0).c_str());    
	list.removeFirst();

	list.slc(number);
}

/*void IML::operation9(LList<std::string>& list)
{
	list.removeFirst();
	list.removeDuplicates();
}*/