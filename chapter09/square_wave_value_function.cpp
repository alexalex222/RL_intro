//
// Created by Kuilin Chen on 2018-07-19.
//

#include "square_wave_value_function.h"

SquareWaveValueFunction::SquareWaveValueFunction(double width, Interval& d, double step_size, int n) :
        domain(d), feature_width(width), alpha(step_size), num_features(n)
{
    double step = static_cast<double>((domain.size() - feature_width)) / (num_features - 1);
    double left = domain.left;

    for (int i = 0; i < num_features - 1; i++) {
        features.emplace_back(Interval(left, left + feature_width));
        left += step;
    }
    features.emplace_back(Interval(left, domain.right));
    weights = vector<double>(num_features, 0.0);
}

vector<int> SquareWaveValueFunction::getActiveFeature(double x) {
    vector<int> active_feature;
    for (size_t i = 0; i < features.size(); i++) {
        if (features[i].contain(x)) {
            active_feature.push_back(i);
        }
    }
    return active_feature;
}

double SquareWaveValueFunction::value(double x) {
    vector<int> active_features = this->getActiveFeature(x);
    double v = 0.0;
    for(auto i : active_features) {
        v += weights[i];
    }
    return v;
}

void SquareWaveValueFunction::update(double delta, double x) {
    vector<int> active_features = this->getActiveFeature(x);
    delta *= alpha/active_features.size();
    for (auto index : active_features) {
        weights[index] += delta;
    }
}

