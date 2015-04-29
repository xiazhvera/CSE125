#include "stdafx.h"
#include "buildView.h"
#include "Model3DFactory.h"

/*
 * things to implement:
 * on click actions
 */

static Model3DFactory* m_factory;

buildView::buildView() : gui() {
	updateview = false;
	createButtons();
}

buildView::buildView(int w, int h) : gui(w, h) {
	updateview = false;
	createButtons();
}


buildView::~buildView() {
}

void buildView::createButtons() {
	m_factory = new  Model3DFactory();

	selectedType = BasicCube;
	yRotation = 0;
	rotateY.identity();
	center = Vector3(-3, -5, -3);

	GeoNode * cube = new roboBase(3, 1);
	cube->localTransform.position = Vector3(0, 0, 0);
	cube->identifier = 0;
	cube->textureType = THREEBYTHREE_BASIC;
	PushGeoNode(cube);
	currentNode = nullptr;  //not allowed to move base cube

	GeoNode * wheel = Model3DFactory::generateObjectWithType(WoodenWheel);
	wheel->localTransform.position = Vector3(1.6, -0.2, 1);
	wheel->identifier = 1;
	wheel->textureType = WoodenWheel;
	PushGeoNode(wheel);

	GeoNode * wheel2 = Model3DFactory::generateObjectWithType(WoodenWheel);
	wheel2->localTransform.position = Vector3(-1.6, -0.2, 1);
	wheel2->identifier = 2;
	wheel2->textureType = WoodenWheel;
	PushGeoNode(wheel2);

	GeoNode * wheel3 = Model3DFactory::generateObjectWithType(WoodenWheel);
	wheel3->localTransform.position = Vector3(1.6, -0.2, -1);
	wheel3->identifier = 3;
	wheel3->textureType = WoodenWheel;
	PushGeoNode(wheel3);

	GeoNode * wheel4 = Model3DFactory::generateObjectWithType(WoodenWheel);
	wheel4->localTransform.position = Vector3(-1.6, -0.2, -1);
	wheel4->identifier = 4;
	wheel4->textureType = WoodenWheel;
	PushGeoNode(wheel4);
	//for now, we just move the last added node
	//currentNode = NodeList[NodeList.size() - 1];

	

	//hardcoded button sizes for now

	//text displays
	//time.jpg dimensions: 800x100
	timer = new buildTimer(width*0.3, height - 50, 400, 50, false, false);
	timer->setScaling(true, false, width, height);
	guiItems.push_back(timer);

	//text box
	//textbox.jpg dimensions: 600x400
	score = new scoreBox(20, height - 100, 150, 100, true, false);
		guiItems.push_back(score);

	//battle button
	button * battle = new button("menuItem/battle.jpg", width - 120, 20);
	battle->setTexture("menuItem/battle_sel.jpg", btnState::SELECTED);
	battle->setTexture("menuItem/battle_press.jpg", btnState::PRESSED);
	buttons.push_back(battle);
	
	int scale = 4;
	
	//scroll box
	//scrollbox jpg dimensions: 1000x1600px
	scroll = new scrollBox(width - 520, 100, 0.5);
	buttons.push_back(scroll);

	//list options
	int identifier = 0;
	for (int i = 0; i < 3; i++) {
		std::string concat = std::to_string(i) + ".jpg";
		std::string selC = std::to_string(i) + "_sel.jpg";
		scroll->addListItem(concat, selC);
		//sublist, must be added right after the parent list
		for (int j = 0; j < 3; j++) {
			concat = std::to_string((i * 10) + j) + ".jpg";
			 selC = std::to_string((i * 10) + j) + "_sel.jpg";
			 scroll->addsubListItem(concat, selC, identifier);
			 identifier++;
		}
	}

	//help button
	button * help = new button("menuItem/help.jpg", 20, 20, true);
	help->setTexture("menuItem/help_sel.jpg", btnState::SELECTED);
	help->setTexture("menuItem/help_press.jpg", btnState::PRESSED);
	buttons.push_back(help);

	//grid textures
	setTexture("uiItem/images/buildModeGrid.jpg", &grids[0]);
	setTexture("uiItem/images/blackgrid.jpg", &grids[1]);
}

void buildView::VUpdate() {
	gui::VUpdate();
	if (!updateview && isCurrentView){// || true) { //use true to disable timer
		timer->start = std::clock();
	}
	for (int i = 0; i < guiItems.size(); i++) {
		guiItems[i]->update();
	}
	updateview = isCurrentView;

	if (score->deaths == 100) score->deaths = 0;
	if (score->hits == 100) score->hits = 0;
	if (score->rank == 100) score->rank = 0;
}

void buildView::VOnRender() {

	//Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the OpenGL matrix mode to ModelView
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	pViewCamera->setUpCamera();
	//glPushMatrix();
	//glLoadMatrixd(pViewCamera->GetCameraGLMatrix().getPointer());

	glPushMatrix();
	glTranslatef(center.x, center.y, center.z);
	glRotatef(yRotation, 0.0, 1.0, 0.0);

	for each (GeoNode* node in NodeList) {
		node->VOnDraw();
	};
	glPopMatrix();

	//draw grid plane quad
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grids[0]);
	glBegin(GL_QUADS);
	//bottom
	glTexCoord2f(0, 0); 
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5, center.z - HALF_GRID - 0.5);
	glTexCoord2f(0, 1); 
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5, center.z + HALF_GRID + 0.5);
	glTexCoord2f(1, 1); 
	glVertex3f(center.x + HALF_GRID + 0.5, center.y - 0.5, center.z + HALF_GRID + 0.5);
	glTexCoord2f(1, 0); 
	glVertex3f(center.x + HALF_GRID + 0.5, center.y - 0.5, center.z - HALF_GRID - 0.5);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, grids[1]);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5, center.z - HALF_GRID - 0.5);
	glTexCoord2f(0, 1);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y + GRID_SIZE - 0.5, center.z - HALF_GRID - 0.5);
	glTexCoord2f(1, 1);
	glVertex3f(center.x + HALF_GRID + 0.5, center.y + GRID_SIZE - 0.5, center.z - HALF_GRID - 0.5);
	glTexCoord2f(1, 0);
	glVertex3f(center.x + HALF_GRID + 0.5, center.y - 0.5, center.z - HALF_GRID - 0.5);

	//to the left
	glTexCoord2f(0, 0);
	//glNormal3f(1, 0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5, center.z - HALF_GRID - 0.5);
	glTexCoord2f(0, 1);
	//glNormal3f(1, 0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y - 0.5, center.z + HALF_GRID + 0.5);
	glTexCoord2f(1, 1);
	//glNormal3f(1, 0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y + GRID_SIZE - 0.5, center.z + HALF_GRID + 0.5);
	glTexCoord2f(1, 0);
	//glNormal3f(1, 0, 0);
	glVertex3f(center.x - HALF_GRID - 0.5, center.y + GRID_SIZE - 0.5, center.z - HALF_GRID - 0.5);
	glEnd();


	set2d();
	drawAllItems();
	set3d();
}

Vector3 buildView::addNewNodePos() {
	//for now, just add to the right of current node
	//logic here for finding place to start new node
	Vector3 check;

	if (currentNode == nullptr)
		check = translateNode(Vector3(0, 1, 0), NodeList[0]);
	else
		check = translateNode(Vector3(1, 0, 0), currentNode);

	if (currentNode != nullptr) {
		Vector3 temp = currentNode->localTransform.position;
		//if we got same position, try to the left
		if (check.equals(temp)) {
			check = translateNode(Vector3(-1, 0, 0), currentNode);
			//if still invalid, fuck it just don't add for now
			if (check.equals(temp)) {
				return Vector3(0,0,0);
			}
		}
	}
	return check;
}

viewType buildView::mouseClickFunc(int state, int x, int y) {
	for (int i = 0; i < buttons.size(); i++) {
		//y is goes top to bottom for mouse,
		//and bottom to top for texture >.<
		buttons[i]->onClick(state, x, height-y);
	}
	if (state == GLUT_UP && prevMouseState != GLUT_UP) {
		if (scroll->addButton->isSelected(x, height - y) ) {
			addNode();
		}
		else if (scroll->removeButton->isSelected(x, height - y)) {
			removeNode();
		}
	}
	selectedType = scroll->currentSelection;
	prevMouseState = state;

	if ((buttons[0]->isSelected(x, height - y) &&
		state == GLUT_UP)) {
		updateview = false;
		isCurrentView = false;
		return viewType::BATTLE;
	}
	else if (buttons[buttons.size() - 1]->isSelected(x, height - y)) {
		return viewType::HELP;
	}
	return viewType::BUILD;
}

void buildView::keyPressFunc(unsigned char key, int x, int y) {
	switch (key) {
	case 8: //backsapce
		//delete block
		removeNode();
		break;
	case 13: //enter
		//add block
		addNode();
		break;
	}
}

viewType buildView::checkTimeOut() {
	if (timer->timeLeft < 0) {
		return viewType::BATTLE;
	}
	return viewType::BUILD;
}

void buildView::addNode() {
	int s = NodeList.size();
	if (s < MAX_BLOCKS) {
		if (selectedType >= 6 && selectedType <= 8) {
			//is a wheel
			for (int i = 1; i < 5; i++) {
				GeoNode * object = Model3DFactory::generateObjectWithType(selectedType);
				object->localTransform.position = NodeList[i]->localTransform.position;
				object->identifier = NodeList[i]->identifier;
				object->textureType = selectedType;
				NodeList[i] = object;
			}
			return;
		}
		//screw it if it isn't valid, don't add
		Vector3 check = addNewNodePos();
		if (check.equals(Vector3(0,0,0))) {
			return;
		}
		GeoNode * object = Model3DFactory::generateObjectWithType(selectedType);
		object->localTransform.position = addNewNodePos();
		object->identifier = s;
		object->textureType = selectedType;
		PushGeoNode(object);
		//for now, we just move the last added node
		currentNode = NodeList[NodeList.size() - 1];
	}
}

void buildView::removeNode() {
	if (NodeList.size() > 5) {
		NodeList.pop_back();
		if (NodeList.size() <= 5) {
			currentNode = nullptr;  //not allowed to move base block
		}
		else {
			currentNode = NodeList[NodeList.size() - 1];
		}
	}
}

bool buildView::validPos(Vector3 t, GeoNode * node) {
	Vector3 check = node->localTransform.position + t;
	if (check.x > HALF_GRID - 1 || check.x < -HALF_GRID + 1) {
		return false;
	}
	if (check.z > HALF_GRID || check.z < -HALF_GRID) {
		return false;
	}
	if (check.y > GRID_SIZE - 1 || check.y < 0) {
		return false;
	}
	return true;
}

Vector3 buildView::translateNode(Vector3 t, GeoNode * node) {
	//this works for now with our small 3x3x3, until mouse raycast is implemented
	//std::cout << "old: " << t.x << " " << t.y << " " << t.z << std::endl;
	//t = rotateY.transform(t);
	//std::cout << t.x << " " << t.y << " " << t.z << std::endl;
	if (yRotation == 180) {
		t.x = -t.x;
		t.z = -t.z;
	} 
	else if (yRotation == 90) {
		double temp = t.x;
		t.x = -t.z;
		t.z = temp;
	}
	else if (yRotation == 270) {
		double temp = t.x;
		t.x = t.z;
		t.z = -temp;
	}

	Vector3 check = node->localTransform.position + t;
	if (!validPos(t, node)) return node->localTransform.position;
	int checkBelow = check.y;
	while (checkBelow > 0) {
		bool foundMatchBelow = false;
		for (int i = 0; i < NodeList.size(); i++) {
			Vector3 temp = NodeList[i]->localTransform.position;
			if (temp.x == check.x && temp.z == check.z) {
				if (temp.y == check.y - 1) {
					foundMatchBelow = true;
				}
			}
		}
		if (!foundMatchBelow) {
			check.y -= 1;
		}
		checkBelow--;
	}
	bool foundMatch = true;
	while (foundMatch) {
		foundMatch = false;
		for (int i = 0; i < NodeList.size(); i++) {
			Vector3 temp = NodeList[i]->localTransform.position;
			//if (check.equals(temp)) {
			if (NodeList[i]->intersect(check)) {
				foundMatch = true;
				break;
			}
		}
		if (foundMatch) {
			check.y += 1;
			t.y += 1;
		}
		if (!validPos(t, node)) {
			return node->localTransform.position;
		}
	}
	return check;
}


bool buildView::setTexture(string filename, GLuint * t) {
	*t = SOIL_load_OGL_texture
		(
		filename.c_str()
		,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);
	if (*t == 0)
	{
		std::cout << filename.c_str() << std::endl;
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return false;
	}

	//return true if successfully set texture
	//std::cout << filename << std::endl;
	//std::cout << "width: " << width << std::endl;
	//std::cout << "height: " << height << std::endl;
	return true;
}