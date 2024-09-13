#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define random(a,b)  a+rand()%(b+1-a)


using namespace std;

void openCSV() {
    ifstream in("sources/price.csv"); // окрываем файл для чтения
    int count = 0;
    int a[6];
    int b[6];
    int c[6];
    string str1;
    string str2;
    string str3;
    if (in.is_open()) {
        
        while (count < 6)
        {
            getline(in, str1, ',');
            getline(in, str2, ',');
            getline(in, str3, '\n');
            a[count] = stoi(str1);
            b[count] = stoi(str2);
            c[count] = stoi(str3);
            cout << a[count] << " " << b[count] << " " << c[count] << endl;
            count++;
        }

    }
    in.close();
    //cout << a[0] << a[5]<<endl;
}  

//Visitor* Visitor::generateVisitor() {
//    Visitor* visitor = new Visitor(names[random(0, names.size() - 1)], surnames[random(0, surnames.size() - 1)], abonements[random(0, abonements.size() - 1)]);
//    return visitor;
//}
class Client {
private:
    int id;
    int days;
    string name;
    string surname;
    string pasport;
    static int counter;
public:
    Client(string name, string surname, string pasport, int days) {
        this-> id = counter++;
        this->name = name;
        this->surname = surname;
        this->pasport = pasport;
        this->days = days;
    }
    void ShowInfo() {
        cout << name << surname << pasport;
    }
    string getName() {
        return   name;
    }
    string getSurname() {
        return   surname;
    }
    string getPasport() {
        return   pasport;
    }
    int getDays() { return days; }
    //void showDays() { cout << days; }
};

int Client::counter = 1;

class Room {
private: 
    int id;
    int square;
    int type;
    int pryce;
    bool status = 0;
    static int counter;
public:
    Room(int square, int type) {
        this->id = counter ++;
        this->square = square;
        this->type = type;
    }
    int getId() {
        return id;
    }
    bool getStatus() { return status; }
    void setStatus(bool status) {
        this->status = status;
    }
    void ShowInfo() {
        cout << id << " " << square << " " << type << endl;;
    }

    int getPrice() {
        int count = 0;
        int a[6];
        int b[6];
        int c[6];
        string str1;
        string str2;
        string str3;
        ifstream in("sources/price.csv"); // окрываем файл для чтения

        if (in.is_open()) {
           
            while (count < 6)
            {
                getline(in, str1, ',');
                getline(in, str2, ',');
                getline(in, str3, '\n');
                a[count] = stoi(str1);
                b[count] = stoi(str2);
                c[count] = stoi(str3);
                count++;
            }
        }
        in.close();
        if (square == a[0] && type == b[0]) {
            pryce = c[0]; return pryce;
        }
        if (square == a[1] && type == b[1]) {
            pryce = c[1]; return pryce;
        }
        if (square == a[2] && type == b[2]) {
            pryce = c[2]; return pryce;
        }
        if (square == a[2] && type == b[2]) {
            pryce = c[2]; return pryce;
        }
        if (square == a[3] && type == b[3]) {
            pryce = c[3]; return pryce;
        }
        if (square == a[4] && type == b[4]) {
            pryce = c[4]; return pryce;
        }
        if (square == a[5] && type == b[5]) {
            pryce = c[5]; return pryce;
        }
    }
};
int Room::counter = 1;

class Hotel {
private:
    vector<Room*> rooms;
public:
    void generateRooms(Room* room) {
        
        cout << "номер " << room->getId() << " создан" << endl;
        auto iter = find(rooms.begin(), rooms.end(), room);
        if (iter == rooms.end()) {
            rooms.push_back(room);
        }
        room->ShowInfo();
        room->getPrice();
    }
    Room* getFreeRoom() {
        for (auto room : rooms) {
            if (!room->getStatus()) {
                return room;
            }
        }
        return nullptr;
    }
};

class Journal {
    
    int uniqNum;
    Hotel* hotel;
    Client* client;
    vector<Client*> clients;
    Room* room = nullptr;
    static int counter;
    bool status = 0;
    static int arrNum;
    int* p = new int[uniqNum];
public:
    Journal(Hotel* hotel) {
        uniqNum = counter++;
        this->hotel = hotel;
        
    }
    void open(Client* client) {
        auto iter = find(clients.begin(), clients.end(), client);
        if (iter == clients.end()) {
            clients.push_back(client);
        }
        this->room = hotel->getFreeRoom();
        if (room != nullptr) {
            room->setStatus(true);
            this->status = true;
            cout << "номер " << uniqNum<< " забронирован" << endl;
            
            fstream fout;
            fout.open("sources/clientjournal.csv", ios::out | ios::app);
            fout << uniqNum << ", "
                << client->getName() << ", "
                << client->getSurname() << ", "
                << client->getPasport() << ", "
                << client->getDays() << "\n";
            fout.close();
            
            int sumPrice = room->getPrice() * client->getDays();
            fstream profit;
            profit.open("sources/Profit.csv", ios::out | ios::app);
            profit << uniqNum << ", "
                << sumPrice  << "\n";
            profit.close();
            
        }
        else {
            cout << "все номера заняты" << endl;

        }
    }
    void close() {
        clients;
        room->setStatus(false);
        room->getId();
        cout << " Номер " << uniqNum << " Свободен " << endl;
        this->room = nullptr;
        this->status = false;
    }

};

    int Journal::counter = 1;
int main()
{
    setlocale(LC_ALL, "rus");
    //openCSV();
   /* int k = 0;
    while ( k < 15) {
        if (k != 13) {
            cout << k << " ";
        }
        k++;
   }*/
    Hotel* hotel = new Hotel();
    hotel->generateRooms(new Room(random(1, 3), random(1, 2)));
    hotel->generateRooms(new Room(random(1, 3), random(1, 2)));
    Journal journal1(hotel);
    Journal journal2(hotel);
    journal1.open(new Client("Dmitry","Bogdan","1223645789",30));
    journal2.open(new Client("Alex", "Vokulenko", "2223666777", 30));
    journal1.close();
    journal2.close();
    return 0;
}

