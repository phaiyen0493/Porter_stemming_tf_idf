#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include "document.h"
using namespace std;

class Documents
{
	private:
	int document_count;
	int stopword_count; //total number of stopwords in input stopwords file
	vector <Document> document_collection;
	vector < pair <string, double> > tf_idf_query;
	vector < pair <int, double> > cosine_similarity;

	public:
	Documents();
	void set_document_count(int count);
	int get_document_count();
	void set_stopword_count(int count);
	int get_stopword_count();
	void Load_file(string file_name);
	void Store_file();
	vector <Document> get_document_vector();
	void Add_document(Document document);
	void eliminate_stop_word(string file_name); //count and remove stop word in the 1st document
	void calculate_tf_idf_document();
	void calculate_tf_idf_query(vector <string> query_word);
	void calculate_cosine_sim();
	void sort_cosine_similarity();
};