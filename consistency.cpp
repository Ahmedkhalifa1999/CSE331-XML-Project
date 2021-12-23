
#include "consistency.h"

stack<int> position;
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
					if (s1.empty()) { break; }
				}

				if (!s1.empty()) {
					s1.pop();
				}


				//store opening tag name in 1st string and clear stack

				if (!s1.empty())
				{
					while (s1.top() != '<')
					{
						tag1.push_back(s1.top());
						s1.pop();
					}
					s1.pop();
					reverse(tag1.begin(), tag1.end());
				}

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
						position.push(index - 1);
						cout << "missing opening tag for -> " << tag2 << endl;
						errortag.push(tag2);
					}
					else
					{

						i = index - 3;
					}

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

					//if (!position.empty()) { position.pop(); }
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
	while (!s1.empty())
	{
		s1.pop();
		while (s1.top() != '<')
		{
			tag1.push_back(s1.top());
			s1.pop();
		}
		s1.pop();
		reverse(tag1.begin(), tag1.end());
		cout << "missing closing tag for -> " << tag1 << endl;
		tag1.insert(0, "/");
		errortag.push(tag1);
		tag1.clear();

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
	{
		return false;
	}
}

// General solution
string correction(string& xml)
{
	string tag = "";
	bool flag;
	while (!errortag.empty())
	{
        tag = errortag.top();
		if (tag[0] == '/')
		{
			tag = tag.substr(1, tag.size());
			flag = locate(tag, xml, '/');
		}
		else
		{
			flag = locate(tag, xml, 0);
		}
		if (flag)
		{
			errortag.pop();
		}
	}

	return xml;
}

bool locate(string tagname, string& xml, char type)
{
	static int tag_pos[11];
	int i = 0;
	static int addedsize = 0;

	if (tagname == "topic" || tagname == "body" || tagname == "id" || tagname == "name" || tagname == "follower")
	{
		if (type == '/')
		{
			i = xml.find(tagname + '>', tag_pos[8]);
			if (i == string::npos)
			{
				i = xml.find(tagname + '>', 0);
			}
			i = xml.find("<", i);
			if ((xml[i + 1] != '/') || (xml[i + 2] != tagname[0]))
			{
				xml.insert(i - 1, "</" + tagname + ">");
				addedsize += 3 + tagname.size();
				return true;
			}
			if (tagname == "topic" && xml[i + 7] == 's')
			{
				xml.insert(i - 1, "</" + tagname + ">");
				addedsize += 3 + tagname.size();
				return true;
			}

			while (xml[i++] != '>');
			tag_pos[8] = i + 1;
		}
		else
		{
			i = position.top();
			if (xml[i] != '<')
			{
				i = xml.find("</", i);
			}
			while (xml[i--] != '>');
			string opening = "<" + tagname + ">";
			xml.insert(i + 2, "<" + tagname + ">");
			addedsize += opening.size();
			position.pop();
			return true;
		}
	}
	else if (tagname == "topics" || tagname == "followers")
	{
		short no = 0;
		if (tagname == "topics")
			no = 7;
		else
			no = 10;

		if (type == '/')
		{
			i = xml.find(tagname + '>', tag_pos[7]);
			if (i == string::npos)
			{
				i = xml.find(tagname + '>', 0);
			}

			do {
				i += 2;
				i = xml.find("</", i);

				if (xml[i + no] == 's')
				{
					tag_pos[7] = i + no;
					return false;
				}
			} while (xml[i + 2] == tagname[0] || xml[i + 2] == 'i');
			xml.insert(i - 2, "</" + tagname + ">");
			addedsize += 3 + tagname.size();
			tag_pos[7] = i + tagname.size();
			return true;
		}
		else
		{
			i = position.top();
			if (xml[i] != '<')
			{
				i = xml.find("</", i);
			}
			//while (xml[i--] != '>');
			string opening = "<" + tagname + ">";
			xml.insert(i - 2, "<" + tagname + ">");
			addedsize += opening.size();
			position.pop();
			return true;
		}
	}
	else if (tagname == "user" || tagname == "post")
	{
		if (type == '/')
		{
			switch (tagname[0]) {

			case 'u':
				i = xml.find("</followers>", tag_pos[0]);
				i = xml.find("<", i + 1);
				if (xml[i + 2] != tagname[0] || xml[i + 6] == 's')
				{
					xml.insert(i, "</user>");
					tag_pos[0] = i;
					return true;
				}
				tag_pos[0] = i;
				break;
			case 'p':
				i = xml.find("<post>", tag_pos[1]);
				i = xml.find("post", i + 5);
				if (xml[i - 1] != '/')
				{
					xml.insert(i - 2, "</post>");
					tag_pos[1] = i;
					return true;
				}
				else if (xml[i + 4] == 's')
				{
					xml.insert(i - 2, "</post>");
					tag_pos[1] = i;
					return true;
				}
				tag_pos[1] = i;
				break;
			}
		}
		else
		{
			i = position.top() + addedsize;
			if (xml[i] != '<')
			{
				i = xml.find("</", i);
			}
			//while (xml[i--] != '>');
			string opening = "<" + tagname + ">";
			xml.insert(i - 1, "<" + tagname + ">");
			addedsize += opening.size();
			position.pop();
			return true;
		}
	}
	else if (tagname == "users")
	{
		if (type == '/')
		{
			xml.append("</users>");
			return true;
		}
		else
		{
			xml.insert(0, "<users>");
			addedsize += 7;
			position.pop();
			return true;
		}
	}
	else if (tagname == "posts")
	{
		if (type == '/')
		{
			i = xml.find("</post>", tag_pos[2]);
			i = xml.find("<", i + 2);
			if (xml[i + 1] != '/' && xml[i + 1] != 'p')
			{
				xml.insert(i - 1, "</posts>");
				tag_pos[2] = i;
				return true;

			}
			tag_pos[2] = i;
		}
		else
		{
			i = position.top();
			if (xml[i] != '<')
			{
				i = xml.find("</", i);
			}
			//while (xml[i--] != '>');
			string opening = "<" + tagname + ">";
			xml.insert(i - 1, "<" + tagname + ">");
			addedsize += opening.size();
			position.pop();
			return true;
		}
	}
	else
	{
		if (type == '/')
		{
			i = xml.find(tagname + ">", tag_pos[3]);
			i = i + tagname.size() + 1;
			xml.insert(i, "</" + tagname + ">");
			tag_pos[3] = i;
			return true;
		}
		else
		{
			i = position.top();
			if (xml[i] != '<')
			{
				i = xml.find("</", i);
			}
			//while (xml[i--] != '>');
			string opening = "<" + tagname + ">";
			xml.insert(i - 1, "<" + tagname + ">");
			addedsize += opening.size();
			position.pop();
			return true;
		}


	}

	return false;

}
