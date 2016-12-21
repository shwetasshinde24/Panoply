## Panoply Home

You can use the [editor on GitHub](https://github.com/shwetasshinde24/Panoply/edit/gh-pages/README.md) to maintain and preview the content for your website in Markdown files.

-----

## Getting Started

### Hardware Requirements

### Enable SGX in BIOS

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

You can use the [editor on GitHub](https://github.com/shwetasshinde24/Panoply/edit/gh-pages/README.md) to maintain and preview the content for your website in Markdown files.

Whenever you commit to this repository, GitHub Pages will run [Jekyll](https://jekyllrb.com/) to rebuild the pages in your site, from the content in your Markdown files.

### Platform Setup

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

### Getting the Demo Code

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/shwetasshinde24/Panoply/settings). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Executing the Example

#### build libssl ad libcrypto libraries
<code>
cd openssl/ssl_bench/topenssl/
make all -j8
</code>
#### move the libraries to src folder
cp libcrypto.a libssl.a ../src/

#### build the enclave and the app
cd ../src/
make all

#### run the app
./app sha1

### Writing your own Application

-----


## FAQs

You can use the [editor on GitHub](https://github.com/shwetasshinde24/Panoply/edit/gh-pages/README.md) to maintain and preview the content for your website in Markdown files.

Whenever you commit to this repository, GitHub Pages will run [Jekyll](https://jekyllrb.com/) to rebuild the pages in your site, from the content in your Markdown files.

### I do not have a machine with SGX Hardware support. How can I use Panoply?

Markdown is a lightweight and easy-to-use syntax for styling your writing. It includes conventions for

### I don't have a linux machine with the required kernel version. Can I still try out Panoply?

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/shwetasshinde24/Panoply/settings). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### I am getting a compile time error about "sgx-status.h". Is something wrong with my setup?

Having trouble with Pages? Check out our [documentation](https://help.github.com/categories/github-pages-basics/) or [contact support](https://github.com/contact) and we’ll help you sort it out.

-----


## Publications

* **"Panoply: Low-TCB Linux Applications With SGX Enclaves"**, 
_Shweta Shinde, Dat Le Tien, Shruti Tople, and Prateek Saxena_, To appear at 
Network and Distributed System Security Symposium (NDSS 2017)
[Paper](https://www.comp.nus.edu.sg/~shweta24/publications/panoply_ndss17.pdf)

-----


## Contact 

### Panoply Team 

#### [Shweta Shinde](https://www.comp.nus.edu.sg/~shweta24/)

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
