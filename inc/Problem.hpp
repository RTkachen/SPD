#ifndef PROBLEM_H
#define PROBLEM_H

#include "Zadanie.hpp"
#include <vector>
#include <iostream>
#include <algorithm>  // do next_permutation
#include <limits>     // dla std::numeric_limits
class Problem {
private:
    int minCq;  // Minimalne Cq
    std::vector<int> bestPermutation;  // Najlepsza permutacja
    std::vector<int> instantion;  // Wektor danych 
    void nextPermutation(std::vector<int>& perm);  // Funkcja do generowania permutacji
    int countC(const std::vector<int>& perm);  // Funkcja do liczenia C
    int countCq(const std::vector<int>& perm);  // Funkcja do liczenia Cq
public:
    Problem(const std::vector<int>& inst) : instantion(inst) {}
    void sortByQ();
    void sortByR();
    // Funkcja do generowania wszystkich permutacji
    void generatePermutations();
    void displayResults();
};

#endif // PROBLEM_H