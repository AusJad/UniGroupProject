#pragma once

#include "vectors.h"

class Mods
{
public:
	Mods();
	Mods(vec4 mod);
	~Mods();

	vec4 getMod();

protected:
	vec4 emo_mod;
};

// Start Mods
// Mod classes are classes that define how much a particular emotion affects the NPC
class EGm : public Mods
{
	EGm();
	EGm(float mod);
	~EGm();
};

class ALm : public Mods
{
	ALm();
	ALm(float mod);
	~ALm();
};

class VAm : public Mods
{
	VAm();
	VAm(float mod);
	~VAm();
};

class RTm : public Mods
{
	RTm();
	RTm(float mod);
	~RTm();
};

// End Mods


class Defs
{
	public:
		Defs();
		Defs(vec4 def);
		~Defs();

		vec4 getDef();

	protected:
		vec4 emo_default;
};

// Start Defaults
// Default classes are modifying the default emotion that the NPC will 'normalise' to.
class ExstasyDef : public Defs
{
	ExstasyDef();
	ExstasyDef(float def);
	~ExstasyDef();
};

class GriefDef : public Defs
{
	GriefDef();
	GriefDef(float def);
	~GriefDef();
};

class AdmirationDef : public Defs
{
	AdmirationDef();
	AdmirationDef(float def);
	~AdmirationDef();
};

class LoathingDef : public Defs
{
	LoathingDef();
	LoathingDef(float def);
	~LoathingDef();
};

class VigilanceDef : public Defs
{
	VigilanceDef();
	VigilanceDef(float def);
	~VigilanceDef();
};

class AmazementDef : public Defs
{
	AmazementDef();
	AmazementDef(float def);
	~AmazementDef();
};

class RageDef : public Defs
{
	RageDef();
	RageDef(float def);
	~RageDef();
};

class TerrorDef : public Defs
{
	TerrorDef();
	TerrorDef(float def);
	~TerrorDef();
};
// End Defaults