#ifndef PERSON_H
#define PERSON_H
#include <string>

using namespace std;

class Person
{
    public:
        Person();
        ~Person();
        bool login(string,string);

    protected:
        int id ;
        string name;
        int age;
        bool gender;
        string userName;
        string password;
        string phoneNumber;

    private:
};

#endif // PERSON_H
