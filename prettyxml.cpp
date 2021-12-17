#include <iostream>
#include <string>
#include <queue>
using namespace std;
 
/*
*Function to repeat a string n times its used to repeat tabs
*time complexity = O(m)
*space complexity = O(1)
*/
string repeat(string s, int n) {
	string repeat;
	for (int i = 0; i < n; i++)
		repeat += s;

	return repeat;
}

/*
*Function to prettify the XML file by keeping the indentation for each level
*time complexity = O(n*m)=O(n)
*space complexity = O(n)
*/

void prettyxml(string* text)
{
	//creating new string s to hold the old string modified
	string x = "",s="";     //string x to substring the orginal string 
	string t("    ");
	string n("\n");
	queue <string> q;      //creating queue to hold the opening and closing tags and the data
	long i = 0, flag;      //flag for the number of characters in tags and data
	int flagt = 1;         //flag for the number of tabs  
	while (i != text->size())
	{
		flag = 0;          //intializing the flag
		if (text->at(i) == '<')
		{
			for (long x = i; text->at(x) != '>'; x++)
			{
				flag++;
			}
			flag++;
			x = text->substr(i, flag); 
			q.push(x);     //pushing opening and closing tag into the queue
			i = i + flag;
		}
		else
		{
			for (long x = i; text->at(x) != '<'; x++)
			{
				flag++;
			}
			x = text->substr(i, flag);
			q.push(x);    //pushing data into the queue
			i = i + flag;
		}

	}
	while (!q.empty())
	{
		x = q.front();
		if (x.at(0) == '<')
		{
			//closing tags
			if (x.at(1) == '/')
			{
				flagt-=2;
				s += repeat(t, flagt);
				s = s + x;
				s = s + n;
				/*s += repeat(t, flagt);
				flagt++;*/
				q.pop();
				if (!q.empty())
				{
					if (q.front().at(1) != '/')
					{
						s += repeat(t, flagt);
						flagt++;
					}
					else
					{
						flagt++;
					}
				}
			}
			//opening tag
			else
			{
				/*if (flagt != 1)
				{
					s += repeat(t, flagt);
					flagt++;
				}*/
				s = s + x;
				s = s + n;
				s += repeat(t, flagt);
				flagt++;
				q.pop();
			}
		}
		//data
		else
		{
			s = s + x;
			s = s + n;
			//s += repeat(t, flagt);
			//flagt--;
			q.pop();
		}
	}
	*text = s;
}
