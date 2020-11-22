// Copyright 2020 MIX-1 <danilonil1@yandex.ru>

#include <Cacher.hpp>

Cacher::Cacher(std::vector<Type> types) {
    for (int t = 0; t < 3; ++t) {
        switch (types[t]) {
            case Straight:
                for (int j = 0; j < Num_Experiment; ++j) {
                    auto arr1 = new long double[Experiment_Size[j]];
                    long double k = 0;
                    // Warming
                    for (int i = 0;
                         i < Experiment_Size[j];
                         i += Num_Data_In_Line) {
                        arr1[i] = random();
                    }
                    // Experiment
                    std::chrono::system_clock::time_point start =
                            std::chrono::high_resolution_clock::now();
                    for (int i = 0;
                         i < Experiment_Size[j] * Num_Repeat;
                         i += Num_Data_In_Line) {
                        k += arr1[i % Experiment_Size[j]];
                    }
                    std::chrono::system_clock::time_point end =
                            std::chrono::high_resolution_clock::now();
                    duration[Straight][j] = static_cast<int>(std::chrono::
                            nanoseconds((end - start)/Num_Repeat).count());
                    delete[] arr1;
                }
                break;
            case Reverse:
                for (int j = 0; j < Num_Experiment; ++j) {
                    auto arr1 = new long double[Experiment_Size[j]];
                    long double k = 0;
                    // Warming
                    for (int i = 0;
                         i < Experiment_Size[j];
                         i += Num_Data_In_Line) {
                        arr1[i] = random();
                    }
                    // Experiment
                    std::chrono::system_clock::time_point start =
                            std::chrono::high_resolution_clock::now();
                    for (int i = Experiment_Size[j] * Num_Repeat;
                         i > 0;
                         i -= Num_Data_In_Line) {
                        k += arr1[i % Experiment_Size[j]];
                    }
                    std::chrono::system_clock::time_point end =
                            std::chrono::high_resolution_clock::now();
                    duration[Reverse][j] = static_cast<int>(std::chrono::
                    nanoseconds((end - start)/Num_Repeat).count());
                    delete[] arr1;
                }
                break;
            case Random:
                for (int j = 0; j < Num_Experiment; ++j) {
                    auto arr1 = new long double[Experiment_Size[j]];
                    long double k = 0;
                    std::set<int> used_num;
                    int n = 0;
                    // Warming
                    for (int i = 0;
                         i < Experiment_Size[j];
                         i += Num_Data_In_Line) {
                        arr1[i] = random();
                    }
                    // Experiment
                    std::chrono::system_clock::time_point start =
                            std::chrono::high_resolution_clock::now();
                    for (int i = 0;
                         i < Experiment_Size[j] * Num_Repeat;
                         i += Num_Data_In_Line) {
                        n = random() % Experiment_Size[j];
                        while (used_num.find(n) != used_num.end()) {
                            break;
                        }
                        k += arr1[n % Experiment_Size[j]];
                    }
                    std::chrono::system_clock::time_point end =
                            std::chrono::high_resolution_clock::now();
                    duration[Random][j] = static_cast<int>(std::chrono::
                    nanoseconds((end - start)/Num_Repeat).count());
                    delete[] arr1;
                }
                break;
        }
    }
}

std::ostream &operator<<(std::ostream& tab, const Cacher& cacher) {
    for (int i = 0; i != Num_Investigation; ++i) {
        tab << "investigation:\n\t travel_variant: " <<
             Experiment_Type[i] << "\n\t experiments:\n";
        for (int j = 0; j != Num_Experiment; ++j) {
            tab << "\t- do_experiment:\n\t\tnumber: " << j+1 <<
                 "\n\t\tinput_data:\n\t\t\tbuffer_size: " <<
                 Experiment_Size_Name[j] <<
                 "\n\t\tresults:\n\t\t\tduration: " <<
                 cacher.duration[i][j] <<
                 " nanoseconds\n";
        }
    }
    return tab;
}
