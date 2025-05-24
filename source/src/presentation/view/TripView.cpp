#include "TripView.h"

TripView::TripView(std::shared_ptr<OutputFormatter> outputFormatter)
    : _outputFormatter(outputFormatter)
{
}

void TripView::displayTripDetails(const Trip &trip) const
{
    _outputFormatter->displayTrip(trip);
}

void TripView::displayAllTrips(const std::vector<Trip> &trips) const
{
    _outputFormatter->displayTrips(trips);
}