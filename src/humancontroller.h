#ifndef _WARGAME_HUMANCONTROLLER_H
#define _WARGAME_HUMANCONTROLLER_H

#include <vector>
#include "agl/drawer.h"
#include "agl/mouse.h"
#include "agl/keyboard.h"
#include "agl/intvector2.h"
#include "playercontroller.h"
#include "unit.h"
#include "support.h"

using namespace AGL;

/// HumanController class
class HumanController : public PlayerController
{
	private:	
		Drawer* drawer;
		Keyboard* keyboard;
		Mouse* mouse;
		
		// Control
		ushort selectedAction; // Ação selecionada (p.ex. alocar construção)  
		Command currentCommand;
		IntVector2* lastCommandPoint;

		IntVector2* rectangleCamera;
		IntVector2* rectangleInit;
		bool drawingRectangle;

		// TODO: undefined reference para o copy constructor do IntVector2 se não usar como ponteiro. Tentar usar como 
		// 		ponteiro, caso não dê, lembrar dos deletes para evitar mem. leaks.
		vector<IntVector2*> selectedPositions; 
		vector<Unit*> selectedObjects;

		void setSelectedPositions(int x, int y, int finalX, int finalY, WarMap* warmap);
		void selectArea(vector<Unit*> units);
		void drawRectangle(WarMap* warmap);

	public:
		
		/* TODO:
				Essa classe irá controlar a entrada do mouse e teclado, guardando o estado de teclas/mouse, se está fazendo
				retângulo de seleção, se terminou o retângulo de seleção, e o estado do retângulo de seleção.
				Também irá possibilitar consultas básicas como quais as unidades selecionadas, etc.
				A classe mãe, PlayerController, determina os comandos finais decididos (independente das entradas de teclado, 
				se houverem).
		 */
	
		HumanController(Drawer* drawer, Game* game, Keyboard* keyboard, Mouse* mouse, Options* opt);
		void update(WarMap* warmap, vector<Unit*> units);
		void draw(WarMap* warmap);
		Command getCommand();
};

#endif

