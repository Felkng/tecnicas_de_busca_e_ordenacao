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

int binarySearchMovie(const vector<Movie> &arr, int l, int r, string dataToFind, int whatType){
    //whatType == 1 } primaryTitle
    //whatType == 2 } genres
    //whatType == 3 } startYear
    int result = -1; //garantir que sempre retorne a primeira aparição no vetor
    while (l <= r) {
        int m = l + (r - l) / 2;
        switch(whatType){
            case 1: 
                if (arr[m].titleType == dataToFind){
                    result = m;
                    r = m - 1;
                }
                else if (arr[m].titleType < dataToFind)
                    l = m + 1;
                else
                    r = m - 1;
            break;
            case 2:
                if (arr[m].genres == dataToFind){
                    result = m;
                    r = m - 1;
                }
                else if (arr[m].genres < dataToFind)
                    l = m + 1;
                else
                    r = m - 1;
            break;
            case 3:
                if (arr[m].startYear == stoi(dataToFind)){
                    result = m;
                    r = m - 1;
                }
                if (arr[m].startYear < stoi(dataToFind))
                    l = m + 1;
                else
                    r = m - 1;
            break;
            default:
                return -1;
        }
    }
    return result;
}

void splitVectorMovie(string dataToParse, vector<Movie> &vectorToParse, vector<Movie> &vectorResult, int dataType){
    //whatType == 1 } primaryTitle
    //whatType == 2 } genres
    //whatType == 3 } startYear
    // Encontrar a primeira ocorrência usando BS
    int first = binarySearchMovie(vectorToParse,0,vectorToParse.size()-1,dataToParse, dataType);
    for(int i=first; i < vectorToParse.size(); i++){
        if(dataType == 1 && vectorToParse[i].titleType == dataToParse)
            vectorResult.push_back(vectorToParse[i]);
        else if(dataType == 2 && vectorToParse[i].genres == dataToParse)
            vectorResult.push_back(vectorToParse[i]);
        else if(dataType == 3 && vectorToParse[i].startYear == stoi(dataToParse))
            vectorResult.push_back(vectorToParse[i]);
        else 
            return;
    }
}

bool compareTitleType(const Movie &a, const Movie &b){
    return a.titleType < b.titleType;
}

bool compareGenres(const Movie &a, const Movie &b){
    return a.genres < b.genres;
}

bool compareStartYear(const Movie &a, const Movie &b){
    return a.startYear < b.startYear;
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

    pair<string, vector<Movie>> TitleType;
    pair<string, vector<Movie>> genres;
    pair<int, vector<Movie>> startYear;

    for(int i=0;i<396;i+=9){
        movie.tconst = content[i];
        movie.titleType = content[i+1];
        TitleType.second.push_back(movie);
        // TitleType.push_back(movie.titleType);
        movie.primaryTitle = content[i+2];
        movie.originalTitle = content[i+3];
        if(content[i+4] == "\\N")
            content[i+4] = "0";
        movie.isAdult = stoi(content[i+4]);
        if(content[i+5] == "\\N")
            content[i+5] = "-1";
        movie.startYear = stoi(content[i+5]);
        startYear.second.push_back(movie);
        // startYear.push_back(movie.startYear);
        if(content[i+6] == "\\N")
            content[i+6] = "-1";
        movie.endYear = stoi(content[i+6]);
        if(content[i+7] == "\\N")
            content[i+7] = "-1";
        movie.duration = stoi(content[i+7]);
        movie.genres = content[i+8];
        genres.second.push_back(movie);
        // genres.push_back(movie.genres);
        movieTable.push_back(movie);
    }
    content.clear();

    sort(TitleType.second.begin(), TitleType.second.end(),compareTitleType);
    sort(genres.second.begin(), genres.second.end(), compareGenres);
    sort(startYear.second.begin(), startYear.second.end(), compareStartYear);
    string val = "Comedy";

    vector<Movie> res;
    splitVectorMovie(val,genres.second,res,2);

    for(auto a: res){
        cout << a.genres << " " << a.tconst << " ";
    }

    cout << endl;

    return 0;
}
