# Panoply
Low-TCB Linux Applications with SGX Enclaves

Please refer to the [Project Page](https://shwetasshinde24.github.io/Panoply) for documentation and setup details.

# Tor Case Study	

## Compilation

### Go to the src directory of the case study 

<code>
$ cd case-studies/freetds/src/
</code>

### Ensure that you have all the necessary library files:

<code>
$ ls *.a
</code>

case-studies/freetds/src/libcrypto.a
case-studies/freetds/src/libevent.a
case-studies/freetds/src/libevent_core.a
case-studies/freetds/src/libevent_extra.a
case-studies/freetds/src/libevent_openssl.a
case-studies/freetds/src/libevent_pthreads.a
case-studies/freetds/src/libssl.a
case-studies/freetds/src/libz.a

### Compile the case study

<code>
$ make all
</code>

## Execution

### Start the Tor Node with the correct configuration files

<code>
$ ./app -f path_to_torrc_config_file
</code>

For example, you can start a chutney node with its custom configuration file

<code>
./app -f path_to_chutney/net/nodes/000a/torrc
</code>

## Setting up a Tor Network

Alternatively, you can setup your own Tor network, with custom configurations for nodes. We use Chutney for this purpose, similar to [OpenSGX Tor](https://github.com/sslab-gatech/opensgx/tree/master/Tor).  

### Install Tor to generate all the default configuration files, and install the Tor client

<code>
$ sudo apt-get install libevent-dev 
</code>

<code>
$ cd case-studies/tor/network-setup/tor-0.2.5.10
</code>

<code>
$ ./configure --disable-asciidoc
</code>

<code>
$ make
</code>

<code>
$ make install
</code>

### Create a Tor Network with Chutney

<code>
$ cd case-studies/tor/network-setup/chutney
</code>

<code>
$ ./chutney configure networks/testsuite
</code>

### Edit the Chutney configuration files
Change the value of RunAsDaemon flag from 1 to 0

<code>
$ vim case-studies/tor/network-setup/chutney/net/nodes/000a/torrc
</code>

<code>
Line 28: RunAsDaemon 0
</code>

### Launch the Tor network & Tor Client

Run each of the following commands in a new terminal

<code>
$ cd case-studies/freetds/src/
</code>

<code>
$ ./app -f ../network-setup/chutney/net/nodes/000a/torrc
</code>

<code>
$ ./app -f ../network-setup/chutney/net/nodes/001a/torrc
</code>

<code>
$ ./app -f ../network-setup/chutney/net/nodes/002a/torrc
</code>

<code>
$ ./app -f ../network-setup/chutney/net/nodes/003r/torrc
</code>

<code>
$ ./app -f ../network-setup/chutney/net/nodes/004r/torrc
</code>

<code>
$ ./app -f ../network-setup/chutney/net/nodes/005r/torrc
</code>

<code>
$ tor -f ../network-setup/chutney/net/nodes/006c/torrc
</code>
