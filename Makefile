# Definicja katalogu budowy i pliku wykonywalnego
BUILD_DIR = build
BIN_DIR = bin
EXECUTABLE = $(BIN_DIR)/rgcmax
#PLIK = $(word 2, $(MAKECMDGOALS))
# Znalezienie wszystkich plików źródłowych C++ w katalogu src/
SRC_FILES = $(wildcard src/*.cpp)

# Domyślny cel "all" - kompiluje projekt, jeśli plik wykonywalny nie istnieje lub kod źródłowy się zmienił
all: clean $(EXECUTABLE)

# Reguła budowania pliku wykonywalnego
$(EXECUTABLE): $(SRC_FILES) | $(BUILD_DIR)
# Budowanie projektu za pomocą CMake
	@cmake --build $(BUILD_DIR)

# Reguła tworzenia katalogu build/, jeśli nie istnieje
$(BUILD_DIR):
	@cmake -B $(BUILD_DIR) > /dev/null 2>&1

# Reguła do uruchomienia programu z folderu głównego SPD
run: $(EXECUTABLE)
# Uruchomienie programu z przekazanym argumentem (ignorując MAKECMDGOALS dla celów "run")
	@$(EXECUTABLE) $(word 2, $(MAKECMDGOALS))

# Reguła "clean" - usuwa pliki budowy i plik wykonywalny
clean:
# Usuwanie folderu build oraz pliku wykonywalnego
	rm -rf $(BUILD_DIR) $(EXECUTABLE)
