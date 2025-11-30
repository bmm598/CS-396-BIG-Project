#include "parser.h"

void parsePoints(nlohmann::json_abi_v3_11_3::basic_json<> pts, size_t size) {
    
    std::ofstream pl("../../prolog/geometry.pl");

    for (size_t i = 0; i < size; i++) {
        pl << "point(p" << i+1 << "," << pts[i]["x"] << "," << pts[i]["y"] << ")." << endl;
    }

    for (size_t i = 0; i < size; i++) {
        size_t j = (i+1) % size;
        pl << "segment(s" << i+1 << ",p" << i+1 << ",p" << j+1 << ")." << endl;
    }

    pl.close();

    cout << "geometry.pl written." << endl;
}

void draftQueries(size_t size) {
    std::ofstream pl("queries.pl");

    pl << closedQuery(size) << endl;

    pl << "duplicate_point_values." << endl;

    pl << validPointCount(size) << endl;

    pl << intersectingPoints(size) << endl;

    pl << collinearPoints(size) << endl;

    pl << allCollinear(size) << endl;

    pl.close();

    cout << "queries.pl written." << endl;
}

std::string closedQuery(size_t size) {
    std::string query = "closed_polygon([";
    for (size_t i = 0; i < size; i++) {
        query += "p" + std::to_string(i + 1);
        if (i < size - 1) query += ",";
    }
    query += "]).";
    return query;
}

std::string validPointCount(size_t size) {
    std::string query = "valid_point_count([";
    for (size_t i = 0; i < size; i++) {
        query += "p" + std::to_string(i + 1);
        if (i < size - 1) query += ",";
    }
    query += "])."; 
    return query;
}

std::string intersectingPoints(size_t size) {
    std::string query = "segments_intersect([";
    for (size_t i = 0; i < size; i++) {
        query += "s" + std::to_string(i + 1);
        if (i < size - 1) query += ",";
    }
    query += "])."; 
    return query;
}

std::string collinearPoints(size_t size) {
    std::string query = "more_than_two_collinear([";
    for (size_t i = 0; i < size; i++) {
        query += "p" + std::to_string(i + 1);
        if (i < size - 1) query += ",";
    }
    query += "])."; 
    return query;
}

std::string allCollinear(size_t size) {
    std::string query = "all_collinear([";
    for (size_t i = 0; i < size; i++) {
        query += "p" + std::to_string(i + 1);
        if (i < size - 1) query += ",";
    }
    query += "])."; 
    return query;
}