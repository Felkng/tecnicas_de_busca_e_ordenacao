#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <regex>
#include <iterator>

struct Movie {
    std::string tconst;
    std::string titleType;
    std::string primaryTitle;
    std::string originalTitle;
    bool isAdult;
    int startYear;
    int endYear;
    int duration;
    std::string genres;
};

// Function to index the table by a specific column
std::unordered_map<std::string, std::vector<Movie>> indexByColumn(const std::vector<Movie>& table, const std::string& columnName) {
    std::unordered_map<std::string, std::vector<Movie>> index;

    for (const Movie& movie : table) {
        if (columnName == "short") {
            index[movie.tconst].push_back(movie);
        }
        // Add more conditions for other columns as needed
    }

    return index;
}

// Function to perform a search based on an indexed column
std::vector<Movie> searchByColumn(const std::unordered_map<std::string, std::vector<Movie>>& index, const std::string& searchTerm) {
    auto it = index.find(searchTerm);
    if (it != index.end()) {
        return it->second;
    }
    return {}; // Return an empty vector if not found
}

int main() {
    std::vector<Movie> movieTable;
    std::string fileName = "teste2.txt"; // Change to your file name

    // Read data from the text file and populate the movieTable vector
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return 1;
    }

    std::string line;

    std::getline(file,line);
    int i = 1;
    while (std::getline(file, line)) {
        std::regex whiteSpace(" ");
        std::regex barraN("\\\\N");
        std::regex igualin("=");
        
        // write the results to an output iterator
        line = std::regex_replace(line, whiteSpace, "=");
        line = std::regex_replace(line, barraN, "-1");

        std::istringstream iss(line);

        Movie movie;
        if((iss >> movie.tconst >> movie.titleType >> movie.primaryTitle >> movie.originalTitle >> movie.isAdult >>  movie.startYear >> movie.endYear >> movie.duration >> movie.genres)){
            movie.primaryTitle = std::regex_replace(movie.primaryTitle, igualin, " ");
            movie.originalTitle = std::regex_replace(movie.originalTitle, igualin, " ");
            movieTable.push_back(movie);
        } else {
            std::cerr << "Failed to parse line: " << line << i << std::endl;

        }
    }

    file.close();

    std::string columnName = "short";
    std::string searchTerm = "Drama";

    // Index the table by the specified column
    std::unordered_map<std::string, std::vector<Movie>> index = indexByColumn(movieTable, columnName);

    // Perform a search using the index
    std::vector<Movie> searchResults = searchByColumn(index, searchTerm);
    
    // Print the search results
    for (const Movie& result : searchResults) {
        std::cout << result.tconst << " | " << result.titleType << " | " << result.primaryTitle << std::endl;
    }


    return 0;
}
