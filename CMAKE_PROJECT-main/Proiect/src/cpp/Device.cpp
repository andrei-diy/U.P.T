#include "Device.hpp"
#include <iostream>
//class User;
class Device;//ublic class Device;

Device::Device(int sn, int device_type){
    this->SN = sn;
    this->device_type = device_type;
    this->booked = false;
    this->id_user = 0;
    std::cout<<"Device < "<<sn<<" > created\n";
}
Device::Device(int sn, int device_type, int user){
    this->id_user = user;
    this->SN = sn;
    this->device_type = device_type;
    this->booked = true;
    std::cout<<"Device < "<<sn<<" > created\n";
}
 Device::Device(const Device& d){
    this->device_type = d.device_type;
    this->SN = d.SN;
    this->id_user = d.id_user;
    this->booked = d.booked;
    std::cout<<"Device < "<<this->SN<<" > was copied\n";
}
Device::~Device(){
    std::cout<<"Device < "<<this->SN<<" > has been deleted\n";
}
bool Device::operator==(Device d){
    if((d.getType() == device_type)&&(d.getSN() == SN)) 
        return true;
    else return false;
}


bool Device::isFree(){
    return this->booked;
}
int Device::getType(){
    return this->device_type;
}
int Device::getSN(){
    return this->SN;
}
int Device::getIDUser(){
    return this->id_user;
}
void Device::setSN(int sn){
    this->SN = sn;
}
void Device::setUser(int user){
    this->id_user = user;
}
void Device::setStatus(bool status){
    this->booked = status;
}


