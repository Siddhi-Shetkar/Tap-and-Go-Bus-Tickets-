#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iomanip> //setw
#include <algorithm>
#include <limits>
#include<set>
#include<stack>
#include<unordered_map>
#include <queue>
using namespace std;
// Struct for BoardingPoint
struct BoardingPoint {
    string name;
    string time;
    string location;
    BoardingPoint(string n, string t, string l) : name(n), time(t), location(l) {}
};

// Struct for DroppingPoint
struct DroppingPoint {
    string name;
    string location;
    int priority;
    DroppingPoint(string n, string l, int p) : name(n), location(l), priority(p) {}
};

// Comparator for priority_queue to prioritize higher priority values
struct CompareDroppingPoint {
    bool operator()(const DroppingPoint& a, const DroppingPoint& b) {
        return a.priority < b.priority; // Max-heap: higher priority first
    }
};
string toLower(const string& s) {
    string result = s;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
string toLowerCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
// Enum to represent cities
enum City {
    HYDERABAD = 1,
    PUNE,
    DELHI,
    LADAKH,
    BANGALORE,
    OOTY,
    PONDICHERRY,
    CHENNAI,
    MUMBAI,
    THANE,
    INVALID_CITY
};

// Map to convert lowercase city names to City enum
map<string, City> cityMap = {
    {"hyderabad", HYDERABAD},
    {"pune", PUNE},
    {"delhi", DELHI},
    {"ladakh", LADAKH},
    {"bangalore", BANGALORE},
    {"ooty", OOTY},
    {"pondicherry", PONDICHERRY},
    {"chennai", CHENNAI},
    {"mumbai", MUMBAI},
    {"thane", THANE}
};

// Function to get City enum from string input
City getCityCode(const string& city) {
    string lowerCity = toLower(city);
    auto it = cityMap.find(lowerCity);
    return (it != cityMap.end()) ? it->second : INVALID_CITY;
}

// Function to check if the route is valid
bool isValidRoute(City from, City to) {
    if (from == INVALID_CITY || to == INVALID_CITY) return false;
    return (from == HYDERABAD && to == PUNE) ||
           (from == DELHI && to == LADAKH) ||
           (from == BANGALORE && to == OOTY) ||
           (from == PONDICHERRY && to == CHENNAI) ||
           (from == MUMBAI && to == THANE);
}

// Function to get standardized city name
string getCityName(City city) {
    switch (city) {
        case HYDERABAD: return "Hyderabad";
        case PUNE: return "Pune";
        case DELHI: return "Delhi";
        case LADAKH: return "Ladakh";
        case BANGALORE: return "Bangalore";
        case OOTY: return "Ooty";
        case PONDICHERRY: return "Pondicherry";
        case CHENNAI: return "Chennai";
        case MUMBAI: return "Mumbai";
        case THANE: return "Thane";
        default: return "";
    }
}
struct details{
    string name;
    long int num;
    char g;
    int age;
};
struct Node{
    int data;
    Node* next;
};
struct Node* head;
void displayBookingSummary(const string& ticketID, const details& passenger,
    const string& boardingPoint, const string& boardingTime,
    const string& droppingPoint, const string& droppingTime,
    Node* seatList, const string& travelDate,
    const string& travel, const string& from, const string& to) {
    cout << "\n===== 🚍 Booking Summary =====" << endl;
    cout << "Ticket ID: " << ticketID << endl;
    cout << "Passenger Name: " << passenger.name << endl;
    cout << "Phone Number: " << passenger.num << endl;
    cout << "Travel: " << travel << " (" << from << " -> " << to << ")" << endl;
    cout << "Boarding Point: " << boardingPoint << " | Time: " << boardingTime << endl;
    cout << "Dropping Point: " << droppingPoint << " | Time: " << droppingTime << endl;
    cout << "Travel Date: " << travelDate << endl;
    cout << "Seat Number(s): ";
    Node* temp = seatList;
    while (temp != NULL) {
        cout << temp->data;
        if (temp->next != NULL) cout << ", ";
        temp = temp->next;
    }
    cout << endl;
}

class Graph {
public:
    // Using unordered_map to map city names (string) to a list of neighboring cities (outgoing routes)
    unordered_map<string, vector<string>> adjList;

    // Add a directed route from city1 to city2
    void addRoute(const string& city1, const string& city2) {
        adjList[city1].push_back(city2);
    }

    // Print all outgoing routes from the given city using arrow notation
    void printRoutes(const string& city) {
        if (adjList.find(city) != adjList.end()) {
            cout << "Routes from " << city << ":\n";
            for (const auto& neighbor : adjList[city]) {
                cout << city << " -> " << neighbor << endl;
            }
        } else {
            cout << "? City not found in the routes.\n";
        }
    }

    // (Optional) Print all routes in the graph
    void printAllRoutes() {
        if (adjList.empty()) {
            cout << "No routes have been added.\n";
            return;
        }
        cout << "All Routes:\n";
        for (const auto& pair : adjList) {
            const string& city = pair.first;
            for (const string& dest : pair.second) {
                cout << city << " -> " << dest << endl;
            }
        }
    }
};

//TICKET ID
string generateTicketID(Node* head) {
    int mod = 100000; // Modulo value for hash calculation
    int hash = 0;
    Node* temp = head;

    // Loop through each seat number and calculate hash
    while (temp != NULL) {
        hash = (hash * 31 + temp->data) % mod;
        temp = temp->next;
    }

    return "TKT" + to_string(hash);
}  
// Binary Search Tree structure
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Insert date into BST
TreeNode* insert(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val)
        root->left = insert(root->left, val);
    else if (val > root->val)
        root->right = insert(root->right, val);
    return root;
}

// Search for a date in BST
bool search(TreeNode* root, int val) {
    if (!root) return false;
    if (val == root->val) return true;
    return val < root->val ? search(root->left, val) : search(root->right, val);
}

// Print BST in order
void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
}


set<int> booked_seats; // Global set to track booked seats

void Insert(int x) {
    Node* temp = new Node();
    temp->data = x;
    temp->next = NULL;
   
    if (head == NULL) {
        head = temp;
    } else {
        Node* temp1 = head;
        while (temp1->next != NULL) {
            temp1 = temp1->next;
        }
        temp1->next = temp;
    }
    booked_seats.insert(x); // Mark seat as booked
}
void Print(){
    Node* temp=head;
    cout<<"Seat no(s) chosen : ";
    while(temp!=NULL){
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
}
class buses {
protected:
    void bus() {
        cout << "🚍  Buses available are : " << endl;
    }
};
class buses_available : public buses {
public:
    void buses_shown() {
        buses::bus(); // calls base class function
    }

    void bus() { // derived class function
        cout<<endl;
        cout << "🚍  Hyderabad -> Pune" << endl;
        cout << "🚍  Delhi -> Ladakh" << endl;
        cout << "🚍  Bangalore -> Ooty" << endl;
        cout << "🚍  Pondicherry -> Chennai" << endl;
        cout << "🚍  Mumbai -> Thane" << endl;
        cout<<endl;
    }
};
struct Bustickets{
    string destination;
    double price;
   
    void print() const {
        cout << destination << " | " << price << "\n";
    }
};
bool compareByPrice(const Bustickets& a, const Bustickets& b) {
    return a.price < b.price;
}
class trip{
    public:
    string from;
    string to;
   
    trip(){
        cout<<"\033[1mEnter trip details : \033[1m"<<endl; //constructor
    }
    void display(){
        cout<<"\033[1mEnter passenger details : \033[1m"<<endl;
    }
};

// Returns true if needle is substring of haystack (case-insensitive)
bool caseInsensitiveMatch(const string& haystack, const string& needle) {
    string hay = toLower(haystack);
    string need = toLower(needle);
    return hay.find(need) != string::npos;
}

// Find best match from a list of strings based on substring matching (returns first matched or empty)
string findMatch(const vector<string>& options, const string& input) {
    for (const auto& option : options) {
        if (caseInsensitiveMatch(option, input)) {
            return option;
        }
    }
    return ""; // no match
}
void WindowSeats(const vector<int>& windowseats) {
    Node* temp = head;
    cout << "Window seat no(s) selected: ";
    while (temp != NULL) {
        if (find(windowseats.begin(), windowseats.end(), temp->data) != windowseats.end()) {
            cout << temp->data << " ";
        }
        temp = temp->next;
    }
    cout << endl;
}
int TotalPrice(int n, trip t1, const vector<int>& windowseats){
    int price = 0;
    if(t1.from=="Hyderabad" && t1.to=="Pune"){
        price=1500;
    }
    else if(t1.from=="Delhi" && t1.to=="Ladakh"){
        price=1800;
    }
    else if(t1.from=="Bangalore" && t1.to=="Ooty"){
        price=1000;
    }
    else if(t1.from=="Pondicherry" && t1.to=="Chennai"){
        price=890;
    }
    else if(t1.from=="Mumbai" && t1.to=="Thane"){
        price=150;
    }
    Node* temp = head;
    int count = 0;
    while (temp != NULL) {
        if (find(windowseats.begin(), windowseats.end(), temp->data) != windowseats.end()) {
            count++;
        }
        temp = temp->next;
    }
    if(count==0){
        return n*price;
    }
    else{
        return n*price + count*100;
    }
}
struct Details {
    long long num{};   // phone number
};

int main()
{
    string travelInput;
    char continue_booking;
    do {
        cout << "\t \t \t \t \t \t🚍  Tap and Go : Bus Tickets" << endl;

        buses_available b;
        b.buses_shown();
        b.bus();
        cout << endl;

        // SORT BUS TICKETS BY PRICE
        vector<Bustickets> tickets = {
            {"Pune", 1500},
            {"Ladakh", 1800},
            {"Ooty", 1000},
            {"Chennai", 890},
            {"Thane", 150}
        };
        sort(tickets.begin(), tickets.end(), compareByPrice);
        cout << "Sorted Bus Tickets by Price:\n";
        for (const auto& ticket : tickets) {
            ticket.print();
        }
        cout << endl;

        // TRIP DETAILS
        trip t1;
        string fromInput, toInput;
        cout << "From : ";
        cin >> fromInput;
        cout << "To : ";
        cin >> toInput;
        cout << endl;
       
    //ENTER MONTH AND TABLE
    int month;
    cout << "Enter your travel month (MM): ";
    cin >> month;

    if (month < 1 || month > 12) {
        cout << " Invalid month entered. Please enter 1–12: "<<month<<endl;
    }
    // User picks a travel date
    int date;
    cout << "Enter your travel date (DD): ";
    cin >> date;
    cout<<endl;
     if (date < 1 || date > 31) {
             cout<<"invalid date entered. Please enter a day from 1 to 31:";
             cin>>date;
     }
        cout << "Selected Date 📅: ";
        if (date < 10) cout << "0";
        cout << date << "/";
        if (month < 10) cout << "0";
        cout << month << "\n";
        cout<<endl;
        // Get city codes
        City fromCity = getCityCode(fromInput);
        City toCity = getCityCode(toInput);

        // Standardize city names for consistency
        t1.from = getCityName(fromCity);
        t1.to = getCityName(toCity);

        // Validate route and display preferred timings
        if (isValidRoute(fromCity, toCity)) {
            cout << "Preferred timings ⌚: " << endl;
            cout << "6:00 - 12:00\t0:00 - 6:00" << endl;
            cout << "12:00 - 18:00\t18:00 - 24:00" << endl;
        } else {
            cout << "🚍 Invalid route or city entered. Please choose a valid route:\n";
            cout << "🚍 Hyderabad -> Pune\n";
            cout << "🚍 Delhi -> Ladakh\n";
            cout << "🚍 Bangalore -> Ooty\n";
            cout << "🚍 Pondicherry -> Chennai\n";
            cout << "🚍 Mumbai -> Thane\n";
            continue; // Skip to next booking iteration
        }
        cout << endl;
        // PREFERRED TIMINGS BY THE USER [DEPARTURE TIME]
         int hour;
         cout << "Enter hour (0 - 23): ";
         cin >> hour;
         cout<<endl;
         
         // Handle bus schedules based on route using switch
        switch (fromCity) {
            case HYDERABAD:
                if (toCity == PUNE) {
                    cout << "\033[1mShowing 12 buses on this route\033[0m" << endl;
                    if (hour >= 0 && hour < 6) {
                        cout << "3 buses are available in this preferred timing:" << endl;
                        cout << endl;
                        cout << "• Sai Krishna Travels | 00:10 <- 9h 30 mins -> 09:40" << endl;
                        cout << "• PVS Express | 01:00 <- 9h 30 mins -> 10:30" << endl;
                        cout << "• Green Line Tours | 02:20 <- 9h 30 mins -> 11:50" << endl;
                    } else if (hour >= 6 && hour < 12) {
                        cout << "3 Buses are available in this preferred timing : " << endl;
                        cout << endl;
                        cout << "• AK TOURS AND TRAVELS | 6:20 <- 12 h 35 mins -> 18:55" << endl;
                        cout << "• Orange Tours and Travels | 7:15 <- 12h 35 mins -> 19:50" << endl;
                        cout << "• IntrCity SmartBus | 8:30 <- 12h 35 mins -> 21:05" << endl;
                    } else if (hour >= 12 && hour < 18) {
                        cout << "3 buses are available in this timing:" << endl;
                        cout << endl;
                        cout << "• Patel Travels | 12:30 <- 9h 30 mins -> 22:00" << endl;
                        cout << "• Yatra Bus Services | 13:15 <- 9h 30 mins -> 22:45" << endl;
                        cout << "• Prasanna Travels | 14:00 <- 9h 30 mins -> 23:30" << endl;
                    } else if (hour >= 18 && hour < 24) {
                        cout << "3 buses are available in this timing:" << endl;
                        cout << endl;
                        cout << "• Shirdi Express | 18:10 <- 9h 30 mins -> 03:40" << endl;
                        cout << "• Saffron Bus Lines | 19:00 <- 9h 30 mins -> 04:30" << endl;
                        cout << "• Pioneer Travels | 20:30 <- 9h 30 mins -> 06:00" << endl;
                    } else {
                        cout << "Invalid Input" << endl;
                    }
                }
                break;

            case BANGALORE:
                if (toCity == OOTY) {
                    cout << "\033[1mShowing 12 buses on this route\033[0m" << endl;
                    if (hour >= 0 && hour < 6) {
                        cout << "3 buses are available in this preferred timing:" << endl;
                        cout << endl;
                        cout << "• Jetliner Bus Co. | 00:10 <- 9h 5 mins -> 09:15" << endl;
                        cout << "• Galaxy Travels | 01:00 <- 9h 5 mins -> 10:05" << endl;
                        cout << "• Metro Travels | 02:20 <- 9h 5 mins -> 11:25" << endl;
                    } else if (hour >= 6 && hour < 12) {
                        cout << "3 buses are available in this timing:" << endl;
                        cout << endl;
                        cout << "• SAM TOURIST | 6:15<-9h 5 mins->15:20" << endl;
                        cout << "• AGR Travels | 7:00<-9h 5 mins->16:05" << endl;
                        cout << "• Green Line Travels and Holidays | 7:45<-9h 5 mins->16:50" << endl;
                    } else if (hour >= 12 && hour < 18) {
                        cout << "3 buses are available in this timing:" << endl;
                        cout << endl;
                        cout << "• KPN Travels | 12:30 <- 9h 5 mins -> 21:35" << endl;
                        cout << "• Royal Travels | 13:15 <- 9h 5 mins -> 22:20" << endl;
                        cout << "• SRS Travels | 14:00 <- 9h 5 mins -> 23:05" << endl;
                    } else if (hour >= 18 && hour < 24) {
                        cout << "• 3 buses are available in this timing:" << endl;
                        cout << endl;
                        cout << "• Orange Travels | 18:10 <- 9h 5 mins -> 03:15" << endl;
                        cout << "• National Travels | 19:00 <- 9h 5 mins -> 04:05" << endl;
                        cout << "• Sundar Express | 20:30 <- 9h 5 mins -> 05:35" << endl;
                    } else {
                        cout << "Invalid Input" << endl;
                    }
                }
                break;

            case PONDICHERRY:
                if (toCity == CHENNAI) {
                    cout << "\033[1mShowing 12 buses on this route\033[0m" << endl;
                    if (hour >= 0 && hour < 6) {
                        cout << "3 buses are available in this preferred timing:" << endl;
                        cout << endl;
                        cout << "• Pondy Express | 00:10 <- 3h 5 mins -> 03:15" << endl;
                        cout << "• Bay Travels | 01:00 <- 3h 5 mins -> 04:05" << endl;
                        cout << "• Sea Breeze Tours | 02:20 <- 3h 5 mins -> 05:25" << endl;
                    } else if (hour >= 6 && hour < 12) {
                        cout << "3 buses are available in this timing:" << endl;
                        cout << endl;
                        cout << "• Fast Track Tours | 6:15 <- 3h 5 mins -> 9:20" << endl;
                        cout << "• Velachery Travels | 7:00 <- 3h 5 mins -> 10:05" << endl;
                        cout << "• Royal Pondy | 7:45 <- 3h 5 mins -> 10:50" << endl;
                    } else if (hour >= 12 && hour < 18) {
                        cout << "3 buses are available in this timing:" << endl;
                        cout << endl;
                        cout << "• Greenfield Travels | 12:30 <- 3h 5 mins -> 15:35" << endl;
                        cout << "• Chennai Link Travels | 13:15 <- 3h 5 mins -> 16:20" << endl;
                        cout << "• Sunshine Travels | 14:00 <- 3h 5 mins -> 17:05" << endl;
                    } else if (hour >= 18 && hour < 24) {
                        cout << "3 buses are available in this timing:" << endl;
                        cout << endl;
                        cout << "• Star Travels | 18:10 <- 3h 5 mins -> 21:15" << endl;
                        cout << "• SpeedLink Travels | 19:00 <- 3h 5 mins -> 22:05" << endl;
                        cout << "• Sundar Travels | 20:30 <- 3h 5 mins -> 23:35" << endl;
                    } else {
                        cout << "Invalid Input" << endl;
                    }
                }
                break;

            case MUMBAI:
                if (toCity == THANE) {
                    cout << "\033[1mShowing 12 buses on this route\033[0m" << endl;
                    if (hour >= 0 && hour < 6) {
                        cout << "3 buses are available in this preferred timing:" << endl;
                        cout << endl;
                        cout << "• CityLink Travels | 00:10 <- 1h 15 mins -> 01:25" << endl;
                        cout << "• MetroFast Bus Co. | 01:00 <- 1h 15 mins -> 02:15" << endl;
                        cout << "• Night Rider Express | 02:20 <- 1h 15 mins -> 03:35" << endl;
                    } else if (hour >= 6 && hour < 12) {
                        cout << "3 buses are available in this timing:" << endl;
                        cout << endl;
                        cout << "• Urban Wings Express | 6:15 <- 1h 15 mins -> 7:30" << endl;
                        cout << "• Brightway Travels | 7:00 <- 1h 15 mins -> 8:15" << endl;
                        cout << "• Star Bus | 7:45 <- 1h 15 mins -> 9:00" << endl;
                    } else if (hour >= 12 && hour < 18) {
                        cout << "3 buses are available in this timing:" << endl;
                        cout << endl;
                        cout << "• Speed Wheels Travels | 12:30 <- 1h 15 mins -> 13:45" << endl;
                        cout << "• Horizon Bus Lines | 13:15 <- 1h 15 mins -> 14:30" << endl;
                        cout << "• MetroLux Travels | 14:00 <- 1h 15 mins -> 15:15" << endl;
                    } else if (hour >= 18 && hour < 24) {
                        cout << "3 buses are available in this timing:" << endl;
                        cout << endl;
                        cout << "• Prime City Tours | 18:10 <- 1h 15 mins -> 19:25" << endl;
                        cout << "• SparkLine Travels | 19:00 <- 1h 15 mins -> 20:15" << endl;
                        cout << "• Skyline Express | 20:30 <- 1h 15 mins -> 21:45" << endl;
                    } else {
                        cout << "Invalid input" << endl;
                    }
                }
                break;

            case DELHI:
                if (toCity == LADAKH) {
                    cout << "\033[1mShowing 12 buses on this route\033[0m" << endl;
                    if (hour >= 0 && hour < 6) {
                        cout << "3 buses are available in this preferred timing:" << endl;
                        cout << endl;
                        cout << "• Himalayan Travels | 00:10 <- 27h 0 mins -> 03:10 (Next Day)" << endl;
                        cout << "• Snowline Express | 01:00 <- 27h 0 mins -> 04:00 (Next Day)" << endl;
                        cout << "• Peak View Bus Co. | 02:20 <- 27h 0 mins -> 05:20 (Next Day)" << endl;
                    } else if (hour >= 6 && hour < 12) {
                        cout << "3 buses are available in this timing:" << endl;
                        cout << endl;
                        cout << "• Summit Travels | 6:15 <- 27h 0 mins -> 9:15 (Next Day)" << endl;
                        cout << "• Glacier Roadways | 7:00 <- 27h 0 mins -> 10:00 (Next Day)" << endl;
                        cout << "• Mountaineer Bus Co. | 7:45 <- 27h 0 mins -> 10:45 (Next Day)" << endl;
                    } else if (hour >= 12 && hour < 18) {
                        cout << "3 buses are available in this timing:" << endl;
                        cout << endl;
                        cout << "• Starlight Tours | 12:30 <- 27h 0 mins -> 15:30 (Next Day)" << endl;
                        cout << "• Dreamland Express | 13:15 <- 27h 0 mins -> 16:15 (Next Day)" << endl;
                        cout << "• Terra Nova Bus Co. | 14:00 <- 27h 0 mins -> 17:00 (Next Day)" << endl;
                    } else if (hour >= 18 && hour < 24) {
                        cout << "3 buses are available in this timing:" << endl;
                        cout << endl;
                        cout << "• Everest Connect Travels | 18:10 <- 27h 0 mins -> 21:10 (Next Day)" << endl;
                        cout << "• Mystic Roadways | 19:00 <- 27h 0 mins -> 22:00 (Next Day)" << endl;
                        cout << "• Highlander Express | 20:30 <- 27h 0 mins -> 23:30 (Next Day)" << endl;
                    } else {
                        cout << "Invalid input" << endl;
                    }
                }
                break;

            default:
                cout << "Invalid city or route selected." << endl;
                break;
        }
   
    cout << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
    cout << "Enter the travels name: ";
    string travel;
    getline(cin, travel);
    string travelLower = toLowerCase(travel);

    bool foundTravel = false;
    string matchedTravel; // Store the original key for boarding/dropping points

    // HYDERABAD TO PUNE TRAVELS BUS DETAILS
    map<string, string> busSchedules = {
        {"AK TOURS AND TRAVELS", "PY01-CT-8582 | AC Bus"},
        {"Orange Tours and Travels", "PY02-OR-4590 | AC Bus"},
        {"IntrCity SmartBus", "PY03-IC-5623 | AC Bus"},
        {"Sai Krishna Travels", "PY07-SK-1234 | AC Bus"},
        {"PVS Express", "PY08-PV-5678 | AC Bus"},
        {"Green Line Tours", "PY09-GL-9101 | AC Bus"},
        {"Patel Travels", "PY13-PT-2233 | AC Bus"},
        {"Yatra Bus Services", "PY14-YB-3344 | AC Bus"},
        {"Prasanna Travels", "PY15-PR-4455 | AC Bus"},
        {"Shirdi Express", "PY19-SE-8899 | AC Bus"},
        {"Saffron Bus Lines", "PY20-SB-9900 | AC Bus"},
        {"Pioneer Travels", "PY21-PI-1011 | AC Bus"}
    };
    for (const auto& pair : busSchedules) {
        if (toLowerCase(pair.first) == travelLower) {
            cout << "Hyderabad to Pune: " << pair.first << " - " << pair.second << endl;
            foundTravel = true;
            matchedTravel = pair.first; // Store original key
        }
    }

    // BANGALORE TO OOTY TRAVELS BUS DETAILS
    map<string, string> busInfo = {
        {"Jetliner Bus Co.", "TN01-JB-1001 | AC Bus"},
        {"Galaxy Travels", "TN02-GT-1002 | AC Bus"},
        {"Metro Travels", "TN03-MT-1003 | AC Bus"},
        {"SAM TOURIST", "PY01-ST-4521 | AC Bus"},
        {"AGR Travels", "PY02-AG-7832 | AC Bus"},
        {"Green Line Travels and Holidays", "PY03-GL-9157 | AC Bus"},
        {"Royal Travels", "TN02-ROY-1002 | AC Bus"},
        {"SRS Travels", "TN03-SRS-1003 | AC Bus"},
        {"KPN Travels", "TN04-PAR-1004 | AC Bus"},
        {"Orange Travels", "PY07-OT-5264 | AC Bus"},
        {"National Travels", "PY08-NT-7143 | AC Bus"},
        {"Sundar Express", "PY09-SE-3821 | AC Bus"}
    };
    for (const auto& pair : busInfo) {
        if (toLowerCase(pair.first) == travelLower) {
            cout << "Bangalore to Ooty: " << pair.first << " - " << pair.second << endl;
            foundTravel = true;
            matchedTravel = pair.first;
        }
    }

    // DELHI TO LADAKH TRAVELS BUS DETAILS
    map<string, string> allBusInfo = {
        {"Himalayan Travels", "HT01-HT-9001 | AC Bus"},
        {"Snowline Express", "SL02-SE-9012 | AC Bus"},
        {"Peak View Bus Co.", "PV03-PV-9023 | AC Bus"},
        {"Starlight Tours", "ST01-ST-2001 | AC Bus"},
        {"Dreamland Express", "DE02-DE-2002 | AC Bus"},
        {"Terra Nova Bus Co.", "TN03-TN-2003 | AC Bus"},
        {"Summit Travels", "ST01-ST-1001 | AC Bus"},
        {"Glacier Roadways", "GR02-GR-1002 | AC Bus"},
        {"Mountaineer Bus Co.", "MB03-MB-1003 | AC Bus"},
        {"Everest Connect Travels", "PY01-ET-1234 | AC Bus"},
        {"Mystic Roadways", "PY02-MR-5678 | AC Bus"},
        {"Highlander Express", "PY03-HE-9101 | AC Bus"}
    };
    for (const auto& pair : allBusInfo) {
        if (toLowerCase(pair.first) == travelLower) {
            cout << "Delhi to Ladakh: " << pair.first << " - " << pair.second << endl;
            foundTravel = true;
            matchedTravel = pair.first;
        }
    }

    // PONDICHERRY TO CHENNAI TRAVELS BUS DETAILS
    map<string, string> travelData = {
        {"Pondy Express", "TN01-PE-1111 | AC"},
        {"Bay Travels", "TN02-BT-2222 | Non-AC"},
        {"Sea Breeze Tours", "TN03-SB-3333 | AC"},
        {"Fast Track Tours", "FT01-FT-1010 | AC Bus"},
        {"Velachery Travels", "VT02-VT-1020 | Non-AC Bus"},
        {"Royal Pondy", "RP03-RP-1030 | AC Bus"},
        {"Star Travels", "PY13-ST-2478 | AC Bus"},
        {"SpeedLink Travels", "PY14-SL-3859 | AC Bus"},
        {"Sundar Travels", "PY15-SU-4612 | AC Bus"},
        {"Greenfield Travels", "GT01-GT-1234 | AC Bus"},
        {"Chennai Link Travels", "CL02-CL-2345 | AC Bus"},
        {"Sunshine Travels", "ST03-ST-3456 | AC Bus"}
    };
    for (const auto& pair : travelData) {
        if (toLowerCase(pair.first) == travelLower) {
            cout << "Pondicherry to Chennai: " << pair.first << " - " << pair.second << endl;
            foundTravel = true;
            matchedTravel = pair.first;
        }
    }

    // MUMBAI TO THANE TRAVELS BUS DETAILS
    map<string, string> travelInfo = {
        {"CityLink Travels", "PY25-CL-1819 | AC Bus"},
        {"MetroFast Bus Co.", "PY26-MF-1920 | AC Bus"},
        {"Night Rider Express", "PY27-NR-2021 | AC Bus"},
        {"Urban Wings Express", "PY31-UW-2425 | AC Bus"},
        {"Brightway Travels", "PY32-BT-2526 | AC Bus"},
        {"Star Bus", "PY33-MS-2627 | AC Bus"},
        {"Speed Wheels Travels", "PY37-SW-3031 | AC Bus"},
        {"Horizon Bus Lines", "PY38-HB-3132 | AC Bus"},
        {"MetroLux Travels", "PY39-ML-3233 | AC Bus"},
        {"Prime City Tours", "PY43-PC-3637 | AC Bus"},
        {"SparkLine Travels", "PY44-SL-3738 | AC Bus"},
        {"Skyline Express", "PY45-SE-3839 | AC Bus"}
    };
    for (const auto& pair : travelInfo) {
        if (toLowerCase(pair.first) == travelLower) {
            cout << "Mumbai to Thane: " << pair.first << " - " << pair.second << endl;
            foundTravel = true;
            matchedTravel = pair.first;
        }
    }

    if (!foundTravel) {
        cout << "No bus operator found with the name: " << travel << endl;
        return 0;
    }

    // BOARDING POINTS
    map<string, queue<BoardingPoint>> boardingPoints;

    // Hyderabad to Pune
    boardingPoints["Sai Krishna Travels"] = queue<BoardingPoint>();
    boardingPoints["Sai Krishna Travels"].push(BoardingPoint("Kukatpally", "00:10", "Kukatpally Metro Station"));
    boardingPoints["Sai Krishna Travels"].push(BoardingPoint("Secunderabad", "00:30", "Secunderabad Railway Station"));
    boardingPoints["PVS Express"] = queue<BoardingPoint>();
    boardingPoints["PVS Express"].push(BoardingPoint("Ameerpet", "01:00", "Ameerpet Bus Stand"));
    boardingPoints["PVS Express"].push(BoardingPoint("Lakdikapul", "01:20", "Lakdikapul Metro"));
    boardingPoints["Green Line Tours"] = queue<BoardingPoint>();
    boardingPoints["Green Line Tours"].push(BoardingPoint("Gachibowli", "02:20", "Gachibowli Circle"));
    boardingPoints["Green Line Tours"].push(BoardingPoint("Hitech City", "02:40", "Hitech City Bus Stop"));
    boardingPoints["AK TOURS AND TRAVELS"] = queue<BoardingPoint>();
    boardingPoints["AK TOURS AND TRAVELS"].push(BoardingPoint("Miyapur", "06:20", "Miyapur Crossroad"));
    boardingPoints["AK TOURS AND TRAVELS"].push(BoardingPoint("Kondapur", "06:40", "Kondapur Bus Depot"));
    boardingPoints["Orange Tours and Travels"] = queue<BoardingPoint>();
    boardingPoints["Orange Tours and Travels"].push(BoardingPoint("Banjara Hills", "07:15", "Banjara Hills Road No. 1"));
    boardingPoints["Orange Tours and Travels"].push(BoardingPoint("Jubilee Hills", "07:35", "Jubilee Check Post"));
    boardingPoints["IntrCity SmartBus"] = queue<BoardingPoint>();
    boardingPoints["IntrCity SmartBus"].push(BoardingPoint("Madhapur", "08:30", "Madhapur Police Station"));
    boardingPoints["IntrCity SmartBus"].push(BoardingPoint("KPHB", "08:50", "KPHB Main Road"));
    boardingPoints["Patel Travels"] = queue<BoardingPoint>();
    boardingPoints["Patel Travels"].push(BoardingPoint("Dilsukhnagar", "12:30", "Dilsukhnagar Bus Stop"));
    boardingPoints["Patel Travels"].push(BoardingPoint("Uppal", "12:50", "Uppal Ring Road"));
    boardingPoints["Yatra Bus Services"] = queue<BoardingPoint>();
    boardingPoints["Yatra Bus Services"].push(BoardingPoint("LB Nagar", "13:15", "LB Nagar Metro"));
    boardingPoints["Yatra Bus Services"].push(BoardingPoint("Nagole", "13:35", "Nagole Bus Stop"));
    boardingPoints["Prasanna Travels"] = queue<BoardingPoint>();
    boardingPoints["Prasanna Travels"].push(BoardingPoint("SR Nagar", "14:00", "SR Nagar Bus Stand"));
    boardingPoints["Prasanna Travels"].push(BoardingPoint("Erragadda", "14:20", "Erragadda Metro"));
    boardingPoints["Shirdi Express"] = queue<BoardingPoint>();
    boardingPoints["Shirdi Express"].push(BoardingPoint("Mehdipatnam", "18:10", "Mehdipatnam Rythu Bazar"));
    boardingPoints["Shirdi Express"].push(BoardingPoint("Tolichowki", "18:30", "Tolichowki Crossroad"));
    boardingPoints["Saffron Bus Lines"] = queue<BoardingPoint>();
    boardingPoints["Saffron Bus Lines"].push(BoardingPoint("Koti", "19:00", "Koti Bus Terminus"));
    boardingPoints["Saffron Bus Lines"].push(BoardingPoint("Nampally", "19:20", "Nampally Railway Station"));
    boardingPoints["Pioneer Travels"] = queue<BoardingPoint>();
    boardingPoints["Pioneer Travels"].push(BoardingPoint("Paradise", "20:30", "Paradise Circle"));
    boardingPoints["Pioneer Travels"].push(BoardingPoint("Begumpet", "20:50", "Begumpet Airport"));

    // Bangalore to Ooty
    boardingPoints["Jetliner Bus Co."] = queue<BoardingPoint>();
    boardingPoints["Jetliner Bus Co."].push(BoardingPoint("Majestic", "00:10", "Majestic Bus Station"));
    boardingPoints["Jetliner Bus Co."].push(BoardingPoint("Koramangala", "00:30", "Koramangala Forum Mall"));
    boardingPoints["Galaxy Travels"] = queue<BoardingPoint>();
    boardingPoints["Galaxy Travels"].push(BoardingPoint("Electronic City", "01:00", "Electronics Market"));
    boardingPoints["Metro Travels"] = queue<BoardingPoint>();
    boardingPoints["Metro Travels"].push(BoardingPoint("Marathahalli", "02:20", "Marathahalli Multiplex"));
    boardingPoints["Metro Travels"].push(BoardingPoint("Whitefield", "02:40", "Whitefield ITPL"));
    boardingPoints["SAM TOURIST"] = queue<BoardingPoint>();
    boardingPoints["SAM TOURIST"].push(BoardingPoint("Madiwala", "06:15", "Madiwala Bus Stop"));
    boardingPoints["SAM TOURIST"].push(BoardingPoint("HSR Layout", "06:35", "HSR Layout BDA Complex"));
    boardingPoints["AGR Travels"] = queue<BoardingPoint>();
    boardingPoints["AGR Travels"].push(BoardingPoint("Jayanagar", "07:00", "Jayanagar 4th Block"));
    boardingPoints["AGR Travels"].push(BoardingPoint("Banashankari", "07:20", "Banashankari Bus Stand"));
    boardingPoints["Green Line Travels and Holidays"] = queue<BoardingPoint>();
    boardingPoints["Green Line Travels and Holidays"].push(BoardingPoint("Indiranagar", "07:45", "Indiranagar Metro"));
    boardingPoints["Green Line Travels and Holidays"].push(BoardingPoint("Domlur", "08:05", "Domlur Flyover"));
    boardingPoints["Royal Travels"] = queue<BoardingPoint>();
    boardingPoints["Royal Travels"].push(BoardingPoint("Kengeri", "13:15", "Kengeri Satellite Town"));
    boardingPoints["Royal Travels"].push(BoardingPoint("Rajarajeshwari Nagar", "13:35", "RR Nagar Arch"));
    boardingPoints["SRS Travels"] = queue<BoardingPoint>();
    boardingPoints["SRS Travels"].push(BoardingPoint("Vijayanagar", "14:00", "Vijayanagar Metro"));
    boardingPoints["SRS Travels"].push(BoardingPoint("Basaveshwara Nagar", "14:20", "Basaveshwara Nagar Bus Stop"));
    boardingPoints["KPN Travels"] = queue<BoardingPoint>();
    boardingPoints["KPN Travels"].push(BoardingPoint("Yeshwanthpur", "12:30", "Yeshwanthpur Railway Station"));
    boardingPoints["KPN Travels"].push(BoardingPoint("Goraguntepalya", "12:50", "Goraguntepalya Flyover"));
    boardingPoints["Orange Travels"] = queue<BoardingPoint>();
    boardingPoints["Orange Travels"].push(BoardingPoint("Hebbal", "18:10", "Hebbal Bus Stop"));
    boardingPoints["Orange Travels"].push(BoardingPoint("RT Nagar", "18:30", "RT Nagar Police Station"));
    boardingPoints["National Travels"] = queue<BoardingPoint>();
    boardingPoints["National Travels"].push(BoardingPoint("Kalyan Nagar", "19:00", "Kalyan Nagar Ring Road"));
    boardingPoints["National Travels"].push(BoardingPoint("Banaswadi", "19:20", "Banaswadi Main Road"));
    boardingPoints["Sundar Express"] = queue<BoardingPoint>();
    boardingPoints["Sundar Express"].push(BoardingPoint("KR Puram", "20:30", "KR Puram Railway Station"));
    boardingPoints["Sundar Express"].push(BoardingPoint("Tin Factory", "20:50", "Tin Factory Bus Stop"));

    // Pondicherry to Chennai
    boardingPoints["Pondy Express"] = queue<BoardingPoint>();
    boardingPoints["Pondy Express"].push(BoardingPoint("JIPMER", "00:10", "JIPMER Main Gate"));
    boardingPoints["Pondy Express"].push(BoardingPoint("Lawspet", "00:25", "Lawspet Bus Stand"));
    boardingPoints["Bay Travels"] = queue<BoardingPoint>();
    boardingPoints["Bay Travels"].push(BoardingPoint("White Town", "01:00", "White Town Promenade"));
    boardingPoints["Bay Travels"].push(BoardingPoint("Auroville", "01:15", "Auroville Visitor Center"));
    boardingPoints["Sea Breeze Tours"] = queue<BoardingPoint>();
    boardingPoints["Sea Breeze Tours"].push(BoardingPoint("Murungapakkam", "02:20", "Murungapakkam Junction"));
    boardingPoints["Sea Breeze Tours"].push(BoardingPoint("Gorimedu", "02:35", "Gorimedu Bus Stop"));
    boardingPoints["Fast Track Tours"] = queue<BoardingPoint>();
    boardingPoints["Fast Track Tours"].push(BoardingPoint("Villianur", "06:15", "Villianur Bus Stand"));
    boardingPoints["Fast Track Tours"].push(BoardingPoint("Ariankuppam", "06:30", "Ariankuppam Check Post"));
    boardingPoints["Velachery Travels"] = queue<BoardingPoint>();
    boardingPoints["Velachery Travels"].push(BoardingPoint("Reddiyarpalayam", "07:00", "Reddiyarpalayam Bus Stop"));
    boardingPoints["Velachery Travels"].push(BoardingPoint("Mudaliarpet", "07:15", "Mudaliarpet Junction"));
    boardingPoints["Royal Pondy"] = queue<BoardingPoint>();
    boardingPoints["Royal Pondy"].push(BoardingPoint("Nellithope", "07:45", "Nellithope Signal"));
    boardingPoints["Royal Pondy"].push(BoardingPoint("Orleanpet", "08:00", "Orleanpet Bus Stop"));
    boardingPoints["Greenfield Travels"] = queue<BoardingPoint>();
    boardingPoints["Greenfield Travels"].push(BoardingPoint("Kamban Nagar", "12:30", "Kamban Nagar Bus Stop"));
    boardingPoints["Greenfield Travels"].push(BoardingPoint("Venkata Nagar", "12:45", "Venkata Nagar Junction"));
    boardingPoints["Chennai Link Travels"] = queue<BoardingPoint>();
    boardingPoints["Chennai Link Travels"].push(BoardingPoint("Moolakulam", "13:15", "Moolakulam Bus Stand"));
    boardingPoints["Chennai Link Travels"].push(BoardingPoint("Rainbow Nagar", "13:30", "Rainbow Nagar Bus Stop"));
    boardingPoints["Sunshine Travels"] = queue<BoardingPoint>();
    boardingPoints["Sunshine Travels"].push(BoardingPoint("Anna Salai", "14:00", "Anna Salai Bus Stop"));
    boardingPoints["Sunshine Travels"].push(BoardingPoint("Marapalam", "14:15", "Marapalam Junction"));
    boardingPoints["Star Travels"] = queue<BoardingPoint>();
    boardingPoints["Star Travels"].push(BoardingPoint("Saradambal Nagar", "18:10", "Saradambal Nagar Bus Stop"));
    boardingPoints["Star Travels"].push(BoardingPoint("Kurinji Nagar", "18:25", "Kurinji Nagar Bus Stop"));
    boardingPoints["SpeedLink Travels"] = queue<BoardingPoint>();
    boardingPoints["SpeedLink Travels"].push(BoardingPoint("ECR", "19:00", "ECR Bus Stand"));
    boardingPoints["SpeedLink Travels"].push(BoardingPoint("Kottur", "19:15", "Kottur Bus Stop"));
    boardingPoints["Sundar Travels"] = queue<BoardingPoint>();
    boardingPoints["Sundar Travels"].push(BoardingPoint("Pudupalayam", "20:30", "Pudupalayam Bus Stop"));
    boardingPoints["Sundar Travels"].push(BoardingPoint("Nellithope Bypass", "20:45", "Nellithope Bypass"));

    // Mumbai to Thane
    boardingPoints["CityLink Travels"] = queue<BoardingPoint>();
    boardingPoints["CityLink Travels"].push(BoardingPoint("Dadar", "00:10", "Dadar TT Circle"));
    boardingPoints["CityLink Travels"].push(BoardingPoint("Sion", "00:20", "Sion Circle"));
    boardingPoints["MetroFast Bus Co."] = queue<BoardingPoint>();
    boardingPoints["MetroFast Bus Co."].push(BoardingPoint("Bandra", "01:00", "Bandra Station"));
    boardingPoints["MetroFast Bus Co."].push(BoardingPoint("Andheri", "01:15", "Andheri Metro"));
    boardingPoints["Night Rider Express"] = queue<BoardingPoint>();
    boardingPoints["Night Rider Express"].push(BoardingPoint("Vile Parle", "02:20", "Vile Parle Station"));
    boardingPoints["Night Rider Express"].push(BoardingPoint("Juhu", "02:35", "Juhu Beach"));
    boardingPoints["Urban Wings Express"] = queue<BoardingPoint>();
    boardingPoints["Urban Wings Express"].push(BoardingPoint("Khar", "06:15", "Khar Station"));
    boardingPoints["Urban Wings Express"].push(BoardingPoint("Santacruz", "06:30", "Santacruz Bus Stand"));
    boardingPoints["Brightway Travels"] = queue<BoardingPoint>();
    boardingPoints["Brightway Travels"].push(BoardingPoint("Chembur", "07:00", "Chembur Naka"));
    boardingPoints["Brightway Travels"].push(BoardingPoint("Ghatkopar", "07:15", "Ghatkopar Metro"));
    boardingPoints["Star Bus"] = queue<BoardingPoint>();
    boardingPoints["Star Bus"].push(BoardingPoint("Vikhroli", "07:45", "Vikhroli Station"));
    boardingPoints["Star Bus"].push(BoardingPoint("Kanjurmarg", "08:00", "Kanjurmarg Bus Stop"));
    boardingPoints["Speed Wheels Travels"] = queue<BoardingPoint>();
    boardingPoints["Speed Wheels Travels"].push(BoardingPoint("Powai", "12:30", "Powai Lake"));
    boardingPoints["Speed Wheels Travels"].push(BoardingPoint("Bhandup", "12:45", "Bhandup Station"));
    boardingPoints["Horizon Bus Lines"] = queue<BoardingPoint>();
    boardingPoints["Horizon Bus Lines"].push(BoardingPoint("Mulund", "13:15", "Mulund Check Naka"));
    boardingPoints["Horizon Bus Lines"].push(BoardingPoint("Airoli", "13:30", "Airoli Bridge"));
    boardingPoints["MetroLux Travels"] = queue<BoardingPoint>();
    boardingPoints["MetroLux Travels"].push(BoardingPoint("Rabale", "14:00", "Rabale Station"));
    boardingPoints["MetroLux Travels"].push(BoardingPoint("Ghansoli", "14:15", "Ghansoli Bus Stop"));
    boardingPoints["Prime City Tours"] = queue<BoardingPoint>();
    boardingPoints["Prime City Tours"].push(BoardingPoint("Koparkhairane", "18:10", "Koparkhairane Bus Depot"));
    boardingPoints["Prime City Tours"].push(BoardingPoint("Vashi", "18:25", "Vashi Plaza"));
    boardingPoints["SparkLine Travels"] = queue<BoardingPoint>();
    boardingPoints["SparkLine Travels"].push(BoardingPoint("Nerul", "19:00", "Nerul LP"));
    boardingPoints["SparkLine Travels"].push(BoardingPoint("Belapur", "19:15", "Belapur CBD"));
    boardingPoints["Skyline Express"] = queue<BoardingPoint>();
    boardingPoints["Skyline Express"].push(BoardingPoint("Kharghar", "20:30", "Kharghar Station"));
    boardingPoints["Skyline Express"].push(BoardingPoint("Kamothe", "20:45", "Kamothe Signal"));

    // Delhi to Ladakh
    boardingPoints["Himalayan Travels"] = queue<BoardingPoint>();
    boardingPoints["Himalayan Travels"].push(BoardingPoint("Kashmiri Gate", "00:10", "ISBT Kashmiri Gate"));
    boardingPoints["Himalayan Travels"].push(BoardingPoint("Majnu Ka Tila", "00:30", "Majnu Ka Tila Bus Stand"));
    boardingPoints["Snowline Express"] = queue<BoardingPoint>();
    boardingPoints["Snowline Express"].push(BoardingPoint("Red Fort", "01:00", "Red Fort Bus Stop"));
    boardingPoints["Snowline Express"].push(BoardingPoint("Daryaganj", "01:20", "Daryaganj Bus Stand"));
    boardingPoints["Peak View Bus Co."] = queue<BoardingPoint>();
    boardingPoints["Peak View Bus Co."].push(BoardingPoint("Sarai Kale Khan", "02:20", "Sarai Kale Khan ISBT"));
    boardingPoints["Peak View Bus Co."].push(BoardingPoint("Okhla", "02:40", "Okhla Bus Stand"));
    boardingPoints["Summit Travels"] = queue<BoardingPoint>();
    boardingPoints["Summit Travels"].push(BoardingPoint("Connaught Place", "06:15", "CP Bus Stop"));
    boardingPoints["Summit Travels"].push(BoardingPoint("India Gate", "06:35", "India Gate Circle"));
    boardingPoints["Glacier Roadways"] = queue<BoardingPoint>();
    boardingPoints["Glacier Roadways"].push(BoardingPoint("South Extension", "07:00", "South Ex Bus Stop"));
    boardingPoints["Glacier Roadways"].push(BoardingPoint("AIIMS", "07:20", "AIIMS Bus Stand"));
    boardingPoints["Mountaineer Bus Co."] = queue<BoardingPoint>();
    boardingPoints["Mountaineer Bus Co."].push(BoardingPoint("Hauz Khas", "07:45", "Hauz Khas Metro"));
    boardingPoints["Mountaineer Bus Co."].push(BoardingPoint("Vasant Vihar", "08:05", "Vasant Vihar Bus Depot"));
    boardingPoints["Starlight Tours"] = queue<BoardingPoint>();
    boardingPoints["Starlight Tours"].push(BoardingPoint("Rohini", "12:30", "Rohini Sector 7"));
    boardingPoints["Starlight Tours"].push(BoardingPoint("Pitampura", "12:50", "Pitampura Metro"));
    boardingPoints["Dreamland Express"] = queue<BoardingPoint>();
    boardingPoints["Dreamland Express"].push(BoardingPoint("Shalimar Bagh", "13:15", "Shalimar Bagh Bus Stop"));
    boardingPoints["Dreamland Express"].push(BoardingPoint("Azadpur", "13:35", "Azadpur Terminal"));
    boardingPoints["Terra Nova Bus Co."] = queue<BoardingPoint>();
    boardingPoints["Terra Nova Bus Co."].push(BoardingPoint("Wazirpur", "14:00", "Wazirpur Depot"));
    boardingPoints["Terra Nova Bus Co."].push(BoardingPoint("Model Town", "14:20", "Model Town Bus Stop"));
    boardingPoints["Everest Connect Travels"] = queue<BoardingPoint>();
    boardingPoints["Everest Connect Travels"].push(BoardingPoint("Karol Bagh", "18:10", "Karol Bagh Metro"));
    boardingPoints["Everest Connect Travels"].push(BoardingPoint("Rajendra Place", "18:30", "Rajendra Place Bus Stop"));
    boardingPoints["Mystic Roadways"] = queue<BoardingPoint>();
    boardingPoints["Mystic Roadways"].push(BoardingPoint("Patel Nagar", "19:00", "Patel Nagar Metro"));
    boardingPoints["Mystic Roadways"].push(BoardingPoint("Shadipur", "19:20", "Shadipur Depot"));
    boardingPoints["Highlander Express"] = queue<BoardingPoint>();
    boardingPoints["Highlander Express"].push(BoardingPoint("Kirti Nagar", "20:30", "Kirti Nagar Metro"));
    boardingPoints["Highlander Express"].push(BoardingPoint("Naraina", "20:50", "Naraina Bus Stand"));

    // Display boarding points
    cout << "\033[1m\nAvailable boarding points for \033[0m" << matchedTravel << ":\n";
    vector<string> availableBoardingPoints; // Store boarding point names for validation
    bool boardingPointsExist = false;
    if (boardingPoints.find(matchedTravel) != boardingPoints.end() && !boardingPoints[matchedTravel].empty()) {
        queue<BoardingPoint> tempQueue = boardingPoints[matchedTravel]; // Copy to preserve original
        while (!tempQueue.empty()) {
            BoardingPoint bp = tempQueue.front();
            cout << "- " << bp.name << " | Time: " << bp.time << " | Location: " << bp.location << endl;
            availableBoardingPoints.push_back(bp.name);
            tempQueue.pop();
        }
        boardingPointsExist = true;
    } else {
        cout << "No boarding points available for this travel service.\n";
        return 0;
    }

    // Get and validate boarding point
    cout << "\nEnter your preferred boarding point: ";
    string bp;
    getline(cin, bp);
    string bpLower = toLowerCase(bp);
    string matchedBoardingPoint;
    bool validBoardingPoint = false;
    for (const auto& name : availableBoardingPoints) {
        if (toLowerCase(name) == bpLower) {
            matchedBoardingPoint = name;
            validBoardingPoint = true;
            break;
        }
    }
    if (!validBoardingPoint) {
        cout << "Invalid boarding point: " << bp << ". Please choose from the available options.\n";
        return 0;
    }

    // DROPPING POINTS
    map<string, vector<DroppingPoint>> droppingPoint;

    // Hyderabad to Pune
    droppingPoint["Sai Krishna Travels"] = {
        DroppingPoint("Pune Station", "Pune", 90),
        DroppingPoint("Khadki", "Khadki Railway Station", 80),
        DroppingPoint("Swargate", "Swargate Bus Stand", 70),
        DroppingPoint("Deccan", "Deccan Gymkhana", 60)
    };
    droppingPoint["PVS Express"] = {
        DroppingPoint("Pune Station", "Pune", 85),
        DroppingPoint("Shivajinagar", "Shivaji Nagar", 75),
        DroppingPoint("Swargate", "Swargate Bus Stand", 65)
    };
    droppingPoint["Green Line Tours"] = {
        DroppingPoint("Pune Station", "Pune", 88),
        DroppingPoint("Katraj", "Katraj Depot", 78),
        DroppingPoint("Swargate", "Swargate Bus Stand", 68)
    };
    droppingPoint["AK TOURS AND TRAVELS"] = {
        DroppingPoint("Pune Station", "Pune", 87),
        DroppingPoint("Bhosari", "Bhosari Area", 77)
    };
    droppingPoint["Orange Tours and Travels"] = {
        DroppingPoint("Swargate", "Swargate Bus Stand", 86),
        DroppingPoint("Hadapsar", "Hadapsar Industrial Area", 76)
    };
    droppingPoint["IntrCity SmartBus"] = {
        DroppingPoint("Pune Station", "Pune", 89),
        DroppingPoint("Kothrud", "Kothrud Area", 79)
    };
    droppingPoint["Patel Travels"] = {
        DroppingPoint("Pune Station", "Pune", 90),
        DroppingPoint("Shivajinagar", "Shivaji Nagar", 70)
    };
    droppingPoint["Yatra Bus Services"] = {
        DroppingPoint("Pune Station", "Pune", 85),
        DroppingPoint("Swargate", "Swargate Bus Stand", 65)
    };
    droppingPoint["Prasanna Travels"] = {
        DroppingPoint("Pune Station", "Pune", 88),
        DroppingPoint("Katraj", "Katraj Depot", 68)
    };
    droppingPoint["Shirdi Express"] = {
        DroppingPoint("Pune Station", "Pune", 85),
        DroppingPoint("Navi Peth", "Navi Peth Area", 75)
    };
    droppingPoint["Saffron Bus Lines"] = {
        DroppingPoint("Swargate", "Swargate Bus Stand", 87),
        DroppingPoint("Hadapsar", "Hadapsar Industrial Area", 77)
    };
    droppingPoint["Pioneer Travels"] = {
        DroppingPoint("Pune Station", "Pune", 89),
        DroppingPoint("Kondhwa", "Kondhwa Area", 69)
    };

    // Bangalore to Ooty
    droppingPoint["Jetliner Bus Co."] = {
        DroppingPoint("Ooty Bus Stand", "Ooty", 90),
        DroppingPoint("Gudalur", "Gudalur Checkpost", 80)
    };
    droppingPoint["Galaxy Travels"] = {
        DroppingPoint("Ooty Bus Stand", "Ooty", 89),
        DroppingPoint("Coonoor", "Coonoor Town", 79)
    };
    droppingPoint["Metro Travels"] = {
        DroppingPoint("Ooty Bus Stand", "Ooty", 87),
        DroppingPoint("Mettupalayam", "Mettupalayam Town", 77)
    };
    droppingPoint["SAM TOURIST"] = {
        DroppingPoint("Ooty Bus Stand", "Ooty", 85),
        DroppingPoint("Lovedale", "Lovedale Area", 75)
    };
    droppingPoint["AGR Travels"] = {
        DroppingPoint("Ooty Bus Stand", "Ooty", 86),
        DroppingPoint("Coonoor", "Coonoor Town", 76)
    };
    droppingPoint["Green Line Travels and Holidays"] = {
        DroppingPoint("Ooty Bus Stand", "Ooty", 88),
        DroppingPoint("Gudalur", "Gudalur Checkpost", 78)
    };
    droppingPoint["Royal Travels"] = {
        DroppingPoint("Ooty Bus Stand", "Ooty", 89),
        DroppingPoint("Mettupalayam", "Mettupalayam Town", 79)
    };
    droppingPoint["SRS Travels"] = {
        DroppingPoint("Ooty Bus Stand", "Ooty", 90),
        DroppingPoint("Coonoor", "Coonoor Town", 80)
    };
    droppingPoint["KPN Travels"] = {
        DroppingPoint("Ooty Bus Stand", "Ooty", 85),
        DroppingPoint("Lovedale", "Lovedale Area", 75)
    };
    droppingPoint["Orange Travels"] = {
        DroppingPoint("Ooty Bus Stand", "Ooty", 84),
        DroppingPoint("Mettupalayam", "Mettupalayam Town", 74)
    };
    droppingPoint["National Travels"] = {
        DroppingPoint("Ooty Bus Stand", "Ooty", 83),
        DroppingPoint("Coonoor", "Coonoor Town", 73)
    };
    droppingPoint["Sundar Express"] = {
        DroppingPoint("Ooty Bus Stand", "Ooty", 85),
        DroppingPoint("Gudalur", "Gudalur Checkpost", 75)
    };

    // Pondicherry to Chennai
    droppingPoint["Pondy Express"] = {
        DroppingPoint("Chennai Central", "Chennai", 90),
        DroppingPoint("Egmore", "Chennai", 80)
    };
    droppingPoint["Bay Travels"] = {
        DroppingPoint("Chennai Central", "Chennai", 88),
        DroppingPoint("Tambaram", "Chennai", 78)
    };
    droppingPoint["Sea Breeze Tours"] = {
        DroppingPoint("Chennai Central", "Chennai", 89),
        DroppingPoint("Guindy", "Chennai", 79)
    };
    droppingPoint["Fast Track Tours"] = {
        DroppingPoint("Chennai Central", "Chennai", 87),
        DroppingPoint("Perungudi", "Chennai", 77)
    };
    droppingPoint["Velachery Travels"] = {
        DroppingPoint("Chennai Central", "Chennai", 85),
        DroppingPoint("Velachery", "Chennai", 75)
    };
    droppingPoint["Royal Pondy"] = {
        DroppingPoint("Chennai Central", "Chennai", 86),
        DroppingPoint("Adayar", "Chennai", 76)
    };
    droppingPoint["Greenfield Travels"] = {
        DroppingPoint("Chennai Central", "Chennai", 84),
        DroppingPoint("Porur", "Chennai", 74)
    };
    droppingPoint["Chennai Link Travels"] = {
        DroppingPoint("Chennai Central", "Chennai", 83),
        DroppingPoint("T Nagar", "Chennai", 73)
    };
    droppingPoint["Sunshine Travels"] = {
        DroppingPoint("Chennai Central", "Chennai", 82),
        DroppingPoint("Adyar", "Chennai", 72)
    };
    droppingPoint["Star Travels"] = {
        DroppingPoint("Chennai Central", "Chennai", 85),
        DroppingPoint("Guindy", "Chennai", 75)
    };
    droppingPoint["SpeedLink Travels"] = {
        DroppingPoint("Chennai Central", "Chennai", 84),
        DroppingPoint("Velachery", "Chennai", 74)
    };
    droppingPoint["Sundar Travels"] = {
        DroppingPoint("Chennai Central", "Chennai", 83),
        DroppingPoint("Tambaram", "Chennai", 73)
    };

    // Mumbai to Thane
    droppingPoint["CityLink Travels"] = {
        DroppingPoint("Thane Station", "Thane", 90),
        DroppingPoint("Kalyan", "Kalyan City", 80)
    };
    droppingPoint["MetroFast Bus Co."] = {
        DroppingPoint("Thane Station", "Thane", 88),
        DroppingPoint("Dombivli", "Dombivli City", 78)
    };
    droppingPoint["Night Rider Express"] = {
        DroppingPoint("Thane Station", "Thane", 85),
        DroppingPoint("Ulhasnagar", "Ulhasnagar City", 75)
    };
    droppingPoint["Urban Wings Express"] = {
        DroppingPoint("Thane Station", "Thane", 87),
        DroppingPoint("Badlapur", "Badlapur Area", 77)
    };
    droppingPoint["Brightway Travels"] = {
        DroppingPoint("Thane Station", "Thane", 86),
        DroppingPoint("Ambarnath", "Ambarnath City", 76)
    };
    droppingPoint["Star Bus"] = {
        DroppingPoint("Thane Station", "Thane", 89),
        DroppingPoint("Neral", "Neral Town", 79)
    };
    droppingPoint["Speed Wheels Travels"] = {
        DroppingPoint("Thane Station", "Thane", 84),
        DroppingPoint("Karjat", "Karjat Area", 74)
    };
    droppingPoint["Horizon Bus Lines"] = {
        DroppingPoint("Thane Station", "Thane", 83),
        DroppingPoint("Murbad", "Murbad Town", 73)
    };
    droppingPoint["MetroLux Travels"] = {
        DroppingPoint("Thane Station", "Thane", 82),
        DroppingPoint("Raigad", "Raigad District", 72)
    };
    droppingPoint["Prime City Tours"] = {
        DroppingPoint("Thane Station", "Thane", 81),
        DroppingPoint("Panvel", "Panvel City", 71)
    };
    droppingPoint["SparkLine Travels"] = {
        DroppingPoint("Thane Station", "Thane", 80),
        DroppingPoint("Alibaug", "Alibaug Area", 70)
    };
    droppingPoint["Skyline Express"] = {
        DroppingPoint("Thane Station", "Thane", 79),
        DroppingPoint("Pen", "Pen City", 69)
    };

    // Delhi to Ladakh
    droppingPoint["Himalayan Travels"] = {
        DroppingPoint("Ladakh", "Ladakh Main Station", 100),
        DroppingPoint("Leh", "Leh Town", 85)
    };
    droppingPoint["Snowline Express"] = {
        DroppingPoint("Ladakh", "Ladakh Main Station", 95),
        DroppingPoint("Kargil", "Kargil District", 80)
    };
    droppingPoint["Peak View Bus Co."] = {
        DroppingPoint("Ladakh", "Ladakh Main Station", 90),
        DroppingPoint("Srinagar", "Srinagar City", 75)
    };
    droppingPoint["Starlight Tours"] = {
        DroppingPoint("Ladakh", "Ladakh Main Station", 88),
        DroppingPoint("Manali", "Manali Town", 70)
    };
    droppingPoint["Dreamland Express"] = {
        DroppingPoint("Ladakh", "Ladakh Main Station", 85),
        DroppingPoint("Leh", "Leh Town", 68)
    };
    droppingPoint["Terra Nova Bus Co."] = {
        DroppingPoint("Ladakh", "Ladakh Main Station", 83),
        DroppingPoint("Kargil", "Kargil District", 66)
    };
    droppingPoint["Summit Travels"] = {
        DroppingPoint("Ladakh", "Ladakh Main Station", 80),
        DroppingPoint("Srinagar", "Srinagar City", 63)
    };
    droppingPoint["Glacier Roadways"] = {
        DroppingPoint("Ladakh", "Ladakh Main Station", 78),
        DroppingPoint("Manali", "Manali Town", 62)
    };
    droppingPoint["Mountaineer Bus Co."] = {
        DroppingPoint("Ladakh", "Ladakh Main Station", 75),
        DroppingPoint("Leh", "Leh Town", 60)
    };
    droppingPoint["Everest Connect Travels"] = {
        DroppingPoint("Ladakh", "Ladakh Main Station", 85),
        DroppingPoint("Kargil", "Kargil District", 70)
    };
    droppingPoint["Mystic Roadways"] = {
        DroppingPoint("Ladakh", "Ladakh Main Station", 83),
        DroppingPoint("Srinagar", "Srinagar City", 68)
    };
    droppingPoint["Highlander Express"] = {
        DroppingPoint("Ladakh", "Ladakh Main Station", 80),
        DroppingPoint("Manali", "Manali Town", 65)
    };

    // Display dropping points
    vector<string> availableDroppingPoints;
    bool droppingPointsExist = false;
    if (droppingPoint.find(matchedTravel) != droppingPoint.end() && !droppingPoint[matchedTravel].empty()) {
        priority_queue<DroppingPoint, vector<DroppingPoint>, CompareDroppingPoint> pq;
        for (const auto& dp : droppingPoint[matchedTravel]) {
            pq.push(dp);
        }

        cout << "\033[1m\nSuggested dropping points for \033[0m" << matchedTravel << ":\n";
        while (!pq.empty()) {
            DroppingPoint dp = pq.top();
            cout << "- " << dp.name << " | Location: " << dp.location << endl;
            availableDroppingPoints.push_back(dp.name);
            pq.pop();
        }
        droppingPointsExist = true;
    } else {
        cout << "\nNo dropping points available for this travel service.\n";
        return 0;
    }

    // Get and validate dropping point
    cout << "\nEnter your preferred dropping point: ";
    string droppingInput;
    getline(cin, droppingInput);
    string droppingLower = toLowerCase(droppingInput);
    string matchedDroppingPoint;
    bool validDroppingPoint = false;
    for (const auto& name : availableDroppingPoints) {
        if (toLowerCase(name) == droppingLower) {
            matchedDroppingPoint = name;
            validDroppingPoint = true;
            break;
        }
    }
    if (!validDroppingPoint) {
        cout << "Invalid dropping point: " << droppingInput << ". Please choose from the suggested options.\n";
        return 0;
    }

    // Final confirmation
    cout << "\nBooking confirmed for " << matchedTravel << ":\n";
    cout << "- Boarding: " << matchedBoardingPoint << endl;
    cout << "- Dropping: " << matchedDroppingPoint << endl;
    cout<<endl;
   
    //BUS SEATING ARRANGEMENT
    cout << "💺 BUS SEATING ARRANGEMENT : " << endl;
    cout << endl;
    vector<pair<int, int>> vec = {
            {25, 26}, {21, 22}, {17, 18}, {13, 14}, {9, 10}, {5, 6}, {1, 2}
        };
    vector<pair<int, int>> vec1 = {
            {29, 30}, {23, 24}, {19, 20}, {15, 16}, {11, 12}, {7, 8}, {3, 4}
        };
    vector<pair<int, int>> middle = {{27, 28}};
    for (int i = 0; i < vec.size(); ++i) {
            // Left side
            cout << "[" << setw(2) << (booked_seats.find(vec[i].first) != booked_seats.end() ? "XX" : to_string(vec[i].first)) << "]";
            cout << "[" << setw(2) << (booked_seats.find(vec[i].second) != booked_seats.end() ? "XX" : to_string(vec[i].second)) << "]";
            // Middle seats
            if (i == 0) {
                cout << "[" << setw(2) << (booked_seats.find(middle[0].first) != booked_seats.end() ? "XX" : to_string(middle[0].first)) << "]";
                cout << "[" << setw(2) << (booked_seats.find(middle[0].second) != booked_seats.end() ? "XX" : to_string(middle[0].second)) << "]";
            } else {
                cout << "    \t";
            }
            // Right side
            cout << "[" << setw(2) << (booked_seats.find(vec1[i].first) != booked_seats.end() ? "XX" : to_string(vec1[i].first)) << "]";
            cout << "[" << setw(2) << (booked_seats.find(vec1[i].second) != booked_seats.end() ? "XX" : to_string(vec1[i].second)) << "]" << endl;
        }
    cout << endl;
   
    // ASK USER TO SELECT SEAT NUMBERS
    head = NULL;
    int n;
    cout<<"[XX] means the seat is booked !!";
    cout<<endl;
    cout<<"Enter the number of seats required : ";
    cin>>n;
    int x;
    cout<<"Enter the seat no(s) : ";
    for(int i=0;i<n;i++){
        cin>>x;
        Insert(x);
    }
    Print();
   
    //SHOWING WHICH SEATS ARE WINDOW SEATS IN THE SELECTED SEATS
    cout<<endl;
    vector<int> windowseats = {25,21,17,13,9,5,1,30,24,20,16,12,8,4};
    WindowSeats(windowseats);
    cout<<endl;
   
    //USER DETAILS
    cout<<endl;
    t1.display();
    struct details d1;
    cout<<"Enter your name : ";
    cin>>d1.name;
 

    while (true) {
        cout << "Enter your 10-digit phone number: ";
        string input;
        cin >> input;

        bool ok = input.length() == 10 &&
                  all_of(input.begin(), input.end(), ::isdigit);

        if (ok) {
            d1.num = stoll(input);   // convert to number and store
            break;
        }

        cout << "❌  Error: phone number must contain exactly 10 digits (0-9 only).\n";
    }

    cout<<"Enter your gender : ";
    cin>>d1.g;
    cout<<"Enter your age : ";
    cin>>d1.age;
    cout<<endl;
    //CITY AND ROUTE MAPPING
    class Graph {
        public:
    unordered_map<string, vector<string>> adjList;
    void addRoute(const string& from, const string& to) {
        adjList[from].push_back(to);
    }
    void printAllPaths(const string& from, const string& to) {
        vector<string> path;
        unordered_map<string, bool> visited;
        dfs(from, to, visited, path);
    }

private:
    void dfs(const string& current, const string& destination,
             unordered_map<string, bool>& visited, vector<string>& path) {
        visited[current] = true;
        path.push_back(current);

        if (current == destination) {
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i != path.size() - 1) cout << " -> ";
            }
            cout << endl;
        } else {
            for (const string& neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    dfs(neighbor, destination, visited, path);
                }
            }
        }

        path.pop_back();
        visited[current] = false;
    }
};
    Graph g;
    if(t1.from=="Hyderabad"){
    g.addRoute("Hyderabad", "Bangalore");
    g.addRoute("Hyderabad", "Nagpur");
    g.addRoute("Hyderabad", "Pune");
      cout << "Routes from Hyderabad to Pune:\n";
        g.printAllPaths("Hyderabad", "Pune");
        cout<<endl;
    }
   
    if(t1.from=="Delhi"){
     // Add directed routes (Delhi to Ladakh via various cities)
    g.addRoute("Delhi", "Manali");
    g.addRoute("Manali", "Leh");
    g.addRoute("Leh", "Ladakh");
    g.addRoute("Delhi", "Srinagar");
    g.addRoute("Srinagar", "Kargil");
    g.addRoute("Kargil", "Ladakh");
     // Direct route from Delhi to Ladakh
    // Print the routes from Delhi
     cout << "Routes from Delhi to Ladakh:\n";
        g.printAllPaths("Delhi", "Ladakh");
        cout<<endl;
    }
    if(t1.from=="Bangalore"){
     // Add directed routes (Bangalore to Ooty via key cities)
    g.addRoute("Bangalore", "Mysore");
    g.addRoute("Mysore", "Bandipur");
    g.addRoute("Bandipur", "Coonoor");
    g.addRoute("Coonoor", "Ooty");
    // Direct route from Bangalore to Ooty
    // Print the routes from Bangalore
     cout << "Routes from Bangalore to Ooty:\n";
        g.printAllPaths("Bangalore", "Ooty");
        cout<<endl;
    }
   
    if(t1.from=="Pondicherry"){
    // Add directed routes from Pondicherry to Chennai via key towns
    g.addRoute("Pondicherry", "Tindivanam");
    g.addRoute("Tindivanam", "Melmaruvathur");
    g.addRoute("Melmaruvathur", "Chengalpattu");
    g.addRoute("Chengalpattu", "Chennai");
   // Direct route from Pondicherry to Chennai
    // Print the routes from Pondicherry
    cout << "Routes from Pondicherry to Chennai:\n";
        g.printAllPaths("Pondicherry", "Chennai");
        cout<<endl;
    }
   
    if(t1.from=="Mumbai"){
    // Add directed routes from Mumbai to Thane via intermediate cities
    g.addRoute("Mumbai", "Mulund");
    g.addRoute("Mulund", "Airoli");
    g.addRoute("Airoli", "Kopri");
    g.addRoute("Kopri", "Thane");
    // Direct route from Mumbai to Thane
    // Print the routes from Mumbai
    cout << "Routes from Mumbai to Thane:\n";
        g.printAllPaths("Mumbai", "Thane");
        cout<<endl;
    }
    //BOOKING CONFIRMATION
    cout << "Confirm booking? (y/n): ";
    char confirm;
    cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
    // Generate ticket ID
    string ticketID = generateTicketID(head);

    // Get boarding point time
    string boardingTime = "";
    if (boardingPoints.find(matchedTravel) != boardingPoints.end()) { // Use matchedTravel
    queue<BoardingPoint> tempQueue = boardingPoints[matchedTravel];
        while (!tempQueue.empty()) {
            BoardingPoint bp_temp = tempQueue.front();
            if (caseInsensitiveMatch(bp_temp.name, bp)) {
                boardingTime = bp_temp.time;
                break;
            }
            tempQueue.pop();
        }
    }
    // Get dropping point time (based on bus schedule arrival time)
    string droppingTime = "";
    map<string, string> scheduleArrivalTimes = {
    // Hyderabad to Pune
    {"Sai Krishna Travels", "09:40"}, {"PVS Express", "10:30"}, {"Green Line Tours", "11:50"},
    {"AK TOURS AND TRAVELS", "18:55"}, {"Orange Tours and Travels", "19:50"}, {"IntrCity SmartBus", "21:05"},
    {"Patel Travels", "22:00"}, {"Yatra Bus Services", "22:45"}, {"Prasanna Travels", "23:30"},
    {"Shirdi Express", "03:40"}, {"Saffron Bus Lines", "04:30"}, {"Pioneer Travels", "06:00"},
    // Bangalore to Ooty
    {"Jetliner Bus Co.", "09:15"}, {"Galaxy Travels", "10:05"}, {"Metro Travels", "11:25"},
    {"SAM TOURIST", "15:20"}, {"AGR Travels", "16:05"}, {"Green Line Travels and Holidays", "16:50"},
    {"KPN Travels", "21:35"}, {"Royal Travels", "22:20"}, {"SRS Travels", "23:05"},
    {"Orange Travels", "03:15"}, {"National Travels", "04:05"}, {"Sundar Express", "05:35"},
    // Pondicherry to Chennai
    {"Pondy Express", "03:15"}, {"Bay Travels", "04:05"}, {"Sea Breeze Tours", "05:25"},
    {"Fast Track Tours", "09:20"}, {"Velachery Travels", "10:05"}, {"Royal Pondy", "10:50"},
    {"Greenfield Travels", "15:35"}, {"Chennai Link Travels", "16:20"}, {"Sunshine Travels", "17:05"},
    {"Star Travels", "21:15"}, {"SpeedLink Travels", "22:05"}, {"Sundar Travels", "23:35"},
    // Mumbai to Thane
    {"CityLink Travels", "01:25"}, {"MetroFast Bus Co.", "02:15"}, {"Night Rider Express", "03:35"},
    {"Urban Wings Express", "07:30"}, {"Brightway Travels", "08:15"}, {"Star Bus", "09:00"},
    {"Speed Wheels Travels", "13:45"}, {"Horizon Bus Lines", "14:30"}, {"MetroLux Travels", "15:15"},
    {"Prime City Tours", "19:25"}, {"SparkLine Travels", "20:15"}, {"Skyline Express", "21:45"},
    // Delhi to Ladakh (assuming next day arrival)
    {"Himalayan Travels", "03:10"}, {"Snowline Express", "04:00"}, {"Peak View Bus Co.", "05:20"},
    {"Summit Travels", "09:15"}, {"Glacier Roadways", "10:00"}, {"Mountaineer Bus Co.", "10:45"},
    {"Starlight Tours", "15:30"}, {"Dreamland Express", "16:15"}, {"Terra Nova Bus Co.", "17:00"},
    {"Everest Connect Travels", "21:10"}, {"Mystic Roadways", "22:00"}, {"Highlander Express", "23:30"}
    };
    if (scheduleArrivalTimes.find(travel) != scheduleArrivalTimes.end()) {
    droppingTime = scheduleArrivalTimes[travel];
    }
       
    // Format travel date
    string travelDate = to_string(date) + "/" + (month < 10 ? "0" : "") + to_string(month);
    if (scheduleArrivalTimes.find(matchedTravel) != scheduleArrivalTimes.end()) { // Use matchedTravel
        droppingTime = scheduleArrivalTimes[matchedTravel];
    }

    // Display booking summary
    displayBookingSummary(ticketID, d1, bp, boardingTime, droppingInput, droppingTime,
                         head, travelDate, matchedTravel, t1.from, t1.to); // Use matchedTravel
    // TOTAL PRICE
    int Total_Price = TotalPrice(n, t1, windowseats);
    cout << "Total Price = " << Total_Price << endl;
    cout << "Extra charge for window seats - ₹100 for each" << endl;
    cout << "=============================\n" << endl;
   
    //RECENT TICKETS BOOKED
    stack<string> recentTicket;
    recentTicket.push(t1.to);
    recentTicket.push(t1.from);
    recentTicket.push(travel);
    cout << "\nRecent tickets booked:\n";
    while(!recentTicket.empty()){
    cout<<recentTicket.top()<<" ";
    recentTicket.pop();
    }
    cout<<endl;
    }
    cout<<"\t \t \t \t \t \tYour booking is successful!!"<<endl;
    cout << "\nHello, user ! 🚍 ✨ Start booking your ticket and have an amazing journey ahead 🌟 (y/n) : ";
    cin >> continue_booking;
    cout << endl;
    } while (continue_booking == 'y' || continue_booking == 'Y');
    return 0;
}
