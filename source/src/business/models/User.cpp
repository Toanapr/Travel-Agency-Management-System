#include "User.h"

User::User(int id, const std::string &name, const std::string &address,
           const std::string &phone, const std::string &email)
    : _id(id), _name(name), _address(address), _phone(phone), _email(email)
{
}

int User::getId() const
{
    return _id;
}

std::string User::getName() const
{
    return _name;
}

std::string User::getAddress() const
{
    return _address;
}

std::string User::getPhone() const
{
    return _phone;
}

std::string User::getEmail() const
{
    return _email;
}

void User::setName(const std::string &name)
{
    _name = name;
}

void User::setAddress(const std::string &address)
{
    _address = address;
}

void User::setPhone(const std::string &phone)
{
    _phone = phone;
}

void User::setEmail(const std::string &email)
{
    _email = email;
}