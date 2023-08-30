#pragma once

#include "dispositif.h"

namespace PM3D
{
	//
	// Classe CDispositifD3D11
	//
	// BUT : Classe permettant d'implanter un dispositif de rendu 
	// Direct3D
	//
	class CDispositifD3D11 : public CDispositif
	{

	public:
		CDispositifD3D11(const CDS_MODE cdsMode, const HWND hWnd);
		virtual ~CDispositifD3D11();

	};
}