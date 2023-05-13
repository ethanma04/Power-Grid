//Power Grid
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

struct district{
  string name;
  string type;
  int num_resident;
  int power;
  bool has_power;
  int num_technician;
  string technicians[10]; //<- string array



};

void load(string fname, district districts[], int &num, int &power) {

  ifstream fin(fname);
  
  fin >> power >> num;

  
  fin.ignore();



  for(int i = 0; i < num; i++) { 
    getline(fin, districts[i].name);
    //cout << districts[i].name << endl;
    fin >> districts[i].type;
    //cout << districts[i].type << endl;
    fin >> districts[i].num_resident; 
    //cout << districts[i].num_resident << endl;
    fin >> districts[i].power; 
    //cout << districts[i].power << endl;
    fin >> districts[i].has_power; 
    //cout << districts[i].has_power << endl;
    fin >> districts[i].num_technician;
    //cout << districts[i].num_technician << endl;

    fin.ignore();
    for(int j = 0; j < districts[i].num_technician; j++) {

      getline(fin, districts[i].technicians[j]);
      //cout <<  districts[i].technicians[j] << endl;
    }
      
  }
  fin.close();

}

void save(string fname, district districts[], int num, int power) {
  ofstream fout(fname);

  fout << power << endl;
  fout << num << endl;




  for(int i = 0; i < num; i++) { 
    fout << districts[i].name << endl;
    //cout << districts[i].name << endl;
    fout << districts[i].type << endl;
    //cout << districts[i].type << endl;
    fout << districts[i].num_resident << endl; 
    //cout << districts[i].num_resident << endl;
    fout << districts[i].power << endl; 
    //cout << districts[i].power << endl;
    fout << districts[i].has_power << endl; 
    //cout << districts[i].has_power << endl;
    fout << districts[i].num_technician << endl;
    //cout << districts[i].num_technician << endl;


    for(int j = 0; j < districts[i].num_technician; j++) {

      fout << districts[i].technicians[j] << endl;
      //cout <<  districts[i].technicians[j] << endl;
    }
      
  }
}

void print_all(int numDis, district districts[], int power) {
  int demand = 0;
  district temp;
  cout << "The current power supply is " << power << "MW." << endl;
  for(int i = 0; i < numDis - 1; i++) {
    for(int j = 0; j < numDis - 1; j++) {
        if(districts[j].num_resident > districts[j+1].num_resident){
          
          temp.name = districts[j].name;
          districts[j].name = districts[j+1].name;
          districts[j+1].name = temp.name;      

          temp.type = districts[j].type;
          districts[j].type = districts[j+1].type;
          districts[j+1].type = temp.type;

          temp.has_power = districts[j].has_power;
          districts[j].has_power = districts[j+1].has_power;
          districts[j+1].has_power = temp.has_power;

          temp.num_resident = districts[j].num_resident;
          districts[j].num_resident = districts[j+1].num_resident;
          districts[j+1].num_resident = temp.num_resident;

          temp.power = districts[j].power;
          districts[j].power = districts[j+1].power;
          districts[j+1].power = temp.power;

          temp.num_technician = districts[j].num_technician;
          for(int k = 0; k < districts[j].num_technician; k++) {
            temp.technicians[k] = districts[j].technicians[k];
          }
          districts[j].num_technician = districts[j+1].num_technician;
          for(int k = 0; k < districts[j+1].num_technician; k++) {
            districts[j].technicians[k] = districts[j+1].technicians[k];
          }
          districts[j+1].num_technician = temp.num_technician;
          for(int k = 0; k < temp.num_technician; k++) {
            districts[j+1].technicians[k] = temp.technicians[k];
          }

        }
    }
   }
  for(int i = 0; i < numDis; i++) {
    if(!districts[i].has_power) {
      temp.power = districts[i].power;
      districts[i].power = 0;
    }
    cout << districts[i].name << endl;
    cout << "District type: " << districts[i].type << endl;
    cout << "Number of residents: " << districts[i].num_resident << endl;
    cout << "Power use: " << districts[i].power << "MW" << endl;
    cout << "Has power: " << districts[i].has_power << endl;
    
    if(districts[i].num_technician > 0) {
      cout << "Technicians: ";
      for(int j = 0; j < districts[i].num_technician; j++) {
        if(j == districts[i].num_technician - 1) {
          cout << districts[i].technicians[j] << endl;
        }
        else {
          cout << districts[i].technicians[j] << ", ";
        }
      }
    }
    cout << "---" << endl;
    demand += districts[i].power;
  
  }
  if (power < demand) {
    cout << "Critical Error! The current power supply of " << power << "MW is insufficient to supply " << demand << "MW of power demand. Please shut off one or more districts." << endl;
    cout << "---" << endl;
  }
}

void assign_technician(string tech_name, string district_name, district districts[], int num_district) {
  bool check = false;
  for(int i = 0; i < num_district; i++) {
    if(districts[i].name == district_name) {
      districts[i].num_technician ++;
      districts[i].technicians[districts[i].num_technician - 1] = tech_name;
      check = true;
      break;

    }
        
  }
      

  if(check) {
    cout << "Technician assigned!" << endl;
  }
  else {
    cout << "Error! The district with that name doesn't exist." << endl;
  }
}

void cut_power(string district_name, district districts[], int numDis) {
  bool check = false;
  cout << "Enter the name of the district:" << endl;
  cin.ignore();
  getline(cin, district_name);
  for(int i = 0; i < numDis; i++) {
    if(district_name == districts[i].name) {
      districts[i].has_power = false;
      check = true;
      cout << "The district's power has been successfully turned off." << endl;
      break;
    }
  }

  if(!check) {
    cout << "Error! The district with that name doesn't exist." << endl;
  }  
}

void restore_power(string district_name, district districts[], int numDis) {

  bool check = false;
  cout << "Enter the name of the district:" << endl;
  cin.ignore();
  getline(cin, district_name);
  for(int i = 0; i < numDis; i++) {
    if(district_name == districts[i].name) {
      districts[i].has_power = true;
      districts[i].power = 100;
      check = true;
      cout << "The district's power has been successfully turned back on." << endl;
      break;
    }
  }
  if(!check) {
    cout << "Error! The district with that name doesn't exist." << endl;
  }
  
}

int main() {
  string fname, district_name, tech_name;
  int option, power = 0, num = 0;
  district districts[10];
  bool menu = true;
  
  cout << "Please enter the name of the file to load:" << endl;
  cin >> fname;
  

  load(fname, districts, num, power);
  print_all(num, districts, power);

  while(menu) {
    cout << "Main Menu" << endl;
    cout << "1- Status" << endl;
    cout << "2- Set Power Supply" << endl;
    cout << "3- Shutoff Power" << endl;
    cout << "4- Restore Power" << endl;
    cout << "5- Assign Technician" << endl;
    cout << "6- Save" << endl;
    cout << "7- Load" << endl;
    cout << "8- Exit" << endl;
    cout << "Please enter your choice:" << endl;
    cin >> option;

    if(option == 1) {
      print_all(num, districts, power);
    }
    else if(option == 2) {
      cout << "Enter the updated power supply in megawatts:" << endl;
      cin >> power;
      
    }
    else if(option == 3) {
      cut_power(district_name, districts, num);
    }

    else if(option == 4) {
      restore_power(district_name, districts, num);
    }
    else if(option == 5) {
      cout << "Enter the name of the technician:" << endl;
      cin.ignore();
      getline(cin, tech_name);
      cout << "Enter the name of the district to assign them to:" << endl;
      
      getline(cin, district_name);
      assign_technician(tech_name, district_name, districts, num);
      
    }
    else if(option == 6) {
      cout << "Enter the file name to save to:" << endl;
      cin >> fname;
      save(fname, districts, num, power);
      
    }
    else if(option == 7) {
      cout << "Enter the file name to load from:" << endl;
      cin.ignore();
      cin >> fname;
      load(fname, districts, num, power);
      
    }
    else if(option == 8) {
      menu = false;
    }
    else {
      cout << "Invalid option!" << endl;
    }
    

    
  }
  
  return 0;
}