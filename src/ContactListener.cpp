#include "ContactListener.h"

ContactListener::ContactListener(Level const& level) :
	level(&level)
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
 
    b2BodyUserData bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData.pointer)
    {
        auto ptr = (ContactElement*)bodyUserData.pointer;
        ptr->startContact();
        level->enigmeInput(ptr->getInputId(), ptr->getStateValue());
    }

 
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if (bodyUserData.pointer)
    {
        auto ptr = (ContactElement*)bodyUserData.pointer;
        ptr->startContact();
        level->enigmeInput(ptr->getInputId(), ptr->getStateValue());
    }
        
}
void ContactListener::EndContact(b2Contact* contact)
{
    b2BodyUserData bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData.pointer)
    {
        auto ptr = (ContactElement*)bodyUserData.pointer;
        ptr->endContact();
        level->enigmeInput(ptr->getInputId(), ptr->getStateValue());
    }


    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if (bodyUserData.pointer)
    {
        auto ptr = (ContactElement*)bodyUserData.pointer;
        ptr->endContact();
        level->enigmeInput(ptr->getInputId(), ptr->getStateValue());
    }
}