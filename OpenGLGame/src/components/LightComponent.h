#pragma once
#include "rendering/LightManager.h"

class CLightComponent
{
	size_t LightNumber;
	CLightManager* LightManager;
public:
	CLightComponent();
	~CLightComponent();
};

