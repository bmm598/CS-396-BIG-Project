#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include "geometry.h"
#include "parser.h"

using namespace std;

auto getPoints(std::string outputFile) {
    ifstream f("output.json");
    json j;
    f >> j;
   
    auto points = j["points"];
    for (auto& p : points) {
        cout << "Point: (" << p["x"] << ", " << p["y"] << ")\n";
    }
    return points;
}

int main() {
    std::string outputFile = "output.json";
    std::vector<double> pts;
    bool addPoints = true;
    char res;
    double x;
    double y;

    cout << "=== Geometry Engine ===" << endl;
    cout << "Please add a point: " << endl;

    // get user input for point values
    while (addPoints) {
        cout << "X Value: ";
        cin >> x;
        while(cin.fail()) {
            cout << "Please enter an number: ";
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
            cout << "Please enter an number: ";
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
            while(res != 'y' && res != 'Y' && res != 'n' && res != 'N') {
                cout << "Please enter y or n: ";
                cin.clear();
                cin.ignore(256,'\n');
                cin >> res;
            }
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
    cout << "=== Scheme Integration ===" << endl;
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

    auto points = getPoints(outputFile);

    cout << endl;
    cout << "=== Prolog Validation ===" << endl;
    cout << endl;
    parsePoints(points, pts.size()/2);
    draftQueries(pts.size()/2);
    cmd = "swipl -s ../../prolog/main.pl -g \"run_query_from_file('queries.pl')\" -t halt.";
    system(cmd.c_str());

    cout << endl;
    cout << "=== C++ Integration ===" << endl;
    cout << endl;
    cout << "Numerical Operations: " << endl;
    cout << endl;

    // compute distances and perimeter of geometry
    cout << "Computing Distances: " << endl;
    distances(points, pts.size()/2);
    perimeter(points, pts.size()/2);
    cout << endl;

    cout << "Find Centroid/Midpoint: " << endl;
    centroid(points, pts.size()/2);
    cout << endl;
    
    cout << "Translation: " << endl;

    // get user input for translation value
    double t_x;
    double t_y;
    cout << "What would you like to translate by in the x-axis? ";
    cin >> t_x;
    while(cin.fail()) {
        cout << "Please enter an number: ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> t_x;
    }
    cin.clear();
    cin.ignore(256,'\n');
    
    cout << "What would you like to translate by in the y-axis? ";
    cin >> t_y;
    while(cin.fail()) {
        cout << "Please enter an number: ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> t_y;
    }
    cin.clear();
    cin.ignore(256,'\n');
    
    // translate by value
    translate_x(points, t_x, pts.size()/2, outputFile);
    points = getPoints(outputFile);
    translate_y(points, t_y, pts.size()/2, outputFile);
    points = getPoints(outputFile); 
    cout << endl;

    cout << "Find Centroid/Midpoint: " << endl;
    centroid(points, pts.size()/2);
    cout << endl;

    // get user input for scale factor
    double factor;
    cout << "What factor would you like to scale by? ";
    cin >> factor;
    while(cin.fail()) {
        cout << "Please enter an number: ";
        cin.clear();
        cin.ignore(256,'\n');
        cin >> factor;
    }
    cin.clear();
    cin.ignore(256,'\n');

    cout << "Scale about the centroid: " << endl;
    scale(points, factor, pts.size()/2, outputFile);
    points = getPoints(outputFile);
    cout << endl;

    cout << "Computing Distances: " << endl;
    distances(points, pts.size()/2);
    perimeter(points, pts.size()/2);
    cout << endl;

    cout << "Find Centroid/Midpoint: " << endl;
    centroid(points, pts.size()/2);

    cout << endl;
    cout << "=== Prolog Validation ===" << endl;
    cout << endl;
    parsePoints(points, pts.size()/2);
    draftQueries(pts.size()/2);
    cmd = "swipl -s ../../prolog/main.pl -g \"run_query_from_file('queries.pl')\" -t halt.";
    system(cmd.c_str());

    cout << endl;
    cout << "=== End of Geometry Engine ===" << endl;
    cout << endl;

    return 0;
}