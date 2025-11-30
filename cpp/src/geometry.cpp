#include "geometry.h"

auto updatePoints(std::string outputFile) {
    ifstream f(outputFile);
    json j;
    f >> j;
   
    auto points = j["points"];
    // for (auto& p : points) {
    //     cout << "Point: (" << p["x"] << ", " << p["y"] << ")\n";
    // }
    return points;
}

void distances(nlohmann::json_abi_v3_11_3::basic_json<> pts, size_t size) {
    double d;
    // cout << pts[0]["x"] << pts[0]["y"] << endl;
    // loop through all points in order and calc distance for each
    for(size_t i = 0; i < size-1; i++) {
        // cout << pts[i+1]["x"] << "-" << pts[i]["x"] << endl;
        // cout << (int)pts[i+1]["x"] - (int)pts[i]["x"] << endl;
        d = sqrt(pow((double)pts[i+1]["x"] - (double)pts[i]["x"], 2) + pow((double)pts[i+1]["y"] - (double)pts[i]["y"], 2));
        cout << "Distance between Point: (" << pts[i]["x"] << ", " << pts[i]["y"] << 
        ") and Point: " << pts[i+1]["x"] << ", " << pts[i+1]["y"] << ") is: " << d << endl;
    }
    if(size > 2) {
        // calc distance between last point and first point
        d = sqrt(pow((double)pts[0]["x"] - (double)pts[size-1]["x"], 2) + pow((double)pts[0]["y"] - (double)pts[size-1]["y"], 2));

        cout << "Distance between Point: (" << pts[size-1]["x"] << ", " << pts[size-1]["y"] << 
        ") and Point: " << pts[0]["x"] << ", " << pts[0]["y"] << ") is: " << d << endl;
    }
}

void perimeter(nlohmann::json_abi_v3_11_3::basic_json<> pts, size_t size) {
    if(size > 2) {
        double d;
        double sum = 0;
        for(size_t i = 0; i < (size)-1; i++) {
            d = sqrt(pow((double)pts[i+1]["x"] - (double)pts[i]["x"], 2) + pow((double)pts[i+1]["y"] - (double)pts[i]["y"], 2));
            sum += d;
        }
        if(size > 2) {
            d = sqrt(pow((double)pts[0]["x"] - (double)pts[size-1]["x"], 2) + pow((double)pts[0]["y"] - (double)pts[size-1]["y"], 2));
            sum += d;
        }
        cout << "Total perimeter of geometry: " << sum << endl;
    } else {
        cout << "A segment does not have a perimeter" << endl;
    }
}

void translate_x(nlohmann::json_abi_v3_11_3::basic_json<> pts, double t, size_t size, std::string outputFile) {
    std::vector<double> points;
    for(size_t i = 0; i < size; i++) {
        points.push_back((double)pts[i]["x"]+t);
        points.push_back((double)pts[i]["y"]);
    }
    std::string args;
    for (std::size_t i = 0; i < points.size(); i++) {
        args += std::to_string(points[i]) + " ";
    };

    if(size > 2) {
        cout << "Translating polygon by " << t << " on the x-axis" << endl;
    } else {
        cout << "Translating segment by " << t << " on the x-axis" << endl;
    }

    std::string cmd = "racket ./scheme/src/export-json.rkt " + outputFile + " " + args;
    system(cmd.c_str());
}

void translate_y(nlohmann::json_abi_v3_11_3::basic_json<> pts, double t, size_t size, std::string outputFile) {
    std::vector<double> points;
    for(size_t i = 0; i < size; i++) {
        points.push_back((double)pts[i]["x"]);
        points.push_back((double)pts[i]["y"]+t);
    }
    std::string args;
    for (std::size_t i = 0; i < points.size(); i++) {
        args += std::to_string(points[i]) + " ";
    };

    if(size > 2) {
        cout << "Translating polygon by " << t << " on the y-axis" << endl;
    } else {
        cout << "Translating segment by " << t << " on the y-axis" << endl;
    }

    std::string cmd = "racket ./scheme/src/export-json.rkt " + outputFile + " " + args;
    system(cmd.c_str());
}

void centroid(nlohmann::json_abi_v3_11_3::basic_json<> pts, size_t size) {
    double x_sum = 0;
    double y_sum = 0;
    
    for(size_t i = 0; i < size; i++) {
        x_sum += (double)pts[i]["x"];
        y_sum += (double)pts[i]["y"];
    }

    double x_coord = x_sum/(size);
    double y_coord = y_sum/(size);

    if(size > 2) {
        cout << "The centroid of the polygon is: (" << x_coord << ", " << y_coord << ")" << endl;
    } else {
        cout << "The midpoint of the segment is: (" << x_coord << ", " << y_coord << ")" << endl;
    }
}

void scale(nlohmann::json_abi_v3_11_3::basic_json<> pts, int s, size_t size, std::string outputFile) {
    double x_sum = 0;
    double y_sum = 0;
    
    for(size_t i = 0; i < size; i++) {
        x_sum += (double)pts[i]["x"];
        y_sum += (double)pts[i]["y"];
    }

    double x_coord = x_sum/(size);
    double y_coord = y_sum/(size);

    cout << "Scale by a factor of " << s << ": " << endl;

    std::string args = scaleHelper(pts, s, size, x_coord, y_coord);

    std::string cmd = "racket ./scheme/src/export-json.rkt " + outputFile + " " + args;
    system(cmd.c_str());
    pts = updatePoints(outputFile);
}

std::string scaleHelper(nlohmann::json_abi_v3_11_3::basic_json<> pts, int s, size_t size, double cx, double cy) {
    std::vector<double> points;
    for(size_t i = 0; i < size; i++) {
        points.push_back(s*((double)pts[i]["x"] - cx) + cx);
        points.push_back(s*((double)pts[i]["y"] - cy) + cy);
    }
    std::string args;
    for (std::size_t i = 0; i < points.size(); i++) {
        args += std::to_string(points[i]) + " ";
    }
    // cout << args << endl;
    return args;
}