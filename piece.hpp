#pragma once
#include <string>
#include <exception>

namespace modele {

	enum class TypePiece {
		Roi, Reine, Tour, Fou, Cavalier, Pion
	};

	class TropDeRois : public std::exception {
	public :
		const char* what() const noexcept override {
			return "Erreur : Impossible de creer plus de deux rois";
		}
};


	enum class Couleur {BLANC, NOIR};


	class Piece {
	protected:
		Couleur couleur;
		int x, y;
	public:
		Piece(Couleur couleur, int x, int y);
		virtual ~Piece() = default;
		virtual std::string getNom() const = 0;
		virtual bool estMouvementValide(int nouveauX, int nouveauY) const = 0;
		void deplacer(int nouveauX, int nouveauY);
		Couleur getCouleur() const { return couleur;  }
		std::pair<int, int> getPosition() const { return { x, y }; }
	};


	class Roi :public Piece {
	public:
		Roi(Couleur couleur, int x, int y);
		~Roi() override;
		std::string getNom() const override { return "Roi"; }
		bool estMouvementValide(int nouveauX, int nouveauY) const override;
	private:
		static int compteur;
	};

	class Tour : public Piece {
	public:
		Tour(Couleur couleur, int x, int y);
		bool estMouvementValide(int nouveauX, int nouveauY) const override;
		std::string getNom() const override { return "Tour"; }
	};

	class Cavalier : public Piece {
	public:
		Cavalier(Couleur couleur, int x, int y);
		bool estMouvementValide(int nouveauX, int nouveauY) const override;
		std::string getNom() const override { return "Cavalier"; }
	};

	class Reine :public Piece {
	public:
		Reine(Couleur couleur, int x, int y);
		bool estMouvementValide(int nouveauX, int nouveauY) const override;
		std::string getNom() const override { return "Reine"; }
	};

	class Fou : public Piece {
	public:
		Fou(Couleur couleur, int x, int y);
		bool estMouvementValide(int nouveauX, int nouveauY) const override;
		std::string getNom() const override { return "Fou"; }
	};

	class Pion : public Piece {
	public:
		Pion(Couleur couleur, int x, int y);
		bool estMouvementValide(int nouveauX, int nouveauY) const override;
		std::string getNom() const override { return "Pion"; }
	};
}