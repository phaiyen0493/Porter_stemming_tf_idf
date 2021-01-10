#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Document
{
	private:
	int ID;
	int unstemmed_word_count;
	vector <string> title;
	string author;
	vector <string> abstract;
	vector <string> unstemmed_word;
	vector <string> stemmed_word;
	vector < pair <string, int> > tf;
	vector < pair <string, double> > idf;
	vector < pair <string, double> > tf_idf;

	public:
	Document();
	void set_ID(int ID);
	int get_ID();
	void add_title_word(string word);
	vector <string> get_title();
	void set_author(string author);
	string get_author();
	void add_abstract_word(string word);
	vector <string> get_abstract();
	void set_unstemmed_word(vector <string> word);
	vector <string> get_unstemmed_word();
	void set_unstemmed_word_count(int num);
	int get_unstemmed_word_count();
	void set_stemmed_word(vector <string> word);
	vector <string> get_stemmed_word();
	void add_tf(string word, int count);
	void add_idf(string word, double num);
	void add_tf_idf(string word, double num);
	vector <pair <string, int> > get_tf();
	vector <pair <string, double> > get_idf();
	vector <pair <string, double> > get_tf_idf();
};