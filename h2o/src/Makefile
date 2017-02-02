######## SGX SDK Settings ########

SGX_SDK ?= /opt/intel/sgxsdk
SGX_MODE ?= HW
SGX_ARCH ?= x64
#SGX_PRERELEASE ?= 1
SGX_DEBUG ?= 1

ifeq ($(shell getconf LONG_BIT), 32)
	SGX_ARCH := x86
else ifeq ($(findstring -m32, $(CXXFLAGS)), -m32)
	SGX_ARCH := x86
endif

ifeq ($(SGX_ARCH), x86)
	SGX_COMMON_CFLAGS := -m32
	SGX_LIBRARY_PATH := $(SGX_SDK)/lib
	SGX_ENCLAVE_SIGNER := $(SGX_SDK)/bin/x86/sgx_sign
	SGX_EDGER8R := $(SGX_SDK)/bin/x86/sgx_edger8r
else
	SGX_COMMON_CFLAGS := -m64
	SGX_LIBRARY_PATH := $(SGX_SDK)/lib64
	SGX_ENCLAVE_SIGNER := $(SGX_SDK)/bin/x64/sgx_sign
	SGX_EDGER8R := $(SGX_SDK)/bin/x64/sgx_edger8r
endif

ifeq ($(SGX_DEBUG), 1)
ifeq ($(SGX_PRERELEASE), 1)
$(error Cannot set SGX_DEBUG and SGX_PRERELEASE at the same time!!)
endif
endif

ifeq ($(SGX_DEBUG), 1)
        SGX_COMMON_CFLAGS += -O0 -g
else
        SGX_COMMON_CFLAGS += -O2
endif

######## App Settings ########

ifneq ($(SGX_MODE), HW)
	Urts_Library_Name := sgx_urts_sim
else
	Urts_Library_Name := sgx_urts
endif

App_Cpp_Files := App/App.cpp $(wildcard App/IO/*.cpp) $(wildcard App/Thread/*.cpp) $(wildcard App/SysEnvironment/*.cpp) $(wildcard App/Net/*.cpp) $(wildcard App/ssl/*.cpp) $(wildcard App/Untrusted_LocalAttestation/*.cpp) 
App_Include_Paths := -IInclude -IApp -I$(SGX_SDK)/include -I../include -I../src/H2oEnclave/include  -I../topenssl/include 

App_C_Flags := $(SGX_COMMON_CFLAGS) -fPIC -Wno-attributes $(App_Include_Paths) -DH2O_USE_LIBUV=0

# Three configuration modes - Debug, prerelease, release
#   Debug - Macro DEBUG enabled.
#   Prerelease - Macro NDEBUG and EDEBUG enabled.
#   Release - Macro NDEBUG enabled.
ifeq ($(SGX_DEBUG), 1)
        App_C_Flags += -DDEBUG -UNDEBUG -UEDEBUG
else ifeq ($(SGX_PRERELEASE), 1)
        App_C_Flags += -DNDEBUG -DEDEBUG -UDEBUG
else
        App_C_Flags += -DNDEBUG -UEDEBUG -UDEBUG
endif

App_Cpp_Flags := $(App_C_Flags) -std=c++11
App_Link_Flags := $(SGX_COMMON_CFLAGS) -L$(SGX_LIBRARY_PATH) -l$(Urts_Library_Name) -lpthread 

ifneq ($(SGX_MODE), HW)
	App_Link_Flags += -lsgx_uae_service_sim
else
	App_Link_Flags += -lsgx_uae_service
endif

App_Cpp_Objects := $(App_Cpp_Files:.cpp=.o)

App_Name := app

######## Enclave Settings ########

ifneq ($(SGX_MODE), HW)
	Trts_Library_Name := sgx_trts_sim
	Service_Library_Name := sgx_tservice_sim
	Crypto_Library_Name := sgx_tcrypto
else
	Trts_Library_Name := sgx_trts
	Service_Library_Name := sgx_tservice
	Crypto_Library_Name := sgx_tcrypto
endif

######## Library Settings ########

#Trust_Lib_Name := libsyscall_Trusted.a
#TrustLib_Cpp_Files := $(wildcard Sysocall/IO/*.cpp)
#TrustLib_Cpp_Objects := $(TrustLib_Cpp_Files:.cpp=.o)
#TrustLib_Include_Paths := -IInclude -I../src/H2oEnclave/include -I$(SGX_SDK)/include -I$(SGX_SDK)/include/tlibc -I$(SGX_SDK)/include/stlport -I$(SGX_SDK)/include/epid -I./Include
#TrustLib_Compile_Flags := $(SGX_COMMON_CFLAGS) -nostdinc -fvisibility=hidden -fpie -fstack-protector -std=c++03 -nostdinc++ $(TrustLib_Include_Paths)


Enclave_Cpp_Files := $(wildcard H2oEnclave/EnclaveUtil/*.cpp) $(wildcard H2oEnclave/IO/*.cpp) $(wildcard H2oEnclave/SysEnvironment/*.cpp) $(wildcard H2oEnclave/Net/*.cpp) $(wildcard H2oEnclave/Thread/*.cpp) $(wildcard H2oEnclave/EnclaveCommunication/*.cpp) $(wildcard H2oEnclave/LocalAttestationCode/*.cpp) $(wildcard H2oEnclave/h2omain/*.cpp) H2oEnclave/ssl.cpp H2oEnclave/NeverbleedEnclave.cpp H2oEnclave/H2oEnclave.cpp
Enclave_Include_Paths := -IInclude -IH2oEnclave -I../src/H2oEnclave/lib/cloexec -I../src/H2oEnclave/lib/picoparser -I../src/H2oEnclave/deps/yoml -I../src/H2oEnclave/deps/yaml/include -I../src/H2oEnclave/deps/neverbleed -I$(SGX_SDK)/include -I$(SGX_SDK)/include/tlibc -I$(SGX_SDK)/include/stlport -I../include  -I../include/zlib -I../src/H2oEnclave/include -I../topenssl/include
Enclave_C_Flags := $(SGX_COMMON_CFLAGS) -nostdinc -fvisibility=hidden -fpie -fstack-protector $(Enclave_Include_Paths) -DH2O_USE_LIBUV=0
Enclave_Cpp_Flags := $(Enclave_C_Flags) -std=c++03 -nostdinc++ -fpermissive -w 
Enclave_Link_Flags := $(SGX_COMMON_CFLAGS) -Wl,--no-undefined -nostdlib -nodefaultlibs -nostartfiles -L$(SGX_LIBRARY_PATH) \
	-Wl,--whole-archive -l$(Trts_Library_Name) -Wl,--no-whole-archive \
	-Wl,--start-group -lsgx_tstdc -lsgx_tstdcxx ./libcrypto.a ./libz.a ./libssl.a ./libyrmcds.a ./libyaml.a -l$(Crypto_Library_Name) -l$(Service_Library_Name) -Wl,--end-group \
	-Wl,-Bstatic -Wl,-Bsymbolic -Wl,--no-undefined \
	-Wl,-pie,-eenclave_entry -Wl,--export-dynamic  \
	-Wl,--defsym,__ImageBase=0 \
	-Wl,--version-script=H2oEnclave/H2oEnclave.lds

Enclave_Cpp_Objects := $(Enclave_Cpp_Files:.cpp=.o)

Enclave_Name := H2oEnclave.so
Signed_Enclave_Name := H2oEnclave.signed.so
Enclave_Config_File := H2oEnclave/H2oEnclave.config.xml

ifeq ($(SGX_MODE), HW)
ifneq ($(SGX_DEBUG), 1)
ifneq ($(SGX_PRERELEASE), 1)
Build_Mode = HW_RELEASE
endif
endif
endif


.PHONY: all run

ifeq ($(Build_Mode), TMP_HW_RELEASE)
all: $(Trust_Lib_Name) $(App_Name) $(Enclave_Name)
	@echo "The project has been built in release hardware mode."
	@echo "Please sign the $(Enclave_Name) first with your signing key before you run the $(App_Name) to launch and access the enclave."
	@echo "To sign the enclave use the command:"
	@echo "   $(SGX_ENCLAVE_SIGNER) sign -key <your key> -enclave $(Enclave_Name) -out <$(Signed_Enclave_Name)> -config $(Enclave_Config_File)"
	@echo "You can also sign the enclave using an external signing tool. See User's Guide for more details."
	@echo "To build the project in simulation mode set SGX_MODE=SIM. To build the project in prerelease mode set SGX_PRERELEASE=1 and SGX_MODE=HW."
else
all: $(Trust_Lib_Name) $(App_Name) $(Signed_Enclave_Name)
endif

run: all
ifneq ($(Build_Mode), TMP_HW_RELEASE)
	@$(CURDIR)/$(App_Name)
	@echo "RUN  =>  $(App_Name) [$(SGX_MODE)|$(SGX_ARCH), OK]"
endif

######## App Objects ########

App/H2oEnclave_u.c: $(SGX_EDGER8R) H2oEnclave/H2oEnclave.edl
	@cd App && $(SGX_EDGER8R) --use-prefix --untrusted ../H2oEnclave/H2oEnclave.edl --search-path ../H2oEnclave --search-path $(SGX_SDK)/include
	@echo "GEN  =>  $@"

App/H2oEnclave_u.o: App/H2oEnclave_u.c
	@$(CC) $(App_C_Flags) -c $< -o $@
	@echo "CC   <=  $<"

App/vrfcert_u.o: App/vrfcert_u.c
	@$(CC) $(App_C_Flags) -c $< -o $@
	@echo "CC   <=  $<"

App/%.o: App/%.cpp
	@$(CXX) $(App_Cpp_Flags) -c $< -o $@
	@echo "CXX  <=  $<"

$(App_Name): App/vrfcert_u.o App/H2oEnclave_u.o $(App_Cpp_Objects)
	@$(CXX) $^ -o $@ $(App_Link_Flags)
	@echo "LINK =>  $@"


######## Enclave Objects ########

H2oEnclave/H2oEnclave_t.c: $(SGX_EDGER8R) H2oEnclave/H2oEnclave.edl 
	@cd H2oEnclave && $(SGX_EDGER8R) --use-prefix --trusted ../H2oEnclave/H2oEnclave.edl --search-path ../H2oEnclave --search-path $(SGX_SDK)/include
	@echo "GEN  =>  $@"

H2oEnclave/H2oEnclave_t.o: H2oEnclave/H2oEnclave_t.c 
	@$(CC) $(Enclave_C_Flags) -c $< -o $@
	@echo "CC   <=  $<"

H2oEnclave/%.o: H2oEnclave/%.cpp
	@$(CXX) $(Enclave_Cpp_Flags) -c $< -o $@
	@echo "CXX  <=  $<"

$(Enclave_Name): H2oEnclave/H2oEnclave_t.o $(Enclave_Cpp_Objects)
	@$(CXX) $^ -o $@ $(Enclave_Link_Flags)
	@echo "LINK =>  $@"

$(Signed_Enclave_Name): $(Enclave_Name)
	@$(SGX_ENCLAVE_SIGNER) sign -key H2oEnclave/H2oEnclave_private.pem -enclave $(Enclave_Name) -out $@ -config $(Enclave_Config_File)
	@echo "SIGN =>  $@"

.PHONY: clean

clean:
	@rm -f $(App_Name) $(Enclave_Name) $(Signed_Enclave_Name) $(App_Cpp_Objects) App/H2oEnclave_u.* $(Enclave_Cpp_Objects) H2oEnclave/H2oEnclave_t.*
