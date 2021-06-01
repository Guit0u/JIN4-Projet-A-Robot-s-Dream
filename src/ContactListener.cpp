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
                printf("beginContactA\n");
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
                printf("beginContactB\n");
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
                printf("endContactA\n");
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
                printf("endContactB\n");
                ptrB->endContact();
                level->enigmeInput(ptrB->getInputId(), ptrB->getStateValue());
            }
        }

    }
}