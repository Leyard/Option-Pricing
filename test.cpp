#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

#define PI 3.14159265348


using namespace std;

double normal_pdf(double x, double mu=0, double sigma=1){
    return 1/(sqrt(2*PI*sigma*sigma))*exp((-(x-mu)*(x-mu))/(2*sigma*sigma));
}


double inv_cdf(double quantile, double mu=0, double sigma=1){
    // Using the Beasley-Springer-Moro algorithm in Glasserman[2004]
    double a[4] = {2.50662823884, -18.61500062529, 41.39119773534, -25.44106049637};
    double b[4] = {-8.47351093090, 23.08336743743, -21.06224101826, 3.13082909833};
    double c[9] = {0.3374754822726147, 0.9761690190917186, 0.1607979714918209,
                    0.0276438810333863, 0.0038405729373609, 0.0003951896511919, 
                    0.0000321767881768, 0.0000002888167364, 0.0000003960315187};

    quantile = (quantile - mu)/sigma;

    if(quantile >= 0.5 && quantile <= 0.92){
        double num = 0.0;
        double denom = 1.0;
        for (int i=0; i<4; i++){
            num += a[i] * pow((quantile - 0.5), 2*i + 1);
            denom += b[i] * pow((quantile - 0.5), 2*i);
        }
        return num/denom;
    }
    else if(quantile > 0.92 && quantile < 1){
        double num = 0.0;
        for (int i=0; i<9; i++){
            num += c[i] * pow((log(-log(1-quantile))), i);
        }
        return num;
    }
    else{
        return -1.0*inv_cdf(1-quantile);
    }
}


double uniform_rand(double a=0, double b=1){
    // srand(time(0));
    return double(rand())/RAND_MAX * (b-a) + a;
}


double normal_rand(double mu=0, double sigma=1){
    return inv_cdf(uniform_rand());
}



vector<double> mcmc(int n, double (*pdf)(double, double, double), double (*jump)(double, double)) {
    vector<double> result;
    double x0 = 0.1;
    for (int i=0; i<n; i++) {
        double x1;
        double prop = (*jump)(x0, 1);
        double unif = uniform_rand();
        if (uniform_rand() < (*pdf)(prop, 0, 1)/(*pdf)(x0, 0, 1)) x1 = prop;
        else x1 = x0;
        cout << x1 << endl;
        result.push_back(x1);
        x0 = x1;
    }
    return result;
}





int main() {
    for (int i=0; i<1000; i++) {
        cout << normal_rand(0, 1) << endl;
    }
    // mcmc(1000, normal_pdf, normal_rand);
    return 0;
}
