#include <string>
#include <iostream>

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
    for (long x = 0; x < text->size(); x++)
    {
        if ((*text)[x] == '\t')    //checking tabs
        {
            continue;              //skip the tabs
        }
        else {
            newtxt=newtxt+(*text)[x];
        }
    }
    *text = newtxt;                //modifying the old string with new one
}

/*
* Function to delete the new lines from the string
* time complexity = O(n)
* space complexity = O(2n) = O(n)
*/

void removeline(string* text)
{
    string newtxn = "";            //creating new string to hold the old string without lines
    for (long j = 0; j < text->size(); j++)
    {
        if ((*text)[j] == '\n')    //checking lines
        {
            continue;              //skip the lines
        }
        else {
            newtxn = newtxn + (*text)[j];
        }
    }
    //adding spaces at the end of the string to make the loop in prettifying work
    newtxn.insert((newtxn.end()), ' ');
    newtxn.insert((newtxn.end()), ' ');
    *text = newtxn;               //modifying the old string with new one
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

//Function to prettify the XML file by keeping the indentation for each level

void prettifying(string* text)    //call by reference
{
    removetab(text);              //calling removetab function to remove tabs
    removeline(text);             //calling removeline function to remove lines
    int flagt = 1;                //flag for the number of tabs
    long l = text->size()-2;
    string t("  ");
    string n("\n");
    string s = "";                //creating new string to hold the old string modified
    for (long i = 0; i < l; i++)  //looping on the string
    {
        remove_space(*text, i);   //calling removetab function to remove spaces
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
        else if (text->at(i) == ',')     //start new line after , in the data for better shape
        {
            s = s + text->at(i);
            s += n;
            s += repeat(t, flagt);
        }
        else
        {
            s = s + text->at(i);
        }
    }
    *text = s;                          //modifying the old string with new one
}

