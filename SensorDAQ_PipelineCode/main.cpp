#include <iostream>
#include <memory>
#include <vector>
#include "sensor.h"
#include "filter.h"
#include "csv_logger.h"
using namespace std;
int main() {
    try {
        // --- Simulation settings ---
        const double dt = 0.01;
        const int steps = 5000;

        // --- Choose ONE sensor (polymorphism via base pointer) ---
        // unique_ptr means: "this object has exactly one owner; auto-deletes when it goes out of scope"
        unique_ptr<Sensor> sensor = std::make_unique<SineSensor>(
            /*amplitude=*/1.0,
            /*freq_hz=*/1.0,
            /*dt=*/dt,
            /*noise_sigma=*/0.15
        );

        // You can swap sensors without changing the rest of the pipeline:
        // std::unique_ptr<Sensor> sensor = std::make_unique<TemperatureSensor>(20.0, 0.01, dt, 0.2);
        // std::unique_ptr<Sensor> sensor = std::make_unique<PressureSensor>(101.3, 0.8, 0.2, dt, 0.1);

        // --- Build a filter chain (vector of polymorphic filters) ---
        vector<unique_ptr<Filter>> filters;
        filters.push_back(std::make_unique<MovingAverageFilter>(25));
        filters.push_back(std::make_unique<LowPassFilter>(0.15));
        // filters.push_back(std::make_unique<NoFilter>());

        CSVLogger logger("daq.csv");

        for (int i = 0; i < steps; ++i) {
            double time = i * dt;

            // DAQ measurement
            double raw = sensor->read();

            // Pipeline processing
            double filtered = raw;
            for (auto& f : filters) {
                filtered = f->apply(filtered);
            }

            // Log results
            logger.log(time, raw, filtered);
        }

        cout << "Done! Wrote daq.csv (time,raw,filtered)\n";
        cout << "Try plotting it with Python to see filtering.\n";
        return 0;

    } catch (const exception& e) {
        cerr<< "Fatal error: " << e.what() << "\n";
        //std::cerr is the standard error output stream used specifically for displaying error messages and diagnostic information.
        return 1;
    }
}
