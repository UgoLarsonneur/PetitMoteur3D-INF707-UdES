#pragma once
#include "Singleton.h"

namespace PM3D
{
const int IMAGESPARSECONDE = 60;
const double EcartTemps = 1.0 / static_cast<double>(IMAGESPARSECONDE);


//
//   TEMPLATE : CMoteur
//
//   BUT : Template servant à construire un objet Moteur qui implantera les
//         aspects "génériques" du moteur de jeu
//
//   COMMENTAIRES :
//
//        Comme plusieurs de nos objets représenteront des éléments uniques 
//        du système (ex: le moteur lui-même, le lien vers 
//        le dispositif Direct3D), l'utilisation d'un singleton 
//        nous simplifiera plusieurs aspects.
//
template <class T> class CMoteur :public CSingleton<T>
{
public:
	virtual void Run()
	{
		bool bBoucle = true;

		while (bBoucle)
		{
			// Propre à la plateforme - (Conditions d'arrêt, interface, messages)
			bBoucle = RunSpecific();

			// appeler la fonction d'animation
			if (bBoucle)
			{
				bBoucle = Animation();
			}
		}
	}

	virtual int Initialisations()
	{
		// Propre à la plateforme
		InitialisationsSpecific();

		// * Initialisation du dispositif de rendu

		// * Initialisation de la scène

		// * Initialisation des paramètres de l'animation et 
		//   préparation de la première image
		//InitAnimation();

		return 0;
	}

	//
	// FONCTION : Animation 
	//
	// BUT : Fonction responsable de l’animation générale 
	// de la scène
	//
	// NOTES :
	// D’autres animations (autres que 3D) pourront aussi 
	// être appelées ici
	//
	// L’animation est optimisée pour les systèmes moins rapides
	// c.-à-d. qu’elle effectue la présentation dès le début puis 
	// Construis la prochaine image.
	//
	virtual bool Animation()
	{
		// méthode pour lire l’heure et calculer le temps écoulé
		const int64_t TempsCompteurCourant = GetTimeSpecific();
		const double TempsEcoule =
			GetTimeIntervalsInSec(mTempsCompteurPrecedent, TempsCompteurCourant);
		// Est-il temps de rendre l’image ?
		if (TempsEcoule > EcartTemps)
		{
			// Affichage optimisé 
			// pDispositif->Present() ; // On enlevera « // » plus tard
			// On prépare la prochaine image
			// AnimeScene(TempsEcoule) ;
			// On rend l’image sur la surface de travail
			// (tampon d’arrière plan)
			RenderScene();
			// Calcul du temps du prochain affichage
			mTempsCompteurPrecedent = TempsCompteurCourant;
		}
		return true;
	}

protected:

	//Variable pour anim
	int64_t mTempsSuivant;
	int64_t mTempsCompteurPrecedent;

	virtual ~CMoteur() = default;

	virtual int InitAnimation()
	{
		mTempsSuivant = GetTimeSpecific();
		mTempsCompteurPrecedent = GetTimeSpecific();

		//première img
		RenderScene();

		return true;
	}


	// Fonctions spécifiques au rendu et à la présentation de la scène
	virtual bool RenderScene()
	{
		return true;
	}


	// Spécifiques - Doivent être implantés
	virtual int64_t GetTimeSpecific() const = 0;
	virtual double GetTimeIntervalsInSec(int64_t start, int64_t stop) const = 0;

	virtual bool RunSpecific() = 0;
	virtual int InitialisationsSpecific() = 0;
};

} // namespace PM3D
