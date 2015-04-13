/*
 Simple Stata plugin to generate uniform random numbers with 
 the C++ Mersenne Twister engine with the DEFAULT SEED!
 
 Tested with Visual Studio Express 2013:

 Download the stplugin.* files from http://www.stata.com/plugins/
 and put them in the same directory.

 Compile with
 cl cpprandom.cpp stplugin.c /LD /MD /link /out:cpprandom.plugin

 See cpprandom.do for example calling the RNG from within Stata:

 Peter Windridge Apr 2015.
*/


#include "stplugin.h"

#include <random>
using namespace std;


mt19937 gen(mt19937::default_seed);
uniform_real_distribution<> uniform(0, 1);

STDLL stata_call(int argc, char *argv[])
{
	if (SF_nvars() == 0) {
		SF_error("No variable name specified to store uniform numbers.\n");
		return(102);
	}

	ST_double u;
	ST_retcode rc;

	for (ST_int j = SF_in1(); j <= SF_in2(); j++) {
		if (SF_ifobs(j)) {
			// generate a uniform
			u = uniform(gen);

			// store it in FIRST variable specified.
			if (rc = SF_vstore(1, j, u)) return(rc);
		}
	}

	return(0) ;
}


