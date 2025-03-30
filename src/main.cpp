#include "Zadanie.hpp"
#include "Problem.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Użycie: " << argv[0] << " <ścieżka do pliku>" << std::endl;
        return 1;
    }

    // Ścieżka do pliku wejściowego z linii poleceń
    std::string filename = argv[1];

    // Tworzymy obiekt Zadanie i wczytujemy dane z pliku
    Zadanie zadanie(filename);

    // Tworzymy obiekt Problem z danymi z Zadania
    Problem problem(zadanie.getInstantion());

    // Przeglad zupelny
    problem.generatePermutations();
    // Wyswietlamy wynik
    problem.displayResults();

    problem.sortByQ();
    problem.displayResults();
    problem.sortByR();
    problem.displayResults();

    return 0;
}