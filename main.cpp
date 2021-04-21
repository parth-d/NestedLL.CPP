#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "LList.h"

//Local Variables
vector<string> new_ids;
map<string, int> ints;
map<string, LList*> LLs;

//Function Declarations
vector<string> openfile(const string& addr);
vector<string> exec_line(const string& line);
int combine(string s1, string s2);
int copy(string s1, string s2);
int head(string s1, string s2);
int assign(string s1, string s2);
int chs(string s1);
int add_ints(string s1, string s2);
int if_case(string s1);
LList* create(const string& id);

//Driver
int main(){
    map<string, int> command_int{{"NEWID", 1}, {"COMBINE", 2}, {"COPY", 3}, {"HEAD", 4}, {"TAIL", 5}, {"ASSIGN", 6}, {"CHS", 7}, {"ADD", 8}, {"IF", 9}, {"HLT", 10}};
    string addr = R"(C:\Users\parth\Desktop\Current Work\474_SPLI\mytry2\code.txt)";
    vector<string> lines = openfile(addr);
    if (lines.empty()){
        cout << "File either empty or not opened properly.";
        return 1;
    }
//    ints["x"] =5;
//    ints["y"] = 4;
//    LLs["x"] = new LList(1);
//    LLs["x"]->clear();
//    LLs["x"]->append(2);
//    LLs["x"]->append(3);
//    LLs["x"]->append(LLs["x"]);
//    new_ids.push_back("y");
    short i = 0;
    while (i != lines.size())
    {
        int ret;
        vector<string> words = exec_line(lines.at(i));
        switch (command_int[words.back()]) {
            case 1:
                new_ids.push_back(words[0]);
//                cout << "Created newid: " << words[0] << endl;
                break;
            case 2:
                //combine case
                ret = combine(words[0], words[1]);
                if (ret != 0)
                {
                    cout << "There were some problems in the combine operation at line " << i+1 << endl;
                    return 1;
                }
                break;
            case 3:
                //copy case
                ret = copy(words[0], words[1]);
                if (ret != 0)
                {
                    cout << "There were some problems in the copy operation at line " << i+1 << endl;
                    return 1;
                }
                break;
            case 4:
                //head case
                ret = head(words[0], words[1]);
                if (ret != 0)
                {
                    cout << "There were some problems in the head operation at line " << i+1 << endl;
                    return 1;
                }
                break;
            case 5:
                //tail case
                ret = copy(words[0], words[1]);
                if (ret == 0)
                {
//                    cout << "Copy successful" << endl;
                    LLs[words[1]]->head = LLs[words[1]]->head->next;
                    LLs[words[1]]->size--;
                } else
                {
                    cout << "There were some problems in the tail operation at line " << i+1 << endl;
                    return 1;
                }
                break;
            case 6:
                // assign case
                ret = assign(words[0], words[1]);
                if (ret != 0)
                {
                    cout << "There were some problems in the assign operation at line " << i+1 << endl;
                    return 1;
                }
                break;
            case 7:
                //change sign case
                ret = chs(words[0]);
                if (ret != 0)
                {
                    cout << "There were some problems in the change sign operation at line " << i+1 << endl;
                    return 1;
                }
                break;
            case 8:
                //add case
                ret = add_ints(words[0], words[1]);
                if (ret != 0)
                {
                    cout << "There were some problems in the add operation at line " << i+1 << endl;
                    return 1;
                }
                break;
            case 9:
                //if case
                ret = if_case(words[0]);
                if (ret == 0)
                {
                    i = stoi(words[1]);
                    continue;
                }
                else
                    break;
            case 10:
                //halt case
                cout << "Halting at line " << i+1 << endl;
                i = lines.size() - 1;
                break;
            default:
                cout << "Invalid command in file at line " << i + 1 << ". Terminating." << endl;
                return 1;
        }
        i++;
    }
    cout << "Program execution completed." << endl;
    cout << "Program counter: " << i << endl;
    cout << "Linked Lists: " << endl;
    map<string, LList*>::iterator itr;
    for (itr = LLs.begin(); itr != LLs.end(); ++itr)
    {
        cout << itr->first << ": ";
        itr->second->print();
        cout << endl;
    }
    cout << "Ints: " << endl;
    map<string, int>::iterator itr2;
    for (itr2 = ints.begin(); itr2 != ints.end(); ++itr2)
    {
        cout << itr2->first << ": ";
        cout << itr2->second;
        cout << endl;
    }
    return 0;
}


//Function Definitions:


vector<string> openfile(const string& addr){
    string line;
    vector<string> lines;
    ifstream file(addr);
    if (file.is_open()){
        while (getline(file, line)){
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}

vector<string> exec_line(const string& line){
    string word;
    vector<string> words;
    stringstream iss(line);
    while (iss >> word){
        words.push_back(word);
    }
    return words;
}

int combine(string s1, string s2)
{
    // S2 not LList, but declared in new_ids
    if ((LLs.find(s2) == LLs.end()) && (find(new_ids.begin(), new_ids.end(), s2) != new_ids.end() ))
    {
        new_ids.erase(find(new_ids.begin(), new_ids.end(), s2));
        create(s2);
        // S1 is int
        if (ints.find(s1) != ints.end())
            LLs[s2]->prepend(ints[s1]);
            // S1 is LL
        else if (LLs.find(s1) != LLs.end())
            LLs[s2]->prepend(LLs[s1]);
//        LLs[s2]->combine(*LLs[s1]);
        else
        {
            cout << "The ID " << s1 << " is neither an int nor a LL. Please check." << endl;
            return 1;
        }
    }
    // S2 exists as a LList.
    else if (LLs.find(s2) != LLs.end())
    {
        // S1 is int
        if (ints.find(s1) != ints.end())
            LLs[s2]->prepend(ints[s1]);
            // S1 is LL
        else if (LLs.find(s1) != LLs.end())
            LLs[s2]->prepend(LLs[s1]);
//        LLs[s2]->combine(*LLs[s1]);
        else
        {
            cout << "The ID " << s1 << " is neither an int nor a LL. Please check." << endl;
            return 1;
        }
    }
    //S2 non existant.
    else
    {
        cout << "Create " << s2 << " as a new_id first." << endl;
        return 1;
    }
    return 0;
}

int copy(string s1, string s2)
{
    if ((LLs.find(s2) == LLs.end()) && (find(new_ids.begin(), new_ids.end(), s2) != new_ids.end() ))
    {
        new_ids.erase(find(new_ids.begin(), new_ids.end(), s2));
        create(s2);
        // S1 is LL
        if (LLs.find(s1) != LLs.end())
        {
            LLs[s2]->copy_from(LLs[s1]);
        }
        else
        {
            cout << "The ID " << s1 << " is not declared properly as a LL. Please check." << endl;
            return 1;
        }
    }
    else if (LLs.find(s2) != LLs.end())
    {
        // S1 is LL
        if (LLs.find(s1) != LLs.end())
        {
            LLs[s2]->clear();
            LLs[s2]->copy_from(LLs[s1]);
        }
        else
        {
            cout << "The ID " << s1 << " is not declared properly as a LL. Please check." << endl;
            return 1;
        }
    }
    else
    {
        cout << "Create " << s2 << " as a new_id first." << endl;
        return 1;
    }
    return 0;
}

int head(string s1, string s2)
{
    //s1 not an LList
    if (LLs.find(s1) == LLs.end())
    {
        cout << "Identifier 1 not declared properly" << endl;
        return 1;
    }
    else
    {
        //s1's head, a LList
        if (LLs[s1]->head->holds_ll)
        {
            // S2 not LList, but declared in new_ids
            if ((LLs.find(s2) == LLs.end()) && (find(new_ids.begin(), new_ids.end(), s2) != new_ids.end() ))
            {
                new_ids.erase(find(new_ids.begin(), new_ids.end(), s2));
                create(s2);
                LLs[s2]->append(LLs[s1]->head->data.ll);
            }
            else if (LLs.find(s2) != LLs.end())
            {
                LLs[s2]->clear();
                LLs[s2]->append(LLs[s1]->head->data.ll);
            }
        }
        else
        {
            if ((ints.find(s2) == ints.end()) && (find(new_ids.begin(), new_ids.end(), s2) != new_ids.end() ))
            {
                new_ids.erase(find(new_ids.begin(), new_ids.end(), s2));
                ints[s2] = LLs[s1]->head->data.value;
            }
            else if (ints.find(s2) != ints.end())
            {
                ints[s2] = LLs[s1]->head->data.value;
            }
            else
            {
                cout << "s2 not properly declared" << endl;
                return 1;
            }
        }
    }
    return 0;
}

LList* create(const string& id){
    LLs[id] = new LList();
    return LLs[id];
}

int assign(string s1, string s2)
{
    //s2 is not a valid integer
//    if (!(all_of(s2.begin(), s2.end(), ::isdigit)))
//    {
//        cout << "Invalid integer entered" << endl;
//        return 1;
//    }
//    else
    {
        //s1 is a new_id
        if (find(new_ids.begin(), new_ids.end(), s1) != new_ids.end())
        {
            new_ids.erase(find(new_ids.begin(), new_ids.end(), s1));
            ints[s1] = stoi(s2);
        }
        //s1 is an int
        else if (ints.find(s1) != ints.end())
            ints[s1] = stoi(s2);
        else
        {
            cout << "Identifier " << s1 << " is neither new_id nor an int" << endl;
            return 1;
        }
    }
    return 0;
}

int chs(string s1)
{
    //s1 is a new_id
    if (find(new_ids.begin(), new_ids.end(), s1) != new_ids.end())
    {
        cout << "Identifier not yet assigned value" << endl;
        return 1;
    }
    //s1 is an int
    else if (ints.find(s1) != ints.end())
        ints[s1] *= -1;
    else
    {
        cout << "Identifier " << s1 << " is neither new_id nor an int" << endl;
        return 1;
    }
    return 0;
}

int add_ints(string s1, string s2)
{
    if ((ints.find(s1) != ints.end()) && (ints.find(s2) != ints.end()))
        ints[s1] += ints[s2];

    else
    {
        cout << "The integers are not declared correctly. Please check" << endl;
        return 1;
    }
    return 0;
}

int if_case(string s1)
{
    //s1 is LList
    if (LLs.find(s1) != LLs.end())
    {
        if (LLs[s1]->head->data.value == -1723)
            return 0;
    }
    else if (ints.find(s1) != ints.end())
    {
        if (ints[s1] == 0)
            return 0;
    }
    return 1;
}

//
//// Trial main program:
//int main() {
//    LList parth;
//    parth.append(1);
//    parth.append(2);
//    LList rujuta;
//    rujuta.append(11);
//    rujuta.append(12);
//    parth.append(&rujuta);
////    parth.print();
//    rujuta.append(&parth);
//    rujuta.print();
//    return 0;
//}