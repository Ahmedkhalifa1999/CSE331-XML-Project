
#include "Consistency.h"
using namespace std;
/*
 Description:
	 -> this functions loops over xml string by character and checks for
		opening and closing tags in terms of correctness and matching.

	 -> this function stores the opening tags and check them against closing tags.
	 -> if they match the content of stack is cleared and the function returns true.
	 -> if they don't match then the function returns false.
	 -> if a closing tag is missing, the stack is not empty and the function returns false.

	 time complexity = O(n)
	 space complexity = O(n)
	 where n is size of the string.

*/
bool detection(string& xml)
{
	stack<char> s1; //to store tags

	// strings to compare tag names
	string tag1;
	string tag2;


	int i = 0;
	int index = 0;
	while (xml[i] != '\0')
	{
		// loop over the file until you find <
		if (xml[i] == '<')
		{
			//error_location.push_back(i);
			s1.push(xml[i++]);
			// check if it's a closing tag
			if (xml[i] == '/')
			{
				index = i + 1;
				i++;
				//store closing tag name in 2nd string
				while (xml[i] != '>')
				{
					tag2.push_back(xml[i]);
					i++;
				}
				while (s1.top() != '>')
				{
					s1.pop();
				}
				s1.pop();

				//store opening tag name in 1st string and clear stack

				while (s1.top() != '<')
				{
					tag1.push_back(s1.top());
					s1.pop();
				}
				s1.pop();
				reverse(tag1.begin(), tag1.end());

				// compare opening and closing tag names
				if (tag1 != tag2)
				{
					errortag.push(tag1);
					cout << "missing closing tag for " << tag1 << endl;
					i = index - 3;

					// if mismatch delete closing tag name and replace with the correct name
					/*int j = 0;
					while (xml[j] != '>')
					{
						j++;
					}
					//tag1.append(">");
					xml.erase(index, j - 2);
					xml.insert(index, tag1);*/



				}
				else
				{

				}
				tag1.clear();
				tag2.clear();

			}

			else
			{
				// store the contents of the opening tag in stack
				while (xml[i] != '>')
				{
					s1.push(xml[i]);

					i++;
				}
				s1.push(xml[i]);

			}
		}
		i++;
	}

	// if stack is empty then the file is consistent
	if (errortag.empty())
	{
		return true;
	}
	else
		return false;
}

// General solution
string correction(string& xml)
{
	string closingtag = "</";
	while (!errortag.empty())
	{

		closingtag = closingtag + errortag.top();
		errortag.pop();

		closingtag.append(">");
		xml.append(closingtag);
		closingtag = "</";
	}

	return xml;
}
