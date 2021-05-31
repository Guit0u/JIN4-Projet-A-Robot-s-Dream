#pragma once

class ContactElement
{
public:
	explicit ContactElement(int inputId);
	virtual ~ContactElement() = default;
	
	virtual void startContact() = 0;
	virtual void endContact() = 0;

	int getInputId() const;
	int getStateValue() const;
	void setStateValue(int value);

private:
	int inputId;
	int state = 0;
};
