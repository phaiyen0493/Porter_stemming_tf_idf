#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <map>
#include <utility>
#include <chrono>
#include <cmath> 
#include <iomanip> 
#include <sstream>

#include "stemming.h"
#include "documents.h"

using namespace std;

Documents:: Documents()
{
	document_count = 0;
	stopword_count = 0;
}

void Documents:: set_document_count(int count)
{
	document_count = count;
}

int Documents:: get_document_count()
{
	return document_count;
}

void Documents:: Add_document(Document document)
{
	document_collection.push_back(document);
}

void Documents:: Load_file(string file_name)
{
	string word;
	int ID;
	string title_word = "";
	string author;
	string abstract_word = "";
	Documents file;
	ifstream fin;
	
	fin.open(file_name);
	if(fin.fail())
	{
		cout << "Cannot open the file" << endl;
		exit(EXIT_FAILURE);
	}

	fin >> word;

	while (!fin.eof())
	{
		Document document;
		if (word.compare(".I") == 0)
		{
			fin >> ID;
			document.set_ID(ID);
		}

		fin >> word;
		if (word.compare(".T") == 0)
		{
			while (word.compare(".A") != 0)
			{
				fin >> word;

				if (word.compare(".A") != 0)
				{
					title_word = word;
					document.add_title_word(title_word);
				}
			}
			fin.ignore();
		}

		if (word.compare(".A") == 0)
		{
			getline(fin, author, '\n');
			document.set_author(author);
		}

		fin >> word;

		if (word.compare(".W") == 0)
		{
			for (int i = 0; i < document.get_title().size(); i++)
			{
				fin >> word;
			}
				
			while (word.compare(".I") != 0)
			{
				if (fin.eof())
				{
					break;
				}
				fin >> word;
				if (word.compare(".I") != 0)
				{
					abstract_word = word;
					document.add_abstract_word(abstract_word);
				}
			}
		}
		document_collection.push_back(document);
		document_count++;
	}
} 

vector <Document> Documents:: get_document_vector()
{
	return document_collection;
}

void Documents:: eliminate_stop_word(string file_name)
{
	string stop_word;
	bool check; 
	vector <string> word;
	vector <string> stopword_list;
	ifstream fin;
	fin.open(file_name);

	if(fin.fail())
	{
		cout << "Cannot open the file" << endl;
		exit(EXIT_FAILURE);
	}

	while(getline(fin, stop_word, '\n'))
	{
		stopword_list.push_back(stop_word);
		stopword_count++;
	}

	//remove 's and white space
	for (int j = 0; j < document_collection.size(); j++)
	{
		word = document_collection[j].get_abstract();
		
		do
		{
			check = false;
			for (int i = 0; i < word.size(); i++)
			{
				if (word[i].size() == 1 && ispunct(word[i][0]))
				{
					word.erase(word.begin() + i);
					check = true;
				}

				else if (word[i] == "\'s")
				{
					word.erase(word.begin() + i);
					check = true;
				}

				else
				{
					for (int k = 0; k < word[i].size(); k++)
					{
						if ((ispunct(word[i][k]) && word[i][k] != '-') || isdigit(word[i][k]) || isspace(word[i][k]))
						{
							word[i].erase(word[i].begin() + k);
							check = true;
						}
					}
				}
			}
		} while (check == true);
		document_collection[j].set_unstemmed_word (word);
	}

	//remove empty string(s)
	for (int j = 0; j < document_collection.size(); j++)
	{
		word = document_collection[j].get_unstemmed_word ();
		do
		{
			check = false;
			for (int i = 0; i < word.size(); i++)
			{
				if (word[i] == "")
				{
					word.erase(word.begin() + i);
					check = true;
				}
			}
		}while (check == true);
		document_collection[j].set_unstemmed_word (word);
	}

	//remove stop words
	for (int j = 0; j < document_collection.size(); j++)
	{
		word = document_collection[j].get_unstemmed_word ();
		do
		{
			check = false;
			for (int i = 0; i < word.size(); i++)
			{
				for (int n = 0; n < stopword_list.size(); n++)
				{
					if (word[i].compare(stopword_list[n]) == 0)
					{
						word.erase(word.begin() + i);
						check = true;
					}
				}
			}
		} while (check == true);
		document_collection[j].set_unstemmed_word(word);
	}
}

void Documents:: set_stopword_count(int count)
{
	stopword_count = count;
}

int Documents:: get_stopword_count()
{
	return stopword_count;
}

vector <string> remove_duplicate(vector <string> word)
{
	sort (word.begin(), word.end());
	word.erase(unique(word.begin(), word.end()), word.end());
	return word;
}

bool ascending (string a, string b)
{
	return (a < b);
}

bool descending (pair <int, double> &a, pair <int, double> &b)
{
	return (a.second > b.second);
}

void Documents:: sort_cosine_similarity()
{
	sort(cosine_similarity.begin(), cosine_similarity.end(), descending);
}

void Documents:: Store_file()
{
	vector <string> title = document_collection[0].get_title();
	vector <string> abstract = document_collection[0].get_abstract();
	vector <string> unstemmed_word = document_collection[0].get_unstemmed_word();
	vector <string> query_word;
	string word;
	string query_stream;

	cout << "ID: " << document_collection[0].get_ID() << " Title:";

	for (int i = 0; i < title.size(); i++)
	{
		cout << " " << title[i];
	}
	cout << endl;
	cout << "Author: " << document_collection[0].get_author() << endl;

	for (int i = 0; i < abstract.size(); i++)
	{
		cout << " " << abstract[i];
	}
	cout << endl << endl;

	cout << "There are currently " << stopword_count << " known stopwords." << endl << endl;

	for (int i = 0; i < unstemmed_word.size(); i++)
	{
		cout << unstemmed_word[i] << " ";
	}
	cout << endl;

	cout << "Number of unique unstemmed words: " << remove_duplicate(unstemmed_word).size() << endl << endl;

	for (int j = 0; j < document_collection.size(); j++)
	{
		vector <string> stemmed_word;
		unstemmed_word = document_collection[j].get_unstemmed_word();
		for (int i = 0; i < unstemmed_word.size(); i++)
		{
			stemmed_word.push_back(stem(unstemmed_word[i]));
		}
		document_collection[j].set_stemmed_word(stemmed_word);
	}

	for (int i = 0; i < document_collection[0].get_stemmed_word().size(); i++)
	{
		cout << document_collection[0].get_stemmed_word()[i] << " ";
	}

	cout << "\nNumber of unique stemmed words: " << remove_duplicate(document_collection[0].get_stemmed_word()).size() << endl << endl;	

	calculate_tf_idf_document();

	for (int i = 0; i < remove_duplicate(document_collection[0].get_stemmed_word()).size(); i++)
	{
		cout << "Word: " << setw(20) << right << document_collection[0].get_tf()[i].first << "\tTF: " << document_collection[0].get_tf()[i].second << "\tIDF: " << fixed << setprecision(5) << document_collection[0].get_idf()[i].second << "\tTF_IDF: " << document_collection[0].get_tf_idf()[i].second << endl;
	}

	cout << "\nPlease enter a query to find related documents: ";
	getline (cin, query_stream, '\n');
	istringstream is(query_stream);

	while (is >> word)
	{
		query_word.push_back(word);
	}
	calculate_tf_idf_query(query_word);

	cout << "\nThe top most similar documents are:" << endl;
	calculate_cosine_sim();

	cout << "Complete!" << endl;
}

void Documents:: calculate_tf_idf_document()
{
	vector <string> unique_stemmed_word;
	vector <string> unique_stemmed_word1;
	int count;
	double idf;
	double tf_idf;
	double num; //garbage num

	//get tf
	for (int i = 0; i < document_collection.size(); i++)
	{
		unique_stemmed_word = remove_duplicate(document_collection[i].get_stemmed_word());
		sort(unique_stemmed_word.begin(), unique_stemmed_word.end(), ascending);
		
		for (int j = 0; j < unique_stemmed_word.size(); j++)
		{
			count = 0;
			for (int k = 0; k < document_collection[i].get_stemmed_word().size(); k++)
			{
				if (unique_stemmed_word[j].compare(document_collection[i].get_stemmed_word()[k]) == 0)
				{	
					count++;
				}
			}
			document_collection[i].add_tf(unique_stemmed_word[j], count);
		}
	}

	//get idf
	for (int i = 0; i < document_collection.size(); i++)
	{
		unique_stemmed_word = remove_duplicate(document_collection[i].get_stemmed_word());
		sort(unique_stemmed_word.begin(), unique_stemmed_word.end(), ascending);
		
		for (int j = 0; j < unique_stemmed_word.size(); j++)
		{
			count = 0;
			for (int k = 0; k < document_collection.size(); k++)
			{
				unique_stemmed_word1 = remove_duplicate(document_collection[k].get_stemmed_word());
				for (int n = 0; n < unique_stemmed_word1.size(); n++)
				{
					if (unique_stemmed_word[j].compare(unique_stemmed_word1[n]) == 0)
					{
						count++;
					}
				}
			}
			num = ((double) (document_count)) / ((double) (count));
			idf = log(num);
			document_collection[i].add_idf(unique_stemmed_word[j], idf);
		}
	}

	//get tf_idf
	for (int i = 0; i < document_collection.size(); i++)
	{
		unique_stemmed_word = remove_duplicate(document_collection[i].get_stemmed_word());
		sort(unique_stemmed_word.begin(), unique_stemmed_word.end(), ascending);
		
		for (int j = 0; j < unique_stemmed_word.size(); j++)
		{
			if (unique_stemmed_word[j].compare(document_collection[i].get_tf()[j].first) == 0 && unique_stemmed_word[j].compare(document_collection[i].get_idf()[j].first) == 0)
			{
				tf_idf = (double) document_collection[i].get_tf()[j].second * document_collection[i].get_idf()[j].second;
			}
			document_collection[i].add_tf_idf(unique_stemmed_word[j], tf_idf);
		}
	}

}

void Documents:: calculate_tf_idf_query(vector <string> query_word)
{
	int count;
	double tf_idf;

	vector <string> stemmed_query_word;
	for (int i = 0; i < query_word.size(); i++)
	{
		stemmed_query_word.push_back(stem(query_word[i]));
	}

	vector <string> unique_query_word = remove_duplicate(stemmed_query_word);
	vector < pair <string, double> > idf;

	for (int i = 0; i < unique_query_word.size(); i++)
	{
		count = 0;
		for (int k = 0; k < stemmed_query_word.size(); k++)
		{
			if (unique_query_word[i].compare(stemmed_query_word[k]) == 0)
			{
				count++;
			}
		}
		
		for (int j = 0; j < document_collection.size(); j++)
		{
			idf = document_collection[j].get_idf();
			for (int n = 0; n < idf.size(); n++)
			{
				if (unique_query_word[i].compare(idf[n].first) == 0)
				{
					tf_idf = ((double) count) * idf[n].second;
					break;
				}
			}
		}
		tf_idf_query.push_back(pair <string, double> (unique_query_word[i], tf_idf));
	}
}

void Documents:: calculate_cosine_sim()
{
	double dot_product, sum_of_docs, sum_of_query, cosine_sim;
	int doc_ID;

	for (int i = 0; i < document_collection.size(); i++)
        {
		dot_product = 0;
		sum_of_query = 0;
                for (int j = 0; j < tf_idf_query.size(); j++)
                {
			sum_of_docs = 0;
			for (int k = 0; k < document_collection[i].get_tf_idf().size(); k++)
                        {
				if ((tf_idf_query[j].first).compare(document_collection[i].get_tf_idf()[k].first) == 0)
				{
					dot_product += (double) (tf_idf_query[j].second) * (double) (document_collection[i].get_tf_idf()[k].second);
				}
				sum_of_docs += (double) (pow(document_collection[i].get_tf_idf()[k].second, 2.0));
			}
			sum_of_query += (double) (pow(tf_idf_query[j].second, 2.0));
		}
		doc_ID = document_collection[i].get_ID();
		cosine_sim = (double) (dot_product)/ ((double) (sqrt(sum_of_query)) * (double) (sqrt(sum_of_docs)));
		cosine_similarity.push_back(pair <int, double> (doc_ID, cosine_sim));
	}

	sort_cosine_similarity();

	for (int i = 0; i < 5; i++)
	{
		cout << "\t" << cosine_similarity[i].first << "\t" << cosine_similarity[i].second << endl;
	}
}


