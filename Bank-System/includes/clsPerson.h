#pragma once
#include "InterfaceCommunication.h"
#include <iostream>
#include <string>
using namespace std;

class clsPerson : public InterfaceCommunication
{

private:

    string _FirstName;
    string _LastName;
    string _Email;
    string _Phone;

public:

    clsPerson(string FirstName, string LastName, string Email, string Phone)
    {

        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;
    }

    void SetFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }

    string GetFirstName()
    {
        return _FirstName;
    }

    __declspec(property(get = GetFirstName, put = SetFirstName)) string FirstName;

    void SetLastName(string LastName)
    {
        _LastName = LastName;
    }

    string GetLastName()
    {
        return _LastName;
    }

    __declspec(property(get = GetLastName, put = SetLastName)) string LastName;

    void SetEmail(string Email)
    {
        _Email = Email;
    }

    string GetEmail()
    {
        return _Email;
    }

    __declspec(property(get = GetEmail, put = SetEmail)) string Email;

    void SetPhone(string Phone)
    {
        _Phone = Phone;
    }

    string GetPhone()
    {
        return _Phone;
    }

    __declspec(property(get = GetPhone, put = SetPhone)) string Phone;

    string FullName()
    {
        return _FirstName + " " + _LastName;
    }

    void SendEmail(string Title, string Body)
    {

    }

    void SendFax(string Title, string Body)
    {

    }

    void SendSMS(string Title, string Body)
    {


    }
};

/*

	An abstract class in C++ is a class that contains at least one pure virtual function.
	It cannot be instantiated (i.e., you cannot create objects from it directly).
	It is typically used as a base class to enforce a common interface for multiple derived classes.




	Case		Abstract?		Can Create Object?	Must Override in Derived Class?
	With = 0		✅ Yes		❌ No					✅ Yes
	Without = 0		❌ No		✅ Yes					❌ No
*/


/*

	A virtual function is a function that is declared in a base class but is meant to be overridden in derived classes. When we call the function using a base class pointer or reference, 
	the version of the function in the derived class will be executed (if it exists)



*/