#include <iostream>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <regex>
#include <iterator>

using namespace std;

struct Movie {
    string tconst;
    string titleType;
    string primaryTitle;
    string originalTitle;
    bool isAdult;
    int startYear;
    int endYear;
    int duration;
    string genres;
};



pair<string, string> splitString(const string& input) {
    // Encontrar a posição do primeiro caractere de nova linha
    size_t pos = input.find('\n');

    // Se não encontrar '\n', retorna a string original e uma string vazia
    if (pos == string::npos) {
        return make_pair(input, "");
    }

    // Extrair a substring antes do '\n'
    string part1 = input.substr(0, pos);

    // Extrair a substring após o '\n'
    string part2 = input.substr(pos + 1);

    // Retornar as duas partes em um par de strings
    return make_pair(part1, part2);
}

int main() {
    vector<Movie> movieTable;
    string fileName = "filmesCrop.txt"; // Change to your file name

    // Read data from the text file and populate the movieTable vector
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << fileName << endl;
        return 1;
    }

    string line;

    getline(file,line);
    int i = 0;
    int ct = 0;
    Movie movie;
    vector<string> content;
    // istringstream iss;
    while(getline(file,line,'\t')){
        if(i%8==0){
            // cout << "linha: " << line << endl;
            pair<string,string> separator = splitString(line);
            // cout << "separador 1: " << separator.first << endl;
            // cout << "separador 2: " << separator.second << endl;
            content.push_back(separator.first);
            if(separator.second != "")
                content.push_back(separator.second);
        }else{
            content.push_back(line);
        }
        i++;

        // // iss.str("");
        // // iss.clear();
        // // iss.str(line);
        // istringstream iss(line);
        // // iss >> movie.tconst >> movie.titleType >> movie.primaryTitle >> movie.originalTitle >> movie.isAdult >> movie.startYear >> movie.endYear >> movie.duration >> movie.genres;
        // // movieTable.push_back(movie);
    }
    // while (getline(file, line)) {
    //     regex whiteSpace(" ");
    //     regex barraN("\\\\N");
    //     regex igualin("=");
        
    //     // write the results to an output iterator
    //     line = regex_replace(line, whiteSpace, "=");
    //     line = regex_replace(line, barraN, "-1");
    //     // iss.getline(line);
    //     // iss(line);

    //     if((iss >> movie.tconst >> movie.titleType >> movie.primaryTitle >> movie.originalTitle >> movie.isAdult >>  movie.startYear >> movie.endYear >> movie.duration >> movie.genres)){
    //         movie.primaryTitle = regex_replace(movie.primaryTitle, igualin, " ");
    //         movie.originalTitle = regex_replace(movie.originalTitle, igualin, " ");
    //         movieTable.push_back(movie);
    //     } else {
    //         cerr << "Failed to parse line: " << line << i << endl;

    //     }
    // }
    // map<string,string> title_types;
    file.close();
    map<string,set<string>> title_types_map;
    map<string,set<string>> genres_map;
    map<int,set<string>> startYear_map;
    for(int i=0;i<content.size();i+=9){
        movie.tconst = content[i];
        movie.titleType = content[i+1];
        movie.primaryTitle = content[i+2];
        movie.originalTitle = content[i+3];
        if(content[i+4] == "\\N")
            content[i+4] = "0";
        movie.isAdult = stoi(content[i+4]);
        if(content[i+5] == "\\N")
            content[i+5] = "-1";
        movie.startYear = stoi(content[i+5]);
        if(content[i+6] == "\\N")
            content[i+6] = "-1";
        movie.endYear = stoi(content[i+6]);
        if(content[i+7] == "\\N")
            content[i+7] = "-1";
        movie.duration = stoi(content[i+7]);
        movie.genres = content[i+8];
        title_types_map[movie.titleType].insert(movie.tconst);
        genres_map[movie.genres].insert(movie.tconst);
        startYear_map[movie.startYear].insert(movie.tconst);
        movieTable.push_back(movie);
    }
    content.clear();

    // set<string> title_types_map_union;
    // set<string> genres_map_union;

    // for (const auto& entry : title_types_map) {
    //         cout << entry.first << ": ";
            
    //         // Print each element in the vector
    //         for (const auto& value : entry.second) {
    //             cout << value << " ";
    //         }

    //         cout << endl;
    // }

    set<string> intersection;
    // Use set_intersection to find the common elements
    set_intersection(
        title_types_map["short"].begin(), title_types_map["short"].end(),
        genres_map["Drama,History,Short"].begin(), genres_map["Drama,History,Short"].end(),
        inserter(intersection, intersection.begin())
    );

    // Print the intersection
    cout << "Intersection: ";
    for (string value : intersection) {
        cout << value << " ";
    }
    cout << endl;

    return 0;
}
