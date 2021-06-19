#include <iostream>
#include <string>
#include <fstream>
#include "LList.h"
#include "Stack.h"
#include "Errors.h"
#include "IML.h"


// explaining the logic of this program:
//   <SRT-ORD "ASC">81 3<MAP-INC "1">4 12 55<AGG-AVG>4 8
//    </AGG-AVG></MAP-INC>22</SRT-ORD>

// ->string "<SRT-ORD "ASC">81 3<MAP-INC "1">4 12 55<AGG-AVG>4 8
//    </AGG-AVG></MAP-INC>22</SRT-ORD>"

// -> check if it is correct -> errors class   (this class does not work)

// -> if it is correct -> stack -> < SA 81 3 < + 1 4 12 55 < A 4 8 > > 22 >    // start poping and push elements in stack2

// 1. stack2 ->  > 22 > > 8 4 A > (stop) -> > 22 > 
// 1. list -> A 4 8    ->call operation for A (operation5)    -> 6  ->stack2 -> > 22 > 6

// 2. pop from stack1 (< SA 81 3 < + 1 4 12 55)  in stack2 -> (> 22 > 6 55 12 4 1 + >) 
// 2. list -> + 1 4 12 55 6  -> call operation for + (operation1)  -> 5 13 56 7  -> stack2 -> > 22 5 13 56 7

// 3. pop from stack1 (< SA 81 3) in stack2 -> (> 22 5 13 56 7 3 81 SA <)  
// 3. list -> SA 81 3 7 56 13 5 22 ->call operation for SA (operation9) -> 3 5 7 13 22 56 81 -> stack2 -> 81 56 22 13 7 5 3

// 4. stack1 is already empty! then writes stack2 (pop elements) into file -> 3 5 7 13 22 56 81



void readFromFile(const std::string& fileName, std::string& text)
{
	std::ifstream inFile(fileName, std::ios::in);

	if (inFile.is_open()) {
		std::getline(inFile, text);
		inFile.close();
	}
	else {
		std::cout << "Error! Unable to read from this file. \n";
	}
}

void writeToFile(const std::string& fileName, Stack<std::string>& stack) 
{
	//write stack into string
	std::string text = "";
	while (!stack.isEmpty()) {
		text += stack.getTop();
		stack.pop();
	}

	std::ofstream outFile(fileName, std::ios::out);

	if (outFile.is_open()) {
		outFile << text;
		outFile.close();
	}
	else {
		std::cout << "Error! Unable to write from this file. \n";
	}
}


int main(){

	/* test input strings:
		<SRT-ORD "ASC">81 3<MAP-INC "1">4 12 55<AGG-AVG>4 8</AGG-AVG></MAP-INC>22</SRT-ORD>
	*/

	/*std::string text = "";
	//std::string fileName = "newFile.txt";
	//std::string file = "C:/Users/zazaq/Desktop/firstFile_project.txt";
	readFromFile("C:/Users/zazaq/Desktop/firstFile_project.txt", text);
	//> 22 > > 8 4 A < 55 12 4 1 + < 3 81 SA <

	IML p;
	//p.interpretator(text);

	Stack<std::string> stack;
	Stack<std::string> helper;
	p.interpretator(text, stack, helper);
	//std::cout << text << std::endl << std::endl;
	//writeToFile("newFile", p.interpretator(text));

	std::cout << "main   " << stack.getTopSize();
	while (!stack.isEmpty()) {
		std::cout << stack.getTop() << " ";
		stack.pop();
	}*/

	/* DUPLICATES TESTS
	LList<int> list1;
	list1.push_back(68);
	list1.push_back(85);
	list1.push_back(92);
	list1.push_back(85);
	list1.push_back(68);
	list1.push_back(25);
	list1.push_back(85);
	

	list1.removeDuplicates();
	//list1.removeLast();
	//IML m;
	//m.removeD(list1);
	//m.operation7(list);
	//list.sortASC();
	size_t size = list1.getSize();
	for (size_t i = 0; i < size; i++)
	{
		std::cout << list1.getAt(i) << " ";
	}
	*/

	return 0;
}