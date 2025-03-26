#include <User.hpp>
#include <iostream> 
#include <string>
#include <cstring>

User::User(int id, char* nume){ 
    this->id = id;
    this->nume = nume;
    std::cout<<"User created\n";
}
User::User(const User& user){
    int length = strlen(user.nume);
    this->nume = new char[length];
    memcpy(this->nume, user.nume,length);
    this->id = user.id;
    std::cout<<"Copy of user  created\n";
}
User::User( User&& user){
    this->nume = user.nume;
    this->id = user.id;
    std::cout<<"Shallow copy of user  created\n";

    user.nume = nullptr;
}
User::~User(){
    
    //delete []nume;
    std::cout<<"User <  >deleted\n";
}

void User::setID(int id){
    this->id = id;
}
void User::setNume(char* nume){
    int length = strlen(nume);
    this->nume = new char[length];
    memcpy(this->nume,nume,length);
}
int User::getID(){
    return this->id;
}
char* User::getNume(){
    return this->nume;
}
void User::printID(){
    std::cout<<"Display user "<< this->getID()<<"\n";
}