
/* GameLogic.h */
#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include "Robot.h"
#include "ObjectEvents.h"
#include "Network.h"
#include "GamePhysics.h"
#include "definition.h"
#include "TimeFrame.h"
#include "DamageSystem.h"
#include "GERobotDeath.h"
#include "GameState.h"
#include <math.h>
#include "GEHealthUpdate.h"
#include "GETime.h"
#include "Scoreboard.h"
#include "GECollisonHappen.h"
#include "GEScoreboardUpdate.h"
#include <random>
#include "Hill.h"
#include "GEHillUpdate.h"
#include "GEPlayerHillUpdate.h"
#include "SpawnPoint.h"

#define FIELD_WIDTH 100
#define FIELD_HEIGHT 100
#define INSTANT_KILL 1
#define UPDATE_HILL 15


class GameLogic {
private:
	Network* network;
	GamePhysics* gamePhysics;
	TimeFrame* countDown;
	TimeFrame*	physicsTimer;
	DamageSystem* damageSystem;
	Scoreboard* scoreboard;
	Hill* hill;
	int counter;
	SpawnPoint* spawnPoint;
	Robot* dmgDealtArr[4];
	string names[4];

	std::vector<GameObj*> gameObjs;
	//when you delete a obj, deleteConstraints(), ~() delete rigidBody, set to nullptr
	//
	//check gameObjs vector every X ticks, push !null objs into new_gmaeObjs list
	//gameObjs = new_gameObjs

	std::map<int, GameObj *> clientPair;
	//clear

	//std::map< btCollisionObject*, GameObj*> objCollisionPair;
	//clear

	//std::vector<Constraint*> constraints;
	std::vector<ObjectEvents *> objEventList;
    std::vector<GameEvents *> gameEventList;
	std::vector<ObjectEvents *> buildList;
	std::uniform_real_distribution<double>* dist;
	std::default_random_engine generator;
	int lastTime;

public:
	int numPlayers;
	GameLogic();
	~GameLogic();
	unsigned int waitToConnect();
	unsigned int gameLoop();
	int gameStart();
	void prePhyLogic();
	void addWalls();
	void addGround();
	void postPhyLogic();
	void deleteGameObj(GameObj*);
	void cleanDataStructures();
	int breakConstraints(GameObj*);
	void createDeathEvent(Robot*);
	void createHealthUpdateEvent(Robot*);
	void createScoreboardUpdateEvent();
	void createGEClientCollision( GameObj*, GameObj*);
	void createHillUpdateEvent();
	void createPlayerHillUpdateEvent(int);
	void postDamageLogic(GameObj*, int e, btManifoldPoint*);
	void postHealthLogic(Robot* arr[]);
	void postDeathLogic(Robot*);

	int buildMode();
	int startBuild();
	int endGame();


	void applyMeleeForce(GameObj*, GameObj*);

	btVector3* convertQuaternionToEuler(btQuaternion* q);
	btQuaternion* convertEulerToQuaternion(double, double, double);
	int clearGame();
};
#endif