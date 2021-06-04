#include "ContactListener.h"

ContactListener::ContactListener(Level const& level) :
	level(&level)
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
    if (contact && contact->IsTouching())
    {
        b2BodyUserData bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData.pointer)
        {
            auto ptrA = (ContactElement*)bodyUserData.pointer;
            if (ptrA)
            {
                ptrA->startContact();
                level->enigmeInput(ptrA->getInputId(), ptrA->getStateValue());
            }
        }
        
        
        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserData.pointer)
        {
            auto ptrB = (ContactElement*)bodyUserData.pointer;
            if (ptrB)
            {
                ptrB->startContact();
                level->enigmeInput(ptrB->getInputId(), ptrB->getStateValue());
            }
        }
        
    }

}
void ContactListener::EndContact(b2Contact* contact)
{
    if (contact && !contact->IsTouching())
    {
        b2BodyUserData bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData.pointer)
        {
            auto ptrA = (ContactElement*)bodyUserData.pointer;
            if (ptrA)
            {
                ptrA->endContact();
                level->enigmeInput(ptrA->getInputId(), ptrA->getStateValue());
            }
        }


        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserData.pointer)
        {
            auto ptrB = (ContactElement*)bodyUserData.pointer;
            if (ptrB)
            {
                ptrB->endContact();
                level->enigmeInput(ptrB->getInputId(), ptrB->getStateValue());
            }
        }

    }
}