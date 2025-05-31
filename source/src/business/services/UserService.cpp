#include "UserService.h"
#include "BookingService.h"

UserService::UserService(std::shared_ptr<IUserRepository> userRepository, std::shared_ptr<BookingService> bookingService)
    : _userRepository(userRepository), _bookingService(bookingService)
{
}

std::vector<User> UserService::getAllUsers()
{
    return _userRepository->getAll();
}

std::optional<User> UserService::getUserById(int id)
{
    return _userRepository->getById(id);
}

std::vector<User> UserService::findUsersByName(const std::string &name)
{
    return _userRepository->findByName(name);
}

bool UserService::addUser(const User &user)
{
    return _userRepository->add(user);
}

bool UserService::updateUser(const User &user)
{
    return _userRepository->update(user);
}

bool UserService::deleteUser(int id)
{
    // Check if there are any bookings for this user
    if (_bookingService && hasUserBookings(id))
    {
        // Can't delete a user that has bookings
        return false;
    }
    return _userRepository->remove(id);
}

bool UserService::hasUserBookings(int userId)
{
    if (!_bookingService)
    {
        return false;
    }
      auto bookings = _bookingService->findBookingsByUserId(userId);
    return !bookings.empty();
}