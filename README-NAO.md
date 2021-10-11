# ChilitagsModule: Chilitags for NAO Robot
=====================================================

ChilitagsModule implements Chilitags (Bonnard et al., 2013) on a NAO robot (SoftBank Robotics Europe, France). Chilitags are 2D fiducial markers to detect objects and determine their positions. ChilitagsModule was tested on NAOqi 2.1 and 2.4 on a NAO robot. While Pepper robot (SoftBank Robotics Europe, France) also has a NAOqi operating system, ChilitagsModule was not tested on it.
 
For looking and pointing at objects with Chilitags using a NAO robot, see B. Irfan (2016), "Robust Pointing with NAO Robot", `https://github.com/birfan/NAOpointing`, which uses ChilitagsModule.

## Install Chilitags and ChilitagsModule on NAO Using Precompiled Libraries

* Open Choregraphe. From Connection -> Advanced, choose file transfer.

* Upload the precompiled ChilitagsModule files in *naoModule/compiled_files* to the robot (9 files).

* Connect to the robot using terminal (e.g. via putty from Windows).

* Run the following commands:

```
    $ su  (password is root)
    $ mv /usr/lib/libstdc++.so /usr/lib/libstdc++_nao.so
    $ mv /usr/lib/libstdc++.so.6 /usr/lib/libstdc++_nao.so.6
    $ mv /usr/lib/libstdc++.so.6.0.14 /usr/lib/libstdc++_nao.so.6.0.14
    $ mkdir dev
    $ cd dev
    $ mkdir bin
    $ mkdir lib
    $ cd ../..
    $ scp libchilitagsmodule.so /home/nao/dev/lib
    $ scp testchilitagsmodule* /home/nao/dev/bin
    $ scp libchilitags.so /usr/lib
    $ scp libchilitags_static.a /usr/lib
    $ scp libstdc++.so* /usr/lib

    $ nano naoqi/preferences/autoload.ini
```

* Add the following line under [user]

```
    /home/nao/dev/lib/libchilitagsmodule.so
```

* Save and close the file (Ctrl + Alt + X), and restart naoqi

```
    $ nao restart
```

* Test the module by running

```
    $ python dev/bin/testchilitagsmodule.py
```

* Then present Chilitags number 8 to NAO to retrieve the info.


## Install Chilitags and ChilitagsModule on NAO Using OpenNAO (Compile from Source)

Use the following instructions for compiling Chilitags and ChilitagsModule for NAO robot (using OpenNAO) and running the module on the robot, if the precompiled libraries do not work.

*   Download OpenNAO OS VirtualBox and C++ NAOqi cross toolchain for Linux 32 from Software (OR use the *libnaoqi_files* folder in *naoModule* folder provided instead of the toolchain) in 


    http://community.aldebaran.com


*   Setup OpenNAO using VirtualBox


*   Clone Chilitags and ChilitagsModule to OpenNAO: 


    git clone https://github.com/birfan/chilitags

```
    $ cd chilitags
```

*   Use the *naoModule/libnaoqi_files* folder to copy the files to *include*, *lib*, *bin*, *share/cmake* and *share/naoqi* (copy the naoqi folder completely) to */usr/local/include*, */usr/local/lib*, */usr/local/share*, */usr/local/bin*, respectively.

    OR  in the cross toolchain folder, go to *libnaoqi* folder and copy the files that contain "al" and "qi", along with "rttools" and "naoqi" from localhost to virtual (OpenNAO) to the respective places as above.

### Configure GCC to C++11

*    In OpenNAO:

```
    $ mkdir src

    $ mkdir dev
```

On local computer:


*   Get gcc-5.3.0


*   Copy the folder to OpenNAO:

```
    $ scp -P 2222 -r gcc-5.3.0/ nao@localhost:/home/nao/src/
```

On OpenNAO:

```
    $ cd src/gcc-5.3.0

    $ mkdir build && cd build

    $ ../configure --enable-languages=c,c++

    $ sudo make -j8

    $ sudo make install exec_prefix=/usr/local
```


*   Export the local library path to update the gcc

```
    $ export "LD_LIBRARY_PATH=/usr/local/lib"
```

*   In chilitags/CMakeLists.txt, change the add_definitions for c++11 to the format below:

```
    add_definitions(-std=gnu++11)
```

### Compile Chilitags

In *chilitags/build* folder:

*   To run it locally on the NAO:

```
   $ cmake .. -DCMAKE_CXX_COMPILER="/usr/local/bin/c++" -DCMAKE_C_COMPILER="/usr/local/bin/gcc" -DCMAKE_CXX_FLAGS_RELEASE="-O3 -DNDEBUG -D_GLIBCXX_USE_CXX11_ABI=0 -s -mtune=atom -mssse3 -mfpmath=sse" -DCMAKE_C_FLAGS_RELEASE="-O3 -DNDEBUG -s -mtune=atom -mssse3 -mfpmath=sse" -DWITH_NAOMODULE=ON -DWITH_TOOLS=ON -DCMAKE_BUILD_TYPE=Release -DCHILITAGSMODULE_IS_REMOTE=OFF
```

*   To run it remotely from OpenNAO:

```
    $ cmake .. -DCMAKE_CXX_COMPILER="/usr/local/bin/c++" -DCMAKE_C_COMPILER="/usr/local/bin/gcc" -DCMAKE_CXX_FLAGS_RELEASE="-O3 -DNDEBUG -D_GLIBCXX_USE_CXX11_ABI=0 -s -mtune=atom -mssse3 -mfpmath=sse" -DCMAKE_C_FLAGS_RELEASE="-O3 -DNDEBUG -s -mtune=atom -mssse3 -mfpmath=sse" -DWITH_NAOMODULE=ON -DWITH_TOOLS=ON -DCMAKE_BUILD_TYPE=Release -DCHILITAGSMODULE_IS_REMOTE=ON
```

### Rename Old Libraries On NAO

To be able to revert to the default libraries in case of any problems, rename the libraries on NAO:

```
    $ mkdir dev && cd dev

    $ mkdir bin && mkdir lib

    $ sudo mv /usr/lib/libstdc++.so /usr/lib/libstdc++_nao.so

    $ sudo mv /usr/lib/libstdc++.so.6 /usr/lib/libstdc++_nao.so.6

    $ sudo mv /usr/lib/libstdc++.so.6.0.14 /usr/lib/libstdc++_nao.so.6.0.14
```

## Run Chilitags on NAO Locally:


*   Send the code from OpenNAO to NAO:

```
    $ cd chilitags/build/naoModule

    $ scp libchilitagsmodule.so nao@robotIP:/home/nao/dev/lib

    $ scp testchilitagsmodule* nao@robotIP:/home/nao/dev/bin

    $ cd ../src

    $ scp libchilitags.so nao@robotIP:/usr/lib

    $ scp libchilitags_static.a nao@robotIP:/usr/lib
    
    $ cd /usr/local/lib

    $ scp libstdc++.so* nao@robotIP:/usr/lib
```

*   On NAO:

```
    $ nano naoqi/preferences/autoload.ini
```

*   Add the following line under [user]

```
    /home/nao/dev/lib/libchilitagsmodule.so
```

*   Save and close the file, and restart naoqi

```
    $ nao restart
```

*   When the robot starts (and all the modules load)

```
    $ cd dev/bin

    $ ./testchilitagsmodule "127.0.0.1"
```
    OR

```
    $ python testchilitagsmodule.py
```

## Run Chilitags Remotely (from OpenNAO):

(Comment /home/nao/dev/lib/libchilitagsmodule.so in the *autoload.ini* file, if previously added and restart Nao)

```
    $ cd chilitags/build/naoModule

    $ ./chilitagsmodule --pip robotIP --pport 9559

    $ ./testchilitagsmodule robotIP
```
    OR

```
    $ python testchilitagsmodule.py
```

## Coding style

This repository uses `uncrustify`, a tool that does automatic code formatting based on a predefined configuration defined in `uncrustify.cfg` (updated according to version 0.71.0) to keep the code formatting consistent with Chilitags. 

## License

ChilitagsModule is released under GNU Lesser General Public License v3.0 (LGPL3) in accordance with Chilitags (Bonnard et al., 2013). Cite the following if using this work:

 * Chilitags for NAO Robot. B. Irfan and S. Lemaignan. University of Plymouth, UK. `https://github.com/birfan/chilitags`. 2016.

 * Chilitags 2: Robust Fiducial Markers for Augmented Reality. Q. Bonnard, S. Lemaignan, G.  Zufferey, A. Mazzei, S. Cuendet, N. Li, P. Dillenbourg. CHILI, EPFL, Switzerland. `http://chili.epfl.ch/software`. 2013.

```
	@misc{chilitagsModule,
		title = {Chilitags for NAO Robot},
		author={Irfan, Bahar and Lemaignan, S\'{e}verin},
		publisher={University of Plymouth, UK},
		url={https://github.com/birfan/chilitags},
		year={2016}
	}

	@misc{chilitags,
		title = {Chilitags 2: Robust Fiducial Markers for Augmented Reality and Robotics.},
		author={Bonnard, Quentin and Lemaignan, S\'{e}verin and Zufferey, Guillaume and Mazzei, Andrea and Cuendet, S\'{e}bastien and Li, Nan and \"{O}zg\"{u}r, Ayberk and Dillenbourg, Pierre},
		publisher={CHILI, EPFL, Switzerland},
		url={http://chili.epfl.ch/software},
		year={2013}
	}
```

## Contact

If you need further information about using Chilitags with the NAO robot, contact Bahar Irfan: bahar.irfan (at) plymouth (dot) ac (dot) uk (the most recent contact information is available at [personal website](https://www.baharirfan.com)).
