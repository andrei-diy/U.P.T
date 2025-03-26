#include "User.hpp"
#include "Label.hpp"
#include "Device.hpp"
#include <iostream>
using namespace Booking;
//#include <string>

void verify_state(Device d){
  std::cout<<" device " <<d.getSN() <<" has available status [" <<d.isFree()<< "] \n"; 
}
int main(){
    char a[]  = { 'A' };
    char b[]  = { 'B' };
    char c[]  = { 'C' };
    
    Device d1(1111,0,1), d2(2222,0,2), d3(3333,0,3);
    User user1(1,a), user2(2,b), user3(3,c);

    // in case we have two users with the same name(profession) we can copy the object and modify the id;
    User user4 = user3; //User user4 = new User(user3);
    user4.setID(4);

    // a user can have multiple devices with the same type/caracteristics booked 
    Device d4 = d1;
    d4.setSN(4444);

    std::cout<<"########################tema1###################\n";
    // copy constructor used when an obj is a parameter in a function
    verify_state(d4);
    
    Device test(1111,0,0);
    if( d1 == d2 ) std::cout<<"####### d1==d2 ########\n";
    if( d1 == test ) std::cout<<"####### d1==test #######\n";
    user1.printID();

    std::cout<<"########################tema2###################\n";
    Booking::BLabel label1("laptop_HP","1902313"),label2("laptop_ASUS","1921312"),label3("laptop_MAC","17232123");
    label1.printLabel();
    label2.printLabel();
    label3.printLabel();

    std::cout<<"\n verify that the assign operator works fine , label 1 should have the value of label 3\n";
    label1 = label2 = label3;
    label1.printLabel(); // verify that the assign operator works fine , label 1 should have the value of label 3

    std::cout<<"\n verify copy constructor / bitwise copy  and copy assignment\n";
    label1 = BLabel("a","1231");
    
    std::cout<<"\n verify move constructor / shallow copy  and move assignment\n";
    label1 == move(label2);
    label1 = move(BLabel("a","1231"));

    std::cout<<"\n\n\n";
    return 0;
}