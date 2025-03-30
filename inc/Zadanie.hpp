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
    int p;  // Czas wykonywania operacji
    int r;  // Czas dostępności operacji
    int q;  // Czas stygnięcia operacji
    std::vector<int> instantion;  // Wektor do przechowywania danych instancji

    // Funkcja do wczytywania danych z pliku
    void readFromFile(const std::string& filename);

public:
    // Konstruktor, który inicjalizuje dane oraz wywołuje funkcję do wczytywania danych
    Zadanie(const std::string& filename);

    // Funkcja do zwrócenia wczytanych danych
    const std::vector<int>& getInstantion() const;

    // Funkcje dostępowe (gettery)
    int getN() const;
    int getP() const;
    int getR() const;
    int getQ() const;
};

#endif // ZADANIE_HPP