#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;

auto updatePoints(std::string outputFile);

void distances(nlohmann::json_abi_v3_11_3::basic_json<> pts, size_t size);

void perimeter(nlohmann::json_abi_v3_11_3::basic_json<> pts, size_t size);

void translate_x(nlohmann::json_abi_v3_11_3::basic_json<> pts, double t, size_t size, std::string outputFile);

void translate_y(nlohmann::json_abi_v3_11_3::basic_json<> pts, double t, size_t size, std::string outputFile);

void centroid(nlohmann::json_abi_v3_11_3::basic_json<> pts, size_t size);

void scale(nlohmann::json_abi_v3_11_3::basic_json<> pts, int s, size_t size, std::string outputFile);

std::string scaleHelper(nlohmann::json_abi_v3_11_3::basic_json<> pts, int s, size_t size, double cx, double cy);

#endif