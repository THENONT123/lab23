#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream source(filename);
    string text,strname;
    char name[100];
    int score[3] = {};
    char format[] = "%[^:]: %d %d %d";
    while(getline(source,text)){
        sscanf(text.c_str(),format,name,&score[0],&score[1],&score[2]);
        strname = name;
        int sumscore = score[0]+score[1]+score[2];
        names.push_back(strname);
        scores.push_back(sumscore);
        grades.push_back(score2grade(sumscore));
    }
}

void getCommand(string &command, string &key){
    cout<<"Please input your command:\n";
    string input;
    getline(cin,input);

    int end = input.find(" ");
    if(end != -1){
        command = toUpperStr(input.substr(0,end));
        key = input.substr(end+1);
    }
    else{
        command = toUpperStr(input.substr(0,end));
    }
}

void searchName(vector<string>&names, vector<int>&scores, vector<char>&grades , string key){
    int count=0;
    for(size_t i = 0 ;i<names.size();i++){
        if(toUpperStr(names[i])==toUpperStr(key)){
            count++;
            cout<<"---------------------------------\n";
            cout<<names[i]<<"'s score = "<<scores[i]<<"\n";
            cout<<names[i]<<"'s grade = "<<grades[i];
            cout<<"\n---------------------------------\n";
        }
    }
    if(count == 0){
            cout<<"---------------------------------\n";
            cout<<"Cannot found.\n";
            cout<<"---------------------------------\n";
        }
}

void searchGrade(vector<string>&names , vector<int>&scores , vector<char>&grades ,string key){
    string grade;
    int count = 0;
    cout<<"---------------------------------\n";
    for(size_t i = 0;i<names.size();i++){
        grade = grades[i];
        if(grade == key){
            count++;
            cout<<names[i]<<" ("<<scores[i]<<")\n";
        }
    }
    if(count == 0 ){
        cout<<"Cannot found.\n";
    }
    cout<<"---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
