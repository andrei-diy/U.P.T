#ifndef DEVICE_HPP
#define DEVICE_HPP

/*namespace BookingAPP {*/

    class Device{

    private:

        int device_type;
        int SN;
        bool booked;
        int id_user;


    public:
        Device();
        Device(int,int);
        Device(int,int,int);
    
        Device(const Device&);

        ~Device();

    public:
        bool isFree();
        int getType();
        int getIDUser();
        int getSN();

        void setSN(int);
        void setUser(int);
        void setStatus(bool);
        bool operator==(Device);

};

/*} // namespace BookingAPP*/

#endif // DEVICE__APP
