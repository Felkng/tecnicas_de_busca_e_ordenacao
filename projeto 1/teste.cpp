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

//função auxiliar para tratar a leitura de dados separados por '\n' ao invés de '\t'
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

//busca a primeira ocorrencia dos dados inseridos
int binarySearchMovie(const vector<Movie> &arr, int l, int r, string dataToFind, int whatType){
    //whatType == 1 } titleType
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

//Cria um vetor resultado filtrado pela entrada a partir do dado inserido 
void parserVectorMovie(string dataToParse, vector<Movie> &vectorToParse, vector<Movie> &vectorResult, int dataType){
    //whatType == 1 } titleType
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

//função para usar de parâmetro na ordenação de titleTypes
bool compareTitleType(const Movie &a, const Movie &b){
    return a.titleType < b.titleType;
}
//função para usar de parâmetro na ordenação de genres
bool compareGenres(const Movie &a, const Movie &b){
    return a.genres < b.genres;
}
//função para usar de parâmetro na ordenação de startYear
bool compareStartYear(const Movie &a, const Movie &b){
    return a.startYear < b.startYear;
}
//função para usar de parâmetro na ordenação de tconst
bool compareIds(const Movie &a, const Movie &b){
    return a.tconst < b.tconst;
}

void intercesectionLinearMovie(const vector<Movie> &a, const vector<Movie> &b, vector<Movie> &res){
    for(int i=0, j=0; i < a.size() && j < b.size() ; ){
        if(a[i].tconst == b[j].tconst){
            res.push_back(a[i]);
            i++;
            j++;
        }else if(a[i].tconst < b[j].tconst){
            i++;
        }else{
            j++;
        }
    }
}


// parserVectorMovie("tvEpisode",TitleType.second,resTitleType,1);
// sort(resTitleType.begin(), resTitleType.end(), compareIds);
// parserVectorMovie("Comedy",genres.second,resGenres,2);
// sort(resGenres.begin(), resGenres.end(), compareIds);
// parserVectorMovie("2017",startYear.second,resStartYear,3);
// sort(resStartYear.begin(), resStartYear.end(), compareIds);

void moviesConsult(vector<Movie> &titleType, vector<Movie> &genres, vector<Movie> &startYear, vector<Movie> &resTitleType, vector<Movie> &resGenres, vector<Movie> &resStartYear, string consultas){
    cout << "\n---" << consultas << "---" << endl;
    if(consultas.find("1") != consultas.npos){
        string valueTitleType;
        cout << "Qual TitleType deseja procurar? \n";
        cin >> valueTitleType;
        parserVectorMovie(valueTitleType,titleType,resTitleType,1);
        sort(resTitleType.begin(),resTitleType.end(),compareIds);
    }
    if(consultas.find("2") != consultas.npos){
        string valueGenres;
        cout << "Qual Genres deseja procurar? \n";
        cin >> valueGenres;
        parserVectorMovie(valueGenres,genres,resGenres,2);
        sort(resGenres.begin(),resGenres.end(),compareIds);
    }
    if(consultas.find("3") != consultas.npos){
        string valueStartYear;
        cout << "Qual StartYear deseja procurar? \n";
        cin >> valueStartYear;
        parserVectorMovie(valueStartYear,startYear,resStartYear,3);
        sort(resStartYear.begin(),resStartYear.end(),compareIds);
    }
    //if(consultas.find("4")){}
}

void printResult(vector<Movie> &resTitleType, vector<Movie> &resGenres, vector<Movie> &resStartYear,vector<Movie> &resultado){
    vector<Movie> intersector;

    if(!resTitleType.empty() && !resStartYear.empty() && !resGenres.empty()){
        intercesectionLinearMovie(resTitleType,resStartYear,intersector);
        intercesectionLinearMovie(resGenres,intersector,resultado);
    }else if(!resTitleType.empty() && !resStartYear.empty()){
        intercesectionLinearMovie(resTitleType,resStartYear,resultado);
    }else if(!resTitleType.empty() && !resGenres.empty()){
        intercesectionLinearMovie(resTitleType,resGenres,resultado);
    }else if(!resGenres.empty() && !resStartYear.empty()){
        intercesectionLinearMovie(resGenres,resStartYear,resultado);
    }else{
        intercesectionLinearMovie(resTitleType,resTitleType,resultado);
        if(!resultado.empty())
            intercesectionLinearMovie(resGenres,resGenres,resultado);
        if(!resultado.empty())
            intercesectionLinearMovie(resStartYear,resStartYear,resultado);

    }

    for(auto x : resultado){
        cout << "tconst: " << x.tconst << " OriginalTitle: " << x.originalTitle << " StartYear: " << x.startYear  << " TitleType: " << x.titleType << " Genres: " << x.genres << "\n";
    }

    cout << endl;
    resTitleType.clear();
    resGenres.clear();
    resStartYear.clear();
}

void menu(){
    system("clear");
    cout << "********************************************\n\n";
    cout << "Qual consulta deseja realizar? \n\n";
    cout << "1 - Filmes \n2 - Cinemas\n\n";
    cout << "********************************************\n\n";

}

void menuFilmes(){
    system("clear");
    cout << "********************************************\n\n";
    cout << "Quais filtros deseja utilizar?\n\n";
    cout << "1 - TitleType\n2 - Genres\n3 - StartYear\n\n";
    cout << "********************************************\n\n";
}

void menuMoreOneMovie(){
    system("clear");
    cout << "********************************************\n\n";
    cout << "Mais algum? Qual?\n\n";
    cout << "0 - NÃO\n";
    cout << "1 - TitleType\n2 - Genres\n3 - StartYear\n\n";
    cout << "********************************************\n\n";
}

void finalizar(){
    cout << "********************************************\n\n";
    cout << "Algo mais?\n\n";
    cout << "0 - SAIR\n1 - Outra consulta\n\n";
    cout << "********************************************\n\n";
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
        // TitleType.push_back(movie.titleType);
        movie.primaryTitle = content[i+2];
        movie.originalTitle = content[i+3];
        if(content[i+4] == "\\N")
            content[i+4] = "0";
        movie.isAdult = stoi(content[i+4]);
        if(content[i+5] == "\\N")
            content[i+5] = "-1";
        movie.startYear = stoi(content[i+5]);
        // startYear.push_back(movie.startYear);
        if(content[i+6] == "\\N")
            content[i+6] = "-1";
        movie.endYear = stoi(content[i+6]);
        if(content[i+7] == "\\N")
            content[i+7] = "-1";
        movie.duration = stoi(content[i+7]);
        movie.genres = content[i+8];
        // genres.push_back(movie.genres);
        movieTable.push_back(movie);
        genres.second.push_back(movie);
        startYear.second.push_back(movie);
        TitleType.second.push_back(movie);
    }
    content.clear();

    sort(TitleType.second.begin(), TitleType.second.end(),compareTitleType);
    sort(genres.second.begin(), genres.second.end(), compareGenres);
    sort(startYear.second.begin(), startYear.second.end(), compareStartYear);

    vector<Movie> resTitleType;
    vector<Movie> resGenres;
    vector<Movie> resStartYear;
    vector<Movie> resultado;

    string input;
    for(;;){
        menu();
        cin >> input;
        if(input == "1"){
            menuFilmes();
            cin >> input;
            for(;;){
                menuMoreOneMovie();
                string addMore;
                cin >> addMore;
                if(addMore == "0")
                    break;
                if(input.find(addMore) == input.npos){
                    input.append(addMore);
                }
            }
            moviesConsult(TitleType.second,genres.second,startYear.second,resTitleType,resGenres,resStartYear,input);
            printResult(resTitleType,resGenres,resStartYear,resultado);
            finalizar();
            cin >> input;
            if(input == "0")
                return 0;
            else
                continue;
        }
    }


    return 0;
}
