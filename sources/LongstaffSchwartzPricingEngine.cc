#include "LongstaffSchwartzPricingEngine.hpp"
#include <vector>


double LongstaffSchwartzPricingEngine::Value(unsigned Steps, unsigned NumPath) {
    double dt = option_.Maturity() / Steps;
    double init_price = option_.UnderlyingPrice();
    double df = exp(-option_.RiskfreeRate()*dt);

    Matrix paths(NumPath, Steps);
    Matrix exercise(NumPath, Steps);
    std::vector<int> IfITM(0, Steps);
    std::vector<int> ITMCount(0, Steps);   // record how many simulations are in-the-money at each step
    for (unsigned i=0; i < NumPath; i++) {
        paths.data[i][0] = option_.UnderlyingPrice();
        exercise.data[i][0] = option_.ExerciseValue(paths.data[i][0]);
        if (exercise(i, 0) > 0) ITMCount[0] += 1;
        for (unsigned j=1; j < Steps; j++) {
            double deviate = random::normal((option_.RiskfreeRate()-0.5*pow(option_.Volatility(), 2))*dt, pow(option_.Volatility(), 2)*dt);
            paths.data[i][j] = paths(i, j-1)*exp(deviate);
            exercise.data[i][j] = option_.ExerciseValue(paths(i, j));
            if (exercise(i, j) > 0) ITMCount[j] += 1;
        }
    }

    Matrix continuation(NumPath, Steps);
    Matrix OptimalCashFlow(NumPath, Steps);   // optimal cash flow realized at each step on each path, max(exercise, continuation)
    // Optimal cash flow at maturity is exercise
    for (int i=0; i<NumPath; i++)
        OptimalCashFlow.data[i][Steps] = exercise(i, Steps);
    for (unsigned i=Steps-1; i>0; i--) {
        Matrix Y(ITMCount[i], 1);
        Matrix X(ITMCount[i], 3);   // 1, X, X^2
        for (unsigned j=0; j<NumPath; j++) {
            Y.data[j][0] = exercise(i+1, j)*df;
            X.data[j][0] = 1.0;
            X.data[j][1] = paths(i, j);
            X.data[j][2] = paths(i, j)*paths(i, j);
        }
        Matrix B = (X.transpose()*X).inverse() * (X.transpose()*Y);
        Matrix C = X*B;
        for (int j=0; i<NumPath; j++) {
            if (exercise(i, j) > C(j, 0))
                OptimalCashFlow.data[i][j] = exercise(i, j);
            else
                OptimalCashFlow.data[i][j] = C(j, 0);
        }


    }
    

    double OptionValue;
    return OptionValue;
}
