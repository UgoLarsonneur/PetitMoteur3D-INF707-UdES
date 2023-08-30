#pragma once

#include "moteur.h"
#include "Horloge.h"

namespace PM3D
{
#define MAX_LOADSTRING 100

class CMoteurWindows final : public CMoteur<CMoteurWindows>
{
public:
	void SetWindowsAppInstance(HINSTANCE hInstance);

private:
	bool InitAppInstance();
	ATOM MyRegisterClass(HINSTANCE hInstance);
	int Show();

	// Les fonctions spécifiques
	virtual int64_t GetTimeSpecific() const override;
	virtual double GetTimeIntervalsInSec(int64_t start, int64_t stop) const override;
	virtual int InitialisationsSpecific() override;
	virtual bool RunSpecific() override;

	// Fonctions "Callback" -- Doivent être statiques
	static LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

	HACCEL hAccelTable;						// handle Windows de la table des accélérateurs
	static HINSTANCE hAppInstance;			// handle Windows de l'instance actuelle de l'application
	HWND hMainWnd;							// handle Windows de la fenêtre principale
	TCHAR szWindowClass[MAX_LOADSTRING];	// le nom de la classe de fenêtre principale

	Horloge m_Horloge;
};

} // namespace PM3D
