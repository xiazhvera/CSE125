#pragma once

#include "stdafx.h"
#include "glew.h"
#include "tiny_obj_loader.h"
#include <GL/glut.h>
#include <string>
#include <iostream>
#include "SOIL.h"

class ShaderSystem
{
public:
	//Shader id
	vector<GLhandleARB> shader_ids;
	//Four maps
	GLuint texturaID[4];


	ShaderSystem();
	bool loadShaders(string vertex_shader_path, string fragment_shader_path);
	~ShaderSystem();
};

