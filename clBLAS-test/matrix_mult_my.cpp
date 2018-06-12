#include <ocl_util.h>
#include <cassert>

#include <clBLAS.h>

namespace  {

int rowsA = 1024,
        colsB = 1024,
        common = 1024;

static const clblasOrder order = clblasRowMajor;

static const cl_double alpha = 10;

static const clblasTranspose transA = clblasNoTrans;
static const cl_double* A;

static const clblasTranspose transB = clblasNoTrans;
static const cl_double* B;

static cl_double* C;

static cl_double* D;

void init(double* matrix, int row, int column) {
    for (int j = 0; j < column; j++) {
        for (int i = 0; i < row; i++) {
            matrix[j * row + i] = ((double) (i + j + 1));
        }
    }
}

void print(const char * name, const double* matrix, int row, int column) {
    printf("Matrix %s has %d rows and %d columns:\n", name, row, column);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%.3f ", matrix[j * row + i]);
        }
        printf("\n");
    }
    printf("\n");
}

void create_matices() {
    A = (double*) malloc(rowsA * common * sizeof(double));
    B = (double*) malloc(common * colsB * sizeof(double));
    C = (double*) malloc(rowsA * colsB * sizeof(double));
    D = (double*) malloc(rowsA * colsB * sizeof(double));

    assert(A != NULL);
    assert(B != NULL);
    assert(C != NULL);
    assert(D != NULL);

    srand(time(NULL));

    init((double*)A, rowsA, common);
    init((double*)B, common, colsB);
}

cl_mem bufA, bufB, bufC;
cl_command_queue queue = 0;
cl_context ctx = 0;
cl_event event = NULL;

int init_cl() {
    cl_int err;
    cl_platform_id platform = 0;
    cl_device_id device = 0;
    cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };

    /* Setup OpenCL environment. */
    err = clGetPlatformIDs(1, &platform, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetPlatformIDs() failed with %d\n", err );
        return 1;
    }

    err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, NULL);
    if (err != CL_SUCCESS) {
        printf( "clGetDeviceIDs() failed with %d\n", err );
        return 1;
    }

    props[1] = (cl_context_properties)platform;
    ctx = clCreateContext(props, 1, &device, NULL, NULL, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateContext() failed with %d\n", err );
        return 1;
    }

    queue = clCreateCommandQueue(ctx, device, 0, &err);
//    cl_queue_properties props_q[] = { CL_QUEUE_PROPERTIES,
//            (const cl_queue_properties) (CL_QUEUE_ON_DEVICE &&
//            CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE),
//            0
//            };
//    queue = clCreateCommandQueueWithProperties(ctx, device, props_q, &err);
    if (err != CL_SUCCESS) {
        printf( "clCreateCommandQueue() failed with %d\n", err );
        clReleaseContext(ctx);
        return 1;
    }

    /* Setup clblas. */
    err = clblasSetup();
    if (err != CL_SUCCESS) {
        printf("clblasSetup() failed with %d\n", err);
        clReleaseCommandQueue(queue);
        clReleaseContext(ctx);
        return 1;
    }

    /* Prepare OpenCL memory objects and place matrices inside them. */
    bufA = clCreateBuffer(ctx, CL_MEM_READ_ONLY, rowsA * common * sizeof(double),
                          NULL, &err);
    bufB = clCreateBuffer(ctx, CL_MEM_READ_ONLY, common * colsB * sizeof(double),
                          NULL, &err);
    bufC = clCreateBuffer(ctx, CL_MEM_READ_WRITE, rowsA * colsB * sizeof(double),
                          NULL, &err);

    err = clEnqueueWriteBuffer(queue, bufA, CL_TRUE, 0,
            rowsA * common * sizeof(double), A, 0, NULL, NULL);
    err = clEnqueueWriteBuffer(queue, bufB, CL_TRUE, 0,
            common * colsB * sizeof(double), B, 0, NULL, NULL);
    err = clEnqueueWriteBuffer(queue, bufC, CL_TRUE, 0,
            rowsA * colsB * sizeof(double), C, 0, NULL, NULL);
    err = clEnqueueWriteBuffer(queue, bufC, CL_TRUE, 0,
            rowsA * colsB * sizeof(double), C, 0, NULL, NULL);
    /* Call clblas extended function. Perform gemm for the lower right sub-matrices */

    return 0;
}

void deinit_cl() {
    /* Release OpenCL events. */
    clReleaseEvent(event);

    /* Release OpenCL memory objects. */
    clReleaseMemObject(bufC);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufA);

    /* Finalize work with clblas. */
    clblasTeardown();

    /* Release OpenCL working objects. */
    clReleaseCommandQueue(queue);
    clReleaseContext(ctx);
}

int test() {
    cl_int err;
    int ret = 0;

    err = clblasDgemm(order, transA, transB,
                         rowsA, colsB, rowsA, 1,
                         bufA, 0, 1024,
                         bufB, 0, 1024, 0,
                         bufC, 0, 1024,
                         1, &queue, 0, NULL, &event);
    if (err != CL_SUCCESS) {
        printf("clblasSgemmEx() failed with %d\n", err);
        ret = 1;
    }
    else {
        /* Wait for calculations to be finished. */
        err = clWaitForEvents(1, &event);

        /* Fetch results of calculations from GPU memory. */
        err = clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0,
                sizeof(double),
//                rowsA * colsB * sizeof(double),
                                  D, 0, NULL, NULL);

        /* At this point you will get the result of SGEMM placed in 'result' array. */
        printf("%f\n", D[0]);
    }


    return ret;
}

} // unnamed

int test_my() {
    create_matices();
    init_cl();

    for(int i = 0; i < 50; i++) {
        test();
    }

    deinit_cl();
    return 0;
}

