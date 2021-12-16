#include <iostream>
#include <string>

using namespace std;

/*
*Function to repeat a string n times its used to repeat tabs
*time complexity = O(n)
*space complexity = O(n)
*/
string repeat(string s, int n) {
    string repeat;
    for (int i = 0; i < n; i++)
        repeat += s;

    return repeat;
}

/*
* Function to delete the tabs from the string
* time complexity = O(n)
* space complexity = O(2n) = O(n)
*/
void removetab(string* text)
{
    string newtxt = "";            //creating new string to hold the old string without tabs
    long i = 0, flag = 0;
    while (i != text->size())
    {
        if (text->at(i) == '<')
        {
            for (long x = i; (text->at(x) != '>' && x < (text->size() - 1)); x++)
            {

                if ((*text)[x] == '\t' || (*text)[x] == ' '|| (*text)[x] == '\n')    //checking tabs
                {
                    continue;              //skip the tabs
                }
                else {
                    newtxt = newtxt + (*text)[x];
                }
                i = x;
            }

            newtxt = newtxt + ">";
            i++;
        }
        else
        {
            for (long x = i; (text->at(x) != '<' && x < (text->size() - 1)); x++)
            {
                //newtxt = newtxt + (*text)[x];
                flag = x;
            }
            flag++;
            if ((text->at(flag) == '<') && ((text->at(flag + 1) == '/')|| (text->at(flag + 2) == '/')))
            {
                for (long x = i; x < flag; x++)
                {
                    newtxt = newtxt + (*text)[x];

                }
                i = flag;
            }
            else
            {
                for (long x = i; x < flag; x++)
                {
                    if ((*text)[x] == '\t' || (*text)[x] == ' ' || (*text)[x] == '\n')    //checking tabs
                    {
                        continue;              //skip the tabs
                    }
                    else {
                        newtxt = newtxt + (*text)[x];
                    }

                }
                i = flag;
            }
            i--;
        }
       i++;
        /*if (i == 0)
        {
            newtxt = newtxt + "<";
        }*/
        /*newtxt = newtxt + "<";*/
        //for (long x = i; (text->at(x) != '<' && x < (text->size() - 1)); x++)
        //{
        //    if ((*text)[x] == '\t' || (*text)[x] == ' ')    //checking tabs
        //    {
        //        continue;              //skip the tabs
        //    }
        //    else {
        //        newtxt = newtxt + (*text)[x];
        //    }
        //    i = x;
        //}
        //newtxt = newtxt + "<";
        //i++;
        //for (long y=i;( text->at(y) != '<' && text->at(y+1) != '/' && y+1<text->size()-1); y++)
        //{
        //    newtxt = newtxt + (*text)[y];
        //    i++;

        //}

    }
    //adding spaces at the end of the string to make the loop in prettifying work
    newtxt.insert((newtxt.end()), ' ');
    newtxt.insert((newtxt.end()), ' ');
    *text = newtxt;                //modifying the old string with new one
}

/*
* Function to delete the spaces between the start and the end of the tags
* time complexity = O(n)
* space complexity = O(n)
*/

void remove_space(string& line, long& i)
{
    for (; i < line.size(); i++)
    {
        if (line[i] != ' ')
            return;                //return without spaces
    }
}

void prettifying(string* text)
{
    removetab(text);
    int flagt = 1;                //flag for the number of tabs                 
    long l = text->size()-2;
    string t("  ");
    string n("\n");
    string s = "";
	for (long i = 0; i < l; i++)
	{
 //       if (text->at(i) == '<')
 //       {
 //           if(i==0)
 //           {
 //               s = s + text->at(i);
 //           }
 //           else if (text->at(i+1) == '/'|| (text->at(i + 1) == ' '&& text->at(i + 2) == '/'))
 //           {
 //               /*s += n;
 //               s += repeat(t, flagt - 1);*/
 //               s = s + text->at(i);
 //               flagt--;
 //           }
 //           else
 //           {
 //               s += n;                                      //adding new line
 //               s += repeat(t, flagt);                       //adding tab
 //               s = s + text->at(i);
 //               flagt++;
 //           }
 //       }
 //       else
 //       {
 //           s = s + text->at(i);
 //       }

	//}
 //   *text = s;
        if (text->at(i) == '>' && text->at(i + 2) != '/')     //tag closing
        {
            s = s + text->at(i);
            if (text->at(i + 1) == '<')                      //tag opening
            {
                s += n;                                      //adding new line
                s += repeat(t, flagt);                       //adding tab
                flagt++;
            }
            else                                             //data
            {
                s += n;
                s += repeat(t, flagt);
            }
        }

        else if (text->at(i) == ' ' && text->at(i + 1) == '<')  //removing spaces before opening tag
        {
            continue;
        }
        /*else if (text->at(i) == '>' && text->at(i + 1) == '<' && text->at(i + 2) == '/')
        {
            s = s + text->at(i);
            s += n;
            s += repeat(t, flagt-1);

        }*/

        //closing tags 

        else if ((text->at(i) == '<' && text->at(i + 1) == '/') || (text->at(i) == '<' && text->at(i + 1) == ' ' && text->at(i + 2) == '/') || (text->at(i) == '/' && text->at(i + 1) == '>') || (text->at(i) == '?' && text->at(i + 1) == '>'))
        {


            s += n;
            s += repeat(t, flagt - 1);
            s = s + text->at(i);
            flagt--;

        }
        //else if (text->at(i) == ',')     //start new line after , in the data for better shape
        //{
        //    s = s + text->at(i);
        //    s += n;
        //    s += repeat(t, flagt);
        //}
        else
        {
            s = s + text->at(i);
        }
    }
    *text = s;                          //modifying the old string with new one
}
//void main()
//{
//    string x("<users>\n<user>\t<id>1</id>  <name>A   hm   ed A  li</name><posts><post><body>Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.</body><topics><topic>economy</topic><topic>finance</topic></topics></post><post>");
//    prettifying(&x);
//    cout << x << endl;
//}