#pragma once
#include "Weapon.h"
#include "GOBox.h"
#include "definition.h"

enum RANGED_TYPES{
	GUN = 0,
	LASER = 1,
	ROCKET = 2,
};
class RangedWeapon:public Weapon
{
private:
	double _pInitForce;
	double _pMass;
	double _pWidth;
	double _pHeight;
	double _pDepth;
	int _pBlockType;

public:
	RangedWeapon(int, GameObj*);
	~RangedWeapon();


	double getPInitForce();
	double getPMass();
	double getPWidth();
	double getPHeight();
	double getPDepth();
	int getPBlockType();
};


