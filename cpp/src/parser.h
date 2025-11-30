#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;

void parsePoints(nlohmann::json_abi_v3_11_3::basic_json<> pts, size_t size);

void draftQueries(size_t size);

std::string closedQuery(size_t size);

std::string validPointCount(size_t size);

std::string intersectingPoints(size_t size);

std::string collinearPoints(size_t size);

std::string allCollinear(size_t size);

#endif