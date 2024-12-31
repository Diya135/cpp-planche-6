#include <iostream>
#include <cmath>
#include <vector>
#include <string>
//Exercice 1:
class Vecteur {
private:
    double x, y;

public:
    Vecteur() : x(0), y(0) {}
    Vecteur(double x, double y) : x(x), y(y) {}

    void afficher() const {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
    }

    void deplacer(double dx, double dy) {
        x += dx;
        y += dy;
    }
};

class Vecteur3D : public Vecteur {
private:
    double z;

public:
    Vecteur3D(double x, double y, double z) : Vecteur(x, y), z(z) {}

    void afficher() const {
        Vecteur::afficher();
        std::cout << "z: " << z << std::endl;
    }
};

int main() {
    Vecteur v1; // Vecteur nul
    v1.afficher();
    v1.deplacer(2.5, 6);
    v1.afficher();

    Vecteur3D* v3D = new Vecteur3D(1.0, 2.0, 3.0);
    v3D->afficher();
    delete v3D;

    return 0;
}
//exercice 2:
class Robot {
protected:
    std::string nom;
    double x, y;
    double portee;
    bool estMort;

public:
    Robot(std::string nom, double x, double y, double portee)
        : nom(nom), x(x), y(y), portee(portee), estMort(false) {}

    void deplacer(double v, double w) {
        x += v;
        y += w;
    }

    void afficher() const {
        std::cout << "Nom: " << nom << ", Position: (" << x << ", " << y << "), Est mort: " << estMort << std::endl;
    }

    bool estDansPortee(const Robot& autre) const {
        double distance = std::sqrt(std::pow(x - autre.x, 2) + std::pow(y - autre.y, 2));
        return distance < portee;
    }

    void tuer(Robot& autre) {
        if (estDansPortee(autre) && !autre.estMort) {
            autre.estMort = true;
            std::cout << nom << " a tué " << autre.nom << std::endl;
        }
    }
};

class RobotChasseur : public Robot {
public:
    RobotChasseur(std::string nom, double x, double y, double portee)
        : Robot(nom, x, y, portee) {}
};

int main() {
    RobotChasseur optimus("Optimus", 2, 3, 25);
    optimus.deplacer(33, 19);
    optimus.afficher();

    std::vector<Robot> robots = {
        Robot("Robot1", 10, 10, 15),
        Robot("Robot2", 20, 20, 15),
        Robot("Robot3", 30, 30, 15),
        Robot("Robot4", 40, 40, 15),
        Robot("Robot5", 50, 50, 15)
    };

    for (auto& robot : robots) {
        optimus.tuer(robot);
    }

    return 0;
}
//Exercice 3:
class Vehicule {
protected:
    static int numeroSerie;
    int numeroVehicule;
    int annee;
    double prix;

public:
    Vehicule(int annee, double prix) : annee(annee), prix(prix) {
        numeroVehicule = ++numeroSerie;
        if (numeroVehicule > 10000) {
            numeroVehicule = 1;
            numeroSerie++;
        }
    }

    virtual void accelerer() = 0;

    void afficher() const {
        std::cout << "Numéro de série: " << numeroSerie << ", Année: " << annee << ", Prix: " << prix << std::endl;
    }
};

int Vehicule::numeroSerie = 0;

class Voiture : public Vehicule {
private:
    int nombrePlaces;

public:
    Voiture(int annee, double prix, int places) : Vehicule(annee , prix), nombrePlaces(places) {}

    void accelerer() override {
        std::cout << "Je peux atteindre 200 km/h" << std::endl;
    }
};

class Camion : public Vehicule {
private:
    double chargeMaximale;

public:
    Camion(int annee, double prix, double charge) : Vehicule(annee, prix), chargeMaximale(charge) {}

    void accelerer() override {
        std::cout << "Je peux atteindre 120 km/h" << std::endl;
    }
};

int main() {
    Voiture v1(2020, 20000, 5);
    v1.afficher();
    v1.accelerer();

    Camion c1(2019, 30000, 1000);
    c1.afficher();
    c1.accelerer();

    return 0;
}
//Exercice 4:
class Piece {
protected:
    std::string couleur;
    int x, y;

public:
    Piece(std::string couleur, int x, int y) : couleur(couleur), x(x), y(y) {}

    virtual void afficher() const = 0;
};

class Pion : public Piece {
public:
    Pion(std::string couleur, int x, int y) : Piece(couleur, x, y) {}

    void afficher() const override {
        std::cout << "Pion " << couleur << " à la position (" << x << ", " << y << ")" << std::endl;
    }

    void deplacer() {
        y += 1;
        if (y > 8) {
            std::cout << "Le pion a dépassé la limite de l'échiquier." << std::endl;
        }
    }
};

class Roi : public Piece {
public:
    Roi(std::string couleur, int x, int y) : Piece(couleur, x, y) {}

    void afficher() const override {
        std::cout << "Roi " << couleur << " à la position (" << x << ", " << y << ")" << std::endl;
    }
};

int main() {
    std::vector<Piece*> pieces;
    pieces.push_back(new Pion("Blanc", 4, 2));
    pieces.push_back(new Roi("Noir", 5, 5));

    for (auto piece : pieces) {
        piece->afficher();
    }

    // Nettoyage de la mémoire
    for (auto piece : pieces) {
        delete piece;
    }

    return 0;
}
//Exercice 5
class Personne {
protected:
    std::string nom;
    int age;
    char sexe;

public:
    Personne(std::string nom, int age, char sexe) : nom(nom), age(age), sexe(sexe) {}

    virtual std::string getPersonne() const {
        return "Nom: " + nom + ", Age: " + std::to_string(age) + ", Sexe: " + sexe;
    }
};

class Enseignant : public Personne {
private:
    std::string charge;

public:
    Enseignant(std::string nom, int age, char sexe, std::string charge)
        : Personne(nom, age, sexe), charge(charge) {}

    std::string getPersonne() const override {
        return Personne::getPersonne() + ", Charge: " + charge;
    }
};

class Etudiant : public Personne {
private:
    std::string filiere;

public:
    Etudiant(std::string nom, int age, char sexe, std::string filiere)
        : Personne(nom, age, sexe), filiere(filiere) {}

    std::string getPersonne() const override {
        return Personne::getPersonne() + ", Filière: " + filiere;
    }
};

class Contractuel : public Enseignant, public Etudiant {
public:
    Contractuel(std::string nom, int age, char sexe, std::string charge, std::string filiere)
        : Personne(nom, age, sexe), Enseignant(nom, age, sexe, charge), Etudiant(nom, age, sexe, filiere) {}

    std::string getPersonne() const override {
        return Enseignant::getPersonne() + ", Filière: " + Etudiant::getPersonne();
    }
};

int main() {
    Enseignant e("Alice", 40, 'F', "Mathématiques");
    Etudiant et("Bob", 20, 'M', "Informatique");
    Contractuel c("Charlie", 30, 'M', "Physique", "Informatique");

    std::cout << e.getPersonne() << std::endl;
    std::cout << et.getPersonne() << std::endl;
    std::cout << c.getPersonne() << std::endl;

    return 0;
}