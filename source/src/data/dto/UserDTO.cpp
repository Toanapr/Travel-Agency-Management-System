#include "UserDTO.h"

UserDTO::UserDTO() : _id(0), _name(""), _address(""), _phone(""), _email("")
{
}

UserDTO::UserDTO(int id, const std::string &name, const std::string &address,
                 const std::string &phone, const std::string &email)
    : _id(id), _name(name), _address(address), _phone(phone), _email(email)
{
}

int UserDTO::getId() const
{
    return _id;
}

const std::string &UserDTO::getName() const
{
    return _name;
}

const std::string &UserDTO::getAddress() const
{
    return _address;
}

const std::string &UserDTO::getPhone() const
{
    return _phone;
}

const std::string &UserDTO::getEmail() const
{
    return _email;
}

void UserDTO::setId(int id)
{
    _id = id;
}

void UserDTO::setName(const std::string &name)
{
    _name = name;
}

void UserDTO::setAddress(const std::string &address)
{
    _address = address;
}

void UserDTO::setPhone(const std::string &phone)
{
    _phone = phone;
}

void UserDTO::setEmail(const std::string &email)
{
    _email = email;
}