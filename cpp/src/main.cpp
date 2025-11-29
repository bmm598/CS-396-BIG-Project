#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;

// #include "geometry.h"

using namespace std;

int main() {
    std::string outputFile = "output.json";
    std::vector<int> pts;
    bool addPoints = true;
    char res;
    int x;
    int y;

    cout << "=== Geometry Engine ===" << endl;
    cout << "Please add a point: " << endl;

    while (addPoints) {
        cout << "X Value: ";
        cin >> x;
        while(cin.fail()) {
            cout << "Please enter an integer: ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> x;
        }
        cin.clear();
        cin.ignore(256,'\n');

        pts.push_back(x);

        cout << "Y Value: ";
        cin >> y;
        while(cin.fail()) {
            cout << "Please enter an integer: ";
            cin.clear();
            cin.ignore(256,'\n');
            cin >> y;
        }
        cin.clear();
        cin.ignore(256,'\n');

        pts.push_back(y);

        cout << "Point " << "(" << x << ", " << y << ")" << " added." << endl; 

        if(pts.size()>2) {
            cout << "Would you like to add another point? y/n ";
            cin >> res;
            if(res == 'y' || res == 'Y') {
                addPoints = true;
            }
            else {
                addPoints = false;
            }
        } else {
            cout << "Please add another point." << endl;
        }
    }

    cout << endl;
    cout << "Using Scheme to generate points:" << endl;

    // append point arguments to a string to be parsed in the command
    std::string args;
    for (std::size_t i = 0; i < pts.size(); i++) {
        args += std::to_string(pts[i]) + " ";
    };

    // create command
    std::string cmd = "racket ../../scheme/src/export-json.rkt " + outputFile + " " + args;
    system(cmd.c_str());

    ifstream f("output.json");
    json j;
    f >> j;
   
    auto points = j["points"];
    for (auto& p : points) {
        cout << "Point: (" << p["x"] << ", " << p["y"] << ")\n";
    }



    return 0;
}