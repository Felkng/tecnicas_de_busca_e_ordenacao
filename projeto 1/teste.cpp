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
//função para usar de parâmetro na ordenação de runTime
bool compareRunTime(const Movie &a, const Movie &b){
    return a.duration < b.duration;
}

//função que faz a interseção entre 2 conjuntos de forma linear
void intercesectionLinearMovie(vector<Movie> a, vector<Movie> b, vector<Movie> &res){
    res.clear();
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

//binarySearchDeMovies
int binarySearch(const vector<pair<string,vector<Movie>>> & arr, string target, int left, int right) {
    if (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].first == target) {
            return mid;
        } else if (arr[mid].first < target) {
            return binarySearch(arr, target, mid + 1, right);
        } else {
            return binarySearch(arr, target, left, mid - 1);
        }
    }
    return -1;
}

//Faz a uinião dos filmes em uma mesma coluna
void unionMovies(vector<pair<string,vector<Movie>>> &movieParser, vector<Movie> &result, int pos){
    for(int i=0; i<movieParser[pos].second.size();i++){
        result.push_back(movieParser[pos].second[i]);
    }
}

//Faz a consulta aos filmes de 1 ou mais colunas ao mesmo tempo
void movieConsulter(vector<vector<pair<string,vector<Movie>>>> &movieParser, vector<vector<Movie>> &result, string input){
    cout << "\n---" << input << "---" << endl;
    if(input.find("1") != input.npos){
        int choice=1;
        int pos=0;
        string valueTitleType;
        for(int i=0;;i++){
            if(choice == 1){
                cout << "\n\nQual/quais TitleType deseja procurar? \n";
                cin >> valueTitleType;
                pos = binarySearch(movieParser[0],valueTitleType,0,movieParser[0].size()-1);
                if(pos != -1)
                    unionMovies(movieParser[0],result[0],pos);
            }else{
                break;
            }
            cout << "\n\nMais outro?\n\n";
            cout << "1 - SIM\n\n2 - NÃO\n\n";
            cin >> choice;
        }
        // parserVectorMovie(valueTitleType,titleType,resTitleType,1, especify);
        sort(result[0].begin(),result[0].end(),compareIds);
    }
    if(input.find("2") != input.npos){
        int choice=1;
        int pos=0;
        string valueGenres;
        for(int i=0;;i++){
            if(choice == 1){
                cout << "\n\nQual/quais Gênero deseja procurar? \n";
                cin >> valueGenres;
                pos = binarySearch(movieParser[1],valueGenres,0,movieParser[1].size()-1);
                if(pos != -1)
                    unionMovies(movieParser[1],result[1],pos);
            }else{
                break;
            }
            cout << "\n\nMais outro?\n\n";
            cout << "1 - SIM\n\n2 - NÃO\n\n";
            cin >> choice;
        }
        // parserVectorMovie(valueGenres,genres,resGenres,2, especify);
        sort(result[1].begin(),result[1].end(),compareIds);
    }
    if(input.find("3") != input.npos){
        string valueStartYear, valueEndYear;
        int choice, pos;
        cout << "\n\nDeseja procurar por um ano específico ou entre um intervalo de tempo?\n\n";
        cout << "1 - Ano específico\n2 - Intervalo\n\n";
        cin >> choice;
        if(choice == 1){
            cout << "\n\nQual ano?\n\n";
            cin >> valueStartYear;
            pos = binarySearch(movieParser[2],valueStartYear,0,movieParser[2].size()-1);
            if(pos != -1)
                unionMovies(movieParser[2],result[2],pos);
            // parserVectorMovie(valueStartYear,startYear,resStartYear,3,especify);
            sort(result[2].begin(),result[2].end(),compareIds);
        }else{
            cout << "\n\nAno de lançamento: \n\n";
            cin >> valueStartYear;
            cout << "\n\nAno de término:\n\n";
            cin >> valueEndYear;
            int finalPos;
            // pos = binarySearch(movieParser[2],valueStartYear,0,movieParser[2].size()-1);
            for(int i=0, j=0; j < movieParser[2].size(); j++){
                if(movieParser[2][i].first >= valueStartYear){
                    pos=i;
                }else{
                    i++;
                }
                if(movieParser[2][i].first <= valueEndYear){
                    finalPos = j;
                }else{
                    break;
                }
            }
            // finalPos = binarySearch(movieParser[2],valueEndYear,0,movieParser[2].size()-1);
            cout << "------ " << pos << "---------" << finalPos;
            for(int i=pos; i<finalPos; i++){
                if(i != -1)
                    unionMovies(movieParser[2],result[2],i);
            }
            // especify = valueEndYear;
            // parserVectorMovie(valueStartYear,startYear,resStartYear,3,especify);
            sort(result[2].begin(),result[2].end(),compareIds);
        }
    }
    if(input.find("4") != input.npos){
        string valueRunTime;
        int pos;
        cout << "\n\nQual intervalo de tempo de duração você procura? \n";
        cin >> valueRunTime;
        pos = binarySearch(movieParser[3],valueRunTime,0,movieParser[3].size()-1);
        unionMovies(movieParser[3],result[3],pos);
        // parserVectorMovie(valueRunTime,runTime,resRunTime,4,especify);
        sort(result[3].begin(),result[3].end(),compareIds);
    }
}

//Imprime a interseção, se houver, dos filmes procurados
void printResult(vector<Movie> finalRes, vector<vector<Movie>> &resultado, string input){
    int ctVerify=0;
    if(input.find("1") != input.npos){
        intercesectionLinearMovie(resultado[0], resultado[0], finalRes);
        ctVerify++;
    }
    if(input.find("2") != input.npos){
        if(ctVerify == 0){
            intercesectionLinearMovie(resultado[1], resultado[1], finalRes);
            ctVerify++;
        }
        intercesectionLinearMovie(finalRes, resultado[1], finalRes);
    }
    if(input.find("3") != input.npos){
        if(ctVerify == 0){
            intercesectionLinearMovie(resultado[2],resultado[2],finalRes);
            ctVerify++;
        }
        intercesectionLinearMovie(finalRes,resultado[2],finalRes);
    }
    if(input.find("4") != input.npos){
        if(ctVerify == 0){
            intercesectionLinearMovie(resultado[3],resultado[3],finalRes);
            ctVerify++;
        }
        intercesectionLinearMovie(finalRes,resultado[3],finalRes);
    }
    cout << "\n\n";
    for(auto x : finalRes){
        cout << "tconst: " << x.tconst << " OriginalTitle: " << x.originalTitle << " StartYear: " << x.startYear << " endYear: " << x.endYear  << " TitleType: " << x.titleType << " Genres: " << x.genres << " Duração: " << x.duration <<"\n";
    }
    cout << endl;
    resultado[0].clear();
    resultado[1].clear();
    resultado[2].clear();
    resultado[3].clear();
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
    cout << "1 - Tipo de filme\n2 - Gênero\n3 - Ano\n4 - Duração\n\n";
    cout << "********************************************\n\n";
}

void menuMoreOneMovie(){
    system("clear");
    cout << "********************************************\n\n";
    cout << "Mais algum? Qual?\n\n";
    cout << "0 - NÃO\n";
    cout << "1 - Tipo de filme\n2 - Gênero\n3 - Ano\n4 - Duração\n\n";
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
    int j = 0;
    int ct = 0;
    Movie movie;
    vector<string> content;
    while(getline(file,line,'\t')){
        if(j%8==0){
            pair<string,string> separator = splitString(line);
            content.push_back(separator.first);
            if(separator.second != "")
                content.push_back(separator.second);
        }else{
            content.push_back(line);
        }
        j++;

    }

    file.close();

     vector<Movie> TitleType;
     vector<Movie> genres;
     vector<Movie> startYear;
     vector<Movie> runTime;

    for(int i=0;i<content.size();i+=9){
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
        // movieTable.push_back(movie);
        genres.push_back(movie);
        startYear.push_back(movie);
        TitleType.push_back(movie);
        runTime.push_back(movie);
    }
    content.clear();

    sort(TitleType.begin(), TitleType.end(),compareTitleType);
    sort(genres.begin(), genres.end(), compareGenres);
    sort(startYear.begin(), startYear.end(), compareStartYear);
    sort(runTime.begin(), runTime.end(), compareRunTime);

    vector<Movie> resTitleType;
    vector<Movie> resGenres;
    vector<Movie> resStartYear;
    vector<Movie> resRunTime;

    // vector<pair<vector<string>,vector<Movie>>> movieParser;

    vector<vector<pair<string,vector<Movie>>>> movieParser;

    movieParser.resize(4);
    movieParser[0].resize(1);
    movieParser[1].resize(1);
    movieParser[2].resize(1);
    movieParser[3].resize(1);

    int a=0,b=0,c=0,d=0;
    for(int i=0; i<TitleType.size(); i++){
        if(TitleType[i].titleType == movieParser[0][a].first){
            movieParser[0][a].second.push_back(TitleType[i]);
        }else{
            movieParser[0].push_back(make_pair(TitleType[i].titleType,vector<Movie>{TitleType[i]}));
            a++;
        }if(genres[i].genres == movieParser[1][b].first){
            movieParser[1][b].second.push_back(genres[i]);
        }else{
            movieParser[1].push_back(make_pair(genres[i].genres,vector<Movie>{genres[i]}));
            b++;
        }if(to_string(startYear[i].startYear) == movieParser[2][c].first){
            movieParser[2][c].second.push_back(startYear[i]);
        }else{
            movieParser[2].push_back(make_pair(to_string(startYear[i].startYear),vector<Movie>{startYear[i]}));
            c++;
        }if(to_string(runTime[i].duration) == movieParser[3][d].first){
            movieParser[3][d].second.push_back(runTime[i]);
        }else{
            movieParser[3].push_back(make_pair(to_string(runTime[i].duration),vector<Movie>{runTime[i]}));
            d++;
        }
    }

    vector<vector<Movie>> resultado;
    vector<Movie> finalRes;
    resultado.push_back(resTitleType);
    resultado.push_back(resGenres);
    resultado.push_back(resStartYear);
    resultado.push_back(resRunTime);

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
            movieConsulter(movieParser,resultado,input);
            printResult(finalRes,resultado,input);
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
