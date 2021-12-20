
#include "consistency.h"

stack<string> errortag;

using namespace std;

bool detection(string& xml)
{
	stack<char> s1; //to store tags
	stack<string> buffer;

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
					buffer.push(tag1);
					if (s1.empty())
					{

						while (!buffer.empty())
						{
							int j;
							string copy = buffer.top();
							s1.push('<');
							for (j = 0; j < copy.size(); j++)
							{
								s1.push(copy[j]);
							}
							s1.push('>');
							buffer.pop();
						}
						cout << "missing opening tag for -> " << tag2 << endl;
						errortag.push(tag2);
					}
					else
					{
						i = index - 3;
					}


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

	while (!buffer.empty())
	{
		cout << "missing closing tag for -> " << buffer.top() << endl;
		string temp = "/";
		temp.append(buffer.top());
		errortag.push(temp);
		buffer.pop();
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
