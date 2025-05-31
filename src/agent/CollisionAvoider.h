#pragma once

class Navigator;
class Vehicle;
class Driver;
class CollisionArea;


class CollisionAvoider
{
	Navigator* navigator_;
	Vehicle* vehicle_;
	Driver* driver_;
	CollisionArea* stoppingPoint_;
	

public:
	CollisionAvoider();
};

