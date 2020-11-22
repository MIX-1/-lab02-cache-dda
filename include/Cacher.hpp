// Copyright 2020 MIX-1 <danilonil1@yandex.ru>

#ifndef INCLUDE_CACHER_HPP_
#define INCLUDE_CACHER_HPP_
#include <iostream>
#include <string>
#include <chrono>
#include <vector>
#include <set>

using std :: cout;
using string = std :: string;

const int Experiment_Size[5] = {8192, 65536, 131072, 262144, 786432};
[[maybe_unused]] const string Experiment_Size_Name[5] = {
    "128 kb",
    "1 mb",
    "2 mb",
    "4 mb",
    "12 mb"
};
[[maybe_unused]] const string Experiment_Type[3] = {"Straight", "Reverse", "Random"};
const int Num_Investigation = 3;
const int Num_Experiment = 5;
const int Num_Repeat = 1000;
const int Num_Data_In_Line = 4;

class Cacher {
 public:
  enum Type {Straight, Reverse, Random};

  explicit Cacher(std::vector<Type>);

  Cacher() = delete;

  friend std::ostream& operator<<(std::ostream&, const Cacher&);

 private:
  int duration[Num_Investigation][Num_Experiment];
};

#endif // INCLUDE_CACHER_HPP_

