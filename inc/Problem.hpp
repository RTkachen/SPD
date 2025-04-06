#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>
#include <iostream>
#include <algorithm>  // do next_permutation
#include <limits>     // dla std::numeric_limits
#include <bits/stdc++.h>
class Problem {
private:
    int minCq;  // Minimalne Cq
    int n;
    std::vector<int> bestPermutation;  // Najlepsza permutacja
    std::vector<int> instantion;  // Wektor danych 
    int countC(const std::vector<int>& perm);  // Funkcja do liczenia C
    int countCq(const std::vector<int>& perm);  // Funkcja do liczenia Cq
    void initializePermutation();
public:
Problem(const std::vector<int> inst, const int& n) : instantion(std::move(inst)), n(n) {}
    void sortByQ();
    void sortByR();
    void schrage();
    void schragePmtn();
    void customHeuristic();
    // Funkcja do generowania wszystkich permutacji
    void generatePermutations();
    void displayResults();
};

#endif // PROBLEM_H