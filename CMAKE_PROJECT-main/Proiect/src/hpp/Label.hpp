#ifndef Label_HPP
#define Label_HPP

#include <string>
using namespace std;

namespace Booking{
class Label{ 
    public:
        virtual void printLabel() = 0; 
};
class AVLabel : public Label{
    //void printLabel();
};

class BLabel : public Label{
    private:
        string text;
        string ISBN;
    public:
        BLabel(string,string);
        ~BLabel();
        BLabel(const BLabel&);
        BLabel(BLabel&&);
   public:
        void setText(string);
        void setISBN(string);

        string getText();
        string getISBN();
        void printLabel();
        BLabel operator=(BLabel);
        BLabel& operator==(BLabel&&);
};

}
//namespace Label

#endif