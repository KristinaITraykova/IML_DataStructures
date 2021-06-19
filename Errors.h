#pragma once

#include <string>

// all eventual errors 
const std::string missingTag = "Tag is missing!";
const std::string error1 = "< is missing!";
const std::string error2 = "> is missing!";
const std::string error3 = "Syntax error!";
const std::string error4 = "Invalid number!";
const std::string error5 = "Did not find close operation!";
const std::string error6 = "Not enough arguments!";
/*
class Errors
{
	std::string text;
	// size_t error;
	
	void copy(const Errors& other);
	void del();

public:
	Errors();
	Errors(const std::string& _text);
	Errors(const Errors&);
	Errors& operator=(const Errors&);
	~Errors();

	bool isNumber(char);
	void print();

	bool countBrackets();                  // < and >   works
	bool isDigit(std::string& str);                        // works (also for fractional and negative)
	bool checkOperations();

	bool checkMap(size_t& index);
	bool checkAgg(size_t& index);
	bool checkSrt(size_t& index);
	
	bool isCorrectOpenCloseOperation();   // checks if for every operation there is the same close operation
	void checkOperation1(size_t&, bool, bool);
	bool enoughArguments(size_t startIndex, size_t endIndex);               // checks if for every operation there are enough arguments(numbers)

	void checkAll();
};*/