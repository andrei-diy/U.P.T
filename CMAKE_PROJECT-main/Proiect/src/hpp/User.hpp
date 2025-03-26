#ifndef USER_HPP
#define USER_HPP

//namespace BookingAPP {
class Base_User{
    public:
        virtual void printID() = 0; 
};

class User : public Base_User{
    private:
        int id;
        char* nume;
    public:
        User();
        User(int,char*);

        User(const User&);
        User(User&&);
        
        ~User();
   public:
        void setID(int);
        void setNume(char*);

        int getID();
        char* getNume();

        void printID();
};

//} // namespace BookingAPP

#endif // USER__APP