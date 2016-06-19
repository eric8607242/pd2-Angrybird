/*#include "con.h"

con::contact()
{

}
void con::BeginContact(b2Contact* contact)
{
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData )
      {
          static_cast<Ball*>( bodyUserData )->startContact();
          std::cout<<"check"<<std::endl;
      }
      //check if fixture B was a ball
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData )
      {
          static_cast<Ball*>( bodyUserData )->startContact();
          std::cout<<"check"<<std::endl;
      }
}

void con::EndContact(b2Contact *contact)
{

}
*/
