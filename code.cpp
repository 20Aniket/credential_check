#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

const int ValidCredentials = 0;
const int IncorrectPassword = 1;
const int IncorrectCredentials = 2;

int checkCredentials(string username, string password) {
  ifstream file("login.csv");
  string line;
  while (getline(file, line)) {
    size_t commaPos = line.find(',');
    string fileUsername = line.substr(0, commaPos);
    string filePassword = line.substr(commaPos + 1);
    if (fileUsername == username) {
      if (filePassword == password) {
        return ValidCredentials;
      } else {
        return IncorrectPassword;
      }
    }
  }
  return IncorrectCredentials;
}

void printmenu(string username, string password) {
  char order;
  double Total = 0.0;
  string orderDetails;
  cout << left << setw(10) << "Code" << setw(20) << "Item"
       << "Price"
       << "\n";
  cout << "-----------------------------------\n";
  cout << left << setw(10) << "R" << setw(20) << "Rice Pilaf"
       << "$5.00"
       << "\n";
  cout << left << setw(10) << "F" << setw(20) << "French Potatoes"
       << "$2.25"
       << "\n";
  cout << left << setw(10) << "T" << setw(20) << "Tuna on Toast"
       << "$7.00"
       << "\n";
  cout << left << setw(10) << "G" << setw(20) << "Grilled Cheese"
       << "$6.75"
       << "\n";
  cout << left << setw(10) << "S" << setw(20) << "Veggie Samosa"
       << "$1.00"
       << "\n";
  cout << left << setw(10) << "D" << setw(20) << "Soft Drinks"
       << "$1.25"
       << "\n";
  do {
    cout << "What would you like to order? (Enter '$' to finish ordering): ";
    cin >> order;
    switch (order) {
    case 'R':
      Total += 5.00;
      orderDetails += "Rice Pilaf, ";
      break;
    case 'F':
      Total += 2.25;
      orderDetails += "French Potatoes, ";
      break;
    case 'T':
      Total += 7.00;
      orderDetails += "Tuna on Toast, ";
      break;
    case 'G':
      Total += 6.75;
      orderDetails += "Grilled Cheese, ";
      break;
    case 'S':
      Total += 1.00;
      orderDetails += "Veggie Samosa, ";
      break;
    case 'D':
      Total += 1.25;
      orderDetails += "Soft Drinks, ";
      break;
    case '$':
      break;
    default:
      cout << "That is not a proper menu choice. Try again" << endl;
      break;
    }
  } while (order != '$');
  char choice;
  cout << "Your total is $" << Total << ". Do you want to pay? (Y/N): ";
  cin >> choice;
  if (choice == 'Y' || choice == 'y') {
    if (!orderDetails.empty()) {
      orderDetails.pop_back();
      orderDetails.pop_back();
    }
    time_t now = time(0);
    tm *current_time = localtime(&now);
    char *datetime = asctime(current_time);
    ofstream file("login.csv", ios::app);
    if (file.is_open()) {
      file << username << "," << password << "," << datetime << ","
           << "Total: $" << Total << "," << orderDetails << "\n";
      file.close();
      cout << "Order details saved successfully for " << username << ".\n";
    } else {
      cout << "Unable to open file to save order details.\n";
    }
    cout << "Thank you for your order!\n";
  } else {
    cout << "Thank you for visiting the Jass Cafe!\n";
  }
}

int main() {
  string username;
  string password;
  bool done = false;
  do {
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    int status = checkCredentials(username, password);
    switch (status) {
    case ValidCredentials:
      cout << "Valid credentials.\n";
      printmenu(username, password);
      break;
    case IncorrectPassword:
      cout << "Incorrect password. Please try again.\n";
      break;
    case IncorrectCredentials:
      ofstream file("login.csv", ios::app);
      if (file.is_open()) {
        file << username << "," << password << "\n";
        file.close();
        cout << "Credentials saved successfully.\n";
      } else {
        cout << "Unable to create file for writing.\n";
      }
      break;
    }
    char continueChoice;
    cout << "Are you ready to place an order? (Y/N): ";
    cin >> continueChoice;
    if (continueChoice != 'Y' && continueChoice != 'y') {
      done = true;
    }
  } while (!done);
}