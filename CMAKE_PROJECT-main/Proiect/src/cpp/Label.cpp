#include "Label.hpp"
#include <iostream> 
#include <string>
#include <cstring>

using namespace Booking;
using namespace std;

BLabel::BLabel(string text, string ISBN){ 
    this->text = text;
    this->ISBN = ISBN;
    std::cout<<"Label  <"+ text + ">  created\n"; 
}
void BLabel::setText(string text){
    this->text = text;
}
void BLabel::setISBN(string ISBN){
    this->ISBN = ISBN;
}
string BLabel::getText(){
    return this->text;
}
string BLabel::getISBN(){
    return this->ISBN;
}
void BLabel::printLabel(){
    std::cout<<this->text + " " + this->ISBN + " ------label printed\n";
}
BLabel::~BLabel(){   
    std::cout<<"Label <" + this->text + "> deleted\n";
}
BLabel::BLabel(BLabel&& label){
    this->text = label.text;
    this->ISBN = label.ISBN;
    std::cout<<"Shallow copy of label" + label.text + " was created\n";
}
BLabel::BLabel(const BLabel& label){
    this->text = label.text;
    this->ISBN = label.ISBN;
    std::cout<<"Bit wise copy of label" + label.text + " was created\n";
}
BLabel BLabel::operator=(BLabel op2) //copy assign operator
{
    this->text = op2.getText(); // These are integer assignments
    this->ISBN = op2.getISBN(); // and the = retains its original
    std::cout<<"Label <" + this->text + "> asign by copy operator\n";
    return *this;
}
BLabel& BLabel::operator==(BLabel&& op2) //copy assign operator
{
    this->text = op2.getText(); // These are integer assignments
    this->ISBN = op2.getISBN(); // and the = retains its original
    std::cout<<"Label <" + this->text + "> asign by move operator\n";
    return *this;
}