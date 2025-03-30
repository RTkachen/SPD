#include "Zadanie.hpp"


// Funkcja do wczytywania danych z pliku
void Zadanie::readFromFile(const std::string& filename) {
    std::ifstream file(filename);  // Otwarcie pliku do odczytu
    if (!file) {
        std::cerr << "Nie można otworzyć pliku!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);  // Tworzymy strumień do analizy linii
        int j, p, r, q;
        if (ss >> j >> p >> r >> q) {
            // Przechowywanie danych w wektorze instantion
            instantion.push_back(j);
            instantion.push_back(p);
            instantion.push_back(r);
            instantion.push_back(q);
        } else {
            std::cerr << "Błąd podczas czytania linii: " << line << std::endl;
        }
    }

    file.close();  // Zamknięcie pliku
}

// Konstruktor, który inicjalizuje dane oraz wywołuje funkcję do wczytywania danych
Zadanie::Zadanie(const std::string& filename) {
    readFromFile(filename);  // Wczytanie danych z pliku
}

// Funkcja do zwrócenia wczytanych danych
const std::vector<int>& Zadanie::getInstantion() const {
    return instantion;
}

// Funkcje dostępowe (gettery)
int Zadanie::getN() const { return n; }
int Zadanie::getP() const { return p; }
int Zadanie::getR() const { return r; }
int Zadanie::getQ() const { return q; }