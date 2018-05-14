#include "RenderModuleStubb.h"

RenderModuleStubb::RenderModuleStubb() {
	running = true;
	wireframe = false;
	id.setName("RM");
}

void RenderModuleStubb::DrawQuad(point tl, point br, float y) {
	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(tl.x, tl.y, y);
	glTexCoord2f(0, 0);
	glVertex3f(tl.x, br.y, y);
	glTexCoord2f(1, 0);
	glVertex3f(br.x, br.y, y);
	glTexCoord2f(1, 1);
	glVertex3f(br.x, tl.y, y);
	glEnd();
	glEnable(GL_LIGHTING);
}

void RenderModuleStubb::DrawQuad(vec3 tl, float widthx, float widthz, float height, vec3 trans) {
	glPushMatrix();
	glTranslatef(trans.x(), trans.y(), trans.z());
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(tl.x(), tl.y(), tl.z());
	glTexCoord2f(0, 0);
	glVertex3f(tl.x(), tl.y() + height, tl.z());
	glTexCoord2f(1, 0);
	glVertex3f(tl.x() + widthx, tl.y() + height, tl.z());
	glTexCoord2f(1, 1);
	glVertex3f(tl.x() + widthx, tl.y(), tl.z());

	glTexCoord2f(0, 1);
	glVertex3f(tl.x(), tl.y(), tl.z() + widthz);
	glTexCoord2f(0, 0);
	glVertex3f(tl.x(), tl.y() + height, tl.z() + widthz);
	glTexCoord2f(1, 0);
	glVertex3f(tl.x() + widthx, tl.y() + height, tl.z() + widthz);
	glTexCoord2f(1, 1);
	glVertex3f(tl.x() + widthx, tl.y(), tl.z() + widthz);
	glEnd();

	glPopMatrix();
}

void RenderModuleStubb::storeTexture(const int & texID, unsigned pixelsize, unsigned width, unsigned height, const unsigned char* data) {
	glGenTextures(1, (GLuint*)&texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, (pixelsize == 24) ? GL_RGB : GL_RGBA, width, height, 0, (pixelsize == 24) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)data);
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void RenderModuleStubb::genSubTex(const int & texID, unsigned pixelsize, unsigned width, unsigned height, unsigned subx, unsigned suby, unsigned subwidth, unsigned subheight, const unsigned char* data) {
	glGenTextures(1, (GLuint*)&texID);

	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
	unsigned char *subimg = (unsigned char*)(data + (subx + suby*width) * 3);

	glTexImage2D(GL_TEXTURE_2D, 0, (pixelsize == 24) ? GL_RGB : GL_RGBA, subwidth, subheight, 0, (pixelsize == 24) ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, (const GLvoid*)subimg);

	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);

	glBindTexture(GL_TEXTURE_2D, NULL);
}

void  RenderModuleStubb::deleteTexture(const int & texID) {
	glDeleteTextures(1, (GLuint*)&texID);
}

void RenderModuleStubb::bindMultiTexture(const int & texIDcolor, const int & texIDdetail) {
	glDisable(GL_BLEND);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D, texIDcolor);
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D, texIDdetail);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_ARB);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_RGB_SCALE_ARB, 2);
}

void RenderModuleStubb::bindTexture(const int & texID) {
	glBindTexture(GL_TEXTURE_2D, texID);
}

void RenderModuleStubb::disableMultiTexture() {
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderModuleStubb::renderArrayTriStrip(std::vector<unsigned> &indicies, std::vector<vec3> &vertices, const vec3 & trans) {
	glPushMatrix();
	glTranslatef(trans.x(), trans.y(), trans.z());
	glBegin(GL_TRIANGLE_STRIP);
	for (unsigned i = 0; i < indicies.size(); i++) {
		glVertex3f(vertices.at(indicies.at(i)).x(), vertices.at(indicies.at(i)).y(), vertices.at(indicies.at(i)).z());
	}
	glEnd();
	glPopMatrix();
}
void RenderModuleStubb::renderArrayTri(std::vector<unsigned>& indicies, std::vector<vec3>& vertices, std::vector<vec2> & texcoords, const vec3 & trans) {

	glPushMatrix();
	glTranslatef(trans.x(), trans.y(), trans.z());
	glBegin(GL_TRIANGLES);
	for (unsigned i = 0; i < indicies.size(); i++) {
		if (texcoords.empty() == false) glTexCoord2f(texcoords.at(indicies.at(i)).x(), texcoords.at(indicies.at(i)).y());
		glVertex3f(vertices.at(indicies.at(i)).x(), vertices.at(indicies.at(i)).y(), vertices.at(indicies.at(i)).z());
	}
	glEnd();
	glPopMatrix();
}

void RenderModuleStubb::msgrcvr() {
	MessagingBus* tmp = Singleton<MessagingBus>::getInstance();
	Message tmpm;

	while (tmp->hasMessage(id)) {

		tmpm = tmp->getMessage(id);

		if (tmpm.getInstruction() == WIREFRAME) {
			if (wireframe) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			wireframe = !wireframe;
		}
		else
			if (tmpm.getInstruction() == KILL) {
				running = false;
			}
	}
}

void RenderModuleStubb::renderArrayTri(std::vector<unsigned>& indicies, std::vector<vec3>& vertices, std::vector<vec3> normals, std::vector<vec2> & texcoords, const vec3 & trans) {
	glPushMatrix();
	glTranslatef(trans.x(), trans.y(), trans.z());
	glBegin(GL_TRIANGLES);
	for (unsigned i = 0; i < indicies.size(); i++) {
		if (texcoords.empty() == false) glTexCoord2f(texcoords.at(indicies.at(i)).x(), texcoords.at(indicies.at(i)).y());
		//Temporarily scaled for demo purposes
		if (normals.empty() == false) glNormal3f(normals.at(indicies.at(i)).x(), normals.at(indicies.at(i)).y(), normals.at(indicies.at(i)).z());
		glVertex3f(vertices.at(indicies.at(i)).x(), vertices.at(indicies.at(i)).y(), vertices.at(indicies.at(i)).z());
	}
	glEnd();
	glPopMatrix();
}

void RenderModuleStubb::renderMultiTexturedArrayTriStrip(std::vector<unsigned> & indicies, std::vector<vec3> & vertices, std::vector<vec2> & texcoords, std::vector<float> lights, const vec3 & trans) {
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glTranslatef(trans.x(), trans.y(), trans.z());
	glBegin(GL_TRIANGLE_STRIP);
	for (unsigned i = 0; i < indicies.size(); i++) {
		glColor4ub((GLubyte)lights.at(indicies.at(i)) * 1, (GLubyte)lights.at(indicies.at(i)) * 1, (GLubyte)lights.at(indicies.at(i)) * 1, (GLubyte)255);
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, texcoords.at(indicies.at(i)).x(), texcoords.at(indicies.at(i)).y());
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB, texcoords.at(indicies.at(i)).x() * 64, texcoords.at(indicies.at(i)).y() * 64);
		glVertex3f(vertices.at(indicies.at(i)).x(), vertices.at(indicies.at(i)).y(), vertices.at(indicies.at(i)).z());
	}
	glEnd();
	glPopMatrix();

	glColor4ub(255, 255, 255, 255);
	glEnable(GL_LIGHTING);
}

void RenderModuleStubb::renderTexturedArrayTriStrip(std::vector<unsigned> & indicies, std::vector<vec3> & vertices, std::vector<vec2> & texcoords) {
	glBegin(GL_TRIANGLE_STRIP);
	for (unsigned i = 0; i < indicies.size(); i++) {
		glTexCoord2f(texcoords.at(indicies.at(i)).x(), texcoords.at(indicies.at(i)).y());
		glVertex3f(vertices.at(indicies.at(i)).x(), vertices.at(indicies.at(i)).y(), vertices.at(indicies.at(i)).z());
	}
	glEnd();
}

void RenderModuleStubb::renderMultiTexturedArrayTriStrip(std::vector<unsigned> & indicies, std::vector<vec3> & vertices, std::vector<vec2> & texcoords, const vec3 & trans) {
	glPushMatrix();
	glTranslatef(trans.x(), trans.y(), trans.z());
	glBegin(GL_TRIANGLE_STRIP);
	for (unsigned i = 0; i < indicies.size(); i++) {
		glMultiTexCoord2fARB(GL_TEXTURE0_ARB, texcoords.at(indicies.at(i)).x(), texcoords.at(indicies.at(i)).y());
		glMultiTexCoord2fARB(GL_TEXTURE1_ARB, texcoords.at(indicies.at(i)).x() * 32, texcoords.at(indicies.at(i)).y() * 32);
		glVertex3f(vertices.at(indicies.at(i)).x(), vertices.at(indicies.at(i)).y(), vertices.at(indicies.at(i)).z());
	}
	glEnd();
	glPopMatrix();
}

void RenderModuleStubb::init(int argc, char** argv) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	glfwWindowHint(GLFW_DEPTH_BITS, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	window = glfwCreateWindow(1280, 720, "Game Engine", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, reshape);
	glEnable(GL_TEXTURE_2D);

	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}

	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}

	glfwSetWindowSizeLimits(window, 1280, 720, 1280, 720);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	//::ShowWindow(::GetConsoleWindow(), SW_HIDE);
	reshape(window, 1280, 720);
	glClearColor(0.0f, 0.0f, 0.0f, 0.92f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	float ambient[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
	float diffuse[4] = { 0.1f, 0.5f, 0.8f, 1.0f };
	float specular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float emission[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15.0f);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Assign created components to GL_LIGHT0
	configureLights();
}

bool RenderModuleStubb::shouldContinue() {
	return !glfwWindowShouldClose(window) && running;
}

void RenderModuleStubb::startRenderCycle() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	gluLookAt(campos.x(), campos.y(), campos.z(),
		camlook.x(), camlook.y(), camlook.z(),
		0.0f, 1.0f, 0.0f);
	glPushMatrix();
	commitLights();
}

void RenderModuleStubb::RenderFacingCamera() {
	glPushMatrix();
	glLoadIdentity();
}

void RenderModuleStubb::StopRenderFacingCamera() {
	glPopMatrix();
}

void RenderModuleStubb::endRenderCycle() {
	glPopMatrix();
	glFlush();
	glfwSwapBuffers(window);
	glfwPollEvents();
	msgrcvr();
}

void RenderModuleStubb::reshape(GLFWwindow* window, int width, int height) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(45.0f, aspect, 1, 22000);
	glMatrixMode(GL_MODELVIEW);
}

void RenderModuleStubb::callLookAt(vec3 r1, vec3 r2, vec3 r3) {
	campos = r1;
	camlook = r2;
}

void RenderModuleStubb::callLookAtImmediate(vec3 r1, vec3 r2, vec3 r3) {
	glPushMatrix();
	gluLookAt(r1.x(), r1.y(), r1.z(),
		r2.x(), r2.y(), r2.z(),
		r3.x(), r3.y(), r3.z());
}

float RenderModuleStubb::getTimeElapsed() {
	return (float)glfwGetTime();
}


float RenderModuleStubb::getTimeSinceUpdate() {

	float currentTime = (float)glfwGetTime();
	float returnTime = (currentTime - timeLastUpdate);
	timeLastUpdate = currentTime;
	return returnTime;
}

void RenderModuleStubb::configureLights() {

	glEnable(GL_LIGHTING);

	//light 0
	lights[0].enabled = true;
	setLightdiffuse(0, 1, 1, 1, 1.0f);
	setLightAmbient(0, 0.2f, 0.2f, 0.2f, 1.0f);
	setLightspecular(0, 1, 1, 1, 1.0f);
	setLightposition(0, 0.0f, 1.0f, 0.0f, 0);

	for (int i = 0; i < 8; i++) {
		if (lights[i].enabled) {
			switch (i) {
			case 0: glEnable(GL_LIGHT0);
				break;
			case 1: glEnable(GL_LIGHT1);
				break;
			case 2: glEnable(GL_LIGHT2);
				break;
			case 3: glEnable(GL_LIGHT3);
				break;
			case 4: glEnable(GL_LIGHT4);
				break;
			case 5: glEnable(GL_LIGHT5);
				break;
			case 6: glEnable(GL_LIGHT6);
				break;
			case 7: glEnable(GL_LIGHT7);
				break;
			}
		}
	}

}

void RenderModuleStubb::commitLights() {
	for (int i = 0; i < 8; i++) {
		if (lights[i].enabled) {
			switch (i) {
			case 0: {		glLightfv(GL_LIGHT0, GL_AMBIENT, lights[0].ambientLight);
				glLightfv(GL_LIGHT0, GL_DIFFUSE, lights[0].diffuseLight);
				glLightfv(GL_LIGHT0, GL_SPECULAR, lights[0].specularLight);
				glLightfv(GL_LIGHT0, GL_POSITION, lights[0].position);
				break;
			}
			case 1: {		glLightfv(GL_LIGHT1, GL_AMBIENT, lights[1].ambientLight);
				glLightfv(GL_LIGHT1, GL_DIFFUSE, lights[1].diffuseLight);
				glLightfv(GL_LIGHT1, GL_SPECULAR, lights[1].specularLight);
				glLightfv(GL_LIGHT1, GL_POSITION, lights[1].position);
				break;
			}
			case 2: {		glLightfv(GL_LIGHT2, GL_AMBIENT, lights[2].ambientLight);
				glLightfv(GL_LIGHT2, GL_DIFFUSE, lights[2].diffuseLight);
				glLightfv(GL_LIGHT2, GL_SPECULAR, lights[2].specularLight);
				glLightfv(GL_LIGHT2, GL_POSITION, lights[2].position);
				break;
			}
			case 3: {		glLightfv(GL_LIGHT3, GL_AMBIENT, lights[3].ambientLight);
				glLightfv(GL_LIGHT3, GL_DIFFUSE, lights[3].diffuseLight);
				glLightfv(GL_LIGHT3, GL_SPECULAR, lights[3].specularLight);
				glLightfv(GL_LIGHT3, GL_POSITION, lights[3].position);
				break;
			}
			case 4: {		glLightfv(GL_LIGHT4, GL_AMBIENT, lights[4].ambientLight);
				glLightfv(GL_LIGHT4, GL_DIFFUSE, lights[4].diffuseLight);
				glLightfv(GL_LIGHT4, GL_SPECULAR, lights[4].specularLight);
				glLightfv(GL_LIGHT4, GL_POSITION, lights[4].position);
				break;
			}
			case 5: {		glLightfv(GL_LIGHT5, GL_AMBIENT, lights[5].ambientLight);
				glLightfv(GL_LIGHT5, GL_DIFFUSE, lights[5].diffuseLight);
				glLightfv(GL_LIGHT5, GL_SPECULAR, lights[5].specularLight);
				glLightfv(GL_LIGHT5, GL_POSITION, lights[5].position);
				break;
			}
			case 6: {		glLightfv(GL_LIGHT6, GL_AMBIENT, lights[6].ambientLight);
				glLightfv(GL_LIGHT6, GL_DIFFUSE, lights[6].diffuseLight);
				glLightfv(GL_LIGHT6, GL_SPECULAR, lights[6].specularLight);
				glLightfv(GL_LIGHT6, GL_POSITION, lights[6].position);
				break;
			}
			case 7: {		glLightfv(GL_LIGHT7, GL_AMBIENT, lights[7].ambientLight);
				glLightfv(GL_LIGHT7, GL_DIFFUSE, lights[7].diffuseLight);
				glLightfv(GL_LIGHT7, GL_SPECULAR, lights[7].specularLight);
				glLightfv(GL_LIGHT7, GL_POSITION, lights[7].position);
				break;
			}
			}
		}
	}
}

void RenderModuleStubb::setLightAmbient(int lightNo, float first, float second, float third, float fourth) {
	if (lightNo < 8 && lightNo > -1) {
		lights[lightNo].ambientLight[0] = first;
		lights[lightNo].ambientLight[1] = second;
		lights[lightNo].ambientLight[2] = third;
		lights[lightNo].ambientLight[3] = fourth;
	}
}
void RenderModuleStubb::setLightdiffuse(int lightNo, float first, float second, float third, float fourth) {
	if (lightNo < 8 && lightNo > -1) {
		lights[lightNo].diffuseLight[0] = first;
		lights[lightNo].diffuseLight[1] = second;
		lights[lightNo].diffuseLight[2] = third;
		lights[lightNo].diffuseLight[3] = fourth;
	}
};
void RenderModuleStubb::setLightspecular(int lightNo, float first, float second, float third, float fourth) {
	if (lightNo < 8 && lightNo > -1) {
		lights[lightNo].specularLight[0] = first;
		lights[lightNo].specularLight[1] = second;
		lights[lightNo].specularLight[2] = third;
		lights[lightNo].specularLight[3] = fourth;
	}
};
void RenderModuleStubb::setLightposition(int lightNo, float first, float second, float third, float fourth) {
	if (lightNo < 8 && lightNo > -1) {
		lights[lightNo].position[0] = first;
		lights[lightNo].position[1] = second;
		lights[lightNo].position[2] = third;
		lights[lightNo].position[3] = fourth;
	}

};

HWND RenderModuleStubb::getWinWindow() {
	return glfwGetWin32Window(window);
}

void RenderModuleStubb::pushMatrix(const float mat[16]) {
	glPushMatrix();
	glMultMatrixf(mat);
}

void RenderModuleStubb::popMatrix() {
	glPopMatrix();
}

GeometeryStream & RenderModuleStubb::getGeoStream() {
	return geoStream;
}