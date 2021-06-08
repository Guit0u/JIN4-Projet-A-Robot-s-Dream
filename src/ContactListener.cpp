#include "ContactListener.h"

/*
Contructor of ContactListener
need level to call input enigme depending on the case
*/
ContactListener::ContactListener(Level const& level) :
	level(&level)
{
}

/*
methode called when a contact start
*/
void ContactListener::BeginContact(b2Contact* contact)
{
    if (contact && contact->IsTouching())
    {
        b2BodyUserData bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData.pointer) // check if te contact has a userData
        {
            auto ptrA = (ContactElement*)bodyUserData.pointer; // only contactElement have userData
            if (ptrA)
            {
                ptrA->startContact();
                auto PPptr = dynamic_cast<PressurePlate*>(ptrA);
                if (PPptr) // special case : Pressure plate, call enigme input instanly
                {
                    level->enigmeInput(ptrA->getInputId(), ptrA->getStateValue());
                }
            }
        }
        
        // same with the other body
        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserData.pointer)
        {
            auto ptrB = (ContactElement*)bodyUserData.pointer;
            if (ptrB)
            {
                ptrB->startContact();
                auto PPptr = dynamic_cast<PressurePlate*>(ptrB);
                if (PPptr)
                {
                    level->enigmeInput(ptrB->getInputId(), ptrB->getStateValue());
                }
            }
        }
        
    }

}

/*
methode called when contact end
*/
void ContactListener::EndContact(b2Contact* contact)
{
    // similar to BeginContact
    if (contact && !contact->IsTouching())
    {
        b2BodyUserData bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData.pointer)
        {
            auto ptrA = (ContactElement*)bodyUserData.pointer;
            if (ptrA)
            {
                ptrA->endContact();
                auto PPptr = dynamic_cast<PressurePlate*>(ptrA);
                if (PPptr)
                {
                    level->enigmeInput(ptrA->getInputId(), ptrA->getStateValue());
                }
            }
        }


        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserData.pointer)
        {
            auto ptrB = (ContactElement*)bodyUserData.pointer;
            if (ptrB)
            {
                ptrB->endContact();
                auto PPptr = dynamic_cast<PressurePlate*>(ptrB);
                if (PPptr)
                {
                    level->enigmeInput(ptrB->getInputId(), ptrB->getStateValue());
                }
            }
        }

    }
}