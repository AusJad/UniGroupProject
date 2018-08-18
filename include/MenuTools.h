#pragma once

#include "Maths.h"
#include "RenderModuleStubb.h"
#include "TextureManager.h"
#include "FontEngine.h"
#include "GUI.h"

/**
* @class MenuTools
* @brief Provides an interface for menu objects.
*
* @author Morgan Smolder
* @version 01
* @date 08/05/2018
*/
class MenuTools
{
public:
	/**
	* @brief Draw buttons on menu.
	*
	* @param t1 - The first position.
	* @param t2 - The second position.
	* @param z - The z value of the menu.
	* @param color - The colour of the menu with a alpha channel.
	* @param text - The text to be shown on screen.
	* @param font - The font for the text.
	*/
	static void drawButton(vec2 & tl, vec2 & br, float z, vec4 & color, std::string text, std::string font);
	/**
	* @brief Draw a textured square.
	* 
	* @param t1 - The first position.
	* @param br - The second position.
	* @param z - The z value of the menu.
	* @param texture - The texture for the menu.
	* @param trans - If the menu is see through.
	*/
	static void drawTSquare(vec2 & tl, vec2 & br, float z, std::string texture, bool trans);

	/**
	* @brief Draw a rotated textured square.
	*
	* @param t1 - The first position.
	* @param br - The second position.
	* @param z - The z value of the menu.
	* @param texture - The texture for the menu.
	* @param trans - If the menu is see through.
	* @param rot - The rotation vector.
	*/
	static void drawRotTSquare(vec2 & tl, vec2 & br, float z, std::string texture, bool trans, const vec4 & rot);

	/**
	* @brief Draw a non-textued square.
	* 
	* @param t1 - The first position.
	* @param br2 - The second position.
	* @param z - The z value of the menu.
	* @param color - The colour of the square.
	*/
	static void drawSquare(vec2 & tl, vec2 & br, float z, vec4 & color);

	/**
	* @brief Render the text onto the menu.
	*
	* @param start - The starting position.
	* @param z - The menu z value.
	* @param size - The size of the text.
	* @param torender - The string to render.
	*/
	static void renderText(vec2 start, float z, float size, std::string torender);
	
	/**
	* @brief Render the text onto the menu.
	*
	* @param start - The starting position.
	* @param z - The menu z value.
	* @param size - The size of the text.
	* @param torender - The string to render.
	*/
	static void renderTextF(vec2 start, float z, float size, std::string torender, std::string font);


	/**
	* @brief A method to fade the menu in.
	*
	* @param t1 - The first position vector.
	* @param br - The second position vector.
	* @param z - The menu z value.
	* @param curfade - The current fade value.
	* @param time - The time of the animation.
	*
	* @return - The fade value after method has finished.
	*/
	static float fadeIn(vec2 & tl, vec2 & br, float z,  float curfade, float time);
	
	/**
	* @brief A method to fade out the menu.
	*
	* @param t1 - The first position vector.
	* @param br - The second position vector.
	* @param z - The z value of the menu.
	* @param curfade - The current alpha channel value.
	* @param time - The time the fade animation should take.
	*
	* @return float - The alpha channel value.
	*/
	static float fadeOut(vec2 & tl, vec2 & br, float z, float curfade, float time);

	/**
	* @brief Draw the menu.
	*
	* @param loc - The location of the menu.
	* @param model - The model data.
	*/
	static void drawModel(vec3 loc, std::string model);

	static void interpretClick(int x, int y);

	static void switchMenuMode();
};

