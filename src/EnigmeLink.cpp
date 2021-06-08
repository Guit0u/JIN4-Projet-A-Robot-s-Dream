#include "EnigmeLink.h"

EnigmeLink::EnigmeLink(int inputId, int condValue, int outputId) :
	Enigme(outputId),
	inputId(inputId),
	condValue(condValue)	
{}

void EnigmeLink::inputEvent(int id, int value)
{
	if (inputId == id && value == condValue)
	{
		setResolved(true);
	}
	else if (inputId == id) // only set to false if it's the right id but not the right value
	{
		setResolved(false);
	}
}