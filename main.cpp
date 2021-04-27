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
int combine(const string& s1, const string& s2);
int copy(const string& s1, const string& s2);
int head(const string& s1, const string& s2);
int assign(const string& s1, const string& s2);
int chs(const string& s1);
int add_ints(const string& s1, const string& s2);
int if_case(const string& s1);
LList* create(const string& id);

//Driver
int main(){
    // Map defining command to int to apply appropriate switch case
    map<string, int> command_int{{"NEWID", 1}, {"COMBINE", 2}, {"COPY", 3}, {"HEAD", 4}, {"TAIL", 5}, {"ASSIGN", 6}, {"CHS", 7}, {"ADD", 8}, {"IF", 9}, {"HLT", 10}};

    string addr;
    cout << "Enter name of the file: " << endl;
    cin >> addr;

    // 'lines' vector stores individual lines.
    vector<string> lines = openfile(addr);
    // If file is empty or not opened properly.
    if (lines.empty()){
        cout << "File either empty or not opened properly.";
        return 1;
    }

    int i = 0;
    while (i != lines.size())
    {
        int ret;
        vector<string> words = exec_line(lines.at(i));
        switch (command_int[words.back()]) {
            case 1:
                // Create a new-id
                new_ids.push_back(words[0]);
                break;
            case 2:
                // Combine case
                ret = combine(words[0], words[1]);
                if (ret != 0)
                {
                    cout << "There were some problems in the combine operation at line " << i+1 << endl;
                    return 1;
                }
                break;
            case 3:
                // Copy case
                ret = copy(words[0], words[1]);
                if (ret != 0)
                {
                    cout << "There were some problems in the copy operation at line " << i+1 << endl;
                    return 1;
                }
                break;
            case 4:
                // Head case
                ret = head(words[0], words[1]);
                if (ret != 0)
                {
                    cout << "There were some problems in the head operation at line " << i+1 << endl;
                    return 1;
                }
                break;
            case 5:
                // Tail case
                ret = copy(words[0], words[1]);
                if (ret == 0)
                {
                    LLs[words[1]]->head = LLs[words[1]]->head->next;
                    LLs[words[1]]->size--;
                } else
                {
                    cout << "There were some problems in the tail operation at line " << i+1 << endl;
                    return 1;
                }
                break;
            case 6:
                // Assign case
                ret = assign(words[0], words[1]);
                if (ret != 0)
                {
                    cout << "There were some problems in the assign operation at line " << i+1 << endl;
                    return 1;
                }
                break;
            case 7:
                // Change sign case
                ret = chs(words[0]);
                if (ret != 0)
                {
                    cout << "There were some problems in the change sign operation at line " << i+1 << endl;
                    return 1;
                }
                break;
            case 8:
                // Add case
                ret = add_ints(words[0], words[1]);
                if (ret != 0)
                {
                    cout << "There were some problems in the add operation at line " << i+1 << endl;
                    return 1;
                }
                break;
            case 9:
                // If case
                ret = if_case(words[0]);
                if (ret == 0)
                {
                    i = stoi(words[1]);
                    continue;
                }
                else
                    break;
            case 10:
                // Halt case
                cout << "Halting at line " << i+1 << endl;
                i = lines.size() - 1;
                break;
            default:
                cout << "Invalid command in file at line " << i + 1 << ". Terminating." << endl;
                return 1;
        }
        i++;
    }
    cout << "\n \n ===================================== \n \n" << "Program execution completed." << endl;
    cout << "Program counter: " << i << endl;
    cout << "\nLinked Lists: " << endl;

    // Iterator to print linked lists.
    map<string, LList*>::iterator itr;
    for (itr = LLs.begin(); itr != LLs.end(); ++itr)
    {
        cout << itr->first << ": ";
        itr->second->print();
        cout << endl;
    }
    cout << "\nInts: " << endl;

    // Iterator to print ints.
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

// Return vector containing lines
vector<string> openfile(const string& addr){
    string line;
    vector<string> lines;
    ifstream file(addr);
    if (file.is_open()){
        while (getline(file, line))
        {
            if (line.size() == 1)
            {
                cout << "Empty line found after line " << lines.size() << ". Skipping." << endl;
                continue;
            }
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}

// Return vector containing words in line
vector<string> exec_line(const string& line){
    string word;
    vector<string> words;
    stringstream iss(line);
    while (iss >> word)
        words.push_back(word);
    return words;
}

// Combine operation
int combine(const string& s1, const string& s2)
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
        else
        {
            cout << "The ID " << s1 << " is neither an int nor a LL. Please check." << endl;
            return 1;
        }
    }
    //S2 non existent.
    else
    {
        cout << "Create " << s2 << " as a new_id first." << endl;
        return 1;
    }
    return 0;
}

// Copy case
int copy(const string& s1, const string& s2)
{
    // S2 not LList, but declared in new_ids
    if ((LLs.find(s2) == LLs.end()) && (find(new_ids.begin(), new_ids.end(), s2) != new_ids.end() ))
    {
        new_ids.erase(find(new_ids.begin(), new_ids.end(), s2));
        create(s2);
        if (LLs.find(s1) != LLs.end())
            LLs[s2]->copy_from(LLs[s1]);
        else if (find(new_ids.begin(), new_ids.end(), s1) != new_ids.end())
            LLs[s2]->clear();
        else {
            cout << "The ID " << s1 << " is not declared properly as a LL. Please check." << endl;
            return 1;
        }
    }
    // S2 is a linked list
    else if (LLs.find(s2) != LLs.end())
    {
        if (LLs.find(s1) != LLs.end())
        {
            LLs[s2]->clear();
            LLs[s2]->copy_from(LLs[s1]);
        }
        else if (find(new_ids.begin(), new_ids.end(), s1) != new_ids.end())
            LLs[s2]->clear();
        else {
            cout << 2 << endl;
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

int head(const string& s1, const string& s2)
{
    //s1 not an LList
    if (LLs.find(s1) == LLs.end())
    {
        cout << "Identifier 1 not declared properly" << endl;
        return 1;
    }
    else
    {
        // S1's head is a LList
        if (LLs[s1]->head->holds_ll)
        {
            // S2 not LList, but declared in new_ids
            if ((LLs.find(s2) == LLs.end()) && (find(new_ids.begin(), new_ids.end(), s2) != new_ids.end() ))
            {
                new_ids.erase(find(new_ids.begin(), new_ids.end(), s2));
                create(s2);
                LLs[s2]->append(LLs[s1]->head->data.ll);
            }
            // S2 a linked list
            else if (LLs.find(s2) != LLs.end())
            {
                LLs[s2]->clear();
                LLs[s2]->append(LLs[s1]->head->data.ll);
            }
            else if ((LLs.find(s2) == LLs.end()) && (find(new_ids.begin(), new_ids.end(), s2) == new_ids.end() ))
            {
                cout << "s2 not properly declared" << endl;
                return 1;
            }
        }
        // S1's head is an int
        else
        {
            // S2 not an int, but declared in new_ids
            if ((ints.find(s2) == ints.end()) && (find(new_ids.begin(), new_ids.end(), s2) != new_ids.end() ))
            {
                new_ids.erase(find(new_ids.begin(), new_ids.end(), s2));
                ints[s2] = LLs[s1]->head->data.value;
            }
            // S2 a linked list
            else if (ints.find(s2) != ints.end())
            {
                ints[s2] = LLs[s1]->head->data.value;
            }
            else if ((ints.find(s2) == ints.end()) && (find(new_ids.begin(), new_ids.end(), s2) == new_ids.end() ))
            {
                cout << "s2 not properly declared" << endl;
                return 1;
            }
        }
    }
    return 0;
}
// Create a new Linked List
LList* create(const string& id){
    LLs[id] = new LList();
    return LLs[id];
}

// Assign operation
int assign(const string& s1, const string& s2)
{
    //s2 is not a valid integer
    if ((to_string(stoi(s2)).size()) != s2.size())
    {
        cout << "Invalid integer entered" << endl;
        return 1;
    }
    else
    {
        // S1 is a new_id
        if (find(new_ids.begin(), new_ids.end(), s1) != new_ids.end())
        {
            new_ids.erase(find(new_ids.begin(), new_ids.end(), s1));
            ints[s1] = stoi(s2);
        }
        // S1 is an int
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

// Change sign operation
int chs(const string& s1)
{
    // S1 is a new_id
    if (find(new_ids.begin(), new_ids.end(), s1) != new_ids.end())
    {
        cout << "Identifier not yet assigned value" << endl;
        return 1;
    }
    // S1 is an int
    else if (ints.find(s1) != ints.end())
        ints[s1] *= -1;
    // S1 non existent
    else
    {
        cout << "Identifier " << s1 << " is neither new_id nor an int" << endl;
        return 1;
    }
    return 0;
}

// Add case
int add_ints(const string& s1, const string& s2)
{
    // Both ints found successfully
    if ((ints.find(s1) != ints.end()) && (ints.find(s2) != ints.end()))
        ints[s1] += ints[s2];
    else
    {
        cout << "The integers are not declared correctly. Please check" << endl;
        return 1;
    }
    return 0;
}

// If case
int if_case(const string& s1)
{
    // S1 is LList
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
