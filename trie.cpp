#include <bits/stdc++.h>
using namespace std;
#include <fstream>
#include <iostream>
#include <string>

struct Trie
{
    int wordcount;
    Trie* childs[26];
    
    Trie(){
        wordcount=0;
        for(int i=0;i<26;i++){
            childs[i]=nullptr;
        }
    }

    void insert_word(string& word){
        Trie* trev=this;
    
        int siz=word.length();
        for(int i=0;i<siz;i++){
            if(trev->childs[word[i]-'a']==nullptr){
                trev->childs[word[i]-'a']=new Trie();
            }
            trev=trev->childs[word[i]-'a'];
        }
        trev->wordcount+=1;
    }

    bool search_word(string& word){
        Trie* trev=this;
        int siz=word.length();
        for(int i=0;i<siz;i++){
            if(trev->childs[word[i]-'a']==nullptr){
                return false;
            }
            trev=trev->childs[word[i]-'a'];
        }
        if(trev->wordcount>0){
            return true;
        }
        return false;
    }

    bool search_prefix(string& word){
        Trie* trev=this;
        int siz=word.length();
        for(int i=0;i<siz;i++){
            if(trev->childs[word[i]-'a']==nullptr){
                return false;
            }
            trev=trev->childs[word[i]-'a'];
        }
        return true;
    }

    bool delete_word(string& word){
        Trie* trev=this;
        int siz=word.length();
        Trie* lastBranchNode = nullptr;
        char lastChar;
        for(int i=0;i<siz;i++){
            if(trev->childs[word[i]-'a']==nullptr){
                return false;
            }
            int count=0;
            for(int i=0;i<26;i++){
                if(trev->childs[i]!=nullptr){
                    count++;
                }
            }
            if(count>1){
                lastBranchNode=trev;
                lastChar=word[i];
            }
            trev=trev->childs[word[i]-'a'];
        }
        bool anc=false;
        for(int i=0;i<26;i++){
            if(trev->childs[i]!=nullptr){
                anc=true;
            }
        }
        if(anc){
            trev->wordcount--;
            return true;
        }else if(lastBranchNode!=nullptr){
            lastBranchNode->childs[lastChar-'a']=nullptr;
            return true;
        }else{
            this->childs[word[0]-'a']=nullptr;
            return true;
        }
        return false;
    }
};

int dp(string& txt1,string& txt2,int i1,int i2,vector<vector<int>>& lst){
    if(i1>=txt1.length() && i2>=txt2.length()){
        return 0;
    }
    if(i2>=txt2.length()){
        return txt1.length()-i1;
    }
    if(i1>=txt1.length()){
        return txt2.length()-i2;
    }
    if(lst[i1][i2]==-1){
        if(txt1[i1]==txt2[i2]){
            lst[i1][i2]=dp(txt1,txt2,i1+1,i2+1,lst);
        }else{
            lst[i1][i2]=1+min({dp(txt1,txt2,i1+1,i2+1,lst),dp(txt1,txt2,i1,i2+1,lst),dp(txt1,txt2,i1+1,i2,lst)});
        }
    }
    return lst[i1][i2];
}


void minDistance(string word) {
    int siz1=word.length();
    ifstream file("dictionary.txt");

    if (!file.is_open()) {
        cout << "Error: Could not open dictionary.txt!" << endl;
        return ;
    }

    string word2;
    priority_queue<pair<int,string>> pq;
    while(file >> word2){
        int siz2=word2.length();
        vector<vector<int>> arr(siz1,vector<int> (siz2,-1));
        int dist=dp(word,word2, 0,0,arr);
        pq.push({(-1)*dist,word2});
    }
    file.close();
    for(int i=0;i<2;i++){
        cout << i+1 << ". " << pq.top().second << endl;
        pq.pop();
    }
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Please enter a word." << endl;
        return 1;
    }

    string str = argv[1];

    Trie* trie = new Trie();
    ifstream file("dictionary.txt");

    if (!file.is_open()) {
        cout << "Error: Could not open dictionary.txt!" << endl;
        return 1;
    }

    string word;
    while (file >> word) {
        trie->insert_word(word);
    }
    file.close();

    if (trie->search_word(str)) {
        cout << "The entered word is correct" << endl;
    } else {
        cout << "The word entered is incorrect" << endl;
        cout << "Here are some suggestions : " << endl;
        minDistance(str);
    }

    return 0;
}