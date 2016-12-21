## Panoply Home

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. 

-----

## Getting Started

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. 

### Hardware Requirements

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. 


### Enable SGX in BIOS

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. 


#### Quick test for checking hardware support

https://github.com/ayeks/SGX-hardware

### Software Requirements

* Ubuntu* Desktop-14.04-LTS 64bits

* Linux Kernel v3.13.

-----


## Intel SGX Setup

### Build and Install Intel SGX Driver
https://github.com/01org/linux-sgx-driver


###  Build and Install Intel SGX SDK and Intel SGX PSW

https://github.com/01org/linux-sgx

### Resources for Troubleshooting

#### Intel Developer Zone: 

* [Intel® Software Guard Extensions SDK](https://software.intel.com/en-us/sgx-sdk)

#### Intel Documentation:

* [Installation Guide](https://download.01.org/intel-sgx/linux-1.6/docs/Intel_SGX_SDK_Installation_Guide_Linux_1.6_Open_Source.pdf)

* [Developer Guide](https://download.01.org/intel-sgx/linux-1.6/docs/Intel_SGX_Developer_Guide.pdf)

* [Developer Reference](https://download.01.org/intel-sgx/linux-1.6/docs/Intel_SGX_SDK_Developer_Reference_Linux_1.6_Open_Source.pdf)


-----

## Panoply Demo

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. 


### Platform Setup

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer nec odio. Praesent libero. Sed cursus ante dapibus diam. Sed nisi. Nulla quis sem at nibh elementum imperdiet. Duis sagittis ipsum. Praesent mauris. Fusce nec tellus sed augue semper porta. Mauris massa. Vestibulum lacinia arcu eget nulla. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Curabitur sodales ligula in libero. 

### Getting the Demo Code

Thank you for your interest in Panoply. Please drop me an [email] (https://www.comp.nus.edu.sg/~shweta24/) for getting access to the demo code. 

### Executing the Example

#### build libssl ad libcrypto libraries

<code>
cd openssl/ssl_bench/topenssl/
make all -j8
</code>

#### move the libraries to src folder

<code>
cp libcrypto.a libssl.a ../src/
</code>

#### build the enclave and the app

<code>
cd ../src/
make all
</code>

#### run the app

<code>
./app sha1
</code>

#### making changes to the app

* Current code

<code>
// ret = TopensslEnclave_ecall_test_bm_ssl(global_eid, &ecall_return, argc, argv);
ret = TopensslEnclave_ecall_test_speed_crypto(global_eid, &ecall_return, argc, argv);
</code>

* Modified code

<code>
ret = TopensslEnclave_ecall_test_bm_ssl(global_eid, &ecall_return, argc, argv);
//ret = TopensslEnclave_ecall_test_speed_crypto(global_eid, &ecall_return, argc, argv);
</code>

* Build and re-run the app

<code>
make all
 ./app -dhe1024dsa -bytes 102400 -num 10 -tls1 -server_auth -time
</code>


### Writing your own Application

-----


## FAQs

We have tested the demo in our development environment, and have tried our best to document the procedure to setup a similar environment on your machine. However, several things might go wrong in this process. Following is a list of all the issues we have seen in our experienceL

### I cannot run the demo. Is something wrong with my SGX SDK or Panoply setup?
Before starting the Panoply demo setup, ensure that you are able to execute the Sample application shipped with the Intel SDX SDK. If you are not able to execute the SDK Sample code, then something went wrong with your SDX SDK setup. However, if you were able to execute the sample code and only OpenSSL is failing, then perhaps its a Panoply-specific problem. Please drop me an [email] (https://www.comp.nus.edu.sg/~shweta24/) with the details of the bug / error / runtime failure logs.  

### I am getting a compile time error about "sgx-status.h". Is something wrong with my setup?

Don't panic. The SGX SDK version you installed does not have this header file. Download the header file from [here](https://www.dropbox.com/s/w1rhk2ytbfsvlvp/sgx_status.h?dl=0), and place it in the include directory of the SDK installation. The default location for the include direcroty is /opt/intel/sgxsdk/include and the file path is  /opt/intel/sgxsdk/include/sgx_status.h

### I do not have a machine with SGX Hardware support. How can I use Panoply?

Yes, you can setup the SDK in simulation mode for non-SGX machines. Please refer to the [Intel Installation Guide] (https://download.01.org/intel-sgx/linux-1.6/docs/Intel_SGX_SDK_Installation_Guide_Linux_1.6_Open_Source.pdf) to know more about how to setup the simulation enviroment. After the setup, make sure you are able to run the Sample code shipped with the SDK inside the VM. Then, simply follow the steps listed in the Panoply demo setup guide.

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

#### [Shweta Shinde](https://www.comp.nus.edu.sg/~shweta24/): Project Maintainer

#### [Dat Le Tien](https://coinsrs.no/dat-le-tien/)

#### [Shruti Tople](http://www.comp.nus.edu.sg/~shruti90/)

#### [Prateek Saxena](https://www.comp.nus.edu.sg/~prateeks/)
 

### Support

Having trouble with Panoply? Check out our [FAQ](https://shwetasshinde24.github.io/Panoply/faq.html) or tell us about it [directly]() and we’ll help you sort it out.

### Announcements

Want to get future updates for Panoply? Join our [Google Group](panoply-announcements@googlegroups.com). 

### Acknowledging Panoply

* Using Panoply in your research projects and want to acknowledge it? Just [cite](https://www.comp.nus.edu.sg/~shweta24/panoply_ndss17.bib) our [NDSS'17 paper](https://www.comp.nus.edu.sg/~shweta24/publications/panoply_ndss17.pdf).

* Panoply is released under [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0).

-----


## Acknowledgements


### Intel 
We thank Mona Vij and Simon Johnson from Intel for their feedback. 


### National Research Foundation 
This research was partially supported by a grant from the National Research Foundation, Prime Ministers Office, Singapore under its National Cybersecurity R&D Program (<a href="http://www.comp.nus.edu.sg/~tsunami/">TSUNAMi project, No. NRF2014NCR-NCR001-21 </a>) and administered by the National Cybersecurity R&D Directorate.

<p align="center"><img src="http://www.nrf.gov.sg/html/images/common/logo-nrf.png" alt="National Research Foundation, Prime Ministers Office, Singapore"> </p>
