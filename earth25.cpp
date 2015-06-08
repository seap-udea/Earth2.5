////////////////////////////////////////////////////////////////////////
// EXTERNAL UTILITIES
////////////////////////////////////////////////////////////////////////
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf.h>
#include <gsl/gsl_const_mksa.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_roots.h>
#include <libconfig.h++>

////////////////////////////////////////////////////////////////////////
// NAMESPACE
////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace libconfig;

////////////////////////////////////////////////////////////////////////
// TYPES
////////////////////////////////////////////////////////////////////////
typedef double real;
typedef void* params;
typedef FILE* file;

////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
////////////////////////////////////////////////////////////////////////
class Config CFG;
gsl_rng* RANGEN;

////////////////////////////////////////////////////////////////////////
// MACROS
////////////////////////////////////////////////////////////////////////
//Configuration
#define setting const Setting&
#define configInit() setting CFG_ROOT=CFG.getRoot()
#define configList(var,name) setting var=CFG_ROOT[name]
#define configValue(type,var,name) type var=CFG.lookup(name)
#define configValueList(list,var,name) list.lookupValue(name,var)

//String
#define MULTI(str) #str

//Numeric
#define powint(x,n) gsl_pow_int(x,n)
#define PI M_PI
#define PI2 (PI*PI)
#define D2R PI/180

//Physical and astronomical constants
#define MSUN (GSL_CONST_MKSA_SOLAR_MASS) //kg
#define RSUN (6.96342E8) //m
#define AU (GSL_CONST_MKSA_ASTRONOMICAL_UNIT) //m
#define HOURS (3600.0) //s
#define YEAR (365.25*GSL_CONST_MKSA_DAY) //s
#define MEARTH (5.9736E24) //kg
#define REARTH (6.371E6) //m
#define GCONST (GSL_CONST_MKSA_GRAVITATIONAL_CONSTANT) // m^3 / (kg s^2)

////////////////////////////////////////////////////////////////////////
// ROUTINES
////////////////////////////////////////////////////////////////////////
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//I/O
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
int configLoad(const char* file)
{
  if(fopen(file,"r")!=NULL) 
    CFG.readFile(file); 
  else {
    fprintf(stderr,"No configuration file '%s' found\n",file);
    exit(1);
  }
}
