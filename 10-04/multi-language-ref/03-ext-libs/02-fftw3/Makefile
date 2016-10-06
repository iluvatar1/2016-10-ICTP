# compiler configuration
# C
CC=gcc
CFLAGS=-Wall -g
LFLAGS=-lm
# C++
CXX=g++
CXXFLAGS=-Wall -g
LXXFLAGS=
# F77
FC=gfortran
FFLAGS=-Wall -g -std=legacy
FLFLAGS=
# F95
F90=gfortran
F90FLAGS=-Wall -g -std=f95
F90LFLAGS=

FFTW_INC=-I /scratch/local/include
FFTW_LIB=-L /scratch/local/lib -lfftw3 -lm

#############################################

all: fsynth_f77 fsynth_f95 fsynth_c fsynth_cxx fanalyze_f95 fanalyze_c
    

clean:
	rm -f fsynth_f77 fsynth_f95 fsynth_c fsynth_cxx fanalyze_f95 fanalyze_c
	rm -f *.dat *.mod *~ a.out *.o

#############################################
EXTRA_OBJS=utilities.o


fsynth_f77: fsynth.f $(EXTRA_OBJS)
	$(FC) $(FFLAGS) -o $@ $^ $(FLFLAGS)

fsynth_f95: fsynth.f90 $(EXTRA_OBJS)
	$(F90) $(F90FLAGS) -o $@ $^ $(F90LFLAGS)

fsynth_c: fsynth.c $(EXTRA_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

fsynth_cxx: fsynth.cpp $(EXTRA_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LXXFLAGS)

fanalyze_cxx: fanalyze.cpp $(EXTRA_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LXXFLAGS)

utilities.o: utilities.c
	$(CC) $(CFLAGS) -c $<

fanalyze_f95: fanalyze.f90
	$(F90) $(F90FLAGS) $(FFTW_INC) -o $@ $^ $(F90LFLAGS)  $(FFTW_LIB)

fanalyze_c: fanalyze.c
	$(CC) $(CFLAGS) $(FFTW_INC) -o $@ $^ $(LFLAGS) $(FFTW_LIB)

