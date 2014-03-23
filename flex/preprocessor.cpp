#include "header.h"
#include "preprocessor.h"

using namespace std;

string remove_comments(string s) {
    string source;
    ifstream iFile(s.c_str());
    getline(iFile, source, '\0');
    while(source.find("/*") != std::string::npos) {
        size_t Beg = source.find("/*");
        source.erase(Beg, (source.find("*/", Beg) - Beg)+2);
    }
    while(source.find("//") != std::string::npos) {
        size_t Beg = source.find("//");
        source.erase(Beg, source.find("\n", Beg) - Beg);
    }
    return source;
}

string replace_macros(string s) {
    string source;
    ifstream iFile(s.c_str());
    getline(iFile, source, '\0');
    map<string, string> macros;
    while(source.find("#define ") != std::string::npos) {
        size_t Beg = source.find("#define ");
    }
    map<string,string>::iterator l;
    for(l=macros.begin(); l!=macros.end(); l++) {
        while(source.find((*l).first) != std::string::npos) {

        }
    }
    return source;
}

string preprocessor(string s) {
    ofstream output;
    string file_name = ("~"+s.substr(0,s.find_last_of(".")+1)+"pc");
    output.open (file_name.c_str());
    output<<remove_comments(s);
    output.close();/*
    output.open (file_name);
    output<<replace_macros("~"+s.substr(s.find_last_of(".")+1)+".pc");
    output.close();*/
    return file_name;
}
