#include <iostream>
#include <fstream>
#include "learning_methods.h"


void testMonteCarlo() {
    int episodes = 100000;
    double alpha = 2e-5;
    int n_states = 1000;

    // we have 10 aggregations in this example, each has 100 states
    unique_ptr<ValueFunction> vf(new AggregValueFunction(10));
    unique_ptr<vector<double>> distribution(new vector<double >(1000+2, 0.0));
    for (int e = 0; e < episodes; e++) {
        gradientMonteCarlo(vf, alpha, distribution);
    }

    double sum = 0.0;
    for (auto it = distribution->begin(); it != distribution->end(); it++) {
        sum += *it;
    }
    for (auto it = distribution->begin(); it != distribution->end(); it++) {
        *it = *it/sum;
    }

    std::ofstream ofs("monte_carlo_results.csv");
    ofs << "State" << "," << "MC State Value" << "," << "True State Value" << "," << "State Distribution" << "\n";
    for (int i = 1; i <= n_states; i++) {
        ofs << i << "," << vf->value(i) << "," << vf->p.getTrueStateValue(i) << "," << distribution->at((unsigned long) i) << "\n";
    }
    ofs.close();

}

void testSemiGradientTD() {
    int episodes = 100000;
    double alpha = 2e-4;
    int n_states = 1000;

    // we have 10 aggregations in this example, each has 100 states
    unique_ptr<ValueFunction> vf(new AggregValueFunction(10));
    for (int e = 0; e < episodes; e++) {
        std::cout << "Episode: " << e << std::endl;
        semiGradientTemporalDifference(vf, alpha, 1);   // one step TD
    }

    std::ofstream ofs("TD_results.csv");
    ofs << "State" << "," << "TD State Value" << "," << "True State Value" << "\n";
    for (int i = 1; i <= n_states; i++) {
        ofs << i << "," << vf->value(i) << "," << vf->p.getTrueStateValue(i) << "\n";
    }
    ofs.close();

}

void paramsTD() {
    int n_states = 1000;

    // truncate value for better display
    double truncate_value = 0.55;

    // all possible steps
    vector<int> steps;
    for (int i = 0; i < 10; i++) steps.push_back(static_cast<int>(pow(2, i)));

    // all possible alphas
    vector<double> alphas;
    for (int i = 0; i <= 10; i++) alphas.push_back(static_cast<double>(i) * 0.1);


    // each run has 10 episodes
    int episodes = 10;

    // perform 100 independent runs
    int runs = 100;

    // track the errors for each (step, alpha) combination
    vector<vector<double>> errs(steps.size(), vector<double>(alphas.size(), 0.0));
    for (int run = 0; run < runs; run++) {
        for (size_t step_ind = 0; step_ind < steps.size(); step_ind++) {
            int step = steps[step_ind];
            for (size_t alpha_ind = 0; alpha_ind < alphas.size(); alpha_ind++) {
                double alpha = alphas[alpha_ind];
                std::cout << "run: " << run << " step: " << step << " alpha: " << alpha << std::endl;
                unique_ptr<ValueFunction>vf(new AggregValueFunction(20));
                for (int ep = 0; ep < episodes; ep++) {
                    semiGradientTemporalDifference(vf, alpha, step);
                    double error_sum = 0.0;
                    for (int state = 1; state <= n_states; state++) {
                        error_sum += pow((vf->value(state) - vf->p.getTrueStateValue(state)), 2);
                    }
                    errs[step_ind][alpha_ind] += sqrt(error_sum / n_states);
                }
            }

        }
    }

    // write results to file
    std::ofstream ofs("TD_errors.csv");
    for (size_t i = 0; i < steps.size(); i++) {
        for (size_t j = 0; j < alphas.size(); j++) {
            errs[i][j] = errs[i][j]/(runs*episodes);
            if (errs[i][j] > truncate_value) errs[i][j] = truncate_value;
            ofs << errs[i][j];
            if (j == alphas.size() - 1) ofs << "\n";
            else ofs << ",";
        }
    }
    ofs.close();
}


void testBasisVF(int basis_type) {
    int n_states = 1000;

    std::string basis_name;
    if (basis_type == POLYNOMIAL_BASES) basis_name = "Poly";
    else if (basis_type == FOURIER_BASES) basis_name = "Fourier";

    // # of runs
    int runs = 100;

    // each run has 5000 episodes
    unsigned long episodes = 5000;

    // # of bases
    vector<unsigned long> orders {5, 10, 20};

    double alpha = 1e-4;

    unique_ptr<vector<double>> p;

    // track errors for each episode
    vector<vector<double>> errs(orders.size(), vector<double>(episodes, 0.0));
    for (int run = 0; run < runs; run++) {
        for (size_t i = 0; i < orders.size(); i++) {
            unsigned long order = orders[i];
            unique_ptr<ValueFunction> vf(new BasisValueFunction(order, basis_type));
            for (int ep = 0; ep < episodes; ep++) {
                std::cout << "Polynomial basis: " << basis_name << "Run: " << run << " Episode: " << ep << std::endl;
                gradientMonteCarlo(vf, alpha, p);
                double error_sum = 0.0;
                for (int state = 1; state <= n_states; state++) {
                    error_sum += pow((vf->value(state) - vf->p.getTrueStateValue(state)), 2);
                }
                errs[i][ep] += sqrt(error_sum / n_states);
            }
        }
    }

    std::ofstream ofs;
    if (basis_type == POLYNOMIAL_BASES) {
        ofs.open("poly_errors.csv");
    }
    else if (basis_type == FOURIER_BASES) {
        ofs.open("fourier_errors.csv");
    }

    for (size_t i = 0; i < orders.size(); i++) {
        for (int ep = 0; ep < episodes; ep++) {
            errs[i][ep] = errs[i][ep]/runs;
            ofs << errs[i][ep];
            if (ep == episodes - 1) ofs << "\n";
            else ofs << ",";
        }
    }
    ofs.close();
}

void testTile() {
    int n_states = 1000;

    int runs = 100;   ///< # of runs

    unsigned long episodes = 5000;  ///< each run has 5000 episodes

    int numOfTilings = 50; ///< number of tilings

    int tileWidth = 200;    ///< each tile will cover 200 states

    int tilingOffset = 4;   ///< how to put so many tilings

    unique_ptr<vector<double>> p;

    vector<double> errs(episodes, 0.0); ///< track errors for each episode
    for (int run = 0; run < runs; run++) {
        unique_ptr<ValueFunction> vf(new TilingsValueFunction(numOfTilings, tileWidth, tilingOffset));
        for (int ep = 0; ep < episodes; ep++) {
            std::cout << "Tilings --- Run: " << run << " Episode: " << ep << std::endl;
            double alpha = 1.0 / (ep + 1);
            gradientMonteCarlo(vf, alpha, p);
            double error_sum = 0.0;
            for (int state = 1; state <= n_states; state++) {
                error_sum += pow((vf->value(state) - vf->p.getTrueStateValue(state)), 2);
            }
            errs[ep] += sqrt(error_sum / n_states);
        }
    }

    std::ofstream ofs("tile_errors.csv");
    for (int ep = 0; ep < episodes; ep++) {
        errs[ep] = errs[ep]/runs;
        ofs << errs[ep];
        if (ep == episodes - 1) ofs << "\n";
        else ofs << ",";
    }
    ofs.close();

    errs = vector<double>(episodes, 0.0); ///< track errors for each episode
    for (int run = 0; run < runs; run++) {
        unique_ptr<ValueFunction> vf(new AggregValueFunction(n_states/tileWidth));
        for (int ep = 0; ep < episodes; ep++) {
            std::cout << "Aggregation --- Run: " << run << " Episode: " << ep << std::endl;
            double alpha = 1.0 / (ep + 1);
            gradientMonteCarlo(vf, alpha, p);
            double error_sum = 0.0;
            for (int state = 1; state <= n_states; state++) {
                error_sum += pow((vf->value(state) - vf->p.getTrueStateValue(state)), 2);
            }
            errs[ep] += sqrt(error_sum / n_states);
        }
    }

    ofs.open("aggreg_errors.csv");
    for (int ep = 0; ep < episodes; ep++) {
        errs[ep] = errs[ep]/runs;
        ofs << errs[ep];
        if (ep == episodes - 1) ofs << "\n";
        else ofs << ",";
    }
    ofs.close();

}


void testSquareWave() {
    vector<int> num_samples({10, 40, 160, 2560, 10240});
    vector<double> feature_widths({0.2, 0.4, 1.0});
    Interval domain(0.0, 2.0);
    vector<double> axis_x;
    for (int i = 0; i < 10; i++) axis_x.push_back(0.2*i);

    for (auto num : num_samples) {
        std::cout << num << " samples" << std::endl;
        vector<pair<double, double>> samples = gen_sample(num);
        for (auto feature_width : feature_widths) {
            SquareWaveValueFunction vf(feature_width, domain);
            approximate(samples, vf);
            vector<double> values(10, 0.0);
            for (size_t i = 0; i <  10; i++) values[i] = vf.value(axis_x[i]);
        }
    }

}


int main() {
    //testMonteCarlo();
    //testSemiGradientTD();
    //paramsTD();
    //testBasisVF(POLYNOMIAL_BASES);
    //testBasisVF(FOURIER_BASES);
    //testTile();

    testSquareWave();

    std::string filename = "../plot_results.py";
    std::string command = "python ";
    command += filename;
    system(command.c_str());


    return 0;
}