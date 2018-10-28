#include "Traits.h"

/*
NOT IN USE -- MM
*/

Mods::Mods()
{
	emo_mod = vec4(1, 1, 1, 1);
}

Mods::Mods(vec4 mod)
{
	emo_mod = mod;
}

Mods::~Mods()
{

}

vec4 Mods::getMod()
{
	return emo_mod;
}


/* Start mod classes */
// Exstasy and Grief
EGm::EGm()
{
	emo_mod = vec4(2, 1, 1, 1);
}

EGm::EGm(float mod)
{
	emo_mod = vec4(mod, 1, 1, 1);
}

EGm::~EGm()
{

}

// Admiration and Loathing
ALm::ALm()
{
	emo_mod = vec4(1, 2, 1, 1);
}

ALm::ALm(float mod)
{
	emo_mod = vec4(1, mod, 1, 1);
}

ALm::~ALm()
{

}

// Vigilance and Amazement
VAm::VAm()
{
	emo_mod = vec4(1, 1, 2, 1);
}

VAm::VAm(float mod)
{
	emo_mod = vec4(1, 1, mod, 1);
}

VAm::~VAm()
{

}

// Rage and Terror
RTm::RTm()
{
	emo_mod = vec4(1, 1, 1, 2);
}

RTm::RTm(float mod)
{
	emo_mod = vec4(1, 1, 1, mod);
}

RTm::~RTm()
{

}

/* End mod classes */


Defs::Defs()
{
	emo_default = vec4(0, 0, 0, 0);
}

Defs::Defs(vec4 def)
{
	emo_default = def;
}

Defs::~Defs()
{

}

vec4 Defs::getDef()
{
	return emo_default;
}

/* Start default classes */

ExstasyDef::ExstasyDef()
{
	emo_default = vec4(0.5, 0, 0, 0);
}

ExstasyDef::ExstasyDef(float def)
{
	emo_default = vec4(def, 0, 0, 0);
}

ExstasyDef::~ExstasyDef()
{

}



GriefDef::GriefDef()
{
	emo_default = vec4(0.5, 0, 0, 0);
}

GriefDef::GriefDef(float def)
{
	emo_default = vec4(def, 0, 0, 0);
}

GriefDef::~GriefDef()
{

}


AdmirationDef::AdmirationDef()
{
	emo_default = vec4(0, 0.5, 0, 0);
}

AdmirationDef::AdmirationDef(float def)
{
	emo_default = vec4(0, def, 0, 0);
}

AdmirationDef::~AdmirationDef()
{

}


LoathingDef::LoathingDef()
{
	emo_default = vec4(0, 0.5, 0, 0);
}

LoathingDef::LoathingDef(float def)
{
	emo_default = vec4(0, def, 0, 0);
}

LoathingDef::~LoathingDef()
{

}


VigilanceDef::VigilanceDef()
{
	emo_default = vec4(0, 0, 0.5, 0);
}

VigilanceDef::VigilanceDef(float def)
{
	emo_default = vec4(0, 0, def, 0);
}

VigilanceDef::~VigilanceDef()
{

}

AmazementDef::AmazementDef()
{
	emo_default = vec4(0, 0, 0.5, 0);
}

AmazementDef::AmazementDef(float def)
{
	emo_default = vec4(0, 0, def, 0);
}

AmazementDef::~AmazementDef()
{

}


RageDef::RageDef()
{
	emo_default = vec4(0, 0, 0, 0.5);
}

RageDef::RageDef(float def)
{
	emo_default = vec4(0, 0, 0, def);
}

RageDef::~RageDef()
{

}


TerrorDef::TerrorDef()
{
	emo_default = vec4(0, 0, 0, 0.5);
}

TerrorDef::TerrorDef(float def)
{
	emo_default = vec4(0, 0, 0, def);
}

TerrorDef::~TerrorDef()
{

}