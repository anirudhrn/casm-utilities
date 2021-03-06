# casm-utilities
A collection of utilities that make use of the [CASM](https://github.com/prisms-center/CASMcode) libraries. The repository also includes its own library, which wraps around CASM to provide a useable interface, as well as python modules that can call said interface interactively.

## Getting started
This project relies heavily on [CASM](https://github.com/prisms-center/CASMcode), which will be internally compiled.
In order to use this repository, you'll need to have any dependencies of CASM installed, namely the [boost](https://www.boost.org/) libraries.

casm-utilities uses autotools to build and install everything, so if you're installing via git cloning, a few additional packages might need to be installed on your computer:

* autoconf
* automake
* libtool
* autoconf-archive

These should all be readily available via `brew` and `apt-get`.

### Installation
The repository comes with three main components:

* The utilities library (c++)
* A collection of command line utilities
* Python wrappers for the c++ utilities library

Though it is recommended to simply install all three simultaneously, you can toggle any of these components out of the installation process by commenting out the appropriate line `Makemfile.am`.

#### Cloning and generate the configure script
This repository includes a few submodules that are needed in order to fully compile everything.
If you plan on cloning the repository, be sure to do it recursively:
```
git clone --recurse-submodules
```

If you're trying to install after cloning the git repository, you'll first have to generate the `configure` script using the provided script:
```
./boostrap.sh
```

#### Configure the compile environment
Skip this section entirely if you're familiar with the standard `./configure && make && make install` procedure.
If you're unsure what do do, just follow the recommended steps here.

Begin by creating a build directory, this is where all the compilation will take place:
```
mkdir build
cd build
```

You are now ready to run the configure script, which will generate a `Makefile`.
This is the step where you get to specify any compilation flags you might want, as well as where to install everything provided by casm-utilities.
You can bypass the need for admin privileges by using the `--prefix` option (recommended): `--prefix=$HOME/.local`

Once you're set on what flags you need, put it all together to run the configure script:
```
../configure --prefix=$HOME/.local CXXFLAGS='-Any-flags -You -Might-want'    
```

For more information on the configure step, see the documentation by calling `../configure -h`.

#### Make and install casm-utilities
This one is easy:
```
make && make install
```

Be sure to have your `PATH` environment variable pointing at whatever value you chose for your `--prefix`, with `/bin` appended to it.
