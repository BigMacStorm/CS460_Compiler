#ifndef __ITCKET_CNT_H__
#define __ITCKET_CNT_H__

class intRegister{
    public:
        intRegister();
        ~intRegister();
        std::string create();
    private:
        std::string currentReg;
        void incReg();
};

class floatRegister{
    public:
        floatRegister();
        ~floatRegister();
        std::string create();
    private:
        std::string currentReg;
        void incReg();
};


intRegister::intRegister(){
    
}
std::string intRegister::create(){
}
void intRegister::incReg(){
}

