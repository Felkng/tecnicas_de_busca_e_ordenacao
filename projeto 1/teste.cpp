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
#include <chrono>

using namespace std;
//estrutura de filmes
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
//estrutura de cinema
struct Cinema {
    string cinema_ID;
    string cinema_name;
    int cord_X;
    int cord_Y;
    float price_ticket;
    vector<Movie> movies;
};
//estrutura que atribue uma relação de filme para cinema
struct FilmesEmCartaz {
    string cinema_ID;
    Movie filme;
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

void removeCharacter(string &str, char charToRemove) {
    str.erase(remove(str.begin(), str.end(), charToRemove), str.end());
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

//função para usar de parâmetro na ordenação de FilmesEmCartaz
bool compareIdsMovieCartaz(const FilmesEmCartaz &a, const FilmesEmCartaz &b){
    return a.filme.tconst < b.filme.tconst;
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

//binarySearchMoviesStringDeMovies
int binarySearchMoviesString(const vector<pair<string,vector<Movie>>> & arr, string target, int left, int right) {
    if (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].first == target) {
            return mid;
        } else if (arr[mid].first < target) {
            return binarySearchMoviesString(arr, target, mid + 1, right);
        } else {
            return binarySearchMoviesString(arr, target, left, mid - 1);
        }
    }
    return -1;
}

//binarySearchMoviesUsandoInteiros
int binarySearchMoviesInt(const vector<pair<string,vector<Movie>>> & arr, int target, int left, int right) {
    if (left <= right) {
        int mid = left + (right - left) / 2;
        if (stoi(arr[mid].first) == target) {
            return mid;
        } else if (stoi(arr[mid].first) < target) {
            return binarySearchMoviesInt(arr, target, mid + 1, right);
        } else {
            return binarySearchMoviesInt(arr, target, left, mid - 1);
        }
    }
    return -1;
}

int distancia2pts(int x1, int y1, int x2, int y2){
    int dist = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    return dist;
}

//Faz a uinião dos filmes em uma mesma coluna
void unionMovies(vector<pair<string,vector<Movie>>> &movieParser, vector<Movie> &result, int pos){
    for(int i=0; i<movieParser[pos].second.size();i++){
        result.push_back(movieParser[pos].second[i]);
    }
}
//Faz as Queries dos titleType
void titleTypeQuery(vector<vector<pair<string,vector<Movie>>>> &movieParser, vector<vector<Movie>> &result){
    int choice=1;
    int pos=0;
    string valueTitleType;
    for(int i=0;;i++){
        if(choice == 1){
            cout << "\n\nQual/quais TitleType deseja procurar? \n";
            cin >> valueTitleType;
            auto start_time = chrono::high_resolution_clock::now();
            pos = binarySearchMoviesString(movieParser[0],valueTitleType,0,movieParser[0].size()-1);
            if(pos != -1){
                unionMovies(movieParser[0],result[0],pos);
                auto end_time = chrono::high_resolution_clock::now();
                auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
                cout << "Tempo para carregar os dados: " << elapsed_time << "segundos\n";
            }
        }else{
            break;
        }
        cout << "\n\nMais outro?\n\n";
        cout << "1 - SIM\n\n2 - NÃO\n\n";
        cin >> choice;
    }
    // parserVectorMovie(valueTitleType,titleType,resTitleType,1, especify);
    auto start_time = chrono::high_resolution_clock::now();
    sort(result[0].begin(),result[0].end(),compareIds);
    auto end_time = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
    cout << "\nTempo para organizar os dados: " << elapsed_time << "segundos\n";
}
//Faz as Queries de Genres
void genresQuery(vector<vector<pair<string,vector<Movie>>>> &movieParser, vector<vector<Movie>> &result){
    int choice=1;
    int pos=0;
    string valueGenres;
    for(int i=0;;i++){
        if(choice == 1){
            cout << "\n\nQual/quais Gênero deseja procurar? \n";
            cin >> valueGenres;
            auto start_time = chrono::high_resolution_clock::now();
            pos = binarySearchMoviesString(movieParser[1],valueGenres,0,movieParser[1].size()-1);
            if(pos != -1){
                unionMovies(movieParser[1],result[1],pos);
                auto end_time = chrono::high_resolution_clock::now();
                auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
                cout << "Tempo para carregar os dados: " << elapsed_time << "segundos\n";
            }
        }else{
            break;
        }
        cout << "\n\nMais outro?\n\n";
        cout << "1 - SIM\n\n2 - NÃO\n\n";
        cin >> choice;
    }
    // parserVectorMovie(valueGenres,genres,resGenres,2, especify);
    auto start_time = chrono::high_resolution_clock::now();
    sort(result[1].begin(),result[1].end(),compareIds);
    auto end_time = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
    cout << "\nTempo para organizar os dados: " << elapsed_time << "segundos\n";
}
//Faz as Queries de startYear
void yearQuery(vector<vector<pair<string,vector<Movie>>>> &movieParser, vector<vector<Movie>> &result){
    string valueStartYear, valueEndYear;
    int choice, pos;
    cout << "\n\nDeseja procurar por um ano específico ou entre um intervalo de tempo?\n\n";
    cout << "1 - Ano específico\n2 - Intervalo\n\n";
    cin >> choice;
    if(choice == 1){
        cout << "\n\nQual ano?\n\n";
        cin >> valueStartYear;
        auto start_time = chrono::high_resolution_clock::now();
        pos = binarySearchMoviesString(movieParser[2],valueStartYear,0,movieParser[2].size()-1);
        if(pos != -1){
            unionMovies(movieParser[2],result[2],pos);
            auto end_time = chrono::high_resolution_clock::now();
            auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
            cout << "Tempo para carregar os dados: " << elapsed_time << "segundos\n";
        }
        // parserVectorMovie(valueStartYear,startYear,resStartYear,3,especify);
        start_time = chrono::high_resolution_clock::now();
        sort(result[2].begin(),result[2].end(),compareIds);
        auto end_time = chrono::high_resolution_clock::now();
        auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
        cout << "\nTempo para organizar os dados: " << elapsed_time << "segundos\n";
    }else{
        cout << "\n\nAno de lançamento: \n\n";
        cin >> valueStartYear;
        cout << "\n\nAno de término:\n\n";
        cin >> valueEndYear;
        int finalPos;
        // pos = binarySearchMoviesString(movieParser[2],valueStartYear,0,movieParser[2].size()-1);
        auto start_time = chrono::high_resolution_clock::now();
        for(int i=0, j=0; j < movieParser[2].size(); j++){
            if(movieParser[2][i].first >= valueStartYear){
                pos=i;
            }else{
                i++;
            }
            if(valueEndYear >= movieParser[2][j].first){
                finalPos = j;
            }else{
                break;
            }
        }
        // finalPos = binarySearchMoviesString(movieParser[2],valueEndYear,0,movieParser[2].size()-1);
        for(int i=pos; i<finalPos; i++){
            if(i != -1){
                unionMovies(movieParser[2],result[2],i);
            }
        }
        auto end_time = chrono::high_resolution_clock::now();
        auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
        cout << "Tempo para carregar os dados: " << elapsed_time << "segundos\n";
        // especify = valueEndYear;
        // parserVectorMovie(valueStartYear,startYear,resStartYear,3,especify);
        start_time = chrono::high_resolution_clock::now();
        sort(result[2].begin(),result[2].end(),compareIds);
        end_time = chrono::high_resolution_clock::now();
        elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
        cout << "\nTempo para organizar os dados: " << elapsed_time << "segundos\n";
    }
}
//Faz as Queries de duration
void durationQuery(vector<vector<pair<string,vector<Movie>>>> &movieParser, vector<vector<Movie>> &result){
    int valueRunTime;
    int pos;
    cout << "\n\nQual intervalo de tempo de duração você procura? \n";
    cin >> valueRunTime;
    auto start_time = chrono::high_resolution_clock::now();
    pos = binarySearchMoviesInt(movieParser[3],valueRunTime,0,movieParser[3].size()-1);
    if(pos != -1){
        unionMovies(movieParser[3],result[3],pos);
        auto end_time = chrono::high_resolution_clock::now();
        auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
        cout << "Tempo para carregar os dados: " << elapsed_time << "segundos\n";
    }
    start_time = chrono::high_resolution_clock::now();
    sort(result[3].begin(),result[3].end(),compareIds);
    auto end_time = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
    cout << "\nTempo para organizar os dados: " << elapsed_time << "segundos\n";
    
}

//Faz a consulta aos filmes de 1 ou mais colunas ao mesmo tempo
void movieConsulter(vector<vector<pair<string,vector<Movie>>>> &movieParser, vector<vector<Movie>> &result, string input){
    cout << "\n---" << input << "---" << endl;
    if(input.find("1") != input.npos){
        titleTypeQuery(movieParser, result);
    }
    if(input.find("2") != input.npos){
        genresQuery(movieParser,result);
    }
    if(input.find("3") != input.npos){
        yearQuery(movieParser,result);
    }
    if(input.find("4") != input.npos){
        durationQuery(movieParser,result);   
    }
}

//Imprime a interseção, se houver, dos filmes procurados
void printResultMovies(vector<Movie> finalRes, vector<vector<Movie>> &resultado, string input){
    int ctVerify=0;
    auto start_time = chrono::high_resolution_clock::now();
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
    auto end_time = chrono::high_resolution_clock::now();
    for(auto x : finalRes){
        cout << "tconst: " << x.tconst << " OriginalTitle: " << x.originalTitle << " StartYear: " << x.startYear << " endYear: " << x.endYear  << " TitleType: " << x.titleType << " Genres: " << x.genres << " Duração: " << x.duration <<"\n";
    }
    auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
    cout << "Tempo para fazer as interseções: " << elapsed_time << "segundos\n";
    cout << endl;
    resultado[0].clear();
    resultado[1].clear();
    resultado[2].clear();
    resultado[3].clear();
}

//Faz a consulta dos cinemas de 1 ou mais colunas ao mesmo tempo
void cineConsulter(vector<vector<pair<string,vector<Movie>>>> &movieParser,vector<Cinema> &cinemas, vector<vector<Movie>> &result, vector<Cinema> &resCine, string input){
    cout << "\n---" << input << "---" << endl;
    if(input.find("1") != input.npos){
        titleTypeQuery(movieParser, result);
    }
    if(input.find("2") != input.npos){
        genresQuery(movieParser,result);
    }
    if(input.find("3") != input.npos){
        yearQuery(movieParser,result);
    }
    if(input.find("4") != input.npos){
        durationQuery(movieParser,result);   
    }
}

//Faz a interseção linear de FilmesEmCartaz
void intersectionLinearEmCartaz(vector<Movie> finalResMovies,vector<FilmesEmCartaz> filmesEmCartazCrop, vector<FilmesEmCartaz> &res){
    res.clear();
    for(int a=0,b=0; a < finalResMovies.size() && b < filmesEmCartazCrop.size();){
        if(finalResMovies[a].tconst == filmesEmCartazCrop[b].filme.tconst){
            filmesEmCartazCrop[b].filme.duration = finalResMovies[a].duration;
            filmesEmCartazCrop[b].filme.endYear = finalResMovies[a].endYear;
            filmesEmCartazCrop[b].filme.genres = finalResMovies[a].genres;
            filmesEmCartazCrop[b].filme.isAdult = finalResMovies[a].isAdult;
            filmesEmCartazCrop[b].filme.originalTitle = finalResMovies[a].originalTitle;
            filmesEmCartazCrop[b].filme.primaryTitle = finalResMovies[a].primaryTitle;
            filmesEmCartazCrop[b].filme.startYear = finalResMovies[a].startYear;
            filmesEmCartazCrop[b].filme.titleType = finalResMovies[a].titleType;
            res.push_back(filmesEmCartazCrop[b]);
            a++;
            b++;
        }else if(finalResMovies[a].tconst < filmesEmCartazCrop[b].filme.tconst){
            a++;
        }else{
            b++;
        }
    }
}

void intersectionLinearCinemas(vector<Cinema> a, vector<Cinema> b, vector<Cinema> &res){
    res.clear();
    for(int i=0, j=0; i < a.size() && j < b.size() ; ){
        if(a[i].cinema_ID == b[j].cinema_ID){
            res.push_back(a[i]);
            i++;
            j++;
        }else if(a[i].cinema_ID < b[j].cinema_ID){
            i++;
        }else{
            j++;
        }
    }
}

//Imprime os cinemas encontrados utilizando as interseções das queries
void printResultCines(vector<vector<pair<string,vector<Movie>>>> &movieParser,vector<Cinema> &cinemas,vector<Cinema> finalResCine , vector<Movie> finalResMovies,vector<FilmesEmCartaz> &filmesEmCartazCrop, vector<FilmesEmCartaz> &filmesEmCartazCropRes,vector<vector<Movie>> &resultado, string input){
    int ctVerify=0;
    bool hasMovies = false;
    auto start_time = chrono::high_resolution_clock::now();
    if(input.find("1") != input.npos){
        intercesectionLinearMovie(resultado[0], resultado[0], finalResMovies);
        ctVerify++;
        hasMovies = true;
    }
    if(input.find("2") != input.npos){
        if(ctVerify == 0){
            intercesectionLinearMovie(resultado[1], resultado[1], finalResMovies);
            ctVerify++;
        }
        intercesectionLinearMovie(finalResMovies, resultado[1], finalResMovies);
        hasMovies = true;

    }
    if(input.find("3") != input.npos){
        if(ctVerify == 0){
            intercesectionLinearMovie(resultado[2],resultado[2],finalResMovies);
            ctVerify++;
        }
        intercesectionLinearMovie(finalResMovies,resultado[2],finalResMovies);
        hasMovies = true;

    }
    if(input.find("4") != input.npos){
        if(ctVerify == 0){
            intercesectionLinearMovie(resultado[3],resultado[3],finalResMovies);
            ctVerify++;
        }
        intercesectionLinearMovie(finalResMovies,resultado[3],finalResMovies);
        hasMovies = true;

    }
    auto end_time = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
    cout << "Tempo para fazer interseções dos filmes: " << elapsed_time << "segundos\n";
    resultado[0].clear();
    resultado[1].clear();
    resultado[2].clear();
    resultado[3].clear();

    if(ctVerify > 0)
        intersectionLinearEmCartaz(finalResMovies,filmesEmCartazCrop,filmesEmCartazCropRes);
    finalResCine.resize(cinemas.size());
    for(int i=0, pos=0; i < filmesEmCartazCropRes.size(); i++){
        string aux = filmesEmCartazCropRes[i].cinema_ID;
        removeCharacter(aux,'c');
        pos = stoi(aux)-1;
        finalResCine[pos] = cinemas[pos];
        finalResCine[pos].movies.clear();
        finalResCine[pos].movies.push_back(filmesEmCartazCropRes[i].filme);
    }

    int x1=0,y1=0;
    vector<Cinema> dist_vet,price_vet;
     if(input.find("5") != input.npos){
        int max=0, tam=cinemas.size();
        cout << "\n\nQuais as suas coordenadas? ";
        cout << "\nx: ";
        cin >> x1;
        cout <<"\ny: ";
        cin >> y1;
        cout << "\ndistância máxima: ";
        cin >> max;
        for(int i=0; i<tam; i++){
            if(max >= distancia2pts(x1,y1,cinemas[i].cord_X,cinemas[i].cord_Y)){
                dist_vet.push_back(cinemas[i]);
            }
        }
        start_time = chrono::high_resolution_clock::now();
        if(ctVerify > 0)
            intersectionLinearCinemas(finalResCine,dist_vet,finalResCine);
        else
            intersectionLinearCinemas(dist_vet,dist_vet,finalResCine);
        ctVerify++;
        end_time = chrono::high_resolution_clock::now();
        elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
        cout << "Tempo para fazer interseção com cinemas: " << elapsed_time << "segundos\n";
    }

    if(input.find("6") != input.npos){
        int tam = cinemas.size();
        float val=0.0;
        string valS;
        cout << "\n\nQual o valor máximo de ingresso que você está disposto(a) a pagar?\n";
        cin >> valS;
        if(valS.find(",") != string::npos){
            valS.replace(valS.find(","),1,".");
        }
        val = stof(valS);
        for(int i=0; i<tam; i++){
            if(cinemas[i].price_ticket <= val){
                price_vet.push_back(cinemas[i]);
            }
        }
        start_time = chrono::high_resolution_clock::now();
        if(ctVerify > 0)
            intersectionLinearCinemas(finalResCine,price_vet,finalResCine);
        else
            intersectionLinearCinemas(price_vet,price_vet,finalResCine);
        end_time = chrono::high_resolution_clock::now();
        elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
        cout << "Tempo para fazer interseção com cinemas: " << elapsed_time << "segundos\n";
    }

    cout << "\n\n";
    for(auto x: finalResCine){
        if(x.cinema_ID != ""){
            cout << "\n\n" << x.cinema_ID << ": " << x.cinema_name << ", Valor do ingresso: " << x.price_ticket << ", Distância: " << distancia2pts(x1,y1,x.cord_X,x.cord_Y);
            cout << "\n\nFilmes: \n";
            for(auto v:x.movies){
                cout << v.tconst << ": ";
                if(hasMovies){
                    cout << v.originalTitle << ", Tipo de filme: " << v.titleType << ", Gênero: " << v.genres << ", Duração: " << v.duration << ", Ano de lançamento: " << v.startYear << "\n\n";
                }
            }
        }
    }
    dist_vet.clear();
    price_vet.clear();
    finalResCine.clear();
    filmesEmCartazCropRes.clear();
}

void menu(){
    // system("clear");
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

void menuMoreOneCine(){
    system("clear");
    cout << "********************************************\n\n";
    cout << "Mais algum? Qual?\n\n";
    cout << "0 - NÃO\n";
    cout << "1 - Tipo de filme\n2 - Gênero\n3 - Ano\n4 - Duração\n5 - Distância do cinema ao seu local\n6 - Valor de ingresso\n\n";
    cout << "********************************************\n\n";
}

void finalizar(){
    cout << "\n\n********************************************\n\n";
    cout << "Algo mais?\n\n";
    cout << "0 - SAIR\n1 - Outra consulta\n\n";
    cout << "********************************************\n\n";
}

void menuCinemas(){
    system("clear");
    cout << "********************************************\n\n";
    cout << "Quais filtros deseja utilizar?\n\n";
    cout << "1 - Tipo de filme\n2 - Gênero\n3 - Ano\n4 - Duração\n5 - Distância do cinema ao seu local\n6 - Valor de ingresso\n\n";
    cout << "********************************************\n\n";
}


int main() {
    auto start_time = chrono::high_resolution_clock::now();
    string fileName = "filmesCrop.txt"; // Change to your file name

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
     vector<Movie> tconsts;

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
        genres.push_back(movie);
        startYear.push_back(movie);
        TitleType.push_back(movie);
        runTime.push_back(movie);
    }
    content.clear();
    file.close();

    fileName = "cinemas.txt"; 
    ifstream file2(fileName);
    if (!file2.is_open()) {
        cerr << "Failed to open file: " << fileName << endl;
        return 1;
    }
    getline(file2,line);
    vector<Cinema> cinemas, resCine;
    vector<FilmesEmCartaz> emCartazCrop;
    while(getline(file2,line,',')){
        if(line[0] == ' ')
            line.erase(line.begin());
        if(line.find("\n") != string::npos){
            pair<string,string> aux = splitString(line);
            content.push_back(aux.first);
            content.push_back(aux.second);
        }else
            content.push_back(line);
    }
    file2.close();

    sort(TitleType.begin(), TitleType.end(),compareTitleType);
    sort(genres.begin(), genres.end(), compareGenres);
    sort(startYear.begin(), startYear.end(), compareStartYear);
    sort(runTime.begin(), runTime.end(), compareRunTime);
    Cinema cine;
    for(int i=0, l=0; i<content.size(); i++){
        if(l==0){
            cine.cinema_ID = content[i];
            l++;
        }else if(l==1){
            cine.cinema_name = content[i];
            l++;
        }else if(l==2){
            cine.cord_X = stoi(content[i]);
            l++;
        }else if(l==3){
            cine.cord_Y = stoi(content[i]);
            l++;
        }else if(l==4){
            cine.price_ticket = stof(content[i]);
            l++;
        }else if(l==5){
            l=0;
            while(content[i].find("tt") != content[i].npos){
                Movie m;
                FilmesEmCartaz a;
                string aux;
                m.tconst = content[i];
                cine.movies.push_back(m);
                aux = m.tconst;
                removeCharacter(aux,'t');
                if(stoi(aux)%2==0){
                    a.filme = m;
                    a.cinema_ID = cine.cinema_ID;
                    emCartazCrop.push_back(a);
                }
                i++;
            }
            cinemas.push_back(cine);
            resCine.push_back(cine);
            i--;
        }
    }
    content.clear();
    sort(emCartazCrop.begin(),emCartazCrop.end(),compareIdsMovieCartaz);

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
    vector<Cinema> finalResCine;
    vector<FilmesEmCartaz> cartazRes;
    resultado.push_back(resTitleType);
    resultado.push_back(resGenres);
    resultado.push_back(resStartYear);
    resultado.push_back(resRunTime);

    string input;

    auto end_time = chrono::high_resolution_clock::now();
    auto elapsed_time = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time).count() / 1e9;
    cout << "Tempo para carregar os dados: " << elapsed_time << " segundos\n";

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
            printResultMovies(finalRes,resultado,input);
            finalizar();
            cin >> input;
            if(input == "0")
                return 0;
            else
                continue;
        }else if(input == "2"){
            menuCinemas();
            cin >> input;
            for(;;){
                menuMoreOneCine();
                string addMore;
                cin >> addMore;
                if(addMore == "0")
                    break;
                if(input.find(addMore) == input.npos){
                    input.append(addMore);
                }
            }
            cineConsulter(movieParser,cinemas,resultado, resCine,input);
            printResultCines(movieParser,cinemas,finalResCine,finalRes,emCartazCrop,cartazRes,resultado,input);
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
