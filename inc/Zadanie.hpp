#ifndef ZADANIE_HPP
#define ZADANIE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Zadanie {
private:
    int n;  // Numer operacji
    std::vector<int> instantion;  // Wektor do przechowywania danych instancji
    // Funkcja do wczytywania danych z pliku
    void readFromFile(const std::string& filename);

public:
    // Konstruktor, który inicjalizuje dane oraz wywołuje funkcję do wczytywania danych
    Zadanie(const std::string& filename);

    // Funkcja do zwrócenia wczytanych danych
    const std::vector<int>& getInstantion() const;
    void displayFile();
    // Funkcje dostępowe (gettery)
    int getN() const;
};

#endif // ZADANIE_HPP