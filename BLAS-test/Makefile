MKLROOT=/opt/intel/mkl

TARGET=BLAS-test
CXXFLAGS=-O3

# BLAS
#LIBS += -lOpenCL -lclBLAS -lblas 

# dymnamic mkl
#LIBS += -lOpenCL -lclBLAS -L/opt/intel/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_core -lmkl_intel_thread -liomp5 -lpthread 

# static mkl
LIBS += -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_intel_thread.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -liomp5 -lpthread -lm -ldl

include /dxtsrc/lib/makefile.mk
