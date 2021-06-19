#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Errors.h"
/*
void Errors::copy(const Errors& other)
{
	size_t size = other.text.size();
	for (size_t i = 0; i < size; i++)
	{
		text[i] = other.text[i];
	}
}
void Errors::del()
{
	text.erase();
}

Errors::Errors() : text("")
{}

Errors::Errors(const std::string& _text)
{
	text = _text;
}

Errors::Errors(const Errors& other)
{
	copy(other);
}

Errors& Errors::operator=(const Errors& other)
{
	if (this != &other) {
		del();
		copy(other);
	}
	return *this;
}

Errors::~Errors()
{
	del();
}

bool Errors::isNumber(char s)
{
	return s == '0' || s == '1' || s == '2' || s == '3' || s == '4' || s == '5' || s == '6' || s == '7' || s == '8' || s == '9';
}


void Errors::print() {
	std::cout << text;
}

bool Errors::countBrackets()
{
	size_t count1 = 0;    // for <
	size_t count2 = 0;    // for >

	size_t size = text.size();
	for (size_t i = 0; i < size; i++)
	{
		if (text[i] == '<')
			count1++;

		else if (text[i] == '>')
			count2++;
	}
	if (count1 != count2)
		return false;      // std::cout << error1 << error2;
	else
		return true;
}

bool Errors::isDigit(std::string& str)
{
	size_t size = str.size();
	if (isNumber(str[0])) {
		for (size_t i = 0; i < size; i++)
		{
			if (isNumber(str[i]))
				continue;
			else if (str[i] == '.' && i < (size - 1)) {
				i++;
				if (isNumber(str[i]))
					continue;
				else return false;
			}
			else return false;
		}
	}
	else if (str[0] == '-' && isNumber(str[1])) {
		for (size_t i = 1; i < size; i++)
		{
			if (isNumber(str[i]))
				continue;
			else if (str[i] == '.' && i < (size - 1)) {
				i++;
				if (isNumber(str[i]))
					continue;
				else return false;
			}
			else return false;
		}
	}
	else return false;

	return true;
}

bool Errors::checkOperations()
{
	std::string number = "";

	size_t size = text.size();
	for (size_t i = 0; i < size; i++)
	{
		if (text[0] != '<' || text[size-1] != '>')
			return false; 

		if (text[i] == '<' && (isalpha(text[i++]) || text[i++] == '\\')) {
			i++;
			if (text[i] == 'M') {
				checkMap(i);
				if (checkMap(i) == false) {
					return false;
				}
				while(text[i] != '>')
					i++;
			}
			else if (text[i] == 'A') {
				checkAgg(i);
				if (checkAgg(i) == false) {
					return false;
				}
				while (text[i] != '>')
					i++;
			}
			else if (text[i] == 'S') {
				checkSrt(i);
				if (checkSrt(i) == false){
					return false;
				}
				while (text[i] != '>')
					i++;
			}
			else if (text[i] == '\\') {
				i++;

				std::string operation = "";
				size_t count = 7;

				while (count > 0) {
					operation += text[i];
					i++;
					count--;
				}

				if (operation == "MAP-INC" || operation == "MAP-MLT" || operation == "AGG-SUM" ||
					operation == "AGG-PRO" || operation == "AGG-AVG" || operation == "AGG-FST" ||
					operation == "AGG-LST" || operation == "SRT-REV" || operation == "SRT-DST" ||
					operation == "SRT-ORD" || operation == "SRT-SLC") {
					if (text[i] != '>') {
						return false;
					}
				}
				else return false;
			}
			else return false;
		}

		else if (isNumber(text[i]) || (text[i] == '-' && isNumber(text[i++]))) {
			while (text[i] != ' ' || text[i] == '<') {
				number += text[i];
				i++;
			}

			if (!isDigit(number))
				return false;
		}

		else return false;
	}
}

bool Errors::checkMap(size_t& index)
{
	std::string mapOperation = "";
	size_t count = 7;

	while (count > 0) {
		mapOperation += text[index];
		index++;
		count--;
	}

	std::string helperNumber = "";
	if (mapOperation == "MAP-INC" || mapOperation == "MAP-MLT")
	{
		if (text[index] == ' ') {
			index++;

			if (text[index] == '"') {
				index++;

				while (text[index] != '"') {
					helperNumber += text[index];
					index++;
				}

				if (!isDigit(helperNumber)) 
					return false;
				
				if (text[index] != '>')
					return false;
			}
			else return false;
		}
		else return false;
	}
}

bool Errors::checkAgg(size_t& index)
{
	std::string aggOperation = "";
	size_t count = 7;

	while (count > 0) {
		aggOperation += text[index];
		index++;
		count--;
	}
	if (aggOperation == "AGG-SUM" || aggOperation == "AGG-PRO" || aggOperation == "AGG-AVG" ||
		aggOperation == "AGG-FST" || aggOperation == "AGG-LST") 
	{
		if (text[index] == '>') {
			return true;
		}
		else return false;    // syntax error
	}
	else return false;        // syntax error
}

bool Errors::checkSrt(size_t& index)
{
	std::string srtOperation = "";
	size_t count = 7;

	while (count > 0) {
		srtOperation += text[index];
		index++;
		count--;
	}

	std::string helperNumber = "";
	if (srtOperation == "SRT-REV" || srtOperation == "SRT-DST") {
		if (!text[index] != '>')
			return false;
	}
	else if (srtOperation == "SRT-ORD") {
		if (text[index] == ' ') {
			index++;
			if (text[index] == '"') {
				index++;
				if (text[index] == 'A' || text[index] == 'D') {
					std::string ad = "";
					size_t count = 3;

					while (count > 0) {
						ad += text[index];
						index++;
						count--;
					}

					if (ad == "ASC" || ad == "DSC") {
						if (text[index] == '"') {
							index++;
							if (text[index] != '>')
								return false;
						}
						else return false;
					}
					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else if (srtOperation == "SRT-SLC") {
		if (text[index] == ' ') {
			index++;
			if (text[index] == '"') {
				index++;

				while (text[index] != '"') {
					helperNumber += text[index];
					index++;
				}

				if (!isDigit(helperNumber))
					return false;

				if (text[index] != '>')
					return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;    // syntax error
}

bool Errors::isCorrectOpenCloseOperation()
{
	bool flag = false;
	bool enoughArg = false;
	size_t size = text.size();
	for (size_t i = 0; i < size; i++)
	{
		if (text[i] == '<') {
			i++;
			if (isalpha(text[i])) {
				checkOperation1(i, flag, enoughArg);
				if (flag == false && enoughArg == false) {
					std::cout << error5 << "\n" << error6;
					return false;
				}
				else if (flag == false) 
				{
					std::cout << error5;
					return false;         // did not find close operation
				}
				else if (enoughArg == false) {
					std::cout << error6;
					return false;
				}
			}
		}
	}
	return true;
}

void Errors::checkOperation1(size_t& index, bool flag, bool enoughArg)
{
	std::string operation = "";
	std::string operation2 = "";
	size_t count = 7;
	size_t saveIndex = 0;

	size_t size = text.size();
	for (size_t i = index; i < size; i++)
	{
		operation = "";
		count = 7;

		while (count > 0) {
			operation += text[i];
			i++;
			count--;
		}

		for (size_t j = i; j < size; j++)
		{
			if (text[j] == '<') {
				saveIndex = j;
				j++;
				if (text[j] == '\\') {
					j++;
					operation2 = "";
					count = 7;

					while (count > 0) {
						operation2 += text[j];
						j++;
						count--;
					}

					if (operation == operation2) {
						flag = true;
						enoughArg = enoughArguments(index, j);
						text.erase(saveIndex, 10);          // remove/ edit close operation  -> </MAP-INC> ->10 characters
						return;
					}
				}
			}
		}
		return;
	}
}

bool Errors::enoughArguments(size_t startIndex, size_t endIndex)
{
	std::string number = "";
	for (size_t i = startIndex; i < endIndex; i++)
	{
		if (text[i] == '<') {
			while (text[i] != '>')
				i++;
		}

		if (isNumber(text[i]) || (text[i] == '-' && isNumber(text[i++]))) {
			while (text[i] != ' ' || text[i] == '<') {
				number += text[i];
				i++;
			}

			if (isDigit(number)) {
				return true;     // it is enought to find 1 number
			}
		}
	}
	return false;
}

void Errors::checkAll()
{

}*/