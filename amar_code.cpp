#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Apartment
{
private:
    int aptNumber;
    bool isOccupied;
    float rent;
    float electricityBill;
    float gasBill;
    float waterBill;
    float maintainance;
    bool isSecurityCameraNeeded;

public:
    Apartment(int aptnumber)
    {
        this->aptNumber = aptnumber;
        this->rent = 0;
        this->isOccupied = false;
        this->electricityBill = 0;
        this->gasBill = 0;
        this->waterBill = 0;
        this->maintainance = 0;
        this->isSecurityCameraNeeded = false;
    };
    Apartment(int aptnumber, float rent, float electricityBill, float gasBill, float waterBill, float maintainance = 0)
    {
        this->aptNumber = aptnumber;

        this->rent = rent;
        this->electricityBill = electricityBill;
        this->gasBill = gasBill;
        this->waterBill = waterBill;
        this->maintainance = maintainance;
    }

    int getAptNumber()
    {
        return aptNumber;
    }

    bool getIsOccupied()
    {
        return isOccupied;
    }

    void setIsOccupied(bool isOccupied)
    {
        this->isOccupied = isOccupied;
    }

    float getRent()
    {
        return rent;
    }

    float getElectricityBill()
    {
        return electricityBill;
    }

    float getGasBill()
    {
        return gasBill;
    }

    float getWaterBill()
    {
        return waterBill;
    }
    float getTotal()
    {
        return (rent + electricityBill + waterBill + gasBill + maintainance);
    }

    bool getIsSecurityCameraNeeded()
    {
        return isSecurityCameraNeeded;
    }

    void setIsSecurityCameraNeeded(bool isSecurityCameraNeeded)

    {
        this->isSecurityCameraNeeded = isSecurityCameraNeeded;
    }
    void addmaintainance(float extra)
    {
        maintainance += extra;
    }
    friend class BuildingManager; // allow BuildingManager to access private members of Apartment class
};

class Tenant
{
private:
    string name;
    int aptNumber;

public:
    Tenant(string name, int aptNumber)
    {
        this->name = name;
        this->aptNumber = aptNumber;
    }

    string getName()
    {
        return name;
    }

    int getAptNumber()
    {
        return aptNumber;
    }
};

class BuildingManager
{
private:
    vector<Apartment> apartments;

public:
    BuildingManager(int count)
    {
        for (int i = 0; i < count; i++)
        {
            apartments.push_back(Apartment(i + 1));
        }
    };

    void bill_generate(int aptNumber)
    {
        float rent, elbill, gasbill, waterbill;
        if (aptNumber > 0 && aptNumber <= apartments.size())
        {
            Apartment &apt = apartments[aptNumber - 1];
            if (apt.getIsOccupied())
            {
                cout << "Enter your electric bill (in taka): ";
                cin >> elbill;
                cout << "Enter your gas bill (in taka): ";
                cin >> gasbill;
                cout << "Enter your water bill (in taka): ";
                cin >> waterbill;
                apt = (Apartment(aptNumber, 1200, elbill, gasbill, waterbill));
            }
            else
            {
                cout << "Apartment " << aptNumber << " is vacant." << endl;
            }
        }
        else
        {
            cout << "Invalid apartment number." << endl;
        }
    }

    int getNumApartments()
    {
        return apartments.size();
    }

    void rentApartment(int aptNumber)
    {
        if (aptNumber > 0 && aptNumber <= apartments.size())
        {
            Apartment &apt = apartments[aptNumber - 1];
            if (!apt.getIsOccupied())
            {
                apt.setIsOccupied(true);
                cout << "Apartment " << aptNumber << " has been rented." << endl;
            }
            else
            {
                cout << "Apartment " << aptNumber << " is already occupied." << endl;
            }
        }
        else
        {
            cout << "Invalid apartment number." << endl;
        }
    }

    void freeApartment(int aptNumber)
    {
        if (aptNumber > 0 && aptNumber <= apartments.size())
        {
            Apartment &apt = apartments[aptNumber - 1];
            if (apt.getIsOccupied())
            {
                apt.setIsOccupied(false);
                cout << "Apartment " << aptNumber << " has been freed." << endl;
            }
            else
            {
                cout << "Apartment " << aptNumber << " is already vacant." << endl;
            }
        }
        else
        {
            cout << "Invalid apartment number." << endl;
        }
    }

    void requestRepair(int aptNumber, int cost = 200)
    {
        if (aptNumber > 0 && aptNumber <= apartments.size())
        {
            Apartment &apt = apartments[aptNumber - 1];
            apt.addmaintainance(cost);
            cout << "Repair successful for apartment " << aptNumber << "." << endl;
        }
        else
        {
            cout << "Invalid apartment number." << endl;
        }
    }

    void requestPaint(int aptNumber, int cost)
    {
        if (aptNumber > 0 && aptNumber <= apartments.size())
        {

            Apartment &apt = apartments[aptNumber - 1];
            apt.addmaintainance(cost);
            cout << "Successfully painted apartment " << aptNumber << "." << endl;
        }
        else
        {
            cout << "Invalid apartment number." << endl;
        }
    }

    void requestSecurityCamera(int aptNumber)
    {
        if (aptNumber > 0 && aptNumber <= apartments.size())
        {
            Apartment &apt = apartments[aptNumber - 1];
            if (!apt.getIsSecurityCameraNeeded())
            {
                apt.setIsSecurityCameraNeeded(true);
                apt.addmaintainance(5000);
                cout << "Security camera has succesfully added " << aptNumber << "." << endl;
            }
            else
            {
                cout << "Security camera has already added for apartment " << aptNumber << "." << endl;
            }
        }
        else
        {
            cout << "Invalid apartment number." << endl;
        }
    }

    void showApartmentStatus(int aptNumber)
    {
        if (aptNumber > 0 && aptNumber <= apartments.size())
        {
            Apartment &apt = apartments[aptNumber - 1];
            cout << "Apartment " << aptNumber << ":" << endl
                 << "- Occupied: ";
            if (apt.getIsOccupied())
                cout << "YES";
            else
            {
                cout << "NO";
            }
            cout << endl
                 << "- Rent: " << apt.getRent() << endl
                 << "- Electricity bill: " << apt.getElectricityBill() << endl
                 << "- Gas bill: " << apt.getGasBill() << endl
                 << "- Water bill: " << apt.getWaterBill() << endl
                 << "- Total :" << apt.getTotal() << endl;
        }
        else
        {
            cout << "Invalid apartment number." << endl;
        }
    }

    friend class TenantManager; // allow TenantManager to access private members of BuildingManager class
};

class TenantManager
{
private:
    vector<Tenant> tenants;

public:
    TenantManager() {}

    void addTenant(string name, int aptNumber, BuildingManager &buildingManager)
    { // pass reference to BuildingManager object
        if (aptNumber > 0 && aptNumber <= buildingManager.getNumApartments())
        {
            Apartment &apt = buildingManager.apartments[aptNumber - 1];
            if (!apt.getIsOccupied())
            {                                               // check if apartment is vacant
                tenants.push_back(Tenant(name, aptNumber)); // add tenant to list
                buildingManager.rentApartment(aptNumber);   // rent the apartment using the BuildingManager object
                cout << "Tenant added successfully." << endl;
            }
            else
            { // apartment is already occupied
                cout << "Apartment is already occupied." << endl;
            }
        }
        else
        { // invalid apartment number
            cout << "Invalid apartment number." << endl;
        }
    }

    void removeTenant(string name, BuildingManager &buildingManager)
    {                   // pass reference to BuildingManager object
        int index = -1; // initialize index to -1
        for (int i = 0; i < tenants.size(); i++)
        { // loop through tenants list
            if (tenants[i].getName() == name)
            {              // check if name matches
                index = i; // set index to current position in list
                break;     // exit loop
            }
        }
        if (index != -1)
        {                                                  // check if name was found in list
            int aptNumber = tenants[index].getAptNumber(); // get apartment number from tenant object
            buildingManager.freeApartment(aptNumber);      // free the apartment using the BuildingManager object
            tenants.erase(tenants.begin() + index);        // remove tenant from list using iterator arithmetic
            cout << "Tenant removed successfully." << endl;
        }
        else
        { // name was not found in list
            cout << "Tenant not found." << endl;
        }
    }

    friend class BuildingManager; // allow BuildingManager to access private members of TenantManager class
};

int main()
{
    BuildingManager building(10);
    TenantManager tenants;
    int ch;
    string name;
    float cost;
    cout << "**********House Management System**********" << endl;
A:
    cout << "1.Add tenant" << endl
         << "2.Free Apartment" << endl
         << "3.Appartment Status" << endl
         << "4.Generate bill" << endl
         << "5.Maintainance" << endl
         << "press(1/2/3/4): ";
    cin >> ch;
    switch (ch)
    {
    case 1:
        cout << "Enter tenant's name: " << endl;
        cin >> name;
        cout << "Enter apartment number" << endl;
        cin >> ch;
        tenants.addTenant(name, ch, building);
        goto A;
        break;
    case 2:
        cout << "Enter tenant's name: " << endl;
        cin >> name;
        tenants.removeTenant(name, building);
        goto A;
        break;
    case 3:
        cout << "Enter apartment number" << endl;
        cin >> ch;
        building.showApartmentStatus(ch);
        goto A;

    case 4:
        cout << "Enter apartment number" << endl;
        cin >> ch;
        building.bill_generate(ch);
        goto A;
        break;
    case 5:
        cout << "1.Repair house" << endl
             << "2.Paint house" << endl
             << "3.Add security camara" << endl
             << "press(1/2/3): ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "Enter apartment number :" << endl;
            cin >> ch;

            cout << "Enter Amount :";
            cin >> cost;
            building.requestRepair(ch, cost);
            break;
        case 2:
            cout << "Enter apartment number :" << endl;
            cin >> ch;

            cout << "Enter Amount :";
            cin >> cost;
            building.requestPaint(ch, cost);
            break;
        case 3:
            cout << "Enter apartment number :" << endl;
            cin >> ch;
            building.requestSecurityCamera(ch);
            break;
        default:
            cout << "Invalid Input!!";
            break;
        }

        goto A;
        break;
    default:
        cout << "Invalid Input!!";
        goto A;
        break;
    }

    return 0;
}
