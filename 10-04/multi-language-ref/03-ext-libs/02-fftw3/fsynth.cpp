// fourier synthesis code example in C++

#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

static const double TWOPI=6.28318530717958647688;

class fSynth 
{
public:
    fSynth() {};
    ~fSynth() {}; 
    void add_freq(double freq, double intens, double phase);
    void write(string &fname, const int tnum, const double tmax);

protected:
    vector<double> _freq, _phase, _intens;
};

void fSynth::add_freq(double freq, double intens, double phase)
{
    _freq.push_back(freq);
    _intens.push_back(intens);
    _phase.push_back(phase);
}

void fSynth::write(string &fname, const int tnum, const double tmax)
{
    const double tdelta = tmax / static_cast<double>(tnum);
    const int fnum = _freq.size();

    ofstream fp(fname.c_str());
    fp << "# " << tnum << "\n";
    for (int i=0; i < tnum; ++i) {
        double t = static_cast<double>(i) * tdelta;
        double val = 0.0;

        for (int j=0; j < fnum; ++j)
            val += _intens[j]*sin(TWOPI*(_freq[j]*t+_phase[j]));

        fp << t << " "  << val << "\n";
    }
    fp.close();
}

int main(int, char **)
{
    char line[256];

    int fnum;
    cout << "fourier synthesis\n";
    cout << "give number of frequencies" << endl;
    cin >> fnum;
    cin.getline(line,255); // ignore rest of the line.
    cout << "got: " << fnum << endl;

    fSynth fsynth;

    for (int i=0; i < fnum; ++i) {
        double freq,phase,intens;
        cout << "frequency number: " << i+1 << "\n";
        cout << "give frequency, intensity and phase:" << endl;
        cin >> freq >> intens >> phase;
        cin.getline(line,255);
        fsynth.add_freq(freq,intens,phase);
        cout << "got: " << phase << " " << intens << " " << phase << endl;
    }
       
    double tmax;
    cout << "give total time" << endl;
    cin >> tmax;
    cin.getline(line,255);
    cout << "got: " << tmax << endl;

    int tnum;
    cout << "give number of intervals" << endl;
    cin >> tnum;
    cin.getline(line,255);
    cout << "got: " << tnum << endl;

    string fname;
    cout << "give filename" << endl;
    cin >> fname;
    cout << "got: " << fname << endl;

    cout << "generating output" << endl;
    fsynth.write(fname,tnum,tmax);
    return 0;
}


