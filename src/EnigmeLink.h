#pragma once
#include "Enigme.h"

/*
Direct link between an input (pressure plate, switch) to a output (door) with a condition for opening
*/
class EnigmeLink : public Enigme
{
public:
	explicit EnigmeLink(int inputId, int condValue, int outputId);

	void inputEvent(int id, int value) override;


private:
	int inputId; 
	int condValue; 
};

