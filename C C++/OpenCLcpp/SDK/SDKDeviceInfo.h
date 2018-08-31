
/**
 * SDKDeviceInfo
 * class implements the functionality to query
 * various Device related parameters
 */
class SDKDeviceInfo
{
    public :
        cl_device_type dType;               /**< dType device type*/
        cl_uint venderId;                   /**< vendorId VendorId of device*/
        cl_uint maxComputeUnits;            /**< maxComputeUnits maxComputeUnits of device*/
        cl_uint maxWorkItemDims;            /**< maxWorkItemDims maxWorkItemDimensions VendorId of device*/
        size_t* maxWorkItemSizes;           /**< maxWorkItemSizes maxWorkItemSizes of device*/
        size_t maxWorkGroupSize;            /**< maxWorkGroupSize max WorkGroup Size of device*/
        cl_uint preferredCharVecWidth;      /**< preferredCharVecWidth preferred Char VecWidth of device*/
        cl_uint preferredShortVecWidth;     /**< preferredShortVecWidth preferred Short VecWidth of device*/
        cl_uint preferredIntVecWidth;       /**< preferredIntVecWidth preferred Int VecWidth of device*/
        cl_uint preferredLongVecWidth;      /**< preferredLongVecWidth preferred Long VecWidth of device*/
        cl_uint preferredFloatVecWidth;     /**< preferredFloatVecWidth preferredFloatVecWidth of device*/
        cl_uint preferredDoubleVecWidth;    /**< preferredDoubleVecWidth preferred Double VecWidth of device*/
        cl_uint preferredHalfVecWidth;      /**< preferredHalfVecWidth preferred Half VecWidth of device*/
        cl_uint nativeCharVecWidth;         /**< nativeCharVecWidth native Char VecWidth of device*/
        cl_uint nativeShortVecWidth;        /**< nativeShortVecWidth nativeShortVecWidth of device*/
        cl_uint nativeIntVecWidth;          /**< nativeIntVecWidth nativeIntVecWidth of device*/
        cl_uint nativeLongVecWidth;         /**< nativeLongVecWidth nativeLongVecWidth of device*/
        cl_uint nativeFloatVecWidth;        /**< nativeFloatVecWidth native Float VecWidth of device*/
        cl_uint nativeDoubleVecWidth;       /**< nativeDoubleVecWidth native Double VecWidth of device*/
        cl_uint nativeHalfVecWidth;         /**< nativeHalfVecWidth native Half VecWidth of device*/
        cl_uint maxClockFrequency;          /**< maxClockFrequency max Clock Frequency of device*/
        cl_uint addressBits;                /**< addressBits address Bits of device*/
        cl_ulong maxMemAllocSize;           /**< maxMemAllocSize max Mem Alloc Size of device*/
        cl_bool imageSupport;               /**< imageSupport image Support of device*/
        cl_uint maxReadImageArgs;           /**< maxReadImageArgs max ReadImage Args of device*/
        cl_uint maxWriteImageArgs;          /**< maxWriteImageArgs max Write Image Args of device*/
        size_t image2dMaxWidth;             /**< image2dMaxWidth image 2dMax Width of device*/
        size_t image2dMaxHeight;            /**< image2dMaxHeight image 2dMax Height of device*/
        size_t image3dMaxWidth;             /**< image3dMaxWidth image3d MaxWidth of device*/
        size_t image3dMaxHeight;            /**< image3dMaxHeight image 3dMax Height of device*/
        size_t image3dMaxDepth;             /**< image3dMaxDepth image 3dMax Depth of device*/
        size_t maxSamplers;                 /**< maxSamplers maxSamplers of device*/
        size_t maxParameterSize;            /**< maxParameterSize maxParameterSize of device*/
        cl_uint memBaseAddressAlign;        /**< memBaseAddressAlign memBase AddressAlign of device*/
        cl_uint minDataTypeAlignSize;       /**< minDataTypeAlignSize minDataType AlignSize of device*/
        cl_device_fp_config
        singleFpConfig; /**< singleFpConfig singleFpConfig of device*/
        cl_device_fp_config
        doubleFpConfig; /**< doubleFpConfig doubleFpConfig of device*/
        cl_device_mem_cache_type
        globleMemCacheType; /**< globleMemCacheType globleMem CacheType of device*/
        cl_uint globalMemCachelineSize;     /**< globalMemCachelineSize globalMem Cacheline Size of device*/
        cl_ulong globalMemCacheSize;        /**< globalMemCacheSize globalMem CacheSize of device*/
        cl_ulong globalMemSize;             /**< globalMemSize globalMem Size of device*/
        cl_ulong maxConstBufSize;           /**< maxConstBufSize maxConst BufSize of device*/
        cl_uint maxConstArgs;               /**< maxConstArgs max ConstArgs of device*/
        cl_device_local_mem_type
        localMemType;/**< localMemType local MemType of device*/
        cl_ulong localMemSize;              /**< localMemSize localMem Size of device*/
        cl_bool errCorrectionSupport;       /**< errCorrectionSupport errCorrectionSupport of device*/
        cl_bool hostUnifiedMem;             /**< hostUnifiedMem hostUnifiedMem of device*/
        size_t timerResolution;             /**< timerResolution timerResolution of device*/
        cl_bool endianLittle;               /**< endianLittle endian Little of device*/
        cl_bool available;                  /**< available available of device*/
        cl_bool compilerAvailable;          /**< compilerAvailable compilerAvailable of device*/
        cl_device_exec_capabilities
        execCapabilities;/**< execCapabilities exec Capabilities of device*/
        cl_command_queue_properties
        queueProperties;/**< queueProperties queueProperties of device*/
        cl_platform_id platform;            /**< platform platform of device*/
        char* name;                         /**< name name of device*/
        char* vendorName;                   /**< venderName vender Name of device*/
        char* driverVersion;                /**< driverVersion driver Version of device*/
        char* profileType;                  /**< profileType profile Type of device*/
        char* deviceVersion;                /**< deviceVersion device Version of device*/
        char* openclCVersion;               /**< openclCVersion opencl C Version of device*/
        char* extensions;                   /**< extensions extensions of device*/

        /**
         * Constructor
         */
        SDKDeviceInfo()
        {
            dType = CL_DEVICE_TYPE_GPU;
            venderId = 0;
            maxComputeUnits = 0;
            maxWorkItemDims = 0;
            maxWorkItemSizes = NULL;
            maxWorkGroupSize = 0;
            preferredCharVecWidth = 0;
            preferredShortVecWidth = 0;
            preferredIntVecWidth = 0;
            preferredLongVecWidth = 0;
            preferredFloatVecWidth = 0;
            preferredDoubleVecWidth = 0;
            preferredHalfVecWidth = 0;
            nativeCharVecWidth = 0;
            nativeShortVecWidth = 0;
            nativeIntVecWidth = 0;
            nativeLongVecWidth = 0;
            nativeFloatVecWidth = 0;
            nativeDoubleVecWidth = 0;
            nativeHalfVecWidth = 0;
            maxClockFrequency = 0;
            addressBits = 0;
            maxMemAllocSize = 0;
            imageSupport = CL_FALSE;
            maxReadImageArgs = 0;
            maxWriteImageArgs = 0;
            image2dMaxWidth = 0;
            image2dMaxHeight = 0;
            image3dMaxWidth = 0;
            image3dMaxHeight = 0;
            image3dMaxDepth = 0;
            maxSamplers = 0;
            maxParameterSize = 0;
            memBaseAddressAlign = 0;
            minDataTypeAlignSize = 0;
            singleFpConfig = CL_FP_ROUND_TO_NEAREST | CL_FP_INF_NAN;
            doubleFpConfig = CL_FP_FMA |
                             CL_FP_ROUND_TO_NEAREST |
                             CL_FP_ROUND_TO_ZERO |
                             CL_FP_ROUND_TO_INF |
                             CL_FP_INF_NAN |
                             CL_FP_DENORM;
            globleMemCacheType = CL_NONE;
            globalMemCachelineSize = CL_NONE;
            globalMemCacheSize = 0;
            globalMemSize = 0;
            maxConstBufSize = 0;
            maxConstArgs = 0;
            localMemType = CL_LOCAL;
            localMemSize = 0;
            errCorrectionSupport = CL_FALSE;
            hostUnifiedMem = CL_FALSE;
            timerResolution = 0;
            endianLittle = CL_FALSE;
            available = CL_FALSE;
            compilerAvailable = CL_FALSE;
            execCapabilities = CL_EXEC_KERNEL;
            queueProperties = 0;
            platform = 0;
            name = NULL;
            vendorName = NULL;
            driverVersion = NULL;
            profileType = NULL;
            deviceVersion = NULL;
            openclCVersion = NULL;
            extensions = NULL;
        };

        /**
         * Destructor
         */
        ~SDKDeviceInfo()
        {
            delete[] maxWorkItemSizes;
            delete[] name;
            delete[] vendorName;
            delete[] driverVersion;
            delete[] profileType;
            delete[] deviceVersion;
            delete[] openclCVersion;
            delete[] extensions;
        };

        /**
         * setKernelWorkGroupInfo
         * Set all information for a given device id
         * @param deviceId deviceID
         * @return 0 if success else nonzero
         */
        int setDeviceInfo(cl_device_id deviceId)
        {
            cl_int status = CL_SUCCESS;
            //Get device type
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_TYPE,
                         sizeof(cl_device_type),
                         &dType,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_TYPE) failed");
            //Get vender ID
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_VENDOR_ID,
                         sizeof(cl_uint),
                         &venderId,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_VENDOR_ID) failed");
            //Get max compute units
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_MAX_COMPUTE_UNITS,
                         sizeof(cl_uint),
                         &maxComputeUnits,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_MAX_COMPUTE_UNITS) failed");
            //Get max work item dimensions
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS,
                         sizeof(cl_uint),
                         &maxWorkItemDims,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS) failed");
            //Get max work item sizes
            if(maxWorkItemSizes != NULL) delete[] maxWorkItemSizes;
            maxWorkItemSizes = new size_t[maxWorkItemDims];
            CHECK_ALLOCATION(maxWorkItemSizes,
                             "Failed to allocate memory(maxWorkItemSizes)");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_MAX_WORK_ITEM_SIZES,
                         maxWorkItemDims * sizeof(size_t),
                         maxWorkItemSizes,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS) failed");
            // Maximum work group size
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_MAX_WORK_GROUP_SIZE,
                         sizeof(size_t),
                         &maxWorkGroupSize,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_MAX_WORK_GROUP_SIZE) failed");
            // Preferred vector sizes of all data types
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR,
                         sizeof(cl_uint),
                         &preferredCharVecWidth,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR) failed");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT,
                         sizeof(cl_uint),
                         &preferredShortVecWidth,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT) failed");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT,
                         sizeof(cl_uint),
                         &preferredIntVecWidth,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT) failed");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG,
                         sizeof(cl_uint),
                         &preferredLongVecWidth,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG) failed");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT,
                         sizeof(cl_uint),
                         &preferredFloatVecWidth,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT) failed");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE,
                         sizeof(cl_uint),
                         &preferredDoubleVecWidth,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE) failed");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF,
                         sizeof(cl_uint),
                         &preferredHalfVecWidth,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF) failed");
            // Clock frequency
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_MAX_CLOCK_FREQUENCY,
                         sizeof(cl_uint),
                         &maxClockFrequency,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_MAX_CLOCK_FREQUENCY) failed");
            // Address bits
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_ADDRESS_BITS,
                         sizeof(cl_uint),
                         &addressBits,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_ADDRESS_BITS) failed");
            // Maximum memory alloc size
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_MAX_MEM_ALLOC_SIZE,
                         sizeof(cl_ulong),
                         &maxMemAllocSize,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_MAX_MEM_ALLOC_SIZE) failed");
            // Image support
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_IMAGE_SUPPORT,
                         sizeof(cl_bool),
                         &imageSupport,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_IMAGE_SUPPORT) failed");
            // Maximum read image arguments
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_MAX_READ_IMAGE_ARGS,
                         sizeof(cl_uint),
                         &maxReadImageArgs,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_MAX_READ_IMAGE_ARGS) failed");
            // Maximum write image arguments
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_MAX_WRITE_IMAGE_ARGS,
                         sizeof(cl_uint),
                         &maxWriteImageArgs,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_MAX_WRITE_IMAGE_ARGS) failed");
            // 2D image and 3D dimensions
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_IMAGE2D_MAX_WIDTH,
                         sizeof(size_t),
                         &image2dMaxWidth,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_IMAGE2D_MAX_WIDTH) failed");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_IMAGE2D_MAX_HEIGHT,
                         sizeof(size_t),
                         &image2dMaxHeight,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_IMAGE2D_MAX_HEIGHT) failed");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_IMAGE3D_MAX_WIDTH,
                         sizeof(size_t),
                         &image3dMaxWidth,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_IMAGE3D_MAX_WIDTH) failed");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_IMAGE3D_MAX_HEIGHT,
                         sizeof(size_t),
                         &image3dMaxHeight,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_IMAGE3D_MAX_HEIGHT) failed");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_IMAGE3D_MAX_DEPTH,
                         sizeof(size_t),
                         &image3dMaxDepth,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_IMAGE3D_MAX_DEPTH) failed");
            // Maximum samplers
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_MAX_SAMPLERS,
                         sizeof(cl_uint),
                         &maxSamplers,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_MAX_SAMPLERS) failed");
            // Maximum parameter size
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_MAX_PARAMETER_SIZE,
                         sizeof(size_t),
                         &maxParameterSize,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_MAX_PARAMETER_SIZE) failed");
            // Memory base address align
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_MEM_BASE_ADDR_ALIGN,
                         sizeof(cl_uint),
                         &memBaseAddressAlign,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_MEM_BASE_ADDR_ALIGN) failed");
            // Minimum data type align size
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE,
                         sizeof(cl_uint),
                         &minDataTypeAlignSize,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE) failed");
            // Single precision floating point configuration
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_SINGLE_FP_CONFIG,
                         sizeof(cl_device_fp_config),
                         &singleFpConfig,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_SINGLE_FP_CONFIG) failed");
            // Double precision floating point configuration
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_DOUBLE_FP_CONFIG,
                         sizeof(cl_device_fp_config),
                         &doubleFpConfig,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_DOUBLE_FP_CONFIG) failed");
            // Global memory cache type
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_GLOBAL_MEM_CACHE_TYPE,
                         sizeof(cl_device_mem_cache_type),
                         &globleMemCacheType,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_GLOBAL_MEM_CACHE_TYPE) failed");
            // Global memory cache line size
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE,
                         sizeof(cl_uint),
                         &globalMemCachelineSize,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE) failed");
            // Global memory cache size
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_GLOBAL_MEM_CACHE_SIZE,
                         sizeof(cl_ulong),
                         &globalMemCacheSize,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_GLOBAL_MEM_CACHE_SIZE) failed");
            // Global memory size
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_GLOBAL_MEM_SIZE,
                         sizeof(cl_ulong),
                         &globalMemSize,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_GLOBAL_MEM_SIZE) failed");
            // Maximum constant buffer size
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE,
                         sizeof(cl_ulong),
                         &maxConstBufSize,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE) failed");
            // Maximum constant arguments
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_MAX_CONSTANT_ARGS,
                         sizeof(cl_uint),
                         &maxConstArgs,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_MAX_CONSTANT_ARGS) failed");
            // Local memory type
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_LOCAL_MEM_TYPE,
                         sizeof(cl_device_local_mem_type),
                         &localMemType,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_LOCAL_MEM_TYPE) failed");
            // Local memory size
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_LOCAL_MEM_SIZE,
                         sizeof(cl_ulong),
                         &localMemSize,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_LOCAL_MEM_SIZE) failed");
            // Error correction support
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_ERROR_CORRECTION_SUPPORT,
                         sizeof(cl_bool),
                         &errCorrectionSupport,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_ERROR_CORRECTION_SUPPORT) failed");
            // Profiling timer resolution
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_PROFILING_TIMER_RESOLUTION,
                         sizeof(size_t),
                         &timerResolution,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_PROFILING_TIMER_RESOLUTION) failed");
            // Endian little
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_ENDIAN_LITTLE,
                         sizeof(cl_bool),
                         &endianLittle,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_ENDIAN_LITTLE) failed");
            // Device available
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_AVAILABLE,
                         sizeof(cl_bool),
                         &available,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_AVAILABLE) failed");
            // Device compiler available
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_COMPILER_AVAILABLE,
                         sizeof(cl_bool),
                         &compilerAvailable,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_COMPILER_AVAILABLE) failed");
            // Device execution capabilities
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_EXECUTION_CAPABILITIES,
                         sizeof(cl_device_exec_capabilities),
                         &execCapabilities,
                         NULL);
           CHECK_OPENCL_ERROR2(status,
                               "clGetDeviceIDs(CL_DEVICE_EXECUTION_CAPABILITIES) failed");
            // Device queue properities
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_QUEUE_PROPERTIES,
                         sizeof(cl_command_queue_properties),
                         &queueProperties,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_QUEUE_PROPERTIES) failed");
            // Platform
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_PLATFORM,
                         sizeof(cl_platform_id),
                         &platform,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_PLATFORM) failed");
            // Device name
            size_t tempSize = 0;
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_NAME,
                         0,
                         NULL,
                         &tempSize);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_NAME) failed");
            if(name != NULL) delete[] name;
            name = new char[tempSize];
            CHECK_ALLOCATION(name, "Failed to allocate memory(name)");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_NAME,
                         sizeof(char) * tempSize,
                         name,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_NAME) failed");
            // Vender name
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_VENDOR,
                         0,
                         NULL,
                         &tempSize);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_VENDOR) failed");
            if(vendorName != NULL) delete[] vendorName;
            vendorName = new char[tempSize];
            CHECK_ALLOCATION(vendorName, "Failed to allocate memory(venderName)");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_VENDOR,
                         sizeof(char) * tempSize,
                         vendorName,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_VENDOR) failed");
            // Driver name
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DRIVER_VERSION,
                         0,
                         NULL,
                         &tempSize);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DRIVER_VERSION) failed");
            if(driverVersion != NULL) delete[] driverVersion;
            driverVersion = new char[tempSize];
            CHECK_ALLOCATION(driverVersion, "Failed to allocate memory(driverVersion)");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DRIVER_VERSION,
                         sizeof(char) * tempSize,
                         driverVersion,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DRIVER_VERSION) failed");
            // Device profile
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_PROFILE,
                         0,
                         NULL,
                         &tempSize);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_PROFILE) failed");
            if(profileType != NULL) delete[] profileType;
            profileType = new char[tempSize];
            CHECK_ALLOCATION(profileType, "Failed to allocate memory(profileType)");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_PROFILE,
                         sizeof(char) * tempSize,
                         profileType,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_PROFILE) failed");
            // Device version
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_VERSION,
                         0,
                         NULL,
                         &tempSize);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_VERSION) failed");
            if(deviceVersion != NULL) delete[] deviceVersion;
            deviceVersion = new char[tempSize];
            CHECK_ALLOCATION(deviceVersion, "Failed to allocate memory(deviceVersion)");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_VERSION,
                         sizeof(char) * tempSize,
                         deviceVersion,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_VERSION) failed");
            // Device extensions
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_EXTENSIONS,
                         0,
                         NULL,
                         &tempSize);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_EXTENSIONS) failed");
            if(extensions != NULL) delete[] extensions;
            extensions = new char[tempSize];
            CHECK_ALLOCATION(extensions, "Failed to allocate memory(extensions)");
            status = clGetDeviceInfo(
                         deviceId,
                         CL_DEVICE_EXTENSIONS,
                         sizeof(char) * tempSize,
                         extensions,
                         NULL);
           CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_EXTENSIONS) failed");
            // Device parameters of OpenCL 1.1 Specification
#ifdef CL_VERSION_1_1
            std::string deviceVerStr(deviceVersion);
            size_t vStart = deviceVerStr.find(" ", 0);
            size_t vEnd = deviceVerStr.find(" ", vStart + 1);
            std::string vStrVal = deviceVerStr.substr(vStart + 1, vEnd - vStart - 1);
            if(vStrVal.compare("1.0") > 0)
            {
                // Native vector sizes of all data types
                status = clGetDeviceInfo(
                             deviceId,
                             CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR,
                             sizeof(cl_uint),
                             &nativeCharVecWidth,
                             NULL);
               CHECK_OPENCL_ERROR2(status,
                                   "clGetDeviceIDs(CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR) failed");
                status = clGetDeviceInfo(
                             deviceId,
                             CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT,
                             sizeof(cl_uint),
                             &nativeShortVecWidth,
                             NULL);
               CHECK_OPENCL_ERROR2(status,
                                   "clGetDeviceIDs(CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT) failed");
                status = clGetDeviceInfo(
                             deviceId,
                             CL_DEVICE_NATIVE_VECTOR_WIDTH_INT,
                             sizeof(cl_uint),
                             &nativeIntVecWidth,
                             NULL);
               CHECK_OPENCL_ERROR2(status,
                                   "clGetDeviceIDs(CL_DEVICE_NATIVE_VECTOR_WIDTH_INT) failed");
                status = clGetDeviceInfo(
                             deviceId,
                             CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG,
                             sizeof(cl_uint),
                             &nativeLongVecWidth,
                             NULL);
               CHECK_OPENCL_ERROR2(status,
                                   "clGetDeviceIDs(CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG) failed");
                status = clGetDeviceInfo(
                             deviceId,
                             CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT,
                             sizeof(cl_uint),
                             &nativeFloatVecWidth,
                             NULL);
               CHECK_OPENCL_ERROR2(status,
                                   "clGetDeviceIDs(CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT) failed");
                status = clGetDeviceInfo(
                             deviceId,
                             CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE,
                             sizeof(cl_uint),
                             &nativeDoubleVecWidth,
                             NULL);
               CHECK_OPENCL_ERROR2(status,
                                   "clGetDeviceIDs(CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE) failed");
                status = clGetDeviceInfo(
                             deviceId,
                             CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF,
                             sizeof(cl_uint),
                             &nativeHalfVecWidth,
                             NULL);
               CHECK_OPENCL_ERROR2(status,
                                   "clGetDeviceIDs(CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF) failed");
                // Host unified memory
                status = clGetDeviceInfo(
                             deviceId,
                             CL_DEVICE_HOST_UNIFIED_MEMORY,
                             sizeof(cl_bool),
                             &hostUnifiedMem,
                             NULL);
               CHECK_OPENCL_ERROR2(status,
                                   "clGetDeviceIDs(CL_DEVICE_HOST_UNIFIED_MEMORY) failed");
                // Device OpenCL C version
                status = clGetDeviceInfo(
                             deviceId,
                             CL_DEVICE_OPENCL_C_VERSION,
                             0,
                             NULL,
                             &tempSize);
               CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_OPENCL_C_VERSION) failed");
                if(openclCVersion != NULL) delete[] openclCVersion;
                openclCVersion = new char[tempSize];
                CHECK_ALLOCATION(openclCVersion, "Failed to allocate memory(openclCVersion)");
                status = clGetDeviceInfo(
                             deviceId,
                             CL_DEVICE_OPENCL_C_VERSION,
                             sizeof(char) * tempSize,
                             openclCVersion,
                             NULL);
               CHECK_OPENCL_ERROR2(status, "clGetDeviceIDs(CL_DEVICE_OPENCL_C_VERSION) failed");
            }
#endif
            return SDK_SUCCESS;
        }




};



