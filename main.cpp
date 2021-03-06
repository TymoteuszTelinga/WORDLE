
#include <iostream>
#include <fstream>

#include <list>
#include <string>
#include <Windows.h>

using namespace std;

string accepted="",banish="",mask = "_____";
string banishPos[5];

//any letter
bool containLeter(const string& word, const string& letters)
{
    for (size_t l = 0; l < letters.size(); l++)
    {
        if (word.find(letters[l]) != string::npos)
        {
            if (letters[l]<0)
            {
                l++;
                if(word.find(letters[l]) != string::npos)
                {
                    return true;
                }
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}

//contain single character
bool containLeter(const string& word, const char c)
{
    if (word.find(c) != string::npos)
    {
        return true;
    }
    return false;
}

//all letters
bool containLetters(const string& word, const string& letters)
{
    for (size_t l = 0; l < letters.size(); l++)
    {
        if (word.find(letters[l]) == string::npos)
        {
            if (letters[l]<0)
            {
                l++;
                if(word.find(letters[l]) == string::npos)
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

//load all words from file
list<string> loadDict(const string& src)
{
    list<string> dict;

    ifstream file(src);
    if (!file.is_open())
    {
        return dict;
    }

    string word;

    while (!file.eof())
    {
        getline(file,word);
        dict.push_back(word);
    }
    return dict;
    
}

//delete words that contain any of banish letter
void banishLeters(list<string>& dict, const string& letters)
{
    for (auto it = dict.begin(); it != dict.end(); it++)
    {
        if (containLeter(*it,letters))
        {
            it = dict.erase(it);
            it--;
        }
    }
}

//delete words that don't have all of accepted letters
void acceptLeters(list<string>& dict, const string& letters)
{
    if (letters == "")
    {
        return;
    }
    
    for (auto it = dict.begin(); it != dict.end(); it++)
    {
        if (!containLetters(*it,letters))
        {
            it = dict.erase(it);
            it--;
        }
    }
}

//compare word to specifik mask
bool compareToMask(const string& word, const string& mask)
{
    for (size_t m=0,w=0; m < mask.size(); m++,w++)
    {
        if (mask[m] == '_')
        {
            if (word[w] < 0)
            {
                w++;
            }
            continue;
        }
        
        if (word[w] != mask[m])
        {
            return false;
        }
    }

    return true;
}

//delete words thad don't fit mask
void filterByMask(list<string>& dict, const string& mask)
{
    for (auto it = dict.begin(); it != dict.end(); it++)
    {
        if (!compareToMask(*it,mask))
        {
            it = dict.erase(it);
            it--;
        }
    }
}

//check if specifik leters apear on specifik position
bool checkWordPos(const string& word)
{
    for (size_t i = 0; i < 5; i++)
    {
        if(containLeter(banishPos[i],word[i]))
        {
            return true;
        }
    }
    return false;
    
}

//filter word list by checking letters position in word
void filterByPos(list<string>& dict)
{
    for (auto it = dict.begin(); it != dict.end(); it++)
    {
        if (checkWordPos(*it))
        {
            it = dict.erase(it);
            it--;
        }
    }
}

//display top of posible words
void showTopOpcions(const list<string>& dict, const int ammount)
{
    auto it = dict.begin();
    for (size_t i = 0; i < ammount && it != dict.end(); i++,it++)
    {
        cout<<*it<<'\n';
    }
    if (dict.size() > ammount)
    {
        cout<<"...\n";
    }
}

//split letters to categoris base on score
void processWord(const string& word, const string& score)
{
    for (size_t i = 0; i < score.size(); i++)
    {
        switch (score[i])
        {
        case '1':
            mask[i] = word[i];
            break;
        case '0':
            if(accepted.find(word[i]) == string::npos)
            {
                accepted+=word[i];
            }
            banishPos[i]+=word[i];
            break;
        case '-':
            if(banish.find(word[i]) == string::npos)
                banish+=word[i];
            break;
        
        default:
            break;
        }
    }
}

//test funcion
void saveDict(const list<string>& dict, const string& src)
{
    ofstream file(src);

    if (!file.is_open())
    {
        return;
    }
    
    for (auto &word : dict)
    {
        file<<word<<'\n';
    }
    
    file.close();
}
//test funcion
float scoreWord(const string& word)
{
    float sum = 0.0f;
    for (size_t w = 0; w < word.size(); w++)
    {
        if (word[w] > 0)
        {
            switch (word[w])
            {
            case 'a':
                sum+=8.91;
                break;
            case 'b':
                sum+=1.47;
                break;
            case 'c':
                sum+=3.96;
                break;
            case 'd':
                sum+=3.25;
                break;
            case 'e':
                sum+=7.66;
                break;
            case 'f':
                sum+=0.30;
                break;
            case 'g':
                sum+=1.42;
                break;
            case 'h':
                sum+=1.08;
                break;
            case 'i':
                sum+=8.21;
                break;
            case 'j':
                sum+=2.28;
                break;
            case 'k':
                sum+=3.51;
                break;
            case 'l':
                sum+=2.10;
                break;
            case 'm':
                sum+=2.80;
                break;
            case 'n':
                sum+=5.52;
                break;
            case 'o':
                sum+=7.75;
                break;
            case 'p':
                sum+=3.13;
                break;
            case 'r':
                sum+=4.69;
                break;
            case 's':
                sum+=4.32;
                break;
            case 't':
                sum+=3.98;
                break;
            case 'u':
                sum+=2.50;
                break;
            case 'v':
                sum+=0.04;
                break;
            case 'w':
                sum+=4.65;
                break;
            case 'x'://
                sum+=0.02;
                break;
            case 'y':
                sum+=3.76;
                break;
            case 'z':
                sum+=5.64;
                break;
            }
        }
    }
    return sum;
}
//test funcion
uint32_t scoreWord2(const string& word)
{
    uint32_t score=0;
    for (auto &c : word)
    {
        switch (c)
        {
        case 'x':
            score|=1;
            break;
        case 'v':
            score|=(1<<1);
            break;
        case 'f':
            score|=(1<<2);
            break;
        case 'h':
            score|=(1<<3);
            break;
        case 'g':
            score|=(1<<4);
            break;
        case 'b':
            score|=(1<<5);
            break;
        case 'l':
            score|=(1<<6);
            break;
        case 'j':
            score|=(1<<7);
            break;
        case 'u':
            score|=(1<<8);
            break;
        case 'm':
            score|=(1<<9);
            break;
        case 'p':
            score|=(1<<10);
            break;
        case 'd':
            score|=(1<<11);
            break;
        case 'k':
            score|=(1<<12);
            break;
        case 'y':
            score|=(1<<13);
            break;
        case 'c':
            score|=(1<<14);
            break;
        case 't':
            score|=(1<<15);
            break;
        case 's':
            score|=(1<<16);
            break;
        case 'w':
            score|=(1<<17);
            break;
        case 'r':
            score|=(1<<18);
            break;
        case 'n':
            score|=(1<<19);
            break;
        case 'z':
            score|=(1<<20);
            break;
        case 'e':
            score|=(1<<21);
            break;
        case 'o':
            score|=(1<<22);
            break;
        case 'i':
            score|=(1<<23);
            break;
        case 'a':
            score|=(1<<24);
            break;
        }
    }
    return score;
}
//test funcion
bool compareWord(const string& w1, const string& w2)
{
    return ( scoreWord2(w1) > scoreWord2(w2) );
}
//test funcion
void showPosBasedBanish()
{
    for (size_t i = 0; i < 5; i++)
    {
        cout<<i<<": "<<banishPos[i]<<'\n';
    }
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);
    cout<<"Hello"<<endl;

    string word,score;
    list<string> dict;
    dict = loadDict("wordList.txt");
    dict.sort(compareWord);

    cout<<"type your guess\n";
    getline(cin,word);
    getline(cin,score);
    
    while (score != "11111") 
    {
        processWord(word,score);
        cout<<"Banned letters: \""<<banish<<"\" accepted letters: \""<<accepted<<"\" word mask: "<<mask<<'\n';
        banishLeters(dict,banish);
        acceptLeters(dict,accepted);
        filterByPos(dict);
        filterByMask(dict,mask);
        cout<<"options: "<<dict.size()<<endl;
        showTopOpcions(dict,10);
        cout<<"\nnext gues\n";
        cin>>word>>score;
    }
    cout<<"END\n";
    
    return 0;
}