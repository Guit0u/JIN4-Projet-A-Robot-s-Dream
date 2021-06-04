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
	else
	{
		setResolved(false);
	}
}