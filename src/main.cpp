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
    zadanie.displayFile();
    // Tworzymy obiekt Problem z danymi z Zadania
    Problem problem(zadanie.getInstantion(), zadanie.getN());
    
    auto start = std::chrono::high_resolution_clock::now();
    // Przeglad zupelny
    problem.generatePermutations();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Czas wykonania: " << std::fixed << std::setprecision(3) << duration.count() << " s" << std::endl;

    // Wyswietlamy wynik
    problem.displayResults();

    //problem.sortByQ();
    //problem.displayResults();
    //problem.sortByR();
    //problem.displayResults();
    problem.schrage();
    problem.displayResults();
    problem.schragePmtn();
    problem.displayResults();
    problem.customHeuristic();
    problem.displayResults();
    return 0;
}