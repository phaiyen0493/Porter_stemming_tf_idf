#include <iostream>
#include <string>
#include "stemming.h"

using namespace std;

int get_m(string word)
{
	int m = 0;
	for (int i=0; i < (word.length()-1) ; i++)
	{
		if (vowel_check(word[i], i) && !vowel_check(word[i+1], i+1))
		{
			m++;
		}
	}
	return m;
}

bool vowel_in_stem(string word)
{
	if (word.length()<=1) 
	{
		return false;
	}
	for (int i=0; i< (word.length()-1); i++)
	{
		if (vowel_check(word[i], i))
		{
			return true;
		}
	}
	return false;
}

bool vowel_check(char c, int i)
{
	if ((c== 'y' || c == 'Y') && i >0)
	{
		return true;
	}

	if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' || c=='A' || c=='E' || c=='I' || c=='O' || c=='U')
	{
		return true;
	}
	return false;
}

string step1A(string word)
{
	int l = word.length();
        if (l>4 && word.substr(l-4,4)== "sses")
	{
		word.erase(l-2, 2);
		l-=2;
	}
        
        else if (l>3 && word.substr(l-3,3)== "ies")
	{
		word.erase(l-2, 2);
		l-=2;
	}

        else if (l>3 && word[l-1]=='s' && word[l-2]!='s')
	{
		word.erase(l-1,1);
		l--;
	}
        return word;
}

string step1B(string word)
{
        bool check = false;
	int l = word.length();
        if (l>=5 && get_m(word.substr(0,(l-3))) >0 && word.substr(l-3,3)== "eed")
	{
		word.erase(l-1,1);
		l--;
	}

        else if(l>=3 && vowel_in_stem(word.substr(0,(l-2))) && word.substr(l-2,2)== "ed"  )
	{
		word.erase(l-2, 2);
		l-=2;
		check = true;
	}  

	else if (l>=4  && vowel_in_stem(word.substr(0,(l-3))) && word.substr(l-3,3)== "ing")
	{
		word.erase(l-3, 3);
		l-=3;
		check = true;
	}

        if (check == true)
	{
                if (word.substr(l-2,2)== "at") 
		{
                        word += 'e';
			l++;
		}

                else if (word.substr(l-2,2)== "bl")
		{
			word += 'e';
			l++;
		}

                else if (word.substr(l-2,2)== "iz")
		{
			word += 'e';
			l++;
		}

                else if (!vowel_check(word[l-1], l-1) && (word[l-1]==word[l-2]) && word[l-1]!='l' && word[l-1]!='s' && word[l-1]!='z')
		{
			word.erase(l-1,1); 
			l--;
		}

                else if ( l>=3 && get_m(word)== 1 && !vowel_check(word[l-1], l-1) && vowel_check(word[l-2], l-2) && !vowel_check(word[l-3], l-3))
		{      
			if (word[l-1]!='w' && word[l-1]!='x' && word[l-1]!='y')
			{
				word += 'e';
				l++;
			}
		}
	}
        return word;
}

string step1C(string word)
{
	int l = word.length();
        if (word[l-1]=='y' && vowel_in_stem(word.substr(0,(l-1))))
	{
                word.erase(l-1,1);
                word += 'i';
	}
        return word;
}

string step2(string word)
{
	int l = word.length();
        if (l>=9 && get_m(word.substr(0,l-7))>0 && word.substr(l-7,7)=="ational")
	{
		word.erase(l-5,5);
		word += 'e';
		l-=4;
	}

	else if (l>=8 && get_m(word.substr(0,l-6))>0 && word.substr(l-6,6)=="tional")
	{
                word.erase(l-2,2);
		l-=2;                
	}
	
	else if (l>=6 && get_m(word.substr(0,l-4))>0 && word.substr(l-4,4)=="enci")
	{
		word.erase(l-1,1);
		word += 'e';
	}

	else if (l>=6 && get_m(word.substr(0,l-4))>0 && word.substr(l-4,4)=="anci")
        {
                word.erase(l-1,1);
                word += 'e';
        }

	else if (l>=6 && get_m(word.substr(0,l-4))>0 && word.substr(l-4,4)=="izer")
        {
                word.erase(l-1,1);
		l--;
        }

	else if (l>=6 && get_m(word.substr(0,l-4))>0 && word.substr(l-4,4)=="abli")
        {
                word.erase(l-1,1);
                word += 'e';
        }

	else if (l>=6 && get_m(word.substr(0,l-4))>0 && word.substr(l-4,4)=="alli")
	{
		word.erase(l-2,2);
		l-=2; 
	}

	else if (l>=7 && get_m(word.substr(0,l-5))>0 && word.substr(l-5,5)=="entli")
        {
                word.erase(l-2,2);
		l-=2;
        }

	else if (l>=5 && get_m(word.substr(0,l-3))>0 && word.substr(l-3,3)=="eli")
        {
                word.erase(l-2,2);
		l-=2; 
        }

	else if (l>=7 && get_m(word.substr(0,l-5))>0 && word.substr(l-5,5)=="ousli")
        {
                word.erase(l-2,2);
		l-=2;
        }
	
	else if (l>=9 && get_m(word.substr(0,l-7))>0 && word.substr(l-7,7)=="ization")
	{
		word.erase(l-5,5);
                word += 'e';
		l-=4;
	}

	else if (l>=7 && get_m(word.substr(0,l-5))>0 && word.substr(l-5,5)=="ation")
        {
		word.erase(l-3,3);
                word += 'e';
		l-=2;
        }

	else if (l>=6 && get_m(word.substr(0,l-4))>0 && word.substr(l-4,4)=="ator")
        {
                word.erase(l-2,2);
               	word += 'e';
		l--;
        }
        
	else if (l>=7 && get_m(word.substr(0,l-5))>0 && word.substr(l-5,5)=="alism")
	{
		word.erase(l-3,3);
		l-=3;
	}
	
	else if (l>=9 && get_m(word.substr(0,l-7))>0 && word.substr(l-7,7)=="iveness")
        {
                word.erase(l-4,4);
		l-=4;
        }

	else if (l>=9 && get_m(word.substr(0,l-7))>0 && word.substr(l-7,7)=="fulness")
        {
                word.erase(l-4,4);
		l-=4;
        }

	else if (l>=9 && get_m(word.substr(0,l-7))>0 && word.substr(l-7,7)=="ousness")
        {
                word.erase(l-4,4);
		l-=4;
        }

	else if (l>=7 && get_m(word.substr(0,l-5))>0 && word.substr(l-5,5)=="aliti")
        {
                word.erase(l-3,3);
		l-=3;
        }

	else if (l>=7 && get_m(word.substr(0,l-5))>0 && word.substr(l-5,5)=="iviti")
        {
                word.erase(l-3,3);
                word += 'e';
		l-=2;
        }

	else if (l>=8 && get_m(word.substr(0,l-6))>0 && word.substr(l-6,6)=="biliti")
	{
                word.erase(l-5,5);
                word += 'e';
		l-=3;
	}	
	return word;
}


string step3(string word)
{
	int l = word.length();
        if (l>=7 && get_m(word.substr(0,l-5))>0 && word.substr(l-5,5)== "icate")
	{
		word.erase(l-3,3);
		l-=3;
	}

        else if (l>=7 && get_m(word.substr(0,l-5))>0 && word.substr(l-5,5)== "ative")
        {
		word.erase(l-5,5);
		l-=5;
	}

	else if (l>=7 && get_m(word.substr(0,l-5))>0 && word.substr(l-5,5)== "alize")
        {
                word.erase(l-3,3);
		l-=3;
        }

	else if (l>=7 && get_m(word.substr(0,l-5))>0 && word.substr(l-5,5)== "iciti")
        {
                word.erase(l-3,3);
		l-=3;
        }

	else if (l>=6 && get_m(word.substr(0,l-4))>0 && word.substr(l-4,4)== "ical")
        {
                word.erase(l-2,2);
		l-=2;
        }

	else if (l>=5 && get_m(word.substr(0,l-3))>0 && word.substr(l-3,3)=="ful")
        {
                word.erase(l-3,3);
		l-=3;
        }

	else if (l>=6 && get_m(word.substr(0,l-4))>0 && word.substr(l-4,4)== "ness")
        {
                word.erase(l-4,4);
		l-=4;
        }
	return word; 
}

string step4(string word)
{
	int l = word.length();
	if (l>=4 && get_m(word.substr(0,l-2))> 1 && word.substr(l-2,2)=="al")
	{
                word.erase(l-2,2);
		l-=2;
	}

	else if(l>=6 && get_m(word.substr(0,l-4))> 1 && word.substr(l-4,4)=="ance")
	{
                word.erase(l-4,4);
		l-=4;
	}

	else if(l>=6 && get_m(word.substr(0,l-4))> 1 && word.substr(l-4,4)=="ence")
        {
                word.erase(l-4,4);
		l-=4;
        }

	else if(l>=4 && get_m(word.substr(0,l-2))> 1 && word.substr(l-2,2)=="er")
        {
                word.erase(l-2,2);
		l-=2;
        }

	else if(l>=4 && get_m(word.substr(0,l-2))> 1 && word.substr(l-2,2)=="ic")
        {
                word.erase(l-2,2);
		l-=2;
        }

	else if(l>=6 && get_m(word.substr(0,l-4))> 1 && word.substr(l-4,4)=="able")
        {
                word.erase(l-4,4);
		l-=4;
        }

	else if(l>=6 && get_m(word.substr(0,l-4))> 1 && word.substr(l-4,4)=="ible")
        {
                word.erase(l-4,4);
		l-=4;
        }

	else if(l>=5 && get_m(word.substr(0,l-3))> 1 && word.substr(l-3,3)=="ant")
        {
                word.erase(l-3,3);
		l-=3;
        }
	
	else if(l>=7 && get_m(word.substr(0,l-5))> 1 && word.substr(l-5,5)=="ement")
        {
                word.erase(l-5,5);
		l-=5;
        }

	else if(l>=6 && get_m(word.substr(0,l-4))> 1 && word.substr(l-4,4)=="ment")
        {
                word.erase(l-4,4);
		l-=4;
        }

	else if(l>=5 && get_m(word.substr(0,l-3))> 1 && word.substr(l-3,3)=="ent")
        {
                word.erase(l-3,3);
		l-=3;
        }

	else if(l>=6 && get_m(word.substr(0,l-3))> 1 &&(word[l-4]=='s'||word[l-4]=='t')&& word.substr(l-3,3)=="ion")
        {
                word.erase(l-3,3);
		l-=3;
        }

	else if(l>=4 && get_m(word.substr(0,l-2))>1 && word.substr(l-2,2)=="ou")
        {
                word.erase(l-2,2);
		l-=2;
        }
	
	else if(l>=5 && get_m(word.substr(0,l-3))>1 && word.substr(l-3,3)=="ism")
        {
                word.erase(l-3,3);
		l-=3;
        }

	else if(l>=5 && get_m(word.substr(0,l-3))>1 && word.substr(l-3,3)=="ate")
        {
                word.erase(l-3,3);
		l-=3;
        }

	else if(l>=5 && get_m(word.substr(0,l-3))>1 && word.substr(l-3,3)=="iti")
        {
                word.erase(l-3,3);
		l-=3;
        }

	else if(l>=5 && get_m(word.substr(0,l-3))>1 && word.substr(l-3,3)=="ous")
        {
                word.erase(l-3,3);
		l-=3;
        }

	else if(l>=5 && get_m(word.substr(0,l-3))>1 && word.substr(l-3,3)=="ive")
        {
                word.erase(l-3,3);
		l-=3;
        }

	else if(l>=5 && get_m(word.substr(0,l-3))>1 && word.substr(l-3,3)=="ize")
        {
                word.erase(l-3,3);
		l-=3;
        }
        return word;
}

string step5A(string word)
{
	int l = word.length();
        if (word[l-1]=='e' && get_m(word.substr(0,l-1))>1 )
	{
                word.erase(l-1,1);
		l--;
 	}

        else if (l>=3 && word[l-1]=='e' && get_m(word.substr(0,l-1))==1 && (vowel_check(word[0], 0) || !(!vowel_check(word[l-2], l-2) && vowel_check(word[l-3], l-3) && !vowel_check(word[l-4], l-4))))
        {
		word.erase(l-1,1);
		l--;
        }
        return word;
}

string step5B(string word)
{
	int l = word.length();
	if (get_m(word.substr(0,l-1))>1 && word[l-1]=='l' && word[l-2]=='l')
	{
		word.erase(l-1,1);
	}		
        return word;
}

string stem(string word)
{
	word = step1A(word);
	word = step1B(word);
	word = step1C(word);
	word = step2(word);
	word = step3(word);
	word = step4(word);
	word = step5A(word);
	word = step5B(word);

        return word;
}
