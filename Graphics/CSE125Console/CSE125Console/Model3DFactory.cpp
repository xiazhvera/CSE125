#include "stdafx.h"
#include "Model3DFactory.h"
#include "Model3DGroup.h"
static vector<RenderObject*> render_obj_lst;
static map<int, RenderObject*> render_obj_map;
Model3DFactory::Model3DFactory()
{
	//blocks
	render_obj_map.insert(std::pair<int, RenderObject*>(BasicCube, new RenderObject("Assets/BasicCube/cube2.obj", "Assets/BasicCube/tex.png", "Assets/BasicCube/normals.png", "Assets/BasicCube/gloss.png", "Assets/BasicCube/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(GlowingCube, new RenderObject("Assets/WhiteCube/simplecube2.obj", "Assets/WhiteCube/tex.png", "Assets/WhiteCube/normals.png", "Assets/WhiteCube/gloss.png", "Assets/WhiteCube/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(WoodenCube, new RenderObject("Assets/WoodenCube/woodcube.obj", "Assets/WoodenCube/tex.png", "Assets/WoodenCube/normals.png", "Assets/WoodenCube/gloss.png", "Assets/WoodenCube/metallic.png")));
	//weapons
	render_obj_map.insert(std::pair<int, RenderObject*>(BGun, new RenderObject("Assets/BlockyGun/gat.obj", "Assets/BlockyGun/tex.png", "Assets/BlockyGun/normals.png", "Assets/BlockyGun/gloss.png", "Assets/BlockyGun/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(Mace, new RenderObject("Assets/Mace/mace.obj", "Assets/Mace/tex.png", "Assets/Mace/normals.png", "Assets/Mace/gloss.png", "Assets/Mace/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(Mallet, new RenderObject("Assets/Hammer/Hammer.obj", "Assets/Hammer/tex.png", "Assets/Hammer/normals.png", "Assets/Hammer/gloss.png", "Assets/Hammer/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(Needle, new RenderObject("Assets/Needle/needle.obj", "Assets/Needle/tex.png", "Assets/Needle/normals.png", "Assets/Needle/gloss.png", "Assets/Needle/metallic.png")));
	//wheels
	render_obj_map.insert(std::pair<int, RenderObject*>(Discount, new RenderObject("Assets/MetalWheel/metalwheel.obj", "Assets/MetalWheel/tex.png", "Assets/MetalWheel/normals.png", "Assets/MetalWheel/gloss.png", "Assets/MetalWheel/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(Tire, new RenderObject("Assets/Tire/tire.obj", "Assets/Tire/tex.png", "Assets/Tire/normals.png", "Assets/Tire/gloss.png", "Assets/Tire/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(WoodenWheel, new RenderObject("Assets/WoodenWheel/woodwheel.obj", "Assets/WoodenWheel/tex.png", "Assets/WoodenWheel/normals.png", "Assets/WoodenWheel/gloss.png", "Assets/WoodenWheel/metallic.png")));
	
	render_obj_map.insert(std::pair<int, RenderObject*>(BATTLEFIELD, new RenderObject("Assets/BattleField/checkerboard.obj", "Assets/BattleField/tex.png", "Assets/BattleField/normals.png", "Assets/BattleField/gloss.png", "Assets/BattleField/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(METHCUBE, new RenderObject("Assets/CrystalMethCube/cubeofmeth.obj", "Assets/CrystalMethCube/tex.png", "Assets/CrystalMethCube/normals.png", "Assets/CrystalMethCube/gloss.png", "Assets/CrystalMethCube/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(TREE1, new RenderObject("Assets/reallylowres/treelowtes.obj", "Assets/reallylowres/tex.png", "Assets/reallylowres/normals.png", "Assets/reallylowres/gloss.png", "Assets/reallylowres/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(TREE2, new RenderObject("Assets/lowishres/treelowish.obj", "Assets/lowishres/tex.png", "Assets/lowishres/normals.png", "Assets/lowishres/gloss.png", "Assets/lowishres/metallic.png")));
	render_obj_map.insert(std::pair<int, RenderObject*>(SUPERTREE, new RenderObject("Assets/Supertree/supertree.obj", "Assets/Supertree/tex.png", "Assets/Supertree/normals.png", "Assets/Supertree/gloss.png", "Assets/Supertree/metallic.png")));

}


Model3DFactory::~Model3DFactory()
{
}

Model3D* Model3DFactory::generateObjectWithType(int type){
	switch (type){
		case Mallet:{
			Model3D * returnModel = new Model3D(render_obj_map[type]);
			returnModel->damageStat = 1;
			return returnModel;
			break;
		}
		case Mace:{
			Model3D * returnModel = new Model3D(render_obj_map[type]);
			returnModel->damageStat = 1;
			return returnModel;
			break;
		}
		case Discount:{
			Model3D * returnModel = new Model3D(render_obj_map[type]);
			returnModel->speedStat = 1;
			return returnModel;
			break;
		}
		case Needle:{
			Model3D * returnModel = new Model3D(render_obj_map[type]);
			returnModel->damageStat = 1;
			return returnModel;
			break;
		}
		case BasicCube:{
			Model3D * returnModel = new Model3D(render_obj_map[type]);
			returnModel->healthStat = 1;
			return returnModel;
			break;
		}
		case WoodenCube:{
			Model3D * returnModel = new Model3D(render_obj_map[type]);
			returnModel->healthStat = 1;
			return returnModel;
			break;
		}
		case WoodenWheel:{
			Model3D * returnModel = new Model3D(render_obj_map[type]);
			returnModel->speedStat = 1;
			return returnModel;
			break;
		}
		case Tire:{
			Model3D * returnModel = new Model3D(render_obj_map[type]);
			returnModel->speedStat = 1;
			return returnModel;
			break;
		}
		case GlowingCube:{
			Model3D * returnModel = new Model3D(render_obj_map[type]);
			returnModel->healthStat = 1;
			return returnModel;
			break;
		}
		case BGun:{
			Model3D * returnModel = new Model3D(render_obj_map[type]);
			returnModel->healthStat = 1;
			return returnModel;
			break;
		}
		case BATTLEFIELD:{
			Model3D * returnModel = new Model3D(render_obj_map[type]);
			returnModel->type = BATTLEFIELD;
			return returnModel;
			break;
		}
		case METHCUBE:{
			Model3D * returnModel = new Model3D(render_obj_map[type]);
			returnModel->type = METHCUBE;
			return returnModel;
			break;
		}
		
		//Fix this
		case THREEBYTHREE_BASIC:{
			Model3DGroup* group = new Model3DGroup();
			for (int i = -1; i < 2; i++){
				for (int j = -1; j < 2; j++){
					Model3D * returnModel = Model3DFactory::generateObjectWithType(BasicCube);
					returnModel->localTransform.position = Vector3(i, 0, j);
					returnModel->localTransform.scale = Vector3(1, 1, 1);
					returnModel->localTransform.rotation = Vector3(0, 0, 0);
					group->addObject(returnModel);
				}
			}
			group->width = 3;
			group->height = 1;
			return group;
			break;
		}
		case THREEBYTHREE_GLOWING:{
			Model3DGroup* group = new Model3DGroup();
			for (int i = -1; i < 2; i++){
				for (int j = -1; j < 2; j++){
					Model3D * returnModel = Model3DFactory::generateObjectWithType(GlowingCube);
					returnModel->localTransform.position = Vector3(i, 0, j);
					returnModel->localTransform.scale = Vector3(1, 1, 1);
					returnModel->localTransform.rotation = Vector3(0, 0, 0);
					group->addObject(returnModel);
				}
			}
			group->width = 3;
			group->height = 1;
			return group;
			break;
		}
		case THREEBYTHREE_WOODEN:{
			Model3DGroup* group = new Model3DGroup();
			for (int i = -1; i < 2; i++){
				for (int j = -1; j < 2; j++){
					Model3D * returnModel = Model3DFactory::generateObjectWithType(WoodenCube);
					returnModel->localTransform.position = Vector3(i, 0, j);
					returnModel->localTransform.scale = Vector3(1, 1, 1);
					returnModel->localTransform.rotation = Vector3(0, 0, 0);
					group->addObject(returnModel);
				}
			}
			group->width = 3;
			group->height = 1;
			return group;
			break;
		}
		case THREEBYTHREE_WHEEL_DISCOUNT:{
			Model3DGroup* group = new Model3DGroup();
			Model3D * returnModel = Model3DFactory::generateObjectWithType(Discount);
			returnModel->localTransform.position = Vector3(-2, 0, -1);
			returnModel->localTransform.scale = Vector3(1, 1, 1);
			returnModel->localTransform.rotation = Vector3(0, 0, 0);
			group->addObject(returnModel); 
			returnModel = Model3DFactory::generateObjectWithType(Discount);
			returnModel->localTransform.position = Vector3(-2, 0, 1);
			returnModel->localTransform.scale = Vector3(1, 1, 1);
			returnModel->localTransform.rotation = Vector3(0, 0, 0);
			group->addObject(returnModel);

			returnModel = Model3DFactory::generateObjectWithType(Discount);
			returnModel->localTransform.position = Vector3(2, 0, -1);
			returnModel->localTransform.scale = Vector3(1, 1, 1);
			returnModel->localTransform.rotation = Vector3(0, 0, 0);
			group->addObject(returnModel);

			returnModel = Model3DFactory::generateObjectWithType(Discount);
			returnModel->localTransform.position = Vector3(2, 0, 1);
			returnModel->localTransform.scale = Vector3(1, 1, 1);
			returnModel->localTransform.rotation = Vector3(0, 0, 0);
			group->addObject(returnModel);

			return group;
			break;
		}
	case THREEBYTHREE_WHEEL_TIRE:{
			Model3DGroup* group = new Model3DGroup();
			Model3D * returnModel = Model3DFactory::generateObjectWithType(Tire);
			returnModel->localTransform.position = Vector3(-2, 0, -1);
			returnModel->localTransform.scale = Vector3(1, 1, 1);
			returnModel->localTransform.rotation = Vector3(0, 0, 0);
			group->addObject(returnModel);
			returnModel = Model3DFactory::generateObjectWithType(Tire);
			returnModel->localTransform.position = Vector3(-2, 0, 1);
			returnModel->localTransform.scale = Vector3(1, 1, 1);
			returnModel->localTransform.rotation = Vector3(0, 0, 0);
			group->addObject(returnModel);

			returnModel = Model3DFactory::generateObjectWithType(Tire);
			returnModel->localTransform.position = Vector3(2, 0, -1);
			returnModel->localTransform.scale = Vector3(1, 1, 1);
			returnModel->localTransform.rotation = Vector3(0, 0, 0);
			group->addObject(returnModel);

			returnModel = Model3DFactory::generateObjectWithType(Tire);
			returnModel->localTransform.position = Vector3(2, 0, 1);
			returnModel->localTransform.scale = Vector3(1, 1, 1);
			returnModel->localTransform.rotation = Vector3(0, 0, 0);
			group->addObject(returnModel);

			return group;
			break;
	}
	case THREEBYTHREE_WHEEL_WOODEN:{
			Model3DGroup* group = new Model3DGroup();
			Model3D * returnModel = Model3DFactory::generateObjectWithType(WoodenWheel);
			returnModel->localTransform.position = Vector3(-2, 0, -1);
			returnModel->localTransform.scale = Vector3(1, 1, 1);
			returnModel->localTransform.rotation = Vector3(0, 0, 0);
			group->addObject(returnModel);
			returnModel = Model3DFactory::generateObjectWithType(WoodenWheel);
			returnModel->localTransform.position = Vector3(-2, 0, 1);
			returnModel->localTransform.scale = Vector3(1, 1, 1);
			returnModel->localTransform.rotation = Vector3(0, 0, 0);
			group->addObject(returnModel);

			returnModel = Model3DFactory::generateObjectWithType(WoodenWheel);
			returnModel->localTransform.position = Vector3(2, 0, -1);
			returnModel->localTransform.scale = Vector3(1, 1, 1);
			returnModel->localTransform.rotation = Vector3(0, 0, 0);
			group->addObject(returnModel);

			returnModel = Model3DFactory::generateObjectWithType(WoodenWheel);
			returnModel->localTransform.position = Vector3(2, 0, 1);
			returnModel->localTransform.scale = Vector3(1, 1, 1);
			returnModel->localTransform.rotation = Vector3(0, 0, 0);
			group->addObject(returnModel);

			return group;
			break;
	}
		
	//Environment objects
	case TREE1:{
		Model3D * returnModel = new Model3D(render_obj_map[type]);
		returnModel->type = TREE1;
		return returnModel;
		break;
	}
	case TREE2:{
		Model3D * returnModel = new Model3D(render_obj_map[type]);
		returnModel->type = TREE2;
		return returnModel;
		break;
	}
	case SUPERTREE:{
		Model3D * returnModel = new Model3D(render_obj_map[type]);
		returnModel->type = SUPERTREE;
		return returnModel;
		break;
	}
		case WALL:{
					  break;
		}
		case BULLET_1:{
						  break;
		}

	}
}

Vector3 Model3DFactory::getOffset(int type) {
	switch (type) {
	case Discount: 
		break;
	case Tire:
		break;
	case WoodenWheel:
		break;
	default:
		break;
	}
	return Vector3(0, 0, 0);
}
