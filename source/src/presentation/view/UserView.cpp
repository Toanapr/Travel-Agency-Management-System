#include "UserView.h"

UserView::UserView(std::shared_ptr<OutputFormatter> outputFormatter)
    : _outputFormatter(outputFormatter)
{
}

void UserView::displayUserDetails(const User &user) const
{
    _outputFormatter->displayUser(user);
}

void UserView::displayAllUsers(const std::vector<User> &users) const
{
    _outputFormatter->displayUsers(users);
}