#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <limits>
using namespace std;

// Smart Home Management System
// Concepts: classes, inheritance, polymorphism, encapsulation,
// constructors, virtual functions, vectors, and menu-driven programming.

class Device {
protected:
    int id;
    string name;
    bool isOn;
public:
    Device(int deviceId, const string& deviceName)
        : id(deviceId), name(deviceName), isOn(false) {}
    virtual ~Device() = default;

    int getId() const { return id; }
    string getName() const { return name; }
    bool getStatus() const { return isOn; }

    void turnOn() {
        isOn = true;
        cout << name << " is now ON.\n";
    }
    void turnOff() {
        isOn = false;
        cout << name << " is now OFF.\n";
    }
    virtual void displayDetails() const = 0;
    virtual void controlDevice() = 0;
};

class Light : public Device {
private:
    int brightness; // 0 to 100 percent
public:
    Light(int deviceId, const string& deviceName)
        : Device(deviceId, deviceName), brightness(70) {}

    void controlDevice() override {
        if (!isOn) {
            cout << "Turn the light ON before changing brightness.\n";
            return;
        }
        int value;
        cout << "Enter brightness (0-100): ";
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            return;
        }
        if (value < 0 || value > 100) {
            cout << "Brightness must be between 0 and 100.\n";
            return;
        }
        brightness = value;
        cout << name << " brightness set to " << brightness << "%.\n";
    }

    void displayDetails() const override {
        cout << "ID: " << id << " | Light: " << name
             << " | Status: " << (isOn ? "ON" : "OFF")
             << " | Brightness: " << brightness << "%\n";
    }
};

class Fan : public Device {
private:
    int speed; // 1 to 5
public:
    Fan(int deviceId, const string& deviceName)
        : Device(deviceId, deviceName), speed(3) {}

    void controlDevice() override {
        if (!isOn) {
            cout << "Turn the fan ON before changing speed.\n";
            return;
        }
        int value;
        cout << "Enter fan speed (1-5): ";
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            return;
        }
        if (value < 1 || value > 5) {
            cout << "Fan speed must be between 1 and 5.\n";
            return;
        }
        speed = value;
        cout << name << " speed set to " << speed << ".\n";
    }

    void displayDetails() const override {
        cout << "ID: " << id << " | Fan: " << name
             << " | Status: " << (isOn ? "ON" : "OFF")
             << " | Speed: " << speed << "/5\n";
    }
};

class AirConditioner : public Device {
private:
    int temperature; // 16 to 30 degrees Celsius
public:
    AirConditioner(int deviceId, const string& deviceName)
        : Device(deviceId, deviceName), temperature(24) {}

    void controlDevice() override {
        if (!isOn) {
            cout << "Turn the AC ON before changing temperature.\n";
            return;
        }
        int value;
        cout << "Enter temperature (16-30 C): ";
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            return;
        }
        if (value < 16 || value > 30) {
            cout << "Temperature must be between 16 and 30 C.\n";
            return;
        }
        temperature = value;
        cout << name << " temperature set to " << temperature << " C.\n";
    }

    void displayDetails() const override {
        cout << "ID: " << id << " | AC: " << name
             << " | Status: " << (isOn ? "ON" : "OFF")
             << " | Temperature: " << temperature << " C\n";
    }
};

class SmartHome {
private:
    vector<unique_ptr<Device>> devices;

    Device* findDevice(int deviceId) {
        for (auto& device : devices) {
            if (device->getId() == deviceId) return device.get();
        }
        return nullptr;
    }

    void showDevices() const {
        cout << "\n----- Smart Home Devices -----\n";
        for (const auto& device : devices) device->displayDetails();
        cout << "------------------------------\n";
    }

    void setDevicePower(bool turnOn) {
        int deviceId;
        cout << "Enter device ID: ";
        if (!(cin >> deviceId)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            return;
        }
        Device* device = findDevice(deviceId);
        if (!device) {
            cout << "Device not found.\n";
            return;
        }
        if (turnOn) device->turnOn();
        else device->turnOff();
    }

    void configureDevice() {
        int deviceId;
        cout << "Enter device ID to configure: ";
        if (!(cin >> deviceId)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            return;
        }
        Device* device = findDevice(deviceId);
        if (!device) {
            cout << "Device not found.\n";
            return;
        }
        device->controlDevice();
    }

public:
    SmartHome() {
        devices.push_back(make_unique<Light>(1, "Living Room Light"));
        devices.push_back(make_unique<Fan>(2, "Bedroom Fan"));
        devices.push_back(make_unique<AirConditioner>(3, "Living Room AC"));
    }

    void run() {
        int choice = -1;
        do {
            cout << "\n========== SMART HOME MANAGEMENT SYSTEM ==========\n";
            cout << "1. View all devices\n";
            cout << "2. Turn a device ON\n";
            cout << "3. Turn a device OFF\n";
            cout << "4. Configure a device\n";
            cout << "5. Turn ALL devices ON\n";
            cout << "6. Turn ALL devices OFF\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";

            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Please enter a valid number.\n";
                choice = -1;
                continue;
            }

            switch (choice) {
                case 1: showDevices(); break;
                case 2: setDevicePower(true); break;
                case 3: setDevicePower(false); break;
                case 4: configureDevice(); break;
                case 5:
                    for (auto& device : devices) device->turnOn();
                    break;
                case 6:
                    for (auto& device : devices) device->turnOff();
                    break;
                case 0:
                    cout << "Thank you for using Smart Home Management System.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    SmartHome home;
    home.run();
    return 0;
}
