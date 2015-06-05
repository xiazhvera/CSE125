#include "stdafx.h"
#include "EventSystem.h"
#include "EventInfo.h"
#include "EventDeath.h"
#include "EventParticle.h"
#include "EventTimer.h"
#include "EventScoreboard.h"
#include "EventHealth.h"
#include "EventCollision.h"
#include "EventWaiting.h"
#include "EventEmergency.h"
#include "EventHillUpdate.h"
#include "EventPlayerHillUpdate.h"
#include "GameCore.h"
#include "Fire.h"
#include "Window.h"
#include "ParticleSystem.h"

EventSystem::EventSystem()
{
	//sound = new Sound(); // initialize a new Sound object
}


EventSystem::~EventSystem()
{
}

void EventSystem::ProcessGamePacket(GameInfoPacket* packet)
{
	vector<EventInfo*>eventinfos = packet->event_infos;
	for (int i = 0; i < (int)eventinfos.size(); i++)
	{
		EventInfo* event = eventinfos[i];
		//std::cout << "mydoubleptr points to " << typeid(*event).name() << '\n';
		switch (event->event_type){
		case TEventDeath:{
							 //Switch back to game view
							 if (((EventDeath*)event)->death_id == (g_pCore->pPlayer->playerid)){
								 //printf("Death Event has been received \n");

								 // switch to build view
								 Window::factory->delayedRebuild();
								 // switch to build view sound in Window
								 
							 }
							 else{
								 //Explosion particle effect
								 //Explosion sound


							 }
							
							 break;
		}
		case TEventParticle:{
								//printf("particle event received \n");
								//Window::factory->battlemode->PushGeoNode();
								break;
		}
		case TEventTimer:{
							 EventTimer * t = (EventTimer *)event;
							 //printf("time event received \n");
							 //CHANGE BATTLE MODE ONLY
							 Window::factory->battlemode->timer->updateTime(t->time);
							 /////// end GUI

							 /////check if the game has ended
							 if (t->time <= 1) {
								 ///send player data to end screen for display
								 Window::factory->gameOver->numDeaths = Window::factory->score->getDeaths();
								 Window::factory->gameOver->numTakedowns = Window::factory->score->getTakedowns();
								 Window::factory->gameOver->myRank = Window::factory->score->getRank();
								 ///end
								 Window::factory->switchView(GLUT_KEY_F5);
							 }
							 ////end check



							 break;


		}
		case TEventScoreboard:{
								  EventScoreboard * s = (EventScoreboard *) event;
								 // printf("scoreboard event received\n");

								  //Change score variables in battle mode and build mode
								  int myID = g_pCore->pPlayer->playerid;
								  float deaths = max(s->deaths[myID], 1);
								  float kills = max(s->takedowns[myID], 1);
								  float myScore = kills / deaths;
								  
								  //calculate rank
								  int rank = 1;
								  for (int i = 0; i < 4; i++) {
									  if (i != myID) {
										  kills = max(s->takedowns[i], 1);
										  deaths = max(s->deaths[i], 1);
										  if (myScore < (kills / deaths) ) {
											  rank++;
										  }
									  }
								  }

								  if (Window::factory->viewmode == viewType::BUILD) {
									  Window::factory->score->updateScore(s->deaths[myID], s->takedowns[myID], rank);
								  }
								  else {
										// check if enter the money zone
									  int previous = Window::factory->buildmode->startingMoney;
									  if (s->gold[myID] > previous){
										  Window::soundObject->playMoneyCollection(); 
									  }

									  Window::factory->buildmode->startingMoney = s->gold[myID];
									  Window::factory->score->updateScore(s->deaths[myID], s->takedowns[myID], rank, s->gold[myID]);
								  }
								  /////// end GUI

								  break;

		}
		case TEventUpdateHealth:{
									//Update health bar
									EventHealth * h = (EventHealth *) event;
									//printf("health event received\n");

									//this is for the GUI display update
									if (h->player1id == g_pCore->pPlayer->playerid) {
										if (((float)h->health / (float)h->maxhealth) <= 0.05f){
											g_pCore->pGameView->SetBlur(true, 0.15f, 0.3f);
										}
										else{
											g_pCore->pGameView->SetBlur(false, 0.15f, 0.3f);
										}

										Window::factory->battlemode->updateHealth(h->health, h->maxhealth);
									}
									/////// end GUI

									break;

		}
		case TEventCollisionHappen:{
									  // printf("collision event received\n");
									   EventCollision * h = (EventCollision *)event;
									   switch (h->collision_type){
										   //bullet player
									   case 0:{
												  Fire* f = new Fire(h->x, h->y, h->z, 1, 0);
												  f->static_object = true;
												  f->lifeTime = 5;
												  g_pCore->pGameView->PushEnvironmentNode(f);
												  break;
									   }
										   //player player
									   case 1:{
												  Fire* f = new Fire(h->x, h->y, h->z, 1, 1);
												  f->static_object = true;
												  f->lifeTime = 5;
												  g_pCore->pGameView->PushEnvironmentNode(f);
												  Window::soundObject->playPPCrash(); // play player to player crash sound
												  break;
									   }
										   //player wall
									   case 2:{
												  /*
												  ParticleSystem* f = new ParticleSystem();
												  f->localTransform.position = Vector3(h->x, h->y, h->z);
												  f->static_object = true;
												  f->lifeTime = 10;
												  f->maxParticles = 75;
												  f->pemissionRate = 0.05;
												  f->spawnShape = ParticleInitShape::None;
												  f->cylinderRadius = 2;
												  f->startColor = Vector3(0.8, 0.8, 0);
												  g_pCore->pGameView->PushEnvironmentNode(f);
												  */
												  
												  Fire* f = new Fire(h->x, h->y, h->z, 1, 2);
												  f->static_object = true;
												  f->lifeTime = 1;
												  g_pCore->pGameView->PushEnvironmentNode(f);
												  Window::soundObject->playCollisionWall();// play collision to wall
												  //sound->playCollisionWall(); 
												  break;
									   }
										   //bullet wall
									   case 3:{
												  Fire* f = new Fire(h->x, h->y, h->z, 1, 3);
												  f->static_object = true;
												  f->lifeTime = 5;

												  g_pCore->pGameView->PushEnvironmentNode(f);
												  break;
									   }
										   //explorsion
									   case 4:{
												  break;
									   }
										   break;
									   }
		}
		case TEventWaiting:{
							  // printf("waiting event received\n");
							   break;

		}
		case TEventEmergency:{
								// printf("emergency event received\n");
								 break;

		}
		case TEventHillUpdate:{
								// printf("hill update received\n");
								 EventHillUpdate * h = (EventHillUpdate *)event;
								 /*
								 Model3D* hill = Model3DFactory::generateObjectWithType(GlowingCube);
								 hill->isUpdated = true;
								 hill->shader_type = LIGHTS_SHADER;

								 hill->localTransform.position = Vector3(h->x, h->y, h->z);
								 g_pCore->pGameView->PushEnvironmentNode(hill);
									*/
								 //
								 /*
								 Fire* f = new Fire(h->x, h->y, h->z, 0, 2);
								 f->static_object = true;
								 f->lifeTime = 30;
								 */
								 //g_pCore->pGameView->PushEnvironmentNode(f);

								
								 //factory->battlemode->PushEnvironmentNode(f);

								 break;

		}
		//For displaying effect for user in the zone to receive money
		case TEventPlayerHillUpdate:{
							  // printf("Event player hill update\n");
							   //
							   /*
							   EventPlayerHillUpdate * h = (EventPlayerHillUpdate *)event;
							   //particle
							   for each (GeoNode* node in g_pCore->pGameView->NodeList)
							   {
								   if (node->identifier == h->playerid)
								   {
									   //show something
									   Fire* f = new Fire(node->localTransform.position.x, node->localTransform.position.y + 4, node->localTransform.position.z, 0, 3);
									   f->static_object = true;
									   f->lifeTime = 5;
									  //g_pCore->pGameView->PushEnvironmentNode(f);
								   }
							   }
							   */
							   break;

		}
		case TEventDefault:{
							   //printf("Event default, should not entered\n");
							   break;

		}

		}
	}
}