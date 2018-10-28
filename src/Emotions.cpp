#include "Emotions.h"

Emotions::Emotions()
{
	emotions = vec4(0, 0, 0, 0);
	modifiers = vec4(0, 0, 0, 0);
	defaults = vec4(0, 0, 0, 0);
}

Emotions::Emotions(vec4 emo, vec4 mod, vec4 def)
{
	emotions = emo;
	modifiers = mod;
	defaults = def;
}

Emotions::~Emotions()
{

}

void Emotions::add_emotion(vec4 e) 
{
	emotions += e;
	if (e.x())
	{
		emotions *= vec4(normalization[0], normalization[1], normalization[2], normalization[3]); // 1st row
	}

	if (e.y())
	{
		emotions *= vec4(normalization[4], normalization[5], normalization[6], normalization[7]); // 2nd row
	}

	if (e.z())
	{
		emotions *= vec4(normalization[8], normalization[9], normalization[10], normalization[11]); // 3rd row
	}

	if (e.w())
	{
		emotions *= vec4(normalization[12], normalization[13], normalization[14], normalization[15]); // 4th row
	}

	this->normalize_emotions();
}

void Emotions::add_modifier(vec4 m)
{
	modifiers += m;
}

void Emotions::add_default(vec4 d)
{
	defaults += d;
}

vec4 Emotions::getEmotions()
{
	return emotions;
}

vec4 Emotions::getModifiers()
{
	return modifiers;
}

vec4 Emotions::getDefaults()
{
	return defaults;
}

void Emotions::setEmotions(const vec4 & e)
{
	emotions = e;
}

void Emotions::setModifiers(const vec4 & m)
{
	modifiers = m;
}

void Emotions::setDefaults(const vec4 & d)
{
	defaults = d;
}

void Emotions::normalize_emotions()
{
	if (emotions.x() != defaults.x())
	{
		if (emotions.x() < defaults.x())
		{
			emotions.sx(emotions.x() + 0.1);
		}
		else
		{
			emotions.sx(emotions.x() - 0.1);
		}
	}

	if (emotions.y() != defaults.y())
	{
		if (emotions.y() < defaults.y())
		{
			emotions.sy(emotions.y() + 0.1);
		}
		else
		{
			emotions.sy(emotions.y() - 0.1);
		}
	}

	if (emotions.z() != defaults.z())
	{
		if (emotions.z() < defaults.z())
		{
			emotions.sz(emotions.z() + 0.1);
		}
		else
		{
			emotions.sz(emotions.z() - 0.1);
		}
	}

	if (emotions.w() != defaults.w())
	{
		if (emotions.w() < defaults.w())
		{
			emotions.sw(emotions.w() + 0.1);
		}
		else
		{
			emotions.sw(emotions.w() - 0.1);
		}
	}
}

float Emotions::x()
{
	return emotions.x();
}

float Emotions::y()
{
	return emotions.y();
}

float Emotions::z()
{
	return emotions.z();
}

float Emotions::w()
{
	return emotions.w();
}