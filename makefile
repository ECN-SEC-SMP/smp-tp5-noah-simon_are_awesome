# === Variables ===
EXEC_PROGRAM1 = folder_build
EXEC_PROGRAM2 = main

# === Règles ===

all: $(EXEC_PROGRAM1) $(EXEC_PROGRAM2)  
 
# Compilation de l'exécutable

$(EXEC_PROGRAM1): 
	mkdir -p build

$(EXEC_PROGRAM2): ./build/main.o ./build/utilitaire.o  ./build/utilitaire_fichier.o
	g++ -o $(EXEC_PROGRAM2) ./build/main.o ./build/utilitaire.o  ./build/utilitaire_fichier.o


# Compilation des fichiers sources en fichiers objets
./build/main.o: ./main.cpp
	g++ -I./include -c ./main.cpp -o ./build/main.o

./build/utilitaire.o: ./src/utilitaire.cpp
	g++ -I./include -c ./src/utilitaire.cpp -o ./build/utilitaire.o

./build/utilitaire_fichier.o: ./src/utilitaire_fichier.cpp
	g++ -I./include -c ./src/utilitaire_fichier.cpp -o ./build/utilitaire_fichier.o


# Supprime les fichiers objets et l'exécutable
clean:
	rm -f build/*.o
	rm -f $(EXEC_PROGRAM1) $(EXEC_PROGRAM2)

.PHONY: all cleanZ

