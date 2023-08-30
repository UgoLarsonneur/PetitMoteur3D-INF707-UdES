#pragma once
#include "Singleton.h"

namespace PM3D
{
const int IMAGESPARSECONDE = 60;
const double EcartTemps = 1.0 / static_cast<double>(IMAGESPARSECONDE);


//
//   TEMPLATE�: CMoteur
//
//   BUT�: Template servant � construire un objet Moteur qui implantera les
//         aspects "g�n�riques" du moteur de jeu
//
//   COMMENTAIRES�:
//
//        Comme plusieurs de nos objets repr�senteront des �l�ments uniques 
//        du syst�me (ex: le moteur lui-m�me, le lien vers 
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
			// Propre � la plateforme - (Conditions d'arr�t, interface, messages)
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
		// Propre � la plateforme
		InitialisationsSpecific();

		// * Initialisation du dispositif de rendu

		// * Initialisation de la sc�ne

		// * Initialisation des param�tres de l'animation et 
		//   pr�paration de la premi�re image
		//InitAnimation();

		return 0;
	}

	//
	// FONCTION : Animation 
	//
	// BUT : Fonction responsable de l�animation g�n�rale 
	// de la sc�ne
	//
	// NOTES :
	// D�autres animations (autres que 3D) pourront aussi 
	// �tre appel�es ici
	//
	// L�animation est optimis�e pour les syst�mes moins rapides
	// c.-�-d. qu�elle effectue la pr�sentation d�s le d�but puis 
	// Construis la prochaine image.
	//
	virtual bool Animation()
	{
		// m�thode pour lire l�heure et calculer le temps �coul�
		const int64_t TempsCompteurCourant = GetTimeSpecific();
		const double TempsEcoule =
			GetTimeIntervalsInSec(mTempsCompteurPrecedent, TempsCompteurCourant);
		// Est-il temps de rendre l�image ?
		if (TempsEcoule > EcartTemps)
		{
			// Affichage optimis� 
			// pDispositif->Present() ; // On enlevera � // � plus tard
			// On pr�pare la prochaine image
			// AnimeScene(TempsEcoule) ;
			// On rend l�image sur la surface de travail
			// (tampon d�arri�re plan)
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

		//premi�re img
		RenderScene();

		return true;
	}


	// Fonctions sp�cifiques au rendu et � la pr�sentation de la sc�ne
	virtual bool RenderScene()
	{
		return true;
	}


	// Sp�cifiques - Doivent �tre implant�s
	virtual int64_t GetTimeSpecific() const = 0;
	virtual double GetTimeIntervalsInSec(int64_t start, int64_t stop) const = 0;

	virtual bool RunSpecific() = 0;
	virtual int InitialisationsSpecific() = 0;
};

} // namespace PM3D
