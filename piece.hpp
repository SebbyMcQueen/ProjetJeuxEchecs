#pragma once
#include <string>
#include <exception>

namespace modele {

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
}