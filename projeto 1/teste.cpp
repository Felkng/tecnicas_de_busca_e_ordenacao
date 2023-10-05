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
            pair<string,string> separator = splitString(line);
            content.push_back(separator.first);
            if(separator.second != "")
                content.push_back(separator.second);
        }else{
            content.push_back(line);
        }
        i++;

    }

    file.close();
    vector<string>TitleType;
    vector<string> genres;
    vector<int> startYear;
    for(int i=0;i<396;i+=9){
        movie.tconst = content[i];
        movie.titleType = content[i+1];
        TitleType.push_back(movie.titleType);
        movie.primaryTitle = content[i+2];
        movie.originalTitle = content[i+3];
        if(content[i+4] == "\\N")
            content[i+4] = "0";
        movie.isAdult = stoi(content[i+4]);
        if(content[i+5] == "\\N")
            content[i+5] = "-1";
        movie.startYear = stoi(content[i+5]);
        startYear.push_back(movie.startYear);
        if(content[i+6] == "\\N")
            content[i+6] = "-1";
        movie.endYear = stoi(content[i+6]);
        if(content[i+7] == "\\N")
            content[i+7] = "-1";
        movie.duration = stoi(content[i+7]);
        movie.genres = content[i+8];
        genres.push_back(movie.genres);
        movieTable.push_back(movie);
    }
    content.clear();
    sort(TitleType.begin(), TitleType.end());
    sort(genres.begin(), genres.end());
    sort(startYear.begin(), startYear.end());
    string val = "short";

    // Encontrar a primeira ocorrência usando find
    auto first = find(TitleType.begin(), TitleType.end(), val);
    auto primeiro = distance(TitleType.begin(), first);

    // Encontrar a última ocorrência usando find_end
    vector <string> a;
    a.push_back(val);
    auto end = find_end(TitleType.begin(), TitleType.end(), a.begin(), a.end());
    auto fim = distance(TitleType.begin(), end);

    // Imprimir os resultados
    cout << "Primeira ocorrência de '" << val << "' encontrada no índice " << primeiro << endl;
    cout << "Última ocorrência de '" << val << "' encontrada no índice " << fim << endl;

    cout << endl;

    return 0;
}
