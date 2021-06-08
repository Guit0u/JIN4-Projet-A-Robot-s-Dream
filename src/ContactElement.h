#pragma once

/*
Parent class for any element that is a sensor (interactible element)
*/
class ContactElement
{
public:
	explicit ContactElement(int inputId);
	virtual ~ContactElement() = default;
	
	virtual void startContact() = 0; //called when a contact start
	virtual void endContact() = 0; // called when a contact end

	int getInputId() const;
	int getStateValue() const;
	void setStateValue(int value);


private:
	int inputId; // id of the input port for enigmes
	int state = 0; // state of the contact element
};
