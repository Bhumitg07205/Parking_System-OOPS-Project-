#include<iostream>
#include<ctime>
#include<vector>

using namespace std;

static int count = 0;

class Customer {
    string name;
    string phone;

public:
    Customer() {
        cin.ignore();
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter phone number: ";
        getline(cin, phone);
    }

    string getName() {
        return name;
    }

    string getPhone() {
        return phone;
    }
};

class Vehicle : public Customer {
    string carNo;
    int slotNo, ticketNo, billNo, charges;
    time_t entryTime, exitTime;

public:
    void getTicket(int slot) {
        slotNo = slot;
        cout << "Enter car number: ";
        getline(cin, carNo);
        entryTime = time(0);
        count++;
        ticketNo = count;
        system("cls");
        displayTicket();
    }

    void displayTicket() {
        cout << "************************ Bhumit's CAR PARKING TICKET ************************";
        cout << "\n\nTicket number: " << ticketNo;
        cout << "\nCar Number: " << carNo;
        cout << "\nEntry Time: " << ctime(&entryTime);
        cout << "\nParking Spot: " << slotNo;
        cout << "\nCurrent Status: UNPAID";
        cout << "\n\nEnter any key to go back to main menu..";
        getchar();
        system("cls");
    }

    void getBill() {
        exitTime = time(0);
        billNo = ticketNo;
        calculateCharges();
    }

    int getTicketNo() {
        return ticketNo;
    }

    int getSlot() {
        return slotNo;
    }

    void calculateCharges() {
        long long duration = exitTime - entryTime;
        int mins = duration / 60;
        int hours = mins / 60;
        int extraMin = mins % 60;

        if (hours == 0 && extraMin <= 30) {
            charges = 20;
        } else if (hours <= 2 && extraMin == 0) {
            charges = 55;
        } else if (hours <= 7) {
            charges = 55 + (hours - 2) * 10;
        } else {
            charges = 165;
        }
        displayBill();
    }

    void displayBill() {
        cout << "********************** Bhumit's CAR PARKING BILL **********************";
        cout << "\n\nBill Number: " << billNo;
        cout << "\nCar Number: " << carNo;
        cout << "\nParking Spot: " << slotNo;
        cout << "\nEntry Time: " << ctime(&entryTime);
        cout << "\nExit Time: " << ctime(&exitTime);
        cout << "\nTotal Charges: Rs. " << charges << "/-";
        cout << "\nCurrent Status: PAID";
        cout << "\n\nEnter any key to go back to main menu..";
        getchar();
    }
};

class ParkingLot {
    int capacity;
    int totalFilled;
    vector<bool> parkingSpaces;
    vector<Vehicle> vehicles;

public:
    ParkingLot() {
        capacity = 100;
        totalFilled = 0;
        parkingSpaces.resize(capacity, false);
    }

    bool ifSlotAvailable() {
        return totalFilled < capacity;
    }

    int getFreeSlot() {
        for (int i = 0; i < capacity; ++i) {
            if (!parkingSpaces[i]) {
                parkingSpaces[i] = true;
                totalFilled++;
                return i + 1;
            }
        }
        return -1;
    }

    void newVehicle(Vehicle& v) {
        vehicles.push_back(v);
    }

    void deleteVehicle(int slot) {
        parkingSpaces[slot - 1] = false;
        totalFilled--;
    }

    Vehicle findDepartingCar(int ticketNo) {
        for (Vehicle& v : vehicles) {
            if (v.getTicketNo() == ticketNo) {
                return v;
            }
        }
        return vehicles[0];
    }

    int getCapacity() {
        return capacity;
    }

    int getTotalFilled() {
        return totalFilled;
    }

    void emptyParkingSpotsList() {
        for (int i = 0; i < parkingSpaces.size(); ++i) {
            if (!parkingSpaces[i]) {
                cout << i + 1 << ", ";
            }
        }
    }

    void occupiedParkingSpotsList() {
        for (int i = 0; i < parkingSpaces.size(); ++i) {
            if (parkingSpaces[i]) {
                cout << i + 1 << ", ";
            }
        }
    }
};

void carArrival(ParkingLot& pl) {
    if (pl.ifSlotAvailable()) {
        int slot = pl.getFreeSlot();
        Vehicle v;
        v.getTicket(slot);
        pl.newVehicle(v);
    } else {
        cout << "Sorry, no empty parking space available!" << endl;
    }
}

void carDeparture(ParkingLot& pl) {
    if (pl.getTotalFilled() == 0) {
        cout << "No cars available in your parking lot." << endl;
        getchar();
        return;
    }

    int ticketNo;
    cout << "Enter ticket number: ";
    cin >> ticketNo;
    cin.ignore();

    Vehicle departingCar = pl.findDepartingCar(ticketNo);
    pl.deleteVehicle(departingCar.getSlot());
    system("cls");
    departingCar.getBill();
}

void displayDetails(ParkingLot& pl) {
    cout << "\n\n1. Get the total capacity of Parking Lot";
    cout << "\n2. Get total number of occupied parking spots";
    cout << "\n3. Get total number of empty parking spots";
    cout << "\n4. Get list of empty parking spots";
    cout << "\n5. Get list of occupied parking spots";
    cout << "\n6. Get the total number of parkings";
    cout << "\n7. Exit";

    int choice;
    do {
        cout << "\nEnter your choice: ";
        cin >> choice;
        if (choice < 1 || choice > 7) {
            cout << "\nInvalid input, try again." << endl;
        } else {
            break;
        }
    } while (true);

    system("cls");

    switch (choice) {
    case 1:
        cout << "\nThe capacity of parking lot is " << pl.getCapacity() << endl;
        break;
    case 2:
        cout << "\nThe number of occupied parking spots is " << pl.getTotalFilled() << endl;
        break;
    case 3:
        cout << "\nThe number of empty parking spots is " << pl.getCapacity() - pl.getTotalFilled() << endl;
        break;
    case 4:
        cout << "\nList of empty parking spots: ";
        pl.emptyParkingSpotsList();
        break;
    case 5:
        cout << "\nList of occupied parking spots: ";
        pl.occupiedParkingSpotsList();
        break;
    case 6:
        cout << "\nThe total number of parkings: " << count << endl;
        break;
    case 7:
        return;
    default:
        cout << "Invalid choice!" << endl;
        break;
    }

    cout << "\nPress any key to return to main menu...";
    getchar();
}

int main() {
    ParkingLot pl;
    int choice;
    do {
        system("cls");
        cout << "*************************** CAR PARKING MANAGEMENT SYSTEM ***************************";
        cout << "\n\n1. Arrival of a car";
        cout << "\n2. Departure of a car";
        cout << "\n3. Display details";
        cout << "\n4. Exit";
        cout << "\nSelect an option (1,2 or 3): ";
        cin >> choice;

        while (choice < 1 || choice > 4) {
            system("cls");
            cout << "Invalid Choice!!";
            cout << "\n\n1. Arrival of a car";
            cout << "\n2. Departure of a car";
            cout << "\n3. Display details";
            cout << "\n4. Exit";
            cout << "\nSelect an option (1,2,3 or 4): ";
            cin >> choice;
        }
        system("cls");

        switch (choice) {
        case 1:
            carArrival(pl);
            break;
        case 2:
            carDeparture(pl);
            break;
        case 3:
            displayDetails(pl);
            break;
        case 4:
            exit(0);
        default:
            cout << "Invalid Choice!" << endl;
            break;
        }
    } while (true);

    return 0;
}
