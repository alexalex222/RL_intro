//
// Created by Kuilin Chen on 2018-07-19.
//

#ifndef CHAPTER09_SQUARE_WAVE_VALUE_FUNCTION_H
#define CHAPTER09_SQUARE_WAVE_VALUE_FUNCTION_H

#include "interval.h"
#include <vector>
#include <random>

using std::vector;

class SquareWaveValueFunction {
private:
    double feature_width;   ///< feature width
    int num_features;    ///< number of features
    vector<Interval> features;  ///< list of features
    double alpha;       ///< step size
    Interval domain;    ///< domain of this value function, an instance of Interval
    vector<double> weights; ///< weights for features

public:
    /// constructor
    /// \param width : feature width
    /// \param d : domain of this value function
    /// \param step_size : alpha
    /// \param n : number of features
    SquareWaveValueFunction(double width, Interval& d, double step_size=0.2, int n=50);

    /// Get the indices of corresponding feature windows
    /// \param x : a position
    /// \return : list of active features
    vector<int> getActiveFeature(double x);

    /// Get the value for point x
    /// \param x : a point
    /// \return : state value
    double value(double x);


    /// Update the value function for point x
    /// \param delta : y - x
    /// \param x : position
    void update(double delta, double x);

};






#endif //CHAPTER09_SQUARE_WAVE_VALUE_FUNCTION_H
