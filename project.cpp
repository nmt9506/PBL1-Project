#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;
class DateTime
{
public:
    time_t now = time(0);
    char *dt = ctime(&now);
    void orderDateTime()
    {
        cout << "DateTime: " << dt;
    }
};
class Person
{
protected:
    string name, phoneNumber, address;
    int age;

public:
    Person()
    {
        this->name = "";
        this->age = 0;
        this->phoneNumber = "";
        this->address = "";
    }
    Person(string name, int age, string phoneNumber, string address)
    {
        this->name = name;
        this->age = age;
        this->phoneNumber = phoneNumber;
        this->address = address;
    }
    ~Person() {}
    void inputPersonInfo()
    {
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter age: ";
        cin >> age;
        cout << "Enter phone number: ";
        cin.ignore();
        getline(cin, phoneNumber);
        cout << "Enter address: ";
        getline(cin, address);
    }
    void displayPersonInfo() const
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "PhoneNumber: " << phoneNumber << endl;
        cout << "Address: " << address << endl;
    };
    string getName() const
    {
        return name;
    }
    int getAge() const
    {
        return age;
    }
    string getPhoneNumber() const
    {
        return phoneNumber;
    }
    string getAddress() const
    {
        return address;
    }
};
class Employee : public Person
{
private:
    string employeeID;
    int workingDays;
    long long salaryPerMonth;

public:
    Employee()
    {
        this->employeeID = "";
        this->workingDays = 0;
        this->salaryPerMonth = 0;
    }
    Employee(string employeeID, string name, int age, string phoneNumber, string address, int workingDays, long long salaryPerMonth) : Person(name, age, phoneNumber, address)
    {
        this->employeeID = employeeID;
        this->workingDays = workingDays;
        this->salaryPerMonth = salaryPerMonth;
    }
    Employee(string employeeID, string name, int age, string phoneNumber, string address) : Person(name, age, phoneNumber, address)
    {
        this->employeeID = employeeID;
    }
    ~Employee() {}
    string getEmployeeID() const
    {
        return employeeID;
    }
    void setEmployeeID(string id)
    {
        employeeID = id;
    }
    void setName(string n)
    {
        name = n;
    }
    void setAge(int a)
    {
        age = a;
    }
    void setPhoneNumber(string pN)
    {
        phoneNumber = pN;
    }
    void setAddress(string addr)
    {
        address = addr;
    }
    void inputEmployeeInfo()
    {
        cout << "Enter employeeID: ";
        cin.ignore();
        getline(cin, employeeID);
        Person::inputPersonInfo();
    }
    void displayEmployeeInfo()
    {
        cout << "EmployeeID: " << employeeID << endl;
        Person::displayPersonInfo();
    }
    void inputWorkingDays()
    {
        cout << "Enter working days for employee " << employeeID << " : ";
        cin >> workingDays;
    }
    long long calculateSalary(long long salary = 5600000, int days = 26)
    {
        return salaryPerMonth = salary / float(days) * float(workingDays);
    }
};
class Product
{
protected:
    string productID, productName;
    int stockQuantity;
    long long price;

public:
    Product()
    {
        this->productID = this->productName = "";
        this->stockQuantity = 0;
        this->price = 0;
    }
    Product(string productID, string productName, int stockQuantity, long long price)
    {
        this->productID = productID;
        this->productName = productName;
        this->stockQuantity = stockQuantity;
        this->price = price;
    }
    ~Product()
    {
        this->productID = this->productName = "";
        this->stockQuantity = 0;
        this->price = 0;
    }
    string getProductID()
    {
        return productID;
    }
    string getProductName()
    {
        return productName;
    }
    int getStockQuantity()
    {
        return stockQuantity;
    }
    long long getPrice()
    {
        return price;
    }
    void setProductID(string id)
    {
        this->productID = id;
    }
    void setProductName(string name)
    {
        this->productName = name;
    }
    void setStockQuantity(int qty)
    {
        this->stockQuantity = qty;
    }
    void setPrice(long long price)
    {
        this->price = price;
    }
    int decreaseStockQuantity(int qty)
    {
        return stockQuantity -= qty;
    }
    int increaseStockQuantity(int qty)
    {
        return stockQuantity += qty;
    }
    void inputProductInfo()
    {
        cout << "Enter productID: ";
        cin.ignore();
        getline(cin, productID);
        cout << "Enter product name: ";
        getline(cin, productName);
        cout << "Enter stock quantity: ";
        cin >> stockQuantity;
        cout << "Enter price: ";
        cin >> price;
    }
    void displayProductInfo()
    {
        cout << "ProductID: " << productID << endl;
        cout << "Product name: " << productName << endl;
        cout << "Stock quantity of product: " << stockQuantity << endl;
        cout << "Product price: " << price << endl;
    }
};
class IceCreamStore
{
protected:
    Employee *listEmployee;
    int employeeCount;
    Product *listProduct;
    int productCount;

public:
    IceCreamStore()
    {
        this->listEmployee = nullptr;
        this->listProduct = nullptr;
    }
    IceCreamStore(int employeeCount, int productCount)
    {
        this->listEmployee = new Employee[employeeCount];
        this->listProduct = new Product[productCount];
    }
    ~IceCreamStore()
    {
        delete[] listEmployee;
        delete[] listProduct;
    }
    int countProduct()
    {
        // đọc file để lấy giá trị count (đếm số sản phẩm)
        ifstream is_1("stockmanager.txt");
        if (!is_1.is_open())
        {
            cout << "Can not open file stockmanager.txt" << endl;
            return 0;
        }
        int count = 0;
        string productID, productName;
        int stockQuantity;
        long long price;
        while (is_1 >> productID >> productName >> stockQuantity >> price)
        {
            count++;
        }
        is_1.close();
        return count;
    }
    void displayListProduct()
    {
        cout << "\n----------Product List----------" << endl;
        ifstream in("stockmanager.txt");
        if (!in.is_open())
        {
            cout << "Cannot open file stockmanager.txt !" << endl;
            return;
        }
        productCount = countProduct();
        string productID, productName;
        int stockQuantity;
        long long price;
        listProduct = new Product[productCount];
        for (int i = 0; i < productCount; i++)
        {
            in >> productID >> productName >> stockQuantity >> price;
            listProduct[i] = Product(productID, productName, stockQuantity, price);
            cout << "[" << i + 1 << "] " << endl;
            listProduct[i].displayProductInfo();
            cout << "-----------------------------------" << endl;
        }
        in.close();
    }
    bool checkIDProduct(string id, Product &product)
    {
        string productID, productName;
        int stockQuantity;
        long long price;
        ifstream in("stockmanager.txt");
        if (!in.is_open())
        {
            cout << "Can not open file stockmanager.txt" << endl;
            return false;
        }
        while (in >> productID >> productName >> stockQuantity >> price)
        {
            if (productID == id)
            {
                product = Product(productID, productName, stockQuantity, price); // gán thông tin sản phẩm vào biến product
                return true;
            }
        }
        return false;
    }
    bool checkStockQuantity(int qty, Product &product) // Kiểm tra số lượng sản phẩm trong kho
    {
        return product.getStockQuantity() >= qty;
    }
    void updateStockQuantity(Product &product, string id, int qty, bool decrease) // Cập nhật số lượng sản phẩm trong kho (nếu decrease==true => giảm và ngược lại thì tăng)
    {
        productCount = countProduct();
        string productID, productName;
        int stockQuantity;
        long long price;
        // đọc file để lưu thông tin vào mảng
        ifstream in("stockmanager.txt");
        if (!in.is_open())
        {
            cout << "Can not open file stockmanager.txt" << endl;
            return;
        }
        Product *products = new Product[productCount];
        for (int i = 0; i < productCount; i++)
        {
            in >> productID >> productName >> stockQuantity >> price;
            products[i] = Product(productID, productName, stockQuantity, price);
            if (products[i].getProductID() == id)
            {
                if (decrease == true)
                {
                    products[i].decreaseStockQuantity(qty);
                }
                else
                {
                    products[i].increaseStockQuantity(qty);
                }
            }
        }
        in.close();
        // ghi file để ghi đè lại thông tin sản phẩm vào file.
        ofstream out("stockmanager.txt");
        if (!out.is_open())
        {
            cout << "Can not open file stockmanager.txt" << endl;
            return;
        }
        for (int i = 0; i < productCount; i++)
        {
            out << products[i].getProductID() << " " << products[i].getProductName() << " " << products[i].getStockQuantity() << " " << products[i].getPrice() << endl;
        }

        out.close();
        delete[] products;
    }
    void addProduct()
    {
        ofstream os("stockmanager.txt", ios::app);
        if (!os.is_open())
        {
            cout << "Can not open file stockmanager.txt" << endl;
            return;
        }
        string productID;
        string productName;
        int stockQuantity;
        long long price;
        Product p;
        p.inputProductInfo();
        os << "\n"
           << p.getProductID() << " " << p.getProductName() << " " << p.getStockQuantity() << " " << p.getPrice() << endl;
        cout << "=>Product has been successfully added!" << endl;
        os.close();
    }
    void removeProduct()
    {
        productCount = countProduct();
        if (productCount <= 0)
        {
            cout << "No product to remove!" << endl;
            return;
        }
        // đọc file để gán thông tin sản phẩm vào mảng
        ifstream in("stockmanager.txt");
        if (!in.is_open())
        {
            cout << "Can not open file stockmanager.txt!" << endl;
            return;
        }
        string productID, productName;
        int stockQuantity;
        long long price;
        delete[] listProduct;
        listProduct = new Product[productCount];
        for (int i = 0; i < productCount; i++)
        {
            in >> productID >> productName >> stockQuantity >> price;
            listProduct[i] = Product(productID, productName, stockQuantity, price);
        }
        in.close();
        // Xoá sản phẩm
        int index;
        do
        {
            cout << "Choose product to remove (Enter index): ";
            cin >> index;
        } while (index < 1 || index > productCount);
        Product *newList = new Product[productCount - 1];
        int newIndex = 0;
        for (int i = 0; i < productCount; i++)
        {
            if (i + 1 != index)
            {
                newList[newIndex++] = listProduct[i];
            }
        }
        delete[] listProduct;
        listProduct = newList;
        productCount--;
        // Ghi đè lại file sau khi xoá sảm phẩm
        ofstream out("stockmanager.txt");
        if (!out.is_open())
        {
            cout << "Can not open file stockmanager.txt" << endl;
            return;
        }
        for (int i = 0; i < productCount; i++)
        {
            out << listProduct[i].getProductID() << " " << listProduct[i].getProductName() << " " << listProduct[i].getStockQuantity() << " " << listProduct[i].getPrice() << endl;
        }
        out.close();
        cout << "=>Product has been successfully deleted!" << endl;
    }
    void updateProduct()
    {
        productCount = countProduct();
        if (productCount <= 0)
        {
            cout << "No product to update!" << endl;
            return;
        }
        // Đọc file để gán thông tin của san phẩm vào mảng
        ifstream in("stockmanager.txt");
        if (!in.is_open())
        {
            cout << "Can not open file stockmanager.txt" << endl;
            return;
        }
        string productID;
        string productName;
        int stockQuantity;
        long long price;
        Product *listProduct = new Product[productCount];
        for (int i = 0; i < productCount; i++)
        {
            in >> productID >> productName >> stockQuantity >> price;
            listProduct[i] = Product(productID, productName, stockQuantity, price);
        }
        in.close();
        // Chọn 1 thông tin để sửa
        int index, choice_2_0;
        do
        {
            cout << "Choose product to update (Enter index): ";
            cin >> index;
        } while (index < 1 || index > productCount);
        do
        {
            cout << "\n1. ProductID \n2. Product name\n3. StockQuantity\n4. Product price\n0. Exit\n=>Choice_2_0: ";
            cin >> choice_2_0;
            cin.ignore();
            switch (choice_2_0)
            {
            case 1:
                cout << "\nEnter ProductID: ";
                getline(cin, productID);
                listProduct[index - 1].setProductID(productID);
                cout << "=>Product information updated successfully!" << endl;
                break;

            case 2:
                cout << "\nEnter Product name: ";
                cin.ignore();
                getline(cin, productName);
                listProduct[index - 1].setProductName(productName);
                cout << "=>Product information updated successfully!" << endl;
                break;
            case 3:
                cout << "\nEnter StockQuantity: ";
                cin >> stockQuantity;
                listProduct[index - 1].setStockQuantity(stockQuantity);
                cout << "=>Product information updated successfully!" << endl;
                break;
            case 4:
                cout << "\nEnter Product price: ";
                cin >> price;
                listProduct[index - 1].setPrice(price);
                cout << "=>Product information updated successfully!" << endl;
                break;
            }
        } while (choice_2_0 != 0);
        ofstream out("stockmanager.txt"); // ghi đè lại file sau khi cập nhật
        if (!out.is_open())
        {
            cout << "Can not open file stockmanager.txt" << endl;
            return;
        }
        for (int i = 0; i < productCount; i++)
        {
            out << listProduct[i].getProductID() << " " << listProduct[i].getProductName() << " " << listProduct[i].getStockQuantity() << " " << listProduct[i].getPrice() << endl;
        }
        out.close();
        delete[] listProduct;
    }
    int countEmployee()
    {
        // đọc file để đếm số lượng nhân viên đã có trong file
        ifstream in("employee.txt");
        if (!in.is_open())
        {
            cout << "Cannot open file empoyee.txt for reading!" << endl;
            return 0;
        }
        int count = 0;
        string employeeID, name, phoneNumber, address;
        int age;
        while (in >> employeeID >> name >> age >> phoneNumber >> address)
        {
            count++;
        }
        in.close();
        return count;
    }
    void displayListEmployee()
    {
        cout << "\n----------Employee List----------" << endl;
        ifstream in("employee.txt");
        if (!in.is_open())
        {
            cout << "Cannot open file employee.txt !" << endl;
            return;
        }
        employeeCount = countEmployee();
        string employeeID, name, phoneNumber, address;
        int age;
        listEmployee = new Employee[employeeCount];
        for (int i = 0; i < employeeCount; i++)
        {
            in >> employeeID >> name >> age >> phoneNumber >> address;
            listEmployee[i] = Employee(employeeID, name, age, phoneNumber, address);
            cout << "[" << i + 1 << "] " << endl;
            listEmployee[i].displayEmployeeInfo();
            cout << "-----------------------------------" << endl;
        }
        in.close();
    }
    void addEmployee()
    {
        ofstream os("employee.txt", ios::app);
        if (!os.is_open())
        {
            cout << "Cannot open file employee.txt!" << endl;
            return;
        }
        string employeeID, name, phoneNumber, address;
        int age;
        Employee e;
        e.inputEmployeeInfo();
        os << "\n"
           << e.getEmployeeID() << " " << e.getName() << " " << e.getAge() << " " << e.getPhoneNumber() << " " << e.getAddress();
        cout << "Employee has been successfully added!" << endl;
        os.close();
    }
    void removeEmployee()
    {
        employeeCount = countEmployee();
        if (employeeCount <= 0)
        {
            cout << "No employee to remove." << endl;
            return;
        }
        // đọc file để gán thông tin nhân viên vào mảng
        ifstream in("employee.txt");
        if (!in.is_open())
        {
            cout << "Cannot open file employee.txt !" << endl;
            return;
        }
        string employeeID, name, phoneNumber, address;
        int age;
        delete[] listEmployee;
        listEmployee = new Employee[employeeCount];
        for (int i = 0; i < employeeCount; i++)
        {
            in >> employeeID >> name >> age >> phoneNumber >> address;
            listEmployee[i] = Employee(employeeID, name, age, phoneNumber, address);
        }
        in.close();
        // xoá nhân viên
        int index;
        do
        {
            cout << "Choose employee to remove (Enter index): ";
            cin >> index;
        } while (index < 1 || index > employeeCount);
        Employee *newList = new Employee[employeeCount - 1];
        int newIndex = 0;
        for (int i = 0; i < employeeCount; i++)
        {
            if (i + 1 != index)
            {
                newList[newIndex++] = listEmployee[i];
            }
        }
        delete[] listEmployee;
        listEmployee = newList;
        employeeCount--;
        // ghi đè lại file sau khi xoá nhân viên thành công
        ofstream out("employee.txt");
        if (!out.is_open())
        {
            cout << "Cannot open file employee.txt!" << endl;
            return;
        }
        for (int i = 0; i < employeeCount; i++)
        {
            out << listEmployee[i].getEmployeeID() << " " << listEmployee[i].getName() << " " << listEmployee[i].getAge() << " " << listEmployee[i].getPhoneNumber() << " " << listEmployee[i].getAddress() << endl;
        }
        out.close();
        cout << "=>Employee has been successfully deleted!" << endl;
    }
    void updateEmployee()
    {
        employeeCount = countEmployee();
        if (employeeCount <= 0)
        {
            cout << "No employee to edit info." << endl;
            return;
        }
        // đọc file để gán thông tin nhân viên vào mảng
        ifstream in("employee.txt");
        if (!in.is_open())
        {
            cout << "Cannot open file employee.txt !" << endl;
            return;
        }
        string employeeID, name, phoneNumber, address;
        int age;
        delete[] listEmployee;
        listEmployee = new Employee[employeeCount];
        for (int i = 0; i < employeeCount; i++)
        {
            in >> employeeID >> name >> age >> phoneNumber >> address;
            listEmployee[i] = Employee(employeeID, name, age, phoneNumber, address);
        }
        in.close();
        // lựa chọn 1 thông tin để sửa
        int index, choice_2_1;
        do
        {
            cout << "Choose employee to edit info (Enter index): ";
            cin >> index;
        } while (index < 1 || index > employeeCount);
        do
        {
            cout << "\n1. EmployeeID \n2. Employee name\n3. Employee age\n4. Employee phone number\n5. Employee address\n0. Exit\n=>Choice_2_1: ";
            cin >> choice_2_1;
            cin.ignore();
            switch (choice_2_1)
            {
            case 1: // sửa ID nhân viên
                cout << "\nEnter employeeID: ";
                getline(cin, employeeID);
                listEmployee[index - 1].setEmployeeID(employeeID);
                cout << "=>Employee information has been successfully updated!" << endl;
                break;

            case 2:
                cout << "\nEnter employee name: ";
                getline(cin, name);
                listEmployee[index - 1].setName(name);
                cout << "=>Employee information has been successfully updated!" << endl;
                break;
            case 3:
                cout << "\nEnter employee age: ";
                cin >> age;
                listEmployee[index - 1].setAge(age);
                cout << "=>Employee information has been successfully updated!" << endl;
                break;
            case 4:
                cout << "\nEnter employee phone number: ";
                getline(cin, phoneNumber);
                listEmployee[index - 1].setPhoneNumber(phoneNumber);
                cout << "=>Employee information has been successfully updated!" << endl;
                break;
            case 5:
                cout << "\nEnter employee address: ";
                getline(cin, address);
                listEmployee[index - 1].setAddress(address);
                cout << "=>Employee information has been successfully updated!" << endl;
                break;
            }
        } while (choice_2_1 != 0);
        // ghi đè lại file sau khi sửa thông tin
        ofstream out("employee.txt");
        if (!out.is_open())
        {
            cout << "Cannot open file employee.txt!" << endl;
            return;
        }
        for (int i = 0; i < employeeCount; i++)
        {
            out << listEmployee[i].getEmployeeID() << " " << listEmployee[i].getName() << " " << listEmployee[i].getAge() << " " << listEmployee[i].getPhoneNumber() << " " << listEmployee[i].getAddress() << endl;
        }
        out.close();
    }
    void calculateSalaries()
    {
        employeeCount = countEmployee();
        // đọc file để lưu nhân viên vào mảng
        ifstream in("employee.txt");
        if (!in.is_open())
        {
            cout << "Cannot open file empoyee.txt for reading!" << endl;
            return;
        }
        string employeeID, name, phoneNumber, address;
        int age;
        Employee *listEmployee = new Employee[employeeCount];
        for (int i = 0; i < employeeCount; i++)
        {
            in >> employeeID >> name >> age >> phoneNumber >> address;
            listEmployee[i] = Employee(employeeID, name, age, phoneNumber, address);
        }
        in.close();
        // tính lương
        for (int i = 0; i < employeeCount; i++)
        {
            listEmployee[i].inputWorkingDays();
            listEmployee[i].calculateSalary();
        }
        // xuất ra bảng lương
        cout << "\n----------Table of salary----------" << endl;
        for (int i = 0; i < employeeCount; i++)
        {
            cout << "[" << i + 1 << "] ";
            cout << listEmployee[i].getEmployeeID() << " " << listEmployee[i].getName() << " " << listEmployee[i].calculateSalary() << " VND" << endl;
        }
        delete[] listEmployee;
    }
};
class OrderDetail
{
private:
    Product product;
    int quantity;
    long long unitPrice;

public:
    OrderDetail(Product &product, int quantity, long long unitPrice)
    {
        this->product = product;
        this->quantity = quantity;
        this->unitPrice = unitPrice;
    }
    OrderDetail()
    {

        this->quantity = 0;
        this->unitPrice = 0;
    }
    ~OrderDetail()
    {

        this->quantity = 0;
        this->unitPrice = 0;
    }
    Product getProduct()
    {
        return product;
    }
    int getQuantity()
    {
        return quantity;
    }
    long long calculateSubtotal()
    {
        return product.getPrice() * quantity;
    }
    void displayOrderDetail()
    {
        cout << product.getProductID() << " " << product.getProductName() << " x " << quantity << " = VND " << calculateSubtotal() << endl;
    }
};
class Order
{
private:
    string orderID;
    int amount;
    static int nextOrderNumber;
    DateTime orderDateTime;
    OrderDetail *orderDetails;

public:
    Order()
    {
        this->orderID = generateOrderID();
        this->orderDetails = nullptr;
        this->amount = 0;
    }
    Order(int amount)
    {
        this->orderID = generateOrderID();
        this->amount = amount;
        this->orderDetails = new OrderDetail[amount];
    }
    ~Order()
    {
        delete[] orderDetails;
    }
    static string generateOrderID()
    {
        return "#" + to_string(nextOrderNumber++);
    }
    string getOrderID()
    {
        return orderID;
    }
    void displayMenu()
    {
        string productID, productName;
        int stockQuantity;
        long long price;
        ifstream in("stockmanager.txt");
        if (!in.is_open())
        {
            cout << "Can not open file stockmanager.txt" << endl;
            return;
        }
        cout << "\n--------Menu--------" << endl;
        while (in >> productID >> productName >> stockQuantity >> price)
        {
            cout << productID << "\t" << productName << "\t" << price << endl;
        }
        in.close();
    }
    void addItem(Product &product, int quantity) // thêm mặt hàng vào order
    {
        OrderDetail *newOrderDetails = new OrderDetail[amount + 1];
        for (int i = 0; i < amount; i++)
        {
            newOrderDetails[i] = orderDetails[i];
        }
        newOrderDetails[amount] = OrderDetail(product, quantity, product.getPrice());
        delete[] orderDetails;
        orderDetails = newOrderDetails; // mảng orderDetails trỏ tới mảng newOrderDetails
        amount++;
    }
    void removeItem() // xoá mặt hàng khỏi order
    {
        if (amount <= 0)
        {
            orderDetails = nullptr;
            amount = 0;
            return;
        }
        int index;
        do
        {
            cout << "Choose item to remove (Enter index): ";
            cin >> index;
        } while (index <= 0);
        Product removedProduct = orderDetails[index - 1].getProduct();
        int removeQty = orderDetails[index - 1].getQuantity();
        OrderDetail *newOrderDetails = new OrderDetail[amount - 1];
        IceCreamStore s;
        s.updateStockQuantity(removedProduct, removedProduct.getProductID(), removeQty, false); // false = tăng số lượng
        int newIndex = 0;
        for (int i = 0; i < amount; i++)
        {
            if (i + 1 != index)
            {
                newOrderDetails[newIndex++] = orderDetails[i];
            }
        }
        delete[] orderDetails;
        orderDetails = newOrderDetails;
        amount--;
    }
    long long calculateTotal()
    {
        long long total = 0;
        for (int i = 0; i < amount; i++)
        {
            total += orderDetails[i].calculateSubtotal();
        }
        return total;
    }
    void displayOrder()
    {
        DateTime datetime;
        datetime.orderDateTime();
        for (int i = 0; i < amount; i++)
        {
            if (orderDetails[i].calculateSubtotal() > 0)
            {
                cout << "[" << i + 1 << "] ";
                orderDetails[i].displayOrderDetail();
            }
        }
        cout << "=>Total: VND " << calculateTotal() << endl;
    }
    void takeOrder()
    {
        Product p;
        IceCreamStore s;
        while (true)
        {
            string id, continueOrder;
            int qty;
            cout << "Enter productID and quantity: ";
            cin >> id >> qty;
            Product foundProduct;
            if (s.checkIDProduct(id, foundProduct) == true)
            {
                if (s.checkStockQuantity(qty, foundProduct) == true)
                {
                    addItem(foundProduct, qty);
                    s.updateStockQuantity(foundProduct, id, qty, true); // true = giảm số lượng
                    cout << "Product added succcessfully!" << endl;
                }
                else
                {
                    cout << "Insufficient stock. Only " << foundProduct.getStockQuantity() << " left." << endl;
                }
            }
            else
            {
                cout << "Product not found!" << endl;
            }
            cout << "Continue order? (Y/N): ";
            cin >> continueOrder;
            if (continueOrder == "N" || continueOrder == "n")
            {
                break;
            }
        }
    }
};
int Order::nextOrderNumber = 1;

int main()
{
    Employee e;
    Product p;
    IceCreamStore s;
    int choice;
    do
    {
        cout << "\n********************MENU MANAGEMENT********************" << endl;
        cout << "*****              1. Order                       *****" << endl;
        cout << "*****              2. Employee Management         *****" << endl;
        cout << "*****              3. Product Management          *****" << endl;
        cout << "*****              0. Exit                        *****" << endl;
        cout << "*******************************************************" << endl;
        cout << "                 =>Enter choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        { // in ra menu và order
            Order currentOrder;
            cout << "Starting a new order!" << endl;
            currentOrder.displayMenu();
            currentOrder.takeOrder();
            cout << "\n----------Bill----------" << endl;
            cout << "Order ID: " << currentOrder.getOrderID() << endl;
            currentOrder.displayOrder();
            int choice_1;
            do
            {
                cout << "\n-----Order Management-----" << endl
                     << "1. Add item\n2. Remove item\n0. Exit\n=>Choice_1: ";
                cin >> choice_1;

                switch (choice_1)
                {
                case 1: // Thêm mặt hàng vào order
                    currentOrder.displayMenu();
                    {
                        cout << "-----Add items!-----" << endl;
                        currentOrder.takeOrder();
                        cout << "\n----------Bill----------" << endl;
                        cout << "Order ID: " << currentOrder.getOrderID() << endl;
                        currentOrder.displayOrder();
                    }
                    break;
                case 2: // Xoá mặt hàng khỏi order
                {
                    cout << "-----Remove items!-----" << endl;
                    currentOrder.removeItem();
                    cout << "\n----------Bill----------" << endl;
                    cout << "Order ID: " << currentOrder.getOrderID() << endl;
                    currentOrder.displayOrder();
                    break;
                }
                }
            } while (choice_1 != 0);
            break;
        }
            int choice_2;
        case 2:
        { // Quản lý nhân viên
            do
            {
                cout << "\n-----Employee Management-----" << endl
                     << "1. Display employee list \n2. Add employee\n3. Remove employee\n4. Update employee info\n5. Calculate salary\n0. Exit\n=>Choice_2: ";
                cin >> choice_2;
                switch (choice_2)
                {
                case 1: // Xuất ra danh sách nhân viên
                    s.displayListEmployee();
                    break;
                case 2: // Thêm nhân viên
                    s.displayListEmployee();
                    s.addEmployee();
                    break;
                case 3: // Xoá nhân viên
                    s.displayListEmployee();
                    s.removeEmployee();
                    break;
                case 4: // Thay đổi thông tin nhân viên
                    s.displayListEmployee();
                    s.updateEmployee();
                    break;
                case 5: // Tính lương nhân viên
                    s.calculateSalaries();
                    break;
                }
            } while (choice_2 != 0);
            break;
        }
            int choice_3;
        case 3:
        { // Quản lý sản phẩm
            do
            {
                cout << "\n-----Product Management-----" << endl
                     << "1. Display product list \n2. Add product\n3. Remove product\n4. Update product info\n0. Exit\n=>Choice_3: ";
                cin >> choice_3;
                switch (choice_3)
                {
                case 1: // Xuất ra danh sách sản phẩm
                    s.displayListProduct();
                    break;
                case 2: // Thêm sản phẩm
                    s.displayListProduct();
                    s.addProduct();
                    break;
                case 3: // Xoá sản phẩm
                    s.displayListProduct();
                    s.removeProduct();
                    break;
                case 4: // Thay đổi thông tin sản phẩm
                    s.displayListProduct();
                    s.updateProduct();
                    break;
                }
            } while (choice_3 != 0);
            break;
        }
        }
    } while (choice != 0);
    return 0;
}
