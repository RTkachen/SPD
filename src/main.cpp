#include "Zadanie.hpp"
#include "Problem.hpp"

// Funkcja pomocnicza do mierzenia czasu działania
void measureExecutionTime(const std::string& label, const std::function<void()>& func) {
    auto start = std::chrono::high_resolution_clock::now();
    
    func(); // Wykonanie przekazanej funkcji

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    
    std::cout << "Czas wykonania (" << label << "): "
              << std::fixed << std::setprecision(7) << duration.count() << " s" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Użycie: " << argv[0] << " <ścieżka do pliku>" << std::endl;
        return 1;
    }

    // Ścieżka do pliku wejściowego z linii poleceń
    std::string filename = argv[1];

    // Tworzymy obiekt Zadanie i wczytujemy dane z pliku
    Zadanie zadanie(filename);
    //zadanie.displayFile();
    // Tworzymy obiekt Problem z danymi z Zadania
    std::cout<<zadanie.getN()<<std::endl;
    Problem problem(zadanie.getInstantion(), zadanie.getN());
    
    measureExecutionTime("Przegląd zupełny", [&]() {
        problem.generatePermutations();
    });
    problem.displayResults();

    measureExecutionTime("Sortowanie po q", [&]() {
        problem.sortByQ();
    });
    problem.displayResults();

    measureExecutionTime("Sortowanie po r", [&]() {
        problem.sortByR();
    });
    problem.displayResults();

    measureExecutionTime("Schrage", [&]() {
        problem.schrage();
    });
    problem.displayResults();

    measureExecutionTime("Schrage z wywłaszczeniem", [&]() {
        problem.schragePmtn();
    });
    problem.displayResults();

    measureExecutionTime("Własna heurystyka", [&]() {
        problem.customHeuristic();
    });
    problem.displayResults();

    return 0;

    return 0;
}