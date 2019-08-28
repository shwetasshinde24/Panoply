## Panoply Overview

Intel SGX, a new security capability in emerging CPUs, allows user-level application code to execute in hardware isolated enclaves. Enclave memory is isolated from all other software on the system, even from the privileged OS or hypervisor. While being a promising hardware-rooted building block, enclaves have severely limited capabilities, such as no native access to system calls and standard OS abstractions. These OS abstractions are used ubiquitously in real-world applications.

We present a new system called Panoply which bridges the gap between the SGX-native abstractions and the standard OS abstractions which feature-rich, commodity Linux applications require. Panoply exposse the standard POSIX abstractions to application logic, including access to filesystems, network, multi-threading, multi-processing and thread synchronization primitives. Further, Panoply enforces a strong integrity property for the inter-enclave interactions, ensuring that the execution of the application follows the legitimate control and data-flow even if the OS misbehaves. Thus, commodity Linux applications can enhance security by splitting their application logic in one or more enclaves, or by importing enclave-libraries, with little effort. In contrast to previous systems that enable comparable richness, Panoply  offers two orders of magnitude lower TCB.

-----

## Before we begin with Panoply

Panoply is implemented on top of the Intel SDK 1.6 shipped for Linux Kernel v3.13. Panoply  comprises of a set of API libraries and build extensions. Before you start using Panoply, you should setup a stable Intel SDK developement environment. Then you can quickly test the Panoply applications. Please follow the instructions below, if you are starting from a fresh non-SGX environment. If you have an existing SGX developement environment, then proceed directly to the [demo](https://shwetasshinde24.github.io/Panoply/#panoply-demo) instructions.

The Linux SGX developer environment comprises of hardware with SGX support, bios support for SGX, the SGX driver, the SGX SDK, and the SGX Platform Software. Out of these, the hardware support depends on your processor and the BIOS support is provided by the vendor. The SGX driver, SDK and PSW are provided by Intel.

### Hardware Support and BIOS Settings

* Check if your machine is listed in the following list of hardware which supports Intel SGX 
[https://github.com/ayeks/SGX-hardware](https://github.com/ayeks/SGX-hardware)

* Ensure that you have enabled SGX support in your BIOS. 

* Run the test-sgx.c code from [https://github.com/ayeks/SGX-hardware](https://github.com/ayeks/SGX-hardware) to quickly  check if  SGX is available for your CPU and enabled in BIOS.
 

### Software Requirements

Following is the software configuration required for Intel SGX SDK and Panoply.

* [Ubuntu* Desktop-14.04-LTS 64bits](http://old-releases.ubuntu.com/releases/trusty/ubuntu-14.04.1-desktop-amd64.iso)

* [Linux Kernel v3.13.0-32-generic](http://packages.ubuntu.com/trusty/kernel/linux-image-3.13.0-32-generic)

-----


## Intel SGX Setup

### Build and Install Intel SGX Driver
[Version 1.6](https://github.com/01org/linux-sgx-driver/tree/sgx_driver_1.6)


###  Build and Install Intel SGX SDK and Intel SGX PSW

[Version 1.6](https://github.com/01org/linux-sgx/tree/sgx_1.6)

### Resources for Troubleshooting

#### Intel Developer Zone: 

* [Intel® Software Guard Extensions SDK](https://software.intel.com/en-us/sgx-sdk)

#### Intel Documentation:

* [Installation Guide](https://download.01.org/intel-sgx/linux-1.6/docs/Intel_SGX_SDK_Installation_Guide_Linux_1.6_Open_Source.pdf)

* [Developer Guide](https://download.01.org/intel-sgx/linux-1.6/docs/Intel_SGX_Developer_Guide.pdf)

* [Developer Reference](https://download.01.org/intel-sgx/linux-1.6/docs/Intel_SGX_SDK_Developer_Reference_Linux_1.6_Open_Source.pdf)

-----

## Running Sample code from SGX SDK
Before you start with Panoply, you should ensure that you are able to execute SGX applications. To do this, copy the sample code (the folder is located by default in /opt/intel/sgxsdk/SampleCode/SampleEnclave) to your workspace and build it (<code>make all</code> inside SampleEnclave folder). After sucesfully building the Sample, test it by running <code>./app</code>


-----

## Panoply Demo

You can setup the OpenSSL demo on your own machine using the following steps.

### Getting the Demo Code

You can download the demo code from the [project branch](https://github.com/shwetasshinde24/Panoply/tree/demo-openssl) 

### Executing the OpenSSL Demo Example

#### Extract the zip file

<code>
unzip Panoply-demo-openssl.zip
</code>

#### Build libssl and libcrypto libraries

<code>
cd Panoply-demo-openssl/topenssl/
</code>

<code>
make all -j8
</code>

This produces _libssl.a_ and _libcrypto.a_ files in the topenssl folder.

#### Copy the libraries to src folder

<code>
cp libcrypto.a libssl.a ../src/
</code>

#### Build the Enclave and the App

<code>
cd ../src/
</code>

<code>
make all
</code>

This produces a _TopensslEnclave.signed.so_ file for enclave and an _app_ file for the executable.

#### Run the app

<code>
./app sha1
</code>

The above command is just an example. You can try other tests for the OpenSSL benchmark. For running the complete benchmark, just run the app file without any arguments. 

<code>
./app
</code>

#### Making changes to the App

The App.cpp file has the following code:

* Current code

<code>
/* ret = TopensslEnclave_ecall_test_bm_ssl(global_eid, &ecall_return, argc, argv); */
</code>

<code>
ret = TopensslEnclave_ecall_test_speed_crypto(global_eid, &ecall_return, argc, argv);
</code>

You can modify the above code to execute the SSL test. Do the following changes to the code.

* Modified code

<code>
ret = TopensslEnclave_ecall_test_bm_ssl(global_eid, &ecall_return, argc, argv);         
</code>

<code>
/* ret = TopensslEnclave_ecall_test_speed_crypto(global_eid, &ecall_return, argc, argv); */
</code>

* Build and re-run the app

<code>
make all
</code>

<code>
./app -dhe1024dsa -bytes 102400 -num 10 -tls1 -server_auth -time
</code>

-----

## Case-studies and Benchmarks

The released case-studies and the benchmarks are available from the [Panoply code repository](https://github.com/shwetasshinde24/Panoply)

### Case-studies

 - [OpenSSL](https://github.com/shwetasshinde24/Panoply/tree/master/case-studies/openssl)

 - [FreeTDS](https://github.com/shwetasshinde24/Panoply/tree/master/case-studies/freetds)

 - [H2O Webserver](https://github.com/shwetasshinde24/Panoply/tree/master/case-studies/h2o)

 - [Tor](https://github.com/shwetasshinde24/Panoply/tree/master/case-studies/tor)

### Benchmarks

 - [LMBench](https://github.com/shwetasshinde24/Panoply/tree/master/benchmarks/lmbench)

-----


## FAQs

We have tested the demo in our development environment, and have tried our best to document the procedure to setup a similar environment on your machine. However, several things might go wrong in this process. Following is a list of all the issues we have seen in our experience.

### I cannot run the demo. Is something wrong with my SGX SDK or Panoply setup?
Before starting the Panoply demo setup, ensure that you are able to execute the Sample application shipped with the Intel SDX SDK. If you are not able to execute the SDK Sample code, then something went wrong with your SDX SDK setup. However, if you were able to execute the sample code and only OpenSSL is failing, then perhaps its a Panoply-specific problem. Please drop me an [email](https://www.comp.nus.edu.sg/~shweta24/) with the details of the bug / error / runtime failure logs.  

### I am getting a compile time error about "sgx-status.h". Is something wrong with my setup?

The SGX SDK version you installed does not have this header file. Download the header file from [here](https://www.dropbox.com/s/w1rhk2ytbfsvlvp/sgx_status.h?dl=0), and place it in the include directory of the SDK installation. The default location for the include direcroty is /opt/intel/sgxsdk/include and the file path is  /opt/intel/sgxsdk/include/sgx_status.h

### I do not have a machine with SGX Hardware support. How can I use Panoply?

Yes, you can setup the SDK in simulation mode for non-SGX machines. Please refer to the [Intel Installation Guide](https://download.01.org/intel-sgx/linux-1.6/docs/Intel_SGX_SDK_Installation_Guide_Linux_1.6_Open_Source.pdf) to know more about how to setup the simulation enviroment. After the setup, make sure you are able to run the Sample code shipped with the SDK inside the VM. Then, simply follow the steps listed in the Panoply demo setup guide.

### I don't have a linux machine with the required OS and / or kernel version. Can I still try out Panoply?

Yes, you can create a Ubuntu 14.04 VM and install Intel SGX SDK for simulation mode. This will allow you to execute SGX applications. After the setup, make sure you are able to run the Sample code shipped with the SDK inside the VM. Then, simply follow the steps listed in the Panoply demo setup guide.

-----


## Publications

* **"Panoply: Low-TCB Linux Applications With SGX Enclaves"**, 
_Shweta Shinde, Dat Le Tien, Shruti Tople, and Prateek Saxena_, To appear at 
Network and Distributed System Security Symposium (NDSS 2017)
[Paper](https://www.comp.nus.edu.sg/~shweta24/publications/panoply_ndss17.pdf)

-----


## Contact 

### Panoply Team 

#### [Shweta Shinde](https://people.eecs.berkeley.edu/~shwetas/)

#### [Dat Le Tien](https://coinsrs.no/dat-le-tien/)

#### [Shruti Tople](http://www.comp.nus.edu.sg/~shruti90/)

#### [Priya Deb](http://www.comp.nus.edu.sg/~priya/)

#### [Prateek Saxena](https://www.comp.nus.edu.sg/~prateeks/) 


### Support

Having trouble with Panoply? Check out our [FAQ](https://shwetasshinde24.github.io/Panoply/#faqs) or tell us about it [directly](https://www.comp.nus.edu.sg/~shweta24/) and we’ll help you sort it out.

### Announcements

Want to get future updates for Panoply? Join our [Google Group](panoply-announcements@googlegroups.com). 

### Acknowledging Panoply

* Using Panoply in your research projects and want to acknowledge it? Just [cite](https://dblp.uni-trier.de/rec/bibtex/conf/ndss/ShindeTTS17) our [NDSS'17 paper](https://www.comp.nus.edu.sg/~shweta24/publications/panoply_ndss17.pdf).

* Panoply is released under [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0).

-----


## Acknowledgements


### Intel 
We thank Mona Vij and Simon Johnson from Intel for their feedback. 


### National Research Foundation 
This research was partially supported by a grant from the National Research Foundation, Prime Ministers Office, Singapore under its National Cybersecurity R&D Program (<a href="http://www.comp.nus.edu.sg/~tsunami/">TSUNAMi project, No. NRF2014NCR-NCR001-21 </a>) and administered by the National Cybersecurity R&D Directorate.

<p align="center"><img src="http://www.nrf.gov.sg/html/images/common/logo-nrf.png" alt="National Research Foundation, Prime Ministers Office, Singapore"> </p>
