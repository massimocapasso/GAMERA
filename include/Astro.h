#ifndef _ASTRO_
#define _ASTRO_

#include "Utils.h"

/* TeV->erg */
#define TeV_to_erg 1.602
/* parsec to cm */
#define pc_to_cm 3.0857e18
/* kiloparsec to cm */
#define kpc_to_cm 3.0857e21
/* proton mass in g */
#define m_p_g 1.6726e-24
/* well... pi! */
#define pi 3.1416
/* year in seconds */
#define yr_to_sec 3.15576e7
/* solar mass */
#define mSol 1.9891e33
/* Thomson cross section */
#define sigma_T 6.6524e-25
/* electron mass in erg */
#define m_e 8.187e-7
/* boltzmann constant (erg/K) */
#define kb 1.380658e-16
/* proton mass in erg */
#define m_p 1.50310854e-3
/* pi0 mass in erg */
#define m_pi 2.1622194e-4
/* parsec to cm */
#define pc_to_cm 3.0857e18
/* well... pi! */
#define pi 3.1416
/* year in seconds */
#define yr_to_sec 3.15576e7
/* solar mass */
#define mSol 1.9891e33
/* speed of light cm/s */
#define c_speed 29979245800.
/* elementary charge */
#define el_charge 4.80320427e-10
/* classical electron radius (cm) */
#define eRadius 2.8179e-13
/* planck's constant */
#define hp 6.62606896e-27
/* fine structure constant */
#define fineStructConst 7.2974e-3
/* hour in seconds */
#define h_to_sec 3.6e3
/* pc to lyr */
#define pc_to_lyr 3.26156

using namespace std;

/**
 * @file Astro.C
 * @author Joachim Hahn
 * @short Class that provides utility functions
 * Provides different things, mainly useful for population studies.
 * This includes spiral galaxy models as well as gas distributions,
 * B-Field distributions, coordinate transformations etc.
 * Also includes more technical functions that are helpful in writing
 * GAMERA programs.
 */

class Astro  {
  private:
    Utils *fUtils;
    int ClosestArm;
    double DistanceFromClosestArm;
    double x_a1[7];
    double y_a1[7];
    double x_a2[7];
    double y_a2[7];
    double x_a3[7];
    double y_a3[7];
    double x_a4[7];
    double y_a4[7];
    vector<gsl_spline*> TaylorCordesArms,TaylorCordesArmsInv;
    vector<double> psi0V;
    vector<double> theta0V;
    vector<double> r0V;
    vector<int> ArmsVector;
    double barRadius;
    double barAngle;
    double armWidth;
    double scaleHeight;
    bool QUIETMODE;
    double rMax;
    int SPIRALARMMODEL;
    int SURFACEDENSITYMODEL;
    int CENTRALSTRUCTUREMODEL;
    int MAINSEQUENCEWINDBUBBLEMODEL;
    int MSBUBBLEMODEL;
    bool GAMERAALREADYONTHECONSOLE;
    bool WRAPPINGHAPPENED;
    gsl_spline *TaylorCordesArm1,*TaylorCordesArm2,*TaylorCordesArm3,
               *TaylorCordesArm4,*TaylorCordesArm1Inv,*TaylorCordesArm2Inv,
               *TaylorCordesArm3Inv,*TaylorCordesArm4Inv;
    gsl_interp_accel *accArm1,*accArm2,*accArm3,*accArm4,
                     *accArm1Inv,*accArm2Inv,*accArm3Inv,*accArm4Inv;
  public:
    Astro();
    ~Astro();
    void DisableArm(int arm);///< Switch off an individual arm in Galaxy spiral model
    void EnableArm(int arm);///< Switch on an individual arm in Galaxy spiral model
    double RandomSalpeterInitialMass();///< Dice an initial star mass following the Salpeter law
    double MainSequenceBubbleRadius(double mDotMS, double vMSWind, double timeMS, double n, double initialMass);///< calculate the radius created by the main sequence wind of a star
    double CalculateMSBubbleDensity(double mDotMS, double vMSWind, double timeMS, double n, double bubbleRadius);///< Density inside the main-sequence wind blown bubble.
    double CalculateTimeOnMainSequence(double initialMass);///< Time on the main sequence in years as a function of initial star mass
    double CalculateMSMassLuminosity(double initialMass);///< Main sequence wind mass luminosity as a function of initial star mass
    double CalculateMSWindSpeed(double initialMass);///< Main sequence wind speed as a function of initial star mass
    double CalculateRGWRadius(double pBubble, double mDotRGW, double vRGWind);///< Radius of the red giant wind zone
    void CalculateBField(double x, double y, double z, double &B_tot, double &B_coh, double &B_ord, double &B_iso, vector<double> &regFieldDirection, vector<double> &isoFieldDirection);///< 2D-Model of the large-scale galactic magnetic field structure
    double HIDensity(double x, double y, double z);///< TODO:COMMENT
    double H2Density(double x, double y, double z);///< TODO:COMMENT
    double CalculateHINorm(double R);///< TODO:COMMENT
    double CalculateH2Norm(double R);///< TODO:COMMENT
    double GetHIColumnDensity(double R);///< TODO:COMMENT
    double GetH2ColumnDensity(double R);///< TODO:COMMENT
    double GetHIFWHM(double R);///< TODO:COMMENT
    double GetH2FWHM(double R);///< TODO:COMMENT
    double ModulateGasDensityWithSpirals(double n, double x, double y, double z);
    //double CalculateGasColumnDensity(vector<double> xyzReference,vector<double> GLGB,string gascomponent,double modulate,double range,double steps);///< calculate gas column densities
    double nRadial(double *x, double *pars);///< TODO:COMMENT
    void GetCartesian(double r, double l, double b, double xref, double yref, double zref, double &x, double &y, double &z);///< Galactic coordinates (GL,GB,R) ->Cartesian
    void GetGalactic(double x, double y, double z, double xref, double yref, double zref, double &l, double &b);///< Cartesian coordinates -> Galactic Coordinates(GL,GB,R)
    void RotateCoordinates(double &x, double &y, double &z, double phi, double theta, double psi);///< rotate coordinate around (0,0,0) by (phi,theta,psi)
    void RandomTangentialShift(double r, double width, double &x, double &y);///< gaussian shift along concentric circle (retains r-distribution)
    void RandomGaussianShift(double r, double width, double &x, double &y);
    unsigned int GetRandomArm(double r);///< return a random spiral arm (identifier, i.e. an unsigned integer)
    void Bar(double r, double &x, double &y);///< Get xy Coordinates on a central bar inclined with an angle 'angle' clockwise
    void Disk(double r, double &x, double &y);///< Get random xy Coordinates  on a disk
    double LinearSurfDens(double *x, double *par);///< radial distribution that gives a flat appearance of the galaxy
    void TaylorCordesSpiral(double r, int arm, double &x, double &y);///<TODO: Comment
    double TaylorCordesSpiralAngular(double theta, int arm);///< TODO: Comment
    void ValleeSpiral(double r, int arm, double &x, double &y);///<TODO: Comment
    double ValleeSpiralAngular(double theta, int arm);///<TODO: Comment
    double GetRandomZValue(double scaleHeight);///<TODO: Comment
    vector<double> GetRandomGalactocentricRadii(int n);///<TODO: Comment
    void GalacticPositionXY(double r, int arm, double &x, double &y);///<Return x,y coordinates at given galactocentric radius r and on arm number i
    void PositionOnSpiralArmAngular(double theta, int arm, double &x, double &y); ///< get position on arm in x-y plane given a certain polar angle in the galaxy.
    void GetDistanceToNearestSpiralArm(double x, double y, double &DistanceToClosestArm, int &ClosestArm);
    double GetDistanceToGivenSpiralArm(double x, double y, int arm);
    void ToggleQuietMode() {QUIETMODE=true;}
    vector< vector<double> > DiceGalacticPositions(int i);
    double GetRMax() {return rMax;}
    void SetSpiralArmModel(string centralstructuremodel);
    void SetCentralStructureModel(string centralstructuremodel);
    void SetSurfaceDensityModel(string surfacedensitymodel);
    void SetMainSequenceBubbleModel(string msbubblemodel);
    void SetScaleHeight(double SCALEHEIGHT) {scaleHeight=SCALEHEIGHT;}
    void SetArmWidth(double ARMWIDTH) {armWidth=ARMWIDTH;}
    vector< vector<double> > CreateDensityProfile(double RGWRadius, double mDotRGWind, double vRGWind, double MSBubbleRadius, double MSBubbleDensity, double ISMDensity, double mEj, double rSWRGW, double rSWMS);
    double EvalTaylorCordesArmTheta(double r, int arm);
    double EvalTaylorCordesArmGalactocentricRadius(double theta, int arm);
    double CaseBhattacharyaProfile(double r);
    double IusifovKucukProfile(double r);

};
#endif
