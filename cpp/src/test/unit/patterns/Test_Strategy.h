/*
 * Test_Strategy.h
 *
 *  Created on: Jun 5, 2017
 *      Author: jyates
 */

#ifndef TESTING_PATTERNS_TEST_STRATEGY_H_
#define TESTING_PATTERNS_TEST_STRATEGY_H_

#include <sstream>
#include <cxxtest/TestSuite.h>

#include "../Types/StandardDefines.h"

#include "../../Patterns/Strategist.h"
#include "../../Patterns/Strategy.h"

class VehicleData {
public:
    int currentSpeed;
};

class Vehicle : public Strategy {
public:
    enum class VehicleType {
        UNDEFINED,
        VAN,
        CAR,
        BOAT,
        PLANE,
    };

    Vehicle(int maxSpeed = 0) : m_maxSpeed(maxSpeed) {}
    virtual ~Vehicle() {}

    void executeStrategy() {
        accelerate();
    }

    virtual void accelerate() = 0;

    int getCurrentSpeed() const {
        return m_data->currentSpeed;
    }

    int getMaxSpeed() const {
        return m_maxSpeed;
    }

    void setSharedState(std::shared_ptr<VehicleData> data) {
        m_data = data;
    }

protected:
    const int m_maxSpeed;
    std::shared_ptr<VehicleData> m_data;
};

class Van : public Vehicle {
public:
    Van() : Vehicle(50) {}
    virtual ~Van() {}

    virtual void accelerate() {
        std::stringstream stream("(Van) Current speed = ",
                std::ios::app|std::ios::out);
        m_data->currentSpeed = m_maxSpeed;
        stream << m_data->currentSpeed;
        TS_TRACE(stream.str().c_str());

    }

private:
};

class Car : public Vehicle {
public:
    Car() : Vehicle(100) {}

    virtual void accelerate() {
        std::stringstream stream("(Car) Current speed = ",
                std::ios::app|std::ios::out);
        m_data->currentSpeed = m_maxSpeed;
        stream << m_data->currentSpeed;
        TS_TRACE(stream.str().c_str());
    }

private:
};

class Boat : public Vehicle {
public:
    Boat() : Vehicle(75) {}

    virtual void accelerate() {
        std::stringstream stream("(Boat) Current speed = ",
                std::ios::app|std::ios::out);
        m_data->currentSpeed = m_maxSpeed;
        stream << m_data->currentSpeed;
        TS_TRACE(stream.str().c_str());
    }

private:
};

class Plane : public Vehicle {
public:
    Plane() : Vehicle(200) {}

    virtual void accelerate() {
        std::stringstream stream("(Plane) Current speed = ",
                std::ios::app|std::ios::out);
        m_data->currentSpeed = m_maxSpeed;
        stream << m_data->currentSpeed;
        TS_TRACE(stream.str().c_str());
    }
};

class Test_Strategy: public CxxTest::TestSuite {
public:
    Test_Strategy() :
        m_car(std::move(std::make_unique<Car>(Car()))),
        m_carData(std::make_shared<VehicleData>(VehicleData())),
        m_van(std::move(std::make_unique<Van>(Van()))),
        m_vanData(std::make_shared<VehicleData>(VehicleData())),
        m_boat(std::move(std::make_unique<Boat>(Boat()))),
        m_boatData(std::make_shared<VehicleData>(VehicleData())),
        m_plane(std::move(std::make_unique<Plane>(Plane()))),
        m_planeData(std::make_shared<VehicleData>(VehicleData())) {

        m_car->setSharedState(m_carData);
        m_van->setSharedState(m_vanData);
        m_boat->setSharedState(m_boatData);
        m_plane->setSharedState(m_planeData);
    }

    ~Test_Strategy() {}

    void setUp   () { }
    void tearDown() { }

    void testBasicErrors() {
        try {
            m_vehicleStrategist.switchStrategy(Vehicle::VehicleType::BOAT);
            TS_FAIL("No exception thrown when expected.");
        } catch (std::runtime_error& e) {
            // attempted to switch to a strategy set to a nullptr
            TS_ASSERT_EQUALS(VehicleStrategist::SWITCH_NULLPTR_ERR, e.what());
            TS_TRACE(std::string("Expectation found: ") + e.what());
        }

        try {
            std::unique_ptr<Boat> carPtr;
            m_vehicleStrategist.assignStrategy(Vehicle::VehicleType::BOAT,
                    std::move(carPtr));
            TS_FAIL("No exception thrown when expected.");
        } catch (std::invalid_argument& e) {
            // strategy passed in as nullptr
            TS_ASSERT_EQUALS(VehicleStrategist::PASSED_NULLPTR_ERR, e.what());
            TS_TRACE(std::string("Expectation found: ") + e.what());
        }

        try {
            m_vehicleStrategist.executeCurrentStrategy();
            TS_FAIL("No exception thrown when expected.");
        } catch (std::runtime_error& e) {
            // current strategy object is a nullptr
            TS_ASSERT_EQUALS(VehicleStrategist::CURRENT_NULLPTR_ERR, e.what());
            TS_TRACE(std::string("Expectation found: ") +
                    e.what());
        }
    }

    void testSwitchExecute() {
        int carMaxSpeed = m_car->getMaxSpeed();
        m_vehicleStrategist.assignStrategy(Vehicle::VehicleType::CAR,
                std::move(m_car));

        // try to set the another strategy of the same type again, error condition
        std::unique_ptr<Car> newCar = std::make_unique<Car>(Car());
        try {
            m_vehicleStrategist.assignStrategy(Vehicle::VehicleType::CAR,
                    std::move(newCar));
            TS_FAIL("No exception thrown when expected.");
        } catch (StrategyException& e) {
            TS_ASSERT(e.em_thrownStrategy != nullptr);
            TS_ASSERT_EQUALS(VehicleStrategist::OVERWRITE_ERR, e.what());
            TS_TRACE(std::string("Expectation found: ") +
                    e.what());
        }

        Vehicle::VehicleType oldStrat = m_vehicleStrategist.switchStrategy(
                Vehicle::VehicleType::CAR);
        TS_ASSERT_EQUALS(oldStrat, Vehicle::VehicleType::UNDEFINED);
        m_vehicleStrategist.executeCurrentStrategy();
        TS_ASSERT_EQUALS(m_carData->currentSpeed, carMaxSpeed);

        int vanMaxSpeed = m_van->getMaxSpeed();
        m_vehicleStrategist.assignStrategy(Vehicle::VehicleType::VAN,
                std::move(m_van));

        oldStrat = m_vehicleStrategist.switchStrategy(
                Vehicle::VehicleType::VAN);
        TS_ASSERT_EQUALS(oldStrat, Vehicle::VehicleType::CAR);

        TS_ASSERT(m_vanData->currentSpeed != vanMaxSpeed);
        m_vehicleStrategist.executeCurrentStrategy();
        TS_ASSERT_EQUALS(m_vanData->currentSpeed, vanMaxSpeed);
    }

    void testRemoveAndExecute() {
        m_vehicleStrategist.assignStrategy(Vehicle::VehicleType::PLANE,
                std::move(m_plane));

        m_vehicleStrategist.switchStrategy(Vehicle::VehicleType::PLANE);

        try {
            m_vehicleStrategist.unassignStrategy(Vehicle::VehicleType::PLANE);
            TS_FAIL("No exception thrown when expected.");
        } catch (std::runtime_error& e) {
            TS_ASSERT_EQUALS(VehicleStrategist::IN_USE_ERR, e.what());
            TS_TRACE(std::string("Expectation found: ") +
                    e.what());
        }

        m_vehicleStrategist.assignStrategy(Vehicle::VehicleType::BOAT,
                std::move(m_boat));
        Vehicle::VehicleType oldStrat = m_vehicleStrategist.switchStrategy(
                Vehicle::VehicleType::BOAT);
        TS_ASSERT_EQUALS(oldStrat, Vehicle::VehicleType::PLANE);

        std::unique_ptr<Strategy> removedStrat = std::move(
                m_vehicleStrategist.unassignStrategy(Vehicle::VehicleType::PLANE));
    }
private:
    std::unique_ptr<Car>  m_car;
    std::shared_ptr<VehicleData> m_carData;

    std::unique_ptr<Van>  m_van;
    std::shared_ptr<VehicleData> m_vanData;

    std::unique_ptr<Boat> m_boat;
    std::shared_ptr<VehicleData> m_boatData;

    std::unique_ptr<Plane> m_plane;
    std::shared_ptr<VehicleData> m_planeData;

    typedef Strategist<Vehicle::VehicleType,
        Vehicle::VehicleType::UNDEFINED,
        Vehicle::VehicleType::VAN,
        Vehicle::VehicleType::CAR,
        Vehicle::VehicleType::BOAT,
        Vehicle::VehicleType::PLANE> VehicleStrategist;
    VehicleStrategist m_vehicleStrategist;

};

#endif // TESTING_PATTERNS_TEST_STRATEGY_H_
