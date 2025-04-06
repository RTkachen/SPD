#include "Problem.hpp"

// Funkcja do generowania permutacji
void Problem::generatePermutations() {
    if (n == 0) return;  // Jeśli n == 0, nie ma permutacji do generowania

    std::vector<int> perm(n);  
    std::iota(perm.begin(), perm.end(), 0);  // Tworzymy wektor {0, 1, 2, ..., n-1}

    minCq = std::numeric_limits<int>::max();

    do {
        int cq_val = countCq(perm);

        if (cq_val < minCq) {
            minCq = cq_val;
            bestPermutation = perm;
        }

    } while (std::next_permutation(perm.begin(), perm.end()));
}

void Problem::initializePermutation() {
    bestPermutation.resize(n);
    std::iota(bestPermutation.begin(), bestPermutation.end(), 0);
}

void Problem::sortByR() {
    initializePermutation();

    // Sortowanie według r rosnąco
    std::sort(bestPermutation.begin(), bestPermutation.end(), [&](int a, int b) {
        return instantion[a * 3] < instantion[b * 3];  // r(a) < r(b)
    });

    // Obliczenie wartości C i Cq dla posortowanej kolejności
    minCq = countCq(bestPermutation);
}

void Problem::sortByQ() {
    initializePermutation();

    // Sortowanie według q malejąco
    std::sort(bestPermutation.begin(), bestPermutation.end(), [&](int a, int b) {
        return instantion[a * 3 + 2] > instantion[b * 3 + 2];  // q(a) > q(b)
    });

    // Obliczenie wartości C i Cq dla posortowanej kolejności
    minCq = countCq(bestPermutation);
}


// Funkcja do wyświetlania wyników
void Problem::displayResults() {
  std::cout << "Najmniejsze Cq: " << minCq << std::endl;
  std::cout << "Permutacja dla najmniejszego Cq: ";
  for (auto idx : bestPermutation) {
      std::cout << idx+1 << " ";
  }
  std::cout << std::endl;
}


int Problem::countCq(const std::vector<int>& perm) {
    std::vector<int> C(n);  // Wektor przechowujący wartości C dla operacji

    // Liczymy C na podstawie wzoru
    for (size_t i = 0; i < n; ++i) {
        int idx = perm[i];  // Pobieramy indeks z permutacji
        int r_val = instantion[idx * 3];       // r(i)
        int p_val = instantion[idx * 3 + 1];   // p(i)

        if (i == 0) {
            C[i] = r_val + p_val;  // Dla pierwszej operacji
        } else {
            int prev_C = C[i - 1];
            C[i] = std::max(prev_C, r_val) + p_val;  // Dla kolejnych operacji
        }
    }

    // Obliczamy Cq jako maksymalne C(i) + q(i)
    int Cq = 0;
    for (size_t i = 0; i < n; ++i) {
        int idx = perm[i];
        int q_val = instantion[idx * 3 + 2];  // q(i)
        Cq = std::max(Cq, C[i] + q_val);  
    }

    return Cq;
}