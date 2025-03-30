#include "Problem.hpp"


// Funkcja do generowania permutacji
void Problem::generatePermutations() {
  size_t n = instantion.size() / 4;  // Liczba operacji
  std::vector<int> perm;

  // Tworzymy początkową permutację
  for (size_t i = 0; i < n; ++i) {
      perm.push_back(i);  // Wstawiamy indeksy
  }

  // Zmienna do przechowywania minimalnej wartości Cq
  minCq = std::numeric_limits<int>::max();
  bestPermutation.clear();  // Czyszczenie poprzedniej najlepszej permutacji

  do {
      // Obliczamy Cq dla bieżącej permutacji
      int cq_val = countCq(perm);

      // Jeśli Cq jest mniejsze niż dotychczasowe minimum, zapisujemy nowe minimum
      if (cq_val < minCq) {
          minCq = cq_val;
          bestPermutation = perm;  // Przechowujemy permutację z najmniejszym Cq
      }

  } while (std::next_permutation(perm.begin(), perm.end()));  // Generujemy kolejną permutację
}

void Problem::sortByR() {
    size_t n = instantion.size() / 4;
    bestPermutation.resize(n);

    // Wypełnienie indeksami
    for (size_t i = 0; i < n; ++i) {
        bestPermutation[i] = i;
    }

    // Sortowanie według r rosnąco
    std::sort(bestPermutation.begin(), bestPermutation.end(), [&](int a, int b) {
        return instantion[a * 4 + 2] < instantion[b * 4 + 2];
    });

    // Obliczenie wartości C i Cq dla posortowanej kolejności
    minCq = countCq(bestPermutation);
}


void Problem::sortByQ() {
    size_t n = instantion.size() / 4;
    bestPermutation.resize(n);

    // Wypełnienie indeksami
    for (size_t i = 0; i < n; ++i) {
        bestPermutation[i] = i;
    }

    // Sortowanie według q malejąco
    std::sort(bestPermutation.begin(), bestPermutation.end(), [&](int a, int b) {
        return instantion[a * 4 + 3] > instantion[b * 4 + 3];
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

// Funkcja do liczenia C
int Problem::countC(const std::vector<int>& perm) {
  size_t n = perm.size();
  std::vector<int> C(n);  // Wektor C

  // Liczymy C na podstawie wzoru
  for (size_t i = 0; i < n; ++i) {
      int idx = perm[i];
      int p_val = instantion[idx * 4 + 1];
      int r_val = instantion[idx * 4 + 2];

      if (i == 0) {
          C[i] = r_val + p_val;  // Dla pierwszej operacji
      } else {
          int prev_C = C[i - 1];
          C[i] = std::max(prev_C, r_val) + p_val;  // Dla kolejnych operacji
      }
  }

  // Zwracamy ostatnią wartość C, ponieważ zależy od wszystkich poprzednich
  return C.back();
}

// Funkcja do liczenia Cq
int Problem::countCq(const std::vector<int>& perm) {
  size_t n = perm.size();
  std::vector<int> C(n);  // Wektor do przechowywania wartości C dla operacji

  // Liczymy C na podstawie wzoru
  for (size_t i = 0; i < n; ++i) {
      int idx = perm[i];
      int p_val = instantion[idx * 4 + 1];
      int r_val = instantion[idx * 4 + 2];

      if (i == 0) {
          C[i] = r_val + p_val;  // Dla pierwszej operacji
      } else {
          int prev_C = C[i - 1];
          C[i] = std::max(prev_C, r_val) + p_val;  // Dla kolejnych operacji
      }
  }

  // Teraz obliczamy Cq jako maksymalną wartość C(i) + q(i) dla każdej operacji
  int Cq = std::numeric_limits<int>::min();
  for (size_t i = 0; i < n; ++i) {
      int idx = perm[i];
      int q_val = instantion[idx * 4 + 3];
      Cq = std::max(Cq, C[i] + q_val);  // Maksymalna wartość C(i) + q(i)
  }

  return Cq;
}