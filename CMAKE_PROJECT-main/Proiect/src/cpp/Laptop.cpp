/*
class derived-class : access base-class {
    body of new class
}
*/
#include "Device.cpp"

class Laptop : public Device{
    int memory;
    int powerConsumption;
    char* name;
public:
    Laptop(int SN,int device_type,int id_user,char* name,int memory,int powerConsumption);
    void setInfo(int memory, int powerConsumption, char* name);
};

Laptop::Laptop(int SN,int device_type,int id_user,char* name,int memory,int powerConsumption)
:Device(SN, device_type, id_user){
    this->name = name;
    this->memory = memory;
    this->powerConsumption = powerConsumption;
}
void Laptop::setInfo(int memory, int powerConsumption, char* name){
    this->memory = memory;
    this->powerConsumption = powerConsumption;
    this->name = name;
}
