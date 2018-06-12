#ifndef OCL_UTIL_H_
#define OCL_UTIL_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include <fstream>
#include <streambuf>

//#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#define CL_USE_DEPRECATED_OPENCL_1_0_APIS
#include <CL/cl.hpp>

#define ocl_check_error( rc) { \
	if(rc) { \
		std::cout << rc << " @" << __FILE__ << ":" << __LINE__ << std::endl; \
		exit(rc); \
	} \
}

inline std::string readSource(const char* file_name) {
	std::ifstream t(file_name);
	std::string str((std::istreambuf_iterator<char>(t)),
	                 std::istreambuf_iterator<char>());

	return str;
}

inline std::vector<char> readBinary(const char* file_name) {
	std::ifstream file(file_name, std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<char> buf(size);
	if (!file.read(buf.data(), size))
	{
	    throw std::runtime_error(std::string("file not found: ") + file_name);
	}
	return buf;
}

inline cl::Context createContext() {
    cl_int rc = 0;

    //get all platforms (drivers)
    std::vector<cl::Platform> all_platforms;
    rc = cl::Platform::get(&all_platforms);
    ocl_check_error(rc);

    if(all_platforms.size()==0){
        std::cout<<" No platforms found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Platform default_platform=all_platforms[0];
    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";

    //get default device of the default platform
    std::vector<cl::Device> all_devices;
    rc = default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    ocl_check_error(rc);

    if(all_devices.size()==0){
        std::cout<<" No devices found. Check OpenCL installation!\n";
        exit(1);
    }

    cl::Context context = cl::Context(all_devices);

    return context;
}

inline cl::Device getDevice(const cl::Context& context, int idx = 0) {
    std::vector<cl::Device> all_devices;
    context.getInfo(CL_CONTEXT_DEVICES, &all_devices);

    cl::Device default_device = all_devices[idx];
    std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";

    return default_device;
}



// -----------------------------------------------------------------------------
inline void _setKernelParameters(cl::Kernel &k, int i){}

template<typename T, typename... Args>
inline void _setKernelParameters(cl::Kernel &kernel, int i,
        const T &firstParameter, const Args& ...restOfParameters){
    kernel.setArg(i, firstParameter);
    _setKernelParameters(kernel, i+1, restOfParameters...);
}

template<typename... Args>
inline void setKernelParameters(cl::Kernel &kernel,const Args& ...args){
    _setKernelParameters(kernel, 0, args...);
}

#endif /* OCL_UTIL_H_ */
