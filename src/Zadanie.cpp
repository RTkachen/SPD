#include "Zadanie.hpp"


// Funkcja do wczytywania danych z pliku
void Zadanie::readFromFile(const std::string& filename) {
    std::ifstream file(filename);  
    if (!file) {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
        return;
    }

    int r, p, q;
    file >> n;  // Pierwsza linia - liczba zadań

    while (file >> r >> p >> q) {  // Poprawiona kolejność
        instantion.push_back(r);
        instantion.push_back(p);
        instantion.push_back(q);
    }

    file.close();
}

// Konstruktor, który inicjalizuje dane oraz wywołuje funkcję do wczytywania danych
Zadanie::Zadanie(const std::string& filename) {
    readFromFile(filename);  // Wczytanie danych z pliku
}

// Funkcja do zwrócenia wczytanych danych
const std::vector<int>& Zadanie::getInstantion() const {
    return instantion;
}

void Zadanie::displayFile(){

    std::cout << "Wczytane wartości (r, p, q):\n";
    for (size_t i = 0; i < instantion.size(); i += 3) {
        std::cout << "r: " << instantion[i] 
                  << ", p: " << instantion[i + 1] 
                  << ", q: " << instantion[i + 2] << std::endl;
    }
}

// Funkcje dostępowe (gettery)
int Zadanie::getN() const { return n; }