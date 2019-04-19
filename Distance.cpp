#include <iostream>
#include <cstring>
#include <locale>
#include <algorithm>
#include <fstream>
#include <map>
#include <cmath>
#include "DocDist.h"
#include <chrono>

using namespace std;
#define PI 3.14159265

string tolow (string &s)
{
	string lowStr; // string to keep lower-case chars
	lowStr = s;
	transform (s.begin(), s.end(), lowStr.begin(), ::tolower);
	return lowStr;
}

//this func returns a string with all none-alphanumeric chars deleted
string isPerm (string &a, const string &b)
{
	string outstr;
	// a - our string, b - where to search
	for (int i = 0; i < a.size(); i++)
	{
		for (int j = 0; j < b.size(); j++)
		{
			if (a[i] == b[j])
			{
				outstr.push_back(a[i]);
				break;
			}
		}	
	}
	return outstr;
}

map <string, int> count_words(map <string, int> m, string &in)
{
    //map <string, int> m;
    int i = 0;
    if (m.size() == 0) m.insert(pair<string, int>(in, 1)); // if the map is empty, automatically put new word there
    else {
        for (map<string, int>::iterator it = m.begin(); it != m.end(); it++)
	    {
		    if (in == it->first) // if the word is already in the list
            {
                m[in] = m[in] + 1; // then increment counter
                i++; // and flag as well
                break;
            }
            //else m.insert(pair<string, int>(in, 1));
	    }
        if (i == 0) m.insert(pair<string, int>(in, 1)); // if there is no such word in the list, put it there
        i = 0; // update the flag
    }
	return m;
}

int inner_product (map <string, int> m1, map <string, int> m2)
{
    int sum = 0;
    for (map<string, int>::iterator it1 = m1.begin(); it1 != m1.end(); it1++)
    {
        for (map<string, int>::iterator it2 = m2.begin(); it2 != m2.end(); it2++)
        {
            if (it1->first == it2->first) sum += it1->second*it2->second;
        }
    }
    return sum;
}

double vector_angle (map <string, int> m1, map <string, int> m2)
{
    int num = inner_product(m1,m2);
    double denom = sqrt(inner_product(m1, m1)*inner_product(m2, m2));
    return acos((double)num/denom);
}

int main ()
{
	ifstream inf ("my1.txt", std::ios::in);
    ifstream inf1 ("my.txt", std::ios::in);
	string af, bf;
    string af1, bf1;
	const string perm = "abcdefghijklmnopqrstuvwxyz0123456789";
    map <string, int> m, m1;
    int dot_pr  = 0;
    double vec_ang = 0;
    auto start = chrono::steady_clock::now();
	while (!inf.eof())
	{	
		inf >> af;
		af = tolow (af);
		bf = isPerm(af, perm);
        m = count_words(m, bf);
	}
    while (!inf1.eof())
	{
        inf1 >> af1;
        af1 = tolow (af1);
        bf1 = isPerm(af1, perm);
        m1 = count_words(m1, bf1);
	}
    dot_pr = inner_product (m, m1);
    vec_ang = vector_angle(m, m1);
    auto end = chrono::steady_clock::now();
	cout << "Result: " << endl;
    cout << "Inner product = " << dot_pr << endl;
    cout << "Vector angle = " << vec_ang << " radians" << endl;
    cout << "Vector angle = " << vec_ang*180/PI << " degrees" << endl;
    cout << "Elapsed time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
    // initial algorithm takes approximately 800-900 ms for the default texts
}
