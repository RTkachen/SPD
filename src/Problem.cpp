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

void Problem::customHeuristic() {
    std::vector<int> N(n);
    std::iota(N.begin(), N.end(), 0);

    std::sort(N.begin(), N.end(), [&](int a, int b) {
        return instantion[a * 3] < instantion[b * 3];  // r rosnąco
    });

    bestPermutation.clear();

    while (!N.empty()) {
        int selectedIdx = 0;
        int r0 = instantion[N[0] * 3];
        int q0 = instantion[N[0] * 3 + 2];
        int maxImpact = q0;

        for (size_t i = 1; i < N.size(); ++i) {
            int ri = instantion[N[i] * 3];
            int qi = instantion[N[i] * 3 + 2];
            int impact = qi + (ri - r0);  // szacowany wpływ opóźnienia

            if (impact > maxImpact) {
                maxImpact = impact;
                selectedIdx = i;
            }
        }

        bestPermutation.push_back(N[selectedIdx]);
        N.erase(N.begin() + selectedIdx);
    }

    minCq = countCq(bestPermutation);
}


void Problem::schrage() {
    std::vector<int> N(n);  // indeksy zadań
    std::iota(N.begin(), N.end(), 0);  // [0, 1, 2, ..., n-1]

    // Sortowanie po r rosnąco
    std::sort(N.begin(), N.end(), [&](int a, int b) {
        return instantion[a * 3] < instantion[b * 3];  // r(a) < r(b)
    });

    // kolejka gotowych zadań, sortowana po największym q
    auto cmp_q = [&](int a, int b) {
        return instantion[a * 3 + 2] < instantion[b * 3 + 2];
    };
    std::priority_queue<int, std::vector<int>, decltype(cmp_q)> G(cmp_q);

    bestPermutation.clear();  // finalna kolejność wykonywania zadań

    int t = 0;      // aktualny czas
    size_t idx = 0; // wskaźnik na N

    while (!G.empty() || idx < N.size()) {
        while (idx < N.size() && instantion[N[idx] * 3] <= t) {
            G.push(N[idx]);
            ++idx;
        }

        if (G.empty()) {
            t = instantion[N[idx] * 3];  // przeskok do najbliższego r(i)
        } else {
            int e = G.top(); G.pop();
            bestPermutation.push_back(e);
            t += instantion[e * 3 + 1];  // dodaj p(i)
        }
    }

    minCq = countCq(bestPermutation);
}

void Problem::schragePmtn() {
    std::vector<int> N(n);
    std::iota(N.begin(), N.end(), 0);  // indeksy zadań

    std::sort(N.begin(), N.end(), [&](int a, int b) {
        return instantion[a * 3] < instantion[b * 3];  // r(a) < r(b)
    });

    auto cmp_q = [&](int a, int b) {
        return instantion[a * 3 + 2] < instantion[b * 3 + 2];
    };
    std::priority_queue<int, std::vector<int>, decltype(cmp_q)> G(cmp_q);

    int t = 0;
    int Cmax = 0;
    int l = -1;  // aktualnie wykonywane zadanie
    size_t idx = 0;

    bestPermutation.clear(); // <-- dodane

    while (!G.empty() || idx < N.size()) {
        while (idx < N.size() && instantion[N[idx] * 3] <= t) {
            int j = N[idx];

            G.push(j);
            if (l != -1 && instantion[j * 3 + 2] > instantion[l * 3 + 2]) {
                instantion[l * 3 + 1] = t - instantion[j * 3];  // skracamy p(l)
                t = instantion[j * 3];
                G.push(l);
            }

            ++idx;
        }

        if (G.empty()) {
            t = instantion[N[idx] * 3];
        } else {
            l = G.top(); G.pop();
            bestPermutation.push_back(l); // <-- dodane
            t += instantion[l * 3 + 1];
            Cmax = std::max(Cmax, t + instantion[l * 3 + 2]);
        }
    }

    minCq = Cmax;
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