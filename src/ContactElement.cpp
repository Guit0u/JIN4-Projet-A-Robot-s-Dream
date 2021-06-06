#include "ContactElement.h"

ContactElement::ContactElement(int inputId) :
	inputId(inputId)
{
}

int ContactElement::getInputId() const
{
	return inputId;
}

int ContactElement::getStateValue() const
{
	return state;
}

void ContactElement::setStateValue(int value)
{
	state = value;
}

bool ContactElement::isPressurePlate() {
	return false;
}