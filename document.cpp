#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "document.h"
using namespace std;

Document:: Document()
{
	ID = 0;
	author = "";
}

void Document:: set_ID(int ID)
{
	this->ID = ID;
}

int Document:: get_ID()
{
	return ID;
}

void Document:: add_title_word(string word)
{
	title.push_back(word);
}

vector <string> Document:: get_title()
{
	return title;
}

void Document:: set_author(string author)
{
	this -> author = author;
}

string Document:: get_author()
{
	return author;
}

void Document:: add_abstract_word(string word)
{
	abstract.push_back(word);
}

vector <string> Document:: get_abstract()
{
	return abstract;
}

void Document:: set_unstemmed_word(vector <string> word)
{
	unstemmed_word = word;
}

vector <string> Document:: get_unstemmed_word()
{
	return unstemmed_word;
}

void Document:: set_stemmed_word(vector <string> word)
{
	stemmed_word = word;
}

vector <string> Document:: get_stemmed_word()
{
	return stemmed_word;
}

void Document:: set_unstemmed_word_count(int num)
{
	unstemmed_word_count = num;
}

int Document:: get_unstemmed_word_count()
{
	return unstemmed_word_count;
}

void Document:: add_tf(string word, int count)
{
	tf.push_back(pair <string, int> (word, count));
}

void Document:: add_idf(string word, double num)
{
	idf.push_back(pair <string, double> (word, num));
}

void Document:: add_tf_idf(string word, double num)
{	
	tf_idf.push_back(pair <string, double> (word, num));
}

vector <pair <string, int> > Document:: get_tf()
{
	return tf;
}

vector <pair <string, double> > Document:: get_idf()
{
	return idf;
}

vector <pair <string, double> > Document:: get_tf_idf()
{
	return tf_idf;
}