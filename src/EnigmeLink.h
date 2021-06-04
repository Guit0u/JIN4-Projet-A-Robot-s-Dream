#pragma once
#include "Enigme.h"

class EnigmeLink : public Enigme
{
public:
	explicit EnigmeLink(int inputId, int condValue, int outputId);

	void inputEvent(int id, int value) override;


private:
	int inputId; 
	int condValue; 
};

