#pragma once

#include "Maths.h"
#include "RenderModuleStubb.h"
#include "TextureManager.h"
#include "FontEngine.h"

class MenuTools
{
public:
	static void drawButton(vec2 & tl, vec2 & br, float z, vec4 & color, std::string text, std::string font);
	static void drawTSquare(vec2 & tl, vec2 & br, float z, std::string texture, bool trans);
	static void drawSquare(vec2 & tl, vec2 & br, float z, vec4 & color);
	static void renderText(vec2 start, float z, float size, std::string torender);
	static float fadeIn(vec2 & tl, vec2 & br, float z,  float curfade, float time);
	static float fadeOut(vec2 & tl, vec2 & br, float z, float curfade, float time);
	static void drawModel(vec3 loc, std::string model);
};

