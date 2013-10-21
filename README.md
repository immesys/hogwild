HOGWILD
=======

HOGwild is a simple HOG implementation that is in the process of being ported to
the RISC-V architecture.

Dependencies
------------

You can get install the dependencies on Ubuntu with:

    $ sudo apt-get install build-essential check libopencv-dev 
    
There might be some dependencies missing.

Building
--------

To build, run:
    
    $ autoreconf -i
    $ ./configure
    $ make
    
You need check and opencv installed. 
