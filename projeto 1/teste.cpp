#include <iostream>
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


// Function to index the table by a specific column
// unordered_map<string, vector<Movie>> indexByColumn(const vector<Movie>& table, const string& columnName) {
//     unordered_map<string, vector<Movie>> index;

//     for (const Movie& movie : table) {
//         if (columnName == "short") {
//             index[movie.tconst].push_back(movie);
//         }
//         // Add more conditions for other columns as needed
//     }

//     return index;
// }

// Function to perform a search based on an indexed column
// vector<Movie> searchByColumn(const unordered_map<string, vector<Movie>>& index, const string& searchTerm) {
//     auto it = index.find(searchTerm);
//     if (it != index.end()) {
//         return it->second;
//     }
//     return {}; // Return an empty vector if not found
// }

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
    file.close();
    for(int i=0;i<content.size();i++){
        cout << i << ": " << content[i] << endl;
        // if(i%9==0){
        //     movie.tconst = content[i];
        //     movieTable.push_back(movie);
        // }
    }
    // for(auto x: movieTable){
    //     cout << x.tconst << endl;
    // }
    // cout << movieTable.size() << endl;
    // cout << ct << endl;
    // cout << "OK";

    // string columnName = "short";
    // string searchTerm = "Drama";

    // // Index the table by the specified column
    // unordered_map<string, vector<Movie>> index = indexByColumn(movieTable, columnName);

    // // Perform a search using the index
    // vector<Movie> searchResults = searchByColumn(index, searchTerm);
    
    // // Print the search results
    // for (const Movie& result : searchResults) {
    //     cout << result.tconst << " | " << result.titleType << " | " << result.primaryTitle << endl;
    // }


    return 0;
}
