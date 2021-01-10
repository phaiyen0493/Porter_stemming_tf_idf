#include <iostream>
#include <string>
#include <stdio.h>
#include "documents.h"
using namespace std;

int main()
{
	string input_doc_name;
	string stopwords_filename;

	Documents file;

	cout << "Please enter the name of the collection file: ";
	getline (cin, input_doc_name, '\n');
	file.Load_file(input_doc_name);

	cout << "Please enter the name of the stopwords file: ";
	getline (cin, stopwords_filename, '\n');
	file.eliminate_stop_word(stopwords_filename); //take out stop words in the file

	file.Store_file();
		
	return 0;
}