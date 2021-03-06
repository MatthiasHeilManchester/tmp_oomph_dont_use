#! /bin/sh

# Get the OOPMH-LIB root directory from a makefile
OOMPH_ROOT_DIR=$(make -s --no-print-directory print-top_builddir)


#Set the number of tests to be checked
NUM_TESTS=2


# Setup validation directory
#---------------------------
touch Validation
rm -r -f Validation
mkdir Validation

# Validation for adaptive spin up
#--------------------------------
cd Validation

echo "Running adaptive spin up validation "
mkdir RESLT_CR
mkdir RESLT_TH
../spin_up lala > OUTPUT
echo "done"
echo " " >> validation.log
echo "Adaptive spin validation" >> validation.log
echo "------------------------" >> validation.log
echo " " >> validation.log
echo "Validation directory: " >> validation.log
echo " " >> validation.log
echo "  " `pwd` >> validation.log
echo " " >> validation.log
cat  RESLT_CR/soln0.dat RESLT_CR/soln1.dat \
     RESLT_CR/soln2.dat \
 > results_CR.dat
cat  RESLT_TH/soln0.dat RESLT_TH/soln1.dat \
     RESLT_TH/soln2.dat \
 > results_TH.dat

if test "$1" = "no_fpdiff"; then
  echo "dummy [OK] -- Can't run fpdiff.py because we don't have python or validata" >> validation.log
else
../../../../bin/fpdiff.py ../validata/results_CR.dat.gz  \
         results_CR.dat 0.1 0.5e-09 >> validation.log
../../../../bin/fpdiff.py ../validata/results_TH.dat.gz  \
         results_TH.dat 0.2 1.0e-10 >> validation.log
fi

# Append log to main validation log
cat validation.log >> ../../../../validation.log

cd ..



#######################################################################


#Check that we get the correct number of OKs
# validate_ok_count will exit with status
# 0 if all tests has passed.
# 1 if some tests failed.
# 2 if there are more 'OK' than expected.
. $OOMPH_ROOT_DIR/bin/validate_ok_count

# Never get here
exit 10
