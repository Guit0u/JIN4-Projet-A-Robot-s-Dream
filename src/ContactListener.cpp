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




    /*
    b2BodyUserData bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData.pointer)
    {
        printf("beginContactA\n");
        auto ptr = (ContactElement*)bodyUserData.pointer;
        ptr->startContact();
        level->enigmeInput(ptr->getInputId(), ptr->getStateValue());
    }

 
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if (bodyUserData.pointer)
    {
        printf("beginContactB\n");
        auto ptr = (ContactElement*)bodyUserData.pointer;
        ptr->startContact();
        level->enigmeInput(ptr->getInputId(), ptr->getStateValue());
    }
     */   
}
void ContactListener::EndContact(b2Contact* contact)
{
    printf("endContact\n");
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